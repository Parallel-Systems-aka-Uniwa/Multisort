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

# INSTALL

## Multisort

This repository contains the **Multisort algorithm** implementation using **OpenMP**, developed as part of the **Parallel Systems course** at the **University of West Attica**. The project demonstrates a **parallel divide-and-conquer sorting algorithm** optimized for multi-threaded execution.

---

## 1. Prerequisites

### 1.1 Required Software

- **GCC Compiler** (version supporting OpenMP, typically ≥ 4.2)
- **OpenMP library support**
- Operating System: Linux, macOS, or Windows (via WSL or MinGW)

### 1.2 Optional Software

- **Text Editor / IDE** for source code editing (VSCode, CLion, etc.)
- **Spreadsheet Viewer** for analyzing timing results (`docs/Times.xlsx`)

---

## 2. Installation Steps

### 2.1 Clone the Repository

Clone using Git:

```bash
git clone https://github.com/Parallel-Systems-aka-Uniwa/Multisort.git
```

Alternatively, download the ZIP file and extract it locally.

### 2.2 Navigate to Project Directory

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

## 3. Compilation Instructions

Compile the OpenMP C program using GCC:

```bash
gcc -o omp_msort src/omp_msort.c -fopenmp
```

Explanation:

`-o omp_msort` → output executable named omp_msort

`-fopenmp` → enables OpenMP directives

---

## 4. Execution Instructions

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

## 5. Input Files

- Located in `src/A_unsort/`
- Contain integer arrays of different sizes
- File naming pattern:

```bash
A_T<Threads>_N<Size>_L<Limit>.txt
```

Example: `A_T16_N100000000_L1000.txt` → 16 threads, 100 million elements, LIMIT 1000

---

## 6. Output Files

- Stored in `src/A_sort/`
- Contains the sorted integer array corresponding to input configuration

Examples:

- `Output_T4_N1000000_L500.txt`
- `Output_T16_N100000000_L1000.txt`

---

## 7. Running Experiments

- Modify thread count (T) to evaluate parallel performance
- Modify array size (N) to test scalability
- Adjust recursion LIMIT for optimal parallel/sequential balance
- Compare execution times using spreadsheet data in docs/Times_Multisort.xlsx
