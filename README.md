# High-Performance Computing Benchmarks

This project was developed as part of the **Programming Techniques for Supercomputers** course. It focuses on benchmarking the performance of fundamental computational kernels, analyzing performance bottlenecks, and visualizing results.

## Project Overview

The assignment investigates theoretical and practical performance limits on a modern CPU. It consists of three tasks:

1. **Peak Floating-Point Performance Analysis**  
   Theoretical calculations of maximum performance per core and per chip using superscalarity, SIMD width, FMA availability, and clock frequency.

2. **Loop Optimization with Modulo Variable Expansion (MVE)**  
   Analysis of pipeline bottlenecks and latency hiding using loop unrolling techniques.

3. **Practical Benchmarking**  
   Implementation of benchmark codes for the **Schönauer Triad** and **DAXPY** operations, measuring FLOP/s performance, and visualizing the results.

---

## Code Structure

### 1. `main.cpp`

- Implements two benchmark kernels:
  - **Schönauer Triad**: `a[i] = b[i] + c[i] * d[i]`
  - **DAXPY**: `a[i] = s * b[i] + a[i]`
- Uses adaptive iteration counts to ensure runtime > 0.1s for reliable measurement.
- Writes results to CSV files:
  - `sch_tri_results.csv`
  - `daxpy_results.csv`
- Outputs performance in **MFlop/s** for a range of vector sizes.

### 2. `timing.hpp`

- Provides a lightweight function `getTimeStamp()` based on `std::chrono` for precise timing measurements.

### 3. `plot_benchmarks.py`

- Loads benchmark results from the CSV files.
- Plots performance curves for both kernels:
  - Schönauer Triad
  - DAXPY
- Saves a comparison figure as `benchmark_comparison.png`.

### 4. `assignment_2.pdf`

- Contains the theoretical analysis and detailed write-up:
  - Peak performance calculations
  - Bottleneck analysis
  - Explanation of Modulo Variable Expansion (MVE)
  - Experimental setup and benchmark results
  - Interpretation of the plotted data

---

## Compilation and Execution

### Compilation

Use the Intel C++ compiler (`icpx`) with optimization flags:

```bash
icpx -O3 -march=native -std=c++17 main.cpp -o benchmark.out
```

### Running Benchmarks

On a compute node:

```bash
salloc --nodes=1 --time=01:00:00
srun --cpu-freq=2200000-2200000:performance ./benchmark.out
```

This produces two CSV files with benchmark results.

### Plotting Results

Run the Python script locally:

```bash
python3 plot_benchmarks.py
```

This generates and saves the figure:

- `benchmark_comparison.png`

---

## Results Summary

- **DAXPY** reaches a peak of ~12,000 MFlop/s around `N ≈ 10²–10³`.
- **Schönauer Triad** reaches ~8,500 MFlop/s in the same range.
- Performance drops:
  - After `N ≈ 10³`: L2/L3 cache limitations.
  - After `N ≈ 10⁴`: Memory bandwidth saturation.

---

## File Outputs

- `sch_tri_results.csv` – Schönauer Triad performance results  
- `daxpy_results.csv` – DAXPY performance results  
- `benchmark_comparison.png` – Performance comparison plot  

---

## License

This project is available under the MIT license. See the LICENSE.md file for more info.

## Author

- Mehmet Arif Bagci - mehmet.a.bagc@fau.de  
