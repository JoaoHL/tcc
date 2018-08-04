/* OBS.: Resultados da codificação verificados no site:
 * http://resources.nerdfirst.net/huffman
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

#define MAX 129
#define MAX_INT 2147483647
#define ALPHABET_SIZE 128
#define TEXT_SIZE 682
#define TRUE 1
#define FALSE 0

/* TRIE DEFINITIONS */
typedef struct node Node;
struct node {
	unsigned long int freq;
	char ch;
	char code[50];
	short int done;
	Node *parent;
	Node *left;
	Node *right;
};

char texto[TEXT_SIZE] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Praesent eget risus vitae massa semper aliquam quis mattis quam. Morbi vitae tortor tempus, placerat leo et, suscipit lectus. Phasellus ut euismod massa, eu eleifend ipsum. Nulla eu neque commodo, dapibus dolor eget, dictum arcu. In nec purus eu tellus consequat ultricies. Donec feugiat tempor turpis, rutrum sagittis mi venenatis at. Sed molestie lorem a blandit congue. Ut pellentesque odio quis leo volutpat, vitae vulputate felis condimentum. Praesent vulputate fermentum lorem, id rhoncus sem vehicula eu. Quisque ullamcorper, orci adipiscing auctor viverra, velit arcu malesuada metus, in volutpat tellus sem at justo.";
Node alfabeto[ALPHABET_SIZE];
// Esses nós servem como nós intermediarios da arvore, em contraposição às folhas da árvore
Node intermediarios[ALPHABET_SIZE];
int used_intermediaries;

void count_frequencies();
Node *build_trie();

/* MINIMUM PRIORITY QUEUE DEFINITIONS */
Node *heap[MAX];
int heap_size;

void init_heap();
void heapify();
Node *get_min();
void insert(Node *new);
void swap(int pos1, int pos2);

void generate_codes(Node *root);

int main(int argc, char const *argv[]) {
	int i;
	unsigned long int output_size = 0, input_size = 0;
	Node *raiz, *aux;
	char code[50], input;
	clock_t start, end, total;

	start = clock();

	printf("\nInicializando nós...\n");
	for (int i = 0; i < ALPHABET_SIZE; i++)	{
		alfabeto[i].ch = i;
		alfabeto[i].freq = 0;
		alfabeto[i].done = FALSE;
		alfabeto[i].parent = NULL;
		alfabeto[i].left = NULL;
		alfabeto[i].right = NULL;
	}
	printf("Inicialização OK\n");

	printf("\nCalculando frequência de caracteres...\n");
	while (scanf("%c", &input) != EOF) {
		input_size++;
		alfabeto[input].freq++;
	}
	for (int i = 0; i < ALPHABET_SIZE; i++)	{
		if (alfabeto[i].freq > 0)
			insert(&alfabeto[i]);
	}
	printf("\n");
	printf("Calculo de frequencia OK\n");

	printf("\nBuildando trie...\n");
	raiz = build_trie();
	printf("Build OK\n");

	printf("\nGerando códigos...\n");
	generate_codes(raiz);
	printf("Gerando códigos OK\n");

	end = clock();

	printf("\nTamanho original do arquivo (em megabytes): %.2f\n", (double) (input_size*sizeof(char))/1000000);
	output_size = 0;
	for (int i = 0; i < ALPHABET_SIZE; i++)	{
		if (alfabeto[i].freq > 0)
			output_size += (alfabeto[i].freq * strlen(alfabeto[i].code));
	}
	printf("Tamanho do arquivo codificado (em megabytes, aprox.): %.2f\n", (double) output_size/8000000);
	printf("Taxa de compressão: %ld/%ld = %.2f%\n", output_size, input_size*sizeof(char)*CHAR_BIT, (double) output_size/(input_size*sizeof(char)*CHAR_BIT) * 100);
	printf("Tempo de execução do programa (em segundos): %.5f\n", (double) (end-start)/CLOCKS_PER_SEC);
	printf("\nFim do programa\n");
	return 0;
}

/* TRIE IMPLEMENTATIONS */
// Conta a frequencia de cada caractere da string hardcoded
void count_frequencies() {
	int i;
	for (int i = 0; i < TEXT_SIZE; i++)
		alfabeto[texto[i]].freq++;
}

// Constroi a trie de codificação. Retorna a raiz da trie.
Node *build_trie() {
	Node *raiz;

	while (heap_size > 1) {
		raiz = &intermediarios[used_intermediaries];
		raiz->left = get_min();
		raiz->left->parent = raiz;
		raiz->right = get_min();
		raiz->right->parent = raiz;
		raiz->freq = raiz->left->freq + raiz->right->freq;

		insert(raiz);
		used_intermediaries++;
	}

	raiz = get_min();
	return raiz;
}

/* MINIMUM PRIORITY QUEUE IMPLEMENTATIONS */
void init_heap() {
	int i;

	for (i = 1; i < MAX+1; i++) {
		heap[i] = NULL;
	}

	heap_size = 0;
}

void heapify() {
	int pai, filho;

	pai = 1;
	filho = 2;
	while (filho <= heap_size) {
		if (filho < heap_size && heap[filho]->freq > heap[filho + 1]->freq)
			filho++;
		if (heap[filho]->freq < heap[pai]->freq)
			swap(pai, filho);
		else
			break;
		pai = filho;
		filho = 2*filho;
	}
}

Node *get_min() {
	Node *result = heap[1];

	heap[1] = heap[heap_size];
	heap[heap_size] = NULL;
	heap_size--;
	heapify();

	return result;
}

void insert(Node *new) {
	int p;

	if (heap_size == MAX) {
		printf("Heap cheio\n");
		return;
	}
	heap_size++;
	heap[heap_size] = new;

	p = heap_size;
	while(p > 1 && heap[p/2]->freq > heap[p]->freq ) {
		swap(p/2, p);
		p = p/2;
	}
}

void swap(int pos1, int pos2) {
	Node *temp;

	temp = heap[pos1];
	heap[pos1] = heap[pos2];
	heap[pos2] = temp;
}

void generate_codes(Node *root) {
	Node *aux = root;
	int index = 0;
	char code[50];

	while (!root->done) {
		// se for uma folha
		if (aux->left == NULL && aux->right == NULL) {
			code[index] = '\0';
			strcpy(aux->code, code);
			//printf("%s -> '%c' (freq= %d) // %ld bits\n", aux->code, aux->ch, aux->freq, strlen(aux->code));
			aux->done = TRUE;
			aux = aux->parent;
			index--;
		}
		// se for um nó interno e não teve suas duas subtries codificadas
		// OBS.: começa sempre pelo filho esquerdo
		else if (!aux->left->done || !aux->right->done ){
			if(!aux->left->done) {
				code[index] = '0';
				index++;
				aux = aux->left;
			}
			else {
				code[index] = '1';
				index++;
				aux = aux->right;
			}
		}
		// se for um nó interno e suas subtries foram inteiramente codificadas
		else {
			aux->done = TRUE;
			aux = aux->parent;
			index--;
		}
	}
}