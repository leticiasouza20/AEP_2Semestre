#include <stdio.h>
#include <string.h>

#define LIMITE 50

struct Encontro {
    int codigo;
    char nome[50];
    char tema[30];
    char data[20];
    char horario[20];
    char local[50];
    char responsavel[50];
    int vagas;
    int inscritos;
    int presentes;
    int situacao; /* 1 planejado, 2 realizado, 3 cancelado */
};

/* Funcao simples para mostrar os dados de um encontro. */
void mostrarEncontro(struct Encontro e) {
    printf("\nCodigo: %d\n", e.codigo);
    printf("Nome: %s\n", e.nome);
    printf("Tema: %s\n", e.tema);
    printf("Data: %s\n", e.data);
    printf("Horario: %s\n", e.horario);
    printf("Local: %s\n", e.local);
    printf("Responsavel: %s\n", e.responsavel);
    printf("Vagas: %d\n", e.vagas);
    printf("Inscritos: %d\n", e.inscritos);
    printf("Presentes: %d\n", e.presentes);
    if (e.situacao == 1) {
        printf("Situacao: Planejado\n");
    }
    if (e.situacao == 2) {
        printf("Situacao: Realizado\n");
    }
    if (e.situacao == 3) {
        printf("Situacao: Cancelado\n");
    }
}

/* Evita que letras no lugar de numeros travem o menu. */
int lerNumero() {
    int numero;
    int resultado;
    int letra;
    resultado = scanf("%d", &numero);
    while ((letra = getchar()) != '\n' && letra != EOF) {
        if (letra != ' ' && letra != '\t') resultado = 0;
    }
    if (resultado == EOF) {
        return 0;
    }
    if (resultado != 1) {
        return -1;
    }
    return numero;
}

int main() {
    struct Encontro encontros[LIMITE] = {
        {1, "Saude emocional", "Saude", "A definir", "A definir", "Escola", "Equipe PSE", 30, 0, 0, 1},
        {2, "Combate ao bullying", "Bullying", "A definir", "A definir", "Escola", "Equipe PSE", 25, 0, 0, 1},
        {3, "Trabalhando a autoestima", "Autoestima", "A definir", "A definir", "Escola", "Equipe PSE", 20, 0, 0, 1},
        {4, "Controle da ansiedade", "Ansiedade", "A definir", "A definir", "Escola", "Equipe PSE", 30, 0, 0, 1},
        {5, "Convivencia escolar", "Convivencia", "A definir", "A definir", "Escola", "Equipe PSE", 40, 0, 0, 1}
    };
    int totalEncontros = 5;
    int minhasInscricoes[LIMITE] = {0};
    int totalInscricoes = 0;
    int opcao = -1, resposta, codigo, i, j, posicao, encontrou, jaInscrito;
    int tema, filtro, novaSituacao, presentes, vagasNovas;
    int planejados, realizados, cancelados, somaInscritos, somaPresentes;

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
        opcao = lerNumero();

        switch (opcao) {

            case 1:
                printf("\nDeseja escolher um tema? 1 - Sim / 2 - Nao: ");
                resposta = lerNumero();
                if (resposta != 1 && resposta != 2) {
                    printf("Opcao invalida!\n");
                    break;
                }
                tema = 0;
                if (resposta == 1) {
                    printf("1 - Saude\n2 - Bullying\n3 - Autoestima\n4 - Ansiedade\n5 - Convivencia\n");
                    printf("Escolha o tema: ");
                    tema = lerNumero();
                    if (tema < 1 || tema > 5) {
                        printf("Tema invalido!\n");
                        break;
                    }
                }
                encontrou = 0;
                printf("\n===== ENCONTROS DISPONIVEIS =====\n");
                for (i = 0; i < totalEncontros; i++) {
                    if (encontros[i].situacao == 1 && encontros[i].inscritos < encontros[i].vagas) {
                        if (tema == 0 || (tema == 1 && strcmp(encontros[i].tema, "Saude") == 0) ||
                            (tema == 2 && strcmp(encontros[i].tema, "Bullying") == 0) ||
                            (tema == 3 && strcmp(encontros[i].tema, "Autoestima") == 0) ||
                            (tema == 4 && strcmp(encontros[i].tema, "Ansiedade") == 0) ||
                            (tema == 5 && strcmp(encontros[i].tema, "Convivencia") == 0)) {
                            printf("Codigo: %d | %s | Vagas livres: %d\n", encontros[i].codigo,
                                   encontros[i].nome, encontros[i].vagas - encontros[i].inscritos);
                            encontrou = 1;
                        }
                    }
                }
                if (encontrou == 0) {
                    printf("Nenhum encontro disponivel.\n");
                    break;
                }
                printf("Codigo do encontro (0 para voltar): ");
                codigo = lerNumero();
                if (codigo == 0) break;
                posicao = -1;
                for (i = 0; i < totalEncontros; i++) {
                    if (encontros[i].codigo == codigo) posicao = i;
                }
                if (posicao == -1) {
                    printf("Encontro inexistente!\n");
                    break;
                }
                if (encontros[posicao].situacao != 1 || encontros[posicao].inscritos >= encontros[posicao].vagas) {
                    printf("Encontro indisponivel!\n"); break;
                }
                if (tema != 0) {
                    encontrou = 0;
                    if (tema == 1 && strcmp(encontros[posicao].tema, "Saude") == 0) encontrou = 1;
                    if (tema == 2 && strcmp(encontros[posicao].tema, "Bullying") == 0) encontrou = 1;
                    if (tema == 3 && strcmp(encontros[posicao].tema, "Autoestima") == 0) encontrou = 1;
                    if (tema == 4 && strcmp(encontros[posicao].tema, "Ansiedade") == 0) encontrou = 1;
                    if (tema == 5 && strcmp(encontros[posicao].tema, "Convivencia") == 0) encontrou = 1;
                    if (encontrou == 0) {
                        printf("Encontro fora do tema escolhido!\n");
                        break;
                    }
                }
                mostrarEncontro(encontros[posicao]);
                jaInscrito = 0;
                for (i = 0; i < totalInscricoes; i++) {
                    if (minhasInscricoes[i] == codigo) jaInscrito = 1;
                }
                if (jaInscrito == 1) {
                    printf("Voce ja esta inscrito!\n");
                    break;
                }
                if (totalInscricoes >= LIMITE) {
                    printf("Limite de inscricoes atingido!\n");
                    break;
                }
                printf("Confirmar inscricao? 1 - Sim / 2 - Nao: ");
                resposta = lerNumero();
                if (resposta == 1) {
                    minhasInscricoes[totalInscricoes] = codigo;
                    totalInscricoes++;
                    encontros[posicao].inscritos++;
                    printf("Inscricao realizada com sucesso!\n");
                } else if (resposta == 2) printf("Inscricao nao realizada.\n");
                else printf("Opcao invalida!\n");
                break;

            case 2:
                if (totalInscricoes == 0) {
                    printf("Voce nao possui inscricoes.\n");
                    break;
                }
                printf("\n===== MEUS ENCONTROS =====\n");
                for (i = 0; i < totalInscricoes; i++) {
                    for (j = 0; j < totalEncontros; j++) {
                        if (minhasInscricoes[i] == encontros[j].codigo)
                            printf("Codigo: %d | %s\n", encontros[j].codigo, encontros[j].nome);
                    }
                }
                printf("Codigo para ver detalhes (0 para voltar): ");
                codigo = lerNumero();
                if (codigo == 0) break;
                encontrou = 0;
                for (i = 0; i < totalInscricoes; i++) {
                    if (minhasInscricoes[i] == codigo) {
                        for (j = 0; j < totalEncontros; j++) {
                            if (encontros[j].codigo == codigo) {
                                mostrarEncontro(encontros[j]);
                                encontrou = 1;
                            }
                        }
                    }
                }
                if (encontrou == 0) {
                    printf("Encontro nao encontrado nas suas inscricoes!\n");
                }
                break;

            case 3:
                printf("\nPesquisar por: 1 - Codigo / 2 - Tema: ");
                filtro = lerNumero();
                if (filtro != 1 && filtro != 2) {
                    printf("Filtro invalido!\n");
                    break;
                }
                encontrou = 0;
                if (filtro == 1) {
                    printf("Digite o codigo: ");
                    codigo = lerNumero();
                    for (i = 0; i < totalEncontros; i++) {
                        if (encontros[i].codigo == codigo) {
                            mostrarEncontro(encontros[i]);
                            encontrou = 1;
                        }
                    }
                } else {
                    printf("1 - Saude\n2 - Bullying\n3 - Autoestima\n4 - Ansiedade\n5 - Convivencia\n");
                    printf("Escolha o tema: ");
                    tema = lerNumero();
                    if (tema < 1 || tema > 5) {
                        printf("Tema invalido!\n");
                        break;
                    }
                    for (i = 0; i < totalEncontros; i++) {
                        if ((tema == 1 && strcmp(encontros[i].tema, "Saude") == 0) ||
                            (tema == 2 && strcmp(encontros[i].tema, "Bullying") == 0) ||
                            (tema == 3 && strcmp(encontros[i].tema, "Autoestima") == 0) ||
                            (tema == 4 && strcmp(encontros[i].tema, "Ansiedade") == 0) ||
                            (tema == 5 && strcmp(encontros[i].tema, "Convivencia") == 0)) {
                            printf("Codigo: %d | %s\n", encontros[i].codigo, encontros[i].nome);
                            encontrou = 1;
                        }
                    }
                    if (encontrou == 1) {
                        printf("Codigo para ver detalhes (0 para voltar): ");
                        codigo = lerNumero();
                        if (codigo == 0) break;
                        encontrou = 0;
                        for (i = 0; i < totalEncontros; i++) {
                            if (encontros[i].codigo == codigo) {
                                if ((tema == 1 && strcmp(encontros[i].tema, "Saude") == 0) ||
                                    (tema == 2 && strcmp(encontros[i].tema, "Bullying") == 0) ||
                                    (tema == 3 && strcmp(encontros[i].tema, "Autoestima") == 0) ||
                                    (tema == 4 && strcmp(encontros[i].tema, "Ansiedade") == 0) ||
                                    (tema == 5 && strcmp(encontros[i].tema, "Convivencia") == 0)) {
                                    mostrarEncontro(encontros[i]);
                                    encontrou = 1;
                                }
                            }
                        }
                    }
                }
                if (encontrou == 0) {
                    printf("Nenhum encontro encontrado!\n");
                }
                break;

            case 4:
                if (totalInscricoes == 0) {
                    printf("Voce nao possui inscricoes.\n");
                    break;
                }
                printf("\n===== CANCELAR INSCRICAO =====\n");
                for (i = 0; i < totalInscricoes; i++) {
                    for (j = 0; j < totalEncontros; j++) {
                        if (minhasInscricoes[i] == encontros[j].codigo)
                            printf("Codigo: %d | %s\n", encontros[j].codigo, encontros[j].nome);
                    }
                }
                printf("Codigo para cancelar (0 para voltar): ");
                codigo = lerNumero();
                if (codigo == 0) break;
                jaInscrito = 0;
                for (i = 0; i < totalInscricoes; i++) {
                    if (minhasInscricoes[i] == codigo) jaInscrito = 1;
                }
                if (jaInscrito == 0) {
                    printf("Voce nao esta inscrito neste encontro!\n");
                    break;
                }
                posicao = -1;
                for (i = 0; i < totalEncontros; i++) {
                    if (encontros[i].codigo == codigo) posicao = i;
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
                resposta = lerNumero();
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
                } else if (resposta == 2) printf("Cancelamento nao realizado.\n");
                else printf("Opcao invalida!\n");
                break;

            case 5:
                planejados = 0;
                realizados = 0;
                cancelados = 0;
                somaInscritos = 0;
                somaPresentes = 0;
                for (i = 0; i < totalEncontros; i++) {
                    if (encontros[i].situacao == 1) planejados++;
                    if (encontros[i].situacao == 2) realizados++;
                    if (encontros[i].situacao == 3) cancelados++;
                    somaInscritos = somaInscritos + encontros[i].inscritos;
                    somaPresentes = somaPresentes + encontros[i].presentes;
                }
                printf("\n===== RELATORIO =====\n");
                printf("Total de encontros: %d\n", totalEncontros);
                printf("Planejados: %d\n", planejados);
                printf("Realizados: %d\n", realizados);
                printf("Cancelados: %d\n", cancelados);
                printf("Total de inscricoes: %d\n", somaInscritos);
                printf("Total de participantes presentes: %d\n", somaPresentes);
                if (somaInscritos > 0) {
                    printf("Percentual de presenca: %.1f%%\n", 100.0 * somaPresentes / somaInscritos);
                } else {
                    printf("Percentual de presenca: 0.0%%\n");
                }
                break;

            case 6:
                printf("\n1 - Cadastrar encontro\n2 - Atualizar encontro\nEscolha: ");
                resposta = lerNumero();
                if (resposta == 1) {
                    if (totalEncontros >= LIMITE) {
                        printf("Limite de encontros atingido!\n");
                        break;
                    }
                    i = totalEncontros;
                    encontros[i].codigo = totalEncontros + 1;
                    printf("Nome: "); scanf(" %49[^\n]", encontros[i].nome);
                    printf("Tema: 1 - Saude / 2 - Bullying / 3 - Autoestima / 4 - Ansiedade / 5 - Convivencia: ");
                    tema = lerNumero();
                    if (tema < 1 || tema > 5) {
                        printf("Tema invalido. Cadastro nao realizado!\n");
                        break;
                    }
                    if (tema == 1) strcpy(encontros[i].tema, "Saude");
                    if (tema == 2) strcpy(encontros[i].tema, "Bullying");
                    if (tema == 3) strcpy(encontros[i].tema, "Autoestima");
                    if (tema == 4) strcpy(encontros[i].tema, "Ansiedade");
                    if (tema == 5) strcpy(encontros[i].tema, "Convivencia");
                    printf("Data: "); scanf(" %19[^\n]", encontros[i].data);
                    printf("Horario: "); scanf(" %19[^\n]", encontros[i].horario);
                    printf("Local: "); scanf(" %49[^\n]", encontros[i].local);
                    printf("Responsavel: "); scanf(" %49[^\n]", encontros[i].responsavel);
                    printf("Numero de vagas: ");
                    encontros[i].vagas = lerNumero();
                    if (encontros[i].vagas <= 0) {
                        printf("Quantidade de vagas invalida!\n");
                        break;
                    }
                    encontros[i].inscritos = 0;
                    encontros[i].presentes = 0;
                    encontros[i].situacao = 1;
                    totalEncontros++;
                    printf("Encontro cadastrado! Codigo: %d\n", encontros[i].codigo);
                } else if (resposta == 2) {
                    printf("Codigo do encontro para atualizar: ");
                    codigo = lerNumero();
                    posicao = -1;
                    for (i = 0; i < totalEncontros; i++) {
                        if (encontros[i].codigo == codigo) posicao = i;
                    }
                    if (posicao == -1) {
                        printf("Encontro inexistente!\n");
                        break;
                    }
                    if (encontros[posicao].situacao != 1) {
                        printf("So encontros planejados podem ser editados!\n");
                        break;
                    }
                    mostrarEncontro(encontros[posicao]);
                    printf("Nova quantidade de vagas: ");
                    vagasNovas = lerNumero();
                    if (vagasNovas < encontros[posicao].inscritos || vagasNovas <= 0) {
                        printf("Vagas invalidas! Nao pode ser menor que os inscritos.\n");
                        break;
                    }
                    printf("Novo nome: "); scanf(" %49[^\n]", encontros[posicao].nome);
                    printf("Novo tema: 1 - Saude / 2 - Bullying / 3 - Autoestima / 4 - Ansiedade / 5 - Convivencia: ");
                    tema = lerNumero();
                    if (tema < 1 || tema > 5) {
                        printf("Tema invalido!\n");
                        break;
                    }
                    if (tema == 1) strcpy(encontros[posicao].tema, "Saude");
                    if (tema == 2) strcpy(encontros[posicao].tema, "Bullying");
                    if (tema == 3) strcpy(encontros[posicao].tema, "Autoestima");
                    if (tema == 4) strcpy(encontros[posicao].tema, "Ansiedade");
                    if (tema == 5) strcpy(encontros[posicao].tema, "Convivencia");
                    printf("Nova data: "); scanf(" %19[^\n]", encontros[posicao].data);
                    printf("Novo horario: "); scanf(" %19[^\n]", encontros[posicao].horario);
                    printf("Novo local: "); scanf(" %49[^\n]", encontros[posicao].local);
                    printf("Novo responsavel: "); scanf(" %49[^\n]", encontros[posicao].responsavel);
                    encontros[posicao].vagas = vagasNovas;
                    printf("Encontro atualizado com sucesso!\n");
                } else printf("Opcao invalida!\n");
                break;

            case 7:
                printf("Codigo do encontro: ");
                codigo = lerNumero();
                posicao = -1;
                for (i = 0; i < totalEncontros; i++) {
                    if (encontros[i].codigo == codigo) posicao = i;
                }
                if (posicao == -1) {
                    printf("Encontro inexistente!\n");
                    break;
                }
                mostrarEncontro(encontros[posicao]);
                printf("Nova situacao: 1 - Planejado / 2 - Realizado / 3 - Cancelado: ");
                novaSituacao = lerNumero();
                if (novaSituacao < 1 || novaSituacao > 3) {
                    printf("Situacao invalida!\n");
                    break;
                }
                if (encontros[posicao].situacao != 1 && novaSituacao != encontros[posicao].situacao) {
                    printf("Encontro finalizado nao pode mudar de situacao!\n"); break;
                }
                encontros[posicao].situacao = novaSituacao;
                printf("Situacao atualizada com sucesso!\n");
                break;

            case 8:
                printf("Codigo do encontro: ");
                codigo = lerNumero();
                posicao = -1;
                for (i = 0; i < totalEncontros; i++) {
                    if (encontros[i].codigo == codigo) posicao = i;
                }
                if (posicao == -1) {
                    printf("Encontro inexistente!\n");
                    break;
                }
                if (encontros[posicao].situacao != 2) {
                    printf("So pode registrar presentes em encontro realizado!\n");
                    break;
                }
                printf("Inscritos: %d\n", encontros[posicao].inscritos);
                printf("Quantidade de participantes presentes: ");
                presentes = lerNumero();
                if (presentes < 0 || presentes > encontros[posicao].inscritos) {
                    printf("Quantidade invalida! Deve ser de 0 ate %d.\n", encontros[posicao].inscritos);
                } else {
                    encontros[posicao].presentes = presentes;
                    printf("Participantes registrados com sucesso!\n");
                }
                break;

            case 0:
                printf("\nSistema encerrado!\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
        }
    }
    return 0;
}
