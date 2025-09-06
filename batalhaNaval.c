#include <stdio.h>

// VOCABULARIO TABULEIRO:
#define TAMANHO_TABULEIRO  10
#define TAMANHO_NAVIO       3
#define NAVIO               3
#define AGUA                0
#define NAVIOS              4 // Quantidades de Navios no Tabuleiro


// VOCABULARIO DE DIREÇÕES:
#define ORIENTACAO_VERTICAL            'V'
#define ORIENTACAO_HORIZONTAL          'H'
#define ORIENTACAO_DIAGONAL_DIREITA    'D'
#define ORIENTACAO_DIAGONAL_ESQUERDA   'E'

// VOCABULARIO HABILIDADES
#define HABILIDADE_CONE                 'C'
#define HABILIDADE_OCTAEDRO             'O'
#define HABILIDADE_CRUZ                 'Z'

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
void TabuleiroPosicionar(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int pos_linha, int pos_coluna, char orientacao){

    /*
        Loop do navio, onde adiciona o posicionamento do navio na matriz tabuleiro.
    */
    for(int i = 0; i < TAMANHO_NAVIO; i++){

        switch(orientacao){
            case ORIENTACAO_VERTICAL:{
                // Incrementa o valor de i na posição da coluna
                tabuleiro[pos_linha+i][pos_coluna] = NAVIO;
                break;
            }

            case ORIENTACAO_HORIZONTAL:{
                // Incrementa o valor de i na posição da linha
                tabuleiro[pos_linha][pos_coluna+i] = NAVIO;   
                break; 
            } 

            case ORIENTACAO_DIAGONAL_ESQUERDA:{
                // Decrementa o valor de i da linha e incrementa valor da coluna
                tabuleiro[pos_linha-i][pos_coluna-i] = NAVIO;
                break;
            }

            case ORIENTACAO_DIAGONAL_DIREITA:{
                // Decrementa o valor de i da linha, e incrementa valor i da coluna  
                tabuleiro[pos_linha-i][pos_coluna+i] = NAVIO;
                break;
            }
        }       
    }

}


/*
    Função à seguir, verifica o posicionamento se pode-ser adicionado o navio no tabuleiro.

    Verificações:
    - se o Navio respeita o espaço do tabuleiro, que está definido na constante TAMANHO_TABULEIRO;
    - verifica se o navio não se sobrepoe outro navio já no tabuleiro.

    Retornos:
    - retorna 0: caso ele sobrepõe outro navio;
    - retorna -1; caso ele não respeita a dimensão do tabuleiro;
    - retorna 1: caso ele respeita a dimensão do tabuleiro e não sobrepõe outro navio;
*/
int VerificaPosicionamento(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int pos_linha, int pos_coluna, char orientacao){

    // Variável de controle e retorno da função.
    int status_posicao = 1;


    /* 
        Checagem simples da posição:
        Verifica se a posição linha e coluna não excedem o tabuleiro
    */
    if(pos_linha <= 0 || pos_linha >= TAMANHO_TABULEIRO || pos_coluna < 0 || pos_coluna > TAMANHO_TABULEIRO)
    {
        return -1;
    }


    /*
        Checagem para verificar se o barco formado, não excede o tabuleiro
        e também verifica se sobrepõe outro navio.
    */ 
    int NAVIO_MONTADO = (TAMANHO_NAVIO-1);

    for(int i = 0; i < TAMANHO_NAVIO && status_posicao == 1; i++){

        switch(orientacao){
            case ORIENTACAO_VERTICAL:{

                /*
                    Verificando se o navio formado, não excede o tabuleiro:
                    somando a linha + Tamanho do Navio.
                */ 
                status_posicao = (pos_linha+NAVIO_MONTADO >= TAMANHO_TABULEIRO) ? -1 : 1;

                // Verificando sobreposição
                if(status_posicao == 1){
                    status_posicao = (tabuleiro[pos_linha+i][pos_coluna] == NAVIO) ? 0 : 1;
                }
                break;
            }

            case ORIENTACAO_HORIZONTAL:{
                
                /*
                    Verificando se o navio formado, não excede o tabuleiro:
                    somando a coluna + Tamanho do Navio.
                */    
                status_posicao = (pos_coluna+NAVIO_MONTADO >= TAMANHO_TABULEIRO) ? -1 : 1;

                // Verificando sobreposição
                if(status_posicao == 1){
                    status_posicao = (tabuleiro[pos_linha][pos_coluna+i] == NAVIO) ? 0 : 1;
                }
                break; 
            } 

            case ORIENTACAO_DIAGONAL_ESQUERDA:{
                /*
                    Verificando se o navio formado, não excede o tabuleiro:
                    subtraindo a linha com o Tamanho do Navio e também
                    subtraindo a coluna com o tamanho do navio.
                */  
                status_posicao = (pos_linha-NAVIO_MONTADO < 0 || pos_coluna-NAVIO_MONTADO < 0) ? -1 : 1;

                // Verificando se o navio não sobrepõe outro
                if(status_posicao == 1){
                    status_posicao = (tabuleiro[pos_linha-i][pos_coluna-i] == NAVIO) ? 0 : 1;
                }
                break;
            }

            case ORIENTACAO_DIAGONAL_DIREITA:{
                /*
                    Verificando se o navio formado, não excede o tabuleiro:
                    subtraindo a linha com o Tamanho do Navio e também
                    somando a coluna com o tamanho do navio.
                */ 
                status_posicao = (0 > pos_linha-(NAVIO_MONTADO) || pos_coluna+(NAVIO_MONTADO) < 0) ? -1 : 1;

                // Verificando se o navio, não sobrepõe outro:
                if(status_posicao == 1){
                    status_posicao = (tabuleiro[pos_linha-i][pos_coluna+i] == NAVIO) ? 0 : 1;
                }
                break;
            }       
        } 
    }

    return status_posicao;
}


void Ataque(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], char ataque,int pos_linha, int pos_coluna){
    switch(ataque){
        case HABILIDADE_CONE:{

            for(int i = 0; i < 3; i++){
                tabuleiro[pos_linha+i][pos_coluna] = 5;

                if(i == 2){
                    for (int j = pos_linha-i; j >= 1; --j){
                        tabuleiro[pos_linha+i][pos_coluna+j] = 5;
                        tabuleiro[pos_linha+i][pos_coluna-j] = 5;
                    }
                }
                if(i == 1){
                    for (int j = pos_linha-3; j >= 1; --j){
                        tabuleiro[pos_linha+i][pos_coluna+j] = 5;
                        tabuleiro[pos_linha+i][pos_coluna-j] = 5;
                    }       
                }
            }
            break;
        }

        case HABILIDADE_CRUZ:{

            for(int i = -1; i < 3; i++){
                tabuleiro[pos_linha+i][pos_coluna] = 5;
            }
            for(int i = -2; i < 3; i++){
                tabuleiro[pos_linha][pos_coluna+i] = 5;
            }

            // tabuleiro[pos_linha][pos_coluna] = 1;
            break;
        }
        case HABILIDADE_OCTAEDRO:{
            for(int i = 0; i < 3; i++){
                tabuleiro[pos_linha+i][pos_coluna] = 5;

                if(i == 1){
                    for (int j = pos_linha-1; j > 1; --j){
                        tabuleiro[pos_linha+i][pos_coluna+1] = 5;
                        tabuleiro[pos_linha+i][pos_coluna-1] = 5;
                    }
                }
            }
            break;   
        }
    }
}


int main() {

    // Cria uma matriz, dois vetores com o tamanho de cada vetor especificado.
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Faz a inicialização do tabuleiro, colocando 0 em todos os vetores.
    Tabuleiro(tabuleiro, TABULEIRO_LIMPAR);


    // Inicializando variaveis de posicionamento:
    int navio[NAVIOS][3];

    /*
        NAVIO ID 0
        ORIENTAÇÃO VERTICAL
    */
    navio[0][0] = 2;
    navio[0][1] = 3;
    navio[0][2] = ORIENTACAO_VERTICAL;


    /*
        NAVIO ID 1
        ORIENTAÇÃO VERTICAL
    */
    navio[1][0] = 3;
    navio[1][1] = 6;
    navio[1][2] = ORIENTACAO_VERTICAL;


    /*
        NAVIO ID 2
        ORIENTAÇÃO DIAGONAL ESQUERDA
    */
    navio[2][0] = 9;
    navio[2][1] = 8;
    navio[2][2] = ORIENTACAO_DIAGONAL_ESQUERDA;


    /*
        NAVIO ID 3
        ORIENTAÇÃO DIAGONAL DIREITA
    */
    navio[3][0] = 9;
    navio[3][1] = 1;
    navio[3][2] = ORIENTACAO_DIAGONAL_DIREITA;

    // 

    printf("Bem vindo ao Tabuleiro, montando tabuleiro e navios!\n");
    for(int i = 0; i < NAVIOS; i++){

        int posicao_valida = VerificaPosicionamento(tabuleiro, navio[i][0], navio[i][1], navio[i][2]);

        if(posicao_valida == -1){
            printf("Erro ao montar navio id %d, não respeita as dimensões o tabulario\n", i);
        }
        if(posicao_valida == 0){
            printf("Erro ao montar navio id %d, este navio irá sobrepor outro já existente.\n", i);
        }
        else{
            TabuleiroPosicionar(tabuleiro, navio[i][0], navio[i][1], navio[i][2]);
        }
    }

    Tabuleiro(tabuleiro, TABULEIRO_EXIBIR);

    printf("Mostrar habilidades? (y/n)\nRe:");

    char mostrar_habilidades;
    scanf("%c", &mostrar_habilidades);

    if(mostrar_habilidades == 'y')

        printf("Limpando Tabulário...\n\n");
        Tabuleiro(tabuleiro, TABULEIRO_LIMPAR);

        Ataque(tabuleiro, HABILIDADE_CRUZ, 1, 5);  

        Ataque(tabuleiro, HABILIDADE_OCTAEDRO, 6, 1); 

        Ataque(tabuleiro, HABILIDADE_CONE, 4, 6); 

        Tabuleiro(tabuleiro, TABULEIRO_EXIBIR); 
    return 0;
}
