#include <string.h>
#include <stdlib.h>
#include "questoes.h"

#define MAX_Q_BATALHA 30
#define MAX_Q_VILA 30
#define MAX_Q_BAU 10

static LogicQuestion s_questoes_batalha[MAX_Q_BATALHA];
static int s_num_batalha = 0;

static LogicQuestion s_questoes_vila[MAX_Q_VILA];
static int s_num_vila = 0;

static LogicQuestion s_questoes_bau[MAX_Q_BAU];
static int s_num_bau = 0;

void add_batalha(const char* p, const char* a, const char* b, const char* c, char r) {
    if(s_num_batalha >= MAX_Q_BATALHA) return;
    strcpy(s_questoes_batalha[s_num_batalha].pergunta, p);
    strcpy(s_questoes_batalha[s_num_batalha].op_a, a);
    strcpy(s_questoes_batalha[s_num_batalha].op_b, b);
    strcpy(s_questoes_batalha[s_num_batalha].op_c, c);
    s_questoes_batalha[s_num_batalha].resposta_correta = r;
    s_num_batalha++;
}

void add_vila(const char* p, const char* a, const char* b, const char* c, char r) {
    if(s_num_vila >= MAX_Q_VILA) return;
    strcpy(s_questoes_vila[s_num_vila].pergunta, p);
    strcpy(s_questoes_vila[s_num_vila].op_a, a);
    strcpy(s_questoes_vila[s_num_vila].op_b, b);
    strcpy(s_questoes_vila[s_num_vila].op_c, c);
    s_questoes_vila[s_num_vila].resposta_correta = r;
    s_num_vila++;
}

void add_bau(const char* p, const char* a, const char* b, const char* c, char r) {
    if(s_num_bau >= MAX_Q_BAU) return;
    strcpy(s_questoes_bau[s_num_bau].pergunta, p);
    strcpy(s_questoes_bau[s_num_bau].op_a, a);
    strcpy(s_questoes_bau[s_num_bau].op_b, b);
    strcpy(s_questoes_bau[s_num_bau].op_c, c);
    s_questoes_bau[s_num_bau].resposta_correta = r;
    s_num_bau++;
}

void carregar_questoes() {
    s_num_batalha = 0;
    add_batalha("Se P eh V e Q eh F, entao P ^ Q eh:", "A) Verdadeiro", "B) Falso", "C) Indeterminado", 'B');
    add_batalha("A negacao de (P v Q) eh:", "A) ~P ^ ~Q", "B) ~P v ~Q", "C) P ^ Q", 'A');
    add_batalha("P -> Q e equivalente a:", "A) P ^ ~Q", "B) ~P v Q", "C) Q -> P", 'B');
    add_batalha("Se (P -> Q) eh F, entao:", "A) P eh V e Q eh F", "B) P eh F e Q eh V", "C) Ambos sao F", 'A');
    add_batalha("O valor logico de (V v F) eh:", "A) Verdadeiro", "B) Falso", "C) Nulo", 'A');
    add_batalha("A tabela verdade de P ^ ~P e:", "A) Sempre V (Tautologia)", "B) Sempre F (Contradicao)", "C) Contingencia", 'B');
    add_batalha("Modus Ponens diz que: Se P->Q e P, entao:", "A) ~Q", "B) Q", "C) ~P", 'B');
    add_batalha("Modus Tollens: Se P->Q e ~Q, entao:", "A) P", "B) Q", "C) ~P", 'C');
    add_batalha("A bicondicional P <-> Q e V se:", "A) P e Q tem valores iguais", "B) P e V e Q e F", "C) P e Q tem valores diferentes", 'A');
    add_batalha("A negacao de 'Todo A eh B' eh:", "A) Nenhum A eh B", "B) Algum A nao eh B", "C) Todo B eh A", 'B');
    add_batalha("Se ~P eh F, entao P eh:", "A) Verdadeiro", "B) Falso", "C) Impossivel", 'A');
    add_batalha("Lei da Dupla Negacao: ~~P equivale a:", "A) ~P", "B) P", "C) P v P", 'B');
    add_batalha("Na disjuncao exclusiva (XOR), V xor V eh:", "A) Verdadeiro", "B) Falso", "C) Depende", 'B');
    add_batalha("Silogismo: Todo homem e mortal. Socrates e homem.", "A) Socrates e imortal", "B) Socrates e mortal", "C) Socrates e grego", 'B');
    add_batalha("Se P->Q eh V e P eh V, Q deve ser:", "A) Verdadeiro", "B) Falso", "C) Indeterminado", 'A');
    add_batalha("Qual frase NAO eh uma proposicao?", "A) A lua e quadrada", "B) 2 + 2 = 5", "C) Va para casa!", 'C');
    add_batalha("P v ~P chama-se:", "A) Contradicao", "B) Tautologia", "C) Falacia", 'B');
    add_batalha("A contrapositiva de P -> Q eh:", "A) Q -> P", "B) ~Q -> ~P", "C) ~P -> ~Q", 'B');
    add_batalha("De Morgan: ~(P ^ Q) equivale a:", "A) ~P v ~Q", "B) ~P ^ ~Q", "C) P v Q", 'A');
    add_batalha("Se (P <-> Q) eh F, entao:", "A) P e Q sao iguais", "B) P e Q sao diferentes", "C) P e Q sao falsos", 'B');
    add_batalha("O conectivo 'v' representa:", "A) Conjuncao", "B) Disjuncao", "C) Implicacao", 'B');
    add_batalha("O conectivo '^' representa:", "A) Conjuncao", "B) Disjuncao", "C) Negacao", 'A');
    add_batalha("Se P eh F e Q eh F, P -> Q eh:", "A) Verdadeiro", "B) Falso", "C) Nulo", 'A');
    add_batalha("Se P eh F, entao P ^ Q eh:", "A) Verdadeiro", "B) Falso", "C) Depende de Q", 'B');
    add_batalha("Se P eh V, entao P v Q eh:", "A) Verdadeiro", "B) Falso", "C) Depende de Q", 'A');
    add_batalha("A inversa de P -> Q eh:", "A) Q -> P", "B) ~P -> ~Q", "C) ~Q -> ~P", 'B');
    add_batalha("A reciproca de P -> Q eh:", "A) Q -> P", "B) ~P -> ~Q", "C) ~Q -> ~P", 'A');
    add_batalha("Quantos valores tem uma tabela de 3 variaveis?", "A) 4", "B) 6", "C) 8", 'C');
    add_batalha("P v (P ^ Q) equivale a (Lei da Absorcao):", "A) P", "B) Q", "C) P ^ Q", 'A');
    add_batalha("Falacia da afirmacao do consequente: Se P->Q e Q...", "A) Entao P", "B) Nada se conclui", "C) Entao ~P", 'B');

    s_num_vila = 0;
    add_vila("O pai de Maria tem 5 filhas: Lala, Lele, Lili, Lolo. Qual a 5a?", "A) Lulu", "B) Maria", "C) Lyla", 'B');
    add_vila("Alguns meses tem 31 dias. Quantos tem 28?", "A) 1 (Fevereiro)", "B) 6", "C) 12 (Todos)", 'C');
    add_vila("O que e, o que e? Cai em pe e corre deitado?", "A) Minhoca", "B) Chuva", "C) Cobra", 'B');
    add_vila("O que e, o que e? Tem cidades, mas nao casas; rios, mas nao agua?", "A) O Mapa", "B) O Sonho", "C) O Deserto", 'A');
    add_vila("Quanto mais voce tira, maior ele fica.", "A) O Buraco", "B) O Tempo", "C) O Dinheiro", 'A');
    add_vila("O que passa pela agua e nao se molha?", "A) O Peixe", "B) O Navio", "C) A Sombra", 'C');
    add_vila("Voce esta numa corrida e ultrapassa o segundo. Em que lugar fica?", "A) Primeiro", "B) Segundo", "C) Terceiro", 'B');
    add_vila("O que tem capa mas nao voa, tem folhas mas nao e arvore?", "A) O Caderno", "B) O Livro", "C) O Jornal", 'B');
    add_vila("Se eu tenho 3 macas e voce tira 2, quantas voce tem?", "A) 1", "B) 2", "C) 3", 'B');
    add_vila("O que sobe mas nunca desce?", "A) O Balao", "B) A Idade", "C) A Chuva", 'B');
    add_vila("Tem cabeca, tem dente, tem barba, nao e bicho e nem gente.", "A) O Alho", "B) O Milho", "C) O Abacaxi", 'A');
    add_vila("O que e que anda com os pes na cabeca?", "A) O Piolho", "B) O Chapeu", "C) O Ginasta", 'A');
    add_vila("Uma caixa sem chaves ou tampa, mas guarda um tesouro dourado.", "A) O Cofre", "B) O Ovo", "C) A Laranja", 'B');
    add_vila("O que e meu, mas meus amigos usam mais que eu?", "A) Meu dinheiro", "B) Meu nome", "C) Meu carro", 'B');
    add_vila("Eu tenho cidades, mas nao casas. Tenho montanhas, mas nao arvores.", "A) Mapa", "B) Globo", "C) Sonho", 'A');
    add_vila("O que quebra assim que voce diz o nome?", "A) O Vidro", "B) O Silencio", "C) A Promessa", 'B');
    add_vila("Quem o faz, nao quer. Quem compra, nao usa. Quem usa, nao ve.", "A) O Caixao", "B) O Veneno", "C) O Presente", 'A');
    add_vila("Sempre chego, mas nunca estou aqui. O que sou?", "A) O Amanha", "B) O Ontem", "C) O Hoje", 'A');
    add_vila("Tenho apenas uma cor, mas posso ter varios tamanhos. Sumo no sol.", "A) A Nuvem", "B) A Sombra", "C) A Agua", 'B');
    add_vila("O que tem 4 pernas de manha, 2 a tarde e 3 a noite?", "A) O Homem", "B) O Cachorro", "C) O Gato", 'A');
    add_vila("O que pesa mais: 1kg de algodao ou 1kg de chumbo?", "A) Chumbo", "B) Algodao", "C) Iguais", 'C');
    add_vila("Se ontem fosse amanha, hoje seria sexta. Que dia e hoje?", "A) Quarta", "B) Domingo", "C) Segunda", 'B');
    add_vila("Qual numero completa: 2, 4, 8, 16, ...?", "A) 24", "B) 30", "C) 32", 'C');
    add_vila("Sou alto quando jovem e baixo quando velho. O que sou?", "A) A Vela", "B) A Arvore", "C) O Homem", 'A');
    add_vila("O que tem 13 coracoes mas nenhum orgao?", "A) O Polvo", "B) O Baralho", "C) O Hospital", 'B');
    add_vila("Posso ser quebrada, feita, dita e jogada. O que sou?", "A) A Bola", "B) A Piada", "C) A Roda", 'B');
    add_vila("Se 3 gatos matam 3 ratos em 3 minutos, 100 gatos matam 100 ratos em:", "A) 100 min", "B) 3 min", "C) 1 min", 'B');
    add_vila("O que corre em volta do pasto inteiro sem se mexer?", "A) A Cerca", "B) O Vento", "C) A Grama", 'A');
    add_vila("O que tem um olho mas nao pode ver?", "A) O Ciclope", "B) A Agulha", "C) O Furacao", 'B');
    add_vila("Tenho chaves mas nao abro portas.", "A) O Piano", "B) O Chaveiro", "C) O Mapa", 'A');

    s_num_bau = 0;
    add_bau("Gnomo: Decifra-me! De manha 4 pernas, tarde 2, noite 3.", "A) O Homem", "B) O Escaravelho", "C) O Deus Ra", 'A');
    add_bau("Gnomo: Se todos os Faraos sao Reis e Ramses e Farao...", "A) Ramses e Deus", "B) Ramses e Rei", "C) Ramses e Imortal", 'B');
    add_bau("Gnomo: As Piramides sao triangulos em 3D. Quantas faces tem uma base quadrada?", "A) 4", "B) 5", "C) 6", 'B');
    add_bau("Gnomo: Cleopatra viveu mais perto do iPhone ou das Piramides?", "A) Piramides", "B) iPhone", "C) Exatamente no meio", 'B');
    add_bau("Gnomo: Eu nao sou, eu nao fui, eu nao serei. Ninguem me viu.", "A) O Nada", "B) O Futuro", "C) O Tempo", 'A');
    add_bau("Gnomo: O Nilo corre para o Norte. Se voce navega contra ele, vai para:", "A) Norte", "B) Sul", "C) Leste", 'B');
    add_bau("Gnomo: O que o construtor nao quer, o comprador nao usa e o usuario nao ve?", "A) O Sarcofago", "B) A Piramide", "C) A Mumia", 'A');
    add_bau("Gnomo: Tenho folhas mas nao sou papiro. Tenho historias mas nao falo.", "A) O Escriba", "B) O Livro", "C) A Pedra de Roseta", 'B');
    add_bau("Gnomo: Verdadeiro ou Falso: O zero foi inventado pelos egipcios.", "A) Verdadeiro", "B) Falso (Indianos/Maias)", "C) Falso (Romanos)", 'B');
    add_bau("Gnomo: Se a Esfinge mente, e ela diz 'Eu minto', ela diz a verdade?", "A) Sim", "B) Nao (Paradoxo)", "C) Talvez", 'B');
}

LogicQuestion get_questao_aleatoria() {
    if (s_num_batalha == 0) carregar_questoes();
    int r = rand() % s_num_batalha;
    return s_questoes_batalha[r];
}

LogicQuestion get_questao_vila() {
    if (s_num_vila == 0) carregar_questoes();
    int r = rand() % s_num_vila;
    return s_questoes_vila[r];
}

LogicQuestion get_questao_bau() {
    if (s_num_bau == 0) carregar_questoes();
    int r = rand() % s_num_bau;
    return s_questoes_bau[r];
}