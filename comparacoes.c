/**
@file comparacoes.c
Definição das funções que permitem a comparacão dos valores das casas dentro do tabuleiro.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cgi.h"
#include "estado.h"
#include "comparacoes.h"

// Linhas

/** Função responsável por verificar se existe alguma posição em que é obrigatório jogar SOL_O.
  * 
  * Para tal, considera se duas casas horizontais adjacentes possuem o valor de SOL_X ou FIXO_X.
  * Uma das casas em questão corresponde, à casa da posição (l,c) do tabuleiro.
  * 
  * Se a outra casa adjacente for VAZIA, esta será uma posição onde ocorrerá a ajuda. 
  * Para além disso, se for VAZIA ou AJUDA, será também uma das casas alteradas pelo solver do jogo.  
*/
void line_NearX(ESTADO *n, int l, int c)
{
		n->ajuda.val = 0;

		if ((n->grelha[l][c] == FIXO_X || n->grelha [l][c] == SOL_X) &&
		   (n->grelha[l][c - 1] == FIXO_X || n->grelha [l] [c - 1] == SOL_X))
			{				
				if(n->grelha[l][c + 1] == VAZIA || n->grelha[l][c + 1] == AJUDA)
				{ 
				  n->ajuda.val = 1;
				  n->ajuda.x = l;
				  n->ajuda.y = c + 1;
				  n->ajuda.type = 'O';
				}
				
				if(n->grelha[l][c - 2] == VAZIA || n->grelha[l][c - 2] == AJUDA)  
				{  
				  n->ajuda.val = 1;
				  n->ajuda.x = l;
				  n->ajuda.y = c - 2;
				  n->ajuda.type = 'O';
				}
			}
}

/** Função responsável por verificar se existe alguma posição em que é obrigatório jogar SOL_O.
  * 
  * Para tal, considera as casas horizontais espaçadas por uma casa VAZIA ou AJUDA e que possuem o valor SOL_X ou FIXO_X.
  * Uma dessas casas horizontais está na posição (l,c) do tabuleiro.
  * 
  * Se a casa que se encontra no meio for VAZIA, esta será uma posição onde ocorrerá a ajuda. 
  * Para além disso, se for VAZIA ou AJUDA, será também uma das casas alteradas pelo solver do jogo.
*/
void line_SpacedX(ESTADO *n, int l, int c)
{
		n->ajuda.val = 0;
		
		if ((n->grelha[l][c] == FIXO_X || n->grelha [l][c] == SOL_X) &&
		   (n->grelha[l][c + 2] == FIXO_X || n->grelha [l] [c + 2] == SOL_X)&&
		   (n->grelha[l][c + 1] == VAZIA || n->grelha[l][c + 1] == AJUDA))
					{ 
				         n->ajuda.val = 1;
				         n->ajuda.x = l;
				         n->ajuda.y = c + 1;
						 n->ajuda.type = 'O';
					}
				
		if ((n->grelha[l][c] == FIXO_X || n->grelha [l][c] == SOL_X) &&
		   (n->grelha[l][c - 2] == FIXO_X || n->grelha [l] [c - 2] == SOL_X) &&
		   (n->grelha[l][c - 1] == VAZIA || n->grelha[l][c - 1] == AJUDA))
		           {
						n->ajuda.val = 1;
				   		n->ajuda.x = l;
				   		n->ajuda.y = c - 1;
						n->ajuda.type = 'O';
				   }
}					


/** Função responsável por verificar se existe alguma posição em que é obrigatório jogar SOL_X.
  * 
  * Para tal, considera se duas casas horizontais adjacentes possuem o valor de SOL_O ou FIXO_O.
  * Uma das casas em questão corresponde, à casa da posição (l,c) do tabuleiro.
  * 
  * Se a outra casa adjacente for VAZIA, esta será uma posição onde ocorrerá a ajuda. 
  * Para além disso, se for VAZIA ou AJUDA, será também uma das casas alteradas pelo solver do jogo.  
*/
void line_NearO(ESTADO *n, int l, int c)
{
		n->ajuda.val = 0;
		if ((n->grelha[l][c] == FIXO_O || n->grelha [l][c] == SOL_O) &&
		   (n->grelha[l][c - 1] == FIXO_O || n->grelha [l] [c - 1] == SOL_O))
				{				
				       if(n->grelha[l][c + 1] == VAZIA || n->grelha[l][c + 1] == AJUDA)
				 		{ 
				   		  n->ajuda.val = 1;
				          n->ajuda.x = l;
				          n->ajuda.y = c + 1;
						  n->ajuda.type = 'X';
						}
				       if(n->grelha[l][c - 2] == VAZIA || n->grelha[l][c - 2] == AJUDA)
					   	{ 
				   		  n->ajuda.val = 1;
				          n->ajuda.x = l;
				          n->ajuda.y = c - 2;
						  n->ajuda.type = 'X';
						}
				}
}

/** Função responsável por verificar se existe alguma posição em que é obrigatório jogar SOL_X.
  * 
  * Para tal, considera as casas horizontais espaçadas por uma casa VAZIA ou AJUDA e que possuem o valor SOL_O ou FIXO_O.
  * Uma dessas casas horizontais está na posição (l,c) do tabuleiro.
  *
  * Se a casa que se encontra no meio for VAZIA, esta será uma posição onde ocorrerá a ajuda. 
  * Para além disso, se for VAZIA ou AJUDA, será também uma das casas alteradas pelo solver do jogo. 
*/
void line_SpacedO (ESTADO *n,int l,int c)
{
		if ((n->grelha[l][c] == FIXO_O || n->grelha [l][c] == SOL_O) &&
		   (n->grelha[l][c + 2] == FIXO_O || n->grelha [l] [c + 2] == SOL_O)&&
		   (n->grelha[l][c + 1] == VAZIA || n->grelha[l][c + 1] == AJUDA))
						{ 
				   		  n->ajuda.val = 1;
				          n->ajuda.x = l;
				          n->ajuda.y = c + 1;
						  n->ajuda.type = 'X';
						}
				
		if ((n->grelha[l][c] == FIXO_O || n->grelha [l][c] == SOL_O) &&
		   (n->grelha[l][c - 2] == FIXO_O || n->grelha [l] [c - 2] == SOL_O)&&
		   (n->grelha[l][c - 1] == VAZIA || n->grelha[l][c - 1] == AJUDA))  
						{ 
				   		  n->ajuda.val = 1;
				          n->ajuda.x = l;
				          n->ajuda.y = c - 1;
						  n->ajuda.type = 'X';
						}
}	

// Colunas

/** Função responsável por verificar se existe alguma posição em que é obrigatório jogar SOL_O.
  * 
  * Para tal, considera se duas casas verticais adjacentes possuem o valor de SOL_X ou FIXO_X.
  * Uma das casas em questão corresponde, à casa da posição (l,c) do tabuleiro.
  * 
  * Se a outra casa adjacente for VAZIA, esta será uma posição onde ocorrerá a ajuda. 
  * Para além disso, se for VAZIA ou AJUDA, será também uma das casas alteradas pelo solver do jogo.  
*/
void column_NearX(ESTADO *n, int l, int c)
{
	   n->ajuda.val = 0;

	   if ((n->grelha[l][c] == FIXO_X || n->grelha [l][c] == SOL_X) &&
	      (n->grelha[l - 1][c] == FIXO_X || n->grelha [l - 1][c] == SOL_X))
	   	   {				
	   	       if(n->grelha[l + 1][c] == VAZIA || n->grelha[l + 1][c] == AJUDA) 
	   	 		{ 
				   		  n->ajuda.val = 1;
				          n->ajuda.x = l + 1;
				          n->ajuda.y = c;
						  n->ajuda.type = 'O';
				}
	   		   
	   	       if(n->grelha[l - 2][c] == VAZIA || n->grelha[l - 2][c] == AJUDA)
	   		   	{ 
				   		  n->ajuda.val = 1;
				          n->ajuda.x = l - 2;
				          n->ajuda.y = c;
						  n->ajuda.type = 'O';
				}
	   	   }
}

/** Função responsável por verificar se existe alguma posição em que é obrigatório jogar SOL_O.
  * 
  * Para tal, considera as casas verticais espaçadas por uma casa VAZIA ou AJUDA e que possuem o valor SOL_X ou FIXO_X.
  * Uma dessas casas horizontais está na posição (l,c) do tabuleiro.
  * 
  * Se a casa que se encontra no meio for VAZIA, esta será uma posição onde ocorrerá a ajuda. 
  * Para além disso, se for VAZIA ou AJUDA, será também uma das casas alteradas pelo solver do jogo.
*/
void column_SpacedX(ESTADO*n, int l, int c)
{
	   		if ((n->grelha[l][c] == FIXO_X || n->grelha [l][c] == SOL_X) &&
	   	   (n->grelha[l + 2][c] == FIXO_X || n->grelha [l + 1] [c] == SOL_X) &&
	   	   (n->grelha[l + 1][c] == VAZIA || n->grelha[l + 1][c] == AJUDA))
				{ 
				   		  n->ajuda.val = 1;
				          n->ajuda.x = l + 1;
				          n->ajuda.y = c;
						  n->ajuda.type = 'O';
				}
	   
	   if ((n->grelha[l][c] == FIXO_X || n->grelha [l][c] == SOL_X) &&
	   	   (n->grelha[l - 2][c] == FIXO_X || n->grelha [l - 2] [c] == SOL_X) &&
	   	   (n->grelha[l - 1][c] == VAZIA || n->grelha[l - 1][c] == AJUDA))
	   			{ 
				   		  n->ajuda.val = 1;
				          n->ajuda.x = l - 1;
				          n->ajuda.y = c;
						  n->ajuda.type = 'O';
				}
}   

/** Função responsável por verificar se existe alguma posição em que é obrigatório jogar SOL_X.
  * 
  * Para tal, considera se duas casas verticais adjacentes possuem o valor de SOL_O ou FIXO_O.
  * Uma das casas em questão corresponde, à casa da posição (l,c) do tabuleiro.
  * 
  * Se a outra casa adjacente for VAZIA, esta será uma posição onde ocorrerá a ajuda. 
  * Para além disso, se for VAZIA ou AJUDA, será também uma das casas alteradas pelo solver do jogo.  
*/  
void column_NearO(ESTADO *n, int l, int c)
{
	    n->ajuda.val = 0;
		
		if ((n->grelha[l][c] == FIXO_O || n->grelha [l][c] == SOL_O) &&
		   (n->grelha[l - 1][c] == FIXO_O || n->grelha [l - 1] [c] == SOL_O))
		   {				
				if(n->grelha[l + 1][c] == VAZIA || n->grelha[l + 1][c] == AJUDA)
				{ 
				   n->ajuda.val = 1;
				   n->ajuda.x = l + 1;
				   n->ajuda.y = c;
				   n->ajuda.type = 'X';
				}
					   
				if(n->grelha[l - 2][c] == VAZIA || n->grelha[l - 2][c] == AJUDA) 
				{ 
				   n->ajuda.val = 1;
				   n->ajuda.x = l - 2;
				   n->ajuda.y = c;
				   n->ajuda.type = 'X';
				}
		   }
}

/** Função responsável por verificar se existe alguma posição em que é obrigatório jogar SOL_X.
  * 
  * Para tal, considera as casas verticais espaçadas por uma casa VAZIA ou AJUDA e que possuem o valor SOL_O ou FIXO_O.
  * Uma dessas casas horizontais está na posição (l,c) do tabuleiro.
  * 
  * Se a casa que se encontra no meio for VAZIA, esta será uma posição onde ocorrerá a ajuda. 
  * Para além disso, se for VAZIA ou AJUDA, será também uma das casas alteradas pelo solver do jogo.
*/
void column_SpacedO(ESTADO *n, int l, int c)
{
		n->ajuda.val = 0;
		if ((n->grelha[l][c] == FIXO_O || n->grelha [l][c] == SOL_O) &&
		   (n->grelha[l - 2][c] == FIXO_O || n->grelha [l - 2] [c] == SOL_O) &&
		   ((n->grelha[l - 1][c] == VAZIA) || (n->grelha[l - 1][c] == AJUDA)))
	           	{ 
				   n->ajuda.val = 1;
				   n->ajuda.x = l - 1;
				   n->ajuda.y = c;
				   n->ajuda.type = 'X';
				}
}

// Diagonais

/** Função responsável por verificar se existe alguma posição em que é obrigatório jogar SOL_X.
  * 
  * Para tal, considera as casas oblíquas adjacentes segundo uma reta com declive positivo que possuem o valor SOL_O ou FIXO_O.
  * Uma dessas casas horizontais está na posição (l,c) do tabuleiro.
  * 
  * Se a casa que se encontra no meio for VAZIA, esta será uma posição onde ocorrerá a ajuda. 
  * Para além disso, se for VAZIA ou AJUDA, será também uma das casas alteradas pelo solver do jogo.
*/
void diagonal_NearDirO (ESTADO *n, int l, int c)
{
		n->ajuda.val = 0;
		
		if ((n->grelha[l][c] == FIXO_O || n->grelha [l][c] == SOL_O) &&
		   (n->grelha[l - 1][c + 1] == FIXO_O || n->grelha [l - 1] [c + 1] == SOL_O))
				{
					if (n->grelha[l - 2][c + 2] == VAZIA || n->grelha[l - 2][c + 2] == AJUDA)
						{
							n->ajuda.val = 1;
							n->ajuda.x = l - 2;
							n->ajuda.y = c + 2;
							n->ajuda.type = 'X';
						}

					if (n->grelha[l + 1][c - 1] == VAZIA || n->grelha[l + 1][c - 1] == AJUDA)
						{
							n->ajuda.val = 1;
							n->ajuda.x = l + 1;
							n->ajuda.y = c - 1;
							n->ajuda.type = 'X';
						}
				}
}

/** Função responsável por verificar se existe alguma posição em que é obrigatório jogar SOL_X.
  * 
  * Para tal, considera as casas oblíquas adjacentes segundo uma reta com declive negativo que possuem o valor SOL_O ou FIXO_O.
  * Uma dessas casas horizontais está na posição (l,c) do tabuleiro.
  * 
  * Se a casa que se encontra no meio for VAZIA, esta será uma posição onde ocorrerá a ajuda. 
  * Para além disso, se for VAZIA ou AJUDA, será também uma das casas alteradas pelo solver do jogo.
*/
void diagonal_NearEsqO(ESTADO *n, int l, int c)
{
		n->ajuda.val = 0;	
		if ((n->grelha[l][c] == FIXO_O || n->grelha [l][c] == SOL_O) &&
		   (n->grelha[l - 1][c - 1] == FIXO_O || n->grelha [l - 1] [c - 1] == SOL_O))
				{
					  if (n->grelha[l - 2][c - 2] == VAZIA || n->grelha[l - 2][c - 2] == AJUDA)
						{
							n->ajuda.val = 1;
							n->ajuda.x = l - 2;
							n->ajuda.y = c - 2;
							n->ajuda.type = 'X';
						} 
					  
					  if (n->grelha[l + 1][c + 1] == VAZIA || n->grelha[l + 1][c + 1] == AJUDA)
						{
							n->ajuda.val = 1;
							n->ajuda.x = l + 1;
							n->ajuda.y = c + 1;
							n->ajuda.type = 'X';
						}
				}
}		

/** Função responsável por verificar se existe alguma posição em que é obrigatório jogar SOL_X.
  * 
  * Para tal, considera as casas obliquas espaçadas por uma casa VAZIA ou AJUDA e que possuem o valor SOL_O ou FIXO_O.
  * Uma dessas casas horizontais está na posição (l,c) do tabuleiro.
  * 
  * Se a casa que se encontra no meio for VAZIA, esta será uma posição onde ocorrerá a ajuda. 
  * Para além disso, se for VAZIA ou AJUDA, será também uma das casas alteradas pelo solver do jogo.
*/
void diagonal_SpacedO(ESTADO *n, int l, int c)
{	
		n->ajuda.val = 0;
		if ((n->grelha[l][c] == FIXO_O || n->grelha [l][c] == SOL_O) &&
		   (n->grelha[l - 2][c + 2] == FIXO_O || n->grelha [l - 2] [c + 2] == SOL_O) &&
		   (n->grelha[l - 1][c + 1] == VAZIA || n->grelha[l - 1][c + 1] == AJUDA))
					    {
							n->ajuda.val = 1;
							n->ajuda.x = l - 1;
							n->ajuda.y = c + 1;
							n->ajuda.type = 'X';
						}

		if ((n->grelha[l][c] == FIXO_O || n->grelha [l][c] == SOL_O) &&
		   (n->grelha[l - 2][c - 2] == FIXO_O || n->grelha [l - 2] [c - 2] == SOL_O) &&
		   (n->grelha[l - 1][c - 1] == VAZIA || n->grelha[l - 1][c - 1] == AJUDA))
						{
							n->ajuda.val = 1;
							n->ajuda.x = l - 1;
							n->ajuda.y = c - 1;
							n->ajuda.type = 'X';
						}
}

/** Função responsável por verificar se existe alguma posição em que é obrigatório jogar SOL_O.
  * 
  * Para tal, considera as casas oblíquas adjacentes segundo uma reta com declive positivo que possuem o valor SOL_X ou FIXO_X.
  * Uma dessas casas horizontais está na posição (l,c) do tabuleiro.
  * 
  * Se a casa que se encontra no meio for VAZIA, esta será uma posição onde ocorrerá a ajuda. 
  * Para além disso, se for VAZIA ou AJUDA, será também uma das casas alteradas pelo solver do jogo.
*/
void diagonal_NearDirX (ESTADO *n, int l, int c)
{
		n->ajuda.val = 0;

		if ((n->grelha[l][c] == FIXO_X || n->grelha [l][c] == SOL_X) &&
		   (n->grelha[l - 1][c + 1] == FIXO_X || n->grelha [l - 1] [c + 1] == SOL_X))
				{
					 if (n->grelha[l - 2][c + 2] == VAZIA || n->grelha[l - 2][c + 2] == AJUDA)
						{
							n->ajuda.val = 1;
							n->ajuda.x = l - 2;
							n->ajuda.y = c + 2;
							n->ajuda.type = 'O';
						}
						 
					 if (n->grelha[l + 1][c - 1] == VAZIA || n->grelha[l + 1][c - 1] == AJUDA)
						{
							n->ajuda.val = 1;
							n->ajuda.x = l + 1;
							n->ajuda.y = c - 1;
							n->ajuda.type = 'O';
						}
				}
}

/** Função responsável por verificar se existe alguma posição em que é obrigatório jogar SOL_O.
  * 
  * Para tal, considera as casas oblíquas adjacentes segundo uma reta com declive negativo que possuem o valor SOL_X ou FIXO_X.
  * Uma dessas casas horizontais está na posição (l,c) do tabuleiro.
  * 
  * Se a casa que se encontra no meio for VAZIA, esta será uma posição onde ocorrerá a ajuda. 
  * Para além disso, se for VAZIA ou AJUDA, será também uma das casas alteradas pelo solver do jogo.
*/
void diagonal_NearEsqX (ESTADO *n, int l, int c)
{
		n->ajuda.val = 0;

		if ((n->grelha[l][c] == FIXO_X || n->grelha [l][c] == SOL_X) &&
		   (n->grelha[l - 1][c - 1] == FIXO_X || n->grelha [l - 1] [c - 1] == SOL_X))
				{
				     if (n->grelha[l - 2][c - 2] == VAZIA || n->grelha[l - 2][c - 2] == AJUDA)
						 {
							n->ajuda.val = 1;
							n->ajuda.x = l - 2;
							n->ajuda.y = c - 2;
							n->ajuda.type = 'O';
						 }
					 if (n->grelha[l + 1][c + 1] == VAZIA || n->grelha[l + 1][c + 1] == AJUDA)
					     {
							n->ajuda.val = 1;
							n->ajuda.x = l + 1;
							n->ajuda.y = c + 1;
							n->ajuda.type = 'O';
						}
				}
}

/** Função responsável por verificar se existe alguma posição em que é obrigatório jogar SOL_O.
  * 
  * Para tal, considera as casas obliquas espaçadas por uma casa VAZIA ou AJUDA e que possuem o valor SOL_X ou FIXO_X.
  * Uma dessas casas horizontais está na posição (l,c) do tabuleiro.
  * 
  * Se a casa que se encontra no meio for VAZIA, esta será uma posição onde ocorrerá a ajuda. 
  * Para além disso, se for VAZIA ou AJUDA, será também uma das casas alteradas pelo solver do jogo.
*/
void diagonal_SpacedX(ESTADO*n, int l, int c)
{		
		if ((n->grelha[l][c] == FIXO_X || n->grelha [l][c] == SOL_X) &&
		   (n->grelha[l - 2][c + 2] == FIXO_X || n->grelha [l - 2] [c + 2] == SOL_X) &&
		   (n->grelha[l - 1][c + 1] == VAZIA || n->grelha[l - 1][c + 1] == AJUDA))
						{
							n->ajuda.val = 1;
							n->ajuda.x = l - 1;
							n->ajuda.y = c + 1;
							n->ajuda.type = 'O';
						}
		if ((n->grelha[l][c] == FIXO_X || n->grelha [l][c] == SOL_X) &&
		   (n->grelha[l - 2][c - 2] == FIXO_X || n->grelha [l - 2] [c - 2] == SOL_X) &&
		   (n->grelha[l - 1][c - 1] == VAZIA || n->grelha[l - 1][c - 1] == AJUDA))		
						{
							n->ajuda.val = 1;
							n->ajuda.x = l - 1;
							n->ajuda.y = c - 1;
							n->ajuda.type = 'O';
						}
}