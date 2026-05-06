/*  Tabela hash com buckets de pilhas encadeadas

    O código permite a inserção, busca e exclusão de elementos com nome (chave)
    e código (valor) de modo eficiente, utilizando a tabela hash para efetivar 
    a busca em um intervalo menor. A macro para o tamanho da tabela define a
    quantidade de buckets e, portanto, a distribuição das colisões entre as chaves.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Macros para ajuste de limites
#define MAX_CHAVE 100
#define TAM_TABELA 10
//----------------------------------------------------------------------
// Estrutura para o elemento (nó) da pilha encadeada:
typedef struct Elemento{
    char chave[MAX_CHAVE];
    int valor;
    struct Elemento *proximo;
}Elemento;

// Estrutura para centralizar o tratamento da tabela hash:
typedef struct{
    Elemento *buckets[TAM_TABELA];
}TabelaHash;
//----------------------------------------------------------------------
// Para mais informações, verifique o código das funções
// Funções gerais:
int menu();
int continuar();
int lerInteiro(int minimo, int maximo);
void esperarEnter();
void lerString(char nome[], int tamanho);
// Funções específicas:
int funcaoHash(char chave[]);
void inicializarTabela(TabelaHash *tabela);
int tabelaEstaVazia(TabelaHash *tabela);
void imprimirTabela(TabelaHash *tabela);
void limparTabela(TabelaHash *tabela);
Elemento* buscarElemento(TabelaHash *tabela, char chave[]);
void inserirElemento(TabelaHash *tabela, char chave[], int valor);
void removerElemento(TabelaHash *tabela, char chave[]);
//----------------------------------------------------------------------
int main(){
    system("title Tabela hash");
    TabelaHash tabela;
    inicializarTabela(&tabela);
    int operacao = 1;
    while(operacao == 1){
        system("cls");
        int opcaoMenu = menu();
        switch(opcaoMenu){
            case 1:{
                int inserir = 1;
                while(inserir == 1){
                    system("cls");
                    printf("\tINSERIR ELEMENTO\n\n");
                    printf("Digite seu nome: ");
                    char chave[MAX_CHAVE];
                    lerString(chave, MAX_CHAVE);
                    printf("\nDigite seu codigo: ");
                    int valor = lerInteiro(1, 999999);
                    inserirElemento(&tabela, chave, valor);
                    printf("\n\n");
                    inserir = continuar();
                }
                break;
            }
            case 2:{
                int remover = 1;
                while(remover == 1){
                    system("cls");
                    printf("\tREMOVER ELEMENTO\n\n");
                    if(tabelaEstaVazia(&tabela)){
                        printf("Ainda nao existem pessoas cadastradas!\n\n\n");
                        esperarEnter();
                        remover = 0;
                    }
                    else{
                        printf("Digite o nome da pessoa a remover: ");
                        char chave[MAX_CHAVE];
                        lerString(chave, MAX_CHAVE);
                        removerElemento(&tabela, chave);
                        printf("\n\n\n");
                        remover = continuar();
                    }
                }
                break;
            }
            case 3:{
                int buscar = 1;
                while(buscar == 1){
                    system("cls");
                    printf("\tBUSCAR ELEMENTO\n\n");
                    if(tabelaEstaVazia(&tabela)){
                        printf("Ainda nao existem pessoas cadastradas!\n\n\n");
                        esperarEnter();
                        buscar = 0;
                    }
                    else{
                        printf("Digite o nome da pessoa buscada: ");
                        char chave[MAX_CHAVE];
                        lerString(chave, MAX_CHAVE);
                        Elemento *buscado = buscarElemento(&tabela, chave);
                        if(buscado == NULL){
                            printf("\nElemento nao encontrado!\n\n\n");
                        }
                        else{
                            printf("\nElemento encontrado: %s - Codigo: %i\n\n\n", buscado->chave, buscado->valor);
                        }
                        buscar = continuar();
                    }
                }
                break;
            }
            case 4:{
                system("cls");
                printf("\tIMPRIMIR TABELA\n\n");
                if(tabelaEstaVazia(&tabela)){
                    printf("A tabela esta vazia!");
                }
                else{
                    imprimirTabela(&tabela);
                }
                printf("\n\n\n");
                esperarEnter();
                break;
            }
            case 5:{
                operacao = 0;
                limparTabela(&tabela);
                system("cls");
                printf("Sistema encerrado!\n\n");
                esperarEnter();
                break;
            }
        }
    }
}
//----------------------------------------------------------------------
int menu(){
    printf("\tMENU");
    printf("\n\n1) Adicionar elemento");
    printf("\n2) Remover elemento");
    printf("\n3) Buscar elemento");
    printf("\n4) Imprimir tabela");
    printf("\n5) SAIR");
    printf("\n\nOpcao: ");
    return lerInteiro(1, 5);
}
//----------------------------------------------------------------------
int continuar(){
    printf("Deseja continuar?");
    printf("\n\t1) SIM");
    printf("\n\t0) NAO");
    printf("\n\nOpcao: ");
    return lerInteiro(0, 1);
}
//----------------------------------------------------------------------
// Lê e valida um inteiro em um intervalo passado por parâmetro
int lerInteiro(int minimo, int maximo){
    int valor;
    // Garante que a leitura ocorreu e não use lixo da memória
    int leitura = scanf("%i", &valor);
    // Caso qualquer fator falhe, requisita novamente
    while(leitura != 1 || (valor < minimo || valor > maximo)){
        // Limpa o buffer, em caso de digitar caracteres
        while(getchar() != '\n');
        printf("\nInsira um valor entre %i e %i: ", minimo, maximo);
        leitura = scanf("%i", &valor);
    }
    return valor;
}
//----------------------------------------------------------------------
void esperarEnter(){
	// A função limpa o \n do último Enter e espera outro para continuar;
	// Permite a espera em uma tela, sem exigir entradas específicas.
    printf("Aperte Enter para continuar...");
    while (getchar() != '\n');
    while (getchar() != '\n');
}
//----------------------------------------------------------------------
void lerString(char nome[], int tamanho){
	fgets(nome, tamanho, stdin);
	// Em caso de Enter acidental ou no buffer, escaneia a string novamente.
	while(nome[0] == '\n'){
		fgets(nome, tamanho, stdin);
	}
	// Verifica a posição do Enter, indicando que a string tem o tamanho adequado.
	int posicaoEnter = strcspn(nome, "\n");
	// String tem o tamanho previsto, considerando o Enter (com \0 no final):
	if(nome[posicaoEnter] == '\n'){
		// Garante que o Enter escaneado seja eliminado da string.
		nome[posicaoEnter] = '\0';
	}
	// Caso seja maior que o tamanho reservado:
	else{
		// Limpa o buffer com a parte cortada da string até o \n.
		while(getchar() != '\n');
	}
}
//----------------------------------------------------------------------
// Gera o índice da tabela hash somando os valores binários dos caracteres
int funcaoHash(char chave[]){
    int soma = 0;
    // Percorre toda a string acumulando o valor
    for(int i = 0; chave[i] != '\0'; i++){
        soma += chave[i];
    }
    // O operador de módulo serve para espalhar corretamente os índices
    return soma % TAM_TABELA;
}
//----------------------------------------------------------------------
// Inicializa todos os buckets com NULL para garantir o funcionamento das pilhas
void inicializarTabela(TabelaHash *tabela){
    for(int i = 0; i < TAM_TABELA; i++){
        tabela->buckets[i] = NULL;
    }
}
//----------------------------------------------------------------------
// Percorre a tabela até achar algum cadastro ou retorna que está vazia
int tabelaEstaVazia(TabelaHash *tabela){
    for(int i = 0; i < TAM_TABELA; i++){
        if(tabela->buckets[i] != NULL){
            return 0;
        }
    }
    return 1;
}
//----------------------------------------------------------------------
// Imprime apenas os buckets preenchidos, com todos os cadastros
void imprimirTabela(TabelaHash *tabela){
    for(int i = 0; i < TAM_TABELA; i++){
        if(tabela->buckets[i] == NULL){
            continue;
        }
        printf("Bucket [%i]", i);
        printf("\nCodigo | Nome");
        Elemento *atual = tabela->buckets[i];
        while(atual != NULL){
            printf("\n%6i | %s", atual->valor, atual->chave);
            atual = atual->proximo;
        }
        printf("\n\n");
    }
}
//----------------------------------------------------------------------
// Garante a liberação da memória das pilhas dinâmicas de cada bucket
void limparTabela(TabelaHash *tabela){
    for(int i = 0; i < TAM_TABELA; i++){
        Elemento *topo = tabela->buckets[i];
        while(topo != NULL){
            Elemento *limpar = topo;
            topo = topo->proximo;
            free(limpar);
        }
    }
}
//----------------------------------------------------------------------
// Percorre a pilha até achar uma correspondência
// Retorna a struct com os dados ou NULL
Elemento* buscarElemento(TabelaHash *tabela, char chave[]){
    int indice = funcaoHash(chave);
    Elemento *atual = tabela->buckets[indice];
    while(atual != NULL){
        if(strcmp(atual->chave, chave) == 0){
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}
//----------------------------------------------------------------------
// Aloca a memória dinamicamente e empilha o novo cadastro no bucket certo
void inserirElemento(TabelaHash *tabela, char chave[], int valor){
    Elemento *novo = (Elemento*)malloc(sizeof(Elemento));
    strcpy(novo->chave, chave);
    novo->valor = valor;
    int indice = funcaoHash(chave);
    novo->proximo = tabela->buckets[indice];
    tabela->buckets[indice] = novo;
}
//----------------------------------------------------------------------
// Exibe o elemento escolhido, remove, libera a memória e atualiza a pilha;
void removerElemento(TabelaHash *tabela, char chave[]){
    Elemento *atual = buscarElemento(tabela, chave);
    // Garante o encerramento da função, caso o elemento não exista
    if(atual == NULL){
        printf("\nElemento nao encontrado!");
        return;
    }
    int indice = funcaoHash(chave);
    Elemento *remover = atual;
    atual = tabela->buckets[indice];
    // Para o caso de ser o primeiro elemento, atualiza a pilha
    if(atual == remover){
        tabela->buckets[indice] = atual->proximo;
    }
    // Caso contrário, chega até o anterior e refaz a ligação, separando-o
    else{
        while(atual->proximo != remover){
            atual = atual->proximo;
        }
        atual->proximo = remover->proximo;
    }
    printf("\nElemento removido: %s - Codigo: %i", remover->chave, remover->valor);
    free(remover);
}
//----------------------------------------------------------------------