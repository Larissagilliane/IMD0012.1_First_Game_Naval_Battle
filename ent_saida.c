#include <stdio.h>
#include<stdlib.h>
#include <time.h>
#include <locale.h>
#include <conio.h>
#include <windows.h>
#include "ent_saida.h"

/*
    POSICAO LESTE E OESTE PODEM PARECER INVERTIDAS, MAS SIGNIFICA QUE EST� DE ACORDO COM O POSICIONAMENTO DO TABULEIRO
*/


// CADA ARQUIVO TER� SUA DOCUMENTA��O EM SUA P�GINA

/* COMENT�RIOS E DOCUMENTA��O "ENT_SAIDA.C" ( fun��es explicadas por ordem que aparecem no c�digo ) :
        * verificar_vit�ria :
            - A fun��o recebe as linhas, o tabuleiro com os tiros, a vez do jogador, o nome do jogador da vez e a variavel modo_jogo (informa se �
            computador ou humano).
            - Nela � percorrida toda a matriz tabuleiro, e � somado cada tiro acertado, caso os tiros sejas equivalentes a 20, ele informa quem � o vencedor
            informando seu nome e qual jogador � "1" ou "2"(de acordo com o vez_jogador).

        * alocar_navios :
            - A fun��o recebe, linhas, tabuleiro com os navios, as posi��es linha e coluna, o tipo de navio, sua dire��o e uma variavel que serve como
            boleana e informa se deve somar ou nao ao loop.
            - Nele o jogo confere para cada navio os requisitos para alocar, primeiro � verificado se j� h� navios nessa posi��o recebida, depois ele testa se
            n�o h� navios em sua volta.
            - Testa a dire��o se � v�lida, caso n�o haja impedimento ele aloca os navios de acordo com a dire��o somando ou subtraindo linhas e colunas.

        * imprimir_malha :
            - Nessa fun��o a legenda � exibida, e logo ap�s o tabuleiro com os navios ou com os tiros, depende do tabuleiro enviado.

        *inicializar_malha :
            - Aqui o jogo � "zerado", exibindo apenas �gua, � usado no main para inicializar a matriz.

        *atirar:
            - Na fun��o atirar al�m dos parametros de modo jogo etc, s�o passados os 2 tabuleiros o com os tiros e outro com os navios, a l�gica da fun��o
            consiste em ler o tiro desejado caso seja humano, sortear caso seja computador, conferir se o tiro � valido, e ap�s isso atirar. Se no tabuleiro
            com navios houver navio naquela posi��o, um 'X' � colocado  no tabuleiro com os tiros, se n�o houver navios um '-' � inserido.

        *ent_saida:
            - A fun��o ent_saida pergunta ao usuario onde ele deseja alocar os navios, caso seja um humano ele digita os valores, se for computador ele sorteia.
            Ele confere se a posi��o � v�lida e a dire��o tamb�m (se est� dentro do campo os valores digitados), caso estejam certos ele chama a fun��o de alocar
            e acrescenta um ao contador "i", para que o la�o percorra a quantidade de cada navio. Se for humano ele exibe o tabuleiro alocado ( da fun��o
            imprimir_tabuleiro), caso seja computador ele apenas exibe a mensagem alocando.

 */

int verificar_vitoria (int linhas, int tabuleiro_visualizado[TAMANHO][TAMANHO], int vez_jogador, char *nome, int modo_jogo) // VERIFICA QUEM GANHA
{
    int i, j, cont=0; // CONTADORES
    for(i=0; i<linhas; i++) //LINHAS
    {
        for(j=0; j<linhas; j++) // COLUNAS
        {
            if (tabuleiro_visualizado[i][j] == 'X') // PERCORRE O TABULEIRO ONDE EST�O OS TIROS
            {
                cont++; // SOMA A QUANTIDADE DE TIROS ACERTADOS
            }
        }
    }
    if (cont == 1) // COFERE SE OS TIROS EQUIVALEM A 20, CASO SIM O JOGADOR GANHA
    {
        if (modo_jogo==2) //NA VERS�O HUMANO VS HUMANO, ELE EXIBE O JOGADOR QUE GANHOU E O SEU NOME
        {
            system("COLOR 06");
            printf("              VOC� VENCEU %s !!! \n", nome ,setlocale(LC_ALL,"")); // EXIBE O NOME DO JOAGOR QUE VENCEU
            printf("              PARAB�NS JOGADOR %d !!! \n", vez_jogador); // PEGA O NUMERO DA VEZ DO JOGADOR, QUE EQUIVALE A JOGADOR '1' OU '2'
            Sleep(2000);

            return vez_jogador; // RETORNA QUAL JOGADOR GANHOU PARA QUE SAIA DO LA�O NO ARQUIVO PRINCIPAL
        }
        else if (modo_jogo==3) // CASO SEJA HUMANO VS COMPUTADOR ELE EXIBE O APELIDO DADO AO COMPUTADOR
        {
            system("COLOR 06");
            printf("          COMPUTADOR %s GANHOU !!! \n", nome);
            printf("          VOC� PERDEU JOGADOR 1!!! \n");
            return vez_jogador; // RETORNA O VEZ JOGADOR, PARA INFORMAR QUEM GANHOU
        }
    }
    else // CASO NINGUEM GANHE, A MENSAGEM CONTINUE ATIRANDO, � EXIBIDA
    {
        system("COLOR F9");
        printf("CONTINUE ATIRANDO %s \n", nome);
        return 0;
    }
}

int alocar_navios(int linhas, int tabuleiro[TAMANHO][TAMANHO], int *posicao_linha, int *posicao_coluna, int tipo , int *direcao, int variavel) // FUN��O QUE ALOCA OS NAVIOS, E RECEBE DADOS DA FUN��O "ENT_SAIDA"
{

    if (tipo == Submarino) // NAVIO: SUBMARINO
    {
        if (tabuleiro[*posicao_linha][*posicao_coluna] == '1') // VERIFICA SE J� H� NAVIOS NA POSI��O
        {
            system("COLOR F4"); // COLOCA EM VERMELHO A FONTE, REMETENDO A ERRO
            printf("\n J� H� UM NAVIO NESSAS POSI��ES, TENTE OUTRO VALOR \n");
            Sleep(2000); // PAUSA DE 2 SEGUNDOS
            variavel = 0; //TESTA PARA CONTINUAR NO LOOP, E NAO CONTAR COMO ALOCADO
        }
        else if (tabuleiro[*posicao_linha-1][*posicao_coluna] == '1' || tabuleiro[*posicao_linha+1][*posicao_coluna] == '1' || tabuleiro[*posicao_linha][*posicao_coluna-1] == '1' || tabuleiro[*posicao_linha][*posicao_coluna+1] == '1')
        {
            // VERIFICA SE H� NAVIOS NAS REDONDEZAS
            system("COLOR F4");
            printf("\n VOC� N�O PODE ALOCAR AQUI, H� NAVIOS PR�XIMOS \n");
            Sleep(2000);
            variavel = 0;  //TESTA PARA CONTINUAR NO LOOP, E NAO CONTAR COMO ALOCADO
        }
        else // ALOCA OS NAVIOS
        {
            tabuleiro[*posicao_linha][*posicao_coluna] = '1';
            variavel=1; // TESTA PARA ALOCAR E CONTAR MAIS 1 NO LOOP
        }
    }
    else if (tipo == Corveta) //NAVIO: CORVETA
    {
        switch(*direcao) // ESCOLHE A DIRA��O
        {
        case 1: // PARA NORTE
            if (tabuleiro[*posicao_linha][*posicao_coluna] == '1'|| tabuleiro[*posicao_linha-1][*posicao_coluna] == '1')
            {
                // VERIFICA SE J� H� NAVIOS NA POSI��O
                system("COLOR F4");
                printf("\n J� H� UM NAVIO NESSAS POSI��ES, TENTE OUTRO VALOR\n");
                Sleep(2000);
                variavel = 0;  //TESTA PARA CONTINUAR NO LOOP, E NAO CONTAR COMO ALOCADO
            }
            else if (tabuleiro[*posicao_linha+1][*posicao_coluna] == '1' || tabuleiro[*posicao_linha-2][*posicao_coluna] == '1' || tabuleiro[*posicao_linha][*posicao_coluna-1] == '1' || tabuleiro[*posicao_linha][*posicao_coluna+1] == '1' || tabuleiro[*posicao_linha-1][*posicao_coluna+1] == '1'|| tabuleiro[*posicao_linha-1][*posicao_coluna-1] == '1')
            {
                // VERIFICA SE H� NAVIOS NAS REDONDEZAS, SUBTRAINDO E SOMANDO AS LINHAS E COLUNAS DE ACORDO COM A DIRE��O
                system("COLOR F4");
                printf("\n VOC� N�O PODE ALOCAR AQUI, H� NAVIOS PR�XIMOS  \n");
                Sleep(2000);
                variavel = 0;  //TESTA PARA CONTINUAR NO LOOP, E NAO CONTAR COMO ALOCADO
            }
            else if (*posicao_linha-1 >= 0) // ALOCA OS NAVIOS
            {
                tabuleiro[*posicao_linha][*posicao_coluna] = '1';
                tabuleiro[*posicao_linha-1][*posicao_coluna] = '1';
                variavel = 1; // TESTA PARA ALOCAR E CONTAR MAIS 1 NO LOOP
            }
            else
            {
                // CASO A DIRE��O SEJA INVALIDA ESSE AVISO SER� EXIBIDO
                system("COLOR F4");
                printf("\n DIRE��O INV�LIDA, EST� FORA DO CAMPO \n");
                Sleep(2000);
                variavel = 0;  //TESTA PARA CONTINUAR NO LOOP, E N�O CONTAR COMO ALOCADO
            }
            break;
        case 2: //PARA SUL

            /* AS OPEAR��ES SEGUINTES SAO AS MESMAS DA DIRE��O NORTE ALTERANDO APENAS A FOMAR COMO CONFERE E ALOCA,
             SEGUINDO A DIRE��O ESCOLHIDA  */
            if (tabuleiro[*posicao_linha][*posicao_coluna] == '1'|| tabuleiro[*posicao_linha+1][*posicao_coluna] == '1')
            {
                system("COLOR F4");
                printf("\n J� H� UM NAVIO NESSAS POSI��ES, TENTE OUTRO VALOR\n");
                Sleep(2000);
                variavel = 0;
            }
            else if (tabuleiro[*posicao_linha-1][*posicao_coluna] == '1' || tabuleiro[*posicao_linha+2][*posicao_coluna] == '1' || tabuleiro[*posicao_linha][*posicao_coluna-1] == '1' || tabuleiro[*posicao_linha][*posicao_coluna+1] == '1' || tabuleiro[*posicao_linha+1][*posicao_coluna+1] == '1'|| tabuleiro[*posicao_linha+1][*posicao_coluna-1] == '1')
            {
                system("COLOR F4");
                printf("\n VOC� N�O PODE ALOCAR AQUI, H� NAVIOS PR�XIMOS  \n");
                Sleep(2000);
                variavel = 0;
            }
            else if (*posicao_linha+1<= 14)
            {
                tabuleiro[*posicao_linha][*posicao_coluna] = '1';
                tabuleiro[*posicao_linha+1][*posicao_coluna] = '1';
                variavel = 1;
            }
            else
            {
                system("COLOR F4");
                printf("\n DIRE��O INV�LIDA, EST� FORA DO CAMPO \n");
                Sleep(2000);
                variavel = 0;
            }
            break;
        case 3: //PARA  LESTE
            /* AS OPEAR��ES SEGUINTES SAO AS MESMAS DA DIRE��O NORTE ALTERANDO APENAS A FOMAR COMO CONFERE E ALOCA,
             SEGUINDO A DIRE��O ESCOLHIDA  */
            if (tabuleiro[*posicao_linha][*posicao_coluna] == '1'|| tabuleiro[*posicao_linha][*posicao_coluna-1] == '1')
            {
                system("COLOR F4");
                printf("\n J� H� UM NAVIO NESSAS POSI��ES, TENTE OUTRO VALOR\n");
                Sleep(2000);
                variavel = 0;
            }
            else if (tabuleiro[*posicao_linha-1][*posicao_coluna] == '1' || tabuleiro[*posicao_linha+1][*posicao_coluna] == '1' || tabuleiro[*posicao_linha][*posicao_coluna+1] == '1' || tabuleiro[*posicao_linha][*posicao_coluna-2] == '1' || tabuleiro[*posicao_linha+1][*posicao_coluna-1] == '1'|| tabuleiro[*posicao_linha-1][*posicao_coluna-1] == '1')
            {
                system("COLOR F4");
                printf("\n VOC� N�O PODE ALOCAR AQUI, H� NAVIOS PR�XIMOS  \n");
                Sleep(2000);
                variavel = 0;
            }
            else if (*posicao_coluna-1 >=0)
            {
                tabuleiro[*posicao_linha][*posicao_coluna] = '1';
                tabuleiro[*posicao_linha][*posicao_coluna-1] = '1';
                variavel = 1;
            }
            else
            {
                system("COLOR F4");
                printf("\n DIRE��O INV�LIDA, EST� FORA DO CAMPO \n");
                Sleep(2000);
                variavel = 0;
            }
            break;
        case 4: // PARA OESTE
            /* AS OPEAR��ES SEGUINTES SAO AS MESMAS DA DIRE��O NORTE ALTERANDO APENAS A FOMAR COMO CONFERE E ALOCA,
             SEGUINDO A DIRE��O ESCOLHIDA  */
            if (tabuleiro[*posicao_linha][*posicao_coluna] == '1'|| tabuleiro[*posicao_linha][*posicao_coluna+1] == '1')
            {
                system("COLOR F4");
                printf("\n J� H� UM NAVIO NESSAS POSI��ES, TENTE OUTRO VALOR\n");
                Sleep(2000);
                variavel = 0;
            }
            else if (tabuleiro[*posicao_linha-1][*posicao_coluna] == '1' || tabuleiro[*posicao_linha+1][*posicao_coluna] == '1' || tabuleiro[*posicao_linha][*posicao_coluna-1] == '1' || tabuleiro[*posicao_linha][*posicao_coluna+2] == '1' || tabuleiro[*posicao_linha+1][*posicao_coluna+1] == '1'|| tabuleiro[*posicao_linha-1][*posicao_coluna+1] == '1')
            {
                system("COLOR F4");
                printf("\n VOC� N�O PODE ALOCAR AQUI, H� NAVIOS PR�XIMOS  \n");
                Sleep(2000);
                variavel = 0;
            }
            else if (*posicao_coluna+1 <=14)
            {
                tabuleiro[*posicao_linha][*posicao_coluna] = '1';
                tabuleiro[*posicao_linha][*posicao_coluna+1] = '1';
                variavel = 1;
            }
            else
            {
                system("COLOR F4");
                printf("\n DIRE��O INV�LIDA, EST� FORA DO CAMPO \n");
                Sleep(2000);
                variavel = 0;
            }
            break;
        }
    }

    else if (tipo == Fragata) // NAVIO FRAGATA
        /* AS SEGUINTES OPERA��ES S�O AS MESMAS DO NAVIO ANTERIOR ALTERANDO SOMENTE A QUANTIDADE DE CASAS ALOCADAS  */
    {
        switch(*direcao)
        {
        case 1:
            if (tabuleiro[*posicao_linha][*posicao_coluna] == '1'|| tabuleiro[*posicao_linha-1][*posicao_coluna] == '1' || tabuleiro[*posicao_linha-2][*posicao_coluna] == '1')
            {
                system("COLOR F4");
                printf("\n J� H� UM NAVIO NESSAS POSI��ES, TENTE OUTRO VALOR \n");
                Sleep(2000);
                variavel = 0;
            }
            else if (tabuleiro[*posicao_linha+1][*posicao_coluna] == '1' || tabuleiro[*posicao_linha-3][*posicao_coluna] == '1' || tabuleiro[*posicao_linha][*posicao_coluna-1] == '1' || tabuleiro[*posicao_linha][*posicao_coluna+1] == '1' || tabuleiro[*posicao_linha-1][*posicao_coluna+1] == '1'||
                     tabuleiro[*posicao_linha-1][*posicao_coluna-1] == '1'|| tabuleiro[*posicao_linha-2][*posicao_coluna-1] == '1' || tabuleiro[*posicao_linha-2][*posicao_coluna+1] == '1')
            {
                system("COLOR F4");
                printf("\n VOC� N�O PODE ALOCAR AQUI, H� NAVIOS PR�XIMOS  \n");
                Sleep(2000);
                variavel = 0;
            }
            else if (*posicao_linha-2 >= 0)
            {
                tabuleiro[*posicao_linha][*posicao_coluna] = '1';
                tabuleiro[*posicao_linha-1][*posicao_coluna] = '1';
                tabuleiro[*posicao_linha-2][*posicao_coluna] = '1';
                variavel = 1;
            }
            else
            {
                system("COLOR F4");
                printf("\n DIRE��O INV�LIDA, EST� FORA DO CAMPO \n");
                Sleep(2000);
                variavel = 0;
            }
            break;
        case 2:
            if (tabuleiro[*posicao_linha][*posicao_coluna] == '1'|| tabuleiro[*posicao_linha+1][*posicao_coluna] == '1' || tabuleiro[*posicao_linha+2][*posicao_coluna] == '1')
            {
                system("COLOR F4");
                printf("\n J� H� UM NAVIO NESSAS POSI��ES, TENTE OUTRO VALOR \n");
                Sleep(2000);
                variavel = 0;
            }
            else if (tabuleiro[*posicao_linha-1][*posicao_coluna] == '1' || tabuleiro[*posicao_linha+3][*posicao_coluna] == '1' || tabuleiro[*posicao_linha][*posicao_coluna-1] == '1' || tabuleiro[*posicao_linha][*posicao_coluna+1] == '1' || tabuleiro[*posicao_linha+1][*posicao_coluna+1] == '1'||
                     tabuleiro[*posicao_linha+1][*posicao_coluna-1] == '1'|| tabuleiro[*posicao_linha+2][*posicao_coluna-1] == '1' || tabuleiro[*posicao_linha+2][*posicao_coluna+1] == '1')
            {
                system("COLOR F4");
                printf("\n VOC� N�O PODE ALOCAR AQUI, H� NAVIOS PR�XIMOS  \n");
                Sleep(2000);
                variavel = 0;
            }
            else if (*posicao_linha+2 <= 14)
            {
                tabuleiro[*posicao_linha][*posicao_coluna] = '1';
                tabuleiro[*posicao_linha+1][*posicao_coluna] = '1';
                tabuleiro[*posicao_linha+2][*posicao_coluna] = '1';
                variavel = 1;
            }
            else
            {
                system("COLOR F4");
                printf("\n DIRE��O INV�LIDA, EST� FORA DO CAMPO \n");
                Sleep(2000);
                variavel = 0;
            }
            break;
        case 3:
            if (tabuleiro[*posicao_linha][*posicao_coluna] == '1'|| tabuleiro[*posicao_linha][*posicao_coluna-1] == '1' || tabuleiro[*posicao_linha][*posicao_coluna-2] == '1')
            {
                system("COLOR F4");
                printf("\n J� H� UM NAVIO NESSAS POSI��ES, TENTE OUTRO VALOR \n");
                Sleep(2000);
                variavel = 0;
            }
            else if (tabuleiro[*posicao_linha][*posicao_coluna+1] == '1' || tabuleiro[*posicao_linha][*posicao_coluna-3] == '1' || tabuleiro[*posicao_linha-1][*posicao_coluna] == '1' || tabuleiro[*posicao_linha+1][*posicao_coluna] == '1' || tabuleiro[*posicao_linha-1][*posicao_coluna-1] == '1'||
                     tabuleiro[*posicao_linha+1][*posicao_coluna-1] == '1'|| tabuleiro[*posicao_linha-1][*posicao_coluna-2] == '1' || tabuleiro[*posicao_linha+1][*posicao_coluna-2] == '1')
            {
                system("COLOR F4");
                printf("\n VOC� N�O PODE ALOCAR AQUI, H� NAVIOS PR�XIMOS  \n");
                Sleep(2000);
                variavel = 0;
            }
            else if (*posicao_coluna-2 >= 0)
            {
                tabuleiro[*posicao_linha][*posicao_coluna] = '1';
                tabuleiro[*posicao_linha][*posicao_coluna-1] = '1';
                tabuleiro[*posicao_linha][*posicao_coluna-2] = '1';
                variavel = 1;
            }
            else
            {
                system("COLOR F4");
                printf("\n DIRE��O INV�LIDA, EST� FORA DO CAMPO \n");
                Sleep(2000);
                variavel = 0;
            }
            break;
        case 4:
            if (tabuleiro[*posicao_linha][*posicao_coluna] == '1'|| tabuleiro[*posicao_linha][*posicao_coluna+1] == '1' || tabuleiro[*posicao_linha][*posicao_coluna+2] == '1')
            {
                printf("\n J� H� UM NAVIO NESSAS POSI��ES, TENTE OUTRO VALOR \n");
                Sleep(2000);
                variavel = 0;
            }
            else if (tabuleiro[*posicao_linha][*posicao_coluna-1] == '1' || tabuleiro[*posicao_linha][*posicao_coluna+3] == '1' || tabuleiro[*posicao_linha-1][*posicao_coluna] == '1' || tabuleiro[*posicao_linha+1][*posicao_coluna] == '1' || tabuleiro[*posicao_linha-1][*posicao_coluna+1] == '1'||
                     tabuleiro[*posicao_linha+1][*posicao_coluna+1] == '1'|| tabuleiro[*posicao_linha-1][*posicao_coluna+2] == '1' || tabuleiro[*posicao_linha+1][*posicao_coluna+2] == '1')
            {
                system("COLOR F4");
                printf("\n VOC� N�O PODE ALOCAR AQUI, H� NAVIOS PR�XIMOS  \n");
                Sleep(2000);
                variavel = 0;
            }
            else if (*posicao_coluna+2 <= 14)
            {
                tabuleiro[*posicao_linha][*posicao_coluna] = '1';
                tabuleiro[*posicao_linha][*posicao_coluna+1] = '1';
                tabuleiro[*posicao_linha][*posicao_coluna+2] = '1';
                variavel = 1;
            }
            else
            {
                system("COLOR F4");
                printf("\n DIRE��O INV�LIDA, EST� FORA DO CAMPO \n");
                Sleep(2000);
                variavel = 0;
            }

            break;
        }
    }
    else if (tipo == Porta_aviao) // NAVIO: PORTA AVI�O
    {
        /* AS SEGUINTES OPERA��ES S�O AS MESMAS DO NAVIO ANTERIOR ALTERANDO SOMENTE A QUANTIDADE DE CASAS ALOCADAS  */
        switch(*direcao)
        {
        case 1:
            if (tabuleiro[*posicao_linha][*posicao_coluna] == '1'|| tabuleiro[*posicao_linha-1][*posicao_coluna] == '1' || tabuleiro[*posicao_linha-2][*posicao_coluna] == '1' || tabuleiro[*posicao_linha-3][*posicao_coluna] == '1')
            {
                system("COLOR F4");
                printf("\n J� H� UM NAVIO NESSAS POSI��ES, TENTE OUTRO VALOR \n");
                Sleep(2000);
                variavel = 0;
            }
            else if (tabuleiro[*posicao_linha+1][*posicao_coluna] == '1' || tabuleiro[*posicao_linha-4][*posicao_coluna] == '1' || tabuleiro[*posicao_linha][*posicao_coluna-1] == '1' || tabuleiro[*posicao_linha][*posicao_coluna+1] == '1' || tabuleiro[*posicao_linha-1][*posicao_coluna-1] == '1'||
                     tabuleiro[*posicao_linha-1][*posicao_coluna+1] == '1'|| tabuleiro[*posicao_linha-2][*posicao_coluna-1] == '1' || tabuleiro[*posicao_linha-2][*posicao_coluna+1] == '1'|| tabuleiro[*posicao_linha-3][*posicao_coluna+1] == '1' || tabuleiro[*posicao_linha-3][*posicao_coluna-1] == '1')
            {
                system("COLOR F4");
                printf("\n VOC� N�O PODE ALOCAR AQUI, H� NAVIOS PR�XIMOS  \n");
                Sleep(2000);
                variavel = 0;
            }
            else if (*posicao_linha-3 >= 0)
            {
                tabuleiro[*posicao_linha][*posicao_coluna] = '1';
                tabuleiro[*posicao_linha-1][*posicao_coluna] = '1';
                tabuleiro[*posicao_linha-2][*posicao_coluna] = '1';
                tabuleiro[*posicao_linha-3][*posicao_coluna] = '1';
                variavel = 1;
            }
            else
            {
                system("COLOR F4");
                printf("\n DIRE��O INV�LIDA, EST� FORA DO CAMPO \n");
                Sleep(2000);
                variavel = 0;
            }

            break;
        case 2:
            if (tabuleiro[*posicao_linha][*posicao_coluna] == '1'|| tabuleiro[*posicao_linha+1][*posicao_coluna] == '1' || tabuleiro[*posicao_linha+2][*posicao_coluna] == '1' || tabuleiro[*posicao_linha+3][*posicao_coluna] == '1')
            {
                system("COLOR F4");
                printf("\n J� H� UM NAVIO NESSAS POSI��ES, TENTE OUTRO VALOR \n");
                Sleep(2000);
                variavel = 0;
            }
            else if (tabuleiro[*posicao_linha-1][*posicao_coluna] == '1' || tabuleiro[*posicao_linha+4][*posicao_coluna] == '1' || tabuleiro[*posicao_linha][*posicao_coluna-1] == '1' || tabuleiro[*posicao_linha][*posicao_coluna+1] == '1' || tabuleiro[*posicao_linha+1][*posicao_coluna-1] == '1'||
                     tabuleiro[*posicao_linha+1][*posicao_coluna+1] == '1'|| tabuleiro[*posicao_linha+2][*posicao_coluna-1] == '1' || tabuleiro[*posicao_linha+2][*posicao_coluna+1] == '1'|| tabuleiro[*posicao_linha+3][*posicao_coluna+1] == '1' || tabuleiro[*posicao_linha+3][*posicao_coluna-1] == '1')
            {
                system("COLOR F4");
                printf("\n VOC� N�O PODE ALOCAR AQUI, H� NAVIOS PR�XIMOS  \n");
                Sleep(2000);
                variavel = 0;
            }
            else if (*posicao_linha+3 <= 14)
            {
                tabuleiro[*posicao_linha][*posicao_coluna] = '1';
                tabuleiro[*posicao_linha+1][*posicao_coluna] = '1';
                tabuleiro[*posicao_linha+2][*posicao_coluna] = '1';
                tabuleiro[*posicao_linha+3][*posicao_coluna] = '1';
                variavel = 1;
            }
            else
            {
                system("COLOR F4");
                printf("\n J� H� UM NAVIO NESSAS POSI��ES, TENTE OUTRO VALOR \n");
                Sleep(2000);
                variavel = 0;
            }

            break;
        case 3:
            if (tabuleiro[*posicao_linha][*posicao_coluna] == '1'|| tabuleiro[*posicao_linha][*posicao_coluna-1] == '1' || tabuleiro[*posicao_linha][*posicao_coluna-2] == '1' || tabuleiro[*posicao_linha][*posicao_coluna-3] == '1')
            {
                system("COLOR F4");
                printf("\n J� H� UM NAVIO NESSAS POSI��ES, TENTE OUTRO VALOR \n");
                Sleep(2000);
                variavel = 0;
            }
            else if (tabuleiro[*posicao_linha][*posicao_coluna+1] == '1' || tabuleiro[*posicao_linha][*posicao_coluna-4] == '1' || tabuleiro[*posicao_linha-1][*posicao_coluna] == '1' || tabuleiro[*posicao_linha+1][*posicao_coluna] == '1' || tabuleiro[*posicao_linha-1][*posicao_coluna-1] == '1'||
                     tabuleiro[*posicao_linha+1][*posicao_coluna-1] == '1'|| tabuleiro[*posicao_linha-1][*posicao_coluna-2] == '1' || tabuleiro[*posicao_linha+1][*posicao_coluna-2] == '1'|| tabuleiro[*posicao_linha+1][*posicao_coluna-3] == '1' || tabuleiro[*posicao_linha-1][*posicao_coluna-3] == '1')
            {
                system("COLOR F4");
                printf("\n VOC� N�O PODE ALOCAR AQUI, H� NAVIOS PR�XIMOS  \n");
                Sleep(2000);
                variavel = 0;
            }
            else if (*posicao_coluna-3 >= 0)
            {
                tabuleiro[*posicao_linha][*posicao_coluna] = '1';
                tabuleiro[*posicao_linha][*posicao_coluna-1] = '1';
                tabuleiro[*posicao_linha][*posicao_coluna-2] = '1';
                tabuleiro[*posicao_linha][*posicao_coluna-3] = '1';
                variavel = 1;
            }
            else
            {
                system("COLOR F4");
                printf("\n DIRE��O INV�LIDA, EST� FORA DO CAMPO \n");
                Sleep(2000);
                variavel = 0;
            }

            break;
        case 4:
            if (tabuleiro[*posicao_linha][*posicao_coluna] == '1'|| tabuleiro[*posicao_linha][*posicao_coluna+1] == '1' || tabuleiro[*posicao_linha][*posicao_coluna+2] == '1' || tabuleiro[*posicao_linha][*posicao_coluna+3] == '1')
            {
                system("COLOR F4");
                printf("\n J� H� UM NAVIO NESSAS POSI��ES, TENTE OUTRO VALOR \n");
                Sleep(2000);
                variavel = 0;
            }
            else if (tabuleiro[*posicao_linha][*posicao_coluna-1] == '1' || tabuleiro[*posicao_linha][*posicao_coluna+4] == '1' || tabuleiro[*posicao_linha-1][*posicao_coluna] == '1' || tabuleiro[*posicao_linha+1][*posicao_coluna] == '1' || tabuleiro[*posicao_linha-1][*posicao_coluna+1] == '1'||
                     tabuleiro[*posicao_linha+1][*posicao_coluna+1] == '1'|| tabuleiro[*posicao_linha-1][*posicao_coluna+2] == '1' || tabuleiro[*posicao_linha+1][*posicao_coluna+2] == '1'|| tabuleiro[*posicao_linha+1][*posicao_coluna+3] == '1' || tabuleiro[*posicao_linha-1][*posicao_coluna+3] == '1')
            {
                system("COLOR F4");
                printf("\n VOC� N�O PODE ALOCAR AQUI, H� NAVIOS PR�XIMOS  \n");
                Sleep(2000);
                variavel = 0;
            }
            else if (*posicao_coluna+3 <= 14)
            {
                tabuleiro[*posicao_linha][*posicao_coluna] = '1';
                tabuleiro[*posicao_linha][*posicao_coluna+1] = '1';
                tabuleiro[*posicao_linha][*posicao_coluna+2] = '1';
                tabuleiro[*posicao_linha][*posicao_coluna+3] = '1';
                variavel = 1;
            }
            else
            {
                system("COLOR F4");
                printf("\n DIRE��O INV�LIDA, EST� FORA DO CAMPO \n");
                Sleep(2000);
                variavel = 0;
            }

            break;
        }
    }

    return variavel;
}

void imprimir_malha (int linhas, int tabuleiro[linhas][linhas], char *nome) // IMPRIME O TABULEIRO, OS PARAMETROS SAO AS LINHAS, O TABULEIRO, E O NOME DO JOGADOR
{
    int i, j; //CONTADORES
    system("COLOR F9"); // COR DE FUNDO BRANCA, E FONTE AZUL.
    printf (" VEZ DE %s: \n", nome); // NOME DO JOGADOR DA VEZ
    printf (" 0 <-> �GUA\n");  // LEGENDA
    printf (" 1 <-> NAVIO \n");
    printf (" X <-> NAVIO ATINGIDO \n");
    printf (" - <-> TIRO NA �GUA \n");
    printf ("\n");

    printf ("    0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 \n\n"); // NUMERA��O DAS  COLUNAS
    for(i=0; i<linhas; i++)
    {
        if(i < 10) // NUMERA��O DAS LINHAS
            printf ("%d   ", i);
        else
            printf ("%d  ", i);
        for(j=0; j<linhas; j++)
        {
            printf ("%c  ", tabuleiro[i][j]); // IMPRIME O TABULEIRO DESEJADO, OU COM NAVIOS OU COM TIROS
        }
        printf ("\n");
    }
}

void inicializar_malha (int linhas, int tabuleiro_visualizado[linhas][linhas], char * nome) // INICIALIZA O TABULEIRO
{
    int i, j;

    for(i=0; i<linhas; i++) //LINHAS
    {
        for(j=0; j<linhas; j++) //COLUNAS
        {
            tabuleiro_visualizado[i][j]='0'; //COLOCA COMO '0' PARA INDICAR A �GUA
        }
    }
}


int atirar (int tabuleiro_visualizado[TAMANHO][TAMANHO], int tabuleiro[TAMANHO][TAMANHO], int *posicao_linha_tiro, int *posicao_coluna_tiro,int vez_jogador, char *nome, int modo_jogo)
{
    // FUN��O RESPONSAVEL PARA ATIRAR, ONDE L� AS COORDENADAS DO TIRO, RECEBE A VEZ DO JOGADOR E O SEU NOME, E O MODO DO JOGO
    if (modo_jogo==2) //CASO SEJA HUMANO VS HUMANO
    {
        system("COLOR F9");
        printf ("\n ATAQUE SEU OPONENTE ! \n");
        printf("\n QUAIS AS COORDENADAS DO TIRO (linha e coluna) ?\n");
        scanf("%d %d", posicao_linha_tiro, posicao_coluna_tiro); // L� AS POSI��ES DOS TIROS
        printf ("\n");
    }
    else if (modo_jogo==3) // CASO SEJA HUMANO VS COMPUTADOR
    {

        Sleep(1000); //TEM INTERVALOR DE 1 SEGUNDO DE DIFEREN�A, PARA QUE OS N�MEROS SORTEADOS PO�AM SER DIFERENTES
        srand((unsigned)time(NULL)); //SEMENTE QUE SORTEIA
        *posicao_linha_tiro=rand()%15; // SORTEIA N�MERO DE 0 A 15
        Sleep(1000); // INTERVALO DE 1 SEGUNDO

        srand((unsigned)time(NULL));
        *posicao_coluna_tiro=rand()%15;
        printf ("\n %d \n %d \n\n",*posicao_linha_tiro, *posicao_coluna_tiro); //EXIBE OS TIROS DADOS, LINHA E COLUNA
        //  printf ("\n Time(NULL) = %d \n\n",(unsigned)time(NULL));
        Sleep(1000);
    }
    if (*posicao_linha_tiro >= 15 || *posicao_linha_tiro < 0 || *posicao_coluna_tiro >=15 || *posicao_coluna_tiro < 0)
    {
        // CONFERE SE O VALOR DIGITADOR EST� DENTRO DO CAMPO
        system("COLOR F4"); //FONTE VERMELHA
        printf ("\n TIRO INV�LIDO \n\n");
        Sleep(2000);
        system("cls");
    }
    else if (tabuleiro[*posicao_linha_tiro][*posicao_coluna_tiro] == '1' && tabuleiro_visualizado[*posicao_linha_tiro][*posicao_coluna_tiro] == '0' )
    {
        // CONFERE SE H� NAVIOS ALOCADOS NO TABULEIRO, CASO SIM ELE MARCA COM UM 'X' , NO TABULEIRO_VISUALIZADO

        tabuleiro_visualizado[*posicao_linha_tiro][*posicao_coluna_tiro]='X'; //MARCA COM UM 'X'
        imprimir_malha(TAMANHO,tabuleiro_visualizado,nome); //IMPRIME TABULEIRO COM O TIRO DADO
        system("COLOR F2"); // COR VERDE DA FONTE
        printf( "\n\n ACERTOU ! \n\n");
        Sleep(2000);
        system("cls"); //LIMPA A TELA
        return vez_jogador; //RETORNA A VEZ DO JOGADOR PARA CONTINUAR NO LOOP E ELE JOGAR NOVAMENTE
    }
    else if (tabuleiro[*posicao_linha_tiro][*posicao_coluna_tiro] == '0' && tabuleiro_visualizado[*posicao_linha_tiro][*posicao_coluna_tiro] == '0' )
    {
        // CASO N�O TENHA NAVIO ALOCADO NO TABULEIRO, ELES MARCA COM UM '-' NO TABULEIRO VISUALIZADO

        tabuleiro_visualizado[*posicao_linha_tiro][*posicao_coluna_tiro]='-'; //MARCA COM UM '-'
        imprimir_malha(TAMANHO,tabuleiro_visualizado,nome); // EXIBE COM O TIRO DADO
        system("COLOR F4"); // COR DA FONTE VERMELHO
        printf( "\n\n ERROU ! \n\n"); // MENSAGEM DE ERRO
        Sleep(2000);
        system("cls"); //LIMPA A TELA
        return 0;
    }
    else // CASO O TIRO DADO JA TENHA SIDO FEITO, A MENSAGEM SEGUINTE SER� EXIBIDA
    {
        system("COLOR F4");
        printf( "\n\n TIRO INV�LIDO \n\n");
        Sleep(2000);
        system("cls"); //LIMPA TELA
        return 0;
    }
    system("cls");
}


void ent_saida (int *posicao_linha,int *posicao_coluna, int *direcao, int tabuleiro[TAMANHO][TAMANHO],char *nome, int modo_jogo)
{
    // FUNCIONA PARA 'CHAMAR' AS PRIMEIRAS FUN��ES DO JOGO

    int i; // CONTADOR
    int variavel;
    //OS TAMANHOS DO NAVIO, VEM DO ENUM.
    system("COLOR F9");
    printf("\n\n ALOCAR !! \n\n ");
    imprimir_malha (TAMANHO,tabuleiro,nome); // IMPRIME O TABULEIRO
    printf ("\n\n FIQUE ATENTO AOS TIPOS DE NAVIOS E SUAS POSI��ES \n\n");

    i=0; // ZERA O CONTADOR, PARA QUE O LOOP SEJA DA QUANTIDADE EXATA DOS NAVIOS DEFINIDOS
    while(i < Submarino_quantidade)
    {
        printf("SUBMARINO !!\n\n");
        if (modo_jogo==2) //HUMANO VS HUMANO
        {
            printf("DIGITE A POSI��O (LINHA E COLUNA) <0 a 14> \n");
            scanf ("%d %d", posicao_linha, posicao_coluna); //L� POSI��O LINHA E COLUNA PARA REALIZAR ALOCA��O
            printf("\n");
        }
        else if (modo_jogo==3) // HUMANO VS COMPUTADOR
        {

            srand((unsigned)time(NULL)); // SEMENTE QUE ALIMENTA SORTEIO
            *posicao_linha=rand()%15; // GERA NUMERO DE 0 A 14
            Sleep(1000); // UM SEGUNDO DE DIFEREN�A PARA QUE O SORTEIO SEJA DE POSS�VEIS N�MEROS DIFERENTES

            srand((unsigned)time(NULL));
            *posicao_coluna=rand()%15;
            Sleep(1000);
        }

        if (*posicao_linha >= 15 || *posicao_linha < 0 || *posicao_coluna >=15 || *posicao_coluna < 0)
        {
            //CONFERE SE O VALOR EST� DENTRO DO CAMPO
            system("COLOR F4");
            printf ("\n POSI��O INV�LIDA, TENTE OUTRO VALOR \n\n");
            Sleep(2000);
        }
        else
        {
            if (alocar_navios(TAMANHO, tabuleiro,posicao_linha,posicao_coluna, Submarino, direcao, variavel))
            {
                //CHAMA FUN��O DE ALOCAR NAVIOS, PARA ALOCAR OS SUBMARINOS
                i++; //SOMA PARA CONFERIR A QUANTIDADE NO FINAL DO LOOP, NO CASO DO SUBMARINO O VALOR ACABAR QUANDO CHEGAR EM 4
            }
            printf("\n");
            if (modo_jogo==2) // CASO SEJA HUMANO VS HUMANO O TABULEIRO � EXIBIDO
            {
                imprimir_malha (TAMANHO,tabuleiro,nome);
                printf("\n");
            }
            else if (modo_jogo==3) // SE FOR HUMANO VS COMPUTADOR APENAS INFORMA QUE EST� SENDO ALOCADO
            {
                system("COLOR F9");
                printf("ALOCANDO SUBMARINO %i\n\n", i);
            }
        }
    }

    i=0; // ZERA O CONTADOR PARA REFAZER O LOOP COM A QUANTIDADE DO NAVIO
    while(i < Corveta_quantidade)
    {
        system("COLOR F9");
        printf("CORVETA !!\n");

        if (modo_jogo==2) // CASO SEJA HUMANO VS HUMANO ELE L� AS POSI��ES E A DIRE��O
        {
            printf("DIGITE A POSI��O (LINHA E COLUNA) <0 a 14> \n");
            scanf ("%d %d", posicao_linha, posicao_coluna);
            printf("\n");
            printf("DIRE��O: NORTE (1), SUL (2), LESTE (3) OU OESTE (4) ? \n");
            scanf ("%d", direcao);
            printf ("\n");
        }
        else if (modo_jogo==3) // CASO SEJA HUMANO VS COMPUTADOR ELE L� AS POSI��ES E A DIRE��O
        {

            srand((unsigned)time(NULL));
            *posicao_linha=rand()%15;

            Sleep(1000);

            srand((unsigned)time(NULL));
            *posicao_coluna=rand()%15;

            Sleep(1000);

            srand((unsigned)time(NULL));
            *direcao= 1 + ( rand() % 4 ); // SORTEIA VALOR ENTRE 1 E 4

            Sleep(1000);
        }

        if (*posicao_linha >= 15 || *posicao_linha < 0 || *posicao_coluna>=15 || *posicao_coluna < 0) //TESTA SE EST� DENTRO DO CAMPO
        {
            system("COLOR F4");
            printf ("\n\n POSI��O INV�LIDA, TENTE OUTRO VALOR \n\n");
            Sleep(2000);
        }
        else if (*direcao <= 0 || *direcao > 4) // TESTA ERRO DE DIRE��O
        {
            system("COLOR F4");
            printf ("\n\n DIRE��O INV�LIDA, TENTE OUTRO VALOR \n\n");
            Sleep(2000);
        }
        else
        {
            printf("\n");

            if(alocar_navios(TAMANHO, tabuleiro,posicao_linha,posicao_coluna, Corveta, direcao, variavel))  //SOMA 1 SE A ALOCA��O FOR V�LIDA
            {
                i++;
            }
            printf("\n");
            if (modo_jogo==2) //IMPRIME
            {
                imprimir_malha (TAMANHO,tabuleiro,nome);
                printf("\n");
            }
            else if (modo_jogo==3) // CASO SEJA COMPUTADOR, APENAS INFORMA.
            {
                system("COLOR F9");
                printf("ALOCANDO CORVETA %i\n\n", i);

            }
        }
    }
    i=0; // ZERA CONTADOR
    while(i < Fragata_quantidade)
    {
        /*  AS SEGUINTES OPERA��ES S�O AS MESMAS DO NAVIO ANTERIOR  */
        printf("FRAGATA !!\n");
        if (modo_jogo==2)
        {
            printf("DIGITE A POSI��O (LINHA E COLUNA) <0 a 14>\n");
            scanf ("%d %d", posicao_linha, posicao_coluna);
            printf("\n");
            printf("DIRE��O: NORTE (1), SUL (2), LESTE (3) OU OESTE (4) ? \n");
            scanf ("%d", direcao);
            printf ("\n");
        }
        else if (modo_jogo==3)
        {

            srand((unsigned)time(NULL));
            *posicao_linha=rand()%15;
            Sleep(1000);

            srand((unsigned)time(NULL));
            *posicao_coluna=rand()%15;

            Sleep(1000);

            srand((unsigned)time(NULL));
            *direcao= 1 + ( rand() % 4 );

            Sleep(1000);
        }
        if (*posicao_linha >= 15 || *posicao_linha < 0 || *posicao_coluna>=15 || *posicao_coluna < 0)
        {
            system("COLOR F4");
            printf ("\n\n POSI��O INV�LIDA, TENTE OUTRO VALOR \n\n");
            Sleep(2000);
        }
        else if (*direcao <= 0 || *direcao > 4)
        {
            system("COLOR F4");
            printf ("\n\n DIRE��O INV�LIDA, TENTE OUTRO VALOR \n\n");
            Sleep(2000);

        }
        else
        {
            if(alocar_navios(TAMANHO, tabuleiro,posicao_linha,posicao_coluna, Fragata, direcao, variavel))  //Soma i se a aloca��o foi v�lida
            {
                i++;
            }
            printf("\n");
            if (modo_jogo==2)
            {
                imprimir_malha (TAMANHO,tabuleiro,nome);
                printf("\n");
            }
            else if (modo_jogo==3)
            {
                system("COLOR F9");
                printf("ALOCANDO FRAGATA %i\n\n", i);

            }
        }
    }

    i=0; //ZERA CONTADOR
    while(i < Porta_aviao_quantidade)
    {
        /*  AS SEGUINTES OPERA��ES S�O AS MESMAS DO NAVIO ANTERIOR  */
        printf("PORTA-AVI�O !!\n");
        if (modo_jogo==2)
        {
            printf("DIGITE A POSI��O (LINHA E COLUNA) <0 a 14>\n");
            scanf ("%d %d", posicao_linha, posicao_coluna);
            printf("\n");
            printf("DIRE��O: NORTE (1), SUL (2), LESTE (3) OU OESTE (4) ? \n");
            scanf ("%d", direcao);
            printf ("\n");
        }
        else if (modo_jogo==3)
        {

            srand((unsigned)time(NULL));
            *posicao_linha=rand()%15;
            Sleep(1000);

            srand((unsigned)time(NULL));
            *posicao_coluna=rand()%15;

            Sleep(1000);

            srand((unsigned)time(NULL));
            *direcao= 1 + ( rand() % 4 );

            Sleep(1000);
        }
        if (*posicao_linha >= 15 || *posicao_linha < 0 || *posicao_coluna>=15 || *posicao_coluna < 0)
        {
            system("COLOR F4");
            printf ("\n\n POSI��O INV�LIDA, TENTE OUTRO VALOR \n\n");
            Sleep(2000);
        }
        else if (*direcao <= 0 || *direcao > 4)
        {
            system("COLOR F4");
            printf ("\n DIRE��O INV�LIDA, TENTE OUTRO VALOR \n\n");
            Sleep(2000);
        }
        else if (alocar_navios(TAMANHO, tabuleiro,posicao_linha,posicao_coluna, Porta_aviao, direcao, variavel))
        {
            i++;
        }
        printf("\n");
        if (modo_jogo==2)
        {
            imprimir_malha (TAMANHO,tabuleiro,nome);
            printf("\n");
        }
        else if (modo_jogo==3)
        {
            system("COLOR F9");
            printf("ALOCANDO PORTA-AVI�O %i\n\n", i);
        }
    }
    system("cls"); //LIMPA A TELA
}
