#ifndef ___COMPARACOES_H___
#define ___COMPARACOES_H___

/**
@file comparacoes.h
Protótipos das funções que permitem a comparacão dos valores das casas dentro do tabuleiro.*/

/** Considera se duas casas horizontais adjacentes possuem o valor de SOL_X ou FIXO_X.*/
void line_NearX(ESTADO *n, int l, int c);

/** Considera as casas horizontais espaçadas por uma casa VAZIA ou AJUDA e que possuem o valor SOL_X ou FIXO_X. */
void line_SpacedX(ESTADO *n, int l, int c);

/** Considera se duas casas horizontais adjacentes possuem o valor de SOL_O ou FIXO_O. */
void line_NearO(ESTADO *n, int l, int c);

//* Considera as casas horizontais espaçadas por uma casa VAZIA ou AJUDA e que possuem o valor SOL_O ou FIXO_O.*/
void line_SpacedO (ESTADO *n,int l,int c);

//* Considera se duas casas verticais adjacentes possuem o valor de SOL_X ou FIXO_X. */
void column_NearX(ESTADO *n, int l, int c);

//* Considera as casas verticais espaçadas por uma casa VAZIA ou AJUDA e que possuem o valor SOL_X ou FIXO_X.
void column_SpacedX(ESTADO*n, int l, int c);

//* Considera se duas casas verticais adjacentes possuem o valor de SOL_O ou FIXO_O. */
void column_NearO(ESTADO *n, int l, int c);

//* Considera as casas verticais espaçadas por uma casa VAZIA ou AJUDA e que possuem o valor SOL_O ou FIXO_O. */
void column_SpacedO(ESTADO *n, int l, int c);

//* Considera as casas oblíquas adjacentes segundo uma reta com declive positivo que possuem o valor SOL_O ou FIXO_O. */
void diagonal_NearDirO (ESTADO *n, int l, int c);

//* Considera as casas oblíquas adjacentes segundo uma reta com declive negativo que possuem o valor SOL_O ou FIXO_O. */
void diagonal_NearEsqO(ESTADO *n, int l, int c);

//* Considera as casas obliquas espaçadas por uma casa VAZIA ou AJUDA e que possuem o valor SOL_O ou FIXO_O. */
void diagonal_SpacedO(ESTADO *n, int l, int c);

//* Considera as casas oblíquas adjacentes segundo uma reta com declive positivo que possuem o valor SOL_X ou FIXO_X. */
void diagonal_NearDirX (ESTADO *n, int l, int c);

//* Considera as casas oblíquas adjacentes segundo uma reta com declive negativo que possuem o valor SOL_X ou FIXO_X. */
void diagonal_NearEsqX (ESTADO *n, int l, int c);

//* Considera as casas obliquas espaçadas por uma casa VAZIA ou AJUDA e que possuem o valor SOL_X ou FIXO_X. */
void diagonal_SpacedX(ESTADO*n, int l, int c);

#endif