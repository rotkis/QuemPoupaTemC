#define NOME 20
#define CPF 12
#define TIPO 2
#define SENHA 20
#define SALDOI 225

typedef struct{
  char nome[NOME];
  char cpf[CPF];
  char tipo[TIPO];
  char senha[SENHA];
  double saldo;
} Banco;	

typedef enum {OK, ERRO, ABRIR, FECHAR, LER, ESCREVER} ERROS;

typedef ERROS (*funcao)(Banco[],int*);

ERROS criar(Banco dados[],int *pos);
ERROS salvar(Banco dados[],int *pos);
ERROS listar(Banco dados[],int *pos);
ERROS apagar(Banco dados[],int *pos, int id);
ERROS debito(Banco dados[],int *pos, int id, double valor);
ERROS extrato(Banco dados[],int *pos, int id);
ERROS transferencia(Banco dados[],int *pos, int idOrigem, int idDestino, double valor);
ERROS carregar(Banco dados[],int *pos);
ERROS deposito(Banco dados[],int *pos);

void clearBuffer();


