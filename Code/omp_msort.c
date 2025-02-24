/*
 *  === File: omp_msort.c ===
 *
 *  Full Name: Athanasiou Vasileios Evangelos
 *  Student ID: 19390005
 *  Degree Program: PADA
 *  
 *  Compilation: gcc -o omp_msort omp_msort.c -fopenmp
 *  Execution: ./omp_msort A_unsort.txt A_sort.txt
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define T 2
#define N 10
#define LIMIT 4

void multisort(int *start, int *space, int size);
void quicksort(int *start, int *end);
int* pivotPartition(int *start, int *end);
void swap(int *a, int *b);
void merge(int *startA, int *endA, int *startB, int *endB, int *space);

int main(int argc, char *argv[]) 
{
    int *A, *Space;                 // The array A to be sorted and the Space array used for sorting
    FILE *fpA_unsort, *fpA_sort;     // Output files for storing array A before and after sorting
    int threads, size;              // Number of threads and size of the array
    int i;                          // Loop index
    double start_time, end_time;    // Execution time of the parallel program

    /*
     *  Set the number of threads and open the output files 
     */
    // We confirm that the parameters are integers
    threads = T;
    size = N;

    omp_set_num_threads(threads);

    if (argc != 3) 
    {
        printf("Usage: %s A_unsort.txt A_sort.txt\n", argv[0]);
        exit(1);
    }

    fpA_unsort = fopen(argv[1], "w");
    if (fpA_unsort == NULL) 
    {
        printf("Cannot open file %s\n", argv[1]);
        exit(1);
    }

    fpA_sort = fopen(argv[2], "w");
    if (fpA_sort == NULL) 
    {
        printf("Cannot open file %s\n", argv[2]);
        exit(1);
    }

    printf("Threads             : %d\n", threads);
    printf("Array size          : %d\n", size);
    printf("Limit for quicksort : %d\n", LIMIT);
    printf("-----------------------------------\n");

    /*
     *  Memory allocation for arrays A and Space
     */
    A = (int *) malloc(size * sizeof(int));
    if (A == NULL)
    {
        printf("Memory allocation failed for A\n");
        exit(1);
    }
    
    Space = (int *) malloc(size * sizeof(int));
    if (Space == NULL)
    {
        printf("Memory allocation failed for Space\n");
        exit(1);
    }

    /*
     *  Initialize array A with random values
     */
    srand(time(NULL));

    for (i = 0; i < size; i++)
    {
        A[i] = rand() % 199 - 99;                  // Values in the range [-99, 99]
        A[i] = A[i] >= 0 ? A[i] + 10 : A[i] - 10;    // Randomly adjust the sign
    }
    
    printf("Before sorting\n");
    printf("-----------------------------------\n");
    printf("The array A has been stored in %s\n", argv[1]);
    
    for (i = 0; i < size; i++)
        fprintf(fpA_unsort, "%d ", A[i]);
    printf("\n");

// ================================= Start of Parallel Computation =================================
    // ---- Start timing the parallel program ----
    start_time = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp single
        multisort(A, Space, size);
    }

    end_time = omp_get_wtime();
    // ---- End timing the parallel program ----
// ================================= End of Parallel Computation =================================

    printf("-----------------------------------\n");
    printf("After sorting\n");
    printf("-----------------------------------\n");
    printf("The array A has been stored in %s\n", argv[2]);
    
    for (i = 0; i < size; i++)
        fprintf(fpA_sort, "%d ", A[i]);
    printf("\n");

    printf("-----------------------------------\n");
    printf("Multisort finished in %lf sec.\n", end_time - start_time);
    printf("-----------------------------------\n");

    fclose(fpA_unsort);
    fclose(fpA_sort);

    free(A);
    free(Space);
    
    return 0;
}

/*
 * === Function: multisort ===
 * Parameters: 
 *    - int *start: Pointer to the beginning of the array to be sorted.
 *    - int *space: Pointer to a helper array of the same size as the original,
 *                  used during the merging of segments.
 *    - int size: The size of the array to be sorted.
 * Returns: 
 *      Nothing (void).
 *
 * The multisort function implements an alternative parallel sorting algorithm compared to mergesort.
 * The algorithm divides the array into four equally sized segments, recursively sorts each segment,
 * and then merges the sorted segments. When the segment size is smaller than the LIMIT, the sequential
 * quicksort algorithm is used for local sorting.
 *
 */
void multisort(int *start, int *space, int size)
{
    int quarter;                                // The size of the segment to be split
    int *startA, *startB, *startC, *startD;       // Pointers to the beginning of the four segments
    int *spaceA, *spaceB, *spaceC, *spaceD;       // Pointers to the helper array segments

    /*
     *  Termination condition: If the segment size is smaller than LIMIT,
     *  the sequential quicksort algorithm, which is more efficient for small arrays, is used.
     */
    if (size < LIMIT)
    {
        quicksort(start, start + size - 1);
        return;
    }

    /*
     *  Phase I: Divide the array into four equal segments 
     */
    quarter = size / 4;
    startA = start; spaceA = space; 
    startB = startA + quarter; spaceB = spaceA + quarter;
    startC = startB + quarter; spaceC = spaceB + quarter;
    startD = startC + quarter; spaceD = spaceC + quarter;

    /*
     *  Phase II: Recursively call multisort for the four segments using OpenMP tasks for execution on different threads
     */
    #pragma omp task firstprivate(start, space, size)
    multisort(startA, spaceA, quarter);

    #pragma omp task firstprivate(start, space, size)
    multisort(startB, spaceB, quarter);

    #pragma omp task firstprivate(start, space, size)
    multisort(startC, spaceC, quarter);

    #pragma omp task firstprivate(start, space, size)
    multisort(startD, spaceD, size - 3 * quarter);

    #pragma omp taskwait

    /*
     *  Phase III: Parallel merge of segments two by two to form segments of double size
     */
    #pragma omp task firstprivate(start, space, size)
    merge(startA, startA + quarter - 1, startB, startB + quarter - 1, spaceA);

    #pragma omp task firstprivate(start, space, size)
    merge(startC, startC + quarter - 1, startD, start + size - 1, spaceC);

    #pragma omp taskwait

    /*
     *  Phase IV: Merge the two remaining segments
     */
    merge(spaceA, spaceC - 1, spaceC, spaceA + size - 1, startA);
}

/*
 * === Function: quicksort ===
 * Parameters: 
 *    - int *start: Pointer to the beginning of the array segment to be sorted.
 *    - int *end: Pointer to the end of the array segment to be sorted.
 * Returns: 
 *      Nothing (void).
 *
 * The quicksort function implements the recursive quicksort algorithm.
 * 1. It selects a pivot element from the segment to be sorted, that is, an element
 *    that is in its correct sorted position.
 * 2. It places all elements less than or equal to the pivot to its left and all greater elements to its right,
 *    partitioning the array into two subarrays.
 * 3. It recursively repeats the process for the left and right subarrays until the entire array is sorted.
 *
 */
void quicksort(int *start, int *end)
{
    int *pvt;

    if (start < end)
    {
        pvt = pivotPartition(start, end); // Select a pivot element and partition the array around it
        quicksort(start, pvt - 1);         // Recursive call for the left subarray
        quicksort(pvt + 1, end);           // Recursive call for the right subarray
    }
}

/*
 * === Function: pivotPartition ===
 * Parameters:
 *    - int *start: Pointer to the beginning of the array segment to be partitioned.
 *    - int *end: Pointer to the end of the array segment to be partitioned.
 * Returns: 
 *    - int*: Pointer to the new location of the pivot after partitioning.
 *
 * The pivotPartition function uses the two-pointer technique to partition the array around a pivot element.
 * 1. The pivot is initially defined as the last element of the segment.
 * 2. It moves all elements less than or equal to the pivot to the left side of the array,
 *    while the greater elements remain on the right side.
 * 3. Finally, it places the pivot in its correct position, i.e., between the smaller and larger elements.
 *
 */
int* pivotPartition(int *start, int *end)
{
    int *pvt;        
    int *i, *j;       

    pvt = end;        // Initialize the pivot to the last element of the segment
    i = start - 1;    // Pointer to the last element less than or equal to the pivot

    // Loop over all elements from start to end-1
    for (j = start; j < end; j++)  
    {
        // If the current element *j is less than or equal to the pivot
        if (*j <= *pvt)  
        {
            i++;          // Move pointer i to the right
            swap(i, j);   // Swap *i (first element greater than pivot) with *j (current element)
        }
    }

    // Place the pivot in its correct position (after the last element less than it)
    swap(i + 1, pvt);  

    // Return pointer to the new position of the pivot
    return i + 1; 
}

/*
 * === Function: swap ===
 * Parameters:
 *    - int *a: Pointer to the first element to be swapped.
 *    - int *b: Pointer to the second element to be swapped.
 * Returns: 
 *      Nothing (void).
 *
 * The swap function exchanges the values of two variables pointed to by a and b.
 *
 */
void swap(int *a, int *b)
{
    int temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

/*
 * === Function: merge ===
 * Parameters:
 *    - int *startA: Pointer to the first element of the first subarray (A).
 *    - int *endA: Pointer to the last element of the first subarray (A).
 *    - int *startB: Pointer to the first element of the second subarray (B).
 *    - int *endB: Pointer to the last element of the second subarray (B).
 *    - int *space: Pointer to a temporary storage array.
 * Returns: 
 *      Nothing (void).
 *
 * The merge function combines two sorted subarrays (A and B) into a single sorted array.
 * The merged array is first stored in the temporary array 'space' and then copied back to the original array.
 *
 */
void merge(int *startA, int *endA, int *startB, int *endB, int *space)
{
    int *i = startA, *j = startB, *k = space; // Initialize pointers for subarrays A, B, and the temporary merge array

    /*
     *  Merge the two sorted subarrays into the temporary array
     */
    while (i <= endA && j <= endB) // While there are elements in both subarrays
    {
        if (*i <= *j) // If the current element in A is less than or equal to the current element in B
        {
            *k = *i; // Store the element from A into the temporary array
            i++;     // Move to the next element in A
        }
        else
        {
            *k = *j; // Store the element from B into the temporary array
            j++;     // Move to the next element in B
        }
        k++; // Move to the next position in the temporary array
    }

    /*
     *  Store any remaining elements from A (if any)
     */ 
    while (i <= endA)
    {
        *k = *i;
        i++;
        k++;
    }

    /*
     *  Store any remaining elements from B (if any)
     */ 
    while (j <= endB)
    {
        *k = *j;
        j++;
        k++;
    }

    /*
     *  Copy the elements from the temporary array back to the original array
     */ 
    for (i = space; i < k; i++)
    {
        *startA = *i;
        startA++;
    }
}
