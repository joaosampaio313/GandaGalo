/**
@file exemplo.c
Junção das funções necessárias para o funcionamento do jogo.
*/
#include "jogo.h"

/** Função que lê o estado do jogo.
  * A leitura varia em função do caracter marcador. Este altera-se consoante os acontecimentos que ocorrem no jogo. */
void game(char *args, ESTADO e, int x, int y)
{
	char* aux;
	if(args != NULL && strlen(args) > 0)
	{
		aux = strstr(args,",");
		switch(aux[1])
		{
		  case 'Q': player_choice(x,y); break;
          case 'T': tab_choice(e,aux,x,y); break;
          case 'G': init_game(e,aux,x,y); break;
          case 'P': play(e,aux,x,y); break;
		  case 'N': check_anchor(e,aux,x,y); break;
		  case 'U': click_undo(e,aux,x,y); break;
		  case 'A': click_anchor(e,aux,x,y); break;
		  case 'H': click_help(e,aux,x,y); break;
		  case 'S': click_solver(e,aux,x,y); break;
	    }
	}  
	else make_title(x,y);
}  
 
/** Função responsável pelo funcionamento do jogo. */
int main()
{
	ESTADO e = {0};
	int x = 1900, y = 935;
	game(getenv("QUERY_STRING"),e,x,y);
    return 0;
}