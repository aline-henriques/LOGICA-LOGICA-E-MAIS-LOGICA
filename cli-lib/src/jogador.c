#include <string.h>
#include <stdlib.h>
#include "jogador.h"

#define NUM_MAX_SPELLS 5
#define NUM_MAX_ITENS 5

static Entity s_jogador;
static Spell s_spells[NUM_MAX_SPELLS];
static Item *s_inventario = NULL;
static int s_num_itens = 0;

static void adicionar_item(const char *nome, int qtd)
{
    if (s_inventario == NULL)
        return;

    for (int i = 0; i < s_num_itens; i++)
    {
        if (strcmp(s_inventario[i].nome, nome) == 0)
        {
            s_inventario[i].quantidade += qtd;
            return;
        }
    }
    if (s_num_itens < NUM_MAX_ITENS)
    {
        strcpy(s_inventario[s_num_itens].nome, nome);
        s_inventario[s_num_itens].quantidade = qtd;
        s_num_itens++;
    }
}

static void remover_item(int indice)
{
    if (s_num_itens == 0 || indice < 0 || indice >= s_num_itens)
        return;
    for (int i = indice; i < s_num_itens - 1; i++)
        s_inventario[i] = s_inventario[i + 1];
    s_num_itens--;
}

void inicializar_jogador_inventario()
{
    strcpy(s_jogador.nome, "Aprendiz Logico");
    s_jogador.hp = 100;
    s_jogador.max_hp = 100;
    s_jogador.mp = 50;
    s_jogador.max_mp = 50;

    if (s_inventario == NULL)
    {
        s_inventario = (Item *)malloc(NUM_MAX_ITENS * sizeof(Item));
    }
    if (s_inventario != NULL)
    {
        memset(s_inventario, 0, NUM_MAX_ITENS * sizeof(Item));
    }

    strcpy(s_spells[0].nome, "Bola da Disjuncao (v)");
    s_spells[0].dano = 30;
    s_spells[0].custo_mp = 10;
    s_spells[0].desbloqueada = 0;

    strcpy(s_spells[1].nome, "Flechas Bicondicional (<->)");
    s_spells[1].dano = 50;
    s_spells[1].custo_mp = 20;
    s_spells[1].desbloqueada = 0;

    strcpy(s_spells[2].nome, "Ataque Basico");
    s_spells[2].dano = 15;
    s_spells[2].custo_mp = 0;
    s_spells[2].desbloqueada = 1;

    strcpy(s_spells[3].nome, "Explosao de Tautologia");
    s_spells[3].dano = 80;
    s_spells[3].custo_mp = 40;
    s_spells[3].desbloqueada = 0;

    strcpy(s_spells[4].nome, "Paradoxo Temporal");
    s_spells[4].dano = 150;
    s_spells[4].custo_mp = 80;
    s_spells[4].desbloqueada = 0;

    s_num_itens = 0;
    adicionar_item("Pocao de Cura", 2);
    adicionar_item("Pocao de MP", 1);
}

void liberar_jogador()
{
    if (s_inventario != NULL)
    {
        free(s_inventario);
        s_inventario = NULL;
    }
}

void desbloquear_feitico(int indice)
{
    if (indice >= 0 && indice < NUM_MAX_SPELLS)
    {
        s_spells[indice].desbloqueada = 1;
    }
}

Entity *get_jogador() { return &s_jogador; }
Spell get_spell(int indice) { return s_spells[indice]; }
Item *get_item(int indice)
{
    if (indice < 0 || indice >= s_num_itens)
        return NULL;
    return &s_inventario[indice];
}
int get_num_itens() { return s_num_itens; }
int get_num_spells() { return NUM_MAX_SPELLS; }

const char *usar_item_jogador(int indice)
{
    if (indice < 0 || indice >= s_num_itens)
        return "Item invalido";
    Item *item = &s_inventario[indice];
    if (strcmp(item->nome, "Pocao de Cura") == 0)
    {
        if (s_jogador.hp < s_jogador.max_hp)
        {
            s_jogador.hp += 50;
            if (s_jogador.hp > s_jogador.max_hp)
                s_jogador.hp = s_jogador.max_hp;
            item->quantidade--;
            if (item->quantidade <= 0)
                remover_item(indice);
            return "Voce usou Pocao de Cura! +50 HP!";
        }
        else
            return "Sua vida ja esta cheia!";
    }
    else if (strcmp(item->nome, "Pocao de MP") == 0)
    {
        if (s_jogador.mp < s_jogador.max_mp)
        {
            s_jogador.mp += 30;
            if (s_jogador.mp > s_jogador.max_mp)
                s_jogador.mp = s_jogador.max_mp;
            item->quantidade--;
            if (item->quantidade <= 0)
                remover_item(indice);
            return "Voce usou Pocao de MP! +30 MP!";
        }
        else
            return "Sua mana ja esta cheia!";
    }
    return "Item desconhecido";
}