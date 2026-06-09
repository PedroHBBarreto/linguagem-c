/*  Counting Sort Estável

    Este código contém uma implementação estável do método de ordenação Counting Sort,
    ou seja, que mantém a ordem relativa dos elementos. Trata-se de um algoritmo que 
    não utiliza comparações.

    Complexidade linear: O(n + k).
*/
#include <stdio.h>
#include <stdlib.h>
// Para utilizar o time() como semente do rand()
#include <time.h>

#define TAM_VETOR 20
#define FAIXA_VALORES 50
//----------------------------------------------------------------------
void countingSort(int vetor[], int tamanho);
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
    countingSort(vetor, tamanho);
    
    printf("\n\nVetor ordenado:\n");
    imprimirVetor(vetor, tamanho);

    return 0;
}
//----------------------------------------------------------------------
void countingSort(int vetor[], int tamanho){
    // Trata vetores com elementos únicos ou erro no tamanho
    if(tamanho <= 1){
        return;
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
    }

    // Passo 6: Copiar o vetor de saída para o original
    for(int i = 0; i < tamanho; i++){
        vetor[i] = output[i];
    }

    // Passo 7: Liberar memória alocada dinamicamente
    free(count);
    free(output);
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