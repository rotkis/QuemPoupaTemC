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
    FILE *arquivo = fopen("dados.dat", "wb");
    if (arquivo == NULL) {
        return ERRO;
    }
    fwrite(pos, sizeof(int), 1, arquivo);
    fwrite(dados, sizeof(Banco), *pos, arquivo);
    fclose(arquivo);
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
        if (strcmp(dados[i].cpf, cpf) == 0) {
            for (int j = i; j < *pos - 1; j++) {
                dados[j] = dados[j + 1];
            }
            (*pos)--;
            return OK;
        }
    }
    return ERRO;
}
ERROS debito(Banco dados[], int *pos) { //pq ta marcado?
        char cpf[CPF];
        double valor;
        printf("Digite o CPF do cliente para debitar: ");
        fgets(cpf, CPF, stdin);
        cpf[strcspn(cpf, "\n")] = 0;
        printf("Digite o valor a ser debitado: ");
        scanf("%lf", &valor);
        clearBuffer();
        for (int i = 0; i < *pos; i++) {
            if (strcmp(dados[i].cpf, cpf) == 0) {
                if (dados[i].saldo < valor) {
                    return ERRO;
                }
                dados[i].saldo -= valor;
                return OK;
            }
        }
        return ERRO;
    }

ERROS extrato(Banco dados[], int *pos) {
        char cpf[CPF];
        printf("Digite o CPF do cliente para ver o extrato: ");
        fgets(cpf, CPF, stdin);
        cpf[strcspn(cpf, "\n")] = 0;
        for (int i = 0; i < *pos; i++) {
            if (strcmp(dados[i].cpf, cpf) == 0) {
                printf("Extrato do cliente %s:\n", dados[i].nome);
                printf("CPF: %s\n", dados[i].cpf);
                printf("Tipo: %s\n", dados[i].tipo);
                printf("Saldo: %.2f\n\n", dados[i].saldo);
                return OK;
            }
        }
        return ERRO;
    }

ERROS transferencia(Banco dados[], int *pos) {
    printf("Teste\n");

}

ERROS carregar(Banco dados[],int *pos) {
    printf("Teste\n");
}


ERROS deposito(Banco dados[],int *pos){
    printf("Teste\n");
}





void clearBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}