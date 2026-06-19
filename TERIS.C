#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

// Estrutura da peça
typedef struct {
    char nome;
    int id;
} Peca;

// ================= FILA CIRCULAR =================
Peca fila[TAM_FILA];
int frente = 0;
int tras = -1;
int quantidadeFila = 0;

// ================= PILHA =================
Peca pilha[TAM_PILHA];
int topo = -1;

// Controle dos IDs das peças
int proximoId = 0;

// Gera uma nova peça aleatória
Peca gerarPeca() {
    Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L'};

    nova.nome = tipos[rand() % 4];
    nova.id = proximoId++;

    return nova;
}

// Insere peça na fila
void enqueue(Peca p) {
    if (quantidadeFila == TAM_FILA) {
        return;
    }

    tras = (tras + 1) % TAM_FILA;
    fila[tras] = p;
    quantidadeFila++;
}

// Remove peça da frente da fila
Peca dequeue() {
    Peca removida = fila[frente];

    frente = (frente + 1) % TAM_FILA;
    quantidadeFila--;

    return removida;
}

// Empilha peça na reserva
void push(Peca p) {
    topo++;
    pilha[topo] = p;
}

// Remove peça da reserva
Peca pop() {
    Peca removida = pilha[topo];
    topo--;

    return removida;
}

// Exibe a fila
void exibirFila() {
    int i, indice;

    printf("\nFila de pecas:\n");

    for (i = 0; i < quantidadeFila; i++) {
        indice = (frente + i) % TAM_FILA;
        printf("[%c %d] ", fila[indice].nome, fila[indice].id);
    }

    printf("\n");
}

// Exibe a pilha
void exibirPilha() {
    int i;

    printf("Pilha de reserva (Topo -> Base): ");

    if (topo == -1) {
        printf("Vazia");
    } else {
        for (i = topo; i >= 0; i--) {
            printf("[%c %d] ", pilha[i].nome, pilha[i].id);
        }
    }

    printf("\n");
}

// Mostra o estado atual do jogo
void exibirEstado() {
    printf("\n==============================");
    printf("\nESTADO ATUAL");
    printf("\n==============================");

    exibirFila();
    exibirPilha();

    printf("\n");
}

// ================= MAIN =================
int main() {
    int opcao;
    int i;

    srand(time(NULL));

    // Inicializa a fila com 5 peças
    for (i = 0; i < TAM_FILA; i++) {
        enqueue(gerarPeca());
    }

    do {
        exibirEstado();

        printf("1 - Jogar peca\n");
        printf("2 - Reservar peca\n");
        printf("3 - Usar peca reservada\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1: {
                Peca jogada = dequeue();

                printf("\nPeca [%c %d] jogada.\n",
                       jogada.nome, jogada.id);

                // Mantém a fila sempre cheia
                enqueue(gerarPeca());
                break;
            }

            case 2: {
                if (topo == TAM_PILHA - 1) {
                    printf("\nPilha de reserva cheia!\n");
                } else {
                    Peca reservada = dequeue();

                    push(reservada);

                    printf("\nPeca [%c %d] enviada para a reserva.\n",
                           reservada.nome, reservada.id);

                    // Mantém a fila cheia
                    enqueue(gerarPeca());
                }
                break;
            }

            case 3: {
                if (topo == -1) {
                    printf("\nNao ha pecas na reserva.\n");
                } else {
                    Peca usada = pop();

                    printf("\nPeca reservada [%c %d] utilizada.\n",
                           usada.nome, usada.id);
                }
                break;
            }

            case 0:
                printf("\nPrograma encerrado.\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}