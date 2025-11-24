#include <stdio.h>
#include <string.h>
#include "mapa.h"
#include "screen.h"
#include "jogador.h"

static char mapa[MAPA_ALTURA][MAPA_LARGURA + 1];
static char frame_buffer[MAPA_ALTURA][MAPA_LARGURA + 1];

char get_mapa_char(int x, int y) {
    if (x < 0 || x >= MAPA_LARGURA || y < 0 || y >= MAPA_ALTURA) return '#';
    return mapa[y][x];
}

void set_mapa_char(int x, int y, char c) {
    if (x >= 0 && x < MAPA_LARGURA && y >= 0 && y < MAPA_ALTURA) {
        mapa[y][x] = c;
    }
}

void inicializar_frame_buffer() {
    for (int i = 0; i < MAPA_ALTURA; i++) {
        strcpy(frame_buffer[i], mapa[i]);
    }
}

void atualizar_jogador_buffer(int px, int py, char model[3][4]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            char c = model[i][j];
            if (c == ' ') continue;
            int dx = px + j;
            int dy = py + i;
            if (dy >= 0 && dy < MAPA_ALTURA && dx >= 0 && dx < MAPA_LARGURA) {
                frame_buffer[dy][dx] = c;
            }
        }
    }
}

void desenhar_mapa_frame() {
    screenHomeCursor();
    printf("\n"); 
    for (int y = 0; y < MAPA_ALTURA; y++) {
        printf(" "); 
        for (int x = 0; x < MAPA_LARGURA; x++) {
            char c = frame_buffer[y][x];
            
            
            if (c == '^') screenSetColor(CYAN, BLACK);       
            else if (c == 'T') screenSetColor(GREEN, BLACK);      
            else if (c == 't') screenSetColor(BROWN, BLACK);      
            else if (c == '#') screenSetColor(DARKGRAY, BLACK); 
            else if (c == 'B' || c == 'b') screenSetColor(YELLOW, BLACK);  
            else if (c == '$') screenSetColor(LIGHTRED, BLACK);     
            else if (c == '~') screenSetColor(BLUE, BLACK);    
            else if (c == 'D') screenSetColor(MAGENTA, BLACK);
            else if (c == 'M') screenSetColor(LIGHTBLUE, BLACK); 
            else if (c == 'C' || c == 'G') screenSetColor(RED, BLACK);       
            else if (c == '>' || c == '<') screenSetColor(WHITE, BLACK);     
            else screenSetColor(WHITE, BLACK); 
            
            printf("%c", c);
        }
        screenSetColor(WHITE, BLACK);
        printf("\n");
    }
}

void adicionar_item_mapa_logica(const char* nome, int qtd) {
    int num = get_num_itens();
    if (num >= 5) return;
    Item* slot = get_item(num);
    if (slot != NULL && slot->quantidade == 0) {
        strcpy(slot->nome, nome);
        slot->quantidade = qtd;
    }
}

void carregar_mapa_fase(int fase) {
    for(int i=0; i<MAPA_ALTURA; i++) memset(mapa[i], ' ', MAPA_LARGURA);

    if (fase == FASE_VILA) {
        strcpy(mapa[0],  "##############################################################################################################");
        strcpy(mapa[1],  "#   VILA DOS LOGICOS                                                      ~~~~~                              #");
        strcpy(mapa[2],  "#                                 H H H                                  ~~~~~~~                             #");
        strcpy(mapa[3],  "#    H H       TT                 H M H                                 ~~~~~~~~~                            #");
        strcpy(mapa[4],  "#    H M       TT                 H H H                                   ~~~~~                 TTT          #");
        strcpy(mapa[5],  "#    H H                                                                   ~~~                 TTTTT         #");
        strcpy(mapa[6],  "#                                                                           ~                   TTT          #");
        strcpy(mapa[7],  "#            ~~~                                                                                             #");
        strcpy(mapa[8],  "#   TT      ~~~~~               $                                       T T T                                #");
        strcpy(mapa[9],  "#   TT       ~~~                                                       T T T T                               #");
        strcpy(mapa[10], "#                                                                       T T T                                #");
        strcpy(mapa[11], "#                                      TT                                 T                                  #");
        strcpy(mapa[12], "#                                     TTTT                                                              >    #");
        strcpy(mapa[13], "#    B                                 TT                                                              >>>   #");
        strcpy(mapa[14], "##############################################################################################################");
    } 
    else if (fase == FASE_FLORESTA) {
        strcpy(mapa[0],  "##############################################################################################################");
        strcpy(mapa[1],  "# TTTT       ^ ^                  T T       T T T            T          ~~~~~              G                 #");
        strcpy(mapa[2],  "#  T           ^                 T T T     T T T T          T T        ~~~~~~~                               #");
        strcpy(mapa[3],  "#      TTT            TT        T T T T     T T T          T T T      ~~~~~~~~~                              #");
        strcpy(mapa[4],  "#     TTTTT                     T T T T      T T            TTT         ~~~~~                                #");
        strcpy(mapa[5],  "#                                T T T                       T                                               #");
        strcpy(mapa[6],  "#      $                                                                                 ^ ^ ^               #");
        strcpy(mapa[7],  "#    ^^^^             C                                                                 ^ ^ ^ ^              #");
        strcpy(mapa[8],  "#   ^^^^^^                                                                             ^ ^ ^ ^ ^             #");
        strcpy(mapa[9],  "#  ^^^^^^^^                                       B                                       ^^^                #");
        strcpy(mapa[10], "#                                                                                                            #");
        strcpy(mapa[11], "#                                                                                                            #");
        strcpy(mapa[12], "#   <                                                                                                   >    #");
        strcpy(mapa[13], "#  <<<                                                                                                 >>>   #");
        strcpy(mapa[14], "##############################################################################################################");
    }
    else { 
        strcpy(mapa[0],  "##############################################################################################################");
        strcpy(mapa[1],  "#                                                                                                            #");
        strcpy(mapa[2],  "#                  ^ ^ ^                 # #       $                       # # #                             #");
        strcpy(mapa[3],  "#                 ^ ^ ^ ^               # # #                             # # # #                            #");
        strcpy(mapa[4],  "#      $         ^ ^ ^ ^ ^             # # # #         ##                # # # # #                           #");
        strcpy(mapa[5],  "#                   ^^^                 # # #         ####                # # # #                            #");
        strcpy(mapa[6],  "#                                                                          # # #                             #");
        strcpy(mapa[7],  "#      B                                  B                                                                  #");
        strcpy(mapa[8],  "#    ^^^^                                                                                     ^              #");
        strcpy(mapa[9],  "#   ^^^^^^            ~~~             ###                      ^                             ^^^             #");
        strcpy(mapa[10], "#  ^^^^^^^^          ~~~~~           #####                    ^^^                           ^^^^^            #");
        strcpy(mapa[11], "#                     ~~~             ###                    ^^^^^                                           #");
        strcpy(mapa[12], "#                                                                                                            #");
        strcpy(mapa[13], "#                         D                                                                                  #");
        strcpy(mapa[14], "##############################################################################################################");
    }
}