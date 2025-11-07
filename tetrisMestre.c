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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

// --- Estrutura que representa uma peça ---
typedef struct {
    char tipo;
    int id;
} Peca;

// --- Estrutura da fila circular ---
typedef struct {
    Peca fila[TAM_FILA];
    int inicio;
    int fim;
    int quantidade;
    int proximoID;
} Fila;

// --- Estrutura da pilha ---
typedef struct {
    Peca pilha[TAM_PILHA];
    int topo;
} Pilha;

// --- Protótipos ---
void inicializarFila(Fila *f);
void inicializarPilha(Pilha *p, Fila *f);
int filaCheia(Fila *f);
int filaVazia(Fila *f);
int pilhaCheia(Pilha *p);
int pilhaVazia(Pilha *p);
Peca gerarPeca(Fila *f);
void enqueue(Fila *f, Peca p);
Peca dequeue(Fila *f);
void push(Pilha *p, Peca p);
Peca pop(Pilha *p);
void mostrarFila(Fila *f);
void mostrarPilha(Pilha *p);
void trocarFrenteFilaTopoPilha(Fila *f, Pilha *p);
void trocarTresPrimeiros(Fila *f, Pilha *p);

int main() {
    srand(time(NULL));

    Fila fila;
    Pilha pilha;
    inicializarFila(&fila);
    inicializarPilha(&pilha, &fila);

    int opcao;

    do {
        printf("\n===== MENU DE CONTROLE =====\n");
        printf("1 - Jogar peça (remover da fila)\n");
        printf("2 - Mostrar fila\n");
        printf("3 - Mostrar pilha\n");
        printf("4 - Trocar peça da frente com topo da pilha\n");
        printf("5 - Trocar 3 primeiros da fila com os 3 da pilha\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: {
                if (!filaVazia(&fila)) {
                    Peca jogada = dequeue(&fila);
                    printf("\n🧩 Peça jogada: ID=%d | Tipo=%c\n", jogada.id, jogada.tipo);
                    enqueue(&fila, gerarPeca(&fila));
                } else {
                    printf("⚠️  Fila vazia!\n");
                }
                mostrarFila(&fila);
                break;
            }

            case 2:
                mostrarFila(&fila);
                break;

            case 3:
                mostrarPilha(&pilha);
                break;

            case 4:
                trocarFrenteFilaTopoPilha(&fila, &pilha);
                break;

            case 5:
                trocarTresPrimeiros(&fila, &pilha);
                break;

            case 0:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}

// --- Inicializações ---
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

void inicializarPilha(Pilha *p, Fila *f) {
    p->topo = -1;
    for (int i = 0; i < TAM_PILHA; i++) {
        push(p, gerarPeca(f));
    }
    printf("\nPilha inicializada com 3 peças!\n");
    mostrarPilha(p);
}

// --- Operações de fila ---
int filaCheia(Fila *f) { return f->quantidade == TAM_FILA; }
int filaVazia(Fila *f) { return f->quantidade == 0; }

void enqueue(Fila *f, Peca p) {
    if (filaCheia(f)) return;
    f->fila[f->fim] = p;
    f->fim = (f->fim + 1) % TAM_FILA;
    f->quantidade++;
}

Peca dequeue(Fila *f) {
    Peca removida = {0, 0};
    if (filaVazia(f)) return removida;
    removida = f->fila[f->inicio];
    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->quantidade--;
    return removida;
}

// --- Operações de pilha ---
int pilhaCheia(Pilha *p) { return p->topo == TAM_PILHA - 1; }
int pilhaVazia(Pilha *p) { return p->topo == -1; }

void push(Pilha *p, Peca peca) {
    if (pilhaCheia(p)) return;
    p->pilha[++p->topo] = peca;
}

Peca pop(Pilha *p) {
    Peca removida = {0, 0};
    if (pilhaVazia(p)) return removida;
    return p->pilha[p->topo--];
}

// --- Gera peça ---
Peca gerarPeca(Fila *f) {
    Peca nova;
    nova.id = f->proximoID++;
    nova.tipo = 'A' + (rand() % 5);
    return nova;
}

// --- Exibição ---
void mostrarFila(Fila *f) {
    printf("\n=== FILA ===\n");
    if (filaVazia(f)) {
        printf("Fila vazia.\n");
        return;
    }
    printf("%-5s %-5s\n", "ID", "Tipo");
    printf("-------------\n");

    int i = f->inicio;
    for (int c = 0; c < f->quantidade; c++) {
        printf("%-5d %-5c\n", f->fila[i].id, f->fila[i].tipo);
        i = (i + 1) % TAM_FILA;
    }
}

void mostrarPilha(Pilha *p) {
    printf("\n=== PILHA ===\n");
    if (pilhaVazia(p)) {
        printf("Pilha vazia.\n");
        return;
    }
    printf("%-5s %-5s\n", "ID", "Tipo");
    printf("-------------\n");
    for (int i = p->topo; i >= 0; i--) {
        printf("%-5d %-5c\n", p->pilha[i].id, p->pilha[i].tipo);
    }
}

// --- Trocas ---
void trocarFrenteFilaTopoPilha(Fila *f, Pilha *p) {
    if (filaVazia(f) || pilhaVazia(p)) {
        printf("⚠️  Não é possível trocar — fila ou pilha vazia.\n");
        return;
    }

    Peca temp = f->fila[f->inicio];
    f->fila[f->inicio] = p->pilha[p->topo];
    p->pilha[p->topo] = temp;

    printf("\n🔄 Peça da frente da fila e topo da pilha foram trocados!\n");
    mostrarFila(f);
    mostrarPilha(p);
}

void trocarTresPrimeiros(Fila *f, Pilha *p) {
    if (f->quantidade < 3 || p->topo != 2) {
        printf("⚠️  É necessário ter 3 peças na pilha e ao menos 3 na fila.\n");
        return;
    }

    for (int i = 0; i < 3; i++) {
        int idxFila = (f->inicio + i) % TAM_FILA;
        Peca temp = f->fila[idxFila];
        f->fila[idxFila] = p->pilha[i];
        p->pilha[i] = temp;
    }

    printf("\n🔄 As 3 primeiras peças da fila e as 3 da pilha foram trocadas!\n");
    mostrarFila(f);
    mostrarPilha(p);
}
