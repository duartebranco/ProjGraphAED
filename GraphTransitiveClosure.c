//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira - Dec 2024
//
// GraphTransitiveClosure - Transitive Closure of a directed graph
//

// Student Name : Filipe Viseu
// Student Number : 119192
// Student Name : Duarte Branco
// Student Number : 119253

/*** COMPLETE THE GraphComputeTransitiveClosure FUNCTION ***/

#include "GraphTransitiveClosure.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "GraphBellmanFordAlg.h"
#include "instrumentation.h"

// Compute the transitive closure of a directed graph
// Return the computed transitive closure as a directed graph
// Use the Bellman-Ford algorithm
Graph* GraphComputeTransitiveClosure(Graph* g) {
  assert(g != NULL);
  assert(GraphIsDigraph(g));
  assert(GraphIsWeighted(g) == 0);

  // COMPLETE THE CODE
  unsigned int numVertices = GraphGetNumVertices(g); // Obtem o numero de vertices do grafo original
  Graph* fechoTransitivo =  GraphCreate(numVertices, 1, 0);// Cria o grafo onde o transitivo vai ser guardado

  for (unsigned int u = 0; u < numVertices; u++) { // Para cada vertice do grafo original
    GraphBellmanFordAlg* bellMan = GraphBellmanFordAlgExecute(g, u); // Executa o algoritmo de Bellman-Ford
    for (unsigned int v = 0; v < numVertices; v++) { // Para cada vertice do grafo original
      if (u != v && GraphBellmanFordAlgReached(bellMan, v)) { // Se o vertice v é alcançável a partir do vertice u (têm que ser diferentes)
        GraphAddEdge(fechoTransitivo, u, v); // Adiciona uma aresta do vertice u para o vertice v no grafo transposto
      }
    }
    GraphBellmanFordAlgDestroy(&bellMan); // Destroi a estrutura do algoritmo de Bellman-Ford
  }

  return fechoTransitivo;
}

// Complexidade:O(V^2*E)
