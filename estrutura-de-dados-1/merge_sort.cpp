/*  Merge Sort

    Este código contém uma implementação do método de ordenação Merge Sort.
    O algoritmo é baseado em uma função recursiva que divide o vetor na metade
    a cada ciclo. Então, volta aplicando o merge desde o vetor com dois elementos,
    colocando-os em ordem. A ordenação restante é feita realocando o menor número
    da vez entre as duas metades do vetor original, até concluir o processo.

    Complexidade linearítmica: O(n log n).
*/
#include <stdio.h>
#include <stdlib.h>
// Para utilizar o time() como semente do rand()
#include <time.h>

#define TAM_VETOR 20
#define FAIXA_VALORES 50
//----------------------------------------------------------------------
void merge(int vetor[], int inicio, int meio, int fim);
void mergeSort(int vetor[], int inicio, int fim);
void imprimirVetor(int vetor[], int tamanho);
//----------------------------------------------------------------------
int main(){
    // Utiliza o retorno de time() (segundos) para definir a semente do rand()
    srand(time(NULL));

    int vetor[TAM_VETOR];

    // Insere valores aleatórios
    for(int i = 0; i < TAM_VETOR; i++){
        vetor[i] = rand() % FAIXA_VALORES;
    }

    // Caso não definido, o tamanho do vetor deverá ser verificado:
    // Tamanho total / tamanho do tipo (bytes)
    int tamanho = sizeof(vetor) / sizeof(vetor[0]);

    printf("Vetor original:\n");
    imprimirVetor(vetor, tamanho);
    mergeSort(vetor, 0, tamanho - 1);
    
    printf("\n\nVetor ordenado:\n");
    imprimirVetor(vetor, tamanho);

    return 0;
}
//----------------------------------------------------------------------
void merge(int vetor[], int inicio, int meio, int fim){
    
    // Calcula o tamanho dos vetores auxiliares
    int tam1 = (meio - inicio) + 1;
    int tam2 = (fim - meio);

    // Declara dinamicamente os vetores com o devido tamanho
    int *esq = (int*)malloc(tam1 * sizeof(int));
    int *dir = (int*)malloc(tam2 * sizeof(int));

    // Copia os dados do vetor principal para as metades da esquerda e direita
    for(int i = 0; i < tam1; i++){
        esq[i] = vetor[inicio + i];
    }

    for(int i = 0; i < tam2; i++){
        dir[i] = vetor[(meio + 1) + i];
    }

    // Variáveis para o laço de realocação ordenada (esquerda, direita, principal)
    int i = 0, j = 0, k = inicio;
    while(i < tam1 && j < tam2){

        // Se o da esquerda for menor ou igual, atribui primeiro, mantendo a ordem
        if(esq[i] <= dir[j]){
            vetor[k] = esq[i];
            i++;
        }

        else{
            vetor[k] = dir[j];
            j++;
        }
        k++;
    }

    // Atribui os elementos restantes (maiores)
    while(i < tam1){
        vetor[k++] = esq[i++];
    }

    while(j < tam2){
        vetor[k++] = dir[j++];
    }

    // Libera a memória dos vetores dinâmicos
    free(esq);
    free(dir);
}
//----------------------------------------------------------------------
void mergeSort(int vetor[], int inicio, int fim){

    // Condição de parada para quando o vetor se tornar unitário
    if(inicio < fim){

        // Cálculo do meio para dividir os vetores auxiliares
        int meio = inicio + (fim - inicio) / 2;

        // Chamadas recursivas para a esquerda e direita
        mergeSort(vetor, inicio, meio);
        mergeSort(vetor, meio + 1, fim);

        // Aplicação real da ordenação, que começa no vetor de dois elementos
        merge(vetor, inicio, meio, fim);
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