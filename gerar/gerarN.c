#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "cgi.h"
#include "estado.h"
#include "verificacao.c"

/* Função que gera um número aleatório de 0 até a c (o argumento introduzido) */
int getrandom(int c){
	time_t t;
	int n;
	srand((unsigned) time(&t));
	n = (rand() % c);
	return n;
}

/** Função que seleciona uma peça do tabuleiro e, se vazia, altera-a.
  *
  * Para tal, é utilizado o número de colunas e linhas, subtraí-se 1 a cada um, para gerar um número aleatório da coluna e linha que se quer mudar.
  * ou seja, é selecionada uma peça aleatória do tabuleiro.
  *
  * Depois, já dentro do tabuleiro, verifica se a peça é VAZIA.
  * Se fôr então de forma aleatória decide se a peça será Bloqueada, X (fixo) ou O (fixo).
*/
void pickSpot(ESTADO e,int cl,int ln,int *cp,int *lp,int *n){
	int c = getrandom(cl);
	int l = getrandom(ln);
	if(c != *cp && l != *lp){
		if(e.grelha[l][c] == VAZIA){
			int peca = getrandom(2);
			if(peca == 0) e.grelha[l][c] = BLOQUEADA;
			if(peca == 1) e.grelha[l][c] = FIXO_X;
			if(peca == 2) e.grelha[l][c] = FIXO_O;
			if(!verfTable(e)){
				e.grelha[l][c] = VAZIA;
				return;
			}
		}
		else return;
		*cp = c; *lp = l;
	}
	else return;
	(*n)--;
}

/** Função que gera uma grelha no estado dado como argumento.
  *
  * A função recebe a dificuldade pretendida e calcula quantas peças devem ser fixas.
  * De seguida, vai chamando a função pickSpot para aleatóriamente colocar uma peça (Bloqueada,X fixo ou O fixa) no tabuleiro.
*/
void gerarGrelha(ESTADO e,int diff,int col,int lin){
	int n;
	int cp, lp;
	cp = 0; lp = 0;
	if(diff == 1) n = ((col*lin)*45)/100;
	else n = ((col*lin)*30)/100;
	while(n!=0){
		pickSpot(e,col-1,lin-1,&cp,&lp,&n);
	}
}
