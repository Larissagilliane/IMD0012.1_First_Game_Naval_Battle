#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <conio.h>
#include <windows.h>
#include "ent_saida.h"

// CADA ARQUIVO TER� SUA DOCUMENTA��O EM SUA P�GINA

/* COMENT�RIOS E DOCUMENTA��O "PRINCIPAL.C":
        - O jogo foi desenvolvido, apesar dos problemas durante o seu seguimento, tentando seguir as regras do documento disponibilizado.
    * Fun��es:
       - As fun��es 'creditos' e 'regras', n�o retornam nenhum valor e servem apenas para exibir textos, referentes ,respectivamente,
       aos cr�ditos do jogo e a curtas intru��es de como jog�-lo.
    * Main:
       - Logo no inicio da fun��o ocorre a declara��o das vari�vies e das estruturas usadas no jogo, logo ap�s as declara��es
       um la�o de repeti��o (while), � criado para fazer com que o usu�rio possa jogar novamente, ao t�rmino do jogo.
       O menu � impresso, e o usu�rio logo em seguida digita a op��o que ele deseja realizar de acordo com a legenda do menu.

       - Caso ele escolha a op��o '2', ele inicia o jogo com 2 jogadores. Os usu�rios devem digitar os seus nomes e iniciar as partidas, as fun��es s�o
       chamadas (a explica��o das fun��es ser�o ditas no arquivo "ent_saida.") e ap�s a chamada de "ent_saida" (onde � chamada a aloca��o), ele come�a o while
       onde ser� decidida a vez do jogador e tamb�m chama a fun��o que confere vit�ria.

       - Caso algum jogador ganhe, ele recebe a op��o se deseja jogar novamente, se ele responder sim o jogo retorna para o menu, caso seja n�o, ele exibe a
       fun��o de cr�ditos do jogo.

       - Se no menu inicial o usu�rio digitar 3, ele chama as fun��es e envia o jogador 2 como computador, transformando a variavel "modo_jogo" em 3.

       - Se o menu a resposta for 4 ele sai do jogo, caso ele digite um valor incorreto ele exibe a mensagem que est� incorreto.

 */

void creditos () // APENAS CHAMA OS CR�DITOS DO JOGO
{
    system("cls");
    printf("CR�DITOS: \n\n Larissa Gilliane Melo de Moura - 20160000820 \n (+ ajuda de professor e ajudantes rsrs)");
    Sleep(5000);
}

void regras () // APRESENTA AS INTRU��ES B�SICAS DO JOGO
{
    printf("\n");
    printf("Regras do jogo: \n\n");
    printf("1.Voc� dever� escolher o modo de jogo que deseja\n\n" );
    printf("2.Se dejesar inciar o jogo, aloque seus navios \n\n");
    printf("3.Submarino (1 casa), Corveta (2 casas), Fragata (3 casa) e Porta-Avi�es (4 casas)).\n\n");
    printf("4.Quando ambos os tabuleiros tiverem sido preenchidos, comece a atirar.\n\n");
    printf("5.Ganhar� o jogo quem atigir todos os barcos do advers�rio primeiro.\n\n");

    Sleep(10000); // DEIXA A TELA PARADA. CALCULADO EM MILISEGUNDOS
}

int main ()//CHAMA AS FUN��ES CONTIDAS NO ARQUIVO ".C"
{

    struct Players player; // SALVA O NOME DOS JOGADORES

    struct Campo tabuleiro1, tabuleiro2; // REGISTRA OS TABULEIROS COM OS NAVIOS, PARA JOGADOR 1 E 2
    struct Campo tabuleiro_visualizado1, tabuleiro_visualizado2; // REGISTRA OS TABULEIOROS COM OS TIROS, PRA JOGADOR 1 E 2

    int opcao_jogo; // ESCOLHE UMA OP��O DO MENU
    int posicao_linha,posicao_coluna,direcao, posicao_linha_tiro, posicao_coluna_tiro; // ARMAZENAM O VALOR DAS VARIAVEIS DE TIRO E DE ALOCA��O
    int vez_jogador = 1; // INDICA A VEZ DO JOGADOR (COME�A DO JOGADOR 1)
    int modo_jogo; // MANDA SE O JOGO SER� HUMANO VS HUMANO, OU HUMANO VS M�QUINA
    int novo_jogo=1; // SERVE PARA O LOOP, CASO O USU�RIO DESEJE JOGAR NOVAMENTE
    long int tempo_comeca; // TEMPO DE COME�O DA PARTIDA
    long int tempo_termina; // TEMPO FINAL DA PARTIDA
    long int duracao; // SUBTRA��O DO TEMPO FINAL DO TEMPO COME�O
    int minutos; // TRANSFORMA PARA MINUTOS
    int segundos; // TRANSFORMA PARA SEGUNDOS

    while (novo_jogo) // LOOP QUE CONFERE SE O JOGADOR QUER REPETIR O JOGO
    {
        tempo_comeca = (unsigned) time(NULL); //  PEGA O TEMPO DE INICIO

        printf("\n"); // MENU
        system("COLOR F9"); // DEFINE A COR DO FUNDO E DA FONTE (FUNDO BRANCO E FONTE AZUL)
        printf(".............. Bem-vindo ao jogo Batalha Natal .............\n\n");
        printf(" 1 - Instru��es.............................................\n", setlocale(LC_ALL,""));
        printf(" 2 - Come�ar o jogo <Player 1 vs Player 2>..................\n");
        printf(" 3 - Come�ar o jogo <Player vs Computador>..................\n");
        printf(" 4 - Sair...................................................\n");
        printf("\n");

        printf("ESCOLHA UMA OP��O: \n");
        scanf ("%i", &opcao_jogo); // USU�RIO ESCOLHE OP��O DO MENU
        system("cls");



        if (opcao_jogo == 1) // CHAMA AS INSTRU��ES
        {
            regras();
        }
        else if (opcao_jogo==2) // CHAMA JOGO HUMANO VS HUMANO
        {
            modo_jogo=2;
            printf ("NOME JOGADOR 1:\n");
            fflush(stdin);
            fgets(player.nome_1, 40, stdin); // REGISTRA O NOME DO JOGADOR 1
            printf ("\n");

            printf ("NOME JOGADOR 2:\n");
            fflush(stdin);
            fgets(player.nome_2, 40, stdin); // REGISTRA O NOME DO JOGADOR 2
            printf ("\n");
            system("cls");


            inicializar_malha(TAMANHO, tabuleiro1.matriz_jogador, player.nome_1); //INICIA A MALHA ONDE FICAR�O OS NAVIOS DO JOGADOR 1 (MAS N�O EXIBE)
            inicializar_malha(TAMANHO, tabuleiro2.matriz_jogador, player.nome_2); //INICIA A MALHA ONDE FICAR�O OS NAVIOS DO JOGADOR 2 (MAS N�O EXIBE)
            //printf("\n\n ALOCAR !! \n\n ");
            inicializar_malha(TAMANHO, tabuleiro_visualizado1.matriz_jogador, player.nome_1); //INICIA A MALHA ONDE FICAR�O OS TIROS DO JOGADOR 1 (MAS N�O EXIBE)
            inicializar_malha(TAMANHO, tabuleiro_visualizado2.matriz_jogador, player.nome_2); //INICIA A MALHA ONDE FICAR�O OS TIROS DO JOGADOR 1 (MAS N�O EXIBE)
            ent_saida(&posicao_linha, &posicao_coluna, &direcao, tabuleiro1.matriz_jogador, player.nome_1,modo_jogo); //SUBROTINA, ONDE CHAMAR� A FUN��O DE ALOCAR, DO JOGADOR 1
            ent_saida(&posicao_linha, &posicao_coluna, &direcao, tabuleiro2.matriz_jogador, player.nome_2,modo_jogo); //SUBROTINA, ONDE CHAMAR� A FUN��O DE ALOCAR, DO JOGADOR 2

            while(1)  //LOOP QUE TESTAR� VIT�RIA, CASO SAIA DELE SIGNIFICA QUE ALGUEM GANHOU, (COME�A COM 1 PARA FUNCIONAR ATE QUE HAJA CONDI�A� DE PARADA -BREAK- )
            {
                if(vez_jogador == 1) // COME�A COM VEZ DO JOGADOR 1
                {

                    printf("\n\n ATIRAR !! \n\n ");
                    imprimir_malha(TAMANHO,tabuleiro_visualizado1.matriz_jogador,player.nome_1); // IMPRIME TABULEIRO LIMPO
                    if(atirar(tabuleiro_visualizado1.matriz_jogador, tabuleiro2.matriz_jogador, &posicao_linha_tiro,&posicao_coluna_tiro, vez_jogador, player.nome_1, modo_jogo) == 1) //COME�A A ATIRAR PARA O JOGADOR 1
                    {
                        vez_jogador = 1; // EMQUANTO ELE ACERTA A VEZ � DELE
                        if(verificar_vitoria (TAMANHO,tabuleiro_visualizado1.matriz_jogador, vez_jogador, player.nome_1,modo_jogo) != 0) // VERIFICA SE JOGADOR 1 GANHA, CASO SIM , ELE SAI DO LA�O
                        {
                            //system("cls");
                            //printf("\n\n DESEJA JOGAR NOVAMENTE ? (1) SIM ou (2) N�O \n\n ");
                            break; // SAI DO LA�O
                        }  // SAI DO WHILE
                    }
                    else
                    {
                        vez_jogador = 2; // CASO ELE ERRE OU N�O TENHA GANHO PASSA A VEZ PARA JOGADOR 2
                    }
                }
                else if (vez_jogador == 2) // COME�A LA�O DO JOGADOR 2
                {
                    printf("\n\n ATIRAR !! \n\n ");
                    imprimir_malha(TAMANHO,tabuleiro_visualizado2.matriz_jogador,player.nome_2); // IMPRIME TABULEIRO LIMPO
                    if(atirar(tabuleiro_visualizado2.matriz_jogador, tabuleiro1.matriz_jogador, &posicao_linha_tiro,&posicao_coluna_tiro, vez_jogador, player.nome_2,modo_jogo) == 2)//COME�A A ATIRAR PARA O JOGADOR 2
                    {
                        vez_jogador = 2; // EMQUANTO ELE ACERTA A VEZ � DELE
                        if(verificar_vitoria (TAMANHO,tabuleiro_visualizado2.matriz_jogador, vez_jogador, player.nome_2,modo_jogo) != 0)// VERIFICA SE JOGADOR 2 GANHA, CASO SIM , ELE SAI DO LA�O
                            break;
                    }
                    else
                    {
                        vez_jogador = 1; // CASO ELE ERRE OU N�O TENHA GANHO PASSA A VEZ PARA JOGADOR 1
                    }
                }
            }
        }
        else if (opcao_jogo==3) // CHAMA JOGO HUMANO VS M�QUINA
        {
            printf ("NOME JOGADOR 1:\n");
            fflush(stdin);
            fgets(player.nome_1, 40, stdin); // REGISTRA O NOME DO JOGADOR 1
            printf ("\n");

            printf ("D� UM APELIDO PARA O COMPUTADOR\n");  // REGISTRA UM APELIDO DO COMPUTADOR
            fflush(stdin);
            fgets(player.nome_2, 40, stdin);
            printf ("\n");
            system("cls");


            inicializar_malha(TAMANHO, tabuleiro1.matriz_jogador, player.nome_1); //INICIA A MALHA ONDE FICAR�O OS NAVIOS DO JOGADOR 1 (MAS N�O EXIBE)
            inicializar_malha(TAMANHO, tabuleiro2.matriz_jogador, player.nome_2); //INICIA A MALHA ONDE FICAR�O OS NAVIOS DO COMPUTADOR (MAS N�O EXIBE)

            inicializar_malha(TAMANHO, tabuleiro_visualizado1.matriz_jogador, player.nome_1); //INICIA A MALHA ONDE FICAR�O OS TIROS DO JOGADOR 1 (MAS N�O EXIBE)
            inicializar_malha(TAMANHO, tabuleiro_visualizado2.matriz_jogador, player.nome_2); //INICIA A MALHA ONDE FICAR�O OS TIROS DO COMPUTADOR (MAS N�O EXIBE)
            ent_saida(&posicao_linha, &posicao_coluna, &direcao, tabuleiro1.matriz_jogador, player.nome_1,2); //SUBROTINA, ONDE CHAMAR� A FUN��O DE ALOCAR, DO JOGADOR 1 //AQUI ELE INDICA QUE O JOGADOR � HUMANO AO PASSAR 2
            ent_saida(&posicao_linha, &posicao_coluna, &direcao, tabuleiro2.matriz_jogador, player.nome_2,3); //SUBROTINA, ONDE CHAMAR� A FUN��O DE ALOCAR, DO COMPUTADOR //AQUI ELE INDICA QUE O JOGADOR UM COMPUTADOR AO PASSAR 3

            while(1) //LOOP QUE TESTAR� VIT�RIA, CASO SAIA DELE SIGNIFICA QUE ALGUEM GANHOU, (COME�A COM 1 PARA FUNCIONAR ATE QUE HAJA CONDI�A� DE PARADA -BREAK- )
            {
                /* TODA A L�GICA OCORRE DA MESMA MANEIRA, A UNICA DIFERN�A SER� QUE O JOGADOR 2 SER� O COMPUTADOR */
                if(vez_jogador == 1)
                {
                    printf("\n\n ATIRAR !! \n\n ");
                    imprimir_malha(TAMANHO,tabuleiro_visualizado1.matriz_jogador,player.nome_1);
                    if(atirar(tabuleiro_visualizado1.matriz_jogador, tabuleiro2.matriz_jogador, &posicao_linha_tiro,&posicao_coluna_tiro, vez_jogador, player.nome_1,2) == 1) //AQUI ELE INDICA QUE O JOGADOR � HUMANO AO PASSAR 2
                    {
                        vez_jogador = 1;
                        if(verificar_vitoria (TAMANHO,tabuleiro_visualizado1.matriz_jogador, vez_jogador, player.nome_1,2) != 0) //AQUI ELE INDICA QUE O JOGADOR � HUMANO AO PASSAR 2
                            break;
                    }
                    else
                    {
                        vez_jogador = 2;
                    }
                }
                else if (vez_jogador == 2)
                {
                    printf("\n\n ATIRAR !! \n\n ");
                    imprimir_malha(TAMANHO,tabuleiro_visualizado2.matriz_jogador,player.nome_2);
                    if(atirar(tabuleiro_visualizado2.matriz_jogador, tabuleiro1.matriz_jogador, &posicao_linha_tiro,&posicao_coluna_tiro, vez_jogador, player.nome_2,3) == 2) //AQUI ELE INDICA QUE O JOGADOR UM COMPUTADOR AO PASSAR 3
                    {
                        vez_jogador = 2;
                        if(verificar_vitoria (TAMANHO,tabuleiro_visualizado2.matriz_jogador, vez_jogador, player.nome_2,3) != 0)//AQUI ELE INDICA QUE O JOGADOR UM COMPUTADOR AO PASSAR 3
                            break;
                    }
                    else
                    {
                        vez_jogador = 1;
                    }
                }
            }
        }
        else if (opcao_jogo == 4) // OP��O DE SAIR DO JOGO
        {
            exit(0);
        }
        else
        {
            printf ("OPERA��O INV�LIDA\n"); //CASO O USU�RIO DIGITE ALGO ERRADO
        }
        tempo_termina = (unsigned) time(NULL); // PEGA O TEMPO FINAL
        duracao = (tempo_termina - tempo_comeca); // SUBTRAI O TEMPO FINAL COM O INCIAL
        minutos = duracao % 60; // PEGA O NUMERO DE MINUTOS
        segundos = duracao - minutos*60; // PEGA OS SEGUNDOS
        printf ("\n Tempo de dura��o da partida: %d minutos e %d segundos \n", minutos, segundos); // IMPRIME O TEMPO DE DURA��O
        system("COLOR F9");

        printf ("\n Deseja jogar de novo ? (0 - N�o / 1 - Sim) \n"); // PERGUNTA AO JOGADOR SE ELE DESEJA JOGAR NOVAMENTE
        scanf ("%i", &novo_jogo);
        system ("cls");

        while(novo_jogo != 1 && novo_jogo != 0)  // TRATAMENTO DE ERRO DA VARIAVEL "NOVO_JOGO
        {
            system("cls");
            printf ("\n Deseja jogar de novo ? (0 - N�o / 1 - Sim) \n");
            scanf ("%i", &novo_jogo);
            system("cls");
        }

    }

    creditos(); // CHAMA OS CR�DITOS
    return 0;
}
