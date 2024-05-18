#include <stdio.h>
#include <string.h>
#include "banco.h"

ERROS criar(Banco dados[],int *pos){
  printf("Digite o nome:");
  fgets(dados[*pos].nome, NOME, stdin);
  dados[*pos].nome[strcmp(dados[*pos].nome, "\n")] = 0;

  printf("Digite o cpf:");
  fgets(dados[*pos].cpf, CPF, stdin);
  dados[*pos].cpf[strcmp(dados[*pos].cpf, "\n")] = 0;

  printf("Digite o tipo, C/P:");
  fgets(dados[*pos].tipo, TIPO, stdin);
  dados[*pos].tipo[strcmp(dados[*pos].tipo, "\n")] = 0;
  clearBuffer();

  printf("Digite a senha:");
  fgets(dados[*pos].senha, SENHA, stdin);
  dados[*pos].senha[strcmp(dados[*pos].senha, "\n")] = 0;

  printf("Digite o saldo Inicial:");
  scanf("%lf", &dados[*pos].saldo);
  clearBuffer();
  
  *pos = *pos + 1;
  return OK;
  
}
ERROS salvar(Banco dados[], int *pos) {
    FILE *arquivo = fopen("dados.bin", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return ERRO;
    }
    fwrite(pos, sizeof(int), 1, arquivo);
    fwrite(dados, sizeof(Banco), *pos, arquivo);
    fclose(arquivo);
    printf("salvo");
    return OK;
}
ERROS listar(Banco dados[], int *pos) {
    for (int i = 0; i < *pos; i++) {
        printf("Cliente %d:\n", i + 1);
        printf("Nome: %s\n", dados[i].nome);
        printf("CPF: %s\n", dados[i].cpf);
        printf("Tipo: %s\n", dados[i].tipo);
        printf("Saldo: %.2f\n\n", dados[i].saldo);
    }
    return OK;
}

ERROS apagar(Banco dados[], int *pos) {
    for (int i = 0; i < *pos; i++) {
        printf("Digite seu CPF:");
        char cpf[CPF];
        fgets(cpf, CPF, stdin);
        cpf[strcspn(cpf, "\n")] = '\0';
        dados[i].cpf[strcspn(dados[i].cpf, "\n")] = '\0';
        if (strcmp(dados[i].cpf, cpf) == 0) {
            for (int j = i; j < *pos - 1; j++) {
                dados[j] = dados[j + 1];
            }
            (*pos)--;
            printf("Conta apagada com sucesso.\n");
            return OK;
        }
    }
    printf("CPF não encontrado.\n");
    return ERRO;
}
ERROS debito(Banco dados[], int *pos) {
        char cpf[CPF];
        double valor;
        printf("Digite o CPF do cliente para debitar: ");
        fgets(cpf, CPF, stdin);
        cpf[strcspn(cpf, "\n")] = 0;
        printf("Digite o valor a ser debitado: ");
        scanf("%lf", &valor);
        clearBuffer();
        for (int i = 0; i < *pos; i++) {
            dados[i].cpf[strcspn(dados[i].cpf, "\n")] = '\0';
            if (strcmp(dados[i].cpf, cpf) == 0) {
                if (dados[i].saldo < valor) {
                    printf("Saldo insuficiente.\n");
                    return ERRO;
                }
                dados[i].saldo -= valor;
                printf("Débito realizado com sucesso.\n");
                return OK;
            }
        }
        printf("CPF não encontrado.\n");
        return ERRO;
    }

ERROS extrato(Banco dados[], int *pos) {
        char cpf[CPF];
        printf("Digite o CPF do cliente para ver o extrato: ");
        fgets(cpf, CPF, stdin);
        cpf[strcspn(cpf, "\n")] = 0;
        for (int i = 0; i < *pos; i++) {
            dados[i].cpf[strcspn(dados[i].cpf, "\n")] = '\0';
            if (strcmp(dados[i].cpf, cpf) == 0) {
                printf("Extrato do cliente %s:\n", dados[i].nome);
                printf("CPF: %s\n", dados[i].cpf);
                printf("Tipo: %s\n", dados[i].tipo);
                printf("Saldo: %.2f\n\n", dados[i].saldo);
                return OK;
            }
        }
        printf("CPF não encontrado.\n");
        return ERRO;
    }

ERROS transferencia(Banco dados[], int *pos) {
    char cpf_origem[CPF], cpf_destino[CPF];
    double valor;
    printf("Digite o CPF do cliente de origem: ");
    fgets(cpf_origem, CPF, stdin);
    cpf_origem[strcspn(cpf_origem, "\n")] = 0;
    printf("Digite o CPF do cliente de destino: ");
    fgets(cpf_destino, CPF, stdin);
    cpf_destino[strcspn(cpf_destino, "\n")] = 0;
    printf("Digite o valor a ser transferido: ");
    scanf("%lf", &valor);
    clearBuffer();
    for (int i = 0; i < *pos; i++){
        dados[i].cpf[strcspn(dados[i].cpf, "\n")] = '\0';
        if (strcmp(dados[i].cpf, cpf_origem) == 0){
            if (dados[i].saldo < valor){
                printf("Saldo insuficiente.\n");
                return ERRO;
            }
            dados[i].saldo -= valor;
            for (int j = 0; j < *pos; j++){
                dados[j].cpf[strcspn(dados[j].cpf, "\n")] = '\0';
                if (strcmp(dados[j].cpf, cpf_destino) == 0){
                    dados[j].saldo += valor;
                    printf("Transferência realizada com sucesso.\n");
                    return OK;
                }
            }
            printf("CPF de destino não encontrado.\n");
            return ERRO;
        }
    }
    printf("CPF de origem não encontrado.\n");
    return ERRO;
}

ERROS carregar(Banco dados[],int *pos) {
    FILE *arquivo = fopen("dados.bin", "rb");
    if (arquivo == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return ERRO;
    }
    fread(pos, sizeof(int), 1, arquivo);
    fread(dados, sizeof(Banco), *pos, arquivo);
    fclose(arquivo);
    printf("carregado\n");
    return OK;
}


ERROS deposito(Banco dados[],int *pos){
    char cpf[CPF];
    double valor;
    printf("Digite o CPF do cliente para depositar: ");
    fgets(cpf, CPF, stdin);
    cpf[strcspn(cpf, "\n")] = 0;
    printf("Digite o valor a ser depositado: ");
    scanf("%lf", &valor);
    clearBuffer();
    for (int i = 0; i < *pos; i++){
        dados[i].cpf[strcspn(dados[i].cpf, "\n")] = '\0';
        if (strcmp(dados[i].cpf, cpf) == 0){
            dados[i].saldo += valor;
            printf("Deposito realizado com sucesso.\n");
            return OK;
        }
    }
    printf("CPF não encontrado.\n");
    return ERRO;
}

void clearBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}