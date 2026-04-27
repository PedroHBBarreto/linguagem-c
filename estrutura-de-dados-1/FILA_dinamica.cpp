/*	Fila dinâmica com ponteiros

	Demonstração funcional de uma das estruturas de dados mais conhecidas.
	A fila caracteriza-se pelo conceito de First In, First Out (FIFO),
	onde o primeiro elemento a entrar é o primeiro a sair.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 50

//----------------------------------------------------------------------
// Define um nó da fila, contendo os dados e um ponteiro autorreferenciado;
// O ponteiro é responsável por encadear os elementos sequencialmente.
typedef struct Elemento{
	int senha;
	char nome[MAX_NOME];
	struct Elemento *proximo;
}Elemento;

// Essa estrutura centraliza o controle da fila verificando seu início e fim.
typedef struct{
	Elemento *inicio;
	Elemento *fim;
}Fila;
//----------------------------------------------------------------------
// Funções do código e da estrutura;
// Para mais detalhes, verificar o código comentado das funções.
int menu(Elemento *inicio);
int continuar();
void esperarEnter();
void cadastrarNome(char nome[], int tamanho);
void inicializarFila(Fila *fila);
void imprimirFila(Fila *fila);
int adicionarElemento(Fila *fila, int *senha);
int removerElemento(Fila *fila);
//----------------------------------------------------------------------
int main(){
	system("title Fila dinamica");
	// Estrutura para controle da fila e inicialização como vazia.
	Fila fila;
	inicializarFila(&fila);
	int senha = 1;
	int operacao = 1;
	while(operacao == 1){
		int opcaoMenu = menu(fila.inicio);
		switch(opcaoMenu){
			case 1:{
				imprimirFila(&fila);
				break;
			}
			case 2:{
				// De acordo com o retorno da função, permite a adição ilimitada de elementos.
				int adicionar = 1;
				while(adicionar == 1){
					adicionar = adicionarElemento(&fila, &senha);
				}
				break;
			}
			case 3:{
				// Usa o retorno da função para definir se a fila está vazia e voltar ao MENU.
				int remover = 1;
				while(remover == 1){
					remover = removerElemento(&fila);
				}
				break;
			}
			case 4:{
				// Percorre toda a estrutura e libera a memória manualmente para fechamento seguro. 
				while(fila.inicio != NULL){
					Elemento *limpar = fila.inicio;
					fila.inicio = fila.inicio->proximo;
					free(limpar);
				}
				// Apenas na opção de saída o ciclo do programa será encerrado.
				operacao = 0;
				system("cls");
				printf("Sistema encerrado!");
				esperarEnter();
				break;
			}
		}
	}
	return 0;
}
//----------------------------------------------------------------------
int menu(Elemento *inicio){
	system("cls");
	printf("\tMENU - FILA DINAMICA");
	// Verifica se a fila está vazia para indicar a próxima senha.
	if(inicio != NULL){
		printf("\n\nProxima senha a ser chamada: %i", inicio->senha);
	}
	printf("\n\n1) Imprimir fila");
	printf("\n2) Adicionar elemento");
	printf("\n3) Remover elemento");
	printf("\n4) SAIR");
	printf("\n\nOpcao: ");
	int opcao;
	// Garante que a leitura foi efetuada e não reutilize o valor da opção anterior.
	int leitura = scanf("%i", &opcao);
	// Verificação para opções inválidas.
	while(leitura != 1 || opcao < 1 || opcao > 4){
		// O getchar consome o buffer e impede falha em caso de digitar letras.
		while(getchar() != '\n');
		printf("\nInsira uma opcao valida: ");
		leitura = scanf("%i", &opcao);
	}
	// Opção retornada que será usada no switch case do MENU.
	return opcao;
}
//----------------------------------------------------------------------
int continuar(){
	printf("\n\nDeseja continuar?");
	printf("\n\t1) SIM");
	printf("\n\t0) NAO (retornar ao MENU)");
	printf("\n\nOpcao: ");
	int opcao;
	// Garante que a leitura foi efetuada e não reutilize o valor da opção anterior.
	int leitura = scanf("%i", &opcao);
	// Verificação para opções inválidas.
	while(leitura != 1 || (opcao != 1 && opcao != 0)){
		// O getchar consome o buffer e impede falha em caso de digitar letras.
		while(getchar() != '\n');
		printf("\nInsira uma opcao valida: ");
		leitura = scanf("%i", &opcao);
	}
	return opcao;
}
//----------------------------------------------------------------------
void esperarEnter(){
	// A função limpa o \n do último Enter e espera outro para continuar;
	// Permite a espera em uma tela, sem exigir entradas específicas.
	printf("\n\nAperte Enter para continuar...");
	while(getchar() != '\n');
	while(getchar() != '\n');
}
//----------------------------------------------------------------------
void cadastrarNome(char nome[], int tamanho){
	printf("Insira seu nome: ");
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
void inicializarFila(Fila *fila){
	// Garante o reconhecimento da fila como vazia no primeiro uso.
	fila->inicio = NULL;
	fila->fim = NULL;
}
//----------------------------------------------------------------------
void imprimirFila(Fila *fila){
	system("cls");
	printf("\tIMPRIMIR FILA");
	// Verifica a existência de elementos.
	if(fila->inicio == NULL){
		printf("\n\nA fila esta vazia!");
	}
	// Se não estiver vazia, prossegue para a impressão.
	else{
		// Copia o elemento do início para percorrer a estrutura e imprimir a fila.
		Elemento *atual = fila->inicio;
		printf("\n\nSenha\t| Nome");
		while(atual != NULL){
			printf("\n%7i | %s", atual->senha, atual->nome);
			atual = atual->proximo;
		}
	}
	esperarEnter();
}
//----------------------------------------------------------------------
int adicionarElemento(Fila *fila, int *senha){
	system("cls");
	printf("\tADICIONAR ELEMENTO\n\n");
	// Aloca memória dinamicamente para adicionar o novo elemento;
	// O uso de malloc é necessário para que a memória persista em todo o código.
	Elemento *novo = (Elemento*)malloc(sizeof(Elemento));
	cadastrarNome(novo->nome, MAX_NOME);
	// Atribui a senha automaticamente e atualiza o valor para a próxima.
	novo->senha = *senha;
	(*senha)++;
	// Tratando-se de uma fila, o próximo elemento ainda não existe.
	novo->proximo = NULL;
	// Para o primeiro elemento, a fila ainda está vazia;
	// Com isso, deve-se marcar o nó adicionado como primeiro e último;
	// Move o fim da fila para o elemento atual.
	if(fila->inicio == NULL){
		fila->inicio = novo;
		fila->fim = novo;
	}
	// Caso não estivesse vazia, apenas atualiza o antigo último para o próximo;
	// Move o fim da fila para o elemento atual.
	else{
		fila->fim->proximo = novo;
		fila->fim = novo;
	}
	// O retorno da opção da função continuar permite a adição contínua no main.
	return continuar();
}
//----------------------------------------------------------------------
int removerElemento(Fila *fila){
	system("cls");
	printf("\tREMOVER ELEMENTO");
	// Verifica a existência de elementos.
	if(fila->inicio == NULL){
		printf("\n\nA fila esta vazia!");
		esperarEnter();
		return 0;
	}
	// Se não estiver vazia, prossegue para remoção de elementos.
	else{
		// A cópia do ponteiro do elemento é necessária para manter seus dados;
		// Imediatamente a fila tem o elemento removido, passando para o próximo.
		Elemento *remover = fila->inicio;
		fila->inicio = fila->inicio->proximo;
		printf("\n\nSenha %i: %s, apresente-se ao balcao!", remover->senha, remover->nome);
		// A memória do ponteiro na variável auxiliar deve ser liberada depois de usada.
		free(remover);
	}
	// Verifica se a fila ficou vazia e encerra a remoção no main.
	if(fila->inicio == NULL){
		printf("\n\nA fila esta vazia!");
		// Caso tenha ficado vazia, deve-se atualizar o fim para nulo.
		fila->fim = NULL;
		esperarEnter();
		return 0;
	}
	// Se ainda houver elementos, confirma se o usuário deseja continuar.
	else{
		return continuar();
	}
}
//----------------------------------------------------------------------