# Tarea 5 - Producto punto con MPI
Ashely Ureña Fonseca C27948
## Compilación

Usar:

g++ producto_punto_mpi.cpp -o producto.exe -I "C:\Program Files (x86)\Microsoft SDKs\MPI\Include" -L "C:\Program Files (x86)\Microsoft SDKs\MPI\Lib\x64" -lmsmpi

## Ejecución

Ejecutar con MPI:

mpiexec -n 4 producto.exe

## Descripción

Este programa calcula el producto punto de dos vectores de tamaño N = 128000 utilizando programación paralela con MPI.

- El proceso 0 inicializa los vectores.
- Los datos se distribuyen entre procesos usando MPI_Send y MPI_Recv.
- Cada proceso calcula su contribución local.
- Se usa MPI_Reduce para obtener el resultado global.
- Se mide el tiempo de ejecución del cálculo.