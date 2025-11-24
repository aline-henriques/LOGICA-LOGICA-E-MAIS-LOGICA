#ifndef __JOGADOR_H__
#define __JOGADOR_H__

#include "questoes.h"

typedef struct {
    char nome[30];
    int hp;
    int max_hp;
    int mp;
    int max_mp;
} Entity;

typedef struct {
    char nome[50];
    int dano;
    int custo_mp;
    int desbloqueada; 
} Spell;

typedef struct {
    char nome[50];
    int quantidade;
} Item;

void inicializar_jogador_inventario();
void liberar_jogador();
Entity* get_jogador();
Spell get_spell(int indice);
void desbloquear_feitico(int indice); 
Item* get_item(int indice);
int get_num_itens();
int get_num_spells();

const char* usar_item_jogador(int indice);

#endif