/*  Selection Sort

    Este código contém uma implementação do método de ordenação Selection Sort.
    O algoritmo funciona buscando o menor elemento do vetor a cada ciclo. Então,
    troca o menor e o inicial, começando na próxima posição na outra iteração.

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
void selectionSort(int vetor[], int tamanho);
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
    selectionSort(vetor, tamanho);
    
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
void selectionSort(int vetor[], int tamanho){

    // O laço percorre cada elemento até o penúltimo
    for(int i = 0; i < tamanho - 1; i++){

        // Salva o índice do menor número atual
        int id_menor = i;
        
        // Percorre a parte não ordenada, um elemento a menos por ciclo
        for(int j = i + 1; j < tamanho; j++){

            // Atualiza o índice do menor, se necessário
            if(vetor[j] < vetor[id_menor]){
                id_menor = j;
            }
        }

        // Troca o menor elemento com o inicial, ordenando um por vez
        swap(&vetor[id_menor], &vetor[i]);
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