#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define MAX_INT 2147483647
#define ALPHABET_SIZE 128
#define TEXT_SIZE 75

/* TRIE DEFINITIONS */
struct node {
	int freq;
	char ch;
	struct node *left;
	struct node *right;
};
typedef struct node Node;

char texto[TEXT_SIZE] = "Se eu fosse um peixinho e soubesse nada, levaria o mundo pro fundo do mar.";
Node alfabeto[ALPHABET_SIZE];

void count_frequency(char ch);

/* MINIMUM PRIORITY QUEUE DEFINITIONS */
Node heap[MAX];
int heap_size;

void init_heap();
void heapify();
Node get_min();
void insert(Node new);
void swap(int pos1, int pos2);

int main(int argc, char const *argv[]) {
	int i;

	for (int i = 0; i < ALPHABET_SIZE; ++i)	{
		alfabeto[i].ch = i;
		alfabeto[i].freq = 0;
		alfabeto[i].left = NULL;
		alfabeto[i].right = NULL;
	}

	for (int i = 0; i < ALPHABET_SIZE; i++) 
		count_frequency((char) i);
	
	for (int i = 0; i < ALPHABET_SIZE; ++i)	{
		printf("%d -> %c, %d\n", i, alfabeto[i].ch, alfabeto[i].freq);
	}

	printf("\nfim do programa\n");
	return 0;
}

/* TRIE IMPLEMENTATIONS */
void count_frequency(char ch) {
	int i;
	for (int i = 0; i < TEXT_SIZE; i++)
		if (texto[i] == ch)
			alfabeto[ch].freq++;
}

/* MINIMUM PRIORITY QUEUE IMPLEMENTATIONS */
void init_heap() {
	int i;

	for (i = 0; i < MAX; i++) {
		heap[i].freq = MAX_INT;
	}

	heap_size = 0;
}

void heapify() {
	int pai, filho1, filho2, pos_min_filho;

	pai = 0;
	while (pai < heap_size) {
		filho1 = (2 * pai) + 1;
		filho2 = filho1 + 1;
		if (heap[pai].freq <= heap[filho1].freq || heap[pai].freq <= heap[filho2].freq)
			break;
		
		pos_min_filho = heap[filho1].freq >= heap[filho2].freq ? filho2 : filho1;
		swap(pai, pos_min_filho);
		pai = pos_min_filho;
	}
}

Node get_min() {
	Node result = heap[0];

	heap[0] = heap[heap_size-1];
	heap_size--;
	heapify();

	return result;
}

void insert(Node new) {
	int p;

	if (heap_size == MAX) {
		printf("Heap cheio\n");
		return;
	}
	heap_size++;
	heap[heap_size - 1] = new;

	p = heap_size - 1;
	while(p >= 1 && heap[p/2].freq > heap[p].freq) {
		swap(p/2, p);
		p = p/2;
	}
}

void swap(int pos1, int pos2) {
	Node temp;

	temp = heap[pos1];
	heap[pos1] = heap[pos2];
	heap[pos2] = temp;
}