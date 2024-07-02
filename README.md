# **DEVELOPMENT OF SOFTWARE FOR INFORMATION SYSTEMS**
## **WINTER SEMESTER 2023–2024**

| FullName                     | ΑΜ                  | Email                   |
| ---------------------------- | ------------------- | ------------------------|
| Marina Mylona                | 1115201900229       | sdi1900229@di.uoa.gr   |
| Vangelis Vrailas             | 1115201900314       | sdi1900314@di.uoa.gr   |
| Despina Christodoulou        | 1115201900303       | sdi1900303@di.uoa.gr   |


Git repository: https://github.com/Vaggelisvl/Project_2023_1

<p align="center">
  <strong>Project 1</strong>
</p>


- **Design options:**<br>
Below we list the main design choice, which illustrates the Graph. Specifically, it is a map, which has as key the class Point and as value a vector from Neighbors. The implementations of the custom map and vector data structures are located in the files headers/structures/unorderedMap/UnorderedMap.h and headers/structures/vector/Vector.h respectively. The Point class represents each element of the file we are reading, which has its coordinates and id. The Neighbor class is an extension of Point with the difference that it has its distance from the key (point).

![image](https://github.com/Vaggelisvl/Project_2023_1/assets/139377786/1bf06e47-0a85-41a3-af03-b7e4fa275e3c)



- **Read from file: src/structures/Dataset.cpp**<br>
Reading from the binary file is done in Dataset.cpp, after the user has given the name of the file he wants to read, the number of point dimensions and the number of points present. The last argument may not give it, if it wants to read from files with the format given to us because it will read it from the file.

- **Graph Initialization: src/structures/graph/GraphInitialization.cpp**<br>
The setKRandomNeighbors method performs the process of randomly initializing the K neighbors for each point in the Graph. After finding the random neighbor in the dataset, it calculates the distance between the current point and the random neighbor using the Euclidean distance function. Creates a Neighbors object for the random neighbor with its ID, distance, and coordinates. Finally he adds it to the Graph and does the same for its reverse.

- **KNN algorithm: src/structures/graph/GraphInitialization.cpp**<br>
The KNNAlgorithm method implements the K-Nearest Neighbors (KNN) algorithm to optimize the set of neighbors for each point in the graph. For each point in the graph it sorts its neighbors by distance so that the neighbor with the longest distance is at the end of the table. Then for each neighbor it searches the neighbors of neighbors and calculates its distance between the current point, after checking for duplicate points. If this distance is less than the maximum distance recorded, then the extended neighbor is replaced. If a change has been made, the function returns 0 to call the same function again, otherwise it returns 1.

- **CNN algorithm for point outside Graph: src/structures/graph/GraphInitialization.cpp**<br>
The findKNearestNeighborsForPoint method executes the algorithm for finding the K-nearest neighbors of a query point that is not in the Graph. Initializes random neighbors and calculates the distances between them. Then it adds to the Graph the query point with these K neighbors and calls the above function (KNNAlgorithm). When the KNN algorithm finishes, it removes this point from the graph.


- **Possibility to use alternative similarity metric: src/structure/utils/Metrics.cpp**<br>
We have implemented two metrics, euclidean and manhatan which are located in the Metrics.cpp file.

- **Dataset:**
1. The format given to us (input1.cpp, 00000200.bin, 00001000.bin)
2. Our format: 100 elements of 20 dimensions (data.bin)

- **Results.txt:**<br>
This file stores the results from the 20 nearest neighbors of each point in the file. It is only used for the purpose of checking the KNN algorithm.

- **In library.cpp there is main**
- **To compile:** make all
- **To compile without installing dependencies:** make all_skip_dependencies
- **For the tests:** make test

- **First Party Optimizations:**<br>
• Show number of correct and incorrect decisions and percentage of total number of correct K nearest neighbors of the algorithm.
• Make changes to the makefile
• Implementation of further tests
• Correction of number of parameters accepted by the program
• General improvements

<p align="center">
  <strong>Project 2</strong>
</p>

- **Optimizations class:**<br>
In this class are the implementations of the second exercise, which inherits the GraphInitialization class. The graph is initialized in the same way as before via the setKRandomNeighbors() function.

- **Local Join: src/structures/graph/Optimizations.cpp**<br>
 The KNN algorithm is called from Library.cpp which for each point in the Graph calls the local join function. This function, for each pair of neighbors, initially checks with the checkDuplicate() function if there are identical ids in the neighbor lists of these two points, measures the distance between them and checks whether one neighbor should be included in the neighbor list of the other.

- **Distance pairs:**<br>
We keep a structure hashMap which has as Key a point and as value a struct(DistanceContents) with the id of another point and the distance between them. This is done in order not to calculate the same distance between two points twice. Checking whether a distance has been recomputed is done in the local join() function with the hashingDuplicateDistnaces() function.

- **Incremental Search: src/structures/graph/Optimizations.cpp**<br>
We have added to the Neighbors structure a flag which after graph initialization becomes true on all neighbors of all points. Then in each local join the incrementalSearch() function is called to check if at least one of the two points has a true flag. When a new point is added as a neighbor within the local join, the flag is set to false.

- **Sampling: src/structures/graph/Optimizations.cpp**<br>
For each point of the graph the function sampling() is called. This function implements the sampling process, in which the percentage of points that will be calculated in a local join is calculated each time. Then for all points in the graph it finds the first percentageToUse neighbors and changes a variable(setHasBeenChoosen) from 0 to 1. This variable is added to the Points structure and initialized for each neighbor to 0.

- **Premature Termination: src/structures/graph/Optimizations.cpp**<br>
Early termination is implemented by using a count variable in each iteration, which records the number of changes in each iteration. At the end of each iteration, a check is made if the count is less than d*K, where d is 0.01 and K is the number of neighbors, and the algorithm terminates.

- **Find point outside graph: src/structures/graph/Optimizations.cpp**<br>
The procedure is similar to the previous exercise for the point-off-graph algorithm, except that each point that is added as a neighbor to the point is updated and the flag is set to true. The implementation is in the findKnearestNeighborsForGraph() function.

- **Reverse Lists**:<br>
The reverse lists are stored in an UnorderedMap named reverseNN and has the same structure as the graph. After initializing the graph the function initReverseNN() is called where the reverseNN is initialized. Also, whenever a neighbor is added or removed, the reverseNN is also updated.

- **Results:**
 1. graph.txt: The graph of the first exercise after the algorithm is printed
 2. optimizedGraph.txt: The graph of the second exercise after the algorithm is printed
 3. reverseNN.txt: Print the graph with the reverse lists after the algorithm
 4. results.txt: All points with nearest neighbors sorted are printed

- **Execute Program:**<br>
Make run defaults to src/input1.bin 100 20 5 1 euclidean
(100 dimensions, 20 points, K=5, queryId=1, Euclidean metric)

- **Second Part's Optimizations:**<br>
•The program accepts the arguments from the command line in this order:<br>
<inputFile> <dimensions> <numOfPoints> <K> <queryId> <d> <metrics> <D> <numOfTrees> <numOfThreads>

<p align="center">
  <strong>Project 3 </strong>
</p>

- **Execute Program:**<br>
Make run defaults to src/input1.bin 100 20 5 1 0.01 euclidean 3 10 5
(100 dimensions, 20 points, K=5, queryId=1, d=0.01, Euclidean metric, D=3, 10 trees, 5 threads)



# **FINAL REPORT**

## **Experiments:**

- **Initialize Script**<br>

   ![image](https://github.com/Vaggelisvl/Project_2023_1/assets/139377786/c76b4359-052c-4b7f-8ebd-6605b49e6748)

In the diagram above we see the execution time of the 3 projects we implemented in the initialization of the graph. We notice that the most time-consuming initialization is of the third project. This makes sense as in this project we made initialization optimizations using random projection trees and comparing leaf points. This procedure was not done in the other two projects but was done with completely random neighbors. So, even though we made optimizations in this step, we don't see any effect in this step with respect to time.



- **KNN Algorithm**<br>

   ![image](https://github.com/Vaggelisvl/Project_2023_1/assets/139377786/c61726f1-a7c5-44ab-ade1-0b3b87a2f97c)

In the diagram above we see the execution time for the KNN algorithm in the 3 projects. We have the shortest execution time in the first project, in which we compared the distances of points between neighbors and neighbors of neighbors. In the second project, however, we changed our perspective and compared the distances between the neighbors and for each neighbor we checked whether it should be added to the k closest to the other. We also had the sampling and some other checks causing the algorithm to slow down. In the third project, this algorithm becomes a job so that the work is shared among the threads and we have a shorter execution time than the second one. This experiment was done with a number of threads equal to 5. Finally, the reason that the first project has a shorter execution time of the algorithm than the third project, is because in the third project the algorithm of the second one is called and not the first one.

- **Program execution time**<br>

  ![image](https://github.com/Vaggelisvl/Project_2023_1/assets/139377786/ded0561e-06ce-49c3-a2fd-bfb80f3308a5)

In the diagram above we see the execution time of each project separately. We notice that the second project has the worst time and this is logical based on the previous experiments. Also, although the CNN algorithm in the third project has a longer time than the first, we see that the execution time of the third is not much longer than the first. This means that with multithreading we managed to reduce the execution time a lot, almost as much as in the first one.


- **Number of Threads**<br>

   ![image](https://github.com/Vaggelisvl/Project_2023_1/assets/139377786/cf4498ba-7b68-4a5c-b8c0-5120bacebdf1)

In the above experiment we see the execution time of the third project, testing the number of threads with 4,5 and 6. The above results lead to the conclusion that for a small number of points and a small number of neighbors we do not see any particular difference in time and the 3 tests have almost the same time, with a minimal difference for 4 threads. On the contrary, at 1000 points with κ=20 and 500 points with κ=25, we see that with 5 threads it shows better results. So we decided that the number 5 for the threads is ideal, since for fewer points we don't see any particular difference, but for more time-consuming procedures it works better.

- **Number of trees**<br>
![image](https://github.com/Vaggelisvl/Project_2023_1/assets/139377786/cad1feec-9fdb-4cc8-bf67-97a59b41cd82)

In the above diagrams we see the success rate, but also the execution time of the program with different number of trees. According to the results we obtained, the creation of 10 trees gives us the best results, except for one case (500 points and κ=10). Looking at the second diagram, we noticed that the times do not have a big difference between them, so we decided that the best choice for the number of random projection trees we will make is 10.


- **Number D**<br>
![image](https://github.com/Vaggelisvl/Project_2023_1/assets/139377786/2cc12d87-7966-478c-80a8-e779ee20b803)

In the diagrams above we see the success rate of the project by changing D (number of points per leaf of the tree). Specifically in the left diagram we see the percentage by choosing D to be 1,2 and 3 with the number of nearest neighbors fixed (κ=5). In the right diagram we choose D to be 3.5 and 7 with k fixed at 10. We noticed that the most efficient choice for the number D is 3.


## **Summary:**

Based on the above experiments, we arrived at specific number options for the dataset which are given as default with the make run. Of course these can be changed from the terminal.
Furthermore, it is important to underline that optimal performance does not automatically result from increasing the number of threads. This choice must be carefully considered, taking into account the peculiarities of procedures such as normCalculation, split, KNN and hyperplane. More threads can lead to unwanted collisions and higher communication costs, which can negatively affect execution times.
Along with the number of threads, memory management also plays a critical role in the overall performance of the application. When running the application with multiple threads, each thread consumes memory to store data and intermediate results.

Using multiple threads can lead to increased memory consumption, as each thread requires its own resources. Depending on the number of threads and the nature of the processes, increasing memory can help or hurt performance. From the experiments we noticed that a high number of threads can lead to unnecessary memory allocation and increased data exchange between threads, thus burdening the system.

Conversely, running with fewer threads or with careful memory management can minimize memory consumption, but affects runtime negatively.

Therefore, optimal memory management has been considered in relation to threading, aiming to achieve a balance between performance and resource consumption.











