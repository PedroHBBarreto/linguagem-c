/*	Pilha dinâmica com ponteiros

	Demonstração funcional de uma das estruturas de dados mais conhecidas.
	A pilha caracteriza-se pelo conceito de Last In, First Out (LIFO),
	onde o último elemento a entrar é o primeiro a sair.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 50

//----------------------------------------------------------------------
// Define um nó da pilha, contendo os dados e um ponteiro autorreferenciado;
// O ponteiro é responsável por encadear os elementos sequencialmente.
typedef struct Elemento{
	char nome[MAX_NOME];
	struct Elemento *proximo;
}Elemento;
//----------------------------------------------------------------------
// Funções do código e da estrutura;
// Para mais detalhes, verificar o código comentado das funções.
int menu();
int continuar();
void esperarEnter();
void cadastrarNome(char nome[], int tamanho);
void imprimirPilha(Elemento **topo);
int adicionarElemento(Elemento **topo);
int removerElemento(Elemento **topo);
//----------------------------------------------------------------------
int main(){
	system("title Pilha dinamica");
	// Ponteiro para o último elemento adicionado, passado para as funções.
	Elemento *topo = NULL;
	int operacao = 1;
	while(operacao == 1){
		int opcaoMenu = menu();
		switch(opcaoMenu){
			case 1:{
				imprimirPilha(&topo);
				break;
			}
			case 2:{
				// De acordo com o retorno da função, permite a adição ilimitada de elementos.
				int adicionar = 1;
				while(adicionar == 1){
					adicionar = adicionarElemento(&topo);
				}
				break;
			}
			case 3:{
				// Usa o retorno da função para definir se a pilha está vazia e voltar ao MENU.
				int remover = 1;
				while(remover == 1){
					remover = removerElemento(&topo);
				}
				break;
			}
			case 4:{
				// Percorre toda a estrutura e libera a memória manualmente para fechamento seguro. 
				while(topo != NULL){
					Elemento *limpar = topo;
					topo = topo->proximo;
					free(limpar);
				}
				// Apenas na opção de saída o ciclo do programa será encerrado.
				operacao = 0;
				system("cls");
				printf("Sistema Encerrado!");
				esperarEnter();
				break;
			}
		}
	}
	return 0;
}
//----------------------------------------------------------------------
int menu(){
	system("cls");
	printf("\tMENU - PILHA DINAMICA");
	printf("\n\n1) Imprimir pilha");
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
void imprimirPilha(Elemento **topo){
	system("cls");
	printf("\tIMPRIMIR PILHA");
	// Verifica a existência de elementos.
	if(*topo == NULL){
		printf("\n\nA pilha esta vazia!");
	}
	// Se não estiver vazia, prossegue para a impressão.
	else{
		// Copia o elemento do topo para percorrer a estrutura e imprimir a pilha.
		Elemento *atual = *topo;
		printf("\n\nPRIMEIRO A SAIR\n");
		while(atual != NULL){
			printf("\n%s", atual->nome);
			atual = atual->proximo;
		}
		printf("\n\nULTIMO A SAIR\n");
	}
	esperarEnter();
}
//----------------------------------------------------------------------
int adicionarElemento(Elemento **topo){
	system("cls");
	printf("\tADICIONAR ELEMENTO\n\n");
	// Aloca memória dinamicamente para adicionar o novo elemento;
	// O uso de malloc é necessário para que a memória persista em todo o código.
	Elemento *novo = (Elemento*)malloc(sizeof(Elemento));
	cadastrarNome(novo->nome, MAX_NOME);
	// O próximo elemento da pilha sempre é o anterior, que no início é NULL (vazia).
	novo->proximo = *topo;
	// Move o ponteiro que indica o último para o elemento que foi adicionado.
	*topo = novo;
	// O retorno da opção da função continuar permite a adição contínua no main.
	return continuar();
}
//----------------------------------------------------------------------
int removerElemento(Elemento **topo){
	system("cls");
	printf("\tREMOVER ELEMENTO");
	// Verifica a existência de elementos.
	if(*topo == NULL){
		printf("\n\nA pilha esta vazia!");
		esperarEnter();
		return 0;
	}
	// Se não estiver vazia, prossegue para remoção de elementos.
	else{
		// A cópia do ponteiro do elemento é necessária para manter seus dados;
		// Imediatamente a pilha tem o elemento removido, passando para o próximo.
		Elemento *remover = *topo;
		*topo = (*topo)->proximo;
		printf("\n\n%s foi removido da pilha!", remover->nome);
		// A memória do ponteiro na variável auxiliar deve ser liberada depois de usada.
		free(remover);
	}
	// Verifica se a pilha ficou vazia e encerra a remoção no main.
	if(*topo == NULL){
		printf("\n\nA pilha esta vazia!");
		esperarEnter();
		return 0;
	}
	// Se ainda houver elementos, confirma se o usuário deseja continuar.
	else{
		return continuar();
	}
}
//----------------------------------------------------------------------