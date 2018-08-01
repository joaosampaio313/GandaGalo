 /**
@file ficheiros.c
Funções relacionadas com ficheiros.
*/

#include "ficheiros.h"

/** Caminho para guardar o ficheiro dos utilizadores. */
#define PATH_UTILIZADORES "/var/www/html/users/"

/**Função que importa um tabuleiro do ficheiro. */
ESTADO puzzle_reader(ESTADO e, FILE *fp){
    int l,c;
    int i,j,m=0;
    char linha[100];

    if (fscanf(fp,"%d %d ", &i, &j) == 2)
    {
        e.num_lins = i;
        e.num_cols = j;
        if (fscanf(fp,"%s",linha) == 1)
        {
          for(l = 0; l < e.num_lins; l++)
          {
              for(c = 0; c < e.num_cols; c++)
              {
                  switch (linha[m])
                  {
                    case '.': e.grelha[l][c] = VAZIA; break;
                    case 'x':
                    case 'X': e.grelha[l][c] = FIXO_X; break;
                    case 'o':
                    case 'O': e.grelha[l][c] = FIXO_O; break;
                    case '#': e.grelha[l][c] = BLOQUEADA; break;
                    case 'c': e.grelha[l][c] = SOL_X; break;
                    case 'p': e.grelha[l][c] = SOL_O; break;
                    case 'h': e.grelha[l][c] = AJUDA; break;
                  }
                  m++;
              }                          
           }
       }
    }
    return e;
}

/** Após uma alteração no tabuleiro, a função escreve no ficheiro o tabuleiro resultante. */
void puzzle_writer(ESTADO e,FILE *fp)
{
    int l,c;
    fprintf(fp,"%d %d ", e.num_lins, e.num_cols);
    for(l=0; l < e.num_lins; l++)
    {
        for(c = 0; c < e.num_cols; c++)
        {
            switch (e.grelha[l][c])
            {
                case VAZIA: fprintf(fp,".");
                            break;
                case FIXO_X: fprintf(fp,"x");
                             break;
                case FIXO_O: fprintf(fp,"o");
                             break;
                case BLOQUEADA: fprintf(fp,"#");
                                break;
                case SOL_X: fprintf(fp,"c");
                            break;
                case SOL_O: fprintf(fp,"p");
                            break;
                case AJUDA: fprintf(fp,"h");
                            break;
            }
        }
    }
}

/** Função responsável por ler o ESTADO que se encontra num ficheiro.
 * Transforma os caracteres lidos no tabuleiro do jogo. 
 * Para além disso, lê a stack que está no ficheiro e atribui-a ao parametro stack do ESTADO. 
 */
ESTADO state_reader(ESTADO e)
{
    char caminho_utilizador[100];
    sprintf(caminho_utilizador,"%splayer%d.txt",PATH_UTILIZADORES,e.utilizador);
    FILE *fp = fopen(caminho_utilizador,"r");
    chmod(caminho_utilizador,0777);
    e = puzzle_reader(e,fp);
    e.stack = readstack(fp);
    fclose(fp);
    return e;
}

//Função responsável por escrever no ficheiro o resultado da alteração do estado.
void state_writer(ESTADO e)
{
    char auxiliar[20];
    sprintf(auxiliar,"%splayer%d.txt",PATH_UTILIZADORES,e.utilizador);
    FILE *fp = fopen(auxiliar,"w");
    chmod(auxiliar,0777);
    puzzle_writer(e,fp);
    stack2str(&e,fp);
    fclose(fp);
}