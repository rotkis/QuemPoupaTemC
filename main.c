#include <stdio.h>
#include <string.h>
#include "banco.h"
int main(){
  funcao fs[] = {criar, salvar, listar, apagar, debito, extrato, transferencia, carregar, deposito};
  Banco dados[10]; // COLOCAR ALG COISA DENTRO DISSO?
  int pos = 0;
  ERROS erro = fs[7](dados, &pos); // fs[0] ????????????
  if (erro != OK)
    pos = 0;

  int opcao;
  do{
    printf("1 - Criar\n");
    printf("2 - Salvar\n");
    printf("3 - Listar\n");
    printf("4 - Apagar\n");
    printf("5 - Debito\n");
    printf("6 - Extrato\n");
    printf("7 - Transferencia\n");
    printf("8 - Deposito\n");
    printf("9 - Carregar\n");
    printf("10 - Sair\n");
    printf("Opcao: ");
    scanf("%d", &opcao);
    clearBuffer();

    opcao--;
    if (opcao < 0 || opcao > 10)
      printf("opção invalida\n");
    else if (opcao == 10)
      printf("sair\n");
    else
      fs[opcao](dados, &pos); // colocar em opção o número certo

  } while (opcao != 10);
  return 0;
}

