/*  Benchmark de métodos de ordenação

    O código a seguir é um compilado de todos os métodos de ordenação
    estudados na disciplina de Estrutura de Dados 1. Seu objetivo é comparar
    métricas relevantes de desempenho, como o tempo de execução, e entender
    os cenários para aplicação ideal de cada um.

    Antes do main(), estão macros úteis e as definições das funções,
    programadas ao final. O programa gera nove vetores de base, que
    são copiados logo antes do uso, em cada método.

    Todos os algoritmos são avaliados com vetores de 5, 10 e 50 mil elementos,
    de modo aleatório, ordenado e inverso, totalizando 9 modos. As métricas
    verificadas são a quantidade de atribuições, comparações e tempo em milissegundos.

    Com foco no estudo realizado, o código apresenta a falha de Stack Overflow
    ao tentar organizar o vetor já ordenado de 50 mil elementos com Quick Sort.
    O erro consiste na sobrecarga da memória da pilha de execução, parte importante
    da análise desenvolvida, motivo pelo qual foi feito desse modo.

*/

#include <stdio.h>
#include <stdlib.h>
// Para utilizar o time() como semente do rand()
#include <time.h>
// Para utilizar a memcpy() e copiar os vetores para cada uso
#include <string.h>

// Tamanho dos vetores de teste e faixa para os valores aleatórios
#define VETOR_5K 5000
#define VETOR_10K 10000
#define VETOR_50K 50000

#define FAIXA_VALORES 30000

// Struct para retornar as ações realizadas durante a ordenação
// O tipo de variável permite maior capacidade para vetores grandes
typedef struct{
    unsigned long long comparacoes;
    unsigned long long atribuicoes;
}Metricas;

//----------------------------------------------------------------------
// Métodos de ordenação:

Metricas countingSort(int vetor[], int tamanho);
//----------------------------------------------------------------------
Metricas insertionSort(int vetor[], int tamanho);
//----------------------------------------------------------------------
Metricas selectionSort(int vetor[], int tamanho);
//----------------------------------------------------------------------
void swap(int *valor1, int *valor2);
int partition(int vetor[], int inicio, int fim, Metricas *valores);
void quickSort(int vetor[], int inicio, int fim, Metricas *valores);
//----------------------------------------------------------------------
void merge(int vetor[], int inicio, int meio, int fim, Metricas *valores);
void mergeSort(int vetor[], int inicio, int fim, Metricas *valores);
//----------------------------------------------------------------------
// Função para testes: imprime o vetor entre colchetes

void imprimirVetor(int vetor[], int tamanho);
//----------------------------------------------------------------------
int main(){
    system("title Benchmark metodos de ordenacao");
    system("cls");

    // Utiliza o retorno de time() (segundos) para definir a semente do rand()
    srand(time(NULL));

    // Caso não definido, o tamanho do vetor deverá ser verificado:
    // Tamanho total / tamanho do tipo (bytes)
    // int tamanho = sizeof(vetor) / sizeof(vetor[0]);
    // Para reduzir as repetições e por saber o intervalo, não será usado

    // Copiar vetor:
    // memcpy(copia, origem, tamanho * sizeof(tipo));

    // Declaração e alocação de memória para os vetores de base:

    // Aleatório
    int *aleatorio5k = (int*)malloc(VETOR_5K * sizeof(int));
    int *aleatorio10k = (int*)malloc(VETOR_10K * sizeof(int));
    int *aleatorio50k = (int*)malloc(VETOR_50K * sizeof(int));

    // Ordenados
    int *ordenado5k = (int*)malloc(VETOR_5K * sizeof(int));
    int *ordenado10k = (int*)malloc(VETOR_10K * sizeof(int));
    int *ordenado50k = (int*)malloc(VETOR_50K * sizeof(int));

    // Inversos
    int *inverso5k = (int*)malloc(VETOR_5K * sizeof(int));
    int *inverso10k = (int*)malloc(VETOR_10K * sizeof(int));
    int *inverso50k = (int*)malloc(VETOR_50K * sizeof(int));


    // Preenchimento dos vetores de base:

    for(int i = 0; i < VETOR_5K; i++){

        // Aleatório, ordenado, inverso
        aleatorio5k[i] = rand() % FAIXA_VALORES;
        ordenado5k[i] = i;
        inverso5k[i] = (VETOR_5K - 1) - i;
    }

    for(int i = 0; i < VETOR_10K; i++){

        // Aleatório, ordenado, inverso
        aleatorio10k[i] = rand() % FAIXA_VALORES;
        ordenado10k[i] = i;
        inverso10k[i] = (VETOR_10K - 1) - i;
    }

    for(int i = 0; i < VETOR_50K; i++){

        // Aleatório, ordenado, inverso
        aleatorio50k[i] = rand() % FAIXA_VALORES;
        ordenado50k[i] = i;
        inverso50k[i] = (VETOR_50K - 1) - i;
    }

    // Vetores para cópia e ordenação
    int *copia5k = (int*)malloc(VETOR_5K * sizeof(int));
    int *copia10k = (int*)malloc(VETOR_10K * sizeof(int));
    int *copia50k = (int*)malloc(VETOR_50K * sizeof(int));

    
    // Variáveis para guardar os clocks do processador e calcular o tempo decorrido
    clock_t inicio, fim;
    double milissegundos;
    
    // Struct que contém a quantidade de comparações e atribuições
    Metricas metricas;

    //----------------------------------------------------------------------
    // Counting Sort
    printf("Counting Sort:");
    
    // Aleatório 5k
    metricas.comparacoes = 0;
    metricas.atribuicoes = 0;
    memcpy(copia5k, aleatorio5k, VETOR_5K * sizeof(int));
    inicio = clock();
    metricas = countingSort(copia5k, VETOR_5K);
    fim = clock();
    milissegundos = (((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000);
    printf("\n\nAleatorio 5k: \t%10llu comparacoes, %10llu atribuicoes, %10.2f milissegundos", metricas.comparacoes, metricas.atribuicoes, milissegundos);

    // Ordenado 5k
    metricas.comparacoes = 0;
    metricas.atribuicoes = 0;
    memcpy(copia5k, ordenado5k, VETOR_5K * sizeof(int));
    inicio = clock();
    metricas = countingSort(copia5k, VETOR_5K);
    fim = clock();
    milissegundos = (((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000);
    printf("\nOrdenado 5k: \t%10llu comparacoes, %10llu atribuicoes, %10.2f milissegundos", metricas.comparacoes, metricas.atribuicoes, milissegundos);

    // Inverso 5k
    metricas.comparacoes = 0;
    metricas.atribuicoes = 0;
    memcpy(copia5k, inverso5k, VETOR_5K * sizeof(int));
    inicio = clock();
    metricas = countingSort(copia5k, VETOR_5K);
    fim = clock();
    milissegundos = (((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000);
    printf("\nInverso 5k: \t%10llu comparacoes, %10llu atribuicoes, %10.2f milissegundos", metricas.comparacoes, metricas.atribuicoes, milissegundos);

    // Aleatório 10k
    metricas.comparacoes = 0;
    metricas.atribuicoes = 0;
    memcpy(copia10k, aleatorio10k, VETOR_10K * sizeof(int));
    inicio = clock();
    metricas = countingSort(copia10k, VETOR_10K);
    fim = clock();
    milissegundos = (((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000);
    printf("\n\nAleatorio 10k: \t%10llu comparacoes, %10llu atribuicoes, %10.2f milissegundos", metricas.comparacoes, metricas.atribuicoes, milissegundos);

    // Ordenado 10k
    metricas.comparacoes = 0;
    metricas.atribuicoes = 0;
    memcpy(copia10k, ordenado10k, VETOR_10K * sizeof(int));
    inicio = clock();
    metricas = countingSort(copia10k, VETOR_10K);
    fim = clock();
    milissegundos = (((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000);
    printf("\nOrdenado 10k: \t%10llu comparacoes, %10llu atribuicoes, %10.2f milissegundos", metricas.comparacoes, metricas.atribuicoes, milissegundos);

    // Inverso 10k
    metricas.comparacoes = 0;
    metricas.atribuicoes = 0;
    memcpy(copia10k, inverso10k, VETOR_10K * sizeof(int));
    inicio = clock();
    metricas = countingSort(copia10k, VETOR_10K);
    fim = clock();
    milissegundos = (((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000);
    printf("\nInverso 10k: \t%10llu comparacoes, %10llu atribuicoes, %10.2f milissegundos", metricas.comparacoes, metricas.atribuicoes, milissegundos);

    // Aleatório 50k
    metricas.comparacoes = 0;
    metricas.atribuicoes = 0;
    memcpy(copia50k, aleatorio50k, VETOR_50K * sizeof(int));
    inicio = clock();
    metricas = countingSort(copia50k, VETOR_50K);
    fim = clock();
    milissegundos = (((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000);
    printf("\n\nAleatorio 50k: \t%10llu comparacoes, %10llu atribuicoes, %10.2f milissegundos", metricas.comparacoes, metricas.atribuicoes, milissegundos);

    // Ordenado 50k
    metricas.comparacoes = 0;
    metricas.atribuicoes = 0;
    memcpy(copia50k, ordenado50k, VETOR_50K * sizeof(int));
    inicio = clock();
    metricas = countingSort(copia50k, VETOR_50K);
    fim = clock();
    milissegundos = (((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000);
    printf("\nOrdenado 50k: \t%10llu comparacoes, %10llu atribuicoes, %10.2f milissegundos", metricas.comparacoes, metricas.atribuicoes, milissegundos);

    // Inverso 50k
    metricas.comparacoes = 0;
    metricas.atribuicoes = 0;
    memcpy(copia50k, inverso50k, VETOR_50K * sizeof(int));
    inicio = clock();
    metricas = countingSort(copia50k, VETOR_50K);
    fim = clock();
    milissegundos = (((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000);
    printf("\nInverso 50k: \t%10llu comparacoes, %10llu atribuicoes, %10.2f milissegundos", metricas.comparacoes, metricas.atribuicoes, milissegundos);

    printf("\n\nAnote os resultados antes de continuar\n\n");
    system("pause");
    system("cls");

    //----------------------------------------------------------------------
    // Insertion Sort
    printf("Insertion Sort:");

    // Aleatório 5k
    metricas.comparacoes = 0;
    metricas.atribuicoes = 0;
    memcpy(copia5k, aleatorio5k, VETOR_5K * sizeof(int));
    inicio = clock();
    metricas = insertionSort(copia5k, VETOR_5K);
    fim = clock();
    milissegundos = (((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000);
    printf("\n\nAleatorio 5k: \t%10llu comparacoes, %10llu atribuicoes, %10.2f milissegundos", metricas.comparacoes, metricas.atribuicoes, milissegundos);

    // Ordenado 5k
    metricas.comparacoes = 0;
    metricas.atribuicoes = 0;
    memcpy(copia5k, ordenado5k, VETOR_5K * sizeof(int));
    inicio = clock();
    metricas = insertionSort(copia5k, VETOR_5K);
    fim = clock();
    milissegundos = (((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000);
    printf("\nOrdenado 5k: \t%10llu comparacoes, %10llu atribuicoes, %10.2f milissegundos", metricas.comparacoes, metricas.atribuicoes, milissegundos);

    // Inverso 5k
    metricas.comparacoes = 0;
    metricas.atribuicoes = 0;
    memcpy(copia5k, inverso5k, VETOR_5K * sizeof(int));
    inicio = clock();
    metricas = insertionSort(copia5k, VETOR_5K);
    fim = clock();
    milissegundos = (((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000);
    printf("\nInverso 5k: \t%10llu comparacoes, %10llu atribuicoes, %10.2f milissegundos", metricas.comparacoes, metricas.atribuicoes, milissegundos);

    // Aleatório 10k
    metricas.comparacoes = 0;
    metricas.atribuicoes = 0;
    memcpy(copia10k, aleatorio10k, VETOR_10K * sizeof(int));
    inicio = clock();
    metricas = insertionSort(copia10k, VETOR_10K);
    fim = clock();
    milissegundos = (((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000);
    printf("\n\nAleatorio 10k: \t%10llu comparacoes, %10llu atribuicoes, %10.2f milissegundos", metricas.comparacoes, metricas.atribuicoes, milissegundos);

    // Ordenado 10k
    metricas.comparacoes = 0;
    metricas.atribuicoes = 0;
    memcpy(copia10k, ordenado10k, VETOR_10K * sizeof(int));
    inicio = clock();
    metricas = insertionSort(copia10k, VETOR_10K);
    fim = clock();
    milissegundos = (((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000);
    printf("\nOrdenado 10k: \t%10llu comparacoes, %10llu atribuicoes, %10.2f milissegundos", metricas.comparacoes, metricas.atribuicoes, milissegundos);

    // Inverso 10k
    metricas.comparacoes = 0;
    metricas.atribuicoes = 0;
    memcpy(copia10k, inverso10k, VETOR_10K * sizeof(int));
    inicio = clock();
    metricas = insertionSort(copia10k, VETOR_10K);
    fim = clock();
    milissegundos = (((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000);
    printf("\nInverso 10k: \t%10llu comparacoes, %10llu atribuicoes, %10.2f milissegundos", metricas.comparacoes, metricas.atribuicoes, milissegundos);

    // Aleatório 50k
    metricas.comparacoes = 0;
    metricas.atribuicoes = 0;
    memcpy(copia50k, aleatorio50k, VETOR_50K * sizeof(int));
    inicio = clock();
    metricas = insertionSort(copia50k, VETOR_50K);
    fim = clock();
    milissegundos = (((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000);
    printf("\n\nAleatorio 50k: \t%10llu comparacoes, %10llu atribuicoes, %10.2f milissegundos", metricas.comparacoes, metricas.atribuicoes, milissegundos);

    // Ordenado 50k
    metricas.comparacoes = 0;
    metricas.atribuicoes = 0;
    memcpy(copia50k, ordenado50k, VETOR_50K * sizeof(int));
    inicio = clock();
    metricas = insertionSort(copia50k, VETOR_50K);
    fim = clock();
    milissegundos = (((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000);
    printf("\nOrdenado 50k: \t%10llu comparacoes, %10llu atribuicoes, %10.2f milissegundos", metricas.comparacoes, metricas.atribuicoes, milissegundos);

    // Inverso 50k
    metricas.comparacoes = 0;
    metricas.atribuicoes = 0;
    memcpy(copia50k, inverso50k, VETOR_50K * sizeof(int));
    inicio = clock();
    metricas = insertionSort(copia50k, VETOR_50K);
    fim = clock();
    milissegundos = (((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000);
    printf("\nInverso 50k: \t%10llu comparacoes, %10llu atribuicoes, %10.2f milissegundos", metricas.comparacoes, metricas.atribuicoes, milissegundos);

    printf("\n\nAnote os resultados antes de continuar\n\n");
    system("pause");
    system("cls");

    //----------------------------------------------------------------------
    // Selection Sort
    printf("Selection Sort:");

    // Aleatório 5k
    metricas.comparacoes = 0;
    metricas.atribuicoes = 0;
    memcpy(copia5k, aleatorio5k, VETOR_5K * sizeof(int));
    inicio = clock();
    metricas = selectionSort(copia5k, VETOR_5K);
    fim = clock();
    milissegundos = (((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000);
    printf("\n\nAleatorio 5k: \t%10llu comparacoes, %10llu atribuicoes, %10.2f milissegundos", metricas.comparacoes, metricas.atribuicoes, milissegundos);

    // Ordenado 5k
    metricas.comparacoes = 0;
    metricas.atribuicoes = 0;
    memcpy(copia5k, ordenado5k, VETOR_5K * sizeof(int));
    inicio = clock();
    metricas = selectionSort(copia5k, VETOR_5K);
    fim = clock();
    milissegundos = (((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000);
    printf("\nOrdenado 5k: \t%10llu comparacoes, %10llu atribuicoes, %10.2f milissegundos", metricas.comparacoes, metricas.atribuicoes, milissegundos);

    // Inverso 5k
    metricas.comparacoes = 0;
    metricas.atribuicoes = 0;
    memcpy(copia5k, inverso5k, VETOR_5K * sizeof(int));
    inicio = clock();
    metricas = selectionSort(copia5k, VETOR_5K);
    fim = clock();
    milissegundos = (((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000);
    printf("\nInverso 5k: \t%10llu comparacoes, %10llu atribuicoes, %10.2f milissegundos", metricas.comparacoes, metricas.atribuicoes, milissegundos);

    // Aleatório 10k
    metricas.comparacoes = 0;
    metricas.atribuicoes = 0;
    memcpy(copia10k, aleatorio10k, VETOR_10K * sizeof(int));
    inicio = clock();
    metricas = selectionSort(copia10k, VETOR_10K);
    fim = clock();
    milissegundos = (((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000);
    printf("\n\nAleatorio 10k: \t%10llu comparacoes, %10llu atribuicoes, %10.2f milissegundos", metricas.comparacoes, metricas.atribuicoes, milissegundos);

    // Ordenado 10k
    metricas.comparacoes = 0;
    metricas.atribuicoes = 0;
    memcpy(copia10k, ordenado10k, VETOR_10K * sizeof(int));
    inicio = clock();
    metricas = selectionSort(copia10k, VETOR_10K);
    fim = clock();
    milissegundos = (((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000);
    printf("\nOrdenado 10k: \t%10llu comparacoes, %10llu atribuicoes, %10.2f milissegundos", metricas.comparacoes, metricas.atribuicoes, milissegundos);

    // Inverso 10k
    metricas.comparacoes = 0;
    metricas.atribuicoes = 0;
    memcpy(copia10k, inverso10k, VETOR_10K * sizeof(int));
    inicio = clock();
    metricas = selectionSort(copia10k, VETOR_10K);
    fim = clock();
    milissegundos = (((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000);
    printf("\nInverso 10k: \t%10llu comparacoes, %10llu atribuicoes, %10.2f milissegundos", metricas.comparacoes, metricas.atribuicoes, milissegundos);

    // Aleatório 50k
    metricas.comparacoes = 0;
    metricas.atribuicoes = 0;
    memcpy(copia50k, aleatorio50k, VETOR_50K * sizeof(int));
    inicio = clock();
    metricas = selectionSort(copia50k, VETOR_50K);
    fim = clock();
    milissegundos = (((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000);
    printf("\n\nAleatorio 50k: \t%10llu comparacoes, %10llu atribuicoes, %10.2f milissegundos", metricas.comparacoes, metricas.atribuicoes, milissegundos);

    // Ordenado 50k
    metricas.comparacoes = 0;
    metricas.atribuicoes = 0;
    memcpy(copia50k, ordenado50k, VETOR_50K * sizeof(int));
    inicio = clock();
    metricas = selectionSort(copia50k, VETOR_50K);
    fim = clock();
    milissegundos = (((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000);
    printf("\nOrdenado 50k: \t%10llu comparacoes, %10llu atribuicoes, %10.2f milissegundos", metricas.comparacoes, metricas.atribuicoes, milissegundos);

    // Inverso 50k
    metricas.comparacoes = 0;
    metricas.atribuicoes = 0;
    memcpy(copia50k, inverso50k, VETOR_50K * sizeof(int));
    inicio = clock();
    metricas = selectionSort(copia50k, VETOR_50K);
    fim = clock();
    milissegundos = (((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000);
    printf("\nInverso 50k: \t%10llu comparacoes, %10llu atribuicoes, %10.2f milissegundos", metricas.comparacoes, metricas.atribuicoes, milissegundos);

    printf("\n\nAnote os resultados antes de continuar\n\n");
    system("pause");
    system("cls");

    //----------------------------------------------------------------------
    // Merge Sort
    printf("Merge Sort:");

    // Aleatório 5k
    metricas.comparacoes = 0;
    metricas.atribuicoes = 0;
    memcpy(copia5k, aleatorio5k, VETOR_5K * sizeof(int));
    inicio = clock();
    mergeSort(copia5k, 0, VETOR_5K - 1, &metricas);
    fim = clock();
    milissegundos = (((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000);
    printf("\n\nAleatorio 5k: \t%10llu comparacoes, %10llu atribuicoes, %10.2f milissegundos", metricas.comparacoes, metricas.atribuicoes, milissegundos);

    // Ordenado 5k
    metricas.comparacoes = 0;
    metricas.atribuicoes = 0;
    memcpy(copia5k, ordenado5k, VETOR_5K * sizeof(int));
    inicio = clock();
    mergeSort(copia5k, 0, VETOR_5K - 1, &metricas);
    fim = clock();
    milissegundos = (((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000);
    printf("\nOrdenado 5k: \t%10llu comparacoes, %10llu atribuicoes, %10.2f milissegundos", metricas.comparacoes, metricas.atribuicoes, milissegundos);

    // Inverso 5k
    metricas.comparacoes = 0;
    metricas.atribuicoes = 0;
    memcpy(copia5k, inverso5k, VETOR_5K * sizeof(int));
    inicio = clock();
    mergeSort(copia5k, 0, VETOR_5K - 1, &metricas);
    fim = clock();
    milissegundos = (((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000);
    printf("\nInverso 5k: \t%10llu comparacoes, %10llu atribuicoes, %10.2f milissegundos", metricas.comparacoes, metricas.atribuicoes, milissegundos);

    // Aleatório 10k
    metricas.comparacoes = 0;
    metricas.atribuicoes = 0;
    memcpy(copia10k, aleatorio10k, VETOR_10K * sizeof(int));
    inicio = clock();
    mergeSort(copia10k, 0, VETOR_10K - 1, &metricas);
    fim = clock();
    milissegundos = (((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000);
    printf("\n\nAleatorio 10k: \t%10llu comparacoes, %10llu atribuicoes, %10.2f milissegundos", metricas.comparacoes, metricas.atribuicoes, milissegundos);

    // Ordenado 10k
    metricas.comparacoes = 0;
    metricas.atribuicoes = 0;
    memcpy(copia10k, ordenado10k, VETOR_10K * sizeof(int));
    inicio = clock();
    mergeSort(copia10k, 0, VETOR_10K - 1, &metricas);
    fim = clock();
    milissegundos = (((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000);
    printf("\nOrdenado 10k: \t%10llu comparacoes, %10llu atribuicoes, %10.2f milissegundos", metricas.comparacoes, metricas.atribuicoes, milissegundos);

    // Inverso 10k
    metricas.comparacoes = 0;
    metricas.atribuicoes = 0;
    memcpy(copia10k, inverso10k, VETOR_10K * sizeof(int));
    inicio = clock();
    mergeSort(copia10k, 0, VETOR_10K - 1, &metricas);
    fim = clock();
    milissegundos = (((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000);
    printf("\nInverso 10k: \t%10llu comparacoes, %10llu atribuicoes, %10.2f milissegundos", metricas.comparacoes, metricas.atribuicoes, milissegundos);

    // Aleatório 50k
    metricas.comparacoes = 0;
    metricas.atribuicoes = 0;
    memcpy(copia50k, aleatorio50k, VETOR_50K * sizeof(int));
    inicio = clock();
    mergeSort(copia50k, 0, VETOR_50K - 1, &metricas);
    fim = clock();
    milissegundos = (((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000);
    printf("\n\nAleatorio 50k: \t%10llu comparacoes, %10llu atribuicoes, %10.2f milissegundos", metricas.comparacoes, metricas.atribuicoes, milissegundos);

    // Ordenado 50k
    metricas.comparacoes = 0;
    metricas.atribuicoes = 0;
    memcpy(copia50k, ordenado50k, VETOR_50K * sizeof(int));
    inicio = clock();
    mergeSort(copia50k, 0, VETOR_50K - 1, &metricas);
    fim = clock();
    milissegundos = (((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000);
    printf("\nOrdenado 50k: \t%10llu comparacoes, %10llu atribuicoes, %10.2f milissegundos", metricas.comparacoes, metricas.atribuicoes, milissegundos);

    // Inverso 50k
    metricas.comparacoes = 0;
    metricas.atribuicoes = 0;
    memcpy(copia50k, inverso50k, VETOR_50K * sizeof(int));
    inicio = clock();
    mergeSort(copia50k, 0, VETOR_50K - 1, &metricas);
    fim = clock();
    milissegundos = (((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000);
    printf("\nInverso 50k: \t%10llu comparacoes, %10llu atribuicoes, %10.2f milissegundos", metricas.comparacoes, metricas.atribuicoes, milissegundos);

    printf("\n\nAnote os resultados antes de continuar\n\n");
    system("pause");
    system("cls");

    //----------------------------------------------------------------------
    // Quick Sort
    printf("Quick Sort:");

    // Aleatório 5k
    metricas.comparacoes = 0;
    metricas.atribuicoes = 0;
    memcpy(copia5k, aleatorio5k, VETOR_5K * sizeof(int));
    inicio = clock();
    quickSort(copia5k, 0, VETOR_5K - 1, &metricas);
    fim = clock();
    milissegundos = (((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000);
    printf("\n\nAleatorio 5k: \t%10llu comparacoes, %10llu atribuicoes, %10.2f milissegundos", metricas.comparacoes, metricas.atribuicoes, milissegundos);

    // Ordenado 5k
    metricas.comparacoes = 0;
    metricas.atribuicoes = 0;
    memcpy(copia5k, ordenado5k, VETOR_5K * sizeof(int));
    inicio = clock();
    quickSort(copia5k, 0, VETOR_5K - 1, &metricas);
    fim = clock();
    milissegundos = (((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000);
    printf("\nOrdenado 5k: \t%10llu comparacoes, %10llu atribuicoes, %10.2f milissegundos", metricas.comparacoes, metricas.atribuicoes, milissegundos);

    // Inverso 5k
    metricas.comparacoes = 0;
    metricas.atribuicoes = 0;
    memcpy(copia5k, inverso5k, VETOR_5K * sizeof(int));
    inicio = clock();
    quickSort(copia5k, 0, VETOR_5K - 1, &metricas);
    fim = clock();
    milissegundos = (((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000);
    printf("\nInverso 5k: \t%10llu comparacoes, %10llu atribuicoes, %10.2f milissegundos", metricas.comparacoes, metricas.atribuicoes, milissegundos);

    // Aleatório 10k
    metricas.comparacoes = 0;
    metricas.atribuicoes = 0;
    memcpy(copia10k, aleatorio10k, VETOR_10K * sizeof(int));
    inicio = clock();
    quickSort(copia10k, 0, VETOR_10K - 1, &metricas);
    fim = clock();
    milissegundos = (((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000);
    printf("\n\nAleatorio 10k: \t%10llu comparacoes, %10llu atribuicoes, %10.2f milissegundos", metricas.comparacoes, metricas.atribuicoes, milissegundos);

    // Ordenado 10k
    metricas.comparacoes = 0;
    metricas.atribuicoes = 0;
    memcpy(copia10k, ordenado10k, VETOR_10K * sizeof(int));
    inicio = clock();
    quickSort(copia10k, 0, VETOR_10K - 1, &metricas);
    fim = clock();
    milissegundos = (((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000);
    printf("\nOrdenado 10k: \t%10llu comparacoes, %10llu atribuicoes, %10.2f milissegundos", metricas.comparacoes, metricas.atribuicoes, milissegundos);

    // Inverso 10k
    metricas.comparacoes = 0;
    metricas.atribuicoes = 0;
    memcpy(copia10k, inverso10k, VETOR_10K * sizeof(int));
    inicio = clock();
    quickSort(copia10k, 0, VETOR_10K - 1, &metricas);
    fim = clock();
    milissegundos = (((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000);
    printf("\nInverso 10k: \t%10llu comparacoes, %10llu atribuicoes, %10.2f milissegundos", metricas.comparacoes, metricas.atribuicoes, milissegundos);

    // Aleatório 50k
    metricas.comparacoes = 0;
    metricas.atribuicoes = 0;
    memcpy(copia50k, aleatorio50k, VETOR_50K * sizeof(int));
    inicio = clock();
    quickSort(copia50k, 0, VETOR_50K - 1, &metricas);
    fim = clock();
    milissegundos = (((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000);
    printf("\n\nAleatorio 50k: \t%10llu comparacoes, %10llu atribuicoes, %10.2f milissegundos", metricas.comparacoes, metricas.atribuicoes, milissegundos);

    /*  ATENÇÃO: A chamada do vetor já ordenado de 50 mil elementos causará
        estouro da memória de execução (Stack Overflow), pois o pivô sempre
        dividirá o vetor com apenas um elemento a menos por ciclo. Para a 
        finalidade do relatório redigido, optou-se por manter no final do código.    
    */

    // Ordenado 50k
    metricas.comparacoes = 0;
    metricas.atribuicoes = 0;
    memcpy(copia50k, ordenado50k, VETOR_50K * sizeof(int));
    inicio = clock();
    quickSort(copia50k, 0, VETOR_50K - 1, &metricas);
    fim = clock();
    milissegundos = (((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000);
    printf("\nOrdenado 50k: \t%10llu comparacoes, %10llu atribuicoes, %10.2f milissegundos", metricas.comparacoes, metricas.atribuicoes, milissegundos);

    // Inverso 50k
    metricas.comparacoes = 0;
    metricas.atribuicoes = 0;
    memcpy(copia50k, inverso50k, VETOR_50K * sizeof(int));
    inicio = clock();
    quickSort(copia50k, 0, VETOR_50K - 1, &metricas);
    fim = clock();
    milissegundos = (((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000);
    printf("\nInverso 50k: \t%10llu comparacoes, %10llu atribuicoes, %10.2f milissegundos", metricas.comparacoes, metricas.atribuicoes, milissegundos);

    printf("\n\nAnote os resultados antes de continuar\n\n");
    system("pause");
    system("cls");

    // Liberar memória alocada dinamicamente

    free(aleatorio5k);
    free(aleatorio10k);
    free(aleatorio50k);
    free(ordenado5k);
    free(ordenado10k);
    free(ordenado50k);
    free(inverso5k);
    free(inverso10k);
    free(inverso50k);
    free(copia5k);
    free(copia10k);
    free(copia50k);

    return 0;
}
//----------------------------------------------------------------------
Metricas countingSort(int vetor[], int tamanho){

    // Variável para conter as comparações e atribuições durante a ordenação
    Metricas valores = {0, 0};

    // Trata vetores com elementos únicos ou erro no tamanho
    if(tamanho <= 1){
        return valores;
    }

    // Passo 1: Encontrar o maior elemento do vetor
    int maior = vetor[0];
    for(int i = 1; i < tamanho; i++){
        if(vetor[i] > maior){
            maior = vetor[i];
        }
    }

    // Passo 2: Criar vetores de contagem e saída
    // Aloca dinamicamente a memória para os vetores

    // Uso do calloc permite inicializar automaticamente com 0
    int *count = (int*)calloc(maior + 1, sizeof(int));
    int *output = (int*)malloc(tamanho * sizeof(int));

    // Passo 3: Contar as ocorrências de cada elemento
    for(int i = 0; i < tamanho; i++){
        // Usa o valor de cada ocorrência como índice
        count[vetor[i]]++;
    }

    // Passo 4: Efetuar a soma dos prefixos
    // Serve para definir as posições de cada elemento
    for(int i = 1; i <= maior; i++){
        // Soma os valores anteriores em cascata, até o final
        count[i] += count[i - 1];
    }

    // Passo 5: Ordenar os números
    // A ordenação deve ocorrer de trás para frente para manter a ordem relativa
    for(int i = tamanho - 1; i >= 0; i--){
        // Busca o índice usando o valor a ser realocado
        int valor = vetor[i];
        int indice = count[valor];
        // Insere o número na posição correta e atualiza a posição do próximo
        output[indice - 1] = valor;
        count[valor]--;

        // Conta a atribuição no vetor de saída
        valores.atribuicoes++;
    }

    // Passo 6: Copiar o vetor de saída para o original
    for(int i = 0; i < tamanho; i++){
        vetor[i] = output[i];

        // Conta as cópias ao vetor original
        valores.atribuicoes++;
    }

    // Passo 7: Liberar memória alocada dinamicamente
    free(count);
    free(output);

    // Retorna as métricas coletadas
    return valores;
}
//----------------------------------------------------------------------
Metricas insertionSort(int vetor[], int tamanho){

    // Variável para conter as comparações e atribuições durante a ordenação
    Metricas valores = {0, 0};

    // O laço percorre cada elemento a partir do segundo
    for(int i = 1; i < tamanho; i++){

        // Key é o valor comparado a cada ciclo
        int key = vetor[i];

        // Primeiro valor guardado
        valores.atribuicoes++;

        // O j caminhará para trás, puxando os elementos maiores para a frente
        int j = i - 1;

        // Percorre o vetor até acabar ou encontrar a parte ordenada
        while(j >= 0){

            // Comparação obrigatória
            valores.comparacoes++;

            if(vetor[j] > key){
                // Passa os valores maiores para a frente e atualiza a posição
                vetor[j + 1] = vetor[j];
                j--;
                
                // Contabiliza as comparações e atribuições a cada passo
                valores.atribuicoes++;
            }
            // Encerra a iteração da vez, caso chegue em um número ordenado
            else{
                break;
            }

        }
        
        // Coloca o valor comparado na posição correta ao final
        vetor[j + 1] = key;

        // Última atribuição do ciclo
        valores.atribuicoes++;
    }
    // Retorna as métricas coletadas
    return valores;
}
//----------------------------------------------------------------------
Metricas selectionSort(int vetor[], int tamanho){

    // Variável para conter as comparações e atribuições durante a ordenação
    Metricas valores = {0, 0};
    
    // O laço percorre cada elemento até o penúltimo
    for(int i = 0; i < tamanho - 1; i++){

        // Salva o índice do menor número atual
        int id_menor = i;
        
        // Percorre a parte não ordenada, um elemento a menos por ciclo
        for(int j = i + 1; j < tamanho; j++){

            // Contabiliza cada comparação dentro da iteração principal
            valores.comparacoes++;

            // Atualiza o índice do menor, se necessário
            if(vetor[j] < vetor[id_menor]){
                id_menor = j;
            }
        }

        // Troca o menor elemento com o inicial, ordenando um por vez
        swap(&vetor[id_menor], &vetor[i]);

        // Cada swap consiste em 3 atribuições
        valores.atribuicoes+=3;
    }
    // Retorna as métricas coletadas
    return valores;
}
//----------------------------------------------------------------------
void swap(int *valor1, int *valor2){
    int temporario = *valor1;
    *valor1 = *valor2;
    *valor2 = temporario;
}
//----------------------------------------------------------------------
int partition(int vetor[], int inicio, int fim, Metricas *valores){

    // Guarda o valor do pivô para comparação
    int pivot = vetor[fim];

    valores->atribuicoes++;

    // A posição correta é presumida como a primeira
    int posicaoCorreta = inicio;

    // O laço percorrerá todos os elementos antes do pivô, até o penúltimo
    // Serve para separar os menores elementos antes da posição do pivô
    for(int i = inicio; i < fim; i++){

        // Comparações a cada elemento para encontrar a posição do pivô
        valores->comparacoes++;

        if(vetor[i] < pivot){
            
            // Caso o valor seja menor, troca e incrementa a posição correta
            swap(&vetor[i], &vetor[posicaoCorreta]);
            posicaoCorreta++;

            // Cada swap consiste em 3 atribuições
            valores->atribuicoes+=3;
        }
    }
    // Efetua a última troca para alocar o pivô na posição correta
    swap(&vetor[fim], &vetor[posicaoCorreta]);

    valores->atribuicoes+=3;

    // Esse índice separa as partições na recursividade
    return posicaoCorreta;
}
//----------------------------------------------------------------------
void quickSort(int vetor[], int inicio, int fim, Metricas *valores){

    // Essa condição encerra a recursividade para o vetor unitário
    if(inicio < fim){

        // A posição do pivô delimita as duas partições 
        int pivot = partition(vetor, inicio, fim, valores);

        // A recursividade dividirá até tratar o vetor como unitário
        quickSort(vetor, inicio, pivot - 1, valores);
        quickSort(vetor, pivot + 1, fim, valores);
    }
}
//----------------------------------------------------------------------
void merge(int vetor[], int inicio, int meio, int fim, Metricas *valores){
    
    // Calcula o tamanho dos vetores auxiliares
    int tam1 = (meio - inicio) + 1;
    int tam2 = (fim - meio);

    // Declara dinamicamente os vetores com o devido tamanho
    int *esq = (int*)malloc(tam1 * sizeof(int));
    int *dir = (int*)malloc(tam2 * sizeof(int));

    // Copia os dados do vetor principal para as metades da esquerda e direita
    // Conta as atribuições para a cópia das metades
    for(int i = 0; i < tam1; i++){
        esq[i] = vetor[inicio + i];

        valores->atribuicoes++;
    }

    for(int i = 0; i < tam2; i++){
        dir[i] = vetor[(meio + 1) + i];

        valores->atribuicoes++;
    }

    // Variáveis para o laço de realocação ordenada (esquerda, direita, principal)
    int i = 0, j = 0, k = inicio;
    while(i < tam1 && j < tam2){

        // Comparação obrigatória
        valores->comparacoes++;
        
        // Se o da esquerda for menor ou igual, atribui primeiro, mantendo a ordem
        if(esq[i] <= dir[j]){
            vetor[k] = esq[i];
            i++;

            valores->atribuicoes++;
        }

        else{
            vetor[k] = dir[j];
            j++;

            valores->atribuicoes++;
        }
        k++;
    }

    // Atribui e conta os elementos restantes (maiores)
    while(i < tam1){
        vetor[k++] = esq[i++];

        valores->atribuicoes++;
    }

    while(j < tam2){
        vetor[k++] = dir[j++];

        valores->atribuicoes++;
    }

    // Libera a memória dos vetores dinâmicos
    free(esq);
    free(dir);
}
//----------------------------------------------------------------------
void mergeSort(int vetor[], int inicio, int fim, Metricas *valores){

    // Condição de parada para quando o vetor se tornar unitário
    if(inicio < fim){

        // Cálculo do meio para dividir os vetores auxiliares
        int meio = inicio + (fim - inicio) / 2;

        // Chamadas recursivas para a esquerda e direita
        mergeSort(vetor, inicio, meio, valores);
        mergeSort(vetor, meio + 1, fim, valores);

        // Aplicação real da ordenação, que começa no vetor de dois elementos
        merge(vetor, inicio, meio, fim, valores);
    }
}
//----------------------------------------------------------------------
void imprimirVetor(int vetor[], int tamanho){
    printf("[");

    // Imprime cada elemento entre vírgulas, exceto o último
    for(int i = 0; i < tamanho - 1; i++){
        printf("%i, ", vetor[i]);
    }
    // Imprime o elemento final para manter a separação correta
    printf("%i", vetor[tamanho - 1]);

    printf("]");
}
//----------------------------------------------------------------------