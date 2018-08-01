#include <stdio.h>
#include <stdlib.h>

#define MAX 129
#define MAX_INT 2147483647
#define ALPHABET_SIZE 128
#define TEXT_SIZE 682

/* TRIE DEFINITIONS */
typedef struct node Node;
struct node {
	int freq;
	char ch;
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

/* UTILITY FUNCS - DEBUGGING ONLY */
void rec_print_trie(Node *root, char *code, int index);

int main(int argc, char const *argv[]) {
	int i;
	Node *raiz, *aux;
	char code[50];

	for (int i = 0; i < ALPHABET_SIZE; i++)	{
		alfabeto[i].ch = i;
		alfabeto[i].freq = 0;
		alfabeto[i].left = NULL;
		alfabeto[i].right = NULL;
	}

	printf("Calculando frequencia de caracteres...\n");
	count_frequencies();
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		if (alfabeto[i].freq > 0) {
			insert(&alfabeto[i]);
		}
	}
	printf("Calculo de frequencia OK\n");

	printf("Buildando trie...\n");
	raiz = build_trie();
	printf("Build OK\n");

	printf("Printando codificação de Huffman...\n");
	rec_print_trie(raiz, code, 0);
	printf("Codificação de Huffman OK\n");

	printf("\nFim do programa\n");
	return 0;
}

/* TRIE IMPLEMENTATIONS */
// Conta a frequencia de cada caractere da string
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
		raiz->right = get_min();
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

/* UTILITY FUNCS - DEBUGGING ONLY */
void rec_print_trie(Node *root, char code[], int index) {
	if (root->left != NULL){
		code[index] = (char) '0';
		rec_print_trie(root->left, code, index+1);
	}
	if (root->right != NULL){
		code[index] = (char) '1';
		rec_print_trie(root->right, code, index+1);		
	}
	if (root->left == NULL && root->right == NULL){
		code[index] = '\0';
		puts(code);
		printf(" -> %c (freq= %d)\n", root->ch, root->freq);
	}
}