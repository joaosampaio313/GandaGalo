#ifndef ___JOGO_H___
#define ___JOGO_H___
/**
@file jogo.h
Protótipos das funções responsáveis pela parte gráfica e pelas alterações que ocorrem no tabuleiro do jogo.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

#include "cgi.h"
#include "estado.h"
#include "stack.h"
#include "ficheiros.h"
#include "ajuda.h"
#include "verificacao.h"

/** Função responsável pelo desenho dos botões que provocam alterações no tabuleiro.*/
void buttons_drawer(ESTADO e);

/** Função responsável pelo desenho dos icones do jogo. */
void icons_drawer(ESTADO e);

/** Função responsável pelo desenho do tabuleiro. */
void puzzle_drawer(ESTADO e, int x, int y);

/** Função responsável pela parte gráfica do jogo. */
void game_drawer(ESTADO e, int x, int y);

/** Função responsável por desenhar as imagens que permitem a escolha do tabuleiro. */
void tab_choice(ESTADO e, char* aux, int x, int y);

/** Função responsável por colocar as imagens que permite escolher o número do utilizador. */
void player_choice(int x, int y);

/** Função responsável por desenhar o tabuleiro inicial.*/
void init_game(ESTADO e,char* aux,int x, int y);

/** Função que identifica a última casa que o jogador alterou antes de utilizar uma âncora. */
void play_finder(ESTADO *e, STV v);

/** Função que altera a peça, consoante a jogada do utilizador. */
STV play_maker(ESTADO *e, int l, int c);

/** Função responsável por atualizar a string do browser sempre que ocorre uma mudança no tabuleiro do jogo. */
char* link_maker(ESTADO e, int l, int c);

/** Função encarregue por colocar as imagens no tabuleiro, consoante as jogadas do utilizador.*/
void play(ESTADO e, char* aux, int x,int y);

/** Função responsável por alterar o tabuleiro para a última jogada do utilizador. */
void click_undo(ESTADO e, char* aux, int x, int y);

/** Função responsável pela ocorrência de ajuda no jogo. */
void click_help (ESTADO e, char* aux, int x, int y);

/** Função responsável por colocar a imagem que permite que ocorra uma iteração da resolução do tabuleiro. */
void click_solver(ESTADO e, char *aux, int x, int y);

/** Função responsável por fixar o momento do jogo pretendido pelo utilizador. */
void check_anchor(ESTADO e,char *aux,int x, int y);

/** Função responsável por regressar ao momento do jogo onde foi fixada a última âncora.*/
void click_anchor(ESTADO e, char* aux, int x, int y);

/** Função responsável por colocar a imagem correspondente ao titulo do jogo.*/
void make_title(int x, int y);

#endif