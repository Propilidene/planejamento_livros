#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
int main()
{
    int tpag,ipag,x=1,j=0,i,u=0;
    float progresso,tempo_leitura,tempo_individual;
    char sprogresso[12],livro[50];
    time_t rawtime;
    struct tm * timeinfo;
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    FILE *p;
    system("cls");
    printf("===== PLANEJAMENTO DE LEITURAS =====\n");
    printf("    Digite 1 para cadastrar o livro.\n");
    printf("    Digite 2 para marcar a pagina que parou do livro. (EM DESENVOLVIMENTO)\n");
    printf("    Digite 3 para ver as instrucoes de uso do programa.\n");
    printf("    Digite 0 para sair.\n");
    while(x != 0)
    {
        printf("\nO que deseja fazer?: ");
        scanf("%d",&x);
        switch(x)
        {
            case 1:
                printf("Digite aqui o nome do livro que deseja cadastrar: ");
                getchar();
                fgets(livro,50,stdin);
                printf("Digite quantas paginas o livro tem: ");
                scanf("%d",&tpag);
                livro[strlen(livro) - 1] = '\0';
                printf("Digite em que pagina do livro voce esta: ",&ipag);
                scanf("%d",&ipag);
                printf("Digite em quantos dias voce deseja ler o livro: ");
                scanf("%f",&tempo_individual);
                printf("Digite aqui quantas horas por dia voce vai se dedicar a esta leitura: ");
                scanf("%f",&tempo_leitura);
                p = fopen("livros.txt","a");
                progresso = (float) 100* ipag / tpag;
                sprintf(sprogresso,"%.2f",progresso);
                strcat(sprogresso,"%");
                fprintf(p,"- %s:\n\n      Inicio da Leitura: %s      Paginas lidas: %d\n      Paginas totais: %d\n      Progresso: %s\n\n",livro,asctime (timeinfo),ipag,tpag,sprogresso);
                float tempos_sugeridos[16],paginas_por_dia[16],paginas_por_hora[16];
                // Recomenda��o do autor (30 paginas por dia) =>
                float autor_dias = (float) (tpag - ipag) / 30;
                float autor_pag_por_hora = (float) 30 / tempo_leitura;


                for (i=5;i<=20;i++)
                {
                    tempos_sugeridos[j] = (float) i * tempo_individual / 10;
                    paginas_por_dia[j] = (tpag - ipag) / tempos_sugeridos[j];
                    paginas_por_hora[j] = paginas_por_dia[j] / tempo_leitura;
                    j++;
                }

                fprintf(p,"   Relatorio: Para voce concluir a leitura, iremos sugerir a voce um plano com dias proximos do seu prazo determinado.\n");
                for(i=0;i<=15;i++)
                {
                    if (i!=5) // Pois quando i é igual a 10 => j era igual 5.
                    {
                        fprintf(p,"      - %.1f dias:\n        Para ler o livro em %.1f dias voce devera ler %.1f paginas por dia ou dentro do seu planejamento diário com (%.1f horas/dia) teriam de ser lidas %.1f paginas por hora.\n\n",tempos_sugeridos[i],tempos_sugeridos[i],paginas_por_dia[i],tempo_leitura,paginas_por_hora[i]);
                    }
                    else
                    {
                        fprintf(p,"      - %.1f dias (Tempo determinado pelo usuário):\n        Para ler o livro em %.1f dias voce devera ler %.1f paginas por dia ou dentro do seu planejamento diário com (%.1f horas/dia) teriam de ser lidas %.1f paginas por hora.\n\n",tempos_sugeridos[i],tempos_sugeridos[i],paginas_por_dia[i],tempo_leitura,paginas_por_hora[i]);
                    }
                }
                fprintf(p,"      - Recomendado pelo autor (%.1f dias):\n        Para ler o livro em %.1f dias você devera ler 30.0 paginas por dia ou dentro do seu planejamento diário com (%.1f horas/dia) teriam de ser lidas %.1f paginas por hora.\n\n\n", autor_dias,autor_dias,tempo_leitura,autor_pag_por_hora);
                Sleep(300);
                printf("\nProcessando .");
                Sleep(400);
                printf(" .");
                Sleep(500);
                printf(" .");
                printf("\nLivro cadastrado com sucesso!\n");
                break;
            case 2:
                printf("Ainda estamos desenvolvendo esse espaco, peco que tenha paciencia e aguarde!\n");
                break;
            case 3:
                system("cls");
                printf("Digitos:\n\n  1: Voce podera cadastrar um livro desejado para a leitura.\n\n");
                printf("  2: Voce podera comparar seu progresso atual com o progresso que voce\n     deveria estar cumprindo atraves de cadastramentos das paginas atuais.\n     {\n          EM DESENVOLVIMENTO\n     }\n\n");
                printf("  3: Se voce esta lendo isso agora, creio que voce ja sabe usar o digito 3.\n\n");
                printf("  0: Caso tenha feito seus cadastramentos e acompanhamentos, digite 0 para sair.\n\n");
                printf("  Qualquer outro digito sem ser os ditos: Ocorrera uma mensagem pedindo para\n                                          voce digitar um numero valido.\n\n");
                system("pause");
                system("cls");
                printf("===== PLANEJAMENTO DE LEITURAS =====\n");
                printf("    Digite 1 para cadastrar o livro.\n");
                printf("    Digite 2 para marcar a pagina que parou do livro. (EM DESENVOLVIMENTO)\n");
                printf("    Digite 3 para ver as instrucoes de uso do programa.\n");
                printf("    Digite 0 para sair.\n");
                break;
            case 0:
                exit(1);
                break;
            default:
                printf("Por favor, digite uma opcao valida!\n");
                break;
        }
    }
    return 0;
}
