// Trie
/*
	Implementação da Trie - Eps 2.1 e 2.2
	
	Dicente: Guilherme Bortoto de Moraes
	  NºUSP: 9360760

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// -------------- Implementação da fila -----------------------

typedef struct No{
	int valor;
	struct No *anterior;
	struct No *prox;
}No;

typedef struct Fila{
	No *inicio;
	No *fim;
	int nElementos;
}Fila;

bool inicializaFila(Fila *fila){
	fila->inicio = NULL;
	fila->fim = NULL;
	fila->nElementos = 0;	
}

bool filaChecaInicializacao(Fila *fila){
	if(fila){
		return 1;
	}
	////printf("Essa fila não está inicializada\n");
	return 0;
}

int filaVazia(Fila *fila){
	if(filaChecaInicializacao){
		if(fila->nElementos == 0){
			return 1;
		}
		return 0;
	}
	return -1;
}

int inserirNaFila(int elemento, Fila *fila){
	if(filaChecaInicializacao){
		No *novoNo = (No *) malloc(sizeof(No));
		if(!novoNo){
			////printf("inserirNaFila: Não foi possivel alocar memória para o novoNó\n");
			return -2;
		}
		novoNo->valor = elemento;
		novoNo->prox = fila->fim;
		novoNo->anterior = NULL;
		
		if(filaVazia(fila) == 1){
			fila->inicio = novoNo;
			fila->fim = novoNo;
		}else{
		fila->fim->anterior = novoNo;
		fila->fim = novoNo;	
		}
		fila->nElementos++;
		return 1;
	}
	return -1;
}

int removerDaFila(Fila *fila){
	if(filaChecaInicializacao){
		if(filaVazia(fila) == 0){
			int valor = fila->inicio->valor;
			fila->inicio = fila->inicio->anterior;
			if(fila->inicio){
				fila->inicio->prox->anterior = NULL;
				free(fila->inicio->prox);
				fila->inicio->prox = NULL;
			}else{
				free(fila->fim);
				fila->fim = NULL;
			}
			fila->nElementos--;
			return valor;
		}
		////printf("removerDaFila: Não foi possível remover da fila - fila vazia\n");
		return -3;
	}
	return -1;
}

void mostraFila(Fila *fila){
	if(filaChecaInicializacao){
		////printf("filaVaria(fila)=%d\n", filaVazia(fila));
		if(filaVazia(fila) == 0){
			No *no = fila->inicio;
			////printf("nElementos: %d | ", fila->nElementos);
			////printf("Conteúdo da fila:");
			while(no){
				////printf(" %d", no->valor);
				no = no->anterior;
			}
			////printf("\n");
			return;
		}
		////printf("mostraFila: A fila está vazia\n");
		return;
	}
	return;
}

void getFilaInteira(int *valores, Fila *fila){
	int i;
	No *atual = fila->inicio;
	for(i=0; i<fila->nElementos; i++){
		valores[i] = atual->valor;
		atual = atual->anterior;
	}	 
}
// -------------- Implementação da fila -----------------------







// -------------- Implementação da trie -----------------------

typedef struct Node {
	// As letras são armazenadas como inteiros de 0 a 25
	int conteudo;
	struct Node * filho;
	// Irmãos:
	struct Node * ant;
	struct Node * prox;
	// Posições onde a palavra aparece
	Fila *positions;
} Node;

typedef struct {
	Node * raiz;
	int n_elementos;
	int altura;
	int currentPosition;
} Trie;

// Converte uma letra para um número
// a, b, c, d, e, f, ..., z
// 0, 1, 2, 3, 4, 5, ..., 25
int charToInt(char letra){
	char letras[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g',
			  'h', 'i', 'j', 'k', 'l', 'm', 'n',
			  'o', 'p', 'q', 'r', 's', 't', 'u',
			  'v', 'w', 'x', 'y', 'z'};
	int i;
	for(i=0; i<26; i++){
		if(letra == letras[i]){
			return i;
		}
	}
	return -1;
}

// Converte um número para uma letra
// 0, 1, 2, 3, 4, 5, ..., 25
// a, b, c, d, e, f, ..., z

char intToChar(int Nletra){
	char letras[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g',
			  'h', 'i', 'j', 'k', 'l', 'm', 'n',
			  'o', 'p', 'q', 'r', 's', 't', 'u',
			  'v', 'w', 'x', 'y', 'z'};
	int i;
	if(Nletra >= 0 && Nletra <= 25){
		return letras[Nletra];
	}
	return '!';
}

bool inicializaNode(Node *node){
	if(!node){
		return 0;
	}
	node->conteudo = -1;
	node->filho = NULL;
	node->ant = NULL;
	node->prox = NULL;
	node->positions = (Fila *) malloc(sizeof(Fila *));
	inicializaFila(node->positions);
	////printf("Node criado com sucesso\n");
	return 1;
	
}

bool inicializaTrie(Trie *trie){
	// Cria a raiz
	trie->raiz = (Node*) malloc(sizeof(Node));
	
	// Inicializa a raiz
	inicializaNode(trie->raiz);
	
	// Inicializa valores internos da Trie
	trie->n_elementos = 0;
	trie->altura = 0;
	trie->currentPosition = 0;
	////printf("Trie criada com sucesso\n");
	return 1;
}

bool checaInicializacaoTrie(Trie *trie){
	if(!trie){
		return 0;
	}
	if(!trie->raiz){
		return 0;
	}
	if(!trie->raiz->positions){
		return 0;
	}
	return 1;
}

void mostraTrieRecursivo(Node *node, int i){
	if(!node){
		return;
	}
	char *conteudo = (char *) malloc(sizeof(char));
	conteudo[0] = intToChar(node->conteudo);
	
	int j;
	for(j=0; j<i; j++){
		//printf("\t");
	}	
	//printf("%s\n", conteudo);
	//printf("%d\n", node->conteudo);
	mostraTrieRecursivo(node->filho, i+1);
	mostraTrieRecursivo(node->prox, i);
	
	return;
}

void mostraTrie(Trie *trie){
	if(checaInicializacaoTrie(trie)){
		mostraTrieRecursivo(trie->raiz, 0);
		return;
	}
	//printf("Trie não inicializada\n");
	return;
}


Node *buscaNaTrieRecursivo(Trie *trie, Node* pai, int *palavraTraduzida, int i, int length){
	Node *atual = pai->filho;
	while(atual){
		//printf("atual->conteudo = %d | palavraTraduzida[i] = %d\n", atual->conteudo, palavraTraduzida[i]);
		////printf("atual->conteudo = %d\n", atual->conteudo);
		////printf("palavraTraduzida[i] = %d\n", palavraTraduzida[i]);
		if(atual->conteudo == palavraTraduzida[i]){
			//printf("Entrou");
			//printf("i = %d\n", i);
			//printf("length-1 = %d\n", length-1);
			if(i == length - 1){
				//printf("Final\n");
				return atual;
			} else {
				pai = atual;
				return buscaNaTrieRecursivo(trie, pai, palavraTraduzida, i+1, length);	
			}
		} else {
			atual = atual->prox;
		}
	}
	//printf("%d\n", -1);
	return NULL;	
}

Node *buscaNaTrie(Trie *trie, char* valor){
	if(!checaInicializacaoTrie(trie)){
		return 0;
	}
	
	int length = strlen(valor);
	
	// Traduz a palavra em números
	int i;
	int *palavraTraduzida = (int *) malloc (length * sizeof(int));
	for(i=0; i<length; i++){
		palavraTraduzida[i] = charToInt(valor[i]);
	}
	
	i = 0;
	return buscaNaTrieRecursivo(trie, trie->raiz, palavraTraduzida, i, length);
}

int buscaDoUsuario(Trie *trie, char *palavra){
	Node *encontrado = buscaNaTrie(trie, palavra);
	
	if(!encontrado){
		return -1;
	}
	if(!filaChecaInicializacao(encontrado->positions)){
		return -1;
	}
	//mostraFila(encontrado->positions);
	
	int length = encontrado->positions->nElementos;
	
	if(length == 0){
		printf("%d\n", -1);
		return 0;
	}
	
	int *elementos = (int *) malloc(sizeof(int) * length);
	getFilaInteira(elementos, encontrado->positions);
	
	int i;
	for(i=0; i<length; i++){
		if(i < length-1){
			printf("%d ", elementos[i]);
		} else {
			printf("%d\n", elementos[i]);
		}
	}
	return 1;
}


bool insereNaTrieRecursivo(Trie *trie, Node* pai, int *palavraTraduzida, int i, int length, int position){
	Node *atual = pai->filho;
	if(atual == NULL){
		//printf("Caso 1\n");
		Node *novoNode = (Node *) malloc(sizeof(Node));
		inicializaNode(novoNode);
		novoNode->conteudo = palavraTraduzida[i];
		pai->filho = novoNode;
		trie->altura++;
		trie->n_elementos++;
		
		//printf("i = %d\n", i);
		//printf("length-1 = %d\n", length-1);
		if(i == length-1){
			inserirNaFila(position, novoNode->positions);
			return 1;
		} else {
			return insereNaTrieRecursivo(trie, novoNode, palavraTraduzida, i+1, length, position);
		}
	} else {
		while(atual){
			//printf("atual->conteudo = %d | palavraTraduzida[i] = %d\n", atual->conteudo, palavraTraduzida[i]);
			if(atual->conteudo == palavraTraduzida[i]){
				//printf("atual->conteudo == palavraTraduzida[i]\n");
				if(i == length - 1){
					//printf("Entrou aqui\n");
					inserirNaFila(position, atual->positions);
					mostraFila(atual->positions);
					return 1;
				} else {
					pai = atual;
					return insereNaTrieRecursivo(trie, pai, palavraTraduzida, i+1, length, position);
				}
			} else {
				if(atual->conteudo > palavraTraduzida[i]){
					//printf("Caso 2\n");
					Node *novoNode = (Node *) malloc(sizeof(Node));
					inicializaNode(novoNode);
					novoNode->conteudo = palavraTraduzida[i];
					novoNode->ant = atual->ant;
					novoNode->prox = atual;
					
					if(atual->ant){
						atual->ant->prox = novoNode;
					}
					
					atual->ant = novoNode;

					if(pai->filho == atual){
						pai->filho = novoNode;
					}
					trie->n_elementos++;
					
					if(i == length-1){
						inserirNaFila(position, novoNode->positions);
						return 1;
					} else {
						pai = novoNode;
						return insereNaTrieRecursivo(trie, pai, palavraTraduzida, i+1, length, position);
					}
				}
			}
			if(!atual->prox){
				//printf("Caso 3\n");
				Node *novoNode = (Node *) malloc(sizeof(Node));
				inicializaNode(novoNode);
				novoNode->conteudo = palavraTraduzida[i];
				novoNode->ant = atual;
				atual->prox = novoNode;
				trie->n_elementos++;
				
				if(i == length-1){
					inserirNaFila(position, novoNode->positions);
					return 1;
				} else {
					pai = novoNode;
					return insereNaTrieRecursivo(trie, pai, palavraTraduzida, i+1, length, position);
				}
			} else {
				atual = atual->prox;
			}
		}
	}
}

bool insereNaTrie(Trie *trie, char* palavra){
	if(!checaInicializacaoTrie(trie)){
		return 0;
	}
	
	int length = strlen(palavra);
	
	// Traduz a palavra em números
	int i;
	int *palavraTraduzida = (int *) malloc (length * sizeof(int));
	for(i=0; i<length; i++){
		palavraTraduzida[i] = charToInt(palavra[i]);
	}
	
	// Seta como primeiro pai a raiz
	i = 0;
	insereNaTrieRecursivo(trie, trie->raiz, palavraTraduzida, i, length, trie->currentPosition);
	
	trie->currentPosition = trie->currentPosition + length + 1;
}

// -------------- Implementação da trie -----------------------




Node *buscaMultiplaDoUsuario(Trie *trie, char *palavra){
	Node *encontrado = buscaNaTrie(trie, palavra);
	
	if(!encontrado){
		Node *tmp = (Node *) malloc(sizeof(Node));
		inicializaNode(tmp);
		tmp->conteudo = -1;
		return tmp;
	}
	if(!filaChecaInicializacao(encontrado->positions)){
		return NULL;
	}
	//mostraFila(encontrado->positions);
	
	//int length = encontrado->positions->nElementos;
	
	/*
	if(length == 0){
		printf("%d\n", -1);
		return 0;
	}
	
	
	int *elementos = (int *) malloc(sizeof(int) * length);
	getFilaInteira(elementos, encontrado->positions);
	
	
	int i;
	for(i=0; i<length; i++){
		if(i < length-1){
			printf("%d ", elementos[i]);
		} else {
			printf("%d\n", elementos[i]);
		}
	}
	return 1;
	*/
	return encontrado;
}





















int main(){
	
	int nTexts[1];
	scanf("%d%*c", nTexts);
	
	int nTextos = nTexts[0];
	
	int i;
	int j;
	
	int **resultados = (int **) malloc(sizeof(int *) * nTextos);
	int tamanhos[nTextos];
	int *elementos;
	
	
	for(i=0; i<nTextos; i++){
		Trie *trie = (Trie *) malloc(sizeof(Trie));
		inicializaTrie(trie);
		char text[128];
		char search[128];
		scanf("%[^\n]%*c", text);
		scanf("%[^\n]%*c", search);
		
		char *palavra;
		palavra = strtok (text, " ");
		while (palavra != NULL)
		{
			insereNaTrie(trie, palavra);
			palavra = strtok (NULL, " ");
		}
		
		
		char *palavraPesquisa;
		palavraPesquisa = strtok (search, " ");
		while (palavraPesquisa != NULL)
		{
			Node *tmp = buscaMultiplaDoUsuario(trie, palavraPesquisa);
			if(tmp){
				int length = tmp->positions->nElementos;
			
				if(length == 0){
					elementos = (int *) malloc(sizeof(int));
					elementos[0] = -1;
					//int elementos[1] = {-1};
					tamanhos[i] = 1;
					resultados[i] = elementos;
				}else{
					elementos = (int *) malloc(sizeof(int) * length);
					//int elementos[length];
					getFilaInteira(elementos, tmp->positions);
					
					for(j=0; j<length; j++){
						printf("Teste %d\n", j);
						printf("%d\n", elementos[j]);
					}
					
					resultados[i] = elementos;
					tamanhos[i] = length;
				}
			} else {
				printf("Testeeeee\n");
				elementos = (int *) malloc(sizeof(int));
				elementos[0] = -1;
				//int elementos[1] = {-1};
				tamanhos[i] = 1;
				resultados[i] = elementos;
			}
			palavraPesquisa = strtok (NULL, " ");
		}
		free(elementos);
	}
	

	int tamanho;
	for(i=0; i<nTextos; i++){
		for(j=0; j<tamanhos[i]; j++){
			printf("[%d][%d]%d ", i, j, resultados[i][j]);
		}
	}
	
	
	/*
	
	
	Trie *trie = (Trie *) malloc(sizeof(Trie));
	inicializaTrie(trie);	
	
	char text[10000];
	////printf("Enter the text:\n");
	scanf("%[^\n]%*c", text);
	
	int nWords[1];
	////printf("Enter the number of words\n");
	scanf("%d%*c", nWords);
	
	char searchTerms[50 * nWords[0]];
	////printf("Enter the search terms\n");
	scanf("%[^\n]%*c", searchTerms);
	
	//char *text = "see a bear sell stock see a bull buy stock bid stock bid stock hear the bell stop";
	
	
	////printf("%s\n", text);
	////printf("\n");
	////printf("%d\n", nWords[0]);
	////printf("\n");
	////printf("%s\n", searchTerms);
	////printf("\n");
	
	char *palavra;
	palavra = strtok (text, " ");
	while (palavra != NULL)
	{
		//printf ("Inserindo %s\n", palavra);
		insereNaTrie(trie, palavra);
		palavra = strtok (NULL, " ");
	}
	
	
	mostraTrie(trie);
	
	char *palavraDeBusca;
	palavraDeBusca = strtok (searchTerms, " ");
	while (palavraDeBusca != NULL)
	{
		//printf ("Buscando %s\n", palavraDeBusca);
		buscaDoUsuario(trie, palavraDeBusca);
		palavraDeBusca = strtok (NULL, " ");
	}
	

	
	
	bool resultado1 = insereNaTrie(trie, "teste", 5, 0);
	//printf("Resultado: %d | n_elementos: %d | Altura: %d\n", resultado1, trie->n_elementos, trie->altura);
	
	bool resultado2 = insereNaTrie(trie, "teste", 5, 6);	
	//printf("Resultado: %d | n_elementos: %d | Altura: %d\n", resultado2, trie->n_elementos, trie->altura);

	//printf("\nPesquisa:\n");
	buscaDoUsuario(trie, "teste");

	*/
	return 0;
}