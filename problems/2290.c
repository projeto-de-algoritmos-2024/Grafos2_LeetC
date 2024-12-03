/**
 * You are given a 0-indexed 2D integer array grid of size m x n. Each cell has one of two values:
 * 0 represents an empty cell,
 * 1 represents an obstacle that may be removed. 
 * You can move up, down, left, or right from and to an empty cell.
 * 
 * Return the minimum number of obstacles to remove so you can move from
 * the upper left corner (0, 0) to the lower right corner (m - 1, n - 1).
 * 
 * Difficulty: Hard
 */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct {
  int x,y;
} point;

typedef struct {
  int cost;
  point to, from;
} node;

typedef struct {
  node *nodes;
  int n, len;
} heap;

void swap(node *a, node *b){
  node aux = *a;
  *a = *b;
  *b = aux;
}

heap *init(int len){
  heap *h = (heap *) malloc(sizeof(heap));
  h->nodes = (node *) malloc(len * sizeof(node));
  h->n = 0;
  h->len = len;
  return h;
}

void shift_up(heap *h){
  int k = h->n-1;
  int pai = (k-1)/2;
  while (k > 0 && h->nodes[pai].cost > h->nodes[k].cost){
      swap(&h->nodes[pai], &h->nodes[k]);
      k = pai;
      pai = (k-1)/2;
  }
}

void insert(heap *h, int cost, point to, point from){
  if (h->n+1 >= h->len){
      h->len *= 2;
      h->nodes = (node *) realloc(h->nodes, h->len*sizeof(node));
  }
  h->nodes[h->n].from = from;
  h->nodes[h->n].to = to;
  h->nodes[h->n].cost = cost;

  h->n++;
  shift_up(h);
}

int minor(heap *h, int k, int l, int r, int *m){
  int value = h->nodes[k].cost;
  if (l < h->n){
    if (h->nodes[l].cost < value){
      value = h->nodes[l].cost;
      *m = l;
    }
    if (r < h->n && h->nodes[r].cost < value){
      value = h->nodes[r].cost;
      *m = r;
    }
  }
  return value;
}

void heapfy(heap *h){
  int k = 0;
  int l = 2*k+1;
  int r = 2*k+2;
  int m;
  while (l < h->n && h->nodes[k].cost > minor(h, k, l, r, &m)){
      swap(&h->nodes[k], &h->nodes[m]);
      k = m;
      l = 2*k+1;
      r = 2*k+2;
  }
}

node remove_root(heap *h){
  h->n--;
  node aux = h->nodes[0];
  h->nodes[0] = h->nodes[h->n];
  heapfy(h);
  return aux;
}

int empty(heap *h){
  return h->n == 0;
}

int minimumObstacles(int** grid, int gridSize, int* gridColSize) {
    int visited[gridSize][gridColSize[0]];
    for (int i = 0; i < gridSize; i++) {
        memset(visited[i], 0, gridColSize[0] * sizeof(int));
    }
    heap *h = init(gridSize*gridColSize[0]);
    // int obstacles = 0;
    insert(h, 0, (point){0,0}, (point){0,0});
    while (!empty(h)){
        node n = remove_root(h);
        int nx = n.to.x, ny = n.to.y;
        if (nx == gridColSize[0] - 1 && ny == gridSize - 1) {
            free(h->nodes);
            free(h);
            return n.cost;
        }
        visited[ny][nx] = 1;
        // obstacles += n.cost;
        if (nx + 1 < gridColSize[0]){
            if (!visited[ny][nx+1]){
                int cost = grid[ny][nx+1];
                point p = {ny, nx+1};
                insert(h, n.cost + cost, p, n.to);
            }
        }
        if (nx - 1 >= 0){
            if (!visited[ny][nx-1]){
                int cost = grid[ny][nx-1];
                point p = {ny, nx-1};
                insert(h, n.cost + cost, p, n.to);
            }
        }
        if (ny + 1 < gridSize){
            if (!visited[ny+1][nx]){
                int cost = grid[ny+1][nx];
                point p = {ny+1, nx};
                insert(h, n.cost + cost, p, n.to);
            }
        }
        if (ny - 1 >= 0){
            if (!visited[ny-1][nx]){
                int cost = grid[ny-1][nx];
                point p = {ny-1, nx};
                insert(h, n.cost + cost, p, n.to);
            }
        }
    }
    return -1;
}