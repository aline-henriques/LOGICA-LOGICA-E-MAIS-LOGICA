#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "historia.h"
#include "screen.h"
#include "timer.h"
#include "keyboard.h"

static void delay_hist(int ms)
{
    timerInit(ms);
    while (!timerTimeOver())
    {
    }
    timerDestroy();
}
static void desenhar_caixa_texto(int x1, int y1, int x2, int y2, const char *titulo)
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
    if (titulo)
    {
        screenGotoxy(x1 + 2, y1);
        printf(" %s ", titulo);
    }
    screenSetNormal();
}

void mostrar_intro_jogo()
{
    screenClear();
    desenhar_caixa_texto(5, 5, 75, 20, "PROLOGO: A QUEDA DA RAZAO");
    screenGotoxy(10, 8);
    printf("O ano eh 2048 da Era da Logica.");
    screenGotoxy(10, 10);
    printf("O Arquimago 'O MATEMATICADOR' enlouqueceu.");
    screenGotoxy(10, 13);
    printf("Agora, verdades sao mentiras.");
    screenGotoxy(30, 18);
    screenSetColor(YELLOW, BLACK);
    printf("[ Pressione Enter ]");
    screenSetNormal();
    screenUpdate();
    getchar();
}

void mostrar_historia_masmorra()
{
    screenClear();
    desenhar_caixa_texto(10, 5, 70, 20, "O CHEFE FINAL");
    screenGotoxy(15, 10);
    printf("A porta de pedra range e se abre lentamente...");
    screenUpdate();
    delay_hist(2000);
}

void mostrar_narrativa_generica(const char *titulo, const char *texto)
{
    screenClear();
    desenhar_caixa_texto(5, 8, 75, 16, titulo);
    screenGotoxy(10, 12);
    printf("%s", texto);
    screenUpdate();
    delay_hist(2000);
}

int rolar_dado_d20()
{
    screenClear();
    desenhar_caixa_texto(30, 8, 50, 16, "ROLANDO D20");
    int resultado = 1;
    for (int i = 0; i < 15; i++)
    {
        resultado = 1 + (rand() % 20);
        screenGotoxy(38, 12);
        screenSetColor(YELLOW, BLACK);
        printf(" %02d ", resultado);
        screenUpdate();
        usleep(50000 + (i * 10000));
    }
    delay_hist(1000);
    screenSetNormal();
    return resultado;
}

void final_cesar_school()
{
    screenClear();
    desenhar_caixa_texto(5, 5, 90, 20, "EPILOGO INESPERADO");

    screenGotoxy(10, 8);
    printf("O Matematicador cai de joelhos, derrotado.");
    screenUpdate();
    delay_hist(2000);

    screenGotoxy(10, 10);
    printf("'TOLO! Voce acha que a logica acaba aqui?'");
    screenUpdate();
    delay_hist(2000);

    screenGotoxy(10, 12);
    screenSetColor(RED, BLACK);
    printf("Ele conjura um feitico proibido: 'LOOP TEMPORAL ACADEMICO'!");
    screenSetNormal();
    screenUpdate();
    delay_hist(3000);

    screenClear();
    desenhar_caixa_texto(5, 5, 90, 20, "RECIFE, 2025 - CESAR SCHOOL");
    screenGotoxy(10, 8);
    printf("Em uma sala de aula refrigerada...");
    screenGotoxy(10, 10);
    printf("Um novo professor de Logica entra na sala.");
    screenGotoxy(10, 12);
    printf("Ele sorri para os alunos...");
    screenGotoxy(10, 14);
    screenSetColor(YELLOW, BLACK);
    printf("'Eu sou o Professor Guilherme. E vamos comecar do zero.'");

    screenGotoxy(10, 17);
    screenSetColor(RED, BLACK);
    printf("FIM DE JOGO?");
    screenSetNormal();
    screenUpdate();

    getchar();
}