#include <stdio.h>

typedef struct Vertex {
    enum list_color{WHITE, GREY, BLACK}color;
    int id;
    int coords[2];
    int weight;
    int d;
    int f;
    int adjCount;
    struct Vertex *next;
    struct Vertex *prev;
    struct Vertex *pred;
    struct Vertex **adjList;
} Vertex;

typedef struct Graph {
    int numVertex;
    struct Vertex *firstV;
} Graph;
