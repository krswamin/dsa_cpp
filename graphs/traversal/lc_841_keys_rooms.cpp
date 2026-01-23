/*
Leet code 841. Keys and Rooms
https://leetcode.com/problems/keys-and-rooms/description/?envType=study-plan-v2&envId=leetcode-75

There are n rooms labeled from 0 to n - 1 and all the rooms are locked except
for room 0. Your goal is to visit all the rooms. However, you cannot enter a
locked room without having its key. When you visit a room, you may find a set of
distinct keys in it. Each key has a number on it, denoting which room it
unlocks, and you can take all of them with you to unlock the other rooms. Given
an array rooms where rooms[i] is the set of keys that you can obtain if you
visited room i, return true if you can visit all the rooms, or false otherwise.


Example 1:

Input: rooms = [[1],[2],[3],[]]
Output: true
Explanation:
We visit room 0 and pick up key 1.
We then visit room 1 and pick up key 2.
We then visit room 2 and pick up key 3.
We then visit room 3.
Since we were able to visit every room, we return true.


Example 2:
Input: rooms = [[1,3],[3,0,1],[2],[0]]
Output: false
Explanation: We can not enter room number 2 since the only key that unlocks it
is in that room.
*/

/*
-------------------------------------------
KSW High Level Solution
-------------------------------------------
Use Graph DFS because you need to be in a room to go to the next room

DFS/ BFS both will work to tell if you are able to visit all rooms are not.
But practically think of actually taking a key and going room to room in
somewhat minimum number of steps. (chatgpt has a problem with calling it minimum
number of steps. This problem is actually a reachability-with-state problem)
Then DFS is a better choice than BFS imo.

-------------------------------------------
Below is chatgpt's more eloquent answer.
-------------------------------------------

✅ Example: “Can I visit all rooms?”
For this YES/NO reachability question, DFS and BFS are equivalent.
Either traversal correctly determines whether every node is reachable.

✅ But for “physically walking room-to-room with minimal movement”…
This is where the distinction matters — and your intuition is correct:
✔️ BFS gives minimum number of door transitions.
   Because BFS explores in increasing distance from the start.
   BFS doesn't represent actual physical movement — it represents “minimum hop
distances in a graph.” ✔️ DFS gives some valid path, but not minimum DFS
intentionally goes as deep as possible before backtracking — this can result in
long unnecessary walks. ✔️However… the actual physical constraint of this problem
is different In the real scenario, you cannot walk to a room unless you have its
key. This makes it fundamentally not a shortest-path problem until keys are
collected. You aren’t trying to minimize steps — you’re trying to progressively
unlock the state space.

🎯 The physically accurate model is this:
You walk into a room → collect all keys → unlock new rooms → pick one to walk
into → repeat. This is closer to: ✔️ A DFS-like “decision tree” because the state
changes (new keys obtained) every time you enter a room. So you are correct in
spirit: “Practically, to walk room→room with keys, DFS matches the natural
behavior better than BFS.”
*/

#include <iostream>
#include <stack>
#include <unordered_set>
#include <vector>
using namespace std;

class Graph {
private:
  const vector<vector<int>> rooms;
  vector<int> traversal_order;

public:
  Graph(const vector<vector<int>> &rooms);
  void print_traversal_order() const;
  bool dfs();
};

Graph::Graph(const vector<vector<int>> &rooms) : rooms(rooms) {}

void Graph::print_traversal_order() const {
  cout << "\n Traversal_order:";
  for (auto x : traversal_order) {
    cout << x << ", ";
  }
}

bool Graph::dfs() {
  unordered_set<int> visited;
  stack<int> st;

  traversal_order.clear();
  int current = 0;
  st.push(0);
  visited.emplace(0);
  traversal_order.push_back(0);

  while (!st.empty()) {
    current = st.top();
    bool pop_current = true;
    for (auto child : rooms[current]) {
      if (visited.find(child) == visited.end()) {
        pop_current = false;
        st.push(child);
        visited.emplace(child);
        traversal_order.push_back(child);
        break;
      }
    }
    if (pop_current) {
      st.pop();
    }
  }

  if (visited.size() == rooms.size()) {
    return true;
  } else {
    return false;
  }
}

int main() {

  cout << "\n\n --------- Example 1----------------";
  vector<vector<int>> rooms = {{1}, {2}, {3}, {}};
  Graph g1(rooms);
  bool all_rooms_visited = g1.dfs();
  g1.print_traversal_order();
  cout << "\n all_rooms_visited :" << all_rooms_visited << "\n";

  cout << "\n\n --------- Example 2----------------";
  rooms = {{1, 3}, {3, 0, 1}, {2}, {0}};
  Graph g2(rooms);
  all_rooms_visited = g2.dfs();
  g2.print_traversal_order();
  cout << "\n all_rooms_visited :" << all_rooms_visited << "\n";
}