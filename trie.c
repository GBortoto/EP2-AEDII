// Trie
/*
	Implementação da Trie - Eps 2.1 e 2.2
	
	Dicente: Guilherme Bortoto de Moraes
	  NºUSP: 9360760

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

// -------------- Implementação da fila -----------------------







// -------------- Implementação da trie -----------------------

typedef struct Node {
	// As letras são armazenadas como
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

bool inicializaTrie(Trie *trie){
	trie->raiz = (Node*) malloc(sizeof(Node));
	if(trie->raiz == NULL){
		return 0;
	}
	trie->n_elementos = 0;
	trie->altura = 0;
	printf("Trie criada com sucesso\n");
	return 1;
}

/*
bool insereNaTrie(){
	
}
*/




// -------------- Implementação da trie -----------------------


void main(void){
	
}