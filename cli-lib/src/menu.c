#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "menu.h"
#include "screen.h"
#include "keyboard.h"
#include "ranking.h"
#include "timer.h"

#define MY_KEY_UP 1000
#define MY_KEY_DOWN 1001
#define MY_KEY_ENTER 10
#define MY_KEY_ESC 27

void limpar_tela_preto_menu() {
    screenHomeCursor();
    screenSetColor(WHITE, BLACK);
    for(int i=0; i<25; i++) {
        for(int j=0; j<80; j++) printf(" ");
        printf("\n");
    }
    screenHomeCursor();
}

void tocar_musica_menu(const char* arquivo) {
    
}

void parar_musica_menu() {
    
}

int get_menu_input() {
    int key = readch();
    if (key == 27) {
        if (keyhit()) {
            int k2 = readch();
            if (k2 == 91) {
                int k3 = readch();
                if (k3 == 65) return MY_KEY_UP;
                if (k3 == 66) return MY_KEY_DOWN;
            }
        }
        return MY_KEY_ESC;
    }
    if (key == 10) return MY_KEY_ENTER;
    return key;
}

void desenhar_arte_xbox() {
    screenSetColor(LIGHTGREEN, BLACK);
    
    screenGotoxy(5, 3);  printf("         .::[[[[[[[::.         ");
    screenGotoxy(5, 4);  printf("      .::[[   ...   [[::.      ");
    screenGotoxy(5, 5);  printf("    .::[   .::[[[::.   ]::.    ");
    screenGotoxy(5, 6);  printf("  .::[   .::[[   ]]::.   ]::.  ");
    screenGotoxy(5, 7);  printf(" .::[   :::[       ]::.   ]::. ");
    screenGotoxy(5, 8);  printf(" ::[   ::[           ]::   ]:: ");
    screenGotoxy(5, 9);  printf(" ::[   ::[           ]::   ]:: ");
    screenGotoxy(5, 10); printf(" '::[   '::.       .::'   ]::' ");
    screenGotoxy(5, 11); printf("  '::[    '::.....::'    ]::'  ");
    screenGotoxy(5, 12); printf("    '::.      '''      .::'    ");
    screenGotoxy(5, 13); printf("      '::..         ..::'      ");
    screenGotoxy(5, 14); printf("         '':::::::::''         ");

    screenSetColor(YELLOW, BLACK);
    screenGotoxy(8, 16); printf(" Lógica, Lógica e Mais Lógica ");
    screenSetNormal();
}

int mostrar_menu_principal() {
    int selecao = 0;
    const int num_opcoes = 3;
    
    // Nenhuma chamada a tocar_musica

    while (1) {
        limpar_tela_preto_menu();
        
        desenhar_arte_xbox();

        screenSetColor(GREEN, BLACK);
        screenGotoxy(50, 4); printf("=====================");
        screenSetColor(WHITE, BLACK);
        screenGotoxy(50, 5); printf(" S  Y  N  A  P  S  E ");
        screenSetColor(GREEN, BLACK);
        screenGotoxy(50, 6); printf("=====================");
        
        screenSetColor(WHITE, BLACK);
        screenGotoxy(50, 9);
        if (selecao == 0) {
            screenSetColor(LIGHTGREEN, BLACK); printf(">> [ NOVO JOGO ]");
        } else {
            screenSetColor(DARKGRAY, BLACK); printf("   [ NOVO JOGO ]");
        }

        screenGotoxy(50, 11);
        if (selecao == 1) {
            screenSetColor(LIGHTGREEN, BLACK); printf(">> [  RANKING  ]");
        } else {
            screenSetColor(DARKGRAY, BLACK); printf("   [  RANKING  ]");
        }

        screenGotoxy(50, 13);
        if (selecao == 2) {
            screenSetColor(LIGHTGREEN, BLACK); printf(">> [   SAIR    ]");
        } else {
            screenSetColor(DARKGRAY, BLACK); printf("   [   SAIR    ]");
        }
        
        screenGotoxy(50, 17);
        screenSetColor(DARKGRAY, BLACK);
        printf("Use W/S e Enter");
        screenSetNormal();

        screenUpdate();

        int key = get_menu_input();

        switch(key) {
            case 'w': case 'W': case MY_KEY_UP:
                selecao--;
                if (selecao < 0) selecao = num_opcoes - 1;
                break;
            case 's': case 'S': case MY_KEY_DOWN:
                selecao++;
                if (selecao >= num_opcoes) selecao = 0;
                break;
            case MY_KEY_ENTER:
                if (selecao == 0) {
                    return 0;
                }
                if (selecao == 1) {
                    desenhar_tela_ranking();
                    break;
                }
                if (selecao == 2) {
                    return 1;
                }
                break;
            case MY_KEY_ESC:
                return 1;
        }
        usleep(16000);
    }
}