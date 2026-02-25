# DSA Usage Guide

Practical examples of using data structures and algorithms.

## Stack Example: Browser History

```kaynat
begin program.

create a stack called history.

note. visit pages.
push home page onto history.
push about page onto history.
push contact page onto history.

say current page is contact page.

note. go back.
pop from history and store as current.
peek at history and store as previous.
say went back to, previous.

note. go back again.
pop from history and store as current.
peek at history and store as previous.
say went back to, previous.

end program.
```

## Queue Example: Print Queue

```kaynat
begin program.

create a queue called print_queue.

note. add print jobs.
enqueue document1.pdf into print_queue.
enqueue document2.pdf into print_queue.
enqueue document3.pdf into print_queue.

note. process print jobs.
while print_queue is not empty.
    dequeue from print_queue and store as job.
    say printing, job.
end.

say all jobs printed.

end program.
```

## Binary Search Tree Example

```kaynat
begin program.

create a binary search tree called bst.

note. insert values.
insert 50 into bst.
insert 30 into bst.
insert 70 into bst.
insert 20 into bst.
insert 40 into bst.
insert 60 into bst.
insert 80 into bst.

note. search for value.
search for 40 in bst and store as found.
if found is true then.
    say value 40 found in tree.
end.

note. get sorted values.
traverse bst inorder and store as sorted.
say sorted values, sorted.

end program.
```

## Graph Example: City Network

```kaynat
begin program.

create a graph called city_network.

note. add cities.
add node new york to city_network.
add node boston to city_network.
add node philadelphia to city_network.
add node washington to city_network.

note. add routes with distances.
add edge from new york to boston with weight 215 in city_network.
add edge from new york to philadelphia with weight 95 in city_network.
add edge from philadelphia to washington with weight 140 in city_network.
add edge from boston to philadelphia with weight 310 in city_network.

note. find shortest path.
find the shortest path from new york to washington in city_network using dijkstra and store as path.
say shortest path, path.

end program.
```

## Sorting Example

```kaynat
begin program.

set numbers to a list containing 64, 34, 25, 12, 22, 11, 90.

say original, numbers.

sort numbers using quick sort and store as sorted.
say sorted, sorted.

end program.
```

## Searching Example

```kaynat
begin program.

set numbers to a list containing 1, 3, 5, 7, 9, 11, 13, 15.

search for 7 in numbers using binary search and store as index.
if index is not equal to negative 1 then.
    say found 7 at index, index.
otherwise.
    say 7 not found.
end.

end program.
```

---

All DSA examples will work once the DSA module is fully implemented.
