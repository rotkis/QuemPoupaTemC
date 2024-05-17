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

  printf("Digite o tipo, Comum/Plus:");
  fgets(dados[*pos].tipo, TIPO, stdin);
  dados[*pos].tipo[strcmp(dados[*pos].tipo, "\n")] = 0; // arrumar

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

ERROS apagar(Banco dados[], int *pos, int id) { //pq ta marcado?
    if (id < 0 || id >= *pos) {
        return ERRO;
    }
    for (int i = id; i < *pos - 1; i++) {
        dados[i] = dados[i + 1];
    }
    (*pos)--;
    return OK;
}
ERROS debito(Banco dados[], int *pos, int id, double valor) { //pq ta marcado?
    if (id < 0 || id >= *pos) {
        return ERRO;
    }
    if (dados[id].saldo < valor) {
        return ERRO;
    }
    dados[id].saldo -= valor;
    return OK;
}
ERROS extrato(Banco dados[], int *pos, int id) {
  if (id < 0 || id >= *pos) {
      return ERRO;
  }
  printf("Extrato do cliente %s:\n", dados[id].nome);
  printf("CPF: %s\n", dados[id].cpf);
  printf("Tipo: %s\n", dados[id].tipo);
  printf("Saldo: %.2f\n\n", dados[id].saldo);
  return OK;
}

ERROS transferencia(Banco dados[], int *pos, int idOrigem, int idDestino, double valor) {}


ERROS carregar(Banco dados[],int *pos);


ERROS deposito(Banco dados[],int *pos);


void clearBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}