#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define filename "commands.txt"

typedef struct _Edge {
	int vertex1;
	int vertex2;
	int weight;
	int flag;
} Edge;

typedef struct _Graph {
	int n_vertex;
	long long n_edge;
	Edge *edge;
} Graph;

Graph *g;

typedef struct _subset {
	int parent;
	int rank;
} subset;
subset *s;

int Find(int i);
void Merge(int x, int y);
int myComp(const void *a, const void *b);
void Kruskal(FILE *fp);

int main() {
	FILE *fp = fopen(filename, "r");
	char infile[128], outfile[128];
	int n_vertices, n_edges, MAX_WEIGHT, n_mst;
	int i = 0;

	if (!fp) {
		printf("file open error\n");
		exit(-1);
	}
	// ����� ���� �̸� �޾ƿ���
	fgets(infile, sizeof(infile), fp);
	fgets(outfile, sizeof(outfile), fp);

	while (infile[i] != '\n' && infile[i] != '\0')
		i++;
	infile[i] = '\0';
	i = 0;
	while (outfile[i] != '\n' && outfile[i] != '\0')
		i++;
	outfile[i] = '\0';
	fclose(fp);

	// �Է� ���Ͽ��� ������ �ҷ�����
	fp = fopen(infile, "r");
	if (!fp) {
		printf("file open error\n");
		exit(-1);
	}

	fscanf(fp, "%d %d %d", &n_vertices, &n_edges, &MAX_WEIGHT);
	g = (Graph*)malloc(sizeof(Graph));
	g->n_vertex = n_vertices;
	g->n_edge = n_edges;
	g->edge = (Edge*)malloc(sizeof(Edge)*n_edges);

	for (i = 0; i < n_edges; i++)
		fscanf(fp, "%d %d %d", &g->edge[i].vertex1, &g->edge[i].vertex2, &g->edge[i].weight);
	fclose(fp);

	// �ʱ�ȭ (make-set)
	s = (subset*)malloc(sizeof(subset)*n_vertices);
	for (i = 0; i < n_vertices; i++) {
		s[i].parent = i;
		s[i].rank = 0;
	}

	fp = fopen(outfile, "w");
	// make MST & print result
	Kruskal(fp);

	fclose(fp);

	// �޸� ����
	free(s);
	free(g->edge);
	free(g);

	return 0;
}

// disjoint sets (union-find)
// find() - path compression
int Find(int i) {
	if (s[i].parent == i)
		return i;

	return s[i].parent = Find(s[i].parent);
}

// union() - union by rank
void Merge(int x, int y) {
	int xroot = Find(x);
	int yroot = Find(y);

	if (s[xroot].rank < s[yroot].rank)
		s[xroot].parent = yroot;
	else {
		s[yroot].parent = xroot;
		if (s[xroot].rank == s[yroot].rank)
			s[xroot].rank++;
	}
}

int myComp(const void *a, const void *b) {
	Edge *a1 = (Edge*)a;
	Edge *b1 = (Edge*)b;
	return a1->weight - b1->weight;
}

void Kruskal(FILE *fp) {
	int e = 0, i = 0, k;
	int cnt = 0;
	int *root;
	Graph *result;
	clock_t start, end1, end2;

	start = clock();
	// weight ���� ������ ����
	qsort(g->edge, g->n_edge, sizeof(g->edge[0]), myComp);
	end2 = clock();

	// connected graph�� �ƴϸ� MST edge ������ ������ �� ����
	// ��� edge ��ȸ�ϸ鼭 �� vertex�� root�� �ٸ��� �����Ѵ�
	for (i = 0; i < g->n_edge; i++) {
		Edge eg = g->edge[i];
		g->edge[i].flag = 0;
		int x = Find(eg.vertex1);
		int y = Find(eg.vertex2);

		if (x != y) {
			Merge(x, y);
			g->edge[i].flag = 1;
		}
	}

	// cnt : connected component ����
	for (e = 0; e < g->n_vertex; e++) {
		if (e == Find(e)) {
			cnt++;
		}
	}

	// cnt��ŭ ��� ������ �迭 �Ҵ� �� �ʱ�ȭ
	result = (Graph*)malloc(sizeof(Graph)*cnt);
	for (i = 0; i < cnt; i++) {
		result[i].n_vertex = 0;
		result[i].n_edge = 0;
	}

	// root vertex ����
	root = (int*)malloc(sizeof(int)*cnt);
	i = 0;
	for (e = 0; e < g->n_vertex; e++) {
		if (e == Find(e)) {
			root[i] = e;
			i++;
		}
	}

	// connected component vertex ���� ����
	for (e = 0; e < g->n_vertex; e++) {
		for (i = 0; i < cnt; i++) {
			if (root[i] == Find(e)) {
				result[i].n_vertex++;
				break;
			}
		}
	}

	// MST total weight ����
	for (i = 0; i < g->n_edge; i++) {
		Edge eg = g->edge[i];

		int x = Find(eg.vertex1);
		int y = Find(eg.vertex2);

		if (x == y && eg.flag == 1) {
			for (k = 0; k < cnt; k++) {
				if (root[k] == Find(x)) {
					result[k].n_edge += eg.weight;
					break;
				}
			}
		}
	}

	end1 = clock();
	// ��� ���
	fprintf(fp, "%d\n", cnt);
	for (i = 0; i < cnt; i++) {
		fprintf(fp, "%d %lld\n", result[i].n_vertex, result[i].n_edge);
	}
	printf("Total Time is %.3fs\n", (double)(end1 - start) / CLOCKS_PER_SEC);
	printf("Sorting Time is %.3fs\n", (double)(end2 - start) / CLOCKS_PER_SEC);

	// �޸� ����
	free(root);
	free(result);
}