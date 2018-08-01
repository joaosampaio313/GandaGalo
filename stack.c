/**
@file stack.c
Definição das funções utilizadas na STACK.*/

#include "estado.h"
#include "stack.h"
#include "stdlib.h"
#include "stdio.h"

// Função responsável pelo push dos dados provenientes da stack do ficheiro.
void addHead (LVal *l, STV val) {
	LVal newnode = malloc(sizeof(struct lista));
	newnode->value = val;
	newnode->prox = *l;
	*l = newnode;
}

// Função responsável pelo pop dos dados provenientes da stack que se encontra no ficheiro.
STV popHead(LVal * l,STV val){
	if (*l != NULL)
	{
		val = (*l)->value;
		LVal aux = *l;
		*l = (*l)->prox;
		free(aux);
	}
	return val;
}

// Função responsável por adicionar dados do jogo na cauda da stack.
void addToTail(LVal *s, int i, int j, char val, int anc) {
	LVal *aux = s;
	LVal newnode = malloc(sizeof(struct lista));
	newnode->value.x=i;
	newnode->value.y=j;
	newnode->value.val=val;
	newnode->value.anc=anc;
	newnode->prox=NULL;
	while (*aux!=NULL)
	{
		aux = &(*aux)->prox;
	}
	*aux=newnode;
}

// Função que retira o elemento do topo da stack, transformando de seguida numa string.
void stack2str(ESTADO * e, FILE *fp){
	STV valor;
	while (e->stack != NULL)
	{
		valor = popHead(&(e->stack),valor);
		fprintf(fp," (%d,%d,%d,%d)",valor.x,valor.y,valor.val,valor.anc);
	}
}

// Função que lê a stack existente no ficheiro que lhe é passado como parâmetro.
LVal readstack (FILE *fp){
	int i,j,anc,val;
	LVal s = NULL;
	while((fscanf(fp," (%d,%d,%d,%d)",&i,&j,&val,&anc)) != EOF)
	{
		addToTail(&s,i,j,(char)val,anc);
	}
	return s;
}