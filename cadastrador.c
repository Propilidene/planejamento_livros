#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
int main()
{
    int tpag,ipag,x=1,progresso,j=0,i;
    float tempo_leitura,tempo_individual;
    char sprogresso[12];
    char *livro;
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    FILE *p;
    system("cls");
    printf("===== PLANEJAMENTO DE LEITURAS =====\n");
    printf("    Digite 1 para cadastrar o livro.\n");
    printf("    Digite 2 para marcar a pagina que parou do livro. (EM DESENVOLVIMENTO)\n");
    printf("    Digite 0 para sair.\n");
    while(x != 0)
    {
        printf("\nO que deseja fazer?: ");
        scanf("%d",&x);
        switch(x)
        {
            case 1:
                livro = (char*) malloc(50 * sizeof(char));
                printf("Digite aqui o nome do livro que deseja cadastrar: ");
                scanf(" %s", livro);
                printf("Digite quantas paginas o livro tem: ");
                scanf("%d",&tpag);
                printf("Digite em que pagina do livro voce esta: ",&ipag);
                scanf("%d",&ipag);
                printf("Digite em quantos dias voce deseja ler o livro: ");
                scanf("%f",&tempo_individual);
                printf("Digite aqui quantas horas por dia voce vai se dedicar a esta leitura: ");
                scanf("%f",&tempo_leitura);
                p = fopen("livros.txt","a");
                progresso = (float) 100* ipag / tpag;
                sprintf(sprogresso,"%d",progresso);
                strcat(sprogresso,"%");
                fprintf(p,"- %s:\n\n      Inicio da Leitura: %s      Paginas lidas: %d\n      Paginas totais: %d\n      Progresso: %s\n\n",livro,asctime (timeinfo),ipag,tpag,sprogresso);
                float tempos_sugeridos[16],paginas_por_dia[16],paginas_por_hora[16];
                // Recomendação do autor (30 paginas por dia) =>
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
                fprintf(p,"      - Recomendado pelo autor (%.1f dias):\n        Para ler o livro em %.1f dias você devera ler 30.0 paginas por dia ou dentro do seu planejamento diário com (%.1f horas/dia) teriam de ser lidas %.1f paginas por hora dentro de %.1f horas.\n\n", autor_dias,autor_dias,tempo_leitura,autor_pag_por_hora,tempo_leitura);

                printf("Parabens, voce cadastrou o livro: %s.\n", livro);
                free(livro);
                break;
            case 2:
                printf("Ainda estamos desenvolvendo esse espaco, peco que tenha paciencia e aguarde!");
                break;
            case 0:
                exit(1);
                break;
            default:
                printf("Por favor, digite uma opcao valida!");
                break;
        }
    }
    return 0;
}