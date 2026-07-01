#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX 100

typedef struct {
    int id;
    char titulo[100];
    char artista[100];
    float duracao;
    char genero[50];
} Musica;

Musica playlist[MAX];
int qtd = 0;

void cor() {
    int opc;

    printf("************************\n");
    printf("* 0 - Reset            *\n");
    printf("* 1 - Vermelho         *\n");
    printf("* 2 - Verde            *\n");
    printf("* 3 - Amarelo          *\n");
    printf("* 4 - Azul             *\n");
    printf("* 5 - Roxo             *\n");
    printf("* 6 - Ciano            *\n");
    printf("************************\n");
    printf("Escolha a cor: ");

    scanf("%d", &opc);
    getchar();
    system("cls");

    switch(opc) {
        case 0:
            printf("\033[0m");
            break;
        case 1:
            printf("\033[1;31m");
            break;
        case 2:
            printf("\033[1;32m");
            break;
        case 3:
            printf("\033[1;33m");
            break;
        case 4:
            printf("\033[1;34m");
            break;
        case 5:
            printf("\033[1;35m");
            break;
        case 6:
            printf("\033[1;36m");
            break;
        default:
            printf("\033[0m");
            printf("Opcao invalida!\n");
    }
}

// Verifica se ID já existe
int idExiste(int id) {
    for(int i = 0; i < qtd; i++) {
        if(playlist[i].id == id)
            return 1;
    }
    return 0;
}

// Cadastrar música
void cadastrar() {

    if(qtd >= MAX) {
        printf("\nPlaylist cheia!\n");
        return;
    }

    int id;

    printf("\nID: ");
    scanf("%d", &id);
    getchar();

    if(idExiste(id)) {
        printf("ID ja cadastrado!\n");
        return;
    }

    playlist[qtd].id = id;

    printf("Titulo: ");
    fgets(playlist[qtd].titulo, 100, stdin);
    playlist[qtd].titulo[strcspn(playlist[qtd].titulo,"\n")] = '\0';

    printf("Artista: ");
    fgets(playlist[qtd].artista, 100, stdin);
    playlist[qtd].artista[strcspn(playlist[qtd].artista,"\n")] = '\0';

    printf("Duracao (minutos): ");
    scanf("%f", &playlist[qtd].duracao);
    getchar();

    printf("Genero: ");
    fgets(playlist[qtd].genero, 50, stdin);
    playlist[qtd].genero[strcspn(playlist[qtd].genero,"\n")] = '\0';

    qtd++;
    system("cls");
    printf("\nMusica cadastrada com sucesso!\n");
}

// Buscar música
int buscarIndice(int id) {

    for(int i = 0; i < qtd; i++) {
        if(playlist[i].id == id)
            return i;
    }

    return -1;
}

void buscar() {

    if(qtd == 0) {
        printf("\nPlaylist vazia!\n");
        return;
    }

    int id;

    printf("Digite o ID: ");
    scanf("%d", &id);

    int pos = buscarIndice(id);

    if(pos == -1) {
        printf("Musica nao encontrada!\n");
        return;
    }

    printf("\nID: %d\n", playlist[pos].id);
    printf("Titulo: %s\n", playlist[pos].titulo);
    printf("Artista: %s\n", playlist[pos].artista);
    printf("Duracao: %.2f\n", playlist[pos].duracao);
    printf("Genero: %s\n", playlist[pos].genero);
}

// Editar
void editar() {

    if(qtd == 0) {
        printf("\nPlaylist vazia!\n");
        return;
    }

    int id;

    printf("ID da musica: ");
    scanf("%d", &id);
    getchar();

    int pos = buscarIndice(id);

    if(pos == -1) {
        printf("Musica nao encontrada!\n");
        return;
    }

    printf("Novo titulo: ");
    fgets(playlist[pos].titulo,100,stdin);
    playlist[pos].titulo[strcspn(playlist[pos].titulo,"\n")] = '\0';

    printf("Novo artista: ");
    fgets(playlist[pos].artista,100,stdin);
    playlist[pos].artista[strcspn(playlist[pos].artista,"\n")] = '\0';

    printf("Nova duracao: ");
    scanf("%f",&playlist[pos].duracao);
    getchar();

    printf("Novo genero: ");
    fgets(playlist[pos].genero,50,stdin);
    playlist[pos].genero[strcspn(playlist[pos].genero,"\n")] = '\0';

    system("cls");
    printf("\nMusica atualizada!\n");
}

// Excluir
void excluir() {

    if(qtd == 0) {
        printf("\nPlaylist vazia!\n");
        return;
    }

    int id;

    printf("ID da musica: ");
    scanf("%d", &id);

    int pos = buscarIndice(id);

    if(pos == -1) {
        printf("Musica nao encontrada!\n");
        return;
    }

    for(int i = pos; i < qtd - 1; i++) {
        playlist[i] = playlist[i + 1];
    }

    qtd--;
    system("cls");
    printf("Musica removida com sucesso!\n");
}

// Listar
void listar() {

    if(qtd == 0) {
        printf("\nPlaylist vazia!\n");
        return;
    }

    printf("\n===== PLAYLIST =====\n");

    for(int i = 0; i < qtd; i++) {

        printf("\nID: %d\n", playlist[i].id);
        printf("Titulo: %s\n", playlist[i].titulo);
        printf("Artista: %s\n", playlist[i].artista);
        printf("Duracao: %.2f\n", playlist[i].duracao);
        printf("Genero: %s\n", playlist[i].genero);
    }
}

// Salvar CSV
void salvarCSV() {

    FILE *arq = fopen("playlist.csv","w");

    if(arq == NULL) {
        printf("Erro ao criar arquivo!\n");
        return;
    }

    fprintf(arq,"ID,Titulo,Artista,Duracao,Genero\n");

    for(int i = 0; i < qtd; i++) {

        fprintf(arq,"%d,%s,%s,%.2f,%s\n",
                playlist[i].id,
                playlist[i].titulo,
                playlist[i].artista,
                playlist[i].duracao,
                playlist[i].genero);
    }

    fclose(arq);
    system("cls");
    printf("Dados salvos com sucesso!\n");
}

// Carregar CSV
void carregarCSV() {

    FILE *arq = fopen("playlist.csv","r");

    if(arq == NULL) {
        printf("Arquivo nao encontrado!\n");
        return;
    }

    qtd = 0;

    char linha[300];

    fgets(linha, sizeof(linha), arq);

    while(fgets(linha, sizeof(linha), arq) != NULL) {

        sscanf(linha,
               "%d,%99[^,],%99[^,],%f,%49[^\n]",
               &playlist[qtd].id,
               playlist[qtd].titulo,
               playlist[qtd].artista,
               &playlist[qtd].duracao,
               playlist[qtd].genero);

        qtd++;
    }

    fclose(arq);
    system("cls");
    printf("Dados carregados com sucesso!\n");
}

// Main
int main() {

    int op;

    do {

        printf("\n===== PLAYLIST =====\n");
        printf("1 - Cadastrar musica\n");
        printf("2 - Buscar musica\n");
        printf("3 - Editar musica\n");
        printf("4 - Excluir musica\n");
        printf("5 - Listar musicas\n");
        printf("6 - Salvar CSV\n");
        printf("7 - Carregar CSV\n");
        printf("8 - Cor\n");
        printf("9 - Sair\n");
        printf("Opcao: ");

        scanf("%d", &op);
        system("cls");

        switch(op) {

            case 1:
                cadastrar();
                break;

            case 2:
                buscar();
                break;

            case 3:
                editar();
                break;

            case 4:
                excluir();
                break;

            case 5:
                listar();
                break;

            case 6:
                salvarCSV();
                break;

            case 7:
                carregarCSV();
                break;

            case 8:
                cor();
                break;

            case 9:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while(op != 9);

    return 0;
}
