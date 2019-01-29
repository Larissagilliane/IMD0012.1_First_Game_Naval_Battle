#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <conio.h>
#include <windows.h>
#include "ent_saida.h"

// CADA ARQUIVO TERÁ SUA DOCUMENTAÇÃO EM SUA PÁGINA

/* COMENTÁRIOS E DOCUMENTAÇÃO "PRINCIPAL.C":
        - O jogo foi desenvolvido, apesar dos problemas durante o seu seguimento, tentando seguir as regras do documento disponibilizado.
    * Funções:
       - As funções 'creditos' e 'regras', não retornam nenhum valor e servem apenas para exibir textos, referentes ,respectivamente,
       aos créditos do jogo e a curtas intruções de como jogá-lo.
    * Main:
       - Logo no inicio da função ocorre a declaração das variávies e das estruturas usadas no jogo, logo após as declarações
       um laço de repetição (while), é criado para fazer com que o usuário possa jogar novamente, ao término do jogo.
       O menu é impresso, e o usuário logo em seguida digita a opção que ele deseja realizar de acordo com a legenda do menu.

       - Caso ele escolha a opção '2', ele inicia o jogo com 2 jogadores. Os usuários devem digitar os seus nomes e iniciar as partidas, as funções são
       chamadas (a explicação das funções serão ditas no arquivo "ent_saida.") e após a chamada de "ent_saida" (onde é chamada a alocação), ele começa o while
       onde será decidida a vez do jogador e também chama a função que confere vitória.

       - Caso algum jogador ganhe, ele recebe a opção se deseja jogar novamente, se ele responder sim o jogo retorna para o menu, caso seja não, ele exibe a
       função de créditos do jogo.

       - Se no menu inicial o usuário digitar 3, ele chama as funções e envia o jogador 2 como computador, transformando a variavel "modo_jogo" em 3.

       - Se o menu a resposta for 4 ele sai do jogo, caso ele digite um valor incorreto ele exibe a mensagem que está incorreto.

 */

void creditos () // APENAS CHAMA OS CRÉDITOS DO JOGO
{
    system("cls");
    printf("CRÉDITOS: \n\n Larissa Gilliane Melo de Moura - 20160000820 \n (+ ajuda de professor e ajudantes rsrs)");
    Sleep(5000);
}

void regras () // APRESENTA AS INTRUÇÕES BÁSICAS DO JOGO
{
    printf("\n");
    printf("Regras do jogo: \n\n");
    printf("1.Você deverá escolher o modo de jogo que deseja\n\n" );
    printf("2.Se dejesar inciar o jogo, aloque seus navios \n\n");
    printf("3.Submarino (1 casa), Corveta (2 casas), Fragata (3 casa) e Porta-Aviões (4 casas)).\n\n");
    printf("4.Quando ambos os tabuleiros tiverem sido preenchidos, comece a atirar.\n\n");
    printf("5.Ganhará o jogo quem atigir todos os barcos do adversário primeiro.\n\n");

    Sleep(10000); // DEIXA A TELA PARADA. CALCULADO EM MILISEGUNDOS
}

int main ()//CHAMA AS FUNÇÕES CONTIDAS NO ARQUIVO ".C"
{

    struct Players player; // SALVA O NOME DOS JOGADORES

    struct Campo tabuleiro1, tabuleiro2; // REGISTRA OS TABULEIROS COM OS NAVIOS, PARA JOGADOR 1 E 2
    struct Campo tabuleiro_visualizado1, tabuleiro_visualizado2; // REGISTRA OS TABULEIOROS COM OS TIROS, PRA JOGADOR 1 E 2

    int opcao_jogo; // ESCOLHE UMA OPÇÃO DO MENU
    int posicao_linha,posicao_coluna,direcao, posicao_linha_tiro, posicao_coluna_tiro; // ARMAZENAM O VALOR DAS VARIAVEIS DE TIRO E DE ALOCAÇÃO
    int vez_jogador = 1; // INDICA A VEZ DO JOGADOR (COMEÇA DO JOGADOR 1)
    int modo_jogo; // MANDA SE O JOGO SERÁ HUMANO VS HUMANO, OU HUMANO VS MÁQUINA
    int novo_jogo=1; // SERVE PARA O LOOP, CASO O USUÁRIO DESEJE JOGAR NOVAMENTE
    long int tempo_comeca; // TEMPO DE COMEÇO DA PARTIDA
    long int tempo_termina; // TEMPO FINAL DA PARTIDA
    long int duracao; // SUBTRAÇÃO DO TEMPO FINAL DO TEMPO COMEÇO
    int minutos; // TRANSFORMA PARA MINUTOS
    int segundos; // TRANSFORMA PARA SEGUNDOS

    while (novo_jogo) // LOOP QUE CONFERE SE O JOGADOR QUER REPETIR O JOGO
    {
        tempo_comeca = (unsigned) time(NULL); //  PEGA O TEMPO DE INICIO

        printf("\n"); // MENU
        system("COLOR F9"); // DEFINE A COR DO FUNDO E DA FONTE (FUNDO BRANCO E FONTE AZUL)
        printf(".............. Bem-vindo ao jogo Batalha Natal .............\n\n");
        printf(" 1 - Instruções.............................................\n", setlocale(LC_ALL,""));
        printf(" 2 - Começar o jogo <Player 1 vs Player 2>..................\n");
        printf(" 3 - Começar o jogo <Player vs Computador>..................\n");
        printf(" 4 - Sair...................................................\n");
        printf("\n");

        printf("ESCOLHA UMA OPÇÃO: \n");
        scanf ("%i", &opcao_jogo); // USUÁRIO ESCOLHE OPÇÃO DO MENU
        system("cls");



        if (opcao_jogo == 1) // CHAMA AS INSTRUÇÕES
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


            inicializar_malha(TAMANHO, tabuleiro1.matriz_jogador, player.nome_1); //INICIA A MALHA ONDE FICARÃO OS NAVIOS DO JOGADOR 1 (MAS NÃO EXIBE)
            inicializar_malha(TAMANHO, tabuleiro2.matriz_jogador, player.nome_2); //INICIA A MALHA ONDE FICARÃO OS NAVIOS DO JOGADOR 2 (MAS NÃO EXIBE)
            //printf("\n\n ALOCAR !! \n\n ");
            inicializar_malha(TAMANHO, tabuleiro_visualizado1.matriz_jogador, player.nome_1); //INICIA A MALHA ONDE FICARÃO OS TIROS DO JOGADOR 1 (MAS NÃO EXIBE)
            inicializar_malha(TAMANHO, tabuleiro_visualizado2.matriz_jogador, player.nome_2); //INICIA A MALHA ONDE FICARÃO OS TIROS DO JOGADOR 1 (MAS NÃO EXIBE)
            ent_saida(&posicao_linha, &posicao_coluna, &direcao, tabuleiro1.matriz_jogador, player.nome_1,modo_jogo); //SUBROTINA, ONDE CHAMARÁ A FUNÇÃO DE ALOCAR, DO JOGADOR 1
            ent_saida(&posicao_linha, &posicao_coluna, &direcao, tabuleiro2.matriz_jogador, player.nome_2,modo_jogo); //SUBROTINA, ONDE CHAMARÁ A FUNÇÃO DE ALOCAR, DO JOGADOR 2

            while(1)  //LOOP QUE TESTARÁ VITÓRIA, CASO SAIA DELE SIGNIFICA QUE ALGUEM GANHOU, (COMEÇA COM 1 PARA FUNCIONAR ATE QUE HAJA CONDIÇAÕ DE PARADA -BREAK- )
            {
                if(vez_jogador == 1) // COMEÇA COM VEZ DO JOGADOR 1
                {

                    printf("\n\n ATIRAR !! \n\n ");
                    imprimir_malha(TAMANHO,tabuleiro_visualizado1.matriz_jogador,player.nome_1); // IMPRIME TABULEIRO LIMPO
                    if(atirar(tabuleiro_visualizado1.matriz_jogador, tabuleiro2.matriz_jogador, &posicao_linha_tiro,&posicao_coluna_tiro, vez_jogador, player.nome_1, modo_jogo) == 1) //COMEÇA A ATIRAR PARA O JOGADOR 1
                    {
                        vez_jogador = 1; // EMQUANTO ELE ACERTA A VEZ É DELE
                        if(verificar_vitoria (TAMANHO,tabuleiro_visualizado1.matriz_jogador, vez_jogador, player.nome_1,modo_jogo) != 0) // VERIFICA SE JOGADOR 1 GANHA, CASO SIM , ELE SAI DO LAÇO
                        {
                            //system("cls");
                            //printf("\n\n DESEJA JOGAR NOVAMENTE ? (1) SIM ou (2) NÃO \n\n ");
                            break; // SAI DO LAÇO
                        }  // SAI DO WHILE
                    }
                    else
                    {
                        vez_jogador = 2; // CASO ELE ERRE OU NÃO TENHA GANHO PASSA A VEZ PARA JOGADOR 2
                    }
                }
                else if (vez_jogador == 2) // COMEÇA LAÇO DO JOGADOR 2
                {
                    printf("\n\n ATIRAR !! \n\n ");
                    imprimir_malha(TAMANHO,tabuleiro_visualizado2.matriz_jogador,player.nome_2); // IMPRIME TABULEIRO LIMPO
                    if(atirar(tabuleiro_visualizado2.matriz_jogador, tabuleiro1.matriz_jogador, &posicao_linha_tiro,&posicao_coluna_tiro, vez_jogador, player.nome_2,modo_jogo) == 2)//COMEÇA A ATIRAR PARA O JOGADOR 2
                    {
                        vez_jogador = 2; // EMQUANTO ELE ACERTA A VEZ É DELE
                        if(verificar_vitoria (TAMANHO,tabuleiro_visualizado2.matriz_jogador, vez_jogador, player.nome_2,modo_jogo) != 0)// VERIFICA SE JOGADOR 2 GANHA, CASO SIM , ELE SAI DO LAÇO
                            break;
                    }
                    else
                    {
                        vez_jogador = 1; // CASO ELE ERRE OU NÃO TENHA GANHO PASSA A VEZ PARA JOGADOR 1
                    }
                }
            }
        }
        else if (opcao_jogo==3) // CHAMA JOGO HUMANO VS MÁQUINA
        {
            printf ("NOME JOGADOR 1:\n");
            fflush(stdin);
            fgets(player.nome_1, 40, stdin); // REGISTRA O NOME DO JOGADOR 1
            printf ("\n");

            printf ("DÊ UM APELIDO PARA O COMPUTADOR\n");  // REGISTRA UM APELIDO DO COMPUTADOR
            fflush(stdin);
            fgets(player.nome_2, 40, stdin);
            printf ("\n");
            system("cls");


            inicializar_malha(TAMANHO, tabuleiro1.matriz_jogador, player.nome_1); //INICIA A MALHA ONDE FICARÃO OS NAVIOS DO JOGADOR 1 (MAS NÃO EXIBE)
            inicializar_malha(TAMANHO, tabuleiro2.matriz_jogador, player.nome_2); //INICIA A MALHA ONDE FICARÃO OS NAVIOS DO COMPUTADOR (MAS NÃO EXIBE)

            inicializar_malha(TAMANHO, tabuleiro_visualizado1.matriz_jogador, player.nome_1); //INICIA A MALHA ONDE FICARÃO OS TIROS DO JOGADOR 1 (MAS NÃO EXIBE)
            inicializar_malha(TAMANHO, tabuleiro_visualizado2.matriz_jogador, player.nome_2); //INICIA A MALHA ONDE FICARÃO OS TIROS DO COMPUTADOR (MAS NÃO EXIBE)
            ent_saida(&posicao_linha, &posicao_coluna, &direcao, tabuleiro1.matriz_jogador, player.nome_1,2); //SUBROTINA, ONDE CHAMARÁ A FUNÇÃO DE ALOCAR, DO JOGADOR 1 //AQUI ELE INDICA QUE O JOGADOR É HUMANO AO PASSAR 2
            ent_saida(&posicao_linha, &posicao_coluna, &direcao, tabuleiro2.matriz_jogador, player.nome_2,3); //SUBROTINA, ONDE CHAMARÁ A FUNÇÃO DE ALOCAR, DO COMPUTADOR //AQUI ELE INDICA QUE O JOGADOR UM COMPUTADOR AO PASSAR 3

            while(1) //LOOP QUE TESTARÁ VITÓRIA, CASO SAIA DELE SIGNIFICA QUE ALGUEM GANHOU, (COMEÇA COM 1 PARA FUNCIONAR ATE QUE HAJA CONDIÇAÕ DE PARADA -BREAK- )
            {
                /* TODA A LÓGICA OCORRE DA MESMA MANEIRA, A UNICA DIFERNÇA SERÁ QUE O JOGADOR 2 SERÁ O COMPUTADOR */
                if(vez_jogador == 1)
                {
                    printf("\n\n ATIRAR !! \n\n ");
                    imprimir_malha(TAMANHO,tabuleiro_visualizado1.matriz_jogador,player.nome_1);
                    if(atirar(tabuleiro_visualizado1.matriz_jogador, tabuleiro2.matriz_jogador, &posicao_linha_tiro,&posicao_coluna_tiro, vez_jogador, player.nome_1,2) == 1) //AQUI ELE INDICA QUE O JOGADOR É HUMANO AO PASSAR 2
                    {
                        vez_jogador = 1;
                        if(verificar_vitoria (TAMANHO,tabuleiro_visualizado1.matriz_jogador, vez_jogador, player.nome_1,2) != 0) //AQUI ELE INDICA QUE O JOGADOR É HUMANO AO PASSAR 2
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
        else if (opcao_jogo == 4) // OPÇÃO DE SAIR DO JOGO
        {
            exit(0);
        }
        else
        {
            printf ("OPERAÇÃO INVÁLIDA\n"); //CASO O USUÁRIO DIGITE ALGO ERRADO
        }
        tempo_termina = (unsigned) time(NULL); // PEGA O TEMPO FINAL
        duracao = (tempo_termina - tempo_comeca); // SUBTRAI O TEMPO FINAL COM O INCIAL
        minutos = duracao % 60; // PEGA O NUMERO DE MINUTOS
        segundos = duracao - minutos*60; // PEGA OS SEGUNDOS
        printf ("\n Tempo de duração da partida: %d minutos e %d segundos \n", minutos, segundos); // IMPRIME O TEMPO DE DURAÇÃO
        system("COLOR F9");

        printf ("\n Deseja jogar de novo ? (0 - Não / 1 - Sim) \n"); // PERGUNTA AO JOGADOR SE ELE DESEJA JOGAR NOVAMENTE
        scanf ("%i", &novo_jogo);
        system ("cls");

        while(novo_jogo != 1 && novo_jogo != 0)  // TRATAMENTO DE ERRO DA VARIAVEL "NOVO_JOGO
        {
            system("cls");
            printf ("\n Deseja jogar de novo ? (0 - Não / 1 - Sim) \n");
            scanf ("%i", &novo_jogo);
            system("cls");
        }

    }

    creditos(); // CHAMA OS CRÉDITOS
    return 0;
}
