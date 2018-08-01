  /**
@file ajuda.c
Ajuda ao jogador
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cgi.h"
#include "estado.h"

#define MAX_BUFFER		10240
#define GRELHA			4
#define TAM			40 

// Funções responsáveis pela ajuda.

// Linhas
// Função responsável por verificar se existe alguma posição em que é obrigatório jogar SOL_X.
// Para tal, considera as casas horizontais adjacentes relativamente á casa da posição (l,c) do tabuleiro.
void line_NearX(ESTADO *n, int l, int c)
{
		n->ajuda.val = 0;

		if ((n->grelha[l][c] == FIXO_X || n->grelha [l][c] == SOL_X) &&
		   (n->grelha[l][c - 1] == FIXO_X || n->grelha [l] [c - 1] == SOL_X))
			{				
				if(n->grelha[l][c + 1] == VAZIA)
				{ 
				  n->ajuda.val = 1;
				  n->ajuda.x = l;
				  n->ajuda.y = c + 1;
				  n->ajuda.type = NEAR_X;
				}
				
				if(n->grelha[l][c - 2] == VAZIA)
				{  
				  n->ajuda.val = 1;
				  n->ajuda.x = l;
				  n->ajuda.y = c - 2;
				  n->ajuda.type = NEAR_X;
				}
			}
}

void line_SpacedX(ESTADO *n, int l, int c)
{
		n->ajuda.val = 0;
		
		if ((n->grelha[l][c] == FIXO_X || n->grelha [l][c] == SOL_X) &&
		   (n->grelha[l][c + 2] == FIXO_X || n->grelha [l] [c + 2] == SOL_X)&&
		   (n->grelha[l][c + 1] == VAZIA))
					{ 
				         n->ajuda.val = 1;
				         n->ajuda.x = l;
				         n->ajuda.y = c + 1;
						 n->ajuda.type = SPACED_X;
					}
				
		if ((n->grelha[l][c] == FIXO_X || n->grelha [l][c] == SOL_X) &&
		   (n->grelha[l][c - 2] == FIXO_X || n->grelha [l] [c - 2] == SOL_X) &&
		   (n->grelha[l][c - 1] == VAZIA))
		           {
						n->ajuda.val = 1;
				   		n->ajuda.x = l;
				   		n->ajuda.y = c - 1;
						n->ajuda.type = SPACED_X;
				   }
}					

// Função responsável por verificar se existe alguma posição em que é obrigatório jogar SOL_O.
// Para tal, considera as casas horizontais adjacentes relativamente á casa da posição (l,c) do tabuleiro.
void lineAdvise_O(ESTADO *n, int l, int c)
{
		n->ajuda.val = 0;
		if ((n->grelha[l][c] == FIXO_O || n->grelha [l][c] == SOL_O) &&
		   (n->grelha[l][c - 1] == FIXO_O || n->grelha [l] [c - 1] == SOL_O))
				{				
				       if(n->grelha[l][c + 1] == VAZIA)
				 		{ 
				   		  n->ajuda.val = 1;
				          n->ajuda.x = l;
				          n->ajuda.y = c + 1;
						}
				       if(n->grelha[l][c - 2] == VAZIA)
					   	{ 
				   		  n->ajuda.val = 1;
				          n->ajuda.x = l;
				          n->ajuda.y = c - 2;
						}
				}
			
		if ((n->grelha[l][c] == FIXO_O || n->grelha [l][c] == SOL_O) &&
		  (n->grelha[l][c + 2] == FIXO_O || n->grelha [l] [c + 2] == SOL_O)&&
		  (n->grelha[l][c + 1] == VAZIA))
						{ 
				   		  n->ajuda.val = 1;
				          n->ajuda.x = l;
				          n->ajuda.y = c + 1;
						}
				
		if ((n->grelha[l][c] == FIXO_O || n->grelha [l][c] == SOL_O) &&
		   (n->grelha[l][c - 2] == FIXO_O || n->grelha [l] [c - 2] == SOL_O)&&
		   (n->grelha[l][c - 1] == VAZIA))  
						{ 
				   		  n->ajuda.val = 1;
				          n->ajuda.x = l;
				          n->ajuda.y = c - 1;
						}
}	

// Colunas

// Função responsável por verificar se existe alguma posição em que é obrigatório jogar SOL_X.
// Para tal, considera as casas verticais adjacentes relativamente á casa da posição (l,c) do tabuleiro.
void columnAdvise_X(ESTADO *n, int l, int c)
{
	   n->ajuda.val = 0;

	   if ((n->grelha[l][c] == FIXO_X || n->grelha [l][c] == SOL_X) &&
	      (n->grelha[l - 1][c] == FIXO_X || n->grelha [l - 1][c] == SOL_X))
	   	   {				
	   	       if(n->grelha[l + 1][c] == VAZIA)
	   	 		{ 
				   		  n->ajuda.val = 1;
				          n->ajuda.x = l + 1;
				          n->ajuda.y = c;
				}
	   		   
	   	       if(n->grelha[l - 2][c] == VAZIA)
	   		   	{ 
				   		  n->ajuda.val = 1;
				          n->ajuda.x = l - 2;
				          n->ajuda.y = c;
				}
	   	   }
	   
	   if ((n->grelha[l][c] == FIXO_X || n->grelha [l][c] == SOL_X) &&
	      (n->grelha[l + 1][c] == FIXO_X || n->grelha [l + 1] [c] == SOL_X) &&
	      (n->grelha[l - 1][c] == VAZIA))
	      		{ 
				   		  n->ajuda.val = 1;
				          n->ajuda.x = l - 1;
				          n->ajuda.y = c;
				}
	   	   			
	   if ((n->grelha[l][c] == FIXO_X || n->grelha [l][c] == SOL_X) &&
	   	   (n->grelha[l + 2][c] == FIXO_X || n->grelha [l + 1] [c] == SOL_X) &&
	   	   (n->grelha[l + 1][c] == VAZIA))
				{ 
				   		  n->ajuda.val = 1;
				          n->ajuda.x = l + 1;
				          n->ajuda.y = c;
				}
	   
	   if ((n->grelha[l][c] == FIXO_X || n->grelha [l][c] == SOL_X) &&
	   	   (n->grelha[l - 2][c] == FIXO_X || n->grelha [l - 2] [c] == SOL_X) &&
	   	   (n->grelha[l - 1][c] == VAZIA))
	   			{ 
				   		  n->ajuda.val = 1;
				          n->ajuda.x = l - 1;
				          n->ajuda.y = c;
				}
}   

// Função responsável por verificar se existe alguma posição em que é obrigatório jogar SOL_O.
// Para tal, considera as casas verticais adjacentes relativamente á casa da posição (l,c) do tabuleiro.
void columnAdvise_O(ESTADO *n, int l, int c)
{
	    n->ajuda.val = 0;
		
		if ((n->grelha[l][c] == FIXO_O || n->grelha [l][c] == SOL_O) &&
		   (n->grelha[l - 1][c] == FIXO_O || n->grelha [l - 1] [c] == SOL_O))
		   {				
				if(n->grelha[l + 1][c] == VAZIA)
				{ 
				   n->ajuda.val = 1;
				   n->ajuda.x = l + 1;
				   n->ajuda.y = c;
				}
					   
				if(n->grelha[l - 2][c] == VAZIA)
				{ 
				   n->ajuda.val = 1;
				   n->ajuda.x = l - 2;
				   n->ajuda.y = c;
				}
		   }
		
		if ((n->grelha[l][c] == FIXO_O || n->grelha [l][c] == SOL_O) &&
		   (n->grelha[l + 1][c] == FIXO_O || n->grelha [l + 1] [c] == SOL_O) &&
		   (n->grelha[l - 1][c] == VAZIA))
				{ 
				   n->ajuda.val = 1;
				   n->ajuda.x = l - 1;
				   n->ajuda.y = c;
				}
	    if ((n->grelha[l][c] == FIXO_O || n->grelha [l][c] == SOL_O) &&
		   (n->grelha[l - 2][c] == FIXO_O || n->grelha [l - 2] [c] == SOL_O) &&
		   (n->grelha[l - 1][c] == VAZIA))
	           	{ 
				   n->ajuda.val = 1;
				   n->ajuda.x = l - 1;
				   n->ajuda.y = c;
				}
}

// Diagonais

// Função responsável por verificar se existe alguma posição em que é obrigatório jogar SOL_O.
// Para tal, considera as casas oblíquas adjacentes relativamente á casa da posição (l,c) do tabuleiro.
void diagonalAdvise_O (ESTADO *n, int l, int c)
{
		n->ajuda.val = 0;
		
		if ((n->grelha[l][c] == FIXO_O || n->grelha [l][c] == SOL_O) &&
		   (n->grelha[l - 1][c + 1] == FIXO_O || n->grelha [l - 1] [c + 1] == SOL_O))
				{
					if (n->grelha[l - 2][c + 2] == VAZIA)
						{
							n->ajuda.val = 1;
							n->ajuda.x = l - 2;
							n->ajuda.y = c + 2;
						}

					if (n->grelha[l + 1][c - 1] == VAZIA)
						{
							n->ajuda.val = 1;
							n->ajuda.x = l + 1;
							n->ajuda.y = c - 1;
						}
				}
				
		if ((n->grelha[l][c] == FIXO_O || n->grelha [l][c] == SOL_O) &&
		   (n->grelha[l - 1][c - 1] == FIXO_O || n->grelha [l - 1] [c - 1] == SOL_O))
				{
					  if (n->grelha[l - 2][c - 2] == VAZIA)
						{
							n->ajuda.val = 1;
							n->ajuda.x = l - 2;
							n->ajuda.y = c - 2;
						} 
					  
					  if (n->grelha[l + 1][c + 1] == VAZIA)
						{
							n->ajuda.val = 1;
							n->ajuda.x = l + 1;
							n->ajuda.y = c + 1;
						}
				}
				
		if ((n->grelha[l][c] == FIXO_O || n->grelha [l][c] == SOL_O) &&
		   (n->grelha[l - 2][c + 2] == FIXO_O || n->grelha [l - 2] [c + 2] == SOL_O) &&
		   (n->grelha[l - 1][c + 1] == VAZIA))
					    {
							n->ajuda.val = 1;
							n->ajuda.x = l - 1;
							n->ajuda.y = c + 1;
						}

		if ((n->grelha[l][c] == FIXO_O || n->grelha [l][c] == SOL_O) &&
		   (n->grelha[l - 2][c - 2] == FIXO_O || n->grelha [l - 2] [c - 2] == SOL_O) &&
		   (n->grelha[l - 1][c - 1] == VAZIA))
						{
							n->ajuda.val = 1;
							n->ajuda.x = l - 1;
							n->ajuda.y = c - 1;
						}
}

// Função responsável por verificar se existe alguma posição em que é obrigatório jogar SOL_X.
// Para tal, considera as casas oblíquas adjacentes relativamente á casa da posição (l,c) do tabuleiro
void diagonalAdvise_X (ESTADO *n, int l, int c)
{
		n->ajuda.val = 0;

		if ((n->grelha[l][c] == FIXO_X || n->grelha [l][c] == SOL_X) &&
		   (n->grelha[l - 1][c + 1] == FIXO_X || n->grelha [l - 1] [c + 1] == SOL_X))
				{
					 if (n->grelha[l - 2][c + 2] == VAZIA)
						{
							n->ajuda.val = 1;
							n->ajuda.x = l - 2;
							n->ajuda.y = c + 2;
						}
						 
					 if (n->grelha[l + 1][c - 1] == VAZIA)
						{
							n->ajuda.val = 1;
							n->ajuda.x = l + 1;
							n->ajuda.y = c - 1;
						}
				}
		
		if ((n->grelha[l][c] == FIXO_X || n->grelha [l][c] == SOL_X) &&
		   (n->grelha[l - 1][c - 1] == FIXO_X || n->grelha [l - 1] [c - 1] == SOL_X))
				{
				     if (n->grelha[l - 2][c - 2] == VAZIA)
						 {
							n->ajuda.val = 1;
							n->ajuda.x = l - 2;
							n->ajuda.y = c - 2;
						 }
					 if (n->grelha[l + 1][c + 1] == VAZIA)
					     {
							n->ajuda.val = 1;
							n->ajuda.x = l + 1;
							n->ajuda.y = c + 1;
						}
				}
				
		if ((n->grelha[l][c] == FIXO_X || n->grelha [l][c] == SOL_X) &&
		   (n->grelha[l - 2][c + 2] == FIXO_X || n->grelha [l - 2] [c + 2] == SOL_X) &&
		   (n->grelha[l - 1][c + 1] == VAZIA))
						{
							n->ajuda.val = 1;
							n->ajuda.x = l - 1;
							n->ajuda.y = c + 1;
						}
		if ((n->grelha[l][c] == FIXO_X || n->grelha [l][c] == SOL_X) &&
		   (n->grelha[l - 2][c - 2] == FIXO_X || n->grelha [l - 2] [c - 2] == SOL_X) &&
		   (n->grelha[l - 1][c - 1] == VAZIA))		
						{
							n->ajuda.val = 1;
							n->ajuda.x = l - 1;
							n->ajuda.y = c - 1;
						}
}

// Função responsável por indicar ao jogador qual a posição mais acertada em que este deve jogar.
void giveHelp (ESTADO n,char* buffer)
{
	n.ajuda.x = -1;
	n.ajuda.y = -1;
	
	int l,c;
	
	for(l = 0; l < n.num_lins && (n.ajuda.val != 1) ; l++)
	{
		for(c = 0; c < n.num_cols && (n.ajuda.val != 1); c++)
			{
				line_NearX(&n,l,c);
				line_SpacedX(&n,l,c);
				/*columnAdvise_O(&n,l,c);
				columnAdvise_X(&n,l,c);
				lineAdvise_O(&n,l,c);
				lineAdvise_X(&n,l,c);
				diagonalAdvise_O(&n,l,c);
				diagonalAdvise_X(&n,l,c); */
			}
	} 
	sprintf(buffer,"http://localhost/cgi-bin/GandaGalo?player1,A%d,%d",(n.ajuda.x),(n.ajuda.y));
}

void solver(ESTADO n, char*buffer)
{
	n.ajuda.x = -1;
	n.ajuda.y = -1;
	
	int l,c;
	
	for(l = 0; l < n.num_lins && (n.ajuda.val != 1) ; l++)
	{
		for(c = 0; c < n.num_cols && (n.ajuda.val != 1); c++)
			{
				line_NearX(&n,l,c);
				line_SpacedX(&n,l,c);
				/*columnAdvise_O(&n,l,c);
				columnAdvise_X(&n,l,c);
				lineAdvise_O(&n,l,c);
				lineAdvise_X(&n,l,c);
				diagonalAdvise_O(&n,l,c);
				diagonalAdvise_X(&n,l,c); */
			}
	} 
	sprintf(buffer,"http://localhost/cgi-bin/GandaGalo?player1,S%d,%d",(n.ajuda.x),(n.ajuda.y));
}
 