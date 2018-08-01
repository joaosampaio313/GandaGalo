/**
@file ajuda.c
Ajuda ao jogador.
*/
#include "ajuda.h"

//Diretorias
/** Caminho para chegar à pasta onde se encontram os tabuleiros do jogo. */
#define PATH_TABULEIROS "/var/www/html/tabuleiros/"

/** Caminho para chegar ao ficheiro dos utilizadores. */
#define PATH_UTILIZADORES "/var/www/html/users/"

// Constantes
/** Constante utilizada para definir o tamanho dos arrays locais formados nas funções criadas.*/
#define MAX_BUFFER      10240

/* Funções responsáveis pela ajuda. */

/** Função que verifica horizontalmente se existe alguma casa em que é possivel dar AJUDA. */ 
void lineAdvise(ESTADO *e, int l, int c)
{
	line_NearX(e,l,c);
	line_SpacedX(e,l,c);
	line_NearO(e,l,c);
	line_SpacedO(e,l,c);
}

/** Função que verifica verticalmente se existe alguma casa em que é possivel dar AJUDA. */ 
void columnAdvise (ESTADO *e, int l, int c)
{
	column_NearX(e,l,c);
	column_SpacedX(e,l,c);
	column_NearO(e,l,c);
	column_SpacedO(e,l,c);
}

/** Função que verifica diagonalmente se existe alguma casa em que é possivel dar AJUDA. */ 
void diagonalAdvise(ESTADO *e,int l, int c)
{
	diagonal_NearDirX(e,l,c);
	diagonal_NearEsqX(e,l,c);
	diagonal_SpacedX(e,l,c);
	diagonal_NearDirO(e,l,c);
	diagonal_NearEsqO(e,l,c);
	diagonal_SpacedO(e,l,c);
}

/** Função que verifica se exista alguma casa em que é possivel dar AJUDA. */
void checkAdviser (ESTADO *e, int l, int c)
{
	lineAdvise(e,l,c);
	columnAdvise(e,l,c);
	diagonalAdvise(e,l,c);
}

/** Função responsável por indicar ao jogador qual a posição mais acertada em que este deve jogar. */
void giveHelp (ESTADO n,char* buffer)
{
	n.ajuda.x = -1;
	n.ajuda.y = -1;

	n.n_ajudas = 0;
	
	int l,c;
	
	for(l = 0; l < n.num_lins && (n.ajuda.val != 1) ; l++)
	{
		for(c = 0; c < n.num_cols && (n.ajuda.val != 1); c++)
			checkAdviser(&n,l,c);
	}
		sprintf(buffer,"http://localhost/cgi-bin/GandaGalo?,H%d,%d,%d,%d",n.utilizador,n.tabuleiro,(n.ajuda.x),(n.ajuda.y));
}
/** Função responsável por colocar no ecrã as imagens que informam as ajudas restantes do utilizador. */
void helpController (ESTADO e)
{
	  switch(e.n_ajudas)
	  {
	  	case 0 : IMAGEM(1,1,60,"4.png"); break;
	  	case 1 : IMAGEM(1,1,60,"3.png"); break;
	  	case 2 : IMAGEM(1,1,60,"2.png"); break;
	  	case 3 : IMAGEM(1,1,60,"1.png"); break;
  
	  	default : IMAGEM(1,1,80,"noMore.png");
	  }
}

/** Função que coloca no jogo a imagem que permite a ocorrência de ajudas. */
void draw_help(ESTADO e)
{
	char buffer[MAX_BUFFER];

	if (verfTable(e) && e.n_ajudas < 4)
		giveHelp(e,buffer);
	
	ABRIR_LINK(buffer);
	IMAGEM(18,10,59,"help.png");
	FECHAR_LINK;
}

/** SOLVER */

/** Função responsável por verificar em que posições poderá ocorrer a ação do solver do jogo. */
void solver(ESTADO n, char*buffer)
{
	n.ajuda.x = -1;
	n.ajuda.y = -1;
	
	int l,c;
	
	for(l = 0; l < n.num_lins && (n.ajuda.val != 1) ; l++)
	{
		for(c = 0; c < n.num_cols && (n.ajuda.val != 1); c++)
			checkAdviser(&n,l,c);
	} 
	sprintf(buffer,"http://localhost/cgi-bin/GandaGalo?,S%d,%d,%d,%d,%c",n.utilizador,n.tabuleiro,(n.ajuda.x),(n.ajuda.y),(n.ajuda.type));
}

/** Função responsável por alterar o valor da casa da posição (l,c) do tabuleiro.
  * Em virtude disso mesmo, considera o carácter recebido, que lhe indica o valor a colocar.
  * 
  * Se o carácter, for 'O' então joga SOL_O. Caso contrário joga SOL_X.
  */  
void chooseVal (ESTADO* e, int l, int c, char sol)
{
	if (sol == 'O')	
		e->grelha[l][c] = SOL_O;
	else
		e->grelha[l][c] = SOL_X;

	if (!verfTable((*e)))
		e->grelha[l][c] = VAZIA;
}

/** Função encarregue de colocar a imagem que permite a ocorrência de uma iteração da resolução do solver. */
void draw_solver(ESTADO e)
{
	char buffer[MAX_BUFFER];
	char caminho[MAX_BUFFER];

	sprintf(caminho,"%splayer%d.txt",PATH_UTILIZADORES,e.utilizador);

	if (verfTable(e) && !(isComplete(e)))
			solver(e,buffer);
	ABRIR_LINK(buffer);
	IMAGEM(18,8,59,"einstein.png");
	FECHAR_LINK;
}
