# Shortest Paths in Graphs
- Unweighted Graph: BFS (for both directed and undirected graph)
- Weighted Graph, positive weights only: Dijkstra
- Weighted Graph, negative weights allowed: Bellman-Ford
- Shorted path between all possible pairs: Floyd-Warshall


| Problem Type                         | Graph Constraints                                          | Algorithm                            | Time Complexity      | Space Complexity | Notes                               |
| ------------------------------------ | ---------------------------------------------------------- | ------------------------------------ | -------------------- | ---------------- | ----------------------------------- |
| **Shortest Path**                    | Unweighted                                                 | **BFS**                              | **O(V + E)**         | **O(V)**         | Finds path with fewest edges        |
| **Shortest Path**                    | Weighted (positive weights only)                           | **Dijkstra (binary heap)**           | **O((V + E) log V)** | **O(V + E)**     | Most common shortest path algorithm |
| **Shortest Path**                    | Weighted (positive weights only)                           | **Dijkstra (Fibonacci heap)**        | **O(E + V log V)**   | **O(V + E)**     | Better theoretical bound            |
| **Shortest Path**                    | Weighted, can have **negative edges** (no negative cycles) | **Bellman–Ford**                     | **O(V × E)**         | **O(V)**         | Detects negative cycles             |
| **Shortest Path (multiple sources)** | DAG (acyclic graph)                                        | **Shortest Path in DAG (Topo + DP)** | **O(V + E)**         | **O(V)**         | Fastest when graph is a DAG         |
| **Shortest Path (all pairs)**        | Any                                                        | **Floyd–Warshall**                   | **O(V³)**            | **O(V²)**        | Answers all-pairs shortest path     |
| **Shortest Path (tree)**             | Tree (no cycles)                                           | **DFS or BFS**                       | **O(V)**             | **O(V)**         | Only one path between nodes         |


\
\

# Longest Paths in Graphs

| Problem Type     | Graph Constraints                           | Algorithm                           | Time Complexity | Space Complexity | Notes                        |
| ---------------- | ------------------------------------------- | ----------------------------------- | --------------- | ---------------- | ---------------------------- |
| **Longest Path** | **DAG only** (like course prerequisites)    | **Longest Path in DAG (Topo + DP)** | **O(V + E)**    | **O(V)**         | ONLY feasible in DAGs        |
| **Longest Path** | General directed graph (may contain cycles) | **NP-Hard**                         | —               | —                | No polynomial-time algorithm |
| **Longest Path** | Tree                                        | **DFS**                             | **O(V)**        | **O(V)**         | Same as tree diameter        |
