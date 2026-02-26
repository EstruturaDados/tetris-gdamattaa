#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

#define MAX 5

// =================================
// Estrutura que representa uma peça
// =================================
typedef struct {
    char tipo;  // Tipo da peça ('I', 'O', 'T', 'L')
    int id;     // Identificador único
} Peca;

// ==========================
// Estrutura da Fila Circular
// ==========================
typedef struct {
    Peca itens[MAX];
    int inicio;
    int fim;
    int tamanho;
} Fila;

// ==========================================
// Variável global para gerar IDs sequenciais
// ==========================================
int proximoId = 0;

// ==========================================
// Função para gerar uma peça automaticamente
// ==========================================
Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;

    nova.tipo = tipos[rand() % 4];  //Sorteia tipo
    nova.id = proximoId++;          //ID sequencial

    return nova;
}

// =====================
// Inicialização da fila
// =====================
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->tamanho = 0;
}

// ===============================
// Verificação se a fila está vazia
// ===============================
int filaVazia(Fila *f) {
    return f->tamanho == 0;
}

// ===============================
// Verificação se a fila está cheia
// ===============================
int filaCheia(Fila *f) {
    return f->tamanho == MAX;
}

// ===============================
// Inserção de peça na fila (enqueue)
// ===============================
void enqueue(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("\n⚠ A fila está cheia! Não é possível inserir.\n");
        return;
    }

    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX;
    f->tamanho++;
}

// ===============================
// Remoção peça da fila (dequeue)
// ===============================
Peca dequeue(Fila *f) {
    Peca removida;

    if (filaVazia(f)) {
        printf("\n⚠ A fila está vazia!\n");
        removida.tipo = '?';
        removida.id = -1;
        return removida;
    }

    removida = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->tamanho--;

    return removida;
}

// ==================================
// Peek da fila (Mostra estado atual)
// ==================================
void mostrarFila(Fila *f) {
    printf("\nFila de peças:\n");

    if (filaVazia(f)) {
        printf("[vazia]\n");
        return;
    }

    int i;
    int indice = f->inicio;

    for (i = 0; i < f->tamanho; i++) {
        printf("[%c %d] ", f->itens[indice].tipo, f->itens[indice].id);
        indice = (indice + 1) % MAX;
    }

    printf("\n");
}


// ================
// Função principal

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
// ================

int main() {
    Fila fila;
    int opcao;

    srand(time(NULL));  //Inicializa gerador aleatório

    inicializarFila(&fila);

    //Inicializa fila com 5 peças
    for (int i = 0; i < MAX; i++) {
        enqueue(&fila, gerarPeca());
    }

    do {
        mostrarFila(&fila);

        printf("\nOpções:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Peca jogada = dequeue(&fila);
                if (jogada.id != -1) {
                    printf("\nPeça jogada: [%c %d]\n", jogada.tipo, jogada.id);

                    //Regra do desafio: ao remover, inserir nova automaticamente
                    enqueue(&fila, gerarPeca());
                }
                break;
            }

            case 2:
                enqueue(&fila, gerarPeca());
                break;

            case 0:
                printf("\nEncerrando o jogo...\n");
                break;

            default:
                printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}

//=================================================================================================================

    // 🧠 Nível Aventureiro: Adição da Pilha de Reserva
    //
    // - Implemente uma pilha linear com capacidade para 3 peças.
    // - Crie funções como inicializarPilha(), push(), pop(), pilhaCheia(), pilhaVazia().
    // - Permita enviar uma peça da fila para a pilha (reserva).
    // - Crie um menu com opção:
    //      2 - Enviar peça da fila para a reserva (pilha)
    //      3 - Usar peça da reserva (remover do topo da pilha)
    // - Exiba a pilha junto com a fila após cada ação com mostrarPilha().
    // - Mantenha a fila sempre com 5 peças (repondo com gerarPeca()).


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

