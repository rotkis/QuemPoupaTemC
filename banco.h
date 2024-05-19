#define NOME 100
#define CPF 13
#define TIPO 2
#define SENHA 20
#define HISTORICO 100
#define TRANSACAO 256

typedef struct {
    char nome[NOME];
    char cpf[CPF];
    char tipo[TIPO];
    char senha[SENHA];
    double saldo;
    char historico[HISTORICO][TRANSACAO];
    int numTransacoes;
} Banco;

typedef enum {OK, ERRO, ABRIR, FECHAR, LER, ESCREVER} ERROS;

typedef ERROS (*funcao)(Banco[],int*);

ERROS criar(Banco dados[],int *pos);
ERROS salvar(Banco dados[],int *pos);
ERROS listar(Banco dados[],int *pos);
ERROS apagar(Banco dados[],int *pos);
ERROS debito(Banco dados[],int *pos);
ERROS extrato(Banco dados[],int *pos);
ERROS transferencia(Banco dados[],int *pos);
ERROS carregar(Banco dados[],int *pos);
ERROS deposito(Banco dados[],int *pos);

void clearBuffer();


