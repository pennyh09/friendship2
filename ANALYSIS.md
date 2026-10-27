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
| friends1.csv   | 10       | 19      | 0          | 99,149    |   19      |      0      |     85167        |
| friendssm.csv  | 10       | 12      | 1          | 59161     |  12       |       1     |      49500       |
| friendsmed.csv | 1,000    | 3,927   | 4          | 15130785  |  3926       |      4      |        23392250     |
| friendslg.csv  | 100,000  | 416,102 | 29         |1336145492 |   416102      |    29        |     84551167413        |


## Analysis
Answer the questions below.

### What seems to be the growth rate for your Friend Groups structure in terms of number of people?
the implementation has O(n^2), where n represents the number of friends. Where although binary search is suppose to reduce the time to find the key but inseting new elements into the vectors still talke O(n). And when the operation repeats for lots of people, the total time is growing quadratically. 
...

### Does it appear to grow faster or slower than expected?
...
My implementation appears to grow faster in execution time than expected. Compared to the scaled instructor results, my implementation takes significantly longer to process the larger datasets. This suggests that my implementation is less efficient as the number of people increases.


### If your implementation is deviating, why do you believe your implementation is deviating from what might be expected?
...
My implementation deviates from the expected performance because it uses vectors to store names and their corresponding IDs. Although binary search makes finding names faster, inserting a new name into its sorted position requires shifting existing elements. As the dataset becomes larger, more elements may need to be shifted, increasing the execution time.

### What do you believe is the dominant structure/algorithm in your implementation?
...
I think is the map implemetation sinc eit is using storted vectors to store the names and the ids. Even if the binary is supposed to reduce the time but the inserting process still require shifting the existing elements in the vector which can be less efficient. 