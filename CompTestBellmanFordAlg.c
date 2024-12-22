// Complexity BellmanFordAlg Test
// Compile it:
// gcc -o CompTestBellmanFordAlg CompTestBellmanFordAlg.c Graph.c GraphBellmanFordAlg.c instrumentation.c SortedList.c IntegersStack.c -I.

#include <assert.h>
#include <stdio.h>
#include "Graph.h"
#include "GraphBellmanFordAlg.h"
#include "instrumentation.h"

void test_graph(Graph* graph, unsigned int numVertices) {
  for (unsigned int i = 0; i < numVertices; i++) {
    InstrReset();
    printf("Shortest path tree rooted at %u:\n", i);
    GraphBellmanFordAlg* BF_result = GraphBellmanFordAlgExecute(graph, i);
    InstrPrint();
    GraphBellmanFordAlgDestroy(&BF_result);
  }
}

int main(void) {
  // Initialize instrumentation
  InstrName[0] = "memops";
  InstrName[1] = "adds";
  InstrCalibrate();

  // Test dig01
  Graph* dig01 = GraphCreate(6, 1, 0);
  GraphAddEdge(dig01, 1, 2);
  GraphAddEdge(dig01, 1, 4);
  GraphAddEdge(dig01, 3, 4);
  printf("Testing dig01:\n");
  test_graph(dig01, 6);
  GraphDestroy(&dig01);

  // Test g01
  Graph* g01 = GraphCreate(6, 0, 0);
  GraphAddEdge(g01, 0, 5);
  GraphAddEdge(g01, 2, 4);
  GraphAddEdge(g01, 2, 3);
  GraphAddEdge(g01, 1, 2);
  GraphAddEdge(g01, 0, 1);
  GraphAddEdge(g01, 3, 4);
  GraphAddEdge(g01, 3, 5);
  GraphAddEdge(g01, 0, 2);
  printf("Testing g01:\n");
  test_graph(g01, 6);
  GraphDestroy(&g01);

  // Test dig03 from file
  FILE* file = fopen("DG_2.txt", "r");
  Graph* dig03 = GraphFromFile(file);
  fclose(file);
  printf("Testing dig03:\n");
  test_graph(dig03, GraphGetNumVertices(dig03));
  GraphDestroy(&dig03);

  return 0;
}