# Project 2 README

Student 1: Penny He (923759739)

Student 2: Kristina Abdullina (924726033)

## Project Status
The project is implemented and passes all 41 tests, including 20 Map tests, 18 Weighted Quick Union tests, and 2 Friend Groups tests. We added one test to Friend Groups.

The implementation uses CVectorMap to store people's names and corresponding element IDs, CWeightedQuickUnion to manage connected groups, and CFriendGroups to handle friendship operations.

The program successfully processes all four provided datasets and determines how many additional friendships are needed to connect everyone into one group.

Valgrind reported zero memory errors and no definitely, indirectly, or possibly lost memory. The final code coverage report showed 100% line coverage and 87.5% function coverage.

## Known Issues
There are currently no known functional issues with our implementation. All 41 tests pass, and the program meets the performance requirements on the provided datasets.

One minor discrepancy is that the provided medium dataset contains 3,926 connections, while the instructor's analysis table lists 3,927.

## Code References
C++ reference for std::vector: https://en.cppreference.com/w/cpp/container/vector

C++ reference for std::vector::insert: https://en.cppreference.com/w/cpp/container/vector/insert

C++ reference for std::vector::erase: https://en.cppreference.com/w/cpp/container/vector/erase

## Generative AI Use
I used ChatGPT for Prompt 1, and ZZZZZ for Prompt 2....

### Prompt 1
My implementation is significantly slower than the instructor's benchmark. How much improvement would there be if I swaped the find in Map from using linear search to using binary search?

### Response 1
Yes, Based on the benchmarks given for your Friend Groups project, switching from linear search to binary search, while also maintaining sorted keys, improved performance significantly, especially for the large dataset.
Dataset	Before	After	Improvement
1,000 people	27.77 ms	23.39 ms	15.8% faster
100,000 people	268.16 s	84.55 s	68.5% less execution time

For the large dataset, your program became approximately 3.17 times as fast.

The theoretical improvement in lookup complexity is:
- Linear search: \(O(n)\)
- Binary search: \(O(\log n)\)
However, this doesn't make the entire Map \(O(\log n)\), because inserting into a sorted vector still takes \(O(n)\)

### Changes 1 
I replaced the linear search in Find（） with binary search
std::size_t left = 0;
std::size_t right = keys.size();

while (left < right) {
    std::size_t mid = left + (right - left) / 2;

    if (key < keys[mid]) {
        right = mid;
    }
    else if (key > keys[mid]) {
        left = mid + 1;
    }
    else {
        val = values[mid];
        return true;
    }
}

return false;

additional to this I also changed the Add() aswell to insert keys in alphabetical order inorder to perform binary search 

### Prompt 2
Can you breify remind me about how to get the values in a tuple?

### Response 2
In C++, there are two main ways to access values in a tuple.
1. Using std::get<index>()
std::tuple<int, std::string, double> t{10, "Alice", 3.5};

std::get<0>(t); // 10
std::get<1>(t); // "Alice"
std::get<2>(t); // 3.5

2. Using structured binding
You can unpack all the values into separate variables:
auto [age, name, gpa] = t;

std::cout << age;  // 10
std::cout << name; // Alice
std::cout << gpa;  // 3.5

### Changes 2
    TName name1 = std::get<0>(connection);
    TName name2 = std::get<1>(connection)
c
can you remind me what should for each function perform?

### Response 2
ForEach() should visit every key-value pair in the Map and perform a given operation on each pair.

For example:
keys   = {"Alice", "Bob", "Charlie"};
values = {10, 20, 30};

The output would be:
Alice: 10
Bob: 20
Charlie: 30

What ForEach() should do
1. Iterate through every element in keys.
2. Get its corresponding element from values at the same index.
3. Call the provided function with that key and value.
4. Continue until all pairs have been visited.
Important: ForEach() does not search for one specific key, insert elements, or remove elements. Its purpose is to process every existing key-value pair.

### Changes 2
    void ForEach(typename CMap<K, V>::TEntityFunction fun) override {
        
         for(std::size_t i = 0 ; i < keys.size(); i++){
            fun(keys[i],values[i]);
         }
    }


### Prompt 4
Why does Valgrind report that ./bin/makefriends does not exist after running make clean and make tests?

### Response 4
Because make clean deletes the compiled executable, including bin/makefriends.

When you run:
make clean
make tests
Two things happen:
1. make clean removes the compiled files and executables.
2. make tests rebuilds only the test executables, not bin/makefriends.
Therefore, when Valgrind tries to execute ./bin/makefriends, the file doesn't exist.

How to fix it
First, rebuild the main executable:
make bin/makefriends
valgrind --leak-check=full --show-leak-kinds=all ./bin/makefriends -f data/friendsmed.csv

### Changes 4
I rebuilt the executable with:

make bin/makefriends

Then I ran Valgrind using the medium dataset.

valgrind --leak-check=full --show-leak-kinds=all ./bin/makefriends -f data/friendsmed.csv

Valgrind reported zero memory errors and zero definitely, indirectly, or possibly lost bytes.


### Prompt 5
After changing my Map implementation, why is the MapTest/0.DuplicateAdd test failing? 

### Response 5
Add() function was updating the stored value when an existing key was encountered.

The failing test indicated that the Map should reject duplicate keys rather than replace their associated values.

The difference between updating an existing value and adding a new key-value pair.


### Changes 5

I changed the duplicate-key condition in Add() from:

values[mid] = val;
return true;

to:

return false;

This prevented an existing key from being overwritten.

After making this change, all 20 Map tests passed.

### Prompt 6
Why does the performance of my Friend Groups implementation appear to grow approximately quadratically?

### Response 6
 Inserting an element into the middle of a vector can take O(n) time because existing elements must shift.

If a large number of people are inserted, these repeated operations can contribute O(n²) total work.

Even though binary search reduces the time needed to find an insertion position, it does not eliminate the shifting required by vector insertion.

### Changes 6

I used this explanation to understand the performance difference between my implementation and the instructor's results.

I included the vector insertion overhead as a likely explanation for the slower runtime in ANALYSIS.md.

### Prompt 7
Why does my medium dataset show 3,926 connections when the instructor's analysis table says there should be 3,927?

### Response 7
Check the CSV file directly to determine whether the difference came from my implementation or the provided dataset.

Use wc -l to count the lines in the file and head to inspect the first few entries.

If the dataset contained 3,926 connections, then the program reporting 3,926 connections would be consistent with the file.

### Changes 7

I ran the following commands:

wc -l data/friendsmed.csv
head -n 5 data/friendsmed.csv

The output showed that the file contained 3,926 lines, matching my program's result.

I kept the actual number of connections in the student results column of ANALYSIS.md rather than changing the program to match the instructor's table.


### prompt 8
What does the Valgrind result mean when it reports zero memory errors but still shows 1,423 bytes as "still reachable"?

### response 8

memory classified as "still reachable" is different from memory classified as "definitely lost" or "possibly lost."

Still-reachable memory means that the program still has a way to access the allocated memory when it exits.

### changes 9

I reviewed the Valgrind output and confirmed the following results:

Definitely lost: 0 bytes

Indirectly lost: 0 bytes

Possibly lost: 0 bytes

Still reachable: 1,423 bytes

Error summary: 0 errors

Since Valgrind did not identify any lost memory or memory errors, I did not make additional changes to the implementation based on this result.

### Prompt 9

Why is our Map implementation still performing poorly even after implementing binary search? Our execution time is not within 30% of the instructor's benchmark.

### Response 9

Although binary search improved the lookup time to O(log n), inserting new elements into the sorted vectors still takes O(n) time because existing elements need to be shifted to maintain their order. When processing larger datasets, these repeated insertions significantly increase the overall execution time. ChatGPT suggested considering alternative data structures, such as binary search trees or hash tables, to improve insertion performance and meet the 30% requirement.

## Changes 10

We reviewed our Map implementation and determined that binary search alone was not enough to meet the performance requirement. We decided to explore other data structures that could improve insertion performance.

### Prompt 10

what would be the runtime for a hashmap?

## Response 10
A hash map (hash table) has an average-case runtime of O(1) for insertion, lookup, and removal.
Operation	Average case	Worst case
Add()	O(1) amortized	O(n)
Find()	O(1)	O(n)
Remove()	O(1)	O(n)
Size()	O(1)	O(1)
ForEach()	O(n)	O(n)

Here, \(n\) represents the number of stored key-value pairs.

### changes 10
We decided to change our Map implementation from sorted vectors to a hash table using separate chaining.