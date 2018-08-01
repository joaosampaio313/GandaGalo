/**
@file verificacao.c
Validação do Tabuleiro
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cgi.h"
#include "estado.h"
//#include "verificacao.h"

int lineCheck(ESTADO n,int l,int c)
{
	if	((n.grelha[l-1][c] == FIXO_X   || n.grelha[l-1][c] == SOL_X) && 
		(n.grelha[l+1][c] == FIXO_X   || n.grelha[l+1][c] == SOL_X)  && 
		(n.grelha[l][c]   == FIXO_X   || n.grelha[l][c]   == SOL_X))
		return 0;
	
	if  ((n.grelha[l-1][c] == FIXO_O || n.grelha[l-1][c] == SOL_O) &&
		(n.grelha[l+1][c] == FIXO_O || n.grelha[l+1][c] == SOL_O)  &&
		(n.grelha[l][c]   == FIXO_O || n.grelha[l][c]   == SOL_O))
		return 0;
	
	return 1;
}

int columnCheck(ESTADO n,int l,int c)
{
	if  ((n.grelha[l][c-1] == FIXO_X || n.grelha[l][c-1] == SOL_X) &&
		(n.grelha[l][c+1] == FIXO_X || n.grelha[l][c+1] == SOL_X)  &&
		((n.grelha[l][c]   == FIXO_X) || (n.grelha[l][c]   == SOL_X)))
		return 0;
	
	if	((n.grelha[l][c-1] == FIXO_O || n.grelha[l][c-1] == SOL_O) &&
		(n.grelha[l][c+1] == FIXO_O || n.grelha[l][c+1] == SOL_O) &&
		((n.grelha[l][c]   == FIXO_O || n.grelha[l][c]   == SOL_O))) 
		return 0;
	
	return 1;
}

int diagonalCheck(ESTADO n,int l,int c)
{
	if  ((n.grelha[l-1][c-1] == FIXO_X || n.grelha[l-1][c-1] == SOL_X) &&
		(n.grelha[l+1][c+1] == FIXO_X || n.grelha[l+1][c+1] == SOL_X) &&
		(n.grelha[l][c]     == FIXO_X || n.grelha[l][c]     == SOL_X))
		return 0;
	
	if  ((n.grelha[l+1][c-1] == FIXO_X || n.grelha[l+1][c-1] == SOL_X) &&
		(n.grelha[l-1][c+1] == FIXO_X || n.grelha[l-1][c+1] == SOL_X)  &&
		(n.grelha[l][c]     == FIXO_X || n.grelha[l][c]     == SOL_X))
		return 0;
	
	if  ((n.grelha[l-1][c-1] == FIXO_O || n.grelha[l-1][c-1] == SOL_O) &&
		(n.grelha[l+1][c+1] == FIXO_O || n.grelha[l+1][c+1] == SOL_O)  &&
		(n.grelha[l][c]     == FIXO_O || n.grelha[l][c]     == SOL_O))
		return 0;
	
	if	((n.grelha[l+1][c-1] == FIXO_O || n.grelha[l+1][c-1] == SOL_O) &&
		(n.grelha[l-1][c+1] == FIXO_O || n.grelha[l-1][c+1] == SOL_O)  &&
		(n.grelha[l][c]     == FIXO_O || n.grelha[l][c]     == SOL_O))
		return 0;
	
	return 1;
}

// Função responsavél por verificar se existe no tabuleiro alguma sequência de 3 casas com o mesmo valor.
int verfTable(ESTADO n) 
{
	int l,c;
	int linha  = n.num_lins;
	int coluna = n.num_cols;

	for (l = 0; l < linha; l++)
		 {
			for (c = 0; c < coluna; c++)
			{
				// Verifica a primeira e a última linha do tabuleiro
				if ((l == 0 || l == linha - 1) && ((c != 0 && c != coluna - 1)))
				{
					if (!(lineCheck(n,l,c))) return 0;
				}

				// Verifica a primeira e a última coluna do tabuleiro
				if ((l != 0 && l != linha - 1) && (c == 0 || c == coluna - 1))
				{
						if (!(columnCheck(n,l,c))) return 0;
				}
				
				//Verifica as restantes posições da grelha
				if ((!(diagonalCheck(n,l,c))) || (!(lineCheck(n,l,c))) || (!(columnCheck(n,l,c)))) return 0;	 
		 	}
		 }
	return 1;
}

int isComplete (ESTADO n)
{
	int l,c;
	int val = 1;
	
	int linha = n.num_lins;
	int coluna = n.num_cols;
	
	for (l = 0; l < linha; l++)
	{
		for (c = 0; c < coluna; c++)
			if (n.grelha[l][c] == VAZIA || n.grelha[l][c] == AJUDA)
				val = 0;
	}

	return val;
}
