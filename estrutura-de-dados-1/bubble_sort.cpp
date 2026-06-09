/*  Bubble Sort

    Este código contém uma implementação do método de ordenação Bubble Sort.
    O algoritmo funciona comparando cada elemento com o próximo, uma unidade
    a menos a cada ciclo. Com isso, leva o maior elemento até o final.

    Complexidade quadrática: O(n²).
*/
#include <stdio.h>
#include <stdlib.h>
// Para utilizar o time() como semente do rand()
#include <time.h>

#define TAM_VETOR 20
#define FAIXA_VALORES 50
//----------------------------------------------------------------------
void swap(int *valor1, int *valor2);
void bubbleSort(int vetor[], int tamanho);
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
    bubbleSort(vetor, tamanho);
    
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
void bubbleSort(int vetor[], int tamanho){

    // O laço percorrerá o vetor N - 1 vezes, com N sendo tamanho
    for(int i = 0; i < tamanho - 1; i++){

        // A cada ciclo, ele percorre um a menos, por já estar ordenado
        for(int j = 0; j < tamanho - i - 1; j++){

            // Se o elemento analisado for maior, leva até o final
            if(vetor[j] > vetor[j + 1]){
                swap(&vetor[j], &vetor[j + 1]);
            }
        }
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