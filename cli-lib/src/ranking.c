#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "ranking.h"
#include "screen.h"
#include "keyboard.h"

#define MAX_ENTRIES 5
#define RANKING_FILE "ranking.txt"

static struct {
    char nome[30];
    int pontos;
} s_ranking[MAX_ENTRIES];

static int s_num_entries = 0;

void limpar_tela_preto_ranking() {
    screenHomeCursor();
    screenSetColor(WHITE, BLACK);
    for(int i=0; i<25; i++) {
        for(int j=0; j<80; j++) printf(" ");
        printf("\n");
    }
    screenHomeCursor();
}

void desenhar_moldura_ranking() {
    screenBoxEnable();
    screenSetColor(WHITE, BLACK);
    
    screenGotoxy(15, 2); printf("%c", BOX_UPLEFT);
    for (int i = 16; i < 65; i++) printf("%c", BOX_HLINE);
    screenGotoxy(65, 2); printf("%c", BOX_UPRIGHT);
    
    for (int i = 3; i < 22; i++) {
        screenGotoxy(15, i); printf("%c", BOX_VLINE);
        screenGotoxy(65, i); printf("%c", BOX_VLINE);
    }
    
    screenGotoxy(15, 22); printf("%c", BOX_DWNLEFT);
    for (int i = 16; i < 65; i++) printf("%c", BOX_HLINE);
    screenGotoxy(65, 22); printf("%c", BOX_DWNRIGHT);
    screenBoxDisable();
}

void carregar_ranking() {
    FILE* f = fopen(RANKING_FILE, "r");
    if (!f) return;

    s_num_entries = 0;
    char line_buffer[100];

    while (s_num_entries < MAX_ENTRIES && fgets(line_buffer, sizeof(line_buffer), f)) {
        char* last_space = strrchr(line_buffer, ' ');
        if (last_space == NULL || last_space == line_buffer) continue;
        
        s_ranking[s_num_entries].pontos = atoi(last_space + 1);
        *last_space = '\0';
        
        strncpy(s_ranking[s_num_entries].nome, line_buffer, 29);
        s_ranking[s_num_entries].nome[29] = '\0';
        s_num_entries++;
    }
    fclose(f);
}

void salvar_ranking(int pontuacao_final) {
    char nome_jogador[30];
    memset(nome_jogador, 0, 30);
    int indice_inserir = -1;

    for (int i = 0; i < MAX_ENTRIES; i++) {
        if (i >= s_num_entries || pontuacao_final >= s_ranking[i].pontos) {
            indice_inserir = i;
            break;
        }
    }

    if (indice_inserir == -1) {
        limpar_tela_preto_ranking();
        desenhar_moldura_ranking();
        screenGotoxy(20, 10);
        printf("Pontuacao: %d", pontuacao_final);
        screenGotoxy(20, 12);
        printf("Voce nao entrou no Hall da Fama.");
        screenGotoxy(20, 14);
        printf("Pressione Enter...");
        screenUpdate();
        int key = 0;
        while (key != 10 && key != 13) { key = readch(); }
        return;
    }

    limpar_tela_preto_ranking();
    desenhar_moldura_ranking();
    
    screenGotoxy(20, 8);
    screenSetColor(YELLOW, BLACK);
    printf("NOVO RECORDE! Pontuacao: %d", pontuacao_final);
    screenSetColor(WHITE, BLACK);
    
    screenGotoxy(20, 10);
    printf("Digite seu nome: ");
    
    int start_x = 37;
    int start_y = 10;
    screenGotoxy(start_x, start_y);
    screenShowCursor();
    screenUpdate();

    int c, i = 0;
    while (1) {
        c = readch();
        if (c == 10 || c == 13) { if (i > 0) break; }
        else if ((c == 127 || c == 8) && i > 0) {
            i--;
            screenGotoxy(start_x + i, start_y); printf(" ");
            screenGotoxy(start_x + i, start_y); screenUpdate();
        }
        else if (c >= 32 && c <= 126 && i < 20) {
            nome_jogador[i] = (char)c;
            screenSetColor(CYAN, BLACK);
            printf("%c", (char)c);
            screenSetColor(WHITE, BLACK);
            i++; screenUpdate();
        }
    }
    
    nome_jogador[i] = '\0';
    screenHideCursor();

    for (int j = MAX_ENTRIES - 1; j > indice_inserir; j--) {
        s_ranking[j] = s_ranking[j - 1];
    }

    strcpy(s_ranking[indice_inserir].nome, nome_jogador);
    s_ranking[indice_inserir].pontos = pontuacao_final;
    if (s_num_entries < MAX_ENTRIES) s_num_entries++;

    FILE* f = fopen(RANKING_FILE, "w");
    if (!f) return;
    for (int j = 0; j < s_num_entries; j++) {
        fprintf(f, "%s %d\n", s_ranking[j].nome, s_ranking[j].pontos);
    }
    fclose(f);
}

void desenhar_tela_ranking() {
    carregar_ranking();
    limpar_tela_preto_ranking();
    desenhar_moldura_ranking();

    screenGotoxy(28, 5);
    screenSetColor(LIGHTMAGENTA, BLACK);
    printf("=== HALL DA FAMA ===");
    screenSetNormal();

    for (int i = 0; i < s_num_entries; i++) {
        screenGotoxy(20, 8 + (i * 2));
        
        if (i == 0) screenSetColor(YELLOW, BLACK);      
        else if (i == 1) screenSetColor(CYAN, BLACK);   
        else if (i == 2) screenSetColor(RED, BLACK);    
        else screenSetColor(LIGHTGREEN, BLACK);         

        printf("%d. %-20s", i + 1, s_ranking[i].nome);
        
        screenGotoxy(50, 8 + (i * 2));
        printf("%05d pts", s_ranking[i].pontos);
    }
    
    if (s_num_entries == 0) {
        screenGotoxy(30, 10);
        screenSetColor(DARKGRAY, BLACK);
        printf("Nenhum recorde salvo.");
    }

    screenSetColor(WHITE, BLACK);
    screenGotoxy(25, 20);
    printf("Pressione Enter para voltar...");
    screenUpdate();

    int key = 0;
    while (key != 10 && key != 13) {
        key = readch();
    }
}