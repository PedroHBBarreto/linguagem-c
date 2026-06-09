/*  Quick Sort

    Este código contém uma implementação do método de ordenação Quick Sort.
    O algoritmo escolhe um número (pivô) para alocar em sua posição correta,
    garantindo que os menores estejam antes e, os maiores, depois. Então, aplica
    a divisão dos lados e alocação do pivô de modo recursivo até estar ordenado.

    Caso médio: Complexidade linearítmica - O(n log n).
    Pior caso: Complexidade quadrática - O(n²).
*/
#include <stdio.h>
#include <stdlib.h>
// Para utilizar o time() como semente do rand()
#include <time.h>

#define TAM_VETOR 20
#define FAIXA_VALORES 50
//----------------------------------------------------------------------
void swap(int *valor1, int *valor2);
int partition(int vetor[], int inicio, int fim);
void quickSort(int vetor[], int inicio, int fim);
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
    quickSort(vetor, 0, tamanho - 1);
    
    printf("\n\nVetor ordenado:\n");
    imprimirVetor(vetor, tamanho);

    return 0;
}
//----------------------------------------------------------------------
void swap(int *valor1, int *valor2){
    int temporario = *valor1;
    *valor1 = *valor2;
    *valor2 = temporario;
}
//----------------------------------------------------------------------
int partition(int vetor[], int inicio, int fim){

    // Guarda o valor do pivô para comparação
    int pivot = vetor[fim];
    // A posição correta é presumida como a primeira
    int posicaoCorreta = inicio;

    // O laço percorrerá todos os elementos antes do pivô, até o penúltimo
    // Serve para separar os menores elementos antes da posição do pivô
    for(int i = inicio; i < fim; i++){

        if(vetor[i] < pivot){
            
            // Caso o valor seja menor, troca e incrementa a posição correta
            swap(&vetor[i], &vetor[posicaoCorreta]);
            posicaoCorreta++;
        }
    }
    // Efetua a última troca para alocar o pivô na posição correta
    swap(&vetor[fim], &vetor[posicaoCorreta]);

    // Esse índice separa as partições na recursividade
    return posicaoCorreta;
}
//----------------------------------------------------------------------
void quickSort(int vetor[], int inicio, int fim){

    // Essa condição encerra a recursividade para o vetor unitário
    if(inicio < fim){

        // A posição do pivô delimita as duas partições 
        int pivot = partition(vetor, inicio, fim);

        // A recursividade dividirá até tratar o vetor como unitário
        quickSort(vetor, inicio, pivot - 1);
        quickSort(vetor, pivot + 1, fim);
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