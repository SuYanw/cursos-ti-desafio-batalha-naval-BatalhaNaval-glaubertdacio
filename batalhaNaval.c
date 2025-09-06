#include <stdio.h>

// VOCABULARIO TABULEIRO:
#define TAMANHO_TABULEIRO  10
#define TAMANHO_NAVIO       3
#define NAVIO               3
#define AGUA                0



// VOCABULARIO DE DIREÇÕES:
#define DIRECAO_VERTICAL    'V'
#define DIRECAO_HORIZONTAL  'H'


// AÇÕES TABULEIRO:
#define TABULEIRO_LIMPAR    -1
#define TABULEIRO_EXIBIR    -2



/*
    A função que faz a inicialização do tabuleiro, também usei para exibir,
    com objetivo de não ter loops desnecessários no código.

    Parâmetros:
        - tabuleiro[][] > indica nossa matriz que será trabalhada no tabuleiro
        - acao > variável que indica ação.
*/
void Tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int acao){
    /*
        A seguir, dois loops onde percorre a matriz Tabuleiro, 
        adicionando o valor da água em todos os vetores. 

        Vetores serão de 0 à 10, exemplo:

        tabuleiro[0][0] = AGUA;
        tabuleiro[0][1] = AGUA;
        tabuleiro[0][2] = AGUA;
        ...
        tabuleiro[9][0] = AGUA;
        tabuleiro[9][1] = AGUA;
    */

    // Looping percorrendo as linhas
    for(int i = 0; i < TAMANHO_TABULEIRO; i++){

        // Looping percorrendo colunas
        for(int x = 0; x < TAMANHO_TABULEIRO; x++){

            if(acao == TABULEIRO_LIMPAR){
                tabuleiro[i][x] = AGUA;
            }

            if(acao == TABULEIRO_EXIBIR){
                printf("%d ", tabuleiro[i][x]);
            }
        }

        if(acao == TABULEIRO_EXIBIR){
            printf("\n");
        }

    }
}


// Função que faz a adição e posicionamento de navios no tabuleiro.
void TabuleiroPosicionar(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int pos_linha, int pos_coluna, char direcao){

    /*
        Loop do navio, onde adiciona o posicionamento do navio na matriz tabuleiro.
    */
    for(int i = 0; i < TAMANHO_NAVIO; i++){

        // Caso for alteração VERTICAL, definido pela variavel direcao
        if(direcao == DIRECAO_VERTICAL)
        {
            tabuleiro[pos_linha+i][pos_coluna] = NAVIO;
        }

        // Caso for alteração HORIZONTAL, definido pela variavel direcao
        else if(direcao == DIRECAO_HORIZONTAL)
        {
            tabuleiro[pos_linha][pos_coluna+i] = NAVIO;    
        }        
    }

}


int main() {

    // Cria uma matriz, dois vetores com o tamanho de cada vetor especificado.
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Faz a inicialização do tabuleiro, colocando 0 em todos os vetores.
    Tabuleiro(tabuleiro, TABULEIRO_LIMPAR);


    // Inicializando variaveis de posicionamento:
    int linha, coluna;

    // Adição do primeiro navio na vertical.
    linha    = 2;
    coluna   = 3;
    TabuleiroPosicionar(tabuleiro, linha, coluna, DIRECAO_VERTICAL);


    // Adição do segundo navio na horizontal.
    linha    = 4;
    coluna   = 5;
    TabuleiroPosicionar(tabuleiro, linha, coluna, DIRECAO_HORIZONTAL);


    Tabuleiro(tabuleiro, TABULEIRO_EXIBIR);
    return 0;
}


