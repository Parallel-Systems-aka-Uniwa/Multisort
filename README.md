<p align="center">
  <img src="https://www.especial.gr/wp-content/uploads/2019/03/panepisthmio-dut-attikhs.png" alt="UNIWA" width="150"/>
</p>

<p align="center">
  <strong>UNIVERSITY OF WEST ATTICA</strong><br>
  SCHOOL OF ENGINEERING<br>
  DEPARTMENT OF COMPUTER ENGINEERING AND INFORMATICS
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
  Co-supervisor: Michalis Iordanakis, Special Technical Laboratory Staff
</p>

<p align="center">
  <a href="https://scholar.google.com/citations?user=LiVuwVEAAAAJ&hl=en" target="_blank">UNIWA Profile</a>
</p>

</hr>

<p align="center">
  Athens, February 2025
</p>


---

# Multisort

This project implements and evaluates the **Multisort algorithm**—a parallel alternative to Mergesort—using **OpenMP**. The goal is to achieve high-performance sorting through a **multi-threaded "divide and conquer"** approach.

---

## Table of Contents

| Section | Folder/File | Description |
|------:|-------------|-------------|
| 1 | `assign/` | Assignment material for the Multisort OpenMP workshop |
| 1.1 | `assign/_Par_Sys_Ask_2_2024-25.pdf` | Assignment description in English |
| 1.2 | `assign/_Παρ_Συσ_Ασκ_2_2024-25.pdf` | Assignment description in Greek |
| 2 | `docs/` | Documentation and performance results for Multisort algorithm |
| 2.1 | `docs/Algorithm-Multisort.pdf` | English documentation for Multisort algorithm |
| 2.2 | `docs/Αλγόριθμος-Multisort.pdf` | Greek documentation for Multisort algorithm |
| 2.3 | `docs/Times_Multisort.xlsx` | Execution times and benchmarks |
| 3 | `src/` | Source code and input/output data for Multisort exercises |
| 3.1 | `src/omp_msort.c` | Main OpenMP Multisort program |
| 3.2 | `src/A_sort/` | Sorted input data files for exercise A |
| 3.3 | `src/A_unsort/` | Unsorted input data files for exercise A |
| 3.4 | `src/Output/` | Output result files from Multisort execution |
| 4 | `README.md` | Repository overview and usage instructions |

---

## Algorithm Overview

The Multisort algorithm decomposes the sorting problem recursively and distributes tasks to parallel threads.

### Steps

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

## Technical Implementation

### OpenMP Integration

- `#pragma omp parallel` → Activates parallel threads
- `#pragma omp single` → Starts the initial recursive call by a single thread
- `#pragma omp task` → Defines tasks for recursion and merging
- `firstprivate` → Ensures each thread has its own initialized copy of variables
- `#pragma omp taskwait` → Synchronization barrier to wait for all sub-tasks

### Key Data Structures & Functions

| Function | Description |
|----------|-------------|
| `multisort` | Core parallel function managing partitioning and task allocation |
| `merge` | Merges two sorted subsets into a temporary array before writing back |
| `quicksort` | Sequential fallback for small sub-arrays below **LIMIT** |
| `pivotPartition` | Partitions array around a pivot element for Quicksort |

---

## Performance Parameters

The implementation evaluates efficiency based on:

- **Table Size (N)** → Total number of integers
- **Threads (T)** → Number of parallel threads
- **Limit (LIMIT)** → Threshold for switching from parallel recursion to sequential Quicksort

**Speedup Analysis**: Execution times for sequential runs (1 thread) are compared against parallel runs (up to 16 threads).

---

## Usage Instructions

The program is executed via command line with parameters:

- Number of threads
- Array size
- Recursion limit

### Example Output Files

- `Output_T4_N1000000_L500.txt` → 4 threads, 1 million elements, LIMIT 500  
- `Output_T16_N100000000_L1000.txt` → 16 threads, 100 million elements, LIMIT 1000

---

# Installation & Setup Guide

This repository contains the **Multisort algorithm** implementation using **OpenMP**, developed as part of the **Parallel Systems course** at the **University of West Attica**. The project demonstrates a **parallel divide-and-conquer sorting algorithm** optimized for multi-threaded execution.

---

## Prerequisites

### Required Software
- **GCC Compiler** (version supporting OpenMP, typically ≥ 4.2)
- **OpenMP library support**
- Operating System: Linux, macOS, or Windows (via WSL or MinGW)

### Optional Software
- **Text Editor / IDE** for source code editing (VSCode, CLion, etc.)
- **Spreadsheet Viewer** for analyzing timing results (`docs/Times.xlsx`)

---

## Installation Steps

### 1. Clone the Repository

Clone using Git:

```bash
git clone https://github.com/Parallel-Systems-aka-Uniwa/Multisort.git
```

Alternatively, download the ZIP file and extract it locally.

### 2. Navigate to Project Directory
```bash
cd Multisort
```

Ensure the following structure exists:
```bash
assign/
docs/
src/
README.md
```

`src/` contains the main program (omp_msort.c) and input files for exercises A and B.

`docs/` contains documentation and performance results.

---

## Compilation Instructions
Compile the OpenMP C program using GCC:
```bash
gcc -o omp_msort src/omp_msort.c -fopenmp
```
Explanation:

`-o omp_msort` → output executable named omp_msort

`-fopenmp` → enables OpenMP directives

---

## Execution Instructions
Run the program via command line with input and output file arguments:
```bash
./omp_msort src/A_unsort/A_unsort.txt src/A_sort/A_sort.txt
```
- **First argument**: path to unsorted input array (A_unsort.txt)
- **Second argument**: path for writing sorted output (A_sort.txt)

Example Run
```bash
./omp_msort src/A_unsort/A_T4_N1000000_L500.txt src/A_sort/Output_T4_N1000000_L500.txt
```

- 4 threads, 1 million elements, recursion LIMIT = 500
- Output saved in the `src/A_sort/` folder

---

## Input Files
- Located in `src/A_unsort/`
- Contain integer arrays of different sizes
- File naming pattern:
```bash
A_T<Threads>_N<Size>_L<Limit>.txt
```

Example: `A_T16_N100000000_L1000.txt` → 16 threads, 100 million elements, LIMIT 1000

---

## Output Files
- Stored in `src/A_sort/`
- Contains the sorted integer array corresponding to input configuration

Examples:
- `Output_T4_N1000000_L500.txt`
- `Output_T16_N100000000_L1000.txt`

---

## Running Experiments
- Modify thread count (T) to evaluate parallel performance
- Modify array size (N) to test scalability
- Adjust recursion LIMIT for optimal parallel/sequential balance
- Compare execution times using spreadsheet data in docs/Times_Multisort.xlsx