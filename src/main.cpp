#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
#include "timing.hpp"

const double s = 1.00000000001;

// Schönauer triad: a[i] = b[i] + c[i] * d[i]
void benchmark_triad(std::ofstream &fout, int N) {
    std::vector<double> a(N, 0.0), b(N, 1.0), c(N, 2.0), d(N, 3.0);
    int NITER = 1;
    double start, end;

    do {
        start = getTimeStamp();
        for (int k = 0; k < NITER; ++k) {
            for (int i = 0; i < N; ++i)
                a[i] = b[i] + c[i] * d[i];
            if (a[N / 2] < 0.0) std::cout << a[N / 2] << "\n";
        }
        end = getTimeStamp();
        if ((end - start) > 0.1) break;
        NITER *= 2;
    } while (true);

    double mflops = static_cast<double>(N) * NITER * 2.0 / ((end - start) * 1e6);
    std::cout << std::fixed << std::setprecision(2)
              << "[Triad] N = " << N << ", MFlop/s = " << mflops << "\n";
    fout << N << "," << mflops << "\n";
}

// DAXPY: a[i] = s * b[i] + a[i]
void benchmark_daxpy(std::ofstream &fout, int N) {
    std::vector<double> a(N, 1.0), b(N, 2.0);
    int NITER = 1;
    double start, end;

    do {
        start = getTimeStamp();
        for (int k = 0; k < NITER; ++k) {
            for (int i = 0; i < N; ++i)
                a[i] = s * b[i] + a[i];
            if (a[N / 2] < 0.0) std::cout << a[N / 2] << "\n";
        }
        end = getTimeStamp();
        if ((end - start) > 0.1) break;
        NITER *= 2;
    } while (true);

    double mflops = static_cast<double>(N) * NITER * 2.0 / ((end - start) * 1e6);
    std::cout << std::fixed << std::setprecision(2)
              << "[DAXPY] N = " << N << ", MFlop/s = " << mflops << "\n";
    fout << N << "," << mflops << "\n";
}

int main() {
    std::ofstream fout_triad("sch_tri_results.csv");
    std::ofstream fout_daxpy("daxpy_results.csv");

    fout_triad << "N,MFlops\n";
    fout_daxpy << "N,MFlops\n";

    for (int r = 8; r <= 44; ++r) {
        int N = static_cast<int>(std::round(std::pow(1.5, r)));


        if (N > 1e8) break;

        benchmark_triad(fout_triad, N);
        benchmark_daxpy(fout_daxpy, N);
    }

    fout_triad.close();
    fout_daxpy.close();

    std::cout << "\nBenchmarking complete.\n"
              << "Results saved to sch_tri_results.csv and daxpy_results.csv\n";

    return 0;
}
