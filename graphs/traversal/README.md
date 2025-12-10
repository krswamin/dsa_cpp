# Undirected Graph BFS
### High Level Summary
There are a few approaches explained here. They have been implemented in undirected_graph_bfs.cpp . Not all approaches are standard. Nevertheless, they are the steps / the iterations which I experimented and implemented until I reached the more standard solution
- Approach 1: bfs_with_status_map. Space O(V), Time O(V^2 + E)
- Approach 2: bfs_with_colored_sets
- Approach 3: bfs_standard : Jump directly to this section for the standard implementation with only one set. 

## Approach 1: bfs_with_status_map
- This uses an unordered_map to track the status of each node 
- Space Complexity : O(V)
- Time Complexity : O(V^2 + E)

Cons:
- The standard BFS Time Complexity is O(V +E), but this could add a time complexity of O(V*V + E) when there are a lot of disconnected nodes.
- The use of unordered_map is a non standard approach. Searching through this is what introduces O(V^2)
- The enum might be good in textbooks, but noisy for production.

### Space Complexity
Total Space Complexity = 3V ~ O(V). \
Uses 3 datastructures + 1 enum
- i)   queue  : bfs_q - V
- ii)  vector : order - V
- iii) unordered_map : status - V (overhead of unordered map ignored)
- iv) There is an enum for the 3 visited states. \


### Time Complexity
Total Time Complexity = 3V ~ O(V) \ 

i) Inititalise the unordered_map:status : O(V) \
```
  for (auto x : graph) {
    status.insert({x.first, State::UNVISITED});
  }
```

ii) core bfs logic: bfs enqueue and dequeue: This O(V+E) 
```
    while (bfs_q.size() != 0) {
      current = bfs_q.front();
      bfs_q.pop();
      order.push_back(current);
      status[current] = State::VISITED;
      auto &neighbors = graph[current];
      for (int neighbor : neighbors) {
        if (status[neighbor] == State::UNVISITED) {
          bfs_q.push(neighbor);
          status[neighbor] = State::LANDED;
        }
      }
    }
```
You add every node to the queue, But you will visit the nodes based on the number of edges . I mean the graph is not a minimum spanning tree, every edge path is examined twice, once per each connected node in an undirected graph. (in a directed graph this would just be only E) \
High level 2V for push, pop. 2E for visiting each edge twice = 2V + 2E ~ O(V+E) \
If you want the greater details. 
- bfs_q.front()	= V
- bfs_q.pop()	= V
- bfs_q.push(neighbor)	≤ V (each node pushed once)
- order.push_back(current)	= V
- status[current] = VISITED	= V
- status[neighbor] = LANDED	≤ V (each node updated once)
- status[neighbor] == UNVISITED	2E (This is the line that visits the edges twice)
Total≈4V+2E+2V=6V+2E = O(V+E) 


iii) Locating the next disconnected node: Worst Case O(V^2)

```
   // Find the next unvisited node
    unvisited_nodes_exist = false;
    for (auto &x : status) {
      if (x.second == State::UNVISITED) {
        start_node = x.first;
        unvisited_nodes_exist = true;
        break;
      }
    }
```
This is the non standard implementation. This extra global scan is what pushes it from O(V) to O(V²) in the worst case.
- Best Case Scenario -If all nodes were connected, you would have to pass through every node once to ensure they are visited = V
- Worst Case Scenario: If all nodes are disconnected, you would pass through this list every single time to ensure all nodes are visited = V*V  = O(V^2) 


This is why the cleaner BFS version (in single set implementation)
```
for (auto& node : graph)
  if (!visited[node]) bfs(node);
```
is strictly better — it avoids repeated full scans.


## Approach 2: bfs_with_colored_sets
- This uses 3 unordered_sets to track the status of each node : white, grey and black. 
- Despite the use of 3 sets the time complexity is much better than Approach 1 even in the worst case scenario of when all nodes are disconnected 
- Space Complexity : O(V)
- Time Complexity : O(V + E)


Cons:
- Using 3 unordered_sets, when you could achieve it with 1 is an overkill. There is a tonne of redundacy i.e the grey set is not needed. The following adds multiple hash-table operations per neighbor
```
white.find(neighbor)
white.erase(neighbor)
grey.insert(neighbor)
```
- Unless you specifically need 3 unordered_sets for the problem. Perhaps to find cycles or shortest paths (even these might not need them), stick to the standard implementation of usine 1 unordered set

Pros
- This was a good way to build sth. The right thing would be to strip this down incrementally to the standard version. Good way to understand the 3 stages unvisited, visited but not explored, explored

### Space Complexity
Total Space Complexity = 5V ~ O(V). \
Uses 3 datastructures + 1 enum
- i)   queue  : bfs_q - V
- ii)  vector : order - V
- iii) unordered_set: white - V (overhead of unordered sets ignored)
- iv)  unordered_set: grey  - V (overhead of unordered sets ignored)
- v)   unordered_set: black - V (overhead of unordered sets ignored)


### Time Complexity 

i) Create an ordered set of the nodes in the white set : O(V) \
```
  for (auto x : graph) {
    white.insert(x.first);
  }
```

ii) core bfs logic: enqueue and dequeue: This O(V+E) 
```
    while (bfs_q.size()) {
      current = bfs_q.front();
      bfs_q.pop();
      grey.erase(current);
      black.insert(current);
      order.push_back(current);
      // Check for neighbors and add them to the queue
      auto &neighbors = graph[current];
      for (auto neighbor : neighbors) {
        // If neighbor has not been visited
        if (white.find(neighbor) != white.end()) {
          // i) push it to the bfs_queue.
          // ii) move it from white to grey
          bfs_q.push(neighbor);
          white.erase(neighbor);
          grey.insert(neighbor);
        }
      }
    }
```

The following adds multiple hash-table operations per neighbor but are still in constant time per iteration
```
white.find(neighbor) : O(1) in 1 iteration, hence V*O(1) = O(V) across all vertices
white.erase(neighbor) : O(1) in 1 iteration, hence V*O(1) = O(V) across all vertices
grey.insert(neighbor) : O(1) in 1 iteration, hence V*O(1) = O(V) across all vertices
```
Despite the 3 sets, asympotitcally the core bfs logic is stil O(V+E)


iii) Locating the next disconnected node (key differentiating factor between Approach1)
```
if (white.size() != 0) {
      start_node = *white.begin();
    }
```
White is an unordered set and hence is O(1) per loop. Worst case scenario of all disconnected nodes, this would become V*O(1) = O(V) . This is why this is better than approach 1


## Approach 3: Standard BFS
Uses 1 bfs_queue, 1 traversal_order and only 1 visited_set
- Space Complexity : O(V)
- Time Complexity : O(V + E)
Question: When do you add the node to Visited(unordered_set), and when to Order(traversal order vector) \
### The short rule (memorize this)
👉 Mark a node as visited when you ENQUEUE it (push to Queue)
👉 Add a node to the traversal when you DEQUEUE it (pop from Queue)

That’s it. That rule holds for almost every BFS you’ll ever write.
Thats the shortest explanation needed for the cleanest possible solution (see code for details)
