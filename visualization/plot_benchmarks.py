import pandas as pd
import matplotlib.pyplot as plt

# Load CSV files
triad_df = pd.read_csv("sch_tri_results.csv")
daxpy_df = pd.read_csv("daxpy_results.csv")

# Create the plot
plt.figure(figsize=(10, 6))
plt.plot(triad_df["N"], triad_df["MFlops"], marker='o', linestyle='-', label="Schönauer Triad")
plt.plot(daxpy_df["N"], daxpy_df["MFlops"], marker='s', linestyle='--', label="DAXPY")

# Plot settings
plt.xscale("log")
plt.ylim(bottom=0)
plt.xlabel("Vector Length N (log scale)")
plt.ylabel("Performance (MFlop/s)")
plt.title("Benchmark Performance: Schönauer Triad vs DAXPY")
plt.grid(True)
plt.legend()
plt.tight_layout()

# Save or display
plt.savefig("benchmark_comparison.png", dpi=300)
plt.show()
