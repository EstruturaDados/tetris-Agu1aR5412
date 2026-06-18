#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5

// Estrutura da peca
typedef struct {
    char nome;
    int id;
} Peca;

// Fila circular
Peca fila[MAX];
int frente = 0;
int tras = -1;
int quantidade = 0;
int proximoId = 0;

// Gera uma nova peca automaticamente
Peca gerarPeca() {
    Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L'};

    nova.nome = tipos[rand() % 4];
    nova.id = proximoId++;

    return nova;
}

// Insere uma peca no final da fila
void enqueue(Peca p) {
    if (quantidade == MAX) {
        printf("\nFila cheia! Nao e possivel inserir nova peca.\n");
        return;
    }

    tras = (tras + 1) % MAX;
    fila[tras] = p;
    quantidade++;

    printf("\nPeca [%c %d] inserida.\n", p.nome, p.id);
}

// Remove a peca da frente da fila
void dequeue() {
    if (quantidade == 0) {
        printf("\nFila vazia! Nenhuma peca para jogar.\n");
        return;
    }

    Peca removida = fila[frente];
    frente = (frente + 1) % MAX;
    quantidade--;

    printf("\nPeca [%c %d] jogada.\n", removida.nome, removida.id);
}

// Exibe a fila
void exibirFila() {
    int i, indice;

    printf("\nFila de pecas:\n");

    if (quantidade == 0) {
        printf("Fila vazia.\n");
        return;
    }

    for (i = 0; i < quantidade; i++) {
        indice = (frente + i) % MAX;
        printf("[%c %d] ", fila[indice].nome, fila[indice].id);
    }

    printf("\n");
}

int main() {
    int opcao;
    int i;

    srand(time(NULL));

    // Inicializa a fila com 5 pecas
    for (i = 0; i < MAX; i++) {
        enqueue(gerarPeca());
    }

    do {
        exibirFila();

        printf("\n===== MENU =====\n");
        printf("1 - Jogar peca\n");
        printf("2 - Inserir nova peca\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                dequeue();
                break;

            case 2:
                enqueue(gerarPeca());
                break;

            case 0:
                printf("\nPrograma encerrado.\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}