#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_WEIGHT 30000
#define NUM_VERTEX 9999
#define OPT_TOTAL_WEIGHT (20 * (NUM_VERTEX/3))
#define NUM_EDGES (NUM_VERTEX*NUM_VERTEX)
#define NUM_MST_EDGES (NUM_VERTEX-1)
#define MAX_HEAP_SIZE (NUM_VERTEX*NUM_VERTEX)

/* GRAPH DECLARATIONS */
typedef struct edge {
	short int from;
	short int to;
	short int weight;
	short int deleted;
} Edge;
Edge edges[NUM_VERTEX*NUM_VERTEX];
Edge mst_edges[2*NUM_MST_EDGES];
short int bsf_touched_vertex[NUM_VERTEX];
short int euler_path[2*NUM_MST_EDGES - 1];
short int hamilton_path[NUM_VERTEX];
short int adj_matrix[NUM_VERTEX][NUM_VERTEX];
void init_edges();
char is_bridge(short int a, short int b);

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
void mst_duplicate_edges();

void find_euler_path();
int find_hamiltonian_path();

/* QUEUES DECLARATIONS */
short int queue[NUM_VERTEX];
short int queue_first = 0;
short int queue_last = 0;

void init_adj();

int main(void) {
	int i, j, sum_w = 0;

	//printf("Começando inicialização\n");
	init_adj();
	ufind_init();
	init_heap();
	init_edges();
	//printf("Inicialização finalizada\n\n");

	//printf("Gerando MST\n");
	mst();
	//printf("MST gerada\n\n");

	//printf("Duplicando aresta\n");
	mst_duplicate_edges();
	//printf("Arestas duplicadas\n\n");

	//printf("Calculando caminho euleriano\n");
	find_euler_path();
	//printf("Caminho euleriano calculado\n\n");

	//printf("Calculando caminho hamiltoniano\n");
	sum_w = find_hamiltonian_path();
	//printf("Caminho hamiltoniano calculado\n\n");

	if (sum_w <= 2*OPT_TOTAL_WEIGHT) {
		printf("ALGORITMO PASSOU!\n");
		printf("%d vs %d\n", OPT_TOTAL_WEIGHT, sum_w);
	}

	return 0;
}

void init_adj() {
    int i, j;
    
    for (i = 0; i < NUM_VERTEX; i++) {
        for (j = 0; j < NUM_VERTEX; j++) {
            adj_matrix[i][j] = 10;
        }
        adj_matrix[i][i] = MAX_WEIGHT;
    }
    adj_matrix[0][1] = 5;
    adj_matrix[1][0] = 5;
    adj_matrix[1][2] = 5;
    adj_matrix[2][1] = 5;
    adj_matrix[1][4] = 5;
    for (i = 3; i < NUM_VERTEX; i += 3) {
        adj_matrix[i][i+1] = 5;
        adj_matrix[i+1][i] = 5;
        adj_matrix[i+1][i+2] = 5;
        adj_matrix[i+2][i+1] = 5;
        adj_matrix[i+1][i-2] = 5;
    }
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

	k = 0;
	mst_num_edges = 0;
	for (i = 0; i < NUM_VERTEX; i++) {
		for (j = 0; j < NUM_VERTEX; j++)
		{
			edges[k].from = i;
			edges[k].to = j;
			edges[k].weight = adj_matrix[i][j];
			edges[k].deleted = FALSE;
			k++;
		}
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

/* Calcula a árvore geradora mínima do grafo */
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

/* Duplica as arestas da MST */
void mst_duplicate_edges() {
	int i, j;

	for (i = 0; i < NUM_MST_EDGES; i++) {
		j = i + NUM_MST_EDGES;
		mst_edges[j].to = mst_edges[i].from;
		mst_edges[j].from = mst_edges[i].to;
		mst_edges[j].weight = mst_edges[i].weight;
		mst_edges[j].deleted = 0;
	}
}

/* Diz se o arco a-b é uma ponte do grafo. Usa BFS. */
char is_bridge(short int a, short int b) {
	int s, i, j;

	for (i = 0; i < NUM_VERTEX; i++) {
		bsf_touched_vertex[i] = FALSE;
		queue[i] = 0;
	}

	// deleta o arco a-b
	for (i = 0; i < 2*NUM_MST_EDGES; i++) {
		if (mst_edges[i].from == a && mst_edges[i].to == b) {
			mst_edges[i].deleted = TRUE;
		}
	}

	// inicializa a queue
	queue_first = 0;
	queue_last = 0;
	queue[queue_first] = a;

	// BFS no grafo sem o arco a-b
	while (queue_first <= queue_last) {
		//pega o primeiro elemento da fila
		s = queue[queue_first % NUM_VERTEX];
		queue_first++;
		bsf_touched_vertex[s] = TRUE;

		// coloca todos os vértices adjacentes a s na fila
		for (i = 0; i < 2*NUM_MST_EDGES; i++) {
			if (!mst_edges[i].deleted) {
				if (mst_edges[i].from == s && bsf_touched_vertex[mst_edges[i].to] == FALSE) {
					queue_last++;
					queue[queue_last % NUM_VERTEX] = mst_edges[i].to;
					bsf_touched_vertex[mst_edges[i].to] = TRUE;
				}
				else if (mst_edges[i].to == s && bsf_touched_vertex[mst_edges[i].from] == FALSE) {
					queue_last++;
					queue[queue_last % NUM_VERTEX] = mst_edges[i].from;	
					bsf_touched_vertex[mst_edges[i].from] = TRUE;
				}
			}
		}
	}

	//recoloca o arco a-b
	for (i = 0; i < 2*NUM_MST_EDGES; i++) {
		if (mst_edges[i].from == a && mst_edges[i].to == b) {
			mst_edges[i].deleted = FALSE;
		}
	}

	// se b não foi tocado, a-b é uma ponte.
	if (!bsf_touched_vertex[b]) {
		return TRUE;
	}
	return FALSE;
}

// Acha o caminho euleriano na MST do grafo. Supõe que o grafo é euleriano.
void find_euler_path() {
	int i, v, count_edges, count_deleted_edges, next_index, last_index;
	char mst_empty = FALSE;
	last_index = 1;
	next_index = 0;

	for (i = 0; i < 2*NUM_MST_EDGES + 1; i++)
		euler_path[i] = -1;

	euler_path[next_index] = 0; //primeiro vertice do caminho é o 0.

	while (!mst_empty && last_index < 2*NUM_MST_EDGES) {
		v = euler_path[next_index]; 
		next_index++;

		// verifica quantas arestas são incidentes em v
		count_edges = 0;
		count_deleted_edges = 0;
		for (i = 0; i < 2*NUM_MST_EDGES; i++) {
			if (!mst_edges[i].deleted) {
				if (mst_edges[i].to == v || mst_edges[i].from == v) {
					count_edges++;
				}
			}
			else {
				count_deleted_edges++;
			}
		}
		if (count_deleted_edges == 2*NUM_MST_EDGES) {
			mst_empty = TRUE;
		} 
		else if (count_edges == 1) {
			for (i = 0; i < 2*NUM_MST_EDGES; i++) {
				if(!mst_edges[i].deleted) {
					if (mst_edges[i].to == v) {
						euler_path[last_index] = mst_edges[i].from;
						last_index++;
						mst_edges[i].deleted = TRUE;
						break;
					} 
					else if (mst_edges[i].from == v) {
						euler_path[last_index] = mst_edges[i].to;
						last_index++;
						mst_edges[i].deleted = TRUE;
						break;
					}
				}
			}
		} 
		else if (count_edges > 1) {
			for (i = 0; i < 2*NUM_MST_EDGES; i++) {
				if (!mst_edges[i].deleted) {
					if (mst_edges[i].to == v) {
						if (!is_bridge(mst_edges[i].to, mst_edges[i].from)) {
							euler_path[last_index] = mst_edges[i].from;
							last_index++;
							mst_edges[i].deleted = TRUE;
							break;
						}
					} 
					else if (mst_edges[i].from == v) {
						if (!is_bridge(mst_edges[i].from, mst_edges[i].to)) {
							euler_path[last_index] = mst_edges[i].to;
							last_index++;
							mst_edges[i].deleted = TRUE;
							break;
						}
					}
				}
			}
		}
	}

	// ALGORITMO DE FLEURY - achar caminho euleriano
	//G' := G { G' = (V', E')} 
	//v0 := um vértice de G' 
	//C := [v0] {Inicialmente, o circuito contém só v0} 
	//	Enquanto E' não vazio
	//		vi := último vértice de C 
	//		Se vi tem só uma aresta incidente;
	//			ai := a aresta incidente a vi em G'
	//		Senão
	//			ai := uma aresta incidente a vi em G' e que não é uma ponte
	//		Retirar a aresta ai do grafo G' 
	//		Acrescentar ai no final de C 
	//		vj := vértice ligado a vi por ai 
	//		Acrescentar vj no final de C
//
//	Retornar C

}

// Acha o caminho hamiltoniano a partir do caminho euleriano
int find_hamiltonian_path() {
	int v, i, j, path_index, total_weight;
	char v_in_hamilton_path;

	for (i = 0; i < NUM_VERTEX; i++)
		hamilton_path[i] = -1;

	total_weight = 0;
	hamilton_path[0] = euler_path[0];
	path_index = 1;

	for (i = 1; i < 2*NUM_MST_EDGES - 1; i++) {
		v = euler_path[i];
		v_in_hamilton_path = FALSE;

		for (j = 0; j < NUM_VERTEX; j++) {
			if (hamilton_path[j] == v)
				v_in_hamilton_path = TRUE;
		}

		if (!v_in_hamilton_path) {
			hamilton_path[path_index] = v;
			total_weight += adj_matrix[hamilton_path[path_index-1]][v];
			path_index++;
		}
	}
	total_weight += adj_matrix[ hamilton_path[NUM_VERTEX-1] ][ hamilton_path[0] ];

	return total_weight;
}
