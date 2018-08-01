#ifndef ___ESTADO_H___
#define ___ESTADO_H___

/**
@file estado.h
Protótipos das funções relacionadas com o estado.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

/** Constante para definir o número máximo de linhas e de colunas que um tabuleiro pode ter. */
#define MAX_GRID 		20

/** Enumeração dos possiveis valores que cada casa do tabuleiro pode ter. */
typedef enum {BLOQUEADA, FIXO_X, FIXO_O, VAZIA, SOL_X, SOL_O,AJUDA} VALOR;

/** Estrutura que guarda as posições, o valor de uma jogada e se a ancora foi ativada.
 * A stack formada, conterá elementos do tipo STV.
 */
typedef struct stval {
	int x;
	int y;
	char val;
	int anc;
} STV;


/** Estrutura necessária para o funcionamento das ajudas e do solver. 
 * 	Armazena:
 * - Um inteiro, que identifica se ocorre ajuda ou se é necessário a utilização do solver.
 * - Dois inteiros, correspondentes às posições onde ocorrerá a AJUDA.
 * - Um char, identificativo do valor que é obrigatório jogar na posicao (x,y) da grelha.
 */
typedef struct aviso {
	int val;
	int x;
	int y;
	char type;
} AVISO;

/** Lista ligada, que permitirá a formação da stack que armazena um STV correspondente a cada jogada. */

typedef struct lista {
	STV value;
	struct lista *prox;
} *LVal;

/** Estrura que guarda o estado do jogo.
 *  Nela é guardada informação preponderante para o seu funciomento, tais como :
 * - Nº de linhas e colunas da grelha.
 * - A grelha e os respetivos valores de cada casa.
 * - Inteiros que identificam o utilizador, o tabuleiro e o nºde ajudas.
 * - Uma estrutura com os dados necessários para a ocorrência de ajudas.
 * - A stack com o histórico do jogo. */
typedef struct estado {
	char num_lins;
	char num_cols;
	char grelha[MAX_GRID][MAX_GRID];
	int utilizador;
	int tabuleiro;
	int n_ajudas;
	AVISO ajuda;
	LVal stack;
} ESTADO;

/** Função que converte um estado numa string. */
char *estado2str(ESTADO e);

/** Função que converte uma string num ESTADO. */
ESTADO str2estado(char *argumentos);

#endif