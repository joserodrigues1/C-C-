#include <stdio.h>
#include <stdlib.h>

// Define a capacidade máxima da fila
#define MAX_FILA 10

// --- ESTRUTURA DA FILA ---
typedef struct {
    int itens[MAX_FILA]; // Vetor para armazenar os elementos
    int inicio;          // Índice do primeiro elemento
    int fim;             // Índice do último elemento
    int quantidade;      // Número de elementos na fila
} Fila;

// --- PROTÓTIPOS DAS FUNÇÕES ---
void inicializarFila(Fila *f);
int filaVazia(Fila *f);
int filaCheia(Fila *f);
void enfileirar(Fila *f, int valor);
int desenfileirar(Fila *f);
void mostrarTodos(Fila *f);
int pesquisarElemento(Fila *f, int valor);
void mostrarElementoPosicao(Fila *f, int pos);
void limparBuffer();

// --- FUNÇÃO PRINCIPAL ---
int main() {
    Fila minhaFila;
    int opcao, valor, pos;

    inicializarFila(&minhaFila);

    do {
        printf("\n--- MENU FILA NUMERICA ---\n");
        printf("1. Enfileirar (Adicionar)\n");
        printf("2. Desenfileirar (Remover)\n");
        printf("3. Pesquisar um elemento\n");
        printf("4. Mostrar elemento de uma posicao\n");
        printf("5. Mostrar todos os elementos\n");
        printf("0. Sair\n");
        printf("--------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                if (filaCheia(&minhaFila)) {
                    printf("\nERRO: A fila esta cheia! Nao e possivel adicionar.\n");
                } else {
                    printf("Digite o numero para enfileirar: ");
                    scanf("%d", &valor);
                    limparBuffer();
                    enfileirar(&minhaFila, valor);
                }
                break;

            case 2:
                if (filaVazia(&minhaFila)) {
                    printf("\nERRO: A fila esta vazia! Nao ha o que remover.\n");
                } else {
                    valor = desenfileirar(&minhaFila);
                    printf("\nElemento %d removido do inicio da fila.\n", valor);
                }
                break;

            case 3:
                if (filaVazia(&minhaFila)) {
                    printf("\nA fila esta vazia. Nao ha o que pesquisar.\n");
                } else {
                    printf("Digite o numero que deseja pesquisar: ");
                    scanf("%d", &valor);
                    limparBuffer();
                    pos = pesquisarElemento(&minhaFila, valor);
                    if (pos != -1) {
                        printf("\nO elemento %d foi encontrado na posicao %d da fila.\n", valor, pos);
                    } else {
                        printf("\nO elemento %d NAO foi encontrado na fila.\n", valor);
                    }
                }
                break;

            case 4:
                 if (filaVazia(&minhaFila)) {
                    printf("\nA fila esta vazia.\n");
                } else {
                    printf("Digite a posicao que deseja ver (0 = primeiro elemento): ");
                    scanf("%d", &pos);
                    limparBuffer();
                    mostrarElementoPosicao(&minhaFila, pos);
                }
                break;

            case 5:
                mostrarTodos(&minhaFila);
                break;

            case 0:
                printf("\nEncerrando o programa...\n");
                break;

            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}

// --- IMPLEMENTAÇÃO DAS FUNÇÕES ---

/**
 * @brief Inicializa a fila, marcando-a como vazia.
 */
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = -1;
    f->quantidade = 0;
}

/**
 * @brief Verifica se a fila está vazia.
 */
int filaVazia(Fila *f) {
    return f->quantidade == 0;
}

/**
 * @brief Verifica se a fila está cheia.
 */
int filaCheia(Fila *f) {
    return f->quantidade == MAX_FILA;
}

/**
 * @brief Adiciona um elemento no final da fila (lógica circular).
 */
void enfileirar(Fila *f, int valor) {
    // A verificação de fila cheia é feita na main
    f->fim = (f->fim + 1) % MAX_FILA; // Avança o 'fim' de forma circular
    f->itens[f->fim] = valor;
    f->quantidade++;
    printf("\nElemento %d adicionado a fila.\n", valor);
}

/**
 * @brief Remove um elemento do início da fila (lógica circular).
 */
int desenfileirar(Fila *f) {
    // A verificação de fila vazia é feita na main
    int valorRemovido = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX_FILA; // Avança o 'inicio' de forma circular
    f->quantidade--;
    return valorRemovido;
}

/**
 * @brief Mostra todos os elementos da fila, do início ao fim.
 */
void mostrarTodos(Fila *f) {
    if (filaVazia(f)) {
        printf("\n>> A fila esta vazia. <<\n");
        return;
    }

    printf("\n--- Elementos na Fila ---\n");
    printf("Inicio -> ");
    int i = f->inicio;
    int count;
    for (count = 0; count < f->quantidade; count++) {
        printf("[%d] ", f->itens[i]);
        i = (i + 1) % MAX_FILA; // Move para o próximo índice de forma circular
    }
    printf("<- Fim\n");
    printf("---------------------------\n");
}

/**
 * @brief Pesquisa por um elemento na fila.
 * @return A posição lógica do elemento (0 para o primeiro) se encontrado, ou -1 se não.
 */
int pesquisarElemento(Fila *f, int valor) {
    int i = f->inicio;
    int count;
    for (count = 0; count < f->quantidade; count++) {
        if (f->itens[i] == valor) {
            return count; // Retorna a posição lógica (0, 1, 2...)
        }
        i = (i + 1) % MAX_FILA;
    }
    return -1; // Não encontrou
}

/**
 * @brief Mostra o elemento em uma posição lógica específica.
 */
void mostrarElementoPosicao(Fila *f, int pos) {
    if (pos < 0 || pos >= f->quantidade) {
        printf("\nERRO: Posicao invalida! A fila tem %d elementos (posicoes de 0 a %d).\n", f->quantidade, f->quantidade - 1);
        return;
    }

    // Calcula o índice real no vetor circular
    int indiceReal = (f->inicio + pos) % MAX_FILA;
    printf("\nO elemento na posicao %d e: %d\n", pos, f->itens[indiceReal]);
}

/**
 * @brief Limpa o buffer de entrada do teclado.
 */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
