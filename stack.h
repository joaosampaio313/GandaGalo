#ifndef ___STACK_H___
#define ___STACK_H___

/**
@file stack.h
Definição das funções relacionadas com a STACK. */

/** Função que lê a stack existente no ficheiro que lhe é passado como parâmetro. */
LVal readstack (FILE *fp);

/** Função que retira o elemento do topo da stack, transformando de seguida numa string. */
void stack2str(ESTADO * e, FILE *fp);

/** Função responsável por adicionar dados do jogo na cauda da stack. */
void addHead (LVal * l, STV val);

/** Função responsável pelo pop dos dados provenientes da stack que se encontra no ficheiro. */
STV popHead (LVal * l, STV aux);

/** Função responsável pelo push dos dados provenientes da stack do ficheiro. */
void addToTail(LVal *s, int i, int j, char val,int anc);

#endif
