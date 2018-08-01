/**
@file jogo.c
Funções responsáveis pela parte gráfica e pelas alterações que ocorrem no tabuleiro do jogo.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

#include "cgi.h"
#include "estado.h"
#include "stack.h"
#include "ajuda.h"
#include "ficheiros.h"
#include "verificacao.h"

//Diretorias
/** Caminho para chegar à pasta onde se encontram os tabuleiros do jogo. */
#define PATH_TABULEIROS "/var/www/html/tabuleiros/"

/** Caminho para chegar ao ficheiro dos utilizadores. */
#define PATH_UTILIZADORES "/var/www/html/users/"

// Constantes
/** Constante utilizada para definir o tamanho dos arrays locais formados nas funções criadas.*/
#define MAX_BUFFER      10240

//Imagens
const char* ficheiro[] = {"bloq.png","x.png","o.png","vazio.png","x.png","o.png","lamp.png"};

/** Função que identifica a última casa que o jogador alterou antes de utilizar uma âncora.
 *  Através do STV que recebe, muda a casa para o seu valor correspondente.
*/
void play_finder(ESTADO *e, STV v){
	
	switch(v.val)
	{
		case VAZIA: e->grelha[v.x][v.y]=SOL_X;
					break;
		case SOL_O: e->grelha[v.x][v.y]=VAZIA;
					break;
		case SOL_X: e->grelha[v.x][v.y]=SOL_O;
					break;
		case AJUDA: e->grelha[v.x][v.y]=SOL_X;
					break;
	}
}
/** Função que altera a peça, consoante a jogada do utilizador. */
STV play_maker(ESTADO *e, int l, int c){
	STV v;
	v.x=l;
	v.y=c;
	switch(e->grelha[l][c])
	{
		case VAZIA: v.val = VAZIA;
					e->grelha[l][c] = SOL_X;
			 		break;
		case SOL_X: v.val = SOL_X;
					e->grelha[l][c] = SOL_O;
			 		break;
		case SOL_O: v.val = SOL_O;
					e->grelha[l][c] = VAZIA;
			 		break;
		case AJUDA: v.val = AJUDA;
					e->grelha[l][c] = SOL_X;
					break;
	}
	return v;
}

/** Função responsável por atualizar a string do browser sempre que ocorre uma mudança no tabuleiro do jogo. */
char* link_maker(ESTADO e, int l, int c)
{
	static char link[MAX_BUFFER];
	
	sprintf(link,"http://localhost/cgi-bin/GandaGalo?,P%d,%d,%d,%d",e.utilizador,e.tabuleiro,l,c);
	return link;
}

/** Função responsável pelo desenho dos botões que provocam alterações no tabuleiro.*/
void buttons_drawer(ESTADO e)
{
	char undo[MAX_BUFFER];
	char ancoraCheck[MAX_BUFFER];
	char ancoraGo[MAX_BUFFER];
	
	sprintf(undo,"http://localhost/cgi-bin/GandaGalo?,U%d,%d",e.utilizador,e.tabuleiro);
	sprintf(ancoraCheck,"http://localhost/cgi-bin/GandaGalo?,N%d,%d",e.utilizador,e.tabuleiro);
	sprintf(ancoraGo,"http://localhost/cgi-bin/GandaGalo?,A%d,%d",e.utilizador,e.tabuleiro);
	
	// Botão para o Undo.
	ABRIR_LINK(undo);
	IMAGEM(9,8,59,"undo.png");
	FECHAR_LINK;

	// Botão para marcar Âncora.
	ABRIR_LINK(ancoraCheck);
	IMAGEM(9,9,59,"marcar.png");
	FECHAR_LINK;

	// Botão para regressar ao estado da última âncora marcada.
	ABRIR_LINK(ancoraGo);
	IMAGEM(9,10,59,"anchor.png");
	FECHAR_LINK;

	draw_help(e);

	draw_solver(e);
}

/** Função responsável pelo desenho dos icones do jogo. */
void icons_drawer(ESTADO e)
{
	if (verfTable(e))
		IMAGEM(20,10,53,"thumbUp.png");
	else
		IMAGEM(20,10,53,"thumbDown.png");

	if (isComplete(e) && verfTable(e))
		IMAGEM(8,7,100,"greatJob.png");
}

// Função responsável pelo desenho do tabuleiro.
void puzzle_drawer(ESTADO e, int x, int y){
	int c, l;
	int trans_L = (y / 4);
	int trans_C = (x / 3);
	int scale = 70;
	if(e.tabuleiro==2) scale = 60;

	for(l = 0; l < e.num_lins; l++)
	{
		for(c = 0; c < e.num_cols; c++)
		{
			VALOR v = e.grelha[l][c];
			switch(v){
				case BLOQUEADA:
					IMAGEM(c + trans_C,l + trans_L,scale, ficheiro[v]);
					break;
				case FIXO_X:
					IMAGEM(c + trans_C, l + trans_L,scale, ficheiro[v]);
					break;
				case FIXO_O:
					IMAGEM(c + trans_C, l + trans_L,scale, ficheiro[v]);
					break;
				case VAZIA:
					ABRIR_LINK(link_maker(e,l,c));
					IMAGEM(c + trans_C, l + trans_L,scale, ficheiro[v]);
					FECHAR_LINK;
					break;
				case SOL_X:
					ABRIR_LINK(link_maker(e,l,c));
					IMAGEM(c + trans_C,l + trans_L,scale, ficheiro[v]);
					FECHAR_LINK;
					break;
				case SOL_O:
					ABRIR_LINK(link_maker(e,l,c));
					IMAGEM(c + trans_C,l + trans_L,scale, ficheiro[v]);
					FECHAR_LINK;
					break;
				case AJUDA:
					ABRIR_LINK(link_maker(e,l,c));
					IMAGEM(c + trans_C,l + trans_L,scale, ficheiro[v]);
					FECHAR_LINK;
					break;
			}
		}
	}
}

/** Função responsável pela parte gráfica do jogo. */
void game_drawer(ESTADO e, int x, int y){
	COMECAR_HTML;
	ABRIR_SVG(x,y);
	RETANGULO(x,y);
	
	ABRIR_LINK("http://localhost/cgi-bin/GandaGalo");
	IMAGEM(2,0,340,"title.png");
	FECHAR_LINK;

	buttons_drawer(e);
	icons_drawer(e);
	puzzle_drawer(e,x,y);

	FECHAR_SVG;
	FECHAR_HTML;
}

/** Função responsável por colocar as imagens que permite escolher o número do utilizador. */
void player_choice(int x, int y){
	char link[MAX_BUFFER];
	
	COMECAR_HTML;
				  ABRIR_SVG(x,y);
				  RETANGULO(x,y);

				  IMAGEM(6,1,150,"jogador.png");

				  sprintf(link,"http://localhost/cgi-bin/GandaGalo?,T1");

				  ABRIR_LINK(link);
				  IMAGEM(6,2,150,"1.png");
				  FECHAR_LINK;

				  sprintf(link,"http://localhost/cgi-bin/GandaGalo?,T2");
				  
				  ABRIR_LINK(link);
				  IMAGEM(6,4,150,"2.png");
				  FECHAR_LINK;

				  FECHAR_SVG;
	FECHAR_HTML;
}

/** Função responsável por desenhar as imagens que permitem a escolha do tabuleiro. */
void tab_choice(ESTADO e, char* aux, int x, int y){
	char link[MAX_BUFFER];
	
	sscanf(aux,",T%d",&e.utilizador);
	COMECAR_HTML;
				  ABRIR_SVG(x,y);
				     RETANGULO(x,y);
   
				     IMAGEM(6,1,150,"tabuleiro.png");
   
				     sprintf(link,"http://localhost/cgi-bin/GandaGalo?,G%d,1",e.utilizador);
				     ABRIR_LINK(link);
				     IMAGEM(6,2,150,"1.png");
				     FECHAR_LINK;
   
				     sprintf(link,"http://localhost/cgi-bin/GandaGalo?,G%d,2",e.utilizador);
				     ABRIR_LINK(link);
				     IMAGEM(6,4,150,"2.png");
				     FECHAR_LINK;				   
				  FECHAR_SVG;
	FECHAR_HTML;
}

/** Função responsável por desenhar o tabuleiro inicial.*/
void init_game(ESTADO e,char* aux,int x, int y){
	char caminho_tabuleiro[100];
	FILE *fp;

	sscanf(aux,",G%d,%d",&e.utilizador,&e.tabuleiro);
	sprintf(caminho_tabuleiro,"%stabuleiro%d.txt",PATH_TABULEIROS,e.tabuleiro);
				  
	fp = fopen(caminho_tabuleiro,"r");
	
	chmod(caminho_tabuleiro,0777);
	e = puzzle_reader(e,fp);
	
	fclose(fp);
	
	game_drawer(e,x,y);
	state_writer(e);
}

/** Função encarregue por colocar as imagens no tabuleiro, consoante as jogadas do utilizador.*/
void play(ESTADO e, char* aux, int x,int y){
	int l,c;
	STV v;

	sscanf(aux,",P%d,%d,%d,%d",&e.utilizador,&e.tabuleiro,&l,&c);
	e = state_reader(e);
	
	v = play_maker(&e,l,c);
	v.anc=0;
				  
	addHead(&(e.stack),v);
	game_drawer(e,x,y);
	state_writer(e);
}

/** Função responsável por alterar o tabuleiro para a última jogada do utilizador. */
void click_undo(ESTADO e, char* aux, int x, int y){
	STV v;

	sscanf(aux,",U%d,%d",&e.utilizador,&e.tabuleiro);
	
	e = state_reader(e);
	 if(e.stack != NULL)
		{
		  v = popHead(&(e.stack),v);
		  e.grelha[v.x][v.y] = v.val;
		}
	game_drawer(e,x,y);
	state_writer(e);
}

/** Função responsável por fixar o momento do jogo pretendido pelo utilizador. */
void check_anchor(ESTADO e,char *aux,int x, int y){
	STV v;
	
	sscanf(aux,",N%d,%d",&e.utilizador,&e.tabuleiro);
	
	e = state_reader(e);
    if(e.stack != NULL)
		{
		  v = popHead(&(e.stack),v);
		  v.anc=1;
		}
	 
	addHead(&(e.stack),v);
	game_drawer(e,x,y);
	state_writer(e);
}

/* Função responsável por regressar ao momento do jogo onde foi fixada a última âncora.*/
void click_anchor(ESTADO e, char* aux, int x, int y){
	STV v;
	
	sscanf(aux,",A%d,%d",&e.utilizador,&e.tabuleiro);
	
	e = state_reader(e);
	v = popHead(&(e.stack),v);
	
	e.grelha[v.x][v.y] = v.val;
	do
	   {
		if(e.stack != NULL)
		 {
			v = popHead(&(e.stack),v);
			e.grelha[v.x][v.y] = v.val;
		 }
	   } while(v.anc!=1);
	
	v.anc=0;
	play_finder(&e,v);
	addHead(&(e.stack),v);
	game_drawer(e,x,y);
	state_writer(e);
}

/** Função responsável pela ocorrência de ajuda no jogo. */
void click_help (ESTADO e, char* aux, int x, int y){
	int l,c;
	STV v;
	sscanf(aux,",H%d,%d,%d,%d",&e.utilizador,&e.tabuleiro,&l,&c);
	e = state_reader(e);
	v.x=l;
	v.y=c;
	v.val=AJUDA;
	v.anc=0;
	e.grelha[l][c]=v.val;

	e.n_ajudas++;

	addHead(&(e.stack),v);
	game_drawer(e,x,y);
	state_writer(e);
}

/** Função responsável por colocar a imagem que permite que ocorra uma iteração da resolução do tabuleiro. */
void click_solver(ESTADO e, char *aux, int x, int y){
	int l,c;
	char sol;
	
	sscanf(aux,",S%d,%d,%d,%d,%c",&e.utilizador,&e.tabuleiro,&l,&c,&sol);
				
	e = state_reader(e);
	
	chooseVal(&e,l,c,sol);
	game_drawer(e,x,y);
	state_writer(e);
}

/** Função responsável por colocar a imagem correspondente ao titulo do jogo.*/
void make_title(int x, int y){
	char link[MAX_BUFFER];
	COMECAR_HTML;
	   ABRIR_SVG(x,y);
	   
	   RETANGULO(x,y);
	   sprintf(link,"http://localhost/cgi-bin/GandaGalo?,Q");
		
	   ABRIR_LINK(link);
		  IMAGEM(1,0,650,"title.png");
	   FECHAR_LINK;
        
	   FECHAR_SVG;
	FECHAR_HTML;
}