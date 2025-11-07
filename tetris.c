#include <stdio.h>

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.


    // 🧩 Nível Novato: Fila de Peças Futuras
    //
    // - Crie uma struct Peca com os campos: tipo (char) e id (int).
    // - Implemente uma fila circular com capacidade para 5 peças.
    // - Crie funções como inicializarFila(), enqueue(), dequeue(), filaCheia(), filaVazia().
    // - Cada peça deve ser gerada automaticamente com um tipo aleatório e id sequencial.
    // - Exiba a fila após cada ação com uma função mostrarFila().
    // - Use um menu com opções como:
    //      1 - Jogar peça (remover da frente)
    //      0 - Sair
    // - A cada remoção, insira uma nova peça ao final da fila.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_NOME 20

// --- Estrutura que representa uma peça ---
typedef struct {
    int id;
    char tipo[TAM_NOME];
} Peca;

// --- Estrutura da fila circular ---
typedef struct {
    Peca fila[TAM_FILA];
    int inicio;
    int fim;
    int quantidade;
} Fila;

// --- Protótipos ---
void inicializarFila(Fila *f);
void exibirFila(Fila *f);
Peca gerarPeca();
void enfileirar(Fila *f, Peca p);
void desenfileirar(Fila *f);

int main() {
    srand(time(NULL));

    Fila fila;
    inicializarFila(&fila);

    int opcao;

    do {
        printf("\n=== MENU FILA DE PECAS ===\n");
        printf("1. Visualizar fila\n");
        printf("2. Jogar (remover) peça\n");
        printf("3. Inserir nova peça\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // consome o '\n'

        switch (opcao) {
            case 1:
                exibirFila(&fila);
                break;
            case 2:
                desenfileirar(&fila);
                break;
            case 3:
                enfileirar(&fila, gerarPeca());
                break;
            case 0:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }

    } while (opcao != 0);

    return 0;
}

// --- Inicializa a fila com 5 peças automáticas ---
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->quantidade = 0;

    for (int i = 0; i < TAM_FILA; i++) {
        enfileirar(f, gerarPeca());
    }
}

// --- Gera uma peça automaticamente ---
Peca gerarPeca() {
    Peca nova;
    nova.id = rand() % 1000; // id aleatório
    const char *tipos[] = {"Cubo", "Esfera", "Cilindro", "Cone", "Pirâmide"};
    int indice = rand() % 5;
    snprintf(nova.tipo, TAM_NOME, "%s", tipos[indice]);
    return nova;
}

// --- Enfileira uma nova peça (insere no fim da fila circular) ---
void enfileirar(Fila *f, Peca p) {
    if (f->quantidade == TAM_FILA) {
        printf("⚠️  Fila cheia! Sobrescrevendo a peça mais antiga...\n");
        // Avança o início para sobrescrever a mais antiga
        f->inicio = (f->inicio + 1) % TAM_FILA;
        f->quantidade--;
    }

    f->fila[f->fim] = p;
    f->fim = (f->fim + 1) % TAM_FILA;
    f->quantidade++;

    printf("✅ Peça inserida: ID=%d | Tipo=%s\n", p.id, p.tipo);
}

// --- Remove a peça da frente da fila ---
void desenfileirar(Fila *f) {
    if (f->quantidade == 0) {
        printf("⚠️  A fila está vazia! Nenhuma peça para jogar.\n");
        return;
    }

    Peca removida = f->fila[f->inicio];
    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->quantidade--;

    printf("🧩 Peça jogada (removida): ID=%d | Tipo=%s\n", removida.id, removida.tipo);
}

// --- Exibe o estado atual da fila ---
void exibirFila(Fila *f) {
    if (f->quantidade == 0) {
        printf("📦 Fila vazia!\n");
        return;
    }

    printf("\n=== FILA ATUAL ===\n");
    printf("%-5s %-10s\n", "ID", "TIPO");
    printf("------------------\n");

    int i = f->inicio;
    for (int count = 0; count < f->quantidade; count++) {
        printf("%-5d %-10s\n", f->fila[i].id, f->fila[i].tipo);
        i = (i + 1) % TAM_FILA;
    }
}



    // 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
    //
    // - Implemente interações avançadas entre as estruturas:
    //      4 - Trocar a peça da frente da fila com o topo da pilha
    //      5 - Trocar os 3 primeiros da fila com as 3 peças da pilha
    // - Para a opção 4:
    //      Verifique se a fila não está vazia e a pilha tem ao menos 1 peça.
    //      Troque os elementos diretamente nos arrays.
    // - Para a opção 5:
    //      Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
    //      Use a lógica de índice circular para acessar os primeiros da fila.
    // - Sempre valide as condições antes da troca e informe mensagens claras ao usuário.
    // - Use funções auxiliares, se quiser, para modularizar a lógica de troca.
    // - O menu deve ficar assim:
    //      4 - Trocar peça da frente com topo da pilha
    //      5 - Trocar 3 primeiros da fila com os 3 da pilha



