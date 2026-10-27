# Make Friends Analysis

## Data
Fill out the remain parts of the following tables.
|            | CPU EPS |
|------------|---------|
| Instructor | 5671.61 |
| Student    |   3882.63      |

|        | Scaling |
|--------|---------|
| I-to-S |   1.4608      |

Scale the instructor numbers with the I-to-S scaling.
| File           | I People | I Con   | I Add Con  | I Time (ns) | S Con   | S Add Con  | S Time (ns) |
|----------------|----------|---------|------------|-------------|---------|------------|-------------|
| friends1.csv   | 10       | 19      | 0          | 99,149    |   19      |      0      |     15125      |
| friendssm.csv  | 10       | 12      | 1          | 59161     |  12       |       1     |      11583       |
| friendsmed.csv | 1,000    | 3,927   | 4          | 15130785  |  3926       |      4      |        2065750   |
| friendslg.csv  | 100,000  | 416,102 | 29         |1336145492 |   416102      |    29        |     286,209,375       |


## Analysis
Answer the questions below.

### What seems to be the growth rate for your Friend Groups structure in terms of number of people?
Our implementation uses a hashtable for the map and the standard vector for union fins. Our growth rate seems to be about O(n) when inserting n friends and O(1) when we are inserting or  finding a friend inside the table. Overall the time depends heavily on the number of friendship.

### Does it appear to grow faster or slower than expected?
Our implementation appears to grow approximately as expected. As the number of people and connections increases, the execution time increases as well. However, after switching from sorted vectors to a hash table, our execution times became significantly faster, even on the larger datasets. Our implementation now performs faster than the scaled instructor benchmarks on all four datasets.


### If your implementation is deviating, why do you believe your implementation is deviating from what might be expected?
Our previous implementation used sorted vectors to store names and their corresponding IDs. Although binary search reduced the time required to find a name, inserting a new name required shifting existing elements, which made the implementation slower on larger datasets. We then changed the Map to use a hash table with separate chaining. This allows insertion and lookup to take O(1) time on average without shifting the existing elements. Rehashing also helps prevent buckets from becoming too crowded, improving overall performance.

### What do you believe is the dominant structure/algorithm in your implementation?
We think that it is the map implementation as we had to constanly change how we implemented the map inorder to be within the performance time. During our previous implementation, they worked well with small and medium datasets while performing badly on the larger dataset but after we swaped to hash table performance time imporved significantly hence map beign the dominant structure.