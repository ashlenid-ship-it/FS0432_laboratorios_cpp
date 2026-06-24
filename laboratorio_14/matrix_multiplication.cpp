#include <iostream>
#include <vector>
#include <fstream>
#include <omp.h>

int main() {

    const int N = 2000;  // se tuvo que ajustar el valor de N por  limitaciones de hardware.

    std::vector<int> threads = {1, 2, 4, 8, 16, 32};

    std::ofstream file("tiempos.txt");
    file << "hilos tiempo\n";

    for (int t : threads) {

        omp_set_num_threads(t);

        std::vector<double> A(N * N, 1.5);
        std::vector<double> B(N * N, 2.0);
        std::vector<double> C(N * N, 0.0);

        double start = omp_get_wtime();

        #pragma omp parallel for
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {

                double suma = 0.0;

                for (int k = 0; k < N; k++) {suma += A[i * N + k] * B[k * N + j];}

                C[i * N + j] = suma;
            }
        }

        double end = omp_get_wtime();

        file << t << " " << (end - start) << "\n";

        std::cout << "Hilos " << t << " listo\n";
    }

    file.close();

    return 0;
}