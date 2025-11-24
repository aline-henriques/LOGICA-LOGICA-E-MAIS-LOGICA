#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/stat.h>

#include "screen.h"
#include "keyboard.h"
#include "jogador.h"
#include "questoes.h"
#include "ranking.h"
#include "timer.h"
#include "menu.h"
#include "mapa.h"
#include "historia.h"

#define FASE_VILA 1
#define FASE_FLORESTA 2
#define FASE_MASMORRA 3

#define MODO_MAPA 100
#define MODO_INVENTARIO_MAPA 101
#define STATE_PLAYER_MAIN_MENU 0
#define STATE_PLAYER_SPELL_MENU 1
#define STATE_PLAYER_ITEM_MENU 2
#define STATE_PLAYER_SPELL_CARD 3
#define STATE_PLAYER_OFFENSIVE_QUIZ 4
#define STATE_ENEMY_TURN_START 5
#define STATE_PLAYER_DEFENSIVE_QUIZ 6
#define STATE_ACTION_RESOLVE 7

#define MY_KEY_UP 1000
#define MY_KEY_DOWN 1001
#define MY_KEY_LEFT 1002
#define MY_KEY_RIGHT 1003
#define MY_KEY_ENTER 10
#define MY_KEY_ESC 27
#define MY_KEY_BACKSPACE 127

#define MAPA_ALTURA 15
#define MAPA_LARGURA 110

int fase_atual = FASE_VILA;
char player_model[3][4] = {" O ", "-|-", "/ \\"};
Entity *global_player;
Entity global_enemy;
int global_player_x, global_player_y;
int global_score = 0;
int global_quiz_attempts = 1;
int global_enemy_damage = 0;
LogicQuestion global_current_question;
int combat_state = MODO_MAPA;
int menu_selecao = 0, spell_selecionada = 0;
char mensagem_log[100] = "Bem-vindo a Synapse.";
int temChaveDaMasmorra = 0;
char nome_do_mestre[30] = "Mestre Desconhecido";

static int dialogo_inicial_mestre_feito = 0;
int cerbero_derrotado = 0;
int golem_derrotado = 0;
int agua_purificada = 0;

void inicializar_jogo();
void mostrar_mensagem_mapa(const char *mensagem);
void desenhar_hud_mapa();
int get_input();
void tocar_musica(const char *arquivo);
void parar_musica();
void desenhar_quiz(const char *titulo, int is_vila);
void desenhar_menu_magia();
void desenhar_menu_itens_combate();
void desenhar_spell_card(int spell_index);
void desenhar_tela_combate(int is_boss);
void processar_input_combate(int key, int *rodando, int is_boss);
void processar_turno_inimigo();
int iniciar_combate(const char *nome_inimigo, int hp_inimigo, int is_boss);
void processar_input_inventario_mapa(int key);
void processar_input_mapa(int key, int *rodando);
void desenhar_inventario_mapa();
void carregar_fase_logica(int fase);
void mostrar_popup_detalhes(const char *titulo, const char *desc1, const char *desc2, const char *desc3);
void desenhar_janela_main(int x1, int y1, int x2, int y2, const char *titulo);
int fibonacci_recursivo(int n);

int fibonacci_recursivo(int n)
{
    if (n <= 1)
        return n;
    return fibonacci_recursivo(n - 1) + fibonacci_recursivo(n - 2);
}

void tocar_musica(const char *arquivo)
{
}
void parar_musica()
{
}
void delay_ms(int ms)
{
    timerInit(ms);
    while (!timerTimeOver())
    {
    }
    timerDestroy();
}
void limpar_tela_preto()
{
    screenHomeCursor();
    screenSetColor(WHITE, BLACK);
    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < 120; j++)
            printf(" ");
        printf("\n");
    }
    screenHomeCursor();
}

void desenhar_janela_main(int x1, int y1, int x2, int y2, const char *titulo)
{
    int i;
    screenBoxEnable();
    screenSetColor(WHITE, BLACK);
    screenGotoxy(x1, y1);
    printf("%c", BOX_UPLEFT);
    for (i = x1 + 1; i < x2; i++)
        printf("%c", BOX_HLINE);
    screenGotoxy(x2, y1);
    printf("%c", BOX_UPRIGHT);
    for (i = y1 + 1; i < y2; i++)
    {
        screenGotoxy(x1, i);
        printf("%c", BOX_VLINE);
        screenGotoxy(x2, i);
        printf("%c", BOX_VLINE);
    }
    screenGotoxy(x1, y2);
    printf("%c", BOX_DWNLEFT);
    for (i = x1 + 1; i < x2; i++)
        printf("%c", BOX_HLINE);
    screenGotoxy(x2, y2);
    printf("%c", BOX_DWNRIGHT);
    screenBoxDisable();
    if (titulo && strlen(titulo) > 0)
    {
        int c = x1 + ((x2 - x1) / 2) - (strlen(titulo) / 2) - 1;
        screenGotoxy(c, y1);
        printf(" %s ", titulo);
    }
    screenSetNormal();
}

int get_input()
{
    int key = readch();
    if (key == 27)
    {
        if (keyhit())
        {
            int k2 = readch();
            if (k2 == 91)
            {
                int k3 = readch();
                if (k3 == 65)
                    return MY_KEY_UP;
                if (k3 == 66)
                    return MY_KEY_DOWN;
                if (k3 == 67)
                    return MY_KEY_RIGHT;
                if (k3 == 68)
                    return MY_KEY_LEFT;
            }
        }
        return MY_KEY_ESC;
    }
    if (key == 10)
        return MY_KEY_ENTER;
    if (key == 127 || key == 8)
        return MY_KEY_BACKSPACE;
    return key;
}

void carregar_fase_logica(int fase)
{
    carregar_mapa_fase(fase);
    if (fase == FASE_VILA)
    {
        global_player_x = 35;
        global_player_y = 8;
    }
    else if (fase == FASE_FLORESTA)
    {
        global_player_x = 5;
        global_player_y = 10;
    }
    else
    {
        global_player_x = 5;
        global_player_y = 5;
    }
}

void mostrar_popup_detalhes(const char *titulo, const char *desc1, const char *desc2, const char *desc3)
{
    limpar_tela_preto();
    desenhar_janela_main(10, 8, 70, 18, "OBTIDO");

    screenGotoxy(15, 10);
    screenSetColor(YELLOW, BLACK);
    printf("%s", titulo);
    screenGotoxy(15, 12);
    screenSetColor(WHITE, BLACK);
    printf("%s", desc1);
    if (desc2)
    {
        screenGotoxy(15, 13);
        printf("%s", desc2);
    }
    if (desc3)
    {
        screenGotoxy(15, 14);
        printf("%s", desc3);
    }

    screenGotoxy(15, 16);
    screenSetColor(DARKGRAY, BLACK);
    printf("[Pressione Enter]");
    screenSetNormal();
    screenUpdate();
    while (get_input() != MY_KEY_ENTER)
        ;
    limpar_tela_preto();
}

void processar_interacao_vila()
{
    limpar_tela_preto();
    desenhar_janela_main(10, 5, 78, 20, "MESTRE DA LOGICA");
    screenUpdate();

    if (!dialogo_inicial_mestre_feito)
    {
        screenGotoxy(15, 8);
        printf("Ola aprendiz. Eu sou o Guardiao desta Vila.");
        screenGotoxy(15, 10);
        printf("Mas minha memoria falha... Qual o meu nome?");
        screenGotoxy(15, 12);
        printf("Nome: ");
        screenUpdate();

        screenShowCursor();
        int i = 0;
        int start_x = 21;
        int start_y = 12;
        screenGotoxy(start_x, start_y);

        while (1)
        {
            int k = get_input();
            if (k == MY_KEY_ENTER)
                break;
            else if (k == MY_KEY_BACKSPACE)
            {
                if (i > 0)
                {
                    i--;
                    screenGotoxy(start_x + i, start_y);
                    printf(" ");
                    screenGotoxy(start_x + i, start_y);
                    screenUpdate();
                }
            }
            else if (k >= 32 && k <= 126 && i < 28)
            {
                nome_do_mestre[i] = (char)k;
                printf("%c", (char)k);
                i++;
                screenUpdate();
            }
        }
        nome_do_mestre[i] = '\0';
        if (i == 0)
            strcpy(nome_do_mestre, "Mestre");
        screenHideCursor();

        screenGotoxy(15, 14);
        printf("Ah, sim! Eu sou %s.", nome_do_mestre);
        screenGotoxy(15, 16);
        printf("[Enter para continuar]");
        screenUpdate();
        while (get_input() != MY_KEY_ENTER)
            ;

        dialogo_inicial_mestre_feito = 1;
        limpar_tela_preto();
        desenhar_janela_main(10, 5, 78, 20, nome_do_mestre);
    }
    else
    {
        desenhar_janela_main(10, 5, 78, 20, nome_do_mestre);
    }

    screenGotoxy(15, 7);
    printf("Seu Score: %d", global_score);
    screenGotoxy(15, 9);
    printf("[1] Bola da Disjuncao (Gratis)");
    screenGotoxy(15, 10);
    printf("[2] Flechas Bicondicional (Gratis)");
    screenGotoxy(15, 11);
    printf("[3] Explosao de Tautologia (300 Pts)");
    screenGotoxy(15, 12);
    printf("[4] Paradoxo Temporal (800 Pts)");
    screenGotoxy(15, 14);
    printf("[ESC] Sair");
    screenUpdate();

    int k = get_input();
    int custo = 0, spell_idx = -1;

    if (k == '1')
    {
        spell_idx = 0;
        custo = 0;
    }
    else if (k == '2')
    {
        spell_idx = 1;
        custo = 0;
    }
    else if (k == '3')
    {
        spell_idx = 3;
        custo = 300;
    }
    else if (k == '4')
    {
        spell_idx = 4;
        custo = 800;
    }
    else
        return;

    if (get_spell(spell_idx).desbloqueada)
    {
        mostrar_mensagem_mapa("Voce ja sabe esse feitico!");
    }
    else
    {
        if (global_score >= custo)
        {
            limpar_tela_preto();
            LogicQuestion q = get_questao_vila();
            desenhar_quiz("PROVA DE MAGIA", 1);
            int key = get_input();
            if (toupper(key) == q.resposta_correta)
            {
                global_score -= custo;
                desbloquear_feitico(spell_idx);
                Spell s = get_spell(spell_idx);
                char buff1[50], buff2[50];
                sprintf(buff1, "Dano: %d", s.dano);
                sprintf(buff2, "Custo MP: %d", s.custo_mp);
                mostrar_popup_detalhes(s.nome, "Feitico Logico Poderoso", buff1, buff2);
            }
            else
            {
                mostrar_mensagem_mapa("Voce falhou no teste. Tente novamente.");
            }
        }
        else
        {
            mostrar_mensagem_mapa("Score insuficiente.");
        }
    }
    limpar_tela_preto();
}

void interagir_agua(int targetX, int targetY)
{
    if (agua_purificada)
    {
        global_player_x = targetX;
        global_player_y = targetY;
        return;
    }

    limpar_tela_preto();
    desenhar_janela_main(10, 8, 70, 15, "AGUA PROFUNDA");
    screenGotoxy(15, 10);
    printf("Deseja nadar? (S/N)");
    screenUpdate();
    int k = get_input();

    if (toupper(k) == 'S')
    {
        int dado = rolar_dado_d20();
        char msg[50];
        sprintf(msg, "Voce rolou: %d", dado);
        mostrar_mensagem_mapa(msg);

        if (dado < 10)
        {
            mostrar_mensagem_mapa("Uma SEREIA DO SOFISMA te puxa!");
            int res = iniciar_combate("SEREIA DO SOFISMA", 80, 0);

            if (res == 1)
            {
                agua_purificada = 1;
                global_player_x = targetX;
                global_player_y = targetY;
                mostrar_mensagem_mapa("Voce venceu! As aguas se acalmaram.");
            }
        }
        else
        {
            mostrar_mensagem_mapa("Voce nadou com seguranca.");
            agua_purificada = 1;
            global_player_x = targetX;
            global_player_y = targetY;
        }
    }
    limpar_tela_preto();
}

void interagir_arvore(int cx, int cy)
{
    limpar_tela_preto();
    desenhar_janela_main(10, 8, 70, 15, "ARVORE ANTIGA");
    screenGotoxy(15, 10);
    printf("Balancar a arvore? (S/N)");
    screenUpdate();
    int k = get_input();

    if (toupper(k) == 'S')
    {
        set_mapa_char(cx, cy, 't');

        int r = rand() % 100;
        if (r < 40)
        {
            adicionar_item_mapa_logica("Pocao de Cura", 1);
            mostrar_popup_detalhes("POCAO DE CURA", "Restaura 50 HP", "Use em batalha", NULL);
        }
        else if (r < 60)
        {
            adicionar_item_mapa_logica("Pocao de MP", 1);
            mostrar_popup_detalhes("POCAO DE MP", "Restaura 30 MP", "Essencial para magias", NULL);
        }
        else
        {
            mostrar_mensagem_mapa("Apenas folhas secas cairam...");
        }
    }
    limpar_tela_preto();
}

void abrir_bau_logico()
{
    if (temChaveDaMasmorra)
    {
        mostrar_mensagem_mapa("O bau ja esta vazio.");
        return;
    }

    limpar_tela_preto();
    desenhar_janela_main(2, 4, 108, 22, "GNOMO DE GIZE");

    screenSetColor(GREEN, BLACK);
    screenGotoxy(35, 6);
    printf("(o.o) 'DECIFRA-ME OU PERDE MP!'");
    screenSetColor(WHITE, BLACK);

    LogicQuestion q = get_questao_bau();
    screenGotoxy(5, 10);
    printf("%s", q.pergunta);
    screenGotoxy(5, 12);
    printf("%s", q.op_a);
    screenGotoxy(5, 13);
    printf("%s", q.op_b);
    screenGotoxy(5, 14);
    printf("%s", q.op_c);

    screenGotoxy(5, 17);
    printf("Sua resposta: ");
    screenUpdate();
    int key = get_input();
    if (toupper(key) == q.resposta_correta)
    {
        global_score += 100;
        mostrar_popup_detalhes("CHAVE DA MASMORRA", "Abre a porta final", "Ganhos: +100 Score", NULL);
        temChaveDaMasmorra = 1;
        adicionar_item_mapa_logica("Chave da Masmorra", 1);
        for (int y = 0; y < MAPA_ALTURA; y++)
            for (int x = 0; x < MAPA_LARGURA; x++)
                if (get_mapa_char(x, y) == 'B')
                    set_mapa_char(x, y, 'b');
    }
    else
    {
        global_player->mp -= 10;
        global_score -= 50;
        if (global_player->mp < 0)
            global_player->mp = 0;
        mostrar_mensagem_mapa("Gnomo: 'TOLO! (-50 pts / -10 MP)'");
    }
}

void mostrar_historia_masmorra_local()
{
    limpar_tela_preto();
    desenhar_janela_main(10, 5, 70, 20, "O CHEFE FINAL");
    screenGotoxy(15, 10);
    printf("A porta se abre...");
    screenUpdate();
    delay_ms(2000);

    limpar_tela_preto();
    desenhar_janela_main(10, 5, 80, 20, "DESAFIO DO INFINITO");
    screenGotoxy(12, 8);
    printf("Boss: 'Prove que entende o infinito!'");
    screenGotoxy(12, 10);
    printf("Qual o 10o termo de Fibonacci? (Dica: 55)");
    screenGotoxy(12, 12);
    printf("Sua resposta: ");
    screenUpdate();

    int i = 0;
    char buf[10];
    screenShowCursor();
    while (i < 3)
    {
        int k = get_input();
        if (k == 10)
            break;
        if (isdigit(k))
        {
            buf[i++] = k;
            printf("%c", k);
            screenUpdate();
        }
    }
    buf[i] = '\0';
    screenHideCursor();

    int resposta = atoi(buf);
    if (resposta == fibonacci_recursivo(10))
    {
        mostrar_mensagem_mapa("Boss: 'Maldito! Vamos lutar!'");
        combat_state = STATE_PLAYER_MAIN_MENU;
        if (iniciar_combate("MATEMATICADOR", 200, 1) == 1)
        {
            final_cesar_school();
            global_player->hp = -999;
        }
    }
    else
    {
        mostrar_mensagem_mapa("Boss: 'Incapaz! Suma!' (-500 HP)");
        global_player->hp = -999;
    }
}

int pode_mover(int novoX, int novoY)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (player_model[i][j] == ' ')
                continue;
            int cx = novoX + j;
            int cy = novoY + i;
            char target = get_mapa_char(cx, cy);

            switch (target)
            {
            case '#':
            case 'H':
                return 0;
            case 'T':
                interagir_arvore(cx, cy);
                return 0;
            case 't':
                return 0;
            case '^':
                return 0;
            case '~':
                interagir_agua(novoX, novoY);
                return 0;
            case '$':
                adicionar_item_mapa_logica("Pocao de Cura", 1);
                set_mapa_char(cx, cy, '.');
                mostrar_popup_detalhes("POCAO DE CURA", "Achado no chao", "+50 HP", NULL);
                return 1;
            case 'M':
                processar_interacao_vila();
                return 0;
            case 'C':
                if (iniciar_combate("CERBERO DO ERRO", 100, 1) == 1)
                {
                    set_mapa_char(cx, cy, '.');
                    cerbero_derrotado = 1;
                    mostrar_mensagem_mapa("Monstro derrotado!");
                }
                return 1;
            case 'G':
                if (iniciar_combate("GOLEM DA GEOMETRIA", 120, 1) == 1)
                {
                    set_mapa_char(cx, cy, '.');
                    golem_derrotado = 1;
                    mostrar_mensagem_mapa("Golem desmontado!");
                }
                return 1;
            case '>':
                if (fase_atual == FASE_VILA)
                {
                    fase_atual = FASE_FLORESTA;
                    carregar_fase_logica(fase_atual);
                }
                else if (fase_atual == FASE_FLORESTA)
                {
                    if (cerbero_derrotado && golem_derrotado)
                    {
                        fase_atual = FASE_MASMORRA;
                        carregar_fase_logica(fase_atual);
                        mostrar_mensagem_mapa("Voce chegou a Masmorra Final!");
                    }
                    else
                    {
                        mostrar_mensagem_mapa("A barreira magica bloqueia! Derrote os guardioes.");
                    }
                }
                return 0;
            case '<':
                if (fase_atual == FASE_FLORESTA)
                {
                    fase_atual = FASE_VILA;
                    carregar_fase_logica(fase_atual);
                }
                return 0;
            case 'B':
                abrir_bau_logico();
                return 0;
            case 'b':
                return 0;
            case 'D':
                if (temChaveDaMasmorra)
                    mostrar_historia_masmorra_local();
                else
                    mostrar_mensagem_mapa("Trancado. Precisa da chave do Gnomo.");
                return 0;
            }
        }
    }
    return 1;
}

void processar_input_mapa(int key, int *rodando)
{
    int novoX = global_player_x;
    int novoY = global_player_y;
    switch (key)
    {
    case 'w':
    case 'W':
    case MY_KEY_UP:
        novoY--;
        break;
    case 's':
    case 'S':
    case MY_KEY_DOWN:
        novoY++;
        break;
    case 'a':
    case 'A':
    case MY_KEY_LEFT:
        novoX--;
        break;
    case 'd':
    case 'D':
    case MY_KEY_RIGHT:
        novoX++;
        break;
    case 'e':
    case 'E':
        combat_state = MODO_INVENTARIO_MAPA;
        return;
    case MY_KEY_ESC:
        *rodando = 0;
        return;
    }
    if (pode_mover(novoX, novoY))
    {
        global_player_x = novoX;
        global_player_y = novoY;
    }
    if (global_player->hp <= 0)
        *rodando = 0;
}

void processar_input_inventario_mapa(int key)
{
    switch (key)
    {
    case 'e':
    case 'E':
    case MY_KEY_ESC:
        combat_state = MODO_MAPA;
        break;
    }
}

void desenhar_hud_mapa()
{
    screenSetColor(WHITE, BLACK);
    screenGotoxy(2, 15 + 2);
    printf("============================================================================");
    screenGotoxy(4, 15 + 3);
    screenSetColor(LIGHTGREEN, BLACK);
    printf(" VIDA: %d/%d ", global_player->hp, global_player->max_hp);
    screenGotoxy(30, 15 + 3);
    screenSetColor(LIGHTBLUE, BLACK);
    printf(" MANA: %d/%d ", global_player->mp, global_player->max_mp);
    screenGotoxy(55, 15 + 3);
    screenSetColor(YELLOW, BLACK);
    printf(" SCORE: %05d ", global_score);
    screenSetColor(WHITE, BLACK);
    screenGotoxy(4, 15 + 4);
    printf("[W,A,S,D] Mover   [E] Inventario   [ESC] Sair");
    screenGotoxy(4, 15 + 6);
    screenSetColor(YELLOW, BLACK);
    printf("> %s", mensagem_log);
    screenSetNormal();
}

void mostrar_mensagem_mapa(const char *mensagem)
{
    strcpy(mensagem_log, mensagem);
    desenhar_hud_mapa();
    screenUpdate();
    get_input();
    strcpy(mensagem_log, "");
}

void desenhar_inventario_mapa()
{
    limpar_tela_preto();
    desenhar_janela_main(10, 4, 70, 18, "MOCHILA");
    int num_itens = get_num_itens();
    screenSetColor(WHITE, BLACK);
    if (num_itens == 0)
    {
        screenGotoxy(15, 8);
        printf("Vazio...");
    }
    else
    {
        for (int i = 0; i < num_itens; i++)
        {
            Item *item = get_item(i);
            if (item && item->quantidade > 0)
            {
                screenGotoxy(15, 8 + i);
                printf("%d. %s (x%d)", i + 1, item->nome, item->quantidade);
            }
        }
    }
    screenGotoxy(15, 16);
    printf("Pressione [E] ou [ESC].");
    screenSetNormal();
    screenUpdate();
}

void desenhar_hp_bar_combate(Entity *e, int x, int y, int largura, int is_player)
{
    screenGotoxy(x, y);
    screenSetColor(is_player ? LIGHTGREEN : LIGHTRED, BLACK);
    printf("%s", e->nome);
    screenSetColor(WHITE, BLACK);
    float perc_hp = (float)e->hp / e->max_hp;
    int blocos_hp = (int)(perc_hp * largura);
    screenGotoxy(x, y + 1);
    screenSetColor(RED, BLACK);
    for (int i = 0; i < largura; i++)
        printf(i < blocos_hp ? "%c" : "%c", i < blocos_hp ? 219 : 176);
    screenSetColor(WHITE, BLACK);
    printf(" %d", e->hp);
    screenGotoxy(x, y + 2);
    screenSetColor(BLUE, BLACK);
    float perc_mp = (float)e->mp / e->max_mp;
    int blocos_mp = (int)(perc_mp * largura);
    for (int i = 0; i < largura; i++)
        printf(i < blocos_mp ? "%c" : "%c", i < blocos_mp ? 219 : 176);
    screenSetColor(WHITE, BLACK);
    printf(" %d", e->mp);
}

void desenhar_tela_combate(int is_boss)
{
    limpar_tela_preto();
    desenhar_janela_main(1, 1, 80, 24, "COMBATE");

    if (strstr(global_enemy.nome, "MATEMATICADOR"))
    {
        screenSetColor(LIGHTMAGENTA, BLACK);
        screenGotoxy(55, 4);
        printf("   /-\\   ");
        screenGotoxy(55, 5);
        printf("  (o_o)  ");
        screenGotoxy(55, 6);
        printf("  /|_|\\  ");
    }
    else if (strstr(global_enemy.nome, "CERBERO"))
    {
        screenSetColor(RED, BLACK);
        screenGotoxy(50, 4);
        printf(" (o)(o)(o) ");
        screenGotoxy(50, 5);
        printf("  \\_|_|_/  ");
        screenGotoxy(50, 6);
        printf("   /   \\   ");
    }
    else if (strstr(global_enemy.nome, "GOLEM"))
    {
        screenSetColor(LIGHTGRAY, BLACK);
        screenGotoxy(55, 4);
        printf("  [o_o]  ");
        screenGotoxy(55, 5);
        printf("  /| |\\  ");
        screenGotoxy(55, 6);
        printf("  |_|_|  ");
    }
    else
    {
        screenSetColor(LIGHTBLUE, BLACK);
        screenGotoxy(55, 4);
        printf("   .~.   ");
        screenGotoxy(55, 5);
        printf("  (o.o)  ");
        screenGotoxy(55, 6);
        printf("   /|\\   ");
        screenGotoxy(55, 7);
        printf("  // \\\\  ");
    }

    desenhar_hp_bar_combate(&global_enemy, 45, 8, 20, 0);

    screenSetColor(CYAN, BLACK);
    screenGotoxy(10, 5);
    printf("    O    ");
    screenGotoxy(10, 6);
    printf("   /|\\   ");
    screenGotoxy(10, 7);
    printf("   / \\   ");
    desenhar_hp_bar_combate(global_player, 5, 8, 20, 1);
    screenGotoxy(3, 15);
    screenSetColor(WHITE, BLACK);
    printf("---------------------------------------------------------------------------");
    if (combat_state == STATE_PLAYER_MAIN_MENU)
    {
        int y = 17;
        screenGotoxy(5, y);
        if (menu_selecao == 0)
            screenSetColor(YELLOW, BLACK);
        else
            screenSetColor(WHITE, BLACK);
        printf(menu_selecao == 0 ? "> ATACAR" : "  ATACAR");
        screenGotoxy(25, y);
        if (menu_selecao == 1)
            screenSetColor(YELLOW, BLACK);
        else
            screenSetColor(WHITE, BLACK);
        printf(menu_selecao == 1 ? "> MAGIA " : "  MAGIA ");
        screenGotoxy(45, y);
        if (menu_selecao == 2)
            screenSetColor(YELLOW, BLACK);
        else
            screenSetColor(WHITE, BLACK);
        printf(menu_selecao == 2 ? "> ITEM  " : "  ITEM  ");
        screenGotoxy(60, y);
        screenSetColor(DARKGRAY, BLACK);
        printf(" [ BLOQUEADO ]");
    }
    screenGotoxy(5, 20);
    screenSetColor(YELLOW, BLACK);
    printf("LOG: %s", mensagem_log);
    screenSetNormal();
}

void desenhar_menu_magia()
{
    limpar_tela_preto();
    desenhar_janela_main(15, 5, 75, 18, "GRIMORIO");
    int num_spells = get_num_spells();
    for (int i = 0; i < num_spells; i++)
    {
        Spell s = get_spell(i);
        screenGotoxy(17, 8 + (i * 2));
        if (!s.desbloqueada)
        {
            screenSetColor(DARKGRAY, BLACK);
            printf("   [ BLOQUEADO ]");
        }
        else
        {
            if (menu_selecao == i)
            {
                screenSetColor(YELLOW, BLACK);
                printf(">> %s (%d MP)", s.nome, s.custo_mp);
            }
            else
            {
                screenSetColor(WHITE, BLACK);
                printf("   %s (%d MP)", s.nome, s.custo_mp);
            }
        }
    }
}
void desenhar_menu_itens_combate()
{
    limpar_tela_preto();
    desenhar_janela_main(15, 5, 65, 18, "BOLSA");
    int num_itens = get_num_itens();
    if (num_itens == 0)
    {
        screenGotoxy(20, 8);
        printf("Vazio...");
    }
    for (int i = 0; i < num_itens; i++)
    {
        Item *item = get_item(i);
        if (item && item->quantidade > 0)
        {
            screenGotoxy(17, 8 + i);
            if (menu_selecao == i)
            {
                screenSetColor(YELLOW, BLACK);
                printf(">> %s (x%d)", item->nome, item->quantidade);
            }
            else
            {
                screenSetColor(WHITE, BLACK);
                printf("   %s (x%d)", item->nome, item->quantidade);
            }
        }
    }
}
void desenhar_spell_card(int spell_index)
{
    limpar_tela_preto();
    desenhar_janela_main(15, 6, 65, 18, "CONJURANDO");
    screenGotoxy(20, 9);
    printf("FEITICO: %s", get_spell(spell_index).nome);
    screenGotoxy(20, 11);
    printf("DANO: %d", get_spell(spell_index).dano);
    screenGotoxy(20, 14);
    screenSetColor(YELLOW, BLACK);
    printf("Prepare-se...");
    screenSetNormal();
    screenUpdate();
}
void desenhar_quiz(const char *titulo, int is_vila)
{
    limpar_tela_preto();
    desenhar_janela_main(5, 2, 75, 20, titulo);
    screenGotoxy(8, 5);
    screenSetColor(CYAN, BLACK);
    printf("%s", global_current_question.pergunta);
    screenSetColor(WHITE, BLACK);
    screenGotoxy(10, 8);
    printf("[A] %s", global_current_question.op_a);
    screenGotoxy(10, 10);
    printf("[B] %s", global_current_question.op_b);
    screenGotoxy(10, 12);
    printf("[C] %s", global_current_question.op_c);
    screenGotoxy(8, 16);
    printf("Resposta: ");
    screenShowCursor();
    screenUpdate();
}
void processar_turno_inimigo()
{
    global_enemy_damage = 10 + (rand() % 6);
    sprintf(mensagem_log, "Inimigo ataca!");
    global_quiz_attempts = 1;
    global_current_question = get_questao_aleatoria();
    combat_state = STATE_PLAYER_DEFENSIVE_QUIZ;
}

void processar_input_combate(int key, int *rodando, int is_boss)
{
    if (combat_state == STATE_PLAYER_MAIN_MENU)
    {
        switch (key)
        {
        case 'a':
        case 'A':
        case MY_KEY_LEFT:
            menu_selecao--;
            if (menu_selecao < 0)
                menu_selecao = 3;
            break;
        case 'd':
        case 'D':
        case MY_KEY_RIGHT:
            menu_selecao++;
            if (menu_selecao > 3)
                menu_selecao = 0;
            break;
        case MY_KEY_ENTER:
            if (menu_selecao == 0)
            {
                spell_selecionada = 2;
                global_quiz_attempts = 1;
                global_current_question = get_questao_aleatoria();
                combat_state = STATE_PLAYER_SPELL_CARD;
            }
            else if (menu_selecao == 1)
            {
                combat_state = STATE_PLAYER_SPELL_MENU;
                menu_selecao = 0;
            }
            else if (menu_selecao == 2)
            {
                combat_state = STATE_PLAYER_ITEM_MENU;
                menu_selecao = 0;
            }
            else if (menu_selecao == 3)
            {
                strcpy(mensagem_log, "Fuga Bloqueada!");
            }
            break;
        }
    }
    else if (combat_state == STATE_PLAYER_SPELL_MENU)
    {
        switch (key)
        {
        case 'w':
        case 'W':
        case MY_KEY_UP:
            menu_selecao--;
            if (menu_selecao < 0)
                menu_selecao = get_num_spells() - 1;
            break;
        case 's':
        case 'S':
        case MY_KEY_DOWN:
            menu_selecao++;
            if (menu_selecao >= get_num_spells())
                menu_selecao = 0;
            break;
        case MY_KEY_ENTER:
        {
            Spell s = get_spell(menu_selecao);
            if (!s.desbloqueada)
            {
                strcpy(mensagem_log, "Feitico bloqueado!");
            }
            else if (global_player->mp >= s.custo_mp)
            {
                spell_selecionada = menu_selecao;
                global_quiz_attempts = 1;
                global_current_question = get_questao_aleatoria();
                combat_state = STATE_PLAYER_SPELL_CARD;
            }
            else
            {
                strcpy(mensagem_log, "Sem MP!");
            }
            break;
        }
        case MY_KEY_ESC:
            combat_state = STATE_PLAYER_MAIN_MENU;
            menu_selecao = 0;
            break;
        }
    }
    else if (combat_state == STATE_PLAYER_ITEM_MENU)
    {
        if (get_num_itens() == 0)
        {
            combat_state = STATE_PLAYER_MAIN_MENU;
            return;
        }
        switch (key)
        {
        case 'w':
        case 'W':
        case MY_KEY_UP:
            menu_selecao--;
            if (menu_selecao < 0)
                menu_selecao = get_num_itens() - 1;
            break;
        case 's':
        case 'S':
        case MY_KEY_DOWN:
            menu_selecao++;
            if (menu_selecao >= get_num_itens())
                menu_selecao = 0;
            break;
        case MY_KEY_ENTER:
        {
            const char *res = usar_item_jogador(menu_selecao);
            sprintf(mensagem_log, "%s", res);
            combat_state = STATE_ACTION_RESOLVE;
            break;
        }
        case MY_KEY_ESC:
            combat_state = STATE_PLAYER_MAIN_MENU;
            break;
        }
    }
    else if (combat_state == STATE_PLAYER_OFFENSIVE_QUIZ || combat_state == STATE_PLAYER_DEFENSIVE_QUIZ)
    {
        screenHideCursor();
        LogicQuestion q = global_current_question;
        int acertou = (toupper(key) == q.resposta_correta);
        if (acertou)
        {
            if (combat_state == STATE_PLAYER_OFFENSIVE_QUIZ)
            {
                global_score += 100;
                Spell s = get_spell(spell_selecionada);
                global_enemy.hp -= s.dano;
                global_player->mp -= s.custo_mp;
                sprintf(mensagem_log, "Acertou! (+100 pts) %d dano!", s.dano);
            }
            else
            {
                global_score += 100;
                sprintf(mensagem_log, "Defesa perfeita! (+100 pts)");
            }
            combat_state = STATE_ACTION_RESOLVE;
        }
        else if (toupper(key) == 'A' || toupper(key) == 'B' || toupper(key) == 'C')
        {
            global_quiz_attempts++;
            if (global_quiz_attempts > 3)
            {
                global_score -= 50;
                if (combat_state == STATE_PLAYER_OFFENSIVE_QUIZ)
                    sprintf(mensagem_log, "Errou 3x. (-50 pts)");
                else
                {
                    global_player->hp -= global_enemy_damage;
                    sprintf(mensagem_log, "Falha! (-50 pts)");
                }
                combat_state = STATE_ACTION_RESOLVE;
            }
        }
    }
}

int iniciar_combate(const char *nome_inimigo, int hp_inimigo, int is_boss)
{
    int rodando_combate = 1;
    int turno_do_jogador = 1;
    strcpy(global_enemy.nome, nome_inimigo);
    global_enemy.hp = hp_inimigo;
    global_enemy.max_hp = hp_inimigo;
    global_enemy.mp = 100;
    global_enemy.max_mp = 100;
    combat_state = STATE_PLAYER_MAIN_MENU;
    int resultado = 0;

    while (rodando_combate)
    {
        if (combat_state == STATE_PLAYER_MAIN_MENU)
            desenhar_tela_combate(is_boss);
        else if (combat_state == STATE_PLAYER_SPELL_MENU)
            desenhar_menu_magia();
        else if (combat_state == STATE_PLAYER_ITEM_MENU)
            desenhar_menu_itens_combate();
        else if (combat_state == STATE_PLAYER_SPELL_CARD)
        {
            desenhar_spell_card(spell_selecionada);
            delay_ms(2000);
            combat_state = STATE_PLAYER_OFFENSIVE_QUIZ;
            continue;
        }
        else if (combat_state == STATE_PLAYER_OFFENSIVE_QUIZ)
            desenhar_quiz("ATAQUE LOGICO", 0);
        else if (combat_state == STATE_PLAYER_DEFENSIVE_QUIZ)
            desenhar_quiz("DEFESA LOGICA", 0);
        else if (combat_state == STATE_ACTION_RESOLVE)
        {
            desenhar_tela_combate(is_boss);
            screenUpdate();
            delay_ms(2000);
            if (turno_do_jogador)
            {
                combat_state = STATE_ENEMY_TURN_START;
                turno_do_jogador = 0;
            }
            else
            {
                combat_state = STATE_PLAYER_MAIN_MENU;
                turno_do_jogador = 1;
            }
            continue;
        }
        else if (combat_state == STATE_ENEMY_TURN_START)
        {
            desenhar_tela_combate(is_boss);
            screenUpdate();
            delay_ms(1000);
            processar_turno_inimigo();
            continue;
        }

        screenUpdate();
        processar_input_combate(get_input(), &rodando_combate, is_boss);
        if (global_enemy.hp <= 0)
        {
            rodando_combate = 0;
            resultado = 1;
            strcpy(mensagem_log, "Vitoria!");
        }
        else if (global_player->hp <= 0)
        {
            rodando_combate = 0;
            resultado = 0;
            strcpy(mensagem_log, "Derrota...");
        }
    }
    return resultado;
}

void loop_do_jogo()
{
    inicializar_jogo();
    mostrar_intro_jogo();
    tocar_musica("menu.mp3");
    int rodando_mapa = 1;
    combat_state = MODO_MAPA;
    while (rodando_mapa)
    {
        if (combat_state == MODO_MAPA)
        {
            limpar_tela_preto();
            inicializar_frame_buffer();
            atualizar_jogador_buffer(global_player_x, global_player_y, player_model);
            desenhar_mapa_frame();
            desenhar_hud_mapa();
            screenUpdate();
            int key = get_input();
            processar_input_mapa(key, &rodando_mapa);
        }
        else if (combat_state == MODO_INVENTARIO_MAPA)
        {
            desenhar_inventario_mapa();
            int key = get_input();
            processar_input_inventario_mapa(key);
        }
        else
        {
            rodando_mapa = 0;
        }
        usleep(16000);
    }
    parar_musica();
    liberar_jogador();
}

void inicializar_jogo()
{
    global_score = 0;
    inicializar_jogador_inventario();
    carregar_questoes();
    carregar_ranking();
    global_player = get_jogador();
    fase_atual = FASE_VILA;
    carregar_fase_logica(fase_atual);
}

int main()
{
    screenInit(1);
    keyboardInit();
    screenHideCursor();
    srand(time(NULL));
    int escolha = mostrar_menu_principal();
    if (escolha == 0)
        loop_do_jogo();
    screenShowCursor();
    screenDestroy();
    keyboardDestroy();
    return 0;
}