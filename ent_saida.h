#ifndef ENT_SAIDA_H_INCLUDED
#define ENT_SAIDA_H_INCLUDED
#define TAMANHO 15

// CADA ARQUIVO TERÁ SUA DOCUMENTAÇÃO EM SUA PÁGINA

/* COMENTÁRIOS E DOCUMENTAÇÃO "ENT_SAIDA.H" :
        * ENUM:
            - Foram criados 2 enums, todos typedef, onde em um contém o tamanho dos navios e em outro a quantidade deles a ser alocada.
            - Ambos são usados no arquivo "ent_saida.c"

        *STRUCT:
            - 3 structs foram criados, um deles regista o nome dos jogadores, para ser utilizado no arquivo "principal.c" e "ent_saida.c".
            Outro deles foi criado para resgistrar o campo, os espaços dos campos. O terceiro, resgistra as matrizes dos jogadores "1" e "2".

 */

typedef enum     // ENUMERA O TAMANHO DOS NAVIOS
{
    Submarino = 1,
    Corveta,
    Fragata,
    Porta_aviao

} Navios_tamanho;

typedef enum    // ENUMERA A QUANTIDADE LIMITE DISTRIBUIDA NO TABULEIRO
{
    Porta_aviao_quantidade = 1,
    Fragata_quantidade,
    Corveta_quantidade,
    Submarino_quantidade

} Navios_quantidade_limite;

struct Quadrado // REGISTRA OS ESPAÇOS DO CAMPO
{
    int valor;
};

struct Campo // REGISTRA OS TABULEIROS, JOGAGOR 1 E 2
{
    int matriz_jogador[TAMANHO][TAMANHO];
    int matriz_adv[TAMANHO][TAMANHO];
};

struct Players // Registra o nome dos jogadores
{
    char nome_1[100];
    char nome_2[100];
};

void inicializar_malha (int linhas, int tabuleiro_visualizado[linhas][linhas], char * nome);
void ent_saida(int *posicao_linha,int *posicao_coluna, int *direcao,int tabuleiro[TAMANHO][TAMANHO],char *nome, int modo_jogo);
int atirar (int tabuleiro_visualizado[TAMANHO][TAMANHO], int tabuleiro[TAMANHO][TAMANHO], int *posicao_linha_tiro, int *posicao_coluna_tiro,int vez_jogador, char *nome, int modo_jogo);
int verificar_vitoria (int linhas, int tabuleiro_visualizado[TAMANHO][TAMANHO], int vez_jogador, char *nome, int modo_jogo);


#endif // ENT_SAIDA_H_INCLUDED
