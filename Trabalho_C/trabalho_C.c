
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct {
    int numero;
    char tipo;
    char horario[6]; // Ex.: "14:35"
} Senha;

typedef struct{
    Senha dados[MAX];
    int inicio;
    int fim;
}FilaNormal;

typedef struct{
    Senha dados[MAX];
    int inicio;
    int fim;
    int qtd;
}FilaPreferencial;

void Menu(FilaNormal *filaNormal, FilaPreferencial *filaPreferencial,int *atendimentos);
void CadastrarSenha(FilaNormal *filaNormal, FilaPreferencial *filaPreferencial);
void InserirFilaPreferencial(FilaPreferencial* filaPreferencial, Senha senha);
void InserirFilaNormal(FilaNormal* filaNnormal, Senha senha);
Senha RemoverFilaNormal(FilaNormal *filaNormal);
Senha RemoverFilaPreferencial(FilaPreferencial *filaPrefencial);
void Atender(FilaNormal *filaNormal, FilaPreferencial *filaPreferencial,int *atendimentos);


int main()
{
    FilaNormal filaNormal;

    filaNormal.inicio = 0;
    filaNormal.fim=-1;

    FilaPreferencial filaPreferencial;

    filaPreferencial.inicio = 0;
    filaPreferencial.fim = -1;
    filaPreferencial.qtd = 0;

    int atendimentos = 0;

    Menu(&filaNormal,&filaPreferencial,&atendimentos);


    return 0;
}

void InserirFilaNormal(FilaNormal *fila, Senha s){
    if (fila->fim == MAX - 1)
    {
        printf("Fila normal cheia!\n");
        return;
    }

    fila->fim++;
    fila->dados[fila->fim] = s;
}
void InserirFilaPreferencial(FilaPreferencial *fila, Senha s){
    if (fila->qtd == MAX)
    {
        printf("Fila preferencial cheia!\n");
        return;
    }

    fila->fim = (fila->fim + 1) % MAX;

    fila->dados[fila->fim] = s;

    fila->qtd++;
}

void CadastrarSenha(FilaNormal *filaNormal, FilaPreferencial *filaPreferencial){
    Senha s;

    printf("Numero da senha: ");
    scanf("%d", &s.numero);

    printf("Tipo (N para Normal | P para Preferencial): ");
    do{
        scanf(" %c", &s.tipo);
        }while(s.tipo != 'N' && s.tipo != 'P');

    printf("Horario (HH:MM): ");
    scanf("%5s", s.horario);

    printf("\nSenha cadastrada!\n");

    if (s.tipo == 'P')
    {
        InserirFilaPreferencial(filaPreferencial, s);
    }
    else{
        InserirFilaNormal(filaNormal, s);
    }
    printf("Pressione Enter para continuar...");
    getchar();   // consome o '\n'
    getchar();   // espera Enter
    system("clear");
}

void MostrarFilaNormal(FilaNormal *fila)
{
    if (fila->fim == -1)
    {
        printf("Fila normal vazia!\n");
        return;
    }

    printf("\n===== FILA NORMAL =====\n");

    for (int i = fila->inicio; i <= fila->fim; i++)
    {
        printf("Senha: %d | Tipo: %c | Horario: %s\n",
               fila->dados[i].numero,
               fila->dados[i].tipo,
               fila->dados[i].horario);
    }
}
void MostrarFilaPreferencial(FilaPreferencial *fila)
{
    if (fila->qtd == 0)
    {
        printf("Fila preferencial vazia!\n");
        return;
    }

    printf("\n===== FILA PREFERENCIAL =====\n");

    int indice = fila->inicio;

    for (int i = 0; i < fila->qtd; i++)
    {
        printf("Senha: %d | Tipo: %c | Horario: %s\n",
               fila->dados[indice].numero,
               fila->dados[indice].tipo,
               fila->dados[indice].horario);

        indice = (indice + 1) % MAX;
    }
}
void MostrarFilas(FilaNormal *filanormal, FilaPreferencial *filapreferencial)
{
    MostrarFilaNormal(filanormal);
    MostrarFilaPreferencial(filapreferencial);
}

Senha RemoverFilaNormal(FilaNormal *fila){
    Senha removida;

    if (fila->fim == -1)
    {
        printf("Fila normal vazia!\n");
        removida.numero = -1;
        return removida;
    }

    removida = fila->dados[0];

    for (int i = 0; i < fila->fim; i++)
    {
        fila->dados[i] = fila->dados[i + 1];
    }

    fila->fim--;

    return removida;
}
Senha RemoverFilaPreferencial(FilaPreferencial *fila)
{
    Senha removida;

    if (fila->qtd == 0)
    {
        printf("Fila preferencial vazia!\n");

        removida.numero = -1;
        return removida;
    }

    removida = fila->dados[fila->inicio];

    fila->inicio = (fila->inicio + 1) % MAX;

    fila->qtd--;

    return removida;
}
void Atender(FilaNormal *filaNormal, FilaPreferencial *filaPreferencial, int *atendimentos){
    Senha s;

    // As duas filas estão vazias
    if (filaNormal->fim == -1 && filaPreferencial->qtd == 0)
    {
        printf("Nao há senhas para atendimento.\n");
        return;
    }

    // Normal vazia
    if (filaNormal->fim == -1)
    {
        s = RemoverFilaPreferencial(filaPreferencial);

        printf("Senha atendida: %d (Preferencial)\n", s.numero);
        return;
    }

    // Preferencial vazia
    if (filaPreferencial->qtd == 0)
    {
        s = RemoverFilaNormal(filaNormal);

        printf("Senha atendida: %d (Normal)\n", s.numero);

        (*atendimentos)++;
        return;
    }

    // Já atendeu duas normais
    if (*atendimentos == 2)
    {
        s = RemoverFilaPreferencial(filaPreferencial);

        printf("Senha atendida: %d (Preferencial)\n", s.numero);

        *atendimentos = 0;
    }
    else
    {
        s = RemoverFilaNormal(filaNormal);

        printf("Senha atendida: %d (Normal)\n", s.numero);

        (*atendimentos)++;
    }
}
void Menu(FilaNormal *filaNormal, FilaPreferencial *filaPreferencial,int *atendimentos){
    int op;
    do{
        printf("=======Menu======\n");
        printf("1 - Cadastrar Senha\n");
        printf("2 - Mostrar Filas\n");
        printf("3 - Atender a Próxima Senha\n");
        printf("4 - Sair\n");
        printf("=================\n");
        scanf("%d",&op);
        switch (op){
        case 1: CadastrarSenha(filaNormal,filaPreferencial);
            break;
        case 2: MostrarFilas(filaNormal,filaPreferencial);
            break;
        case 3: Atender(filaNormal, filaPreferencial, atendimentos);
            break;
        case 4: return ;

        default: printf("Opção invalida\n");

        }
    }while (op != 4);


}


