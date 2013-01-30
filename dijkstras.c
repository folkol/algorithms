#include "algorithms.h"

char** adjacency_matrix;
int num_nodes;
int num_edges;
int start_node;
int end_node;

// Input: num_nodes num_edges start_node end_node numedges*{node_a node_b}
void read_graph() {
  scanf("%d", &num_nodes);
  adjacency_matrix = (char**) calloc(num_nodes, sizeof(char*));
  for(int c = 0; c < num_nodes; c++) {
    adjacency_matrix[c] = (char*) calloc(num_nodes, sizeof(char));
  }

  scanf("%d", &num_edges);
  scanf("%d", &start_node);
  scanf("%d", &end_node);

  int a, b;
  for(int c = 0; c < num_edges; c++) {
    scanf("%d", &a);
    scanf("%d", &b);
    printf("Setting edge for a: %d and b: %d\n", a, b);
    adjacency_matrix[a][b] = 1;
    adjacency_matrix[b][a] = 1;
  }
}

void print_graph() {
  printf("Printing adjacency matrix with size: %d\n", num_nodes);
  for(int i = 0; i < num_nodes; i++) {
    for(int j = 0; j < num_nodes; j++) {
      printf("%c", adjacency_matrix[i][j] + '0');
    } 
    printf("\n");
  }
}

int main(int argc, char** argv) {
  read_graph();
  print_graph();
}
