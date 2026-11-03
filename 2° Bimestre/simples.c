#include <stdio.h>

#define LIMITE 50

struct Encontro {
    int codigo;
    char nome[50];
    int tema;
    char data[20];
    char horario[20];
    char local[50];
    char responsavel[50];
    int vagas;
    int inscritos;
    int presentes;
    int situacao;
};

int main() {

    struct Encontro encontros[LIMITE] = {
        {1, "Saude emocional", 1, "A definir", "A definir", "Escola", "Equipe PSE", 30, 0, 0, 1},
        {2, "Combate ao bullying", 2, "A definir", "A definir", "Escola", "Equipe PSE", 25, 0, 0, 1},
        {3, "Trabalhando a autoestima", 3, "A definir", "A definir", "Escola", "Equipe PSE", 20, 0, 0, 1},
        {4, "Controle da ansiedade", 4, "A definir", "A definir", "Escola", "Equipe PSE", 30, 0, 0, 1},
        {5, "Convivencia escolar", 5, "A definir", "A definir", "Escola", "Equipe PSE", 40, 0, 0, 1}
    };

    int minhasInscricoes[LIMITE] = {0};

    int totalEncontros = 5;
    int totalInscricoes = 0;

    int opcao = -1;
    int resposta, codigo, tema;
    int i, j, posicao, encontrou, jaInscrito;
    int filtro, novaSituacao, presentes, vagasNovas;

    while (opcao != 0) {

        printf("\n===== MENU PRINCIPAL - PSE EM ACAO =====\n");
        printf("1 - Encontros disponiveis\n");
        printf("2 - Meus encontros\n");
        printf("3 - Pesquisar encontro\n");
        printf("4 - Cancelar inscricao\n");
        printf("5 - Relatorio\n");
        printf("6 - Cadastrar ou atualizar encontro\n");
        printf("7 - Atualizar situacao do encontro\n");
        printf("8 - Registrar participantes\n");
        printf("0 - Sair\n");

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {

            /* 1 - ENCONTROS DISPONIVEIS */
            case 1:

                printf("\nDeseja escolher um tema? 1 - Sim / 2 - Nao: ");
                scanf("%d", &resposta);

                if (resposta != 1 && resposta != 2) {
                    printf("Opcao invalida!\n");
                    break;
                }

                tema = 0;

                if (resposta == 1) {
                    printf("\n1 - Saude\n");
                    printf("2 - Bullying\n");
                    printf("3 - Autoestima\n");
                    printf("4 - Ansiedade\n");
                    printf("5 - Convivencia\n");

                    printf("Escolha o tema: ");
                    scanf("%d", &tema);

                    if (tema < 1 || tema > 5) {
                        printf("Tema invalido!\n");
                        break;
                    }
                }

                encontrou = 0;

                printf("\n===== ENCONTROS DISPONIVEIS =====\n");

                for (i = 0; i < totalEncontros; i++) {

                    if (encontros[i].situacao == 1 &&
                        encontros[i].inscritos < encontros[i].vagas) {

                        if (tema == 0 || encontros[i].tema == tema) {

                            printf("Codigo: %d | %s | Vagas livres: %d\n",
                            encontros[i].codigo,
                            encontros[i].nome,
                            encontros[i].vagas - encontros[i].inscritos);

                            encontrou = 1;
                        }
                    }
                }

                if (encontrou == 0) {
                    printf("Nenhum encontro disponivel!\n");
                    break;
                }

                printf("\nDigite o codigo do encontro (0 para voltar): ");
                scanf("%d", &codigo);

                if (codigo == 0) {
                    break;
                }

                posicao = -1;

                for (i = 0; i < totalEncontros; i++) {
                    if (encontros[i].codigo == codigo) {
                        posicao = i;
                    }
                }

                if (posicao == -1) {
                    printf("Encontro inexistente!\n");
                    break;
                }

                if (encontros[posicao].situacao != 1 ||
                    encontros[posicao].inscritos >= encontros[posicao].vagas) {

                    printf("Encontro indisponivel!\n");
                    break;
                }

                if (tema != 0 && encontros[posicao].tema != tema) {
                    printf("Encontro fora do tema escolhido!\n");
                    break;
                }

                printf("\n===== DETALHES DO ENCONTRO =====\n");
                printf("Codigo: %d\n", encontros[posicao].codigo);
                printf("Nome: %s\n", encontros[posicao].nome);

                printf("Tema: ");
                if (encontros[posicao].tema == 1) printf("Saude\n");
                if (encontros[posicao].tema == 2) printf("Bullying\n");
                if (encontros[posicao].tema == 3) printf("Autoestima\n");
                if (encontros[posicao].tema == 4) printf("Ansiedade\n");
                if (encontros[posicao].tema == 5) printf("Convivencia\n");

                printf("Data: %s\n", encontros[posicao].data);
                printf("Horario: %s\n", encontros[posicao].horario);
                printf("Local: %s\n", encontros[posicao].local);
                printf("Responsavel: %s\n", encontros[posicao].responsavel);
                printf("Vagas: %d\n", encontros[posicao].vagas);
                printf("Inscritos: %d\n", encontros[posicao].inscritos);

                jaInscrito = 0;

                for (i = 0; i < totalInscricoes; i++) {
                    if (minhasInscricoes[i] == codigo) {
                        jaInscrito = 1;
                    }
                }

                if (jaInscrito == 1) {
                    printf("Voce ja esta inscrito!\n");
                    break;
                }

                if (totalInscricoes >= LIMITE) {
                    printf("Limite de inscricoes atingido!\n");
                    break;
                }

                printf("\nConfirmar inscricao? 1 - Sim / 2 - Nao: ");
                scanf("%d", &resposta);

                if (resposta == 1) {

                    minhasInscricoes[totalInscricoes] = codigo;
                    totalInscricoes++;

                    encontros[posicao].inscritos++;

                    printf("Inscricao realizada com sucesso!\n");

                } else if (resposta == 2) {
                    printf("Inscricao nao realizada.\n");
                } else {
                    printf("Opcao invalida!\n");
                }

                break;


            /* 2 - MEUS ENCONTROS */
            case 2:

                if (totalInscricoes == 0) {
                    printf("Voce nao possui inscricoes.\n");
                    break;
                }

                printf("\n===== MEUS ENCONTROS =====\n");

                for (i = 0; i < totalInscricoes; i++) {

                    for (j = 0; j < totalEncontros; j++) {

                        if (minhasInscricoes[i] == encontros[j].codigo) {
                            printf("Codigo: %d | %s\n",
                            encontros[j].codigo,
                            encontros[j].nome);
                        }
                    }
                }

                printf("\nDigite o codigo para ver os detalhes (0 para voltar): ");
                scanf("%d", &codigo);

                if (codigo == 0) {
                    break;
                }

                encontrou = 0;

                for (i = 0; i < totalInscricoes; i++) {

                    if (minhasInscricoes[i] == codigo) {

                        for (j = 0; j < totalEncontros; j++) {

                            if (encontros[j].codigo == codigo) {

                                printf("\nNome: %s\n", encontros[j].nome);
                                printf("Codigo: %d\n", encontros[j].codigo);

                                printf("Tema: ");
                                if (encontros[j].tema == 1) printf("Saude\n");
                                if (encontros[j].tema == 2) printf("Bullying\n");
                                if (encontros[j].tema == 3) printf("Autoestima\n");
                                if (encontros[j].tema == 4) printf("Ansiedade\n");
                                if (encontros[j].tema == 5) printf("Convivencia\n");

                                printf("Data: %s\n", encontros[j].data);
                                printf("Horario: %s\n", encontros[j].horario);
                                printf("Local: %s\n", encontros[j].local);
                                printf("Responsavel: %s\n", encontros[j].responsavel);
                                printf("Vagas: %d\n", encontros[j].vagas);

                                encontrou = 1;
                            }
                        }
                    }
                }

                if (encontrou == 0) {
                    printf("Encontro nao encontrado nas suas inscricoes!\n");
                }

                break;


            /* 3 - PESQUISAR ENCONTRO */
            case 3:

                printf("\nPesquisar por:\n");
                printf("1 - Codigo\n");
                printf("2 - Tema\n");
                scanf("%d", &filtro);

                if (filtro == 1) {

                    printf("Digite o codigo: ");
                    scanf("%d", &codigo);

                    encontrou = 0;

                    for (i = 0; i < totalEncontros; i++) {

                        if (encontros[i].codigo == codigo) {

                            printf("\nCodigo: %d\n", encontros[i].codigo);
                            printf("Nome: %s\n", encontros[i].nome);
                            printf("Data: %s\n", encontros[i].data);
                            printf("Horario: %s\n", encontros[i].horario);
                            printf("Local: %s\n", encontros[i].local);

                            encontrou = 1;
                        }
                    }

                    if (encontrou == 0) {
                        printf("Encontro nao encontrado!\n");
                    }

                } else if (filtro == 2) {

                    printf("\n1 - Saude\n");
                    printf("2 - Bullying\n");
                    printf("3 - Autoestima\n");
                    printf("4 - Ansiedade\n");
                    printf("5 - Convivencia\n");

                    printf("Escolha o tema: ");
                    scanf("%d", &tema);

                    if (tema < 1 || tema > 5) {
                        printf("Tema invalido!\n");
                        break;
                    }

                    encontrou = 0;

                    for (i = 0; i < totalEncontros; i++) {

                        if (encontros[i].tema == tema) {

                            printf("Codigo: %d | %s\n",
                            encontros[i].codigo,
                            encontros[i].nome);

                            encontrou = 1;
                        }
                    }

                    if (encontrou == 0) {
                        printf("Nenhum encontro encontrado!\n");
                    }

                } else {
                    printf("Filtro invalido!\n");
                }

                break;


            /* 4 - CANCELAR INSCRICAO */
            case 4:

                if (totalInscricoes == 0) {
                    printf("Voce nao possui inscricoes.\n");
                    break;
                }

                printf("\n===== CANCELAR INSCRICAO =====\n");

                for (i = 0; i < totalInscricoes; i++) {

                    for (j = 0; j < totalEncontros; j++) {

                        if (minhasInscricoes[i] == encontros[j].codigo) {
                            printf("Codigo: %d | %s\n",
                            encontros[j].codigo,
                            encontros[j].nome);
                        }
                    }
                }

                printf("Digite o codigo para cancelar (0 para voltar): ");
                scanf("%d", &codigo);

                if (codigo == 0) {
                    break;
                }

                posicao = -1;
                jaInscrito = 0;

                for (i = 0; i < totalEncontros; i++) {

                    if (encontros[i].codigo == codigo) {
                        posicao = i;
                    }
                }

                for (i = 0; i < totalInscricoes; i++) {

                    if (minhasInscricoes[i] == codigo) {
                        jaInscrito = 1;
                    }
                }

                if (jaInscrito == 0) {
                    printf("Voce nao esta inscrito neste encontro!\n");
                    break;
                }

                if (posicao == -1) {
                    printf("Encontro inexistente!\n");
                    break;
                }

                if (encontros[posicao].situacao != 1) {
                    printf("Nao pode cancelar inscricao de encontro finalizado!\n");
                    break;
                }

                printf("Confirmar cancelamento? 1 - Sim / 2 - Nao: ");
                scanf("%d", &resposta);

                if (resposta == 1) {

                    for (i = 0; i < totalInscricoes; i++) {

                        if (minhasInscricoes[i] == codigo) {

                            for (j = i; j < totalInscricoes - 1; j++) {
                                minhasInscricoes[j] = minhasInscricoes[j + 1];
                            }

                            totalInscricoes--;
                            encontros[posicao].inscritos--;

                            printf("Inscricao cancelada! Vaga liberada.\n");

                            break;
                        }
                    }

                } else if (resposta == 2) {
                    printf("Cancelamento nao realizado.\n");
                } else {
                    printf("Opcao invalida!\n");
                }

                break;


            /* 5 - RELATORIO */
            case 5:

                {
                    int planejados = 0;
                    int realizados = 0;
                    int cancelados = 0;
                    int somaInscritos = 0;
                    int somaPresentes = 0;

                    for (i = 0; i < totalEncontros; i++) {

                        if (encontros[i].situacao == 1) planejados++;
                        if (encontros[i].situacao == 2) realizados++;
                        if (encontros[i].situacao == 3) cancelados++;

                        somaInscritos += encontros[i].inscritos;
                        somaPresentes += encontros[i].presentes;
                    }

                    printf("\n===== RELATORIO =====\n");
                    printf("Total de encontros: %d\n", totalEncontros);
                    printf("Planejados: %d\n", planejados);
                    printf("Realizados: %d\n", realizados);
                    printf("Cancelados: %d\n", cancelados);
                    printf("Total de inscricoes: %d\n", somaInscritos);
                    printf("Total de participantes presentes: %d\n", somaPresentes);

                    if (somaInscritos > 0) {
                        printf("Percentual de presenca: %.1f%%\n",
                        100.0 * somaPresentes / somaInscritos);
                    } else {
                        printf("Percentual de presenca: 0.0%%\n");
                    }
                }

                break;


            /* 6 - CADASTRAR OU ATUALIZAR ENCONTRO */
            case 6:

                printf("\n1 - Cadastrar encontro\n");
                printf("2 - Atualizar encontro\n");
                printf("Escolha: ");
                scanf("%d", &resposta);

                if (resposta == 1) {

                    if (totalEncontros >= LIMITE) {
                        printf("Limite de encontros atingido!\n");
                        break;
                    }

                    i = totalEncontros;

                    encontros[i].codigo = totalEncontros + 1;

                    printf("Nome: ");
                    scanf(" %49[^\n]", encontros[i].nome);

                    printf("\n1 - Saude\n");
                    printf("2 - Bullying\n");
                    printf("3 - Autoestima\n");
                    printf("4 - Ansiedade\n");
                    printf("5 - Convivencia\n");

                    printf("Escolha o tema: ");
                    scanf("%d", &tema);

                    if (tema < 1 || tema > 5) {
                        printf("Tema invalido! Cadastro nao realizado.\n");
                        break;
                    }

                    encontros[i].tema = tema;

                    printf("Data: ");
                    scanf(" %19[^\n]", encontros[i].data);

                    printf("Horario: ");
                    scanf(" %19[^\n]", encontros[i].horario);

                    printf("Local: ");
                    scanf(" %49[^\n]", encontros[i].local);

                    printf("Responsavel: ");
                    scanf(" %49[^\n]", encontros[i].responsavel);

                    printf("Numero de vagas: ");
                    scanf("%d", &encontros[i].vagas);

                    if (encontros[i].vagas <= 0) {
                        printf("Quantidade de vagas invalida!\n");
                        break;
                    }

                    encontros[i].inscritos = 0;
                    encontros[i].presentes = 0;
                    encontros[i].situacao = 1;

                    totalEncontros++;

                    printf("Encontro cadastrado com sucesso!\n");
                    printf("Codigo: %d\n", encontros[i].codigo);

                } else if (resposta == 2) {

                    printf("Codigo do encontro para atualizar: ");
                    scanf("%d", &codigo);

                    posicao = -1;

                    for (i = 0; i < totalEncontros; i++) {

                        if (encontros[i].codigo == codigo) {
                            posicao = i;
                        }
                    }

                    if (posicao == -1) {
                        printf("Encontro inexistente!\n");
                        break;
                    }

                    if (encontros[posicao].situacao != 1) {
                        printf("So encontros planejados podem ser editados!\n");
                        break;
                    }

                    printf("Nova quantidade de vagas: ");
                    scanf("%d", &vagasNovas);

                    if (vagasNovas < encontros[posicao].inscritos || vagasNovas <= 0) {
                        printf("Quantidade de vagas invalida!\n");
                        break;
                    }

                    printf("Novo nome: ");
                    scanf(" %49[^\n]", encontros[posicao].nome);

                    printf("\n1 - Saude\n");
                    printf("2 - Bullying\n");
                    printf("3 - Autoestima\n");
                    printf("4 - Ansiedade\n");
                    printf("5 - Convivencia\n");

                    printf("Novo tema: ");
                    scanf("%d", &tema);

                    if (tema < 1 || tema > 5) {
                        printf("Tema invalido!\n");
                        break;
                    }

                    encontros[posicao].tema = tema;

                    printf("Nova data: ");
                    scanf(" %19[^\n]", encontros[posicao].data);

                    printf("Novo horario: ");
                    scanf(" %19[^\n]", encontros[posicao].horario);

                    printf("Novo local: ");
                    scanf(" %49[^\n]", encontros[posicao].local);

                    printf("Novo responsavel: ");
                    scanf(" %49[^\n]", encontros[posicao].responsavel);

                    encontros[posicao].vagas = vagasNovas;

                    printf("Encontro atualizado com sucesso!\n");

                } else {
                    printf("Opcao invalida!\n");
                }

                break;


            /* 7 - ATUALIZAR SITUACAO */
            case 7:

                printf("Codigo do encontro: ");
                scanf("%d", &codigo);

                posicao = -1;

                for (i = 0; i < totalEncontros; i++) {

                    if (encontros[i].codigo == codigo) {
                        posicao = i;
                    }
                }

                if (posicao == -1) {
                    printf("Encontro inexistente!\n");
                    break;
                }

                printf("\nSituacao atual: ");

                if (encontros[posicao].situacao == 1) printf("Planejado\n");
                if (encontros[posicao].situacao == 2) printf("Realizado\n");
                if (encontros[posicao].situacao == 3) printf("Cancelado\n");

                printf("\nNova situacao:\n");
                printf("1 - Planejado\n");
                printf("2 - Realizado\n");
                printf("3 - Cancelado\n");

                scanf("%d", &novaSituacao);

                if (novaSituacao < 1 || novaSituacao > 3) {
                    printf("Situacao invalida!\n");
                    break;
                }

                if (encontros[posicao].situacao != 1) {
                    printf("Encontro finalizado nao pode mudar de situacao!\n");
                    break;
                }

                encontros[posicao].situacao = novaSituacao;

                printf("Situacao atualizada com sucesso!\n");

                break;


            /* 8 - REGISTRAR PARTICIPANTES */
            case 8:

                printf("Codigo do encontro: ");
                scanf("%d", &codigo);

                posicao = -1;

                for (i = 0; i < totalEncontros; i++) {

                    if (encontros[i].codigo == codigo) {
                        posicao = i;
                    }
                }

                if (posicao == -1) {
                    printf("Encontro inexistente!\n");
                    break;
                }

                if (encontros[posicao].situacao != 2) {
                    printf("So pode registrar presentes em encontro realizado!\n");
                    break;
                }

                printf("Total de inscritos: %d\n", encontros[posicao].inscritos);

                printf("Quantidade de participantes presentes: ");
                scanf("%d", &presentes);

                if (presentes < 0 || presentes > encontros[posicao].inscritos) {

                    printf("Quantidade invalida! Deve ser de 0 ate %d.\n",
                    encontros[posicao].inscritos);

                } else {

                    encontros[posicao].presentes = presentes;

                    printf("Participantes registrados com sucesso!\n");
                }

                break;


            /* 0 - SAIR */
            case 0:

                printf("\nSistema encerrado!\n");

                break;


            default:

                printf("\nOpcao invalida!\n");
        }
    }

    return 0;
}
