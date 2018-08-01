#include <stdio.h>
#include "estado.h"
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER		10240
#define PATH_USERS "/var/www/html/users/"

// Função que converte um ESTADO na string correspondente.
char *estado2str(ESTADO e) {
	static char buffer[MAX_BUFFER];
	unsigned char *p = (unsigned char *) &e;
	int i;

	buffer[0] = 0;
	for(i = 0; i < (int) sizeof(ESTADO); i++)
		sprintf(buffer, "%s%02x", buffer, p[i]);
	
	return buffer;
}

// Função que converte uma string no ESTADO correspondente.
ESTADO str2estado(char *argumentos) {
	ESTADO e;
	unsigned char *p = (unsigned char *) &e;
	int i;

	for(i = 0; i < (int) sizeof(ESTADO); i++, argumentos += 2) {
		unsigned d;
		sscanf(argumentos, "%2x", &d);
		p[i] = (unsigned char) d;
	}
	
	return e;
}

// Função responsável pelo push dos dados provenientes da stack do ficheiro.
void addHead (LVal * l, STV val) {
	LVal newnode = malloc(sizeof(struct lista));
	newnode->value = val;
	newnode->prox = *l;
	*l = newnode;
}

// Função responsável pelo pop dos dados provenientes da stack que se encontra no ficheiro.
STV popHead(LVal * l,STV val){
	if (*l != NULL){
		val = (*l)->value;
		LVal aux = *l;
		l = &(*l)->prox;
		free(aux);
	}
	return val;
}

// Função responsável por adicionar dados do jogo na cauda da stack.
void addToTail(LVal *s, int i, int j, char val) {
	LVal *aux = s;
	LVal newnode = malloc(sizeof(struct lista));
	newnode->value.x=i;
	newnode->value.y=j;
	newnode->value.val=val;
	newnode->prox=NULL;
	while (*aux!=NULL)
		aux = &(*aux)->prox;
	*aux=newnode;
}






