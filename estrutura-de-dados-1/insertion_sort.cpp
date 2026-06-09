/*  Insertion Sort

    Este código contém uma implementação do método de ordenação Insertion Sort.
    O algoritmo funciona comparando um elemento por vez até o final. Com base
    nele, arrasta os maiores para a frente, se necessário.

    Caso médio: Complexidade quadrática - O(n²).
    Melhor caso: Complexidade linear - O(n).
*/
#include <stdio.h>
#include <stdlib.h>
// Para utilizar o time() como semente do rand()
#include <time.h>

#define TAM_VETOR 20
#define FAIXA_VALORES 50
//----------------------------------------------------------------------
void insertionSort(int vetor[], int tamanho);
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
    insertionSort(vetor, tamanho);
    
    printf("\n\nVetor ordenado:\n");
    imprimirVetor(vetor, tamanho);

    return 0;
}
//----------------------------------------------------------------------
void insertionSort(int vetor[], int tamanho){

    // O laço percorre cada elemento a partir do segundo
    for(int i = 1; i < tamanho; i++){

        // Key é o valor comparado a cada ciclo
        int key = vetor[i];
        // O j caminhará para trás, puxando os elementos maiores para a frente
        int j = i - 1;

        // Percorre o vetor até acabar ou encontrar a parte ordenada
        while(j >= 0 && vetor[j] > key){

            // Passa os valores maiores para a frente e atualiza a posição
            vetor[j + 1] = vetor[j];
            j--;
        }

        // Coloca o valor comparado na posição correta ao final
        vetor[j + 1] = key;
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