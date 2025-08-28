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
