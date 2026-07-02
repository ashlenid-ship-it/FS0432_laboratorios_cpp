# Laboratorio 14

Ashley Ureña Fonseca C27948

## Compilar

```bash
g++ -O3 -fopenmp matrix_multiplication.cpp -o matrix
```

## Ejecutar

```bash
OMP_NUM_THREADS=1 ./matrix
OMP_NUM_THREADS=2 ./matrix
OMP_NUM_THREADS=4 ./matrix
OMP_NUM_THREADS=8 ./matrix
OMP_NUM_THREADS=16 ./matrix
OMP_NUM_THREADS=32 ./matrix
```

## Archivos

- matrix_multiplication.cpp
- tiempos.txt
- tiempo_vs_hilos.png

## Justificación del tamaño de N

Se utilizó N = 2000 en lugar del valor mayor propuesto, debido a limitaciones de hardware y tiempo de ejecución.

Este tamaño permite obtener resultados estables y comparables entre diferentes números de hilos sin comprometer la validez del experimento como tal