#ifndef ___FICHEIROS_H___
#define ___FICHEIROS_H___
/**
@file ficheiros.h
Protótipos das funções relacionadas com ficheiros.*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>

#include "estado.h"
#include "stack.h"

/**Função que importa um tabuleiro do ficheiro. */
ESTADO puzzle_reader(ESTADO e, FILE *fp);

/** Após uma alteração no tabuleiro, a função escreve no ficheiro o tabuleiro resultante. */
void puzzle_writer(ESTADO e,FILE *fp);

/** Função responsável por ler o ESTADO que se encontra num ficheiro. */
ESTADO state_reader(ESTADO e);

/** Função responsável por escrever no ficheiro o resultado da alteração do estado. */
void state_writer(ESTADO e);

#endif