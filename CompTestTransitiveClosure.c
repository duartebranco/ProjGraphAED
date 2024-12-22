// Compilar: gcc -o CompTestTransitiveClosure CompTestTransitiveClosure.c Graph.c GraphTransitiveClosure.c GraphBellmanFordAlg.c instrumentation.c SortedList.c IntegersStack.c -I.

#include <assert.h>
#include <stdio.h>
#include "Graph.h"
#include "GraphTransitiveClosure.h"
#include "instrumentation.h"

void test_transitive_closure(Graph* graph) {
  InstrReset();
  Graph* closure = GraphComputeTransitiveClosure(graph);
  InstrPrint();
  
  GraphDestroy(&closure);
}

int main(void) {
    InstrName[0] = "V processados";
    InstrName[1] = "A adicionadas";
    InstrCalibrate();

    //printf("\nTesting dig01:\n");
    //Graph* dig01 = GraphCreate(6, 1, 0);
    //GraphAddEdge(dig01, 1, 2);
    //GraphAddEdge(dig01, 1, 4);
    //GraphAddEdge(dig01, 3, 4);
    //test_transitive_closure(dig01);
    //GraphDestroy(&dig01);

    //printf("\nTesting dig02 (a lot bigger):\n");
    //Graph* dig02 = GraphCreate(100, 1, 0);
    //for(unsigned int i = 0; i < 100; i++) {
    //   for (unsigned int j = 0; j < 100; j++) {
    //       if (i != j) {
    //           GraphAddEdge(dig02, i, j);
    //       }
    //    }
    //}
    //test_transitive_closure(dig02);
    //GraphDestroy(&dig02);

    for(int i = 5; i<=50; i+=5){
        Graph* dig02 = GraphCreate(i, 1, 0);
        for(unsigned int j = 0; j < i; j++) {
            for (unsigned int k = 0; k < i; k++) {
                if (j != k) {
                    GraphAddEdge(dig02, j, k);
                }
            }
        }
        printf("\nTesting dig02 with %d vertices:\n", i);
        test_transitive_closure(dig02);
        GraphDestroy(&dig02);
    }

    printf("\nTesting dig03 from file:\n");
    FILE* file = fopen("DG_2.txt", "r");
    Graph* dig03 = GraphFromFile(file);
    fclose(file);
    test_transitive_closure(dig03);
    GraphDestroy(&dig03);

    return 0;
}

// [5, 10, 15, 20, 25, 30, 35, 40, 45, 50]
// [585, 9595, 49155, 156390, 383425, 797385, 1480395, 2529580, 4057065, 6189975]
// [20, 90, 210, 380, 600, 870, 1190, 1560, 1980, 2450]