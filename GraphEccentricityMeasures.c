//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira - Dec 2024
//
// GraphEccentricityMeasures
//

// Student Name :
// Student Number :
// Student Name : Duarte Branco
// Student Number : 119253

/*** COMPLETE THE GraphEccentricityMeasuresCompute FUNCTION ***/
/*** COMPLETE THE GraphGetCentralVertices FUNCTION ***/
/*** COMPLETE THE GraphEccentricityMeasuresPrint FUNCTION ***/

#include "GraphEccentricityMeasures.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// INT_MAX == INF
#include <limits.h>

#include "Graph.h"
#include "GraphAllPairsShortestDistances.h"

struct _GraphEccentricityMeasures {
  unsigned int*
      centralVertices;  // centralVertices[0] = number of central vertices
                        // array size is (number of central vertices + 1)
  int* eccentricity;    // the eccentricity value of each vertex
  Graph* graph;         // the graph
  int graphRadius;      // the graph radius
  int graphDiameter;    // the graph diameter
};

// Auxiliary static functions
static int GraphComputeRadius(const GraphEccentricityMeasures* p) {
  assert(p != NULL);

  int radius = INT_MAX;
  unsigned int numVertices = GraphGetNumVertices(p->graph);

  for (unsigned int v = 0; v < numVertices; v++) {
    if (p->eccentricity[v] != -1 && p->eccentricity[v] < radius) {
      radius = p->eccentricity[v];
    }
  }

  radius = (radius == INT_MAX) ? -1 : radius;
  return radius;
}

static int GraphComputeDiameter(const GraphEccentricityMeasures* p) {
  assert(p != NULL);

  int diameter = -1;
  unsigned int numVertices = GraphGetNumVertices(p->graph);

  for (unsigned int v = 0; v < numVertices; v++) {
    if (p->eccentricity[v] != -1 && p->eccentricity[v] > diameter) {
      diameter = p->eccentricity[v];
    }
  }

  return diameter;
}

// Allocate memory
// Compute the vertex eccentricity values
// Compute graph radius and graph diameter
// Compute the set of central vertices
GraphEccentricityMeasures* GraphEccentricityMeasuresCompute(Graph* g) {
  assert(g != NULL);

  // COMPLETE THE CODE
  // CREATE AUXILIARY (static) FUNCTIONS, IF USEFUL
  // Graph radius --- the smallest vertex eccentricity value
  // Graph diameter --- the largest vertex eccentricity value
  // Do not forget that -1 represents an IDEFINITE value

  // Computing the set of central vertices
  // Allocate the central vertices array : number of central vertices + 1
  // Fill in the central vertices array

  unsigned int numVertices = GraphGetNumVertices(g);

  // Allocate memory for result
  GraphEccentricityMeasures* result = (GraphEccentricityMeasures*)malloc(sizeof(struct _GraphEccentricityMeasures));
  assert(result != NULL);

  result->graph = g;
  result->eccentricity = (int*)malloc(numVertices * sizeof(int));
  assert(result->eccentricity != NULL);

  // All-pairs shortest distances
  GraphAllPairsShortestDistances* allPairsDistances = GraphAllPairsShortestDistancesExecute(g);
  assert(allPairsDistances != NULL);

  // Eccentricity for each vertex
  for (unsigned int v = 0; v < numVertices; v++) {
    int maxDistance = -1;
    int hasPath = 0;

    for (unsigned int w = 0; w < numVertices; w++) {
      if (v == w) continue;  // Skip self
      
      int distance = GraphGetDistanceVW(allPairsDistances, v, w);
      if (distance != -1) {
        hasPath = 1;
        if (distance > maxDistance) {
          maxDistance = distance;
        }
      }
    }

    // If vertex has no paths to other vertices, set eccentricity to -1
    result->eccentricity[v] = hasPath ? maxDistance : -1;
  }

  // Compute radius and diameter
  result->graphRadius = GraphComputeRadius(result);
  result->graphDiameter = GraphComputeDiameter(result);

  // Compute the set of central vertices
  unsigned int centralCount = 0;
  for (unsigned int v = 0; v < numVertices; v++) {
    if (result->eccentricity[v] == result->graphRadius) {
      centralCount++;
    }
  }

  // Allocate memory for the central vertices array
  result->centralVertices = (unsigned int*)malloc((centralCount + 1) * sizeof(unsigned int));
  assert(result->centralVertices != NULL);

  result->centralVertices[0] = centralCount;
  unsigned int index = 1;
  for (unsigned int v = 0; v < numVertices; v++) {
    if (result->eccentricity[v] == result->graphRadius) {
      result->centralVertices[index++] = v;
    }
  }
  
  GraphAllPairsShortestDistancesDestroy(&allPairsDistances);
  return result;
}

void GraphEccentricityMeasuresDestroy(GraphEccentricityMeasures** p) {
  assert(*p != NULL);

  GraphEccentricityMeasures* aux = *p;

  free(aux->centralVertices);
  free(aux->eccentricity);

  free(*p);
  *p = NULL;
}

// Getting the computed measures

int GraphGetRadius(const GraphEccentricityMeasures* p) {
  assert(p != NULL);

  return p->graphRadius;
}

int GraphGetDiameter(const GraphEccentricityMeasures* p) {
  assert(p != NULL);

  return p->graphDiameter;
}

int GraphGetVertexEccentricity(const GraphEccentricityMeasures* p,
                               unsigned int v) {
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));
  assert(p->eccentricity != NULL);

  return p->eccentricity[v];
}

// Getting a copy of the set of central vertices
// centralVertices[0] = number of central vertices in the set
unsigned int* GraphGetCentralVertices(const GraphEccentricityMeasures* p) {
  assert(p != NULL);
  assert(p->centralVertices != NULL);

  // COMPLETE THE CODE
  unsigned int centralCount = p->centralVertices[0];
  unsigned int* centralVerticesCopy = (unsigned int*)malloc((centralCount + 1) * sizeof(unsigned int));
  assert(centralVerticesCopy != NULL);

  for (unsigned int i = 0; i <= centralCount; i++) {
    centralVerticesCopy[i] = p->centralVertices[i];
  }

  return centralVerticesCopy;
}

// Print the graph radius and diameter
// Print the vertex eccentricity values
// Print the set of central vertices
void GraphEccentricityMeasuresPrint(const GraphEccentricityMeasures* p) {
  assert(p != NULL);
  // COMPLETE THE CODE
  
  // Print the vertex eccentricity values
  printf("Graph Radius: %d\n", p->graphRadius);
  printf("Graph Diameter: %d\n", p->graphDiameter);

  // Print the vertex eccentricity values
  unsigned int numVertices = GraphGetNumVertices(p->graph);
  printf("Vertex Eccentricities:\n");
  for (unsigned int v = 0; v < numVertices; v++) {
    printf("Vertex %u: %d\n", v, p->eccentricity[v]);
  }

  // Print the set of central vertices
  printf("Central Vertices:\n");
  unsigned int centralCount = p->centralVertices[0];
  for (unsigned int i = 1; i <= centralCount; i++) {
    printf("Vertex %u\n", p->centralVertices[i]);
  }
}
