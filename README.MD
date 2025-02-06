# Graph Algorithms Project

This project implements various graph algorithms and provides tests to verify their correctness and performance. The project is written in C and includes the following components:

- Graph representation and manipulation
- Bellman-Ford algorithm for shortest paths
- Transitive closure computation
- Eccentricity measures computation
- All-pairs shortest distances computation
- Instrumentation for performance measurement

## File Description

- **Graph**: Implementation of related operations/representations of the graph data structure, composed of a list of vertices and, for each, its adjacent vertices list, this lits are defined using the generic type *SortedList*.
- **GraphAllPairsShortestDistances**: Implementation of the all-pairs shortest distances algorithm.
- **GraphBellmanFordAlg**: Implementation of the Bellman-Ford algorithm.
- **GraphEccentricityMeasures**: Implementation of the eccentricity measures computation.
- **GraphTransitiveClosure**: Implementation of the transitive closure computation.
- **instrumentation**: Instrumentation for performance measurement.
- **IntegersStack**: Implementation of a stack data structure for integers.
- **SortedList**: Implementation of a sorted list data structure.

There's a folder dedicated to the computacional complexity of the Bellman-Ford and Transitive Closure algorithms - **/Complexity**

Another folder includes the source code of the Project's Report in LaTeX - **/Report_PT**

## Compilation

To compile all algorithms tests programs, run:

```sh
make all
```

This will generate the following executables:

- TestAllPairsShortestDistances
- TestBellmanFordAlg
- TestCreateTranspose
- TestEccentricityMeasures
- TestTransitiveClosure

To clean all the executable just run:

```sh
make clean
```

## Authors

- Duarte Branco
- Filipe Viseu

This project was developed as part of the Algorithms and Data Structures course at the University of Aveiro.

