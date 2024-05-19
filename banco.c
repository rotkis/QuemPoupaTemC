#include "banco.h"
#include <stdio.h>
#include <string.h>

ERROS criar(Banco dados[], int *pos) {
  printf("Digite o nome: ");
  fgets(dados[*pos].nome, NOME, stdin);
  dados[*pos].nome[strcspn(dados[*pos].nome, "\n")] = 0;

  printf("Digite o CPF: ");
  fgets(dados[*pos].cpf, CPF, stdin);
  dados[*pos].cpf[strcspn(dados[*pos].cpf, "\n")] = 0;
  clearBuffer();

  while (1) {
    printf("Digite o tipo, C/P: ");
    fgets(dados[*pos].tipo, TIPO, stdin);
    dados[*pos].tipo[strcspn(dados[*pos].tipo, "\n")] = 0;
    if (dados[*pos].tipo[0] == 'C' || dados[*pos].tipo[0] == 'P') {
      break;
    }
  }
  clearBuffer();
  printf("Digite a senha: ");
  fgets(dados[*pos].senha, SENHA, stdin);
  dados[*pos].senha[strcspn(dados[*pos].senha, "\n")] = 0;

  printf("Digite o saldo inicial: ");
  scanf("%lf", &dados[*pos].saldo);
  clearBuffer();

  dados[*pos].numTransacoes = 0;

  (*pos)++;
  printf("Conta criada com sucesso!\n");
  return OK;
}
ERROS salvar(Banco dados[], int *pos) {
  FILE *arquivo = fopen("dados.bin", "wb");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return ERRO;
  }
  fwrite(pos, sizeof(int), 1, arquivo);
  for (int i = 0; i < *pos; i++) {
    fwrite(&dados[i],
           sizeof(Banco) - sizeof(dados[i].historico) -
               sizeof(dados[i].numTransacoes),
           1, arquivo);
    fwrite(&dados[i].numTransacoes, sizeof(int), 1, arquivo);
    fwrite(dados[i].historico, sizeof(dados[i].historico[0]),
           dados[i].numTransacoes, arquivo);
  }
  fclose(arquivo);
  printf("Dados salvos com sucesso.\n");
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
  char senha[SENHA];
  double valor;
  printf("Digite o CPF do cliente para debitar: ");
  fgets(cpf, CPF, stdin);
  cpf[strcspn(cpf, "\n")] = 0;
  clearBuffer();

  printf("Digite a senha do cliente: ");
  fgets(senha, SENHA, stdin);
  senha[strcspn(senha, "\n")] = 0;

  printf("Digite o valor a ser debitado: ");
  scanf("%lf", &valor);
  clearBuffer();

  for (int i = 0; i < *pos; i++) {
    if (strcmp(dados[i].cpf, cpf) == 0) {
      if (strcmp(dados[i].senha, senha) == 0) {

        double taxa;
        double limite_negativo;

        if (strcmp(dados[i].tipo, "C") == 0) {
          taxa = 0.05;                
          limite_negativo = -1000.00; 
        } else if (strcmp(dados[i].tipo, "P") == 0) {
          taxa = 0.03;                
          limite_negativo = -5000.00; 
        } else {
          printf("Tipo de conta desconhecido.\n");
          return ERRO;
        }

        double valor_total = valor + (valor * taxa);
        if (dados[i].saldo - valor_total < limite_negativo) {
          printf("Saldo insuficiente.\n");
          return ERRO;
        }

        dados[i].saldo -= valor_total;
        snprintf(dados[i].historico[dados[i].numTransacoes++], TRANSACAO,
                 "Débito: -%.2f (incluindo taxa de %.2f)", valor, valor * taxa);
        printf("Débito realizado com sucesso.\n");
        return OK;
      }
    }
  }
  printf("CPF não encontrado.\n");
  return ERRO;
}

ERROS extrato(Banco dados[], int *pos) {
  char cpf[CPF];
  char senha[SENHA];
  printf("Digite o CPF do cliente para ver o extrato: ");
  fgets(cpf, CPF, stdin);
  cpf[strcspn(cpf, "\n")] = 0;
  printf("Digite a senha do cliente: ");
  fgets(senha, SENHA, stdin);
  senha[strcspn(senha, "\n")] = 0;
  for (int i = 0; i < *pos; i++) {
    if (strcmp(dados[i].cpf, cpf) == 0) {
      if (strcmp(dados[i].senha, senha) == 0) {

        printf("Extrato do cliente %s:\n", dados[i].nome);
        printf("CPF: %s\n", dados[i].cpf);
        printf("Tipo: %s\n", dados[i].tipo);
        printf("Saldo: %.2f\n", dados[i].saldo);
        printf("Histórico de transações:\n");
        for (int j = 0; j < dados[i].numTransacoes; j++) {
          printf("%s\n", dados[i].historico[j]);
        }
        return OK;
      }
    }
  }
  printf("CPF não encontrado.\n");
  return ERRO;
}

ERROS transferencia(Banco dados[], int *pos) {
    char cpf_origem[CPF], cpf_destino[CPF], senha_origem[SENHA];
    double valor;

    printf("Digite o CPF do cliente de origem: ");
    fgets(cpf_origem, CPF, stdin);
    cpf_origem[strcspn(cpf_origem, "\n")] = 0;

    printf("Digite a senha do cliente de origem: ");
    fgets(senha_origem, SENHA, stdin);
    senha_origem[strcspn(senha_origem, "\n")] = 0;

    printf("Digite o CPF do cliente de destino: ");
    fgets(cpf_destino, CPF, stdin);
    cpf_destino[strcspn(cpf_destino, "\n")] = 0;

    printf("Digite o valor a ser transferido: ");
    scanf("%lf", &valor);
    clearBuffer();

    int origemIndex = -1, destinoIndex = -1;

    // Encontrar os índices das contas de origem e destino
    for (int i = 0; i < *pos; i++) {
        if (strcmp(dados[i].cpf, cpf_origem) == 0) {
            origemIndex = i;
        }
        if (strcmp(dados[i].cpf, cpf_destino) == 0) {
            destinoIndex = i;
        }
    }

    if (origemIndex == -1) {
        printf("CPF de origem não encontrado.\n");
        return ERRO;
    }

    if (destinoIndex == -1) {
        printf("CPF de destino não encontrado.\n");
        return ERRO;
    }

    // Verificar a senha da conta de origem
    if (strcmp(dados[origemIndex].senha, senha_origem) != 0) {
        printf("Senha incorreta.\n");
        return ERRO;
    }

    double taxa;
    double limite_negativo;

    
    if (strcmp(dados[origemIndex].tipo, "C") == 0) {
        taxa = 0.05;                
        limite_negativo = -1000.00; 
    } else if (strcmp(dados[origemIndex].tipo, "P") == 0) {
        taxa = 0.03;                
        limite_negativo = -5000.00; 
    } else {
        printf("Tipo de conta desconhecido.\n");
        return ERRO;
    }

    double valor_total = valor + (valor * taxa);

    if (dados[origemIndex].saldo - valor_total < limite_negativo) {
        printf("Saldo insuficiente.\n");
        return ERRO;
    }

    dados[origemIndex].saldo -= valor_total;
    dados[destinoIndex].saldo += valor;

    snprintf(dados[origemIndex].historico[dados[origemIndex].numTransacoes++], TRANSACAO,
             "Transferência para %s: -%.2f (incluindo taxa de %.2f)", dados[destinoIndex].nome, valor, valor * taxa);
    snprintf(dados[destinoIndex].historico[dados[destinoIndex].numTransacoes++], TRANSACAO,
             "Transferência de %s: +%.2f", dados[origemIndex].nome, valor);

    printf("Transferência realizada com sucesso.\n");
    return OK;
}

ERROS carregar(Banco dados[], int *pos) {
  FILE *arquivo = fopen("dados.bin", "rb");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return ERRO;
  }
  fread(pos, sizeof(int), 1, arquivo);
  for (int i = 0; i < *pos; i++) {
    fread(&dados[i],
          sizeof(Banco) - sizeof(dados[i].historico) -
              sizeof(dados[i].numTransacoes),
          1, arquivo);
    fread(&dados[i].numTransacoes, sizeof(int), 1, arquivo);
    fread(dados[i].historico, sizeof(dados[i].historico[0]),
          dados[i].numTransacoes, arquivo);
  }
  fclose(arquivo);
  printf("Dados carregados com sucesso.\n");
  return OK;
}

ERROS deposito(Banco dados[], int *pos) {
  char cpf[CPF];
  double valor;
  printf("Digite o CPF do cliente para depositar: ");
  fgets(cpf, CPF, stdin);
  cpf[strcspn(cpf, "\n")] = 0;
  printf("Digite o valor a ser depositado: ");
  scanf("%lf", &valor);
  clearBuffer();
  for (int i = 0; i < *pos; i++) {
    if (strcmp(dados[i].cpf, cpf) == 0) {
      dados[i].saldo += valor;
      snprintf(dados[i].historico[dados[i].numTransacoes++], TRANSACAO,
               "Depósito: +%.2f", valor);
      printf("Depósito realizado com sucesso.\n");
      return OK;
    }
  }
  printf("CPF não encontrado.\n");
  return ERRO;
}

void clearBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}