# Data Structures & Algorithms in Kaynat++

Complete guide to built-in data structures and algorithms.

## Table of Contents

1. [Stack](#stack)
2. [Queue](#queue)
3. [Linked List](#linked-list)
4. [Binary Search Tree](#binary-search-tree)
5. [Graph](#graph)
6. [Heap](#heap)
7. [Hash Map](#hash-map)
8. [Trie](#trie)
9. [Sorting Algorithms](#sorting-algorithms)
10. [Searching Algorithms](#searching-algorithms)
11. [Graph Algorithms](#graph-algorithms)

---

## Stack

A Last-In-First-Out (LIFO) data structure.

### Operations

```kaynat
note. create a stack.
create a stack called history.

note. push elements.
push page one onto history.
push page two onto history.
push page three onto history.

note. pop element.
pop from history and store as last_page.
say last_page.  note. outputs: page three.

note. peek at top.
peek at history and store as top.
say top.  note. outputs: page two.

note. check if empty.
check if history is empty.

note. get size.
find the size of history and store as count.
say count.
```

### Example: Undo System

```kaynat
create a stack called undo_stack.

push action one onto undo_stack.
push action two onto undo_stack.
push action three onto undo_stack.

note. undo last action.
pop from undo_stack and store as last_action.
say undoing, last_action.
```

---

## Queue

A First-In-First-Out (FIFO) data structure.

### Operations

```kaynat
note. create a queue.
create a queue called requests.

note. enqueue elements.
enqueue task one into requests.
enqueue task two into requests.
enqueue task three into requests.

note. dequeue element.
dequeue from requests and store as next_task.
say next_task.  note. outputs: task one.

note. peek at front.
peek at the front of requests and store as front.
say front.  note. outputs: task two.

note. check if empty.
check if requests is empty.

note. get size.
find the size of requests and store as count.
```

### Example: Task Queue

```kaynat
create a queue called task_queue.

enqueue process order into task_queue.
enqueue send email into task_queue.
enqueue update database into task_queue.

while task_queue is not empty.
    dequeue from task_queue and store as task.
    say processing, task.
end.
```

---

## Linked List

A linear data structure with nodes.

### Operations

```kaynat
note. create a linked list.
create a linked list called chain.

note. add nodes.
add node with value 10 to chain.
add node with value 20 to chain.
add node with value 30 to chain.

note. insert at position.
insert node with value 15 at position 1 in chain.

note. remove node.
remove node with value 20 from chain.

note. reverse list.
reverse chain.

note. get length.
find the length of chain and store as len.

note. convert to list.
convert chain to list and store as values.
say values.
```

---

## Binary Search Tree

A tree structure for efficient searching.

### Operations

```kaynat
note. create a BST.
create a binary search tree called bst.

note. insert values.
insert 50 into bst.
insert 30 into bst.
insert 70 into bst.
insert 20 into bst.
insert 40 into bst.

note. search for value.
search for 30 in bst and store as found.
if found is true then.
    say value found.
end.

note. traverse inorder (sorted).
traverse bst inorder and store as sorted_values.
say sorted_values.

note. traverse preorder.
traverse bst preorder and store as preorder_values.

note. traverse postorder.
traverse bst postorder and store as postorder_values.

note. find height.
find the height of bst and store as h.

note. find minimum.
find the minimum in bst and store as min.

note. find maximum.
find the maximum in bst and store as max.

note. delete value.
delete 30 from bst.
```

---

## Graph

A structure of nodes and edges.

### Operations

```kaynat
note. create a graph.
create a graph called network.

note. add nodes.
add node city a to network.
add node city b to network.
add node city c to network.

note. add edges.
add edge from city a to city b with weight 10 in network.
add edge from city b to city c with weight 20 in network.
add edge from city a to city c with weight 30 in network.

note. find shortest path.
find the shortest path from city a to city c in network using dijkstra and store as path.
say path.

note. traverse breadth first.
traverse network from city a using breadth first and store as visited.
say visited.

note. traverse depth first.
traverse network from city a using depth first and store as visited.

note. check for cycle.
check if network has a cycle and store as has_cycle.

note. find connected components.
find all connected components in network and store as components.
```

---

## Heap

A tree-based structure for priority queues.

### Operations

```kaynat
note. create a min heap.
create a min heap called task_heap.

note. insert elements.
insert 5 into task_heap.
insert 3 into task_heap.
insert 7 into task_heap.
insert 1 into task_heap.

note. extract minimum.
extract minimum from task_heap and store as min.
say min.  note. outputs: 1.

note. create a max heap.
create a max heap called score_heap.

insert 10 into score_heap.
insert 20 into score_heap.
insert 15 into score_heap.

note. extract maximum.
extract maximum from score_heap and store as max.
say max.  note. outputs: 20.
```

---

## Hash Map

A key-value data structure.

### Operations

```kaynat
note. create a hash map.
create a hash map called index.

note. put key-value pairs.
put key hello with value greeting into index.
put key goodbye with value farewell into index.

note. get value by key.
get key hello from index and store as word_type.
say word_type.  note. outputs: greeting.

note. remove key.
remove key goodbye from index.

note. check if key exists.
check if key hello exists in index and store as exists.

note. get load factor.
find the load factor of index and store as load.
```

---

## Trie

A tree for storing strings.

### Operations

```kaynat
note. create a trie.
create a trie called dictionary.

note. insert words.
insert word hello into dictionary.
insert word help into dictionary.
insert word world into dictionary.

note. search for word.
search for word hello in dictionary and store as found.

note. find words with prefix.
find all words starting with hel in dictionary and store as suggestions.
say suggestions.  note. outputs: hello, help.

note. delete word.
delete word help from dictionary.
```

---

## Sorting Algorithms

### Bubble Sort

```kaynat
set numbers to a list containing 5, 2, 8, 1, 9.
sort numbers using bubble sort and store as sorted.
say sorted.
```

### Merge Sort

```kaynat
set numbers to a list containing 5, 2, 8, 1, 9.
sort numbers using merge sort and store as sorted.
say sorted.
```

### Quick Sort

```kaynat
set numbers to a list containing 5, 2, 8, 1, 9.
sort numbers using quick sort and store as sorted.
say sorted.
```

### Other Sorting Algorithms

```kaynat
sort numbers using insertion sort and store as sorted.
sort numbers using selection sort and store as sorted.
sort numbers using heap sort and store as sorted.
sort numbers using radix sort and store as sorted.
sort numbers using counting sort and store as sorted.
```

---

## Searching Algorithms

### Linear Search

```kaynat
set numbers to a list containing 5, 2, 8, 1, 9.
search for 8 in numbers using linear search and store as index.
say found at index, index.
```

### Binary Search

```kaynat
set sorted_numbers to a list containing 1, 2, 5, 8, 9.
search for 5 in sorted_numbers using binary search and store as index.
say found at index, index.
```

### Pattern Matching (KMP)

```kaynat
set text to hello world.
set pattern to world.
search for pattern pattern in text using knuth morris pratt and store as positions.
say positions.
```

---

## Graph Algorithms

### Dijkstra's Shortest Path

```kaynat
create a graph called g.
add node a to g.
add node b to g.
add node c to g.
add edge from a to b with weight 4 in g.
add edge from b to c with weight 3 in g.
add edge from a to c with weight 10 in g.

find shortest path from a to c in g using dijkstra and store as path.
say path.
```

### Bellman-Ford

```kaynat
find shortest path from a to c in g using bellman ford and store as path.
```

### Minimum Spanning Tree (Kruskal)

```kaynat
find minimum spanning tree of g using kruskal and store as tree.
```

### Minimum Spanning Tree (Prim)

```kaynat
find minimum spanning tree of g using prim and store as tree.
```

### Topological Sort

```kaynat
perform topological sort on g and store as order.
```

### Strongly Connected Components

```kaynat
find all strongly connected components in g using kosaraju and store as components.
```

---

## Time Complexity Reference

| Operation | Stack | Queue | Linked List | BST (avg) | Hash Map (avg) |
|-----------|-------|-------|-------------|-----------|----------------|
| Insert | O(1) | O(1) | O(1) | O(log n) | O(1) |
| Delete | O(1) | O(1) | O(n) | O(log n) | O(1) |
| Search | O(n) | O(n) | O(n) | O(log n) | O(1) |
| Access | O(n) | O(n) | O(n) | O(log n) | O(1) |

| Sorting Algorithm | Time (avg) | Time (worst) | Space |
|-------------------|------------|--------------|-------|
| Bubble Sort | O(n²) | O(n²) | O(1) |
| Merge Sort | O(n log n) | O(n log n) | O(n) |
| Quick Sort | O(n log n) | O(n²) | O(log n) |
| Heap Sort | O(n log n) | O(n log n) | O(1) |

---

All DSA operations shown here will work in Kaynat++ once fully implemented.
