/*
 * Projeto: Desafio Free Fire - Edição Mestre
 * Nível: Mestre (Ordenação, Busca e Performance)
 * Autor: Rico Player
 * Data: 25/11/2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>   // Necessário para clock()
#include <locale.h>
#include <stdbool.h>

#define MAX_ITENS 20

// 1. Criação da Struct para o Loot
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade; // 1 a 10
} Item;

// --- PROTÓTIPOS ---
void cadastrarItem(Item lista[], int *qtd);
void listarItens(Item lista[], int qtd);
void bubbleSortNome(Item lista[], int qtd, long *comps, double *tempo);
void insertionSortTipo(Item lista[], int qtd, long *comps, double *tempo);
void selectionSortPrioridade(Item lista[], int qtd, long *comps, double *tempo);
void buscaBinariaPorNome(Item lista[], int qtd, bool ordenadoPorNome);
void removerQuebraLinha(char *string);
void limparBuffer();
void limparTela();

// --- MAIN ---
int main() {
    setlocale(LC_ALL, "Portuguese");

    Item mochila[MAX_ITENS];
    int qtdAtual = 0;
    int opcao = 0;
    
    // Variáveis para armazenar estatísticas de desempenho
    long comparacoes = 0;
    double tempoGasto = 0.0;
    bool ordenadoPorNome = false; // Controle para busca binária

    do {
        limparTela();
        printf("\n=== 🔥 DESAFIO FREE FIRE: NIVEL MESTRE 🔥 ===\n");
        printf("Loot na Mochila: %d/%d\n", qtdAtual, MAX_ITENS);
        printf("Status Busca Binária: %s\n", ordenadoPorNome ? "[ATIVO]" : "[BLOQUEADO - Ordene por Nome]");
        printf("---------------------------------------------\n");
        printf("1. Adicionar Item ao Loot\n");
        printf("2. Listar Mochila\n");
        printf("3. Ordenar por NOME (Bubble Sort)\n");
        printf("4. Ordenar por TIPO (Insertion Sort)\n");
        printf("5. Ordenar por PRIORIDADE (Selection Sort)\n");
        printf("6. Buscar Item Específico (Busca Binária)\n");
        printf("0. Sair\n");
        printf("Escolha sua estratégia: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch(opcao) {
            case 1:
                cadastrarItem(mochila, &qtdAtual);
                ordenadoPorNome = false; // Bagunçou a ordem
                break;
            case 2:
                listarItens(mochila, qtdAtual);
                printf("\nEnter para voltar...");
                getchar();
                break;
            case 3:
                bubbleSortNome(mochila, qtdAtual, &comparacoes, &tempoGasto);
                printf("\n📊 PERFORMANCE DO BUBBLE SORT:\n");
                printf("   - Comparações: %ld\n", comparacoes);
                printf("   - Tempo: %f ms\n", tempoGasto);
                ordenadoPorNome = true; // Habilita a busca binária
                printf("\nEnter para continuar...");
                getchar();
                break;
            case 4:
                insertionSortTipo(mochila, qtdAtual, &comparacoes, &tempoGasto);
                printf("\n📊 PERFORMANCE DO INSERTION SORT:\n");
                printf("   - Comparações: %ld\n", comparacoes);
                printf("   - Tempo: %f ms\n", tempoGasto);
                ordenadoPorNome = false; 
                printf("\nEnter para continuar...");
                getchar();
                break;
            case 5:
                selectionSortPrioridade(mochila, qtdAtual, &comparacoes, &tempoGasto);
                printf("\n📊 PERFORMANCE DO SELECTION SORT:\n");
                printf("   - Comparações: %ld\n", comparacoes);
                printf("   - Tempo: %f ms\n", tempoGasto);
                ordenadoPorNome = false;
                printf("\nEnter para continuar...");
                getchar();
                break;
            case 6:
                buscaBinariaPorNome(mochila, qtdAtual, ordenadoPorNome);
                printf("\nEnter para continuar...");
                getchar();
                break;
            case 0:
                printf("Saindo do Lobby... Booyah!\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}

// --- IMPLEMENTAÇÃO DAS FUNÇÕES ---

void cadastrarItem(Item lista[], int *qtd) {
    if (*qtd >= MAX_ITENS) {
        printf("\n[!] Mochila cheia! Você precisa dropar algo.\n");
        getchar();
        return;
    }

    printf("\n--- NOVO ITEM DE LOOT ---\n");
    printf("Nome (ex: AK-47, Kit Medico): ");
    fgets(lista[*qtd].nome, 30, stdin);
    removerQuebraLinha(lista[*qtd].nome);

    printf("Tipo (ex: Arma, Cura, Municao): ");
    fgets(lista[*qtd].tipo, 20, stdin);
    removerQuebraLinha(lista[*qtd].tipo);

    printf("Prioridade (1-Alta a 10-Baixa): ");
    scanf("%d", &lista[*qtd].prioridade);
    limparBuffer();

    (*qtd)++;
    printf(">> Item adicionado à mochila!\n");
}

void listarItens(Item lista[], int qtd) {
    printf("\n%-20s | %-15s | %s\n", "NOME", "TIPO", "PRIORIDADE");
    printf("----------------------------------------------------\n");
    for (int i = 0; i < qtd; i++) {
        printf("%-20s | %-15s | %d\n", 
               lista[i].nome, lista[i].tipo, lista[i].prioridade);
    }
}

// 3. Bubble Sort: Ordenar por NOME
void bubbleSortNome(Item lista[], int qtd, long *comps, double *tempo) {
    *comps = 0;
    clock_t inicio = clock();

    int i, j;
    Item aux;

    for (i = 0; i < qtd - 1; i++) {
        for (j = 0; j < qtd - i - 1; j++) {
            (*comps)++;
            if (strcmp(lista[j].nome, lista[j+1].nome) > 0) {
                aux = lista[j];
                lista[j] = lista[j+1];
                lista[j+1] = aux;
            }
        }
    }

    clock_t fim = clock();
    *tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000.0;
    
    printf("\n>> Mochila organizada por NOME (Bubble Sort)!\n");
    listarItens(lista, qtd);
}

// 4. Insertion Sort: Ordenar por TIPO
void insertionSortTipo(Item lista[], int qtd, long *comps, double *tempo) {
    *comps = 0;
    clock_t inicio = clock();

    int i, j;
    Item chave;

    for (i = 1; i < qtd; i++) {
        chave = lista[i];
        j = i - 1;

        while (j >= 0) {
            (*comps)++;
            if (strcmp(lista[j].tipo, chave.tipo) > 0) {
                lista[j + 1] = lista[j];
                j = j - 1;
            } else {
                break;
            }
        }
        lista[j + 1] = chave;
    }

    clock_t fim = clock();
    *tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000.0;

    printf("\n>> Mochila organizada por TIPO (Insertion Sort)!\n");
    listarItens(lista, qtd);
}

// 5. Selection Sort: Ordenar por PRIORIDADE
void selectionSortPrioridade(Item lista[], int qtd, long *comps, double *tempo) {
    *comps = 0;
    clock_t inicio = clock();

    int i, j, min_idx;
    Item aux;

    for (i = 0; i < qtd - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < qtd; j++) {
            (*comps)++;
            // Prioridade: Menor número (1) é mais importante, então vem primeiro
            if (lista[j].prioridade < lista[min_idx].prioridade) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            aux = lista[i];
            lista[i] = lista[min_idx];
            lista[min_idx] = aux;
        }
    }

    clock_t fim = clock();
    *tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000.0;

    printf("\n>> Mochila organizada por PRIORIDADE (Selection Sort)!\n");
    listarItens(lista, qtd);
}

// 6. Busca Binária
void buscaBinariaPorNome(Item lista[], int qtd, bool ordenadoPorNome) {
    if (!ordenadoPorNome) {
        printf("\n[ERRO] A mochila precisa estar ordenada por NOME (Opção 3)!\n");
        return;
    }

    char busca[30];
    printf("\nDigite o nome do item para buscar: ");
    fgets(busca, 30, stdin);
    removerQuebraLinha(busca);

    int inicio = 0, fim = qtd - 1, meio;
    bool achou = false;

    printf("Vasculhando a mochila...\n");

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        int cmp = strcmp(lista[meio].nome, busca);

        if (cmp == 0) {
            printf("\n>>> ITEM ENCONTRADO! <<<\n");
            printf("Nome: %s | Tipo: %s | Prioridade: %d\n", 
                   lista[meio].nome, lista[meio].tipo, lista[meio].prioridade);
            achou = true;
            break;
        } else if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    if (!achou) printf("\n[!] Item '%s' não encontrado.\n", busca);
}

void removerQuebraLinha(char *string) {
    size_t len = strlen(string);
    if (len > 0 && string[len - 1] == '\n') string[len - 1] = '\0';
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
