#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>

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

int time;

int getInt (int *);
int dialog(const char **, int);
Graph *createGraph();
Vertex *createVertex();
Graph *insertVertex(int, int, int, Graph *);
Graph *D_addVertex(Graph *);
int checkId(int, Graph *);
Vertex *findVertex_byId(int, Graph *);
void insertEdge(int, int, Graph *);
Graph *D_addEdge(Graph *);
Graph *Show_Graph(Graph *);
Graph *deletedVertex(int, Graph *);
Graph *deletedEdge(int, int, Graph *);
Graph *D_deleteVertex(Graph *);
Graph *D_deleteEdge(Graph *);
void DFS_Visit(Vertex *);
Graph *DFS(Graph *);
Graph *minWay(Graph *);
Graph *minWaysEach(Graph *);
void delGraph(Graph *);

int main() {
    int rc, N = 9;
    const char *MSGs[] = {"\n0. Exit.", "1. Add a Vertex.", "2. Add an Edge.", "3. Remove the Vertex.", "4. Remove the Edge.", "5. Show Graph.", "6. Depth First Search.", "7. Minimal way from a vertex to another.", "8. Minimal ways from a vertex to others."};
    Graph *(*fptr[])(Graph *) = {NULL, D_addVertex, D_addEdge, D_deleteVertex, D_deleteEdge, Show_Graph, DFS, minWay, minWaysEach};
    Graph  *G = createGraph();
    while ((rc = dialog(MSGs, N)))
        G = fptr[rc](G);
    printf("Good Bye!\n");
    delGraph(G);
    G = NULL;
    return 0;
}

int getInt (int *a){
    int n;
    do {
        n = scanf("%d", a);
        if(n < 0)
            return 0;
        else if(n == 0){
            printf("%s", "Wrong input! Please, repeat!\n");
            scanf("%*c");
        }
    } while (n == 0);
    return 1;
}

int dialog(const char *msgs[], int N){
    const char *errmsg = "";
    int rc,i,n;
    do{
        puts(errmsg);
        errmsg = "You are wrong. Repeat, please!";
        for(i=0;i<N;++i) puts(msgs[i]);
        puts("Make your choice:-->");
        n = getInt(&rc);
        if(n==0) rc = 0;
    }while(rc<0||rc>=N);
    return rc;
}

Graph *createGraph(){
    Graph *G;
    G = malloc(sizeof(struct Graph));
    return G;
}

Vertex *createVertex(){
    Vertex *U;
    U = malloc(sizeof(struct Vertex));
    U->next = NULL;
    U->prev = NULL;
    U->pred = NULL;
    U->adjList = (Vertex **) calloc (1, sizeof (struct Vertex *));
    U->adjList[0] = NULL;
    return U;
}

Graph *D_addVertex(Graph *G){
    int n = 0, m = 0, k = 0, id = 0, coord1 = 0, coord2 = 0;
    printf("Enter id: -> ");
    n = getInt(&id);
    while(checkId(id, G) == 1){
        printf("Key doubled! Existing id entered! Please, repeat!\n");
        printf("Enter id: -> ");
        n = getInt(&id);
    }
    printf("Enter 1-coordinate: -> ");
    m = getInt(&coord1);
    printf("Enter 2-coordinate: -> ");
    k = getInt(&coord2);
    G = insertVertex(id, coord1, coord2, G);
    puts("Added!\n");
    return G;
}

Graph *insertVertex(int id, int x, int y, Graph *G){
    Vertex *V = createVertex();
    Vertex *temp = NULL;
    V->id = id;
    V->coords[0] = x;
    V->coords[1] = y;
    if(G->numVertex == 0){
        G->firstV = V;
        G->firstV->prev = NULL;
    }
    else if (G->numVertex > 0){
        temp = G->firstV;
        while(temp->next != NULL)
            temp = temp->next;
        temp->next = V;
        V->prev = temp;
    }
    temp = NULL;
    G->numVertex++;
    return G;
}

int checkId(int id, Graph *G){
    Vertex *temp = G->firstV;
    if (temp == NULL)
        return 0;
    if(id == temp->id)
        return 1;
    while(temp->next != NULL){
        temp = temp->next;
        if(id == temp->id)
            return 1;
    }
    return 0;
}

Vertex *findVertex_byId(int id, Graph *G){
    Vertex *V = G->firstV;
    if (V == NULL)
        return NULL;
    if(id == V->id)
        return V;
    while(V->next != NULL){
        V = V->next;
        if(id == V->id)
            return V;
    }
    return NULL;
}

Graph *D_addEdge(Graph *G){
    int n, m, id1, id2;
    if(G->firstV == NULL){
        printf("No added vertex!\n");
        return G;
    }
    printf("Enter 1-vertex's id: -> ");
    n = getInt(&id1);
    printf("Enter 2-vertex's id: -> ");
    m = getInt(&id2);
    while (checkId(id1, G) == 0 || checkId(id2, G) == 0){
        puts("Please, enter existing id of vertexes!\n");
        printf("Enter 1-vertex's id: -> ");
        n = getInt(&id1);
        printf("Enter 2-vertex's id: -> ");
        m = getInt(&id2);
    }
    insertEdge(id1, id2, G);
    puts("Added!\n");
    return G;
}

void insertEdge(int id1, int id2, Graph *G){
    Vertex *V = findVertex_byId(id1, G);
    Vertex *U = findVertex_byId(id2, G);
    Vertex **tempAdjList;
    int n = 0, m = 0;
    if (V->adjCount == 0){
        V->adjList[0] = U;
        V->adjCount++;
        return;
    }
    n = V->adjCount;
    tempAdjList = (Vertex **) calloc ((n+1), sizeof (struct Vertex *));
    for(int i = 0; i < n; ++i)
        tempAdjList[i] = V->adjList[i];
    tempAdjList[n] = U;
    V->adjList = tempAdjList;
    V->adjCount++;
}

Graph *D_deleteVertex(Graph *G){
    int n, id;
    if(G->firstV == NULL){
        printf("No added vertex to delete!\n");
        return G;
    }
    printf("Enter id to delete: -> ");
    n = getInt(&id);
    while (checkId(id, G) == 0){
        printf("ID not found! Please, repeat!\n");
        printf("Enter id: -> ");
        n = getInt(&id);
    }
    G = deletedVertex(id, G);
    puts("Deleted!\n");
    return G;
}

Graph *deletedVertex(int id, Graph *G){
    Vertex *temp = findVertex_byId(id, G);
    if(G->numVertex == 1){
        G = (Graph *) calloc (1, sizeof (Graph));
        free(temp);
        temp = NULL;
        return G;
    }
    if(temp->prev == NULL){
        free(temp->adjList);
        temp->adjList = NULL;
        temp->adjCount = 0;
        G->firstV = temp->next;
        temp->next->prev = NULL;
        free(temp);
        temp = NULL;
    }else if (temp->next == NULL){
        free(temp->adjList);
        temp->adjList = NULL;
        temp->adjCount = 0;
        temp->prev->next = NULL;
        free(temp);
        temp = NULL;
    }else {
        free(temp->adjList);
        temp->adjList = NULL;
        temp->adjCount = 0;
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        free(temp);
        temp = NULL;
    }
    G->numVertex--;
    return G;
}

Graph *D_deleteEdge(Graph *G){
    int n, k, id1, id2;
    Vertex *temp1 = NULL;
    if(G->firstV == NULL){
        printf("No added vertex to delete!\n");
        return G;
    }
    printf("Enter 1-id: -> ");
    n = getInt(&id1);
    while (checkId(id1, G) == 0){
        printf("ID not found! Please, repeat!\n");
        printf("Enter 1-id: -> ");
        n = getInt(&id1);
    }
    temp1 = findVertex_byId(id1, G);
    if(temp1->adjCount == 0){
        printf("No edges!\n");
        temp1 = NULL;
        return G;
    }
    printf("Enter 2-id: -> ");
    k = getInt(&id2);
    while (checkId(id2, G) == 0){
        printf("ID not found! Please, repeat!\n");
        printf("Enter 2-id: -> ");
        k = getInt(&id2);
    }
    G = deletedEdge(id1, id2, G);
    puts("Deleted!\n");
    return G;

}

Graph *deletedEdge(int id1, int id2, Graph *G){
    Vertex *temp1 = findVertex_byId(id1, G);
    Vertex *temp2 = NULL;
    bool deleted = false;
    int n = temp1->adjCount;
    int m = 0;
    for(int i = 0; i < n; ++i){
        if(temp1->adjList[i]->id == id2){
            deleted = true;
            break;
        }
        m++;
    }
    if(deleted == true){
        temp1->adjCount--;
        temp2 = temp1;
        for(int j = 0; j < m; ++j)
            temp1->adjList[j] = temp2->adjList[j];
        for(int i = m; i < temp2->adjCount; ++i)
            temp1->adjList[i] = temp2->adjList[i+1];
    }
    return G;
}

Graph *DFS(Graph *G){
    Vertex *U = G->firstV;
    int n, k, id1, id2;
    printf("Enter ids to know length of way from first to second:\n");
    printf("Enter 1-id: -> ");
    n = getInt(&id1);
    while (checkId(id1, G) == 0){
        printf("ID not found! Please, repeat!\n");
        printf("Enter 1-id: -> ");
        n = getInt(&id1);
    }
    printf("Enter 2-id: -> ");
    k = getInt(&id2);
    while (checkId(id2, G) == 0){
        printf("ID not found! Please, repeat!\n");
        printf("Enter 2-id: -> ");
        k = getInt(&id2);
    }
    time = 0;
    for (int j = 0; j < G->numVertex; ++j){
        if(U->color == WHITE)
            DFS_Visit(U);
        printf("\n");
        U = U->next;
    }
    time = 0;
    return G;
}

void DFS_Visit(Vertex *V){
    V->color = GREY;
    time++;
    V->d = time;
    for(int i = 0; i < V->adjCount; ++i){
        if(V->adjList[i]->color == WHITE){
            V->adjList[i]->pred = V;
            DFS_Visit(V->adjList[i]);
        }
    }
    printf("%d ", V->id);
    V->color = BLACK;
    time++;
    V->f = time;
}

Graph *Show_Graph(Graph *G){
    Vertex *temp1 = G->firstV;
    Vertex *temp2 = NULL;
    int n = 0;
    if (temp1 == NULL){
        printf("No added vertex!\n");
        return G;
    }
    while(temp1 != NULL){
        printf("%d. ( %d, %d )", temp1->id, temp1->coords[0], temp1->coords[1]);
        temp2 = temp1;
        n = temp2->adjCount;
        for(int i = 0; i < n; ++i){
            if (temp2->adjList[i]->id != 0)
                printf(" --> %d", temp2->adjList[i]->id);
        }
        temp1 = temp1->next;
        printf("\n");
    }
    return G;
}

void delGraph(Graph *G){
    G->numVertex = 0;
    free(G->firstV);
}

Graph *minWay(Graph *G){}
Graph *minWaysEach(Graph *G){}

