#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAMADAS 100
#define MAX_TEXTO 100

typedef struct {
    int protocolo;
    char local[MAX_TEXTO];
    char tipo[MAX_TEXTO];
    char horario[MAX_TEXTO];
} Chamada;

typedef struct {
    Chamada itens[MAX_CHAMADAS];
    int topo;
} Pilha;

void inicializarPilha(Pilha *p) {
    // iniciar se estive vazia
    p->topo = -1;
}

int estaVazia(const Pilha *p) {
    // retorna se estive vazia
    return p->topo == -1;
}

int estaCheia(const Pilha *p) {
    // retorna se pilha estive cheia
    return p->topo == MAX_CHAMADAS - 1;
}

int protocoloExiste(const Pilha *p, int protocolo) {
    // verifica se protocolo já existe
    for (int i = 0; i <= p->topo; i++) {
        if (p->itens[i].protocolo == protocolo) {
            return 1;
        }
    }
    return 0;
}

int empilhar(Pilha *p, Chamada chamada) {
    // adicionar nova chamada no topo
    if (estaCheia(p)) {
        return 0;
    }
    if (protocoloExiste(p, chamada.protocolo)) {
        return 0;
    }
    p->itens[++p->topo] = chamada;
    return 1;
}

int desempilhar(Pilha *p, Chamada *saida) {
    // remover última chamada registrada
    if (estaVazia(p)) {
        return 0;
    }
    *saida = p->itens[p->topo--];
    return 1;
}

int consultarTopo(const Pilha *p, Chamada *saida) {
    // retorna a chamada do topo sem remover
    if (estaVazia(p)) {
        return 0;
    }
    *saida = p->itens[p->topo];
    return 1;
}

void limparBuffer(void) {
    // limpar entrada do usuário
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {}
}

void lerTexto(const char *label, char *destino, int tamanho) {
    // ler texto do usuário
    printf("%s: ", label);
    if (fgets(destino, tamanho, stdin) != NULL) {
        size_t len = strlen(destino);
        if (len > 0 && destino[len - 1] == '\n') {
            destino[len - 1] = '\0';
        }
    }
}

void imprimirChamada(const Chamada *c) {
    // imprimir dados da chamada
    printf("Protocolo: %d\n", c->protocolo);
    printf("Local: %s\n", c->local);
    printf("Tipo da ocorrência: %s\n", c->tipo);
    printf("Horário: %s\n", c->horario);
}

void mostrarMenu(void) {
    // mostrar opções para o usuário
    printf("\n=== Pilha de Chamadas de Emergência ===\n");
    printf("1. Registrar chamada\n");
    printf("2. Atender chamada\n");
    printf("3. Consultar última chamada\n");
    printf("4. Sair\n");
    printf("Escolha uma opção: ");
}

int main(void) {
    Pilha pilha;
    inicializarPilha(&pilha);
    int opcao;
    Chamada chamada;

    do {
        mostrarMenu();
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida.\n");
            limparBuffer();
            continue;
        }
        limparBuffer();

        switch (opcao) {
            case 1:
                // registrar nova chamada
                printf("\n--- Registrar nova chamada ---\n");
                printf("Protocolo numero inteiro: ");
                if (scanf("%d", &chamada.protocolo) != 1) {
                    printf("Protocolo invalido.\n");
                    limparBuffer();
                    break;
                }
                limparBuffer();
                lerTexto("Local", chamada.local, MAX_TEXTO);
                lerTexto("Tipo da ocorrencia", chamada.tipo, MAX_TEXTO);
                lerTexto("Horario", chamada.horario, MAX_TEXTO);

                if (empilhar(&pilha, chamada)) {
                    printf("Chamada registrada.\n");
                } else if (estaCheia(&pilha)) {
                    printf("Pilha cheia.\n");
                } else {
                    printf("Protocolo ja existe.\n");
                }
                break;

            case 2:
                // atender chamada do topo
                printf("\n--- Atender ultima chamada ---\n");
                if (desempilhar(&pilha, &chamada)) {
                    printf("Chamado atendido:\n");
                    imprimirChamada(&chamada);
                } else {
                    printf("Sem chamadas.\n");
                }
                break;

            case 3:
                // consultar ultima chamada
                printf("\n--- Consultar ultima chamada ---\n");
                if (consultarTopo(&pilha, &chamada)) {
                    printf("Ultima chamada:\n");
                    imprimirChamada(&chamada);
                } else {
                    printf("Pilha vazia.\n");
                }
                break;

            case 4:
                // sair do programa
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida.\n");
                break;
        }
    } while (opcao != 4);

    return 0;
}