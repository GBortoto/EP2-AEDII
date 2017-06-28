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
	printf("Essa fila não está inicializada\n");
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
			printf("inserirNaFila: Não foi possivel alocar memória para o novoNó\n");
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
		printf("removerDaFila: Não foi possível remover da fila - fila vazia\n");
		return -3;
	}
	return -1;
}

void mostraFila(Fila *fila){
	if(filaChecaInicializacao){
		//printf("filaVaria(fila)=%d\n", filaVazia(fila));
		if(filaVazia(fila) == 0){
			No *no = fila->inicio;
			printf("nElementos: %d | ", fila->nElementos);
			printf("Conteúdo da fila:");
			while(no){
				printf(" %d", no->valor);
				no = no->anterior;
			}
			printf("\n");
			return;
		}
		printf("mostraFila: A fila está vazia\n");
		return;
	}
	return;
}

void getFilaInteira(int *valores, Fila *fila){
	int i;
	No *atual = fila->inicio;
	for(i=0; i<fila->nElementos; i++){
		valores[i] = atual->valor;
		atual = atual->prox;
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
	printf("Node criado com sucesso\n");
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
	printf("Trie criada com sucesso\n");
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


int buscaNaTrieRecursivo(Trie *trie, Node* pai, Node *encontrado, int *palavraTraduzida, int i, int length){
	
}


int buscaNaTrie(Trie *trie, char* valor, Node *encontrado){
	if(!checaInicializacaoTrie(trie)){
		return 0;
	}
	
	int length = strlen(valor);
	
	// Traduz a palavra em números
	int i;
	int *palavraTraduzida = (int *) malloc (length * sizeof(int));
	for(i=0; i<length; i++){
		palavraTraduzida[i] = charToInt(palavra[i]);
	}
	
	i = 0;
	buscaNaTrieRecursivo(trie, trie->raiz, encontrado, palavraTraduzida, i, length);
}


/*
bool insereNaTrieRecursivo(int *palavraTraduzida, int i, int length, int position, Node* pai, Trie *trie){
	Node *atual = pai->filho;
	// Se o node não tem filhos (node novo)
	if(!atual){
		// Se o pai for o final da palavra
		if(i == length-1 && pai->conteudo == palavraTraduzida[i]){
			// Insere no node atual a posição
			inserirNaFila(position, pai->positions);
			trie->n_elementos++;
			return 1;
		// Se o pai não for o final da palavra
		} else {
			Node *novoNode = (Node *) malloc(sizeof(Node));
			inicializaNode(novoNode);
			novoNode->conteudo = palavraTraduzida[i];
			printf("Conteúdo: %d", palavraTraduzida[i]);
			pai->filho = novoNode;
			
			trie->altura++;
			
			if(i == length-1){
				inserirNaFila(position, novoNode->positions);
				return 1;
			} else {
				pai = pai->filho;
				i++;
				return insereNaTrieRecursivo(palavraTraduzida, i, length, position, pai, trie);
			}
		}
	} else {
		while(atual){
			// Se acharmos o conteudo que queremos
			if(atual->conteudo == palavraTraduzida[i]){
				// Se estivermos na última letra
				if(i == length-1){
					// Insere no node atual a posição
					inserirNaFila(position, atual->positions);
					trie->n_elementos++;
					return 1;
				} else {
					// Se não estivermos na última letra
					pai = atual;
					i++;
					return insereNaTrieRecursivo(palavraTraduzida, i, length, position, pai, trie);
				}
			// Se não acharmos o conteúdo que queremos
			} else {
				// Se já passamos o valor que procuramos
				if(atual->conteudo > palavraTraduzida[i]){
					Node *novoNode = (Node *) malloc(sizeof(Node));
					inicializaNode(novoNode);
					novoNode->conteudo = palavraTraduzida[i];
					
					// Arrumando a ordem dos irmãos
					if(atual->ant){
						atual->ant->prox = novoNode;
						novoNode->ant = atual->ant;
						atual->ant = novoNode;
						novoNode->prox = atual;
					} else {
						novoNode->prox = atual;
						atual->ant = novoNode;
						pai->filho = novoNode;
					}
					
					if(i == length-1){
						// Insere no node atual a posição
						inserirNaFila(position, novoNode->positions);
						trie->n_elementos++;
						return 1;
					} else {
						pai = novoNode;
						i++;
						return insereNaTrieRecursivo(palavraTraduzida, i, length, position, pai, trie);
					}
			
				// Se ainda não chegamos ao valor procurado
				} else {

					if(!atual->prox){
						Node *novoNode = (Node *) malloc(sizeof(Node));
						inicializaNode(novoNode);
						novoNode->conteudo = palavraTraduzida[i];
						
						atual->prox = novoNode;
						novoNode->ant = atual;
					
						if(i == length-1){
							// Insere no node atual a posição
							inserirNaFila(position, novoNode->positions);
							trie->n_elementos++;
							return 1;
						} else {						
							pai = novoNode;
							i++;
							return insereNaTrieRecursivo(palavraTraduzida, i, length, position, pai, trie);
						}
					}
					
					atual = atual->prox;
				}
			}
		}
	}
}

bool insereNaTrie(char* palavra, int length, int position, Trie *trie){
	if(!checaInicializacaoTrie(trie)){
		return 0;
	}
	// Traduz a palavra em números
	int i;
	int *palavraTraduzida = (int *) malloc (length * sizeof(int));
	for(i=0; i<length; i++){
		palavraTraduzida[i] = charToInt(palavra[i]);
	}
	
	// Seta como primeiro pai a raiz
	Node *pai = trie->raiz;
	i = 0;
	insereNaTrieRecursivo(palavraTraduzida, i, length, position, pai, trie);
}
*/


int getAlturaTrie(Trie *trie){
	return trie->altura;
}

int getNElementosTrie(Trie *trie){
	return trie->n_elementos;
}

// -------------- Implementação da trie -----------------------


void main(void){
	Trie *trie = (Trie *) malloc(sizeof(Trie));
	inicializaTrie(trie);
	bool resultado = insereNaTrie("teste", 5, 0, trie);
	//printf("Resultado: %d | n_elementos: %d | Altura: %d", resultado, getNElementosTrie(trie), getAlturaTrie(trie));
}