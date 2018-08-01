#ifndef ___VERIFICACAO_H___
#define ___VERIFICACAO_H___

#include "estado.h"
/**
@file verificacao.h
Protótipos das funções que permitem a validação do tabuleiro.*/

/** Função que verifica se existem 3 peças iguais na horizontal (linha). */
int lineCheck(ESTADO n,int l,int c);

/** Função que verifica se existem 3 peças iguais na vertical (coluna). */
int columnCheck(ESTADO n,int l,int c);

/** Função que verifica se existem 3 peças iguais na diagonal. */
int diagonalCheck(ESTADO n,int l,int c);

/** Função responsavél por verificar se existe no tabuleiro alguma sequência de 3 casas com o mesmo valor. */
int verfTable(ESTADO n);

/** Função que verifica se o tabuleiro está completo, isto é, sem quaisquer peças vazias ou peças de ajuda. */
int isComplete (ESTADO n);

#endif