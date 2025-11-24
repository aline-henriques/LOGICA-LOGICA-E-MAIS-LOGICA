#ifndef __MAPA_H__
#define __MAPA_H__

#define MAPA_ALTURA 15
#define MAPA_LARGURA 110 

#define FASE_VILA 1
#define FASE_FLORESTA 2
#define FASE_MASMORRA 3

void carregar_mapa_fase(int fase);
void inicializar_frame_buffer();
void desenhar_mapa_frame();
void atualizar_jogador_buffer(int x, int y, char model[3][4]);
char get_mapa_char(int x, int y);
void set_mapa_char(int x, int y, char c);
void adicionar_item_mapa_logica(const char* nome, int qtd);

#endif