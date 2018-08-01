#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cgi.h"
#include "estado.h"
#include "verificacao.c"
#include "ajuda.c"


#define MAX_BUFFER		10240
#define GRELHA			4
#define TAM			    40 

// Diretoria para encontrar o ficheiro puzzles.txt
#define PATH_TABULEIROS "/var/www/html/puzzles/"
#define PATH_USERS "/var/www/html/users/"	

const char* ficheiro [] = {"bloq.png","x.png","o.png","vazio.png","x.png","o.png","lamp.png"};

// Função que retira o elemento do topo da stack, transformando de seguida numa string.
void stack2str(ESTADO * e, FILE *fp){
	STV valor;
	STV aux;
	if(e->stack!=NULL)
	{
		valor = popHead(&(e->stack),aux);
		fprintf(fp," (%d,%d,%d)",valor.x,valor.y,valor.val);
		//fprintf(fp," (%d,%d,%d)",e->stack->value.x,e->stack->value.y,e->stack->value.val);
	}
}
// Função que lê a stack existente no ficheiro que lhe é passado como parâmetro.
LVal readstack (FILE *fp){
	int i,j;
	int val;
	LVal s = NULL;
	while ((fscanf(fp," (%d,%d,%d)",&i,&j,&val))!=EOF)
	{
		addToTail(&s,i,j,(char)val);
	}
	return s;
}

// Função responsável pela leitura do conteúdo do ficheiro. Este conteúdo será transformado no estado correspondente.
void ler_ficheiro(char *nomef_estado, ESTADO * e){
	char aux[MAX_BUFFER];
	FILE *fp = fopen(nomef_estado,"r");
	fscanf(fp,"%s",aux);
	*e=str2estado(aux);
	e->stack=readstack(fp);
	fclose(fp);
}

// Função responsável por escrever no ficheiro o resultado da alteração do estado.
void escrever_estado(ESTADO e){
	char aux2[200];
	sprintf(aux2,"%s%s.txt",PATH_USERS,e.user);
	FILE *fp = fopen(aux2,"w");
	char aux[MAX_BUFFER];
	strcpy(aux,estado2str(e));
	fprintf(fp, "%s", aux);
	stack2str(&e,fp);
	fclose(fp);
}

// Função responsável por ler o ESTADO que se encontra num ficheiro
char* writeState(char* caminho, char* buffer){
	FILE *fp = fopen(caminho,"w");
	fprintf(fp, "%s", buffer);
	fclose(fp);
	
	return buffer;
}

// Função responsável por atualizar a string do browser, sempre que ocorre uma mudança no tabuleiro do jogo.
char* linkTable(ESTADO e, int l, int c){
	static char link[MAX_BUFFER];
	sprintf(link, "http://localhost/cgi-bin/GandaGalo?%s,P%d,%d",e.user,l,c);
	return (link);
}

void undo(ESTADO e,char* buffer){
	STV jogada;
	STV aux;
	jogada = popHead(&e.stack,aux);
	sprintf(buffer,"http://localhost/cgi-bin/GandaGalo?player1,U%d,%d",jogada.x,jogada.y);
}

void drawUndo (ESTADO e, char * buffer,int x,int y){
	
	int trans_L = (y / 2)/ 40;
	int trans_C = (x / 2)/ 40;

	char caminho[MAX_BUFFER];

	sprintf(caminho,"%splayer1.txt",PATH_USERS);

	if (verfTable(e))
	undo(e,buffer); 

	ABRIR_LINK(writeState(caminho,buffer));
	IMAGEM(trans_C - 630,trans_L - 45,60,"undo.png");
	FECHAR_LINK;

}
// Função responsável pelo desenho do tabuleiro.
void drawTable(ESTADO n,int x, int y){
	int c, l;
	int trans_L = (y / 4);
	int trans_C = (x / 3);
	for(l = 0; l < n.num_lins; l++){
		for(c = 0; c < n.num_cols; c++){
			VALOR v = n.grelha[l][c];
			switch(v){
				case BLOQUEADA:
					IMAGEM(c + trans_C,l +trans_L,60,ficheiro[v]);
					break;
				case FIXO_X:
					IMAGEM(c + trans_C, l + trans_L,60,ficheiro[v]);
					break;
				case FIXO_O:
					IMAGEM(c + trans_C, l + trans_L,60, ficheiro[v]);
					break;
				case VAZIA:
					ABRIR_LINK(linkTable(n,l,c));
					IMAGEM(c + trans_C, l + trans_L,60, ficheiro[v]);
					FECHAR_LINK;
					break;
				case SOL_X:
					ABRIR_LINK(linkTable(n,l,c));
					IMAGEM(c + trans_C,l + trans_L,60, ficheiro[v]);
					FECHAR_LINK;
					break;
				case SOL_O:
					ABRIR_LINK(linkTable(n,l,c));
					IMAGEM(c + trans_C,l + trans_L,60, ficheiro[v]);
					FECHAR_LINK;
					break;
				case AJUDA:
					ABRIR_LINK(linkTable(n,l,c));
					IMAGEM(c + trans_C,l + trans_L,60,ficheiro[v]);
					FECHAR_LINK;
					break;
			}
		}
	}
}

// Função responsável pelo desenho dos comandos do jogo.
// Sinaliza se o jogador completou o tabuleiro e se as suas jogadas são válidas.
void drawButtons(ESTADO e,int x, int y)
{
	char buffer[MAX_BUFFER];
	char caminho[MAX_BUFFER];

	int trans_L = (y / 2)/ 40;
	int trans_C = (x / 2)/ 40;
	
	// Comandos
	ABRIR_LINK("http://localhost/cgi-bin/GandaGalo");
	IMAGEM(trans_C - 415,trans_L + 10,60,"novo.png");
	FECHAR_LINK;

	sprintf(caminho,"%splayer1.txt",PATH_USERS);

	drawUndo(e,buffer,x,y);
	
	if (verfTable(e))
	giveHelp(e,buffer);
	
	ABRIR_LINK(writeState(caminho,buffer));
	IMAGEM(trans_C - 200,trans_L - 40,60,"einstein.png");
	FECHAR_LINK;	
}

// Função responsável pelo desenho dos icones do jogo.
void drawIcons(ESTADO n, int x, int y)
{
	int trans_L = (y / 2)/ 40;
	int trans_C = (x / 2)/ 40;
	// Verificação
		if (!(verfTable(n)))
	IMAGEM(trans_C - 200, trans_L - 110,60,"thumbDown.png");
		else
	IMAGEM(trans_C - 200, trans_L - 110,60,"tUp.png");
		if (isComplete(n) && verfTable(n))
	IMAGEM(trans_C - 470,trans_L - 250,80,"greatJob.png");
}

// Função que lê o ficheiro onde se encontra esquematizado o puzzle do jogo. 
// Transforma os caracteres que nele estão presentes nos valores correspondentes.
ESTADO importTables(char *args, ESTADO e)
{
	int l,c;
	int i,j;
	char linha[100];
      
	FILE *fp = fopen(args,"r");
	 
    fscanf(fp,"%d %d", &i, &j);
		
	e.num_lins = i;
    e.num_cols = j;
        
	for(l = 0; l < e.num_lins; l++)
		{
			fscanf(fp,"%s",linha);
            
			for(c = 0; c < e.num_cols; c++)
				
			{
                switch (linha[c])
				{
                    case '.': e.grelha[l][c]= VAZIA;
                          	  break;
                    case 'x':
                    case 'X': e.grelha[l][c]= FIXO_X;
                           	  break;
                    case 'o':
					case 'O': e.grelha[l][c]= FIXO_O;
				    	      break;
                    case '#': e.grelha[l][c]= BLOQUEADA;
                              break;
                }
            }                          
        }

    fclose(fp);
    return e;
}

// Função responsável por definir qual o valor da peça após o click do jogador.
STV nextPeca(ESTADO * e, int l, int c, STV v)
{
	v.x = l;
	v.y = c;
	switch(e->grelha[l][c]){
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

void lastPeca(ESTADO *e, int l, int c)
{	
	switch(e->grelha[l][c]){
		case VAZIA : e->grelha[l][c] = SOL_O;
					break;
		case SOL_X: e->grelha[l][c] = VAZIA;
					break;
		case SOL_O: e->grelha[l][c] = SOL_X;
					break;
	}
}

// Função que altera o estado do jogo em virtude dos acontecimentos provocados pelo jogador.
ESTADO ler_estado(char *args) 
{
	ESTADO e = {0};
	char *user = "player1";
	char nomef_estado[100];
	char nomef_jogo[100];
	char caminho[100];
	
	int l,c;
	
	sprintf(caminho,"%splayer1.txt",PATH_USERS);

	strcpy(e.user,user);
	
	char * aux = strstr(args,",");
	
	if(args != NULL && strlen(args) > 0)
	{
		STV v;
		sprintf(nomef_estado,"%splayer1.txt",PATH_USERS);
		if (aux[1]=='P'){
			sscanf(aux,",P%d,%d",&l,&c);
			ler_ficheiro(nomef_estado,&e);
			v = nextPeca(&e,l,c,v);
			addHead(&(e.stack),v);
		} else{
			   if (aux[1] == 'A')  
			   {
				sscanf(aux,",A%d,%d",&l,&c);
			   	ler_ficheiro(nomef_estado,&e);
			   	e.grelha[l][c] = AJUDA;
			   }
			   if (aux[1] == 'U')
			   {
				sscanf(aux,",U%d,%d",&l,&c);
				ler_ficheiro(nomef_estado,&e);
				lastPeca(&e,l,c);
				}

			} 
	}
	else 
		   {
		    sprintf(nomef_jogo,"%spuzzle1.txt",PATH_TABULEIROS);
		    e = importTables(nomef_jogo,e);
		   }
	return e;
}

// Função responsável pelo funcionamento do jogo.
int main()
{
	ESTADO e;

	e = ler_estado(getenv("QUERY_STRING"));
	int x = 1366, y = 768;
	COMECAR_HTML;
	ABRIR_SVG(x,y);
	RETANGULO(x,y);
	
	drawTable(e,x,y);
	drawButtons(e,x,y);
	drawIcons(e,x,y);
	
	FECHAR_SVG;
	FECHAR_HTML;
	escrever_estado(e);
	return 0;
}

/*// Função responsável por retirar a string corresponde ao ESTADO. Esta string encontra-se no ficheiro que é passado como argumento.
char* linkHelp(char *nomef_estado, char* res){
	FILE *fp = fopen(nomef_estado,"r");
	fscanf(fp,"%s",res);
	fclose(fp);
	return res;
}*/

/*
ESTADO drawMenu(ESTADO e)
{
	// Escolher o puzzle 1.

	e.puzzle = 1;
	ABRIR_LINK(chooseEasy(e));
	IMAGEM(10,5,60,"warning.png");
	FECHAR_LINK;

	// Escolher o puzzle 2.
	ABRIR_LINK(chooseHard(e));
	IMAGEM(10,7,60,"warning.png");
	FECHAR_LINK; 

return e;
}

ESTADO chooseEasy(char *args)
{
	ESTADO e = str2estado(args);

	e.jogada = 1;
	e.puzzle = 1;

	args = estado2str(e); 
	
	ABRIR_LINK(args);
	IMAGEM(5,5,40,"warning.png");
	FECHAR_LINK;

	return e;
}
*/
