#include <stdio.h>
#include <string.h>
#include "banco.h"
int main(){
  funcao fs[] = {criar, listar, apagar, debito, extrato, transferencia,deposito, carregar , salvar};
  Banco dados[10]; 
  int pos = 0;
  ERROS erro = fs[7](dados, &pos); 
  if (erro != OK)
    pos = 0;

  int opcao;
  do{
    printf("1 - Criar\n");
    printf("2 - Listar\n");
    printf("3 - Apagar\n");
    printf("4 - Debito\n");
    printf("5 - Extrato\n");
    printf("6 - Transferencia\n");
    printf("7 - Deposito\n");
    printf("0 - Sair\n");
    printf("Opcao: ");
    scanf("%d", &opcao);
    clearBuffer();
    opcao--;
    if (opcao > 8)
      printf("opção invalida\n");
    else if (opcao >= 0)
      fs[opcao](dados, &pos);
    else
      printf("sair\n");
  } while (opcao >= 0);
  fs[8](dados, &pos);
}

