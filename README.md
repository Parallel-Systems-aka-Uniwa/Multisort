<p align="center">
  <img src="https://www.especial.gr/wp-content/uploads/2019/03/panepisthmio-dut-attikhs.png" alt="UNIWA" width="150"/>
</p>

<p align="center">
  <strong>UNIVERSITY OF WEST ATTICA</strong><br>
  SCHOOL OF ENGINEERING<br>
  DEPARTMENT OF COMPUTER ENGINEERING AND INFORMATICS
</p>

<p align="center">
  <a href="https://www.uniwa.gr" target="_blank">University of West Attica</a> ·
  <a href="https://ice.uniwa.gr" target="_blank">Department of Computer Engineering and Informatics</a>
</p>

---

<p align="center">
  <strong>Parallel Systems</strong>
</p>

<h1 align="center">
  Multisort
</h1>

<p align="center">
  <strong>Vasileios Evangelos Athanasiou</strong><br>
  Student ID: 19390005
</p>

<p align="center">
  <a href="https://github.com/Ath21" target="_blank">GitHub</a> ·
  <a href="https://www.linkedin.com/in/vasilis-athanasiou-7036b53a4/" target="_blank">LinkedIn</a>
</p>

<hr/>

<p align="center">
  <strong>Supervision</strong>
</p>

<p align="center">
  Supervisor: Vasileios Mamalis, Professor
</p>
<p align="center">
  <a href="https://ice.uniwa.gr/en/emd_person/vassilios-mamalis/" target="_blank">UNIWA Profile</a>
</p>

<p align="center">
  Co-supervisor: Michalis Iordanakis, Academic Scholar
</p>

<p align="center">
  <a href="https://ice.uniwa.gr/academic_sc_ho/" target="_blank">UNIWA Profile</a> ·
  <a href="https://scholar.google.com/citations?user=LiVuwVEAAAAJ&hl=en" target="_blank">Scholar</a>
</p>

</hr>

---

<p align="center">
  Athens, February 2025
</p>

---

<p align="center">
  <img src="https://www.researchgate.net/publication/228870567/figure/fig2/AS:643187416784896@1530359238947/Parallel-sorting-algorithm.png" width="250"/>
</p>

---

# README

## Multisort

This project implements and evaluates the **Multisort algorithm**—a parallel alternative to Mergesort—using **OpenMP**. The goal is to achieve high-performance sorting through a **multi-threaded "divide and conquer"** approach.

---

## Table of Contents

| Section | Folder/File                         | Description                                                   |
| ------: | ----------------------------------- | ------------------------------------------------------------- |
|       1 | `assign/`                           | Assignment material for the Multisort OpenMP workshop         |
|     1.1 | `assign/_Par_Sys_Ask_2_2024-25.pdf` | Assignment description in English                             |
|     1.2 | `assign/_Παρ_Συσ_Ασκ_2_2024-25.pdf` | Assignment description in Greek                               |
|       2 | `docs/`                             | Documentation and performance results for Multisort algorithm |
|     2.1 | `docs/Algorithm-Multisort.pdf`      | English documentation for Multisort algorithm                 |
|     2.2 | `docs/Αλγόριθμος-Multisort.pdf`     | Greek documentation for Multisort algorithm                   |
|     2.3 | `docs/Times_Multisort.xlsx`         | Execution times and benchmarks                                |
|       3 | `src/`                              | Source code and input/output data for Multisort exercises     |
|     3.1 | `src/omp_msort.c`                   | Main OpenMP Multisort program                                 |
|     3.2 | `src/A_sort/`                       | Sorted input data files for exercise A                        |
|     3.3 | `src/A_unsort/`                     | Unsorted input data files for exercise A                      |
|     3.4 | `src/Output/`                       | Output result files from Multisort execution                  |
|       4 | `README.md`                         | Project documentation                                         |
|       5 | `INSTALL.md`                        | Usage instructions                                            |

---

## 1. Algorithm Overview

The Multisort algorithm decomposes the sorting problem recursively and distributes tasks to parallel threads.

### 1.1 Steps

1. **Partitioning**  
   Divide the input array of **N integers** into four equal-sized parts.

2. **Parallel Recursion**  
   Each part is sorted recursively using OpenMP tasks, allowing up to four threads to process simultaneously.

3. **Termination Criterion**  
   If a sub-array reaches a user-defined **LIMIT**, recursion stops and sequential **Quicksort** is used.

4. **Parallel Merging**
   - Merge the four sorted parts in pairs simultaneously.
   - Finally, merge the two remaining parts sequentially to produce a fully sorted array.

---

## 2. Technical Implementation

### 2.1 OpenMP Integration

- `#pragma omp parallel` → Activates parallel threads
- `#pragma omp single` → Starts the initial recursive call by a single thread
- `#pragma omp task` → Defines tasks for recursion and merging
- `firstprivate` → Ensures each thread has its own initialized copy of variables
- `#pragma omp taskwait` → Synchronization barrier to wait for all sub-tasks

### 2. Key Data Structures & Functions

| Function         | Description                                                          |
| ---------------- | -------------------------------------------------------------------- |
| `multisort`      | Core parallel function managing partitioning and task allocation     |
| `merge`          | Merges two sorted subsets into a temporary array before writing back |
| `quicksort`      | Sequential fallback for small sub-arrays below **LIMIT**             |
| `pivotPartition` | Partitions array around a pivot element for Quicksort                |

---

## 3. Performance Parameters

The implementation evaluates efficiency based on:

- **Table Size (N)** → Total number of integers
- **Threads (T)** → Number of parallel threads
- **Limit (LIMIT)** → Threshold for switching from parallel recursion to sequential Quicksort

**Speedup Analysis**: Execution times for sequential runs (1 thread) are compared against parallel runs (up to 16 threads).

---

## 4. Usage Instructions

The program is executed via command line with parameters:

- Number of threads
- Array size
- Recursion limit

### 4.1 Example Output Files

- `Output_T4_N1000000_L500.txt` → 4 threads, 1 million elements, LIMIT 500
- `Output_T16_N100000000_L1000.txt` → 16 threads, 100 million elements, LIMIT 1000
