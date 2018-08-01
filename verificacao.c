/**
@file verificacao.c
Validação do Tabuleiro
*/

#include "verificacao.h"
#include "estado.h"

/** Função que verifica se existem 3 peças iguais na horizontal (linha).
  *
  * Verifica que tipo de peça é, na posição a analizar, e se for X ou O vê as peças à sua direita e à sua esquerda.
  * 
  * Caso houver três peças do mesmo tipo na horizontal retorna valor 0. Se não, retorna valor 1.
*/
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

/** Função que verifica se existem 3 peças iguais na vertical (coluna).
  *
  * Verifica que tipo de peça é, na posição a analizar, e se for X ou O vê as peças em cima e em baixo.
  * 
  * Caso houver três peças do mesmo tipo na vertical retorna valor 0. Se não, retorna valor 1.
*/
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

/** Função que verifica se existem 3 peças iguais na diagonal.
  *
  * Verifica que tipo de peça é, na posição a analizar, e se for X ou O vê as peças do canto superior direito e inferior esquerda.
  * Como também os cantos superior esquerdo e inferior direito.
  * 
  * Caso houver três peças do mesmo tipo na diagonal retorna valor 0. Se não, retorna valor 1.
*/
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

/** Função responsavél por verificar se existe no tabuleiro alguma sequência de 3 casas com o mesmo valor.
  *
  * Os cantos do tabuleiro não são analisados pela função uma vez que serão analizados mas no sentido de verificar outras posições.
  * Isto é, cada posição é analizada pelas posições adjacentes (8 posições; 3x3) o que significa que serão verificados também.
  *
  * A função verifica primeiro os elementos da primeira e última linha, aplicando a função lineCheck.
  * Depois as posições da primeira e última coluna, aplicando a função collumCheck.
  * E por fim, analiza as restantes posições do tabuleiro para determinar se o tabuleiro é válido ou não.
*/
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

/** Função que verifica se o tabuleiro está completo, isto é, sem quaisquer peças vazias ou peças de ajuda. */
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