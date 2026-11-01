#include <stdio.h>
 
int main() {
 
    // DADOS DOS ENCONTROS
    int codigos[5] = {1, 2, 3, 4, 5};
 
    char nomes[5][50] = {
        "Saude emocional",
        "Combate ao bullying",
        "Trabalhando a autoestima",
        "Controle da ansiedade",
        "Convivencia escolar"
    };
 
    char temas[5][30] = {
        "Saude",
        "Bullying",
        "Autoestima",
        "Ansiedade",
        "Convivencia"
    };
 
    int vagas[5] = {30, 25, 20, 30, 40};
    int inscritos[5] = {0, 0, 0, 0, 0};
 
    // INSCRICOES DO USUARIO
    int minhasInscricoes[5];
    int totalInscricoes = 0;
 
    int opcao;        // somente para o menu principal
    int resposta;     // para os submenus e confirmacoes
    int continuar = 1;
    int i, j;
    int codigo;
    int tema;
    int filtro;
    int encontrou;
    int jaInscrito;
 
    // MENU PRINCIPAL
    while (continuar == 1) {
 
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1 - Encontros disponiveis\n");
        printf("2 - Meus encontros\n");
        printf("3 - Pesquisar encontro\n");
        printf("0 - Sair\n");
 
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);
 
        switch (opcao) {
 
            // OPCAO 1 - ENCONTROS DISPONIVEIS
            case 1:
 
                encontrou = 0;
                tema = 0;
 
                printf("\nDeseja escolher um tema?\n");
                printf("1 - Sim\n");
                printf("2 - Nao\n");
                scanf("%d", &resposta);
 
                if (resposta == 1) {
 
                    printf("\nEscolha um tema:\n");
                    printf("1 - Saude\n");
                    printf("2 - Bullying\n");
                    printf("3 - Autoestima\n");
                    printf("4 - Ansiedade\n");
                    printf("5 - Convivencia\n");
 
                    scanf("%d", &tema);
 
                    if (tema < 1 || tema > 5) {
                        printf("\nTema invalido!\n");
                        break;
                    }
 
                } else if (resposta != 2) {
 
                    printf("\nOpcao invalida!\n");
                    break;
                }
 
                // Lista apenas encontros com vagas (e do tema, se escolhido)
                printf("\n===== ENCONTROS DISPONIVEIS =====\n");
 
                for (i = 0; i < 5; i++) {
 
                    if ((tema == 0 || tema - 1 == i) && inscritos[i] < vagas[i]) {
 
                        printf("\nCodigo: %d", codigos[i]);
                        printf("\nEncontro: %s", nomes[i]);
                        printf("\nVagas restantes: %d\n", vagas[i] - inscritos[i]);
 
                        encontrou = 1;
                    }
                }
 
                if (encontrou == 0) {
                    printf("\nNao ha encontros disponiveis.\n");
                    break;
                }
 
                printf("\nDigite o codigo do encontro (0 para voltar): ");
                scanf("%d", &codigo);
 
                if (codigo == 0) {
                    break;
                }
 
                encontrou = 0;
 
                for (i = 0; i < 5; i++) {
 
                    if (codigo == codigos[i]) {
 
                        encontrou = 1;
 
                        printf("\n--- DETALHES DO ENCONTRO ---\n");
                        printf("Nome: %s\n", nomes[i]);
                        printf("Tema: %s\n", temas[i]);
                        printf("Vagas: %d\n", vagas[i]);
                        printf("Inscritos: %d\n", inscritos[i]);
 
                        jaInscrito = 0;
 
                        for (j = 0; j < totalInscricoes; j++) {
                            if (minhasInscricoes[j] == codigo) {
                                jaInscrito = 1;
                            }
                        }
 
                        if (jaInscrito == 1) {
 
                            printf("\nVoce ja esta inscrito!\n");
 
                        } else if (inscritos[i] >= vagas[i]) {
 
                            printf("\nNao existem vagas disponiveis!\n");
 
                        } else {
 
                            printf("\nDeseja confirmar a inscricao?\n");
                            printf("1 - Sim\n");
                            printf("2 - Nao\n");
                            scanf("%d", &resposta);
 
                            if (resposta == 1) {
 
                                minhasInscricoes[totalInscricoes] = codigo;
                                totalInscricoes++;
                                inscritos[i]++;
 
                                printf("\nInscricao realizada com sucesso!\n");
 
                            } else {
 
                                printf("\nInscricao nao realizada.\n");
                            }
                        }
                    }
                }
 
                if (encontrou == 0) {
                    printf("\nEncontro nao encontrado!\n");
                }
 
                break;
 
 
            // OPCAO 2 - MEUS ENCONTROS
            case 2:
 
                if (totalInscricoes == 0) {
 
                    printf("\nVoce ainda nao possui inscricoes!\n");
 
                } else {
 
                    printf("\n===== MEUS ENCONTROS =====\n");
 
                    for (i = 0; i < totalInscricoes; i++) {
 
                        for (j = 0; j < 5; j++) {
 
                            if (minhasInscricoes[i] == codigos[j]) {
 
                                printf("\nCodigo: %d", codigos[j]);
                                printf("\nEncontro: %s\n", nomes[j]);
                            }
                        }
                    }
 
                    printf("\nDigite o codigo para ver os detalhes (0 para voltar): ");
                    scanf("%d", &codigo);
 
                    if (codigo != 0) {
 
                        encontrou = 0;
 
                        for (i = 0; i < totalInscricoes; i++) {
 
                            if (minhasInscricoes[i] == codigo) {
 
                                for (j = 0; j < 5; j++) {
 
                                    if (codigos[j] == codigo) {
 
                                        printf("\n--- DETALHES DO ENCONTRO ---\n");
                                        printf("Nome: %s\n", nomes[j]);
                                        printf("Tema: %s\n", temas[j]);
                                        printf("Vagas: %d\n", vagas[j]);
                                        printf("Inscritos: %d\n", inscritos[j]);
 
                                        encontrou = 1;
                                    }
                                }
                            }
                        }
 
                        if (encontrou == 0) {
                            printf("\nEncontro nao encontrado nas suas inscricoes!\n");
                        }
                    }
                }
 
                break;
 
 
            // OPCAO 3 - PESQUISAR ENCONTRO
            case 3:
 
                encontrou = 0;
 
                printf("\nPesquisar por:\n");
                printf("1 - Codigo\n");
                printf("2 - Tema\n");
                scanf("%d", &filtro);
 
                if (filtro == 1) {
 
                    printf("\nDigite o codigo: ");
                    scanf("%d", &codigo);
 
                    printf("\n===== RESULTADOS =====\n");
 
                    for (i = 0; i < 5; i++) {
                        if (codigo == codigos[i]) {
                            printf("\nCodigo: %d", codigos[i]);
                            printf("\nEncontro: %s\n", nomes[i]);
                            encontrou = 1;
                        }
                    }
 
                } else if (filtro == 2) {
 
                    printf("\nEscolha um tema:\n");
                    printf("1 - Saude\n");
                    printf("2 - Bullying\n");
                    printf("3 - Autoestima\n");
                    printf("4 - Ansiedade\n");
                    printf("5 - Convivencia\n");
 
                    scanf("%d", &tema);
 
                    if (tema < 1 || tema > 5) {
                        printf("\nTema invalido!\n");
                        break;
                    }
 
                    printf("\n===== RESULTADOS =====\n");
 
                    for (i = 0; i < 5; i++) {
                        if (i == tema - 1) {
                            printf("\nCodigo: %d", codigos[i]);
                            printf("\nEncontro: %s\n", nomes[i]);
                            encontrou = 1;
                        }
                    }
 
                } else {
 
                    printf("\nOpcao invalida!\n");
                    break;
                }
 
                if (encontrou == 0) {
                    printf("\nNenhum encontro encontrado!\n");
                    break;
                }
 
                printf("\nDigite o codigo do encontro para ver detalhes (0 para voltar): ");
                scanf("%d", &codigo);
 
                if (codigo == 0) {
                    break;
                }
 
                encontrou = 0;
 
                for (i = 0; i < 5; i++) {
 
                    if (codigo == codigos[i]) {
 
                        encontrou = 1;
 
                        printf("\n--- DETALHES DO ENCONTRO ---\n");
                        printf("Nome: %s\n", nomes[i]);
                        printf("Tema: %s\n", temas[i]);
                        printf("Vagas: %d\n", vagas[i]);
                        printf("Inscritos: %d\n", inscritos[i]);
 
                        printf("\nDeseja se inscrever?\n");
                        printf("1 - Sim\n");
                        printf("2 - Nao\n");
                        scanf("%d", &resposta);
 
                        if (resposta == 1) {
 
                            jaInscrito = 0;
 
                            for (j = 0; j < totalInscricoes; j++) {
                                if (minhasInscricoes[j] == codigo) {
                                    jaInscrito = 1;
                                }
                            }
 
                            if (jaInscrito == 1) {
 
                                printf("\nVoce ja esta inscrito!\n");
 
                            } else if (inscritos[i] >= vagas[i]) {
 
                                printf("\nNao existem vagas disponiveis!\n");
 
                            } else {
 
                                minhasInscricoes[totalInscricoes] = codigo;
                                totalInscricoes++;
                                inscritos[i]++;
 
                                printf("\nInscricao realizada com sucesso!\n");
                            }
 
                        } else {
 
                            printf("\nInscricao nao realizada.\n");
                        }
                    }
                }
 
                if (encontrou == 0) {
                    printf("\nEncontro nao encontrado!\n");
                }
 
                break;
 
 
            // SAIR
            case 0:
 
                continuar = 0;
                break;
 
 
            default:
 
                printf("\nOpcao invalida!\n");
        }
 
 
        // PERGUNTAR SE DESEJA OUTRA OPERACAO
        if (opcao != 0) {
 
            printf("\nDeseja realizar outra operacao?\n");
            printf("1 - Sim\n");
            printf("2 - Nao\n");
            scanf("%d", &continuar);
 
            if (continuar != 1) {
                continuar = 0;
            }
        }
    }
 
    printf("\nSistema encerrado!\n");
 
    return 0;
}
