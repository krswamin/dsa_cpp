# Passing the Graph as Input: Memory Safety and Efficiency considerations

Key Ideas to Remember: 
- 1) Classes usually own their own data, so copying is common and expected.

## OPTION 1: SIMPLEST NAIVE EXAMPLE: 2 DEEP COPIES
```
class UGraph {
private:
    unordered_map<int, unordered_set<int>> graph;
public:
    UGraph(const unordered_map<int, unordered_set<int>> graph_input)
        : graph(graph_input) {};
};

int main() {
  unordered_map<int, unordered_set<int>> map = {
      {0, {1, 3, 5}},    {1, {0, 2, 3, 4, 6}}, {2, {1, 4, 7}},
      {3, {0, 1, 5, 6}}, {4, {1, 2, 6}},       {5, {0, 3, 6}},
      {6, {3, 4, 5, 7}}, {7, {2, 6}},          {18, {19}},
      {19, {18}}};
  UGraph g(map);
}
```

🎯 **TLDR:**
- PROS: Memory safe and correct. 
- CONS: Unnecessarily expensive because 2 deep copes

🎯 **DETAILS: ** \
Note : All copies are deep copies. 
- **map creation in main:** map variable is created in main and lives as long as main exists
- **parameter passing:** map is copied into graph_input : map is "passed by value" to the constructor. This is the first copy (deep copy). For large graphs this copy is unncessarily memory expensive
- **member initialization:** graph_input is again copied into g.graph member variable: this is the second copy (deep copy) and is memory expensive

🎯 **DEEP COPIES- WHAT GETS DEEP COPIED (IN THIS CASE)?** \
Entire container structure is duplicated, but note that the contents are still just ints (trivial types), so there’s nothing deeper beneath them
- ✅ **Structure of the unordered_map:** A new hash table is allocated, with its own buckets.
- ✅ **Each unordered_set<int>**
   - For every adjacency list, a new separate unordered_set is created.
   - All integers inside are copied (they’re just simple values).
- ✅ All ints: copied normally (very cheap).
- 🚫 There is no deeper pointer-based structure , in this case, inside the ints, so there's no "recursive deep copy" beyond containers.



📌 **SUMMARY** 

| Aspect                          | Deep Copy?          | Notes                        |
| ------------------------------- | ------------------- | ---------------------------- |
| `unordered_map` structure       | ✅ Yes               | New table allocated          |
| Each `unordered_set<int>`       | ✅ Yes               | New sets allocated           |
| Integers inside                 | ⚠️ Trivially copied | They're value types          |
| Any pointers or dynamic objects | ❌ None here         | Nothing further to deep-copy |


## OPTION 2: ROBUST & SIMPLE: 1 DEEP COPY
```
class UGraph {
private:
    unordered_map<int, unordered_set<int>> graph;
public:
    UGraph(const unordered_map<int, unordered_set<int>> &graph_input)
        : graph(graph_input) {};
};

int main() {
  unordered_map<int, unordered_set<int>> map = {
      {0, {1, 3, 5}},    {1, {0, 2, 3, 4, 6}}, {2, {1, 4, 7}},
      {3, {0, 1, 5, 6}}, {4, {1, 2, 6}},       {5, {0, 3, 6}},
      {6, {3, 4, 5, 7}}, {7, {2, 6}},          {18, {19}},
      {19, {18}}};
  UGraph g(map);
}
```

🎯 **TLDR:**
- PROS: 
    - Memory safe and correct. 
    - Only 1 deep copy inside the class constructor
- CONS: 

🎯 **DETAILS: ** \
Note : All copies are deep copies. 
- **map creation in main:** map variable is created in main and lives as long as main exists
- **parameter passing:** map is NOT copied into graph_input : map is "passed by reference" to the constructor. map and graph_input are the same
- **member initialization:** graph_input is copied into g.graph member variable: this is the only copy (deep copy) . Could be memory expensive for large graphs

- ✅ **Safety (Low Error-Proneness): GOOD**
  - No aliasing between caller’s map and internal graph
  - No lifetime issues
  - No use-after-move issues
  - No shared ownership confusion
 
- ✅ **Mutability: Controlled and internal**
  - Only your class can modify the graph
  - The caller(main) cannot affect graph after construction

- ✅**Performance: predictable**
  - One deep copy
  - No accidental or double copies like before
  - No move semantics pitfalls


## OPTION 3: ROBUST & SIMPLE, EVEN BETTER IMMUTABLE GRAPH: 1 DEEP COPY
```
class UGraph {
private:
    unordered_map<int, unordered_set<int>> const graph;
public:
    UGraph(const unordered_map<int, unordered_set<int>> &graph_input)
        : graph(graph_input) {};
};

int main() {
  unordered_map<int, unordered_set<int>> map = {
      {0, {1, 3, 5}},    {1, {0, 2, 3, 4, 6}}, {2, {1, 4, 7}},
      {3, {0, 1, 5, 6}}, {4, {1, 2, 6}},       {5, {0, 3, 6}},
      {6, {3, 4, 5, 7}}, {7, {2, 6}},          {18, {19}},
      {19, {18}}};
  UGraph g(map);
}
```

