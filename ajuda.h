#ifndef ___AJUDA_H___
#define ___AJUDA_H___

/**
@file ajuda.h
Protótipos das funções que permitem que utilizador usufrua de ajudas no decorrer do jogo.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cgi.h"
#include "estado.h"
#include "verificacao.h"
#include "ficheiros.h"
#include "comparacoes.h"


/** Função que verifica horizontalmente se existe alguma casa em que é possivel dar AJUDA. */ 
void lineAdvise(ESTADO *e, int l, int c);

/** Função que verifica verticalmente se existe alguma casa em que é possivel dar AJUDA. */ 
void columnAdvise (ESTADO *e, int l, int c);

/** Função que verifica diagonalmente se existe alguma casa em que é possivel dar AJUDA. */ 
void diagonalAdvise(ESTADO *e,int l, int c);


/** Função que verifica se exista alguma casa em que é possivel dar AJUDA. */
void checkAdviser (ESTADO *e, int l, int c);

/** Função responsável por indicar ao jogador qual a posição mais acertada em que este deve jogar. */
void giveHelp (ESTADO n,char* buffer);

/** Função responsável por colocar no ecrã as imagens que informam as ajudas restantes do utilizador. */
void helpController (ESTADO e);

/** Função que coloca no jogo a imagem que permite a ocorrência de ajudas. */
void draw_help(ESTADO e);

/** Função responsável por verificar em que posições poderá ocorrer a ação do solver do jogo. */
void solver(ESTADO n, char*buffer);

/** Função responsável por alterar o valor da casa da posição (l,c) do tabuleiro. */
void chooseVal (ESTADO* e, int l, int c, char sol);

/** Função encarregue de colocar a imagem que permite a ocorrência de uma iteração da resolução do solver. */
void draw_solver(ESTADO e);

#endif