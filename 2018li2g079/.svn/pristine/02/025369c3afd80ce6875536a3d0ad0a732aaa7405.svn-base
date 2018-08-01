#ifndef ___ESTADO_H___
#define ___ESTADO_H___

#define MAX_STRING 100
#define MAX_STACK 100
/**
@file estado.h
Definição do estado e das funções que convertem estados em strings e vice-versa
*/

/** \brief O tamanho máximo da grelha */
#define MAX_GRID		20

/*Ações
Struct responsável pelas açoes
*/

typedef struct stval {
	char val;
	int x;
	int y;
} STV;

typedef struct lista {
	STV value;
	struct lista *prox;
} *LVal;


/* Ajudas
Struct responsável por definir qual a posiçaão onde ocorrerá a ajuda.
*/
typedef struct aviso{
	int val;
	int x;
	int y;
} AVISO;
// Estado

// Enumeração dos valores que cada casa do tabuleiro pode tomar.
typedef enum {BLOQUEADA, FIXO_X, FIXO_O, VAZIA, SOL_X, SOL_O,AJUDA} VALOR;
/**
\brief Estrutura que armazena o estado do jogo
*/
typedef struct estado {
	char num_lins;
	char num_cols;
	char grelha[MAX_GRID][MAX_GRID];
	char user[100];
	LVal stack;
	AVISO ajuda;
} ESTADO;

/**
\brief Função que converte um estado numa string
@param e O estado
@returns A string correspondente ao estado e
*/
char *estado2str(ESTADO e);

/**
\brief Função que converte uma string num estado 
@param argumentos Uma string contendo os argumentos passados à CGI
@returns O estado correspondente à string dos argumentos
*/
ESTADO str2estado(char *argumentos);

void addHead (LVal * l, STV val);

STV popHead (LVal * l, STV aux);

void addToTail(LVal *s, int i, int j, char val);

#endif

