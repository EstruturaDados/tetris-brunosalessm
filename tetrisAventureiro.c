#include <stdio.h>

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.


// Nível Aventureiro

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5

// --- Estrutura que representa uma peça ---
typedef struct {
    char tipo; // Letra representando o tipo (ex: A, B, C...)
    int id;    // Identificador sequencial
} Peca;

// --- Estrutura da fila circular ---
typedef struct {
    Peca fila[TAM_FILA];
    int inicio;
    int fim;
    int quantidade;
    int proximoID; // controla o id sequencial das peças
} Fila;

// --- Protótipos ---
void inicializarFila(Fila *f);
int filaCheia(Fila *f);
int filaVazia(Fila *f);
void enqueue(Fila *f, Peca p);
Peca dequeue(Fila *f);
Peca gerarPeca(Fila *f);
void mostrarFila(Fila *f);

int main() {
    srand(time(NULL)); // semente aleatória

    Fila fila;
    inicializarFila(&fila);

    int opcao;

    do {
        printf("\n=== FILA DE PECAS FUTURAS ===\n");
        printf("1 - Jogar peça (remover da frente)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                if (!filaVazia(&fila)) {
                    Peca removida = dequeue(&fila);
                    printf("\n🧩 Peça jogada: ID=%d | Tipo=%c\n", removida.id, removida.tipo);

                    // Após remover, insere automaticamente uma nova peça
                    Peca nova = gerarPeca(&fila);
                    enqueue(&fila, nova);
                    printf("✨ Nova peça gerada: ID=%d | Tipo=%c\n", nova.id, nova.tipo);
                } else {
                    printf("⚠️  A fila está vazia!\n");
                }

                mostrarFila(&fila);
                break;

            case 0:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opção inválida!\n");
                break;
        }

    } while (opcao != 0);

    return 0;
}

// --- Inicializa a fila com 5 peças ---
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->quantidade = 0;
    f->proximoID = 1;

    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(f, gerarPeca(f));
    }

    printf("\nFila inicializada com 5 peças!\n");
    mostrarFila(f);
}

// --- Verifica se a fila está cheia ---
int filaCheia(Fila *f) {
    return (f->quantidade == TAM_FILA);
}

// --- Verifica se a fila está vazia ---
int filaVazia(Fila *f) {
    return (f->quantidade == 0);
}

// --- Gera automaticamente uma peça ---
Peca gerarPeca(Fila *f) {
    Peca nova;
    nova.id = f->proximoID++;
    nova.tipo = 'A' + (rand() % 5); // gera tipos A, B, C, D, E
    return nova;
}

// --- Insere peça no final da fila (enqueue) ---
void enqueue(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("⚠️  Fila cheia! Não é possível inserir.\n");
        return;
    }

    f->fila[f->fim] = p;
    f->fim = (f->fim + 1) % TAM_FILA;
    f->quantidade++;
}

// --- Remove peça da frente da fila (dequeue) ---
Peca dequeue(Fila *f) {
    Peca removida = {0, 0};
    if (filaVazia(f)) {
        printf("⚠️  Fila vazia! Nenhuma peça para remover.\n");
        return removida;
    }

    removida = f->fila[f->inicio];
    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->quantidade--;
    return removida;
}

// --- Mostra o estado atual da fila ---
void mostrarFila(Fila *f) {
    printf("\n=== ESTADO ATUAL DA FILA ===\n");
    if (filaVazia(f)) {
        printf("📦 A fila está vazia.\n");
        return;
    }

    printf("%-5s %-5s\n", "ID", "Tipo");
    printf("-------------\n");

    int i = f->inicio;
    for (int count = 0; count < f->quantidade; count++) {
        printf("%-5d %-5c\n", f->fila[i].id, f->fila[i].tipo);
        i = (i + 1) % TAM_FILA;
    }
}


