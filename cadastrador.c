#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
struct LIVRO
{
    long int tempo_log;
    int pag_inicial,pag_atual,pag_final;
    float tempo_leitura,tempo_individual;
    char nome[50];
};

int main()
{
    int tpag,ipag,apag,x=1,j,i,w,cont,u=0,livro_escolhido;
    float progresso,tempo_leitura,tempo_individual,tempos_sugeridos[16],paginas_por_dia[16],paginas_por_hora[16],autor_dias,autor_pag_por_hora,terminaem,autor_terminaem,terminariaem,autor_terminariaem,dias_decorridos,autor_atual,atual,paginas_otimas;
    char sprogresso[12],livro[50],detTAM[70],stringboba[8];
    char y = 'n';
    time_t rawtime;
    struct tm * timeinfo;
    struct LIVRO livros_cadastrados[50];
    time_t tempo_log;
    FILE *p;
    FILE *q;
    system("cls");
    printf("===== PLANEJAMENTO DE LEITURAS =====\n");
    printf("    Digite 1 para cadastrar o livro.\n");
    printf("    Digite 2 para marcar a pagina que parou do livro.\n");
    printf("    Digite 3 para ver as instrucoes de uso do programa.\n");
    printf("    Digite 0 para sair.\n");
    while(x != 0)
    {
        printf("\nO que deseja fazer?: ");
        scanf("%d",&x);
        switch(x)
        {
            case 1:
                time(&tempo_log);
                time (&rawtime);
    			timeinfo = localtime (&rawtime);
                j=0;
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
                fprintf(p,"- %s:\n\n      Inicio da Leitura: %s      Pagina Inicial: %d\n      Paginas lidas: %d\n      Paginas totais: %d\n      Progresso: %s\n\n",livro,asctime (timeinfo),ipag,ipag,tpag,sprogresso);
                // Recomendacao do autor (30 paginas por dia) =>
                autor_dias = (float) (tpag - ipag) / 30;
                autor_pag_por_hora = (float) 30 / tempo_leitura;

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
                    terminaem =  (tpag - ipag) / paginas_por_dia[i];
					if (i!=5) // Pois quando i e igual a 10 => j era igual 5.
                    {
                        fprintf(p,"      - Plano de %.1f dias:\n        * Para ler o livro em %.1f dias voce devera ler %.1f paginas por dia ou dentro do seu planejamento diário com (%.1f horas/dia) teriam de ser lidas %.1f paginas por hora.\n        * Termina em %.1f dias.\n\n",tempos_sugeridos[i],tempos_sugeridos[i],paginas_por_dia[i],tempo_leitura,paginas_por_hora[i],terminaem);
                    }
                    else
                    {
                        fprintf(p,"      - Plano de %.1f dias (Tempo determinado pelo usuario):\n        * Para ler o livro em %.1f dias voce devera ler %.1f paginas por dia ou dentro do seu planejamento diário com (%.1f horas/dia) teriam de ser lidas %.1f paginas por hora.\n\n        * Paginas Lidas: %d\n        * Paginas que deveriam ter sido lidas: %.1f\n        * Termina em %.1f dias.\n        * Era pra terminar em %.1f dias.\n        * Resumo: Voce esta dentro do prazo determinado!\n\n",tempos_sugeridos[i],tempos_sugeridos[i],paginas_por_dia[i],tempo_leitura,paginas_por_hora[i],ipag,ipag,terminaem,terminaem);
                    }
                }
                autor_terminaem = (tpag - ipag) / 30.0;
                fprintf(p,"      - Recomendado pelo autor (Plano de %.1f dias):\n        * Para ler o livro em %.1f dias voce devera ler 30.0 paginas por dia ou dentro do seu planejamento diario com (%.1f horas/dia) teriam de ser lidas %.1f paginas por hora.\n        * Termina em %.1f dias.\n\n\n", autor_dias,autor_dias,tempo_leitura,autor_pag_por_hora,autor_terminaem);
                fclose(p);
                p = fopen("livros_cabecalho.txt","r");
				if (p == NULL)
                {
                	p = fopen("livros_cabecalho.txt","w");
                	fclose(p);
                	p = fopen("livros_cabecalho.txt","r");
            	}
				i=0;

				while(fgets(detTAM,70,p) != NULL)
                {
                	i++;
				}

                fclose(p);
                p = fopen("livros_cabecalho.txt","a");
                fprintf(p,"%ld - (%.1f dias -> %.2f hrs/dia -> %d -> %d/%d -> %s) %s\n",(long) tempo_log,tempo_individual,tempo_leitura,ipag,ipag,tpag,sprogresso,livro);
				Sleep(300);
                printf("\nProcessando .");
                Sleep(400);
                printf(" .");
                Sleep(500);
                printf(" .");
                printf("\nLivro cadastrado com sucesso!\n");
                fclose(p);
                break;
            case 2:
                time(&tempo_log);
				system("cls");
                p = fopen("livros_cabecalho.txt","r");
                i=0;
                while(!feof(p))
                {
                    fscanf(p,"%ld - (%f dias -> %f hrs/dia -> %d -> %d/%d -> %s",&livros_cadastrados[i].tempo_log,&livros_cadastrados[i].tempo_individual,&livros_cadastrados[i].tempo_leitura,&livros_cadastrados[i].pag_inicial,&livros_cadastrados[i].pag_atual,&livros_cadastrados[i].pag_final,stringboba);
                    fgets(livros_cadastrados[i].nome,50,p);
                    livros_cadastrados[i].nome[strlen(livros_cadastrados[i].nome) -1] = '\0';
                    i++;
                }
                printf("===== LIVROS CADASTRADOS =====\n");
                cont = i-1;
				for(j=0;j<cont;j++)
                {
                    printf("    %d - %s\n",j+1,livros_cadastrados[j].nome);
                }
                
                while(y == 'n')
                {
					printf("\nDigite o numero do livro que deseja atualizar o progresso: ");
					scanf("%d",&livro_escolhido);
					printf("Opcao escolhida: %s\n\nSe esta correto digite 'y' para sim ou 'n' para nao: ", livros_cadastrados[livro_escolhido -1].nome);
					scanf(" %c",&y);
					
				}
				dias_decorridos = ((long) tempo_log - livros_cadastrados[livro_escolhido -1].tempo_log) / 86400.0;
				system("cls");
				printf("===== %s =====\n\n",livros_cadastrados[livro_escolhido -1].nome);
				printf("Digite a pagina que voce parou deste livro: ");
				scanf("%d",&livros_cadastrados[livro_escolhido -1].pag_atual);
                fclose(p);
				p = fopen("livros.txt","w");
                q = fopen("livros_cabecalho.txt","w");
                for(w=0;w<cont;w++)
				{
					j=0;
					progresso = (float) 100* livros_cadastrados[w].pag_atual / livros_cadastrados[w].pag_final;
                	sprintf(sprogresso,"%.2f",progresso);
                	strcat(sprogresso,"%");
                	fprintf(p,"- %s:\n\n      Inicio da Leitura: %s      Pagina Inicial: %d\n      Paginas lidas: %d\n      Paginas totais: %d\n      Progresso: %s\n\n",livros_cadastrados[w].nome,asctime (timeinfo),livros_cadastrados[w].pag_inicial,livros_cadastrados[w].pag_atual,livros_cadastrados[w].pag_final,sprogresso);
					autor_dias = (livros_cadastrados[w].pag_final - livros_cadastrados[w].pag_inicial) / 30.0;
               	 	autor_pag_por_hora =  30.0 / livros_cadastrados[w].tempo_leitura;
                	for (i=5;i<=20;i++)
                	{
                    	tempos_sugeridos[j] = (float) i * livros_cadastrados[w].tempo_individual / 10;
                    	paginas_por_dia[j] = (livros_cadastrados[w].pag_final - livros_cadastrados[w].pag_inicial) / tempos_sugeridos[j];
                    	paginas_por_hora[j] = paginas_por_dia[j] / livros_cadastrados[w].tempo_leitura;
                    	j++;
               	 	}
               	 	autor_atual = dias_decorridos * 30 + livros_cadastrados[w].pag_inicial;
               	 	autor_terminaem = (livros_cadastrados[w].pag_final - livros_cadastrados[w].pag_atual) / 30.0;
               	 	autor_terminariaem = (livros_cadastrados[w].pag_final - autor_atual) / 30.0;
                	fprintf(p,"   Relatorio: Para voce concluir a leitura, iremos sugerir a voce um plano com dias proximos do seu prazo determinado.\n");
                	for(i=0;i<=15;i++)
                	{
						paginas_otimas = dias_decorridos * paginas_por_dia[i];
                        atual = dias_decorridos * paginas_por_dia[i] + livros_cadastrados[w].pag_inicial;
                    	terminaem = (livros_cadastrados[w].pag_final - livros_cadastrados[w].pag_atual) / paginas_por_dia[i];
                        terminariaem = (livros_cadastrados[w].pag_final - atual) / paginas_por_dia[i];
                        if (i!=5) // Pois quando i é igual a 10 => j era igual 5.
                    	{
                    	    fprintf(p,"      - Plano de %.1f dias:\n        * Para ler o livro em %.1f dias voce devera ler %.1f paginas por dia ou dentro do seu planejamento diario com (%.1f horas/dia) teriam de ser lidas %.1f paginas por hora.\n\n        * Paginas Lidas: %d\n        * Paginas que deveriam ter sido lidas: %.1f\n        * Termina em %.1f dias.\n        * Era pra terminar em %.1f dias.\n",tempos_sugeridos[i],tempos_sugeridos[i],paginas_por_dia[i],livros_cadastrados[w].tempo_leitura,paginas_por_hora[i],livros_cadastrados[w].pag_atual,paginas_otimas,terminaem,terminariaem);
                            if (terminaem >= terminariaem)
                            {
                                if (terminaem - terminariaem >= 1.0)
                                {
                                    fprintf(p,"        * Resumo: Voce esta %.1f dias abaixo do prazo determinado!\n\n",terminaem - terminariaem);
                                }
                                else
                                {
                                    fprintf(p,"        * Resumo: Voce esta dentro do prazo determinado!\n\n");
                                }
                            }
                            else
                            {
                                if (terminariaem - terminaem >= 1.0)
                                {
                                    fprintf(p,"        * Resumo: Voce esta %.1f dias acima do prazo determinado!\n\n",terminariaem - terminaem);
                                }
                                else
                                {
                                    fprintf(p,"        * Resumo: Voce esta dentro do prazo determinado!\n\n");
                                }
                            }
                    	}
                    	else
                    	{
                    	    fprintf(p,"      - Plano de %.1f dias (Tempo determinado pelo usuario):\n        * Para ler o livro em %.1f dias voce devera ler %.1f paginas por dia ou dentro do seu planejamento diario com (%.1f horas/dia) teriam de ser lidas %.1f paginas por hora.\n\n        * Paginas Lidas: %d.\n        * Paginas que deveriam ter sido lidas: %.1f.\n        * Termina em %.1f dias.\n        * Era pra terminar em %.1f dias.\n",tempos_sugeridos[i],tempos_sugeridos[i],paginas_por_dia[i],livros_cadastrados[w].tempo_leitura,paginas_por_hora[i],livros_cadastrados[w].pag_atual,paginas_otimas,terminaem,terminariaem);
                            if (terminaem >= terminariaem)
                            {
                                if (terminaem - terminariaem >= 1.0)
                                {
                                    fprintf(p,"        * Resumo: Voce esta %.1f dias abaixo do prazo determinado!\n\n",terminaem - terminariaem);
                                }
                                else
                                {
                                    fprintf(p,"        * Resumo: Voce esta dentro do prazo determinado!\n\n");
                                }
                            }
                            else
                            {
                                if (terminariaem - terminaem >= 1.0)
                                {
                                    fprintf(p,"        * Resumo: Voce esta %.1f dias acima do prazo determinado!\n\n",terminariaem - terminaem);
                                }
                                else
                                {
                                	fprintf(p,"        * Resumo: Voce esta dentro do prazo determinado!\n\n");
                                }
                            }
                    	}
                	}
                	fprintf(p,"      - Recomendado pelo autor (Plano de %.1f dias):\n        * Para ler o livro em %.1f dias voce devera ler 30.0 paginas por dia ou dentro do seu planejamento diario com (%.1f horas/dia) teriam de ser lidas %.1f paginas por hora.\n\n        * Paginas Lidas: %d.\n        * Paginas que deveriam ter sido lidas: %.1f.\n        * Termina em %.1f dias.\n        * Era pra terminar em %.1f dias.\n", autor_dias,autor_dias,livros_cadastrados[w].tempo_leitura,autor_pag_por_hora,livros_cadastrados[w].pag_atual,paginas_otimas,autor_terminaem,autor_terminariaem);
                    if (autor_terminaem >= autor_terminariaem)
                    {
                        if (autor_terminaem - autor_terminariaem >= 1.0)
                        {
                            fprintf(p,"        * Resumo: Voce esta %.1f dias abaixo do prazo determinado!\n\n\n",autor_terminaem - autor_terminariaem);
                        }
                        else
                        {
                            fprintf(p,"        * Resumo: Voce esta dentro do prazo determinado!\n\n\n");
                        }
                    }
                    else
                    {
                        if (autor_terminariaem - autor_terminaem >= 1.0)
                        {
                            fprintf(p,"        * Resumo: Voce esta %.1f dias acima do prazo determinado!\n\n\n",autor_terminariaem - autor_terminaem);
                        }
                        else
                        {
                            fprintf(p,"        * Resumo: Voce esta dentro do prazo determinado!\n\n\n");
                        }
                    }
                    fprintf(q,"%ld - (%.1f dias -> %.2f hrs/dia -> %d -> %d/%d -> %s) %s\n",(long) livros_cadastrados[w].tempo_log,livros_cadastrados[w].tempo_individual,livros_cadastrados[w].tempo_leitura,livros_cadastrados[w].pag_inicial,livros_cadastrados[w].pag_atual,livros_cadastrados[w].pag_final,sprogresso,livros_cadastrados[w].nome);
            	}
            	Sleep(300);
                printf("\nProcessando .");
                Sleep(400);
                printf(" .");
                Sleep(500);
                printf(" .");
                printf("\nLivro atualizado com sucesso!\n");
                fclose(p);
                fclose(q);
				break;
            case 3:
                system("cls");
                printf("Digitos:\n\n  1: Voce podera cadastrar um livro desejado para a leitura.\n\n");
                printf("  2: Voce podera comparar seu progresso atual com o progresso que voce\n     deveria estar cumprindo atraves de cadastramentos das paginas atuais (Inacabado, ainda precisa automatizar algumas coisas).\n     {\n          EM DESENVOLVIMENTO\n     }\n\n");
                printf("  3: Se voce esta lendo isso agora, creio que voce ja sabe usar o digito 3.\n\n");
                printf("  0: Caso tenha feito seus cadastramentos e acompanhamentos, digite 0 para sair.\n\n");
                printf("  Qualquer outro digito sem ser os ditos: Ocorrera uma mensagem pedindo para\n                                          voce digitar um numero valido.\n\n");
                system("pause");
                system("cls");
                printf("===== PLANEJAMENTO DE LEITURAS =====\n");
                printf("    Digite 1 para cadastrar o livro.\n");
                printf("    Digite 2 para marcar a pagina que parou do livro.\n");
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
