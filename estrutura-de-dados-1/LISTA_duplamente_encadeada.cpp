/*	Lista circular duplamente encadeada com ponteiros

	Demonstração funcional de uma das estruturas de dados mais conhecidas.
	A lista não possui restrições de inserção e remoção como a fila ou pilha,
	permitindo adicionar ou remover de acordo com as funções programadas.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NOME 50

//----------------------------------------------------------------------
// Define um nó da lista, contendo os dados ponteiros autorreferenciados;
// Os ponteiros são responsáveis por encadear os elementos sequencialmente.
typedef struct Elemento{
    int codigo;
    char nome[MAX_NOME];
    struct Elemento *proximo;
    struct Elemento *anterior;
}Elemento;

// Essa estrutura centraliza o controle da lista verificando seu início e fim.
typedef struct Lista{
    Elemento *inicio;
    Elemento *fim;
}Lista;
//----------------------------------------------------------------------
// Funções do código e da estrutura;
// Para mais detalhes, verificar o código comentado das funções.
int menu();
int continuar();
void esperarEnter();
void lerString(char nome[], int tamanho);
void inicializarLista(Lista *lista);
void imprimirLista(Lista *lista);
int adicionarElemento(Lista *lista);
int removerElemento(Lista *lista);
Elemento* buscarCodigo(Lista *lista);
Elemento* buscarNome(Lista *lista);
//----------------------------------------------------------------------
int main(){
    system("title Lista Circular Duplamente Encadeada");
    // Estrutura para controle da lista e inicialização como vazia.
    Lista lista;
    inicializarLista(&lista);
    int operacao = 1;
    while(operacao == 1){
        int opcaoMenu = menu();
        switch(opcaoMenu){
            case 1:{
                imprimirLista(&lista);
                break;
            }
            case 2:{
                // De acordo com o retorno da função, permite a adição ilimitada de elementos.
                int adicionar = 1;
                while(adicionar == 1){
                    adicionar = adicionarElemento(&lista);
                }
                break;
            }
            case 3:{
                // Usa o retorno da função para definir se a lista está vazia e voltar ao MENU.
                int remover = 1;
                while(remover == 1){
                    remover = removerElemento(&lista);
                }
                break;
            }
            case 4:{
                // Percorre toda a estrutura e libera a memória manualmente para fechamento seguro.
                while(lista.fim != NULL){
                    if(lista.inicio == lista.fim){
                        lista.inicio->anterior = NULL;
                    }
                    Elemento *limpar = lista.fim;
                    lista.fim = lista.fim->anterior;
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
int menu(){
    system("cls");
    printf("\tMENU - LISTA CIRCULAR DUPLAMENTE ENCADEADA");
    printf("\n\n1) Vizualizar lista");
    printf("\n2) Adicionar elemento");
    printf("\n3) Remover elemento");
    printf("\n4) SAIR");
    printf("\n\nOpcao:");
    int opcao;
    // Garante que a leitura foi efetuada e não reutilize o valor da opção anterior.
	int leitura = scanf("%i", &opcao);
    // Verificação para opções inválidas.
    while(leitura != 1 || (opcao < 1 || opcao > 4)){
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
    printf("Deseja continuar?");
    printf("\n\t1) Sim");
    printf("\n\t0) Nao (retornar ao menu)");
    printf("\n\nOpcao: ");
    int opcao;
    // Proteção e validação padrão de entrada (verifique a função "menu").
    int leitura = scanf("%i", &opcao);
    while(leitura != 1 || (opcao != 1 && opcao != 0)){
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
    printf("\n\nAperte enter para continuar...");
    while(getchar() != '\n');
    while(getchar() != '\n');
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
void inicializarLista(Lista *lista){
    // Garante o reconhecimento da lista como vazia no primeiro uso.
    lista->inicio = NULL;
    lista->fim = NULL;
}
//----------------------------------------------------------------------
void imprimirLista(Lista *lista){
    system("cls");
    printf("\tIMPRIMIR LISTA\n\n");
    // Verifica a existência de elementos.
    if(lista->fim == NULL){
        printf("A lista esta vazia!");
    }
    // Se não estiver vazia, prossegue para a impressão.
    else{
        // Permite escolher a ordem de impressão, explorando o duplo encadeamento.
        printf("Como deseja imprimir?");
        printf("\n\t1) Ordem de cadastro");
        printf("\n\t2) Ordem inversa");
        printf("\n\nOpcao:");
        int tipoImpressao;
        // Proteção e validação padrão de entrada (verifique a função "menu").
        int leitura = scanf("%i", &tipoImpressao);
        while(leitura != 1 || (tipoImpressao != 1 && tipoImpressao != 2)){
            while(getchar() != '\n');
            printf("\nInsira uma opcao valida: ");
            leitura = scanf("%i", &tipoImpressao);
        }
        system("cls");
        printf("\tIMPRIMIR LISTA\n\n");
        switch(tipoImpressao){
            case 1:{
                // Copia o elemento do início para percorrer a estrutura e imprimir a lista.
                Elemento *atual = lista->inicio;
                printf("Codigo | Nome");
                do{
                    printf("\n%6i | %s", atual->codigo, atual->nome);
                    atual = atual->proximo;
                }while(atual != lista->inicio);
                break;
            }
            case 2:{
                // Copia o elemento do fim para percorrer a estrutura e imprimir a lista.
                Elemento *atual = lista->fim;
                printf("Codigo | Nome");
                do{
                    printf("\n%6i | %s", atual->codigo, atual->nome);
                    atual = atual->anterior;
                }while(atual != lista->fim);
                break;
            }
        }
    }
    esperarEnter();
}
//----------------------------------------------------------------------
int adicionarElemento(Lista *lista){
    system("cls");
    // Aloca memória dinamicamente para adicionar o novo elemento;
	// O uso de malloc é necessário para que a memória persista em todo o código.
    Elemento *aluno = (Elemento*)malloc(sizeof(Elemento));
    printf("\tADICIONAR ELEMENTO");
    printf("\n\nInsira seu codigo de aluno: ");
    // Proteção e validação padrão de entrada (verifique a função "menu").
    int leitura = scanf("%i", &aluno->codigo);
    while(leitura != 1 || (aluno->codigo < 1 || aluno->codigo > 999999)){
        while(getchar() != '\n');
        printf("\nInsira um codigo valido: ");
        leitura = scanf("%i", &aluno->codigo);
    }
    printf("\nInsira o nome do aluno: ");
    lerString(aluno->nome, MAX_NOME);
    // Verifica se a fila está vazia, apontando o novo elemento como o primeiro e último.
    if(lista->fim == NULL){
        lista->inicio = aluno;
        lista->fim = aluno;
    }
    // Para todos os outros casos, atualiza o anterior do primeiro e próximo do último.
    else{
        lista->inicio->anterior = aluno;
        lista->fim->proximo = aluno;
    }
    // Atribui os ponteiro para o novo elemento, caracterizando-o como o último.
    aluno->anterior = lista->fim;
    aluno->proximo = lista->inicio;
    lista->fim = aluno;
    system("cls");
    printf("\tADICIONAR ELEMENTO");
    printf("\n\nAluno cadastrado: %s - Codigo: %i\n\n", aluno->nome, aluno->codigo);
    // O retorno da opção da função continuar permite a adição contínua no main.
    return continuar();
}
//----------------------------------------------------------------------
int removerElemento(Lista *lista){
    system("cls");
    printf("\tREMOVER ELEMENTO\n\n");
    // Verifica a existência de elementos.
    if(lista->fim == NULL){
        printf("A lista esta vazia!");
        esperarEnter();
        return 0;
    }
    // Permite escolher como buscar o aluno a ser removido da lista.
    printf("Como deseja buscar o aluno?");
    printf("\n\t1) Por codigo");
    printf("\n\t2) Por nome");
    printf("\n\nOpcao: ");
    int modoBusca;
    // Proteção e validação padrão de entrada (verifique a função "menu").
    int leitura = scanf("%i", &modoBusca);
    while(leitura != 1 || (modoBusca != 1 && modoBusca != 2)){
        while(getchar() != '\n');
        printf("\nInsira uma opcao valida: ");
        leitura = scanf("%i", &modoBusca);
    }
    // Cria-se uma variável para receber o endereço a ser removido;
    // As funções de busca retornam seu ponteiro (verificar funções).
    Elemento *remover;
    switch(modoBusca){
        case 1:{
            remover = buscarCodigo(lista);
            break;
        }
        case 2:{
            remover = buscarNome(lista);
            break;
        }
    }
    system("cls");
    printf("\tREMOVER ELEMENTO\n\n");
    // Em caso de falha na busca, o ponteiro nulo permite a volta para o menu.
    if(remover == NULL){
        printf("Aluno nao encontrado!");
        esperarEnter();
        return 0;
    }
    // A cópia do ponteiro do elemento é necessária para manter seus dados;
    printf("Aluno removido: %s - Codigo: %i\n\n", remover->nome, remover->codigo);
    if(lista->fim == lista->inicio){
        // Caso seja o último elemento, deve-se atualizar os ponteiros para nulos.
        lista->inicio = NULL;
        lista->fim = NULL;
    }
    // Até 2 elementos restantes, aplicam-se as seguintes regras:
    else{
        // Caso o elemento atual seja o primeiro, seu ponteiro anda para o próximo.
        if(lista->inicio == remover){
            lista->inicio = lista->inicio->proximo;
        }
        // Caso o elemento atual seja o último, seu ponteiro anda para o anterior.
        if(lista->fim == remover){
            lista->fim = lista->fim->anterior;
        }
        // A remoção consiste em unir os elementos adjacentes ao removido entre si.
        remover->anterior->proximo = remover->proximo;
        remover->proximo->anterior = remover->anterior;
    }
    // A memória do ponteiro na variável auxiliar deve ser liberada depois de usada.
    free(remover);
    // Verifica se a lista ficou vazia e encerra a remoção no main.
    if(lista->fim == NULL){
        printf("A lista esta vazia!");
        esperarEnter();
        return 0;
    }
    // Se ainda houver elementos, confirma se o usuário deseja continuar.
    else{
        return continuar();
    }
}
//----------------------------------------------------------------------
Elemento* buscarCodigo(Lista *lista){
    system("cls");
    printf("\tBUSCA POR CODIGO\n\n");
    printf("Insira o codigo a buscar: ");
    int codigoBuscado;
    // Proteção e validação padrão de entrada (verifique a função "menu").
    int leitura = scanf("%i", &codigoBuscado);
    while(leitura != 1 || (codigoBuscado < 1 || codigoBuscado > 999999)){
        while(getchar() != '\n');
        printf("\nInsira um codigo valido: ");
        leitura = scanf("%i", &codigoBuscado);
    }
    // Efetua a busca pelo código desde o início da lista.
    Elemento *atual = lista->inicio;
    do{
        if(atual->codigo == codigoBuscado){
            // Caso encontre, retorna o ponteiro para esse elemento.
            return atual;
        }
        atual = atual->proximo;
    }while(atual != lista->inicio);
    // Caso contrário, retorna nulo.
    return NULL;
}
//----------------------------------------------------------------------
Elemento* buscarNome(Lista *lista){
    system("cls");
    printf("\tBUSCA POR NOME\n\n");
    printf("Insira o nome a buscar: ");
    char nomeBuscado[MAX_NOME];
    lerString(nomeBuscado, MAX_NOME);
    // Após ler o nome, normaliza-o inteiramente em maiúsculo para a comparação.
    for (int i = 0; nomeBuscado[i] != '\0'; i++){
        nomeBuscado[i] = toupper(nomeBuscado[i]);
    }
    // Efetua a busca pelo código desde o início da lista.
    Elemento *atual = lista->inicio;
    do{
        // Copia e normaliza o nome atual para verificar se é igual.
        char nomeAtual[MAX_NOME];
        strcpy(nomeAtual, atual->nome);
        for (int i = 0; nomeAtual[i] != '\0'; i++){
            nomeAtual[i] = toupper(nomeAtual[i]);
        }
        if((strcmp(nomeBuscado, nomeAtual)) == 0){
            // Caso encontre, retorna o ponteiro para esse elemento.
            return atual;
        }
        atual = atual->proximo;
    }while(atual != lista->inicio);
    // Caso contrário, retorna nulo.
    return NULL;
}
//----------------------------------------------------------------------