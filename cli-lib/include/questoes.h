#ifndef __QUESTOES_H__
#define __QUESTOES_H__

typedef struct {
    char pergunta[256];
    char op_a[100];
    char op_b[100];
    char op_c[100];
    char resposta_correta;
} LogicQuestion;

void carregar_questoes();
LogicQuestion get_questao_aleatoria();
LogicQuestion get_questao_vila();
LogicQuestion get_questao_bau();

#endif