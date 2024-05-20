# QuemPoupaTemC

Este projeto feito para criar um sistema de controle de clientes para um banco. O sistema foi desenvolvido em C e pode ser utilizado para gerenciar contas bancárias, realizar transações e manter registros de clientes.

Funcionalidades:
Novo Cliente: Permite criar novos clientes.
Apaga Cliente: Permite apagar clientes existentes pelo CPF.
Listar Clientes: Exibe uma lista de todos os clientes cadastrados.
Débito: Realiza um débito na conta de um cliente.
Depósito: Realiza um depósito na conta de um cliente.
Extrato: Gera um extrato das transações de um cliente.
Transferência Entre Contas: Realiza uma transferência de uma conta para outra.
Sair: Encerra o programa.

Tipos de Conta
Comum: Cobra taxa de 5% a cada débito realizado.
Permite saldo negativo de até R$ 1.000,00.
Plus: Cobra taxa de 3% a cada débito realizado.
Permite saldo negativo de até R$ 5.000,00.

Para compilar o programa, utilize o comando:
gcc -o main.c 
Execução
Para executar o programa, utilize o comando:
./main.c
