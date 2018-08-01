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

const char* ficheiro [] = {"bloq.png","x.png","o.png","vazio.png","x.png","o.png","lamp.png"};

// Função que lê o ficheiro onde se encontra esquematizado o puzzle do jogo. 
// Transforma os caracteres que nele estão presentes nos valores correspondentes.
ESTADO importTables(char *args)
{
	    int l,c;
		int i,j;
		
		char stringPuzzle[100];
        char stringJogo[100];
        char linha[100];
        
		ESTADO e = {0};
		
        // Formação da string do jogo atendendo ao local onde se encontra o ficheiro "puzzles.txt".
		if (args[0] == '\0')
             sprintf(stringJogo,"%spuzzles1.txt",PATH_TABULEIROS);
        else 
		{
			sscanf(args,"%s",stringPuzzle);
            sprintf(stringJogo,"%s%s",PATH_TABULEIROS,stringPuzzle);
        }
		
		// Leitura dos dados provenientes do ficheiro "puzzles.txt".

		FILE *fp = fopen(stringJogo,"r");
	 
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

// Função responsável por atualizar a string do browser, sempre que ocorre uma mudança no tabuleiro do jogo.
char* linkMaker(ESTADO n, int l, int c) // USER E ACAO
{
	static char link[MAX_BUFFER];

	switch(n.grelha[l][c])
	{
	  case VAZIA: 
	  case AJUDA:
	  	n.grelha[l][c] = SOL_X;
	  	break;
	  case SOL_X:
	  	n.grelha[l][c] = SOL_O;
	  	break;
	  case SOL_O:
	  	n.grelha[l][c] = VAZIA;
	  	break;
	 
	}
	sprintf(link, "http://localhost/cgi-bin/GandaGalo?%s", estado2str(n));

	return (link);
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
					ABRIR_LINK(linkMaker(n,l,c));
					IMAGEM(c + trans_C, l + trans_L,60, ficheiro[v]);
					FECHAR_LINK;
					break;
				case SOL_X:
					ABRIR_LINK(linkMaker(n,l,c));
					IMAGEM(c + trans_C,l + trans_L,60, ficheiro[v]);
					FECHAR_LINK;
					break;
				case SOL_O:
					ABRIR_LINK(linkMaker(n,l,c));
					IMAGEM(c + trans_C,l + trans_L,60, ficheiro[v]);
					FECHAR_LINK;
					break;
				case AJUDA:
					ABRIR_LINK(linkMaker(n,l,c));
					IMAGEM(c + trans_C,l + trans_L,60,ficheiro[v]);
					FECHAR_LINK;
					break;
			}
		}
	}
}

// Função responsável pelo desenho dos comandos do jogo.
// Sinaliza se o jogador completou o tabuleiro e se as suas jogadas são válidas.
void drawButtons(ESTADO n,int x, int y)
{	
	char buffer[MAX_BUFFER];
	giveHelp(n,buffer);
	int trans_L = (y / 2)/ 40;
	int trans_C = (x / 2)/ 40;

	// Comandos
	ABRIR_LINK("http://localhost/cgi-bin/GandaGalo");
	IMAGEM(trans_C - 415,trans_L + 10,60,"novo.png");
	FECHAR_LINK;

	ABRIR_LINK(buffer);
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

	//n.grelha[-1][0] = SOL_X;
}

// Função que altera o estado do jogo em virtude dos acontecimentos provocados pelo jogador.
ESTADO ler_estado(char *args) 
{
	printf("args: %s", args);
	if(strlen(args) < 50)
		return importTables(args);
	
	return str2estado(args);
}

// Função responsável pelo funcionamento do jogo.
int main()
{
	ESTADO e = ler_estado(getenv("QUERY_STRING"));
	int x = 1366, y = 768;
	
	COMECAR_HTML;
	ABRIR_SVG(x,y);
	RETANGULO(x,y);
	
	drawTable(e,x,y);
	drawButtons(e,x,y);
	drawIcons(e,x,y);
	
	FECHAR_SVG;
	FECHAR_HTML;
	return 0;
}
