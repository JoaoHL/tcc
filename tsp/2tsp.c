#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_WEIGHT 30000
#define NUM_VERTEX 10
#define NUM_EDGES (10*(10 - 1))/2
#define MAX_HEAP_SIZE 100

/* GRAPH DECLARATIONS */
typedef struct edge {
	short int from;
	short int to;
	short int weight;
	short int deleted;
} Edge;
Edge edges[NUM_VERTEX*NUM_VERTEX];
Edge mst_edges[NUM_VERTEX-1];
short int euler_path[2*(NUM_VERTEX-1)];
short int hamilton_path[NUM_VERTEX];
short int adj_matrix[NUM_VERTEX][NUM_VERTEX] = 
{
	{MAX_WEIGHT,   1, 100, 100, 100, 100, 100, 100, 100, 100},
	{  1, MAX_WEIGHT,   1, 100,   1, 100, 100, 100, 100, 100},
	{100,   1, MAX_WEIGHT, 100, 100, 100, 100, 100, 100, 100},
	{100, 100, 100, MAX_WEIGHT,   1, 100, 100, 100, 100, 100},
	{100,   1, 100,   1, MAX_WEIGHT,   1, 100,   1, 100, 100},
	{100, 100, 100, 100,   1, MAX_WEIGHT, 100, 100, 100, 100},
	{100, 100, 100, 100, 100, 100, MAX_WEIGHT,   1, 100, 100},
	{100, 100, 100, 100, 100, 100,   1, MAX_WEIGHT,   1,   1},
	{100, 100, 100, 100, 100, 100, 100,   1, MAX_WEIGHT, 100},
	{100, 100, 100, 100, 100, 100, 100,   1, 100, MAX_WEIGHT},
};
void init_edges();

/* UNION-FIND DECLARATIONS */
short int ufind_groups[NUM_VERTEX];
short int ufind_num_group;
void ufind_join_groups(short int a, short int b);
void ufind_init();

/* MIN HEAP DECLARATIONS */
Edge *heap[MAX_HEAP_SIZE+1];
int heap_size;
void init_heap();
void heapify();
Edge *get_min();
void insert(Edge *new);
void swap(int pos1, int pos2);

/* MINIMUM SPANNING TREE DECLARATIONS */
int mst_num_edges;
void mst();



int main(void) {
	int i, sum_w = 0;

	ufind_init();
	init_heap();
	init_edges();

	printf("Numero de grupos: %d\n", ufind_num_group);
	mst();

	for (i = 0; i < NUM_VERTEX-1; i++){
		printf("Aresta %d-%d com peso %d\n", mst_edges[i].from, mst_edges[i].to, mst_edges[i].weight);
		sum_w += mst_edges[i].weight;
	}
	printf("Numero final de grupos: %d\n", ufind_num_group);
	printf("Peso da arvore geradora mínima: %d", sum_w);

	return 0;
}

void ufind_init() {
	short int i;

	ufind_num_group = NUM_VERTEX;
	for (int i = 0; i < NUM_VERTEX; i++)
	{
		ufind_groups[i] = i;
	}
}

/*
 Join the groups of two vertexes 'a' and 'b' 
*/
void ufind_join_groups(short int a, short int b) {
	short int a_group, b_group;
	short int i;

	a_group = ufind_groups[a];
	b_group = ufind_groups[b];
	for (i = 0; i < NUM_VERTEX; i++)
		if (ufind_groups[i] == a_group)
			ufind_groups[i] = b_group;

	ufind_num_group--;
}

short int ufind_from_same_group(short int a, short int b) {
	return ufind_groups[a] == ufind_groups[b];
}

void init_edges() {
	int i, j, k;

	mst_num_edges = 0;
	k = 0;
	for (i = 0; i < NUM_VERTEX; i++)
		for (j = 0; j < NUM_VERTEX; j++)
		{
			edges[k].from = i;
			edges[k].to = j;
			edges[k].weight = adj_matrix[i][j];
			edges[k].deleted = 0;
			k++;
		}
}

/* MINIMUM PRIORITY QUEUE IMPLEMENTATIONS */
void init_heap() {
	int i;

	for (i = 1; i < MAX_HEAP_SIZE+1; i++) {
		heap[i] = NULL;
	}

	heap_size = 0;
}

void heapify() {
	int pai, filho;

	pai = 1;
	filho = 2;
	while (filho <= heap_size) {
		if (filho < heap_size && heap[filho]->weight > heap[filho + 1]->weight)
			filho++;
		if (heap[filho]->weight < heap[pai]->weight)
			swap(pai, filho);
		else
			break;
		pai = filho;
		filho = 2*filho;
	}
}

Edge *get_min() {
	Edge *result = heap[1];

	heap[1] = heap[heap_size];
	heap[heap_size] = NULL;
	heap_size--;
	heapify();

	return result;
}

void insert(Edge *new) {
	int p;

	if (heap_size == MAX_HEAP_SIZE) {
		printf("Heap cheio\n");
		return;
	}
	heap_size++;
	heap[heap_size] = new;

	p = heap_size;
	while(p > 1 && heap[p/2]->weight > heap[p]->weight ) {
		swap(p/2, p);
		p = p/2;
	}
}

void swap(int pos1, int pos2) {
	Edge *temp;

	temp = heap[pos1];
	heap[pos1] = heap[pos2];
	heap[pos2] = temp;
}

/* Calculate the minimum spanning tree of the graph */
void mst() {
	int i, j;
	Edge *dummy;

	for (i = 0; i < NUM_VERTEX*NUM_VERTEX; i++) {
		insert(&edges[i]);
	}
	while (ufind_num_group > 1) {
		dummy = get_min();
		if (!ufind_from_same_group(dummy->from, dummy->to)){
			ufind_join_groups(dummy->from, dummy->to);
			mst_edges[mst_num_edges] = *dummy;
			mst_num_edges++;
		}
	}

}