#include <mpi.h>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

double f(double x)
{
    return sin(x);
}

int main(int argc, char* argv[])
{
// iniciar MPI
MPI_Init(&argc, &argv);

int rank;
MPI_Comm_rank(MPI_COMM_WORLD, &rank);


int size;
MPI_Comm_size(MPI_COMM_WORLD, &size);

const int N = 128000;

if (N % size != 0)
{
    if(rank == 0)
    {
        cout << "Error: N debe ser divisible entre el número de procesos." << endl;
    }

    MPI_Finalize();
    return 1;
}

int local_n = N / size;

//vectores locales crear
vector<double> localA(local_n);
vector<double> localB(local_n);

// vectores sólo en el proceso 0
vector<double> A;
vector<double> B;

if(rank == 0)
{
    A.resize(N);
    B.resize(N);

    for(int i = 0; i < N; i++)
    {
        A[i] = f((double)i);
        B[i] = 2 * f((double)i);
    }
}

//envíar los bloques(etiquetas distintas)
if(rank == 0)
{
    for(int i = 0; i < local_n; i++)
    {
        localA[i] = A[i];
        localB[i] = B[i];
    }

    for(int p = 1; p < size; p++)
    {
        MPI_Send(&A[p*local_n], local_n, MPI_DOUBLE, p, 0, MPI_COMM_WORLD);

        MPI_Send(&B[p*local_n], local_n, MPI_DOUBLE, p, 1, MPI_COMM_WORLD);
    }
}

//los demás procesos reciben 

else
{
    MPI_Recv(localA.data(),
             local_n,
             MPI_DOUBLE,
             0,
             0,
             MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);

    MPI_Recv(localB.data(),
             local_n,
             MPI_DOUBLE,
             0,
             1,
             MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
}

// Medir el tiempo del cálculo del producto punto
double inicio = MPI_Wtime();

double suma_local = 0.0;

for(int i = 0; i < local_n; i++)
{
    suma_local += localA[i] * localB[i];
}

double fin = MPI_Wtime();

double tiempo_local = fin - inicio;


//Reducir sumas 
double suma_global = 0.0;

MPI_Reduce(&suma_local,
           &suma_global,
           1,
           MPI_DOUBLE,
           MPI_SUM,
           0,
           MPI_COMM_WORLD);


// Para obtener eñ mayor tiempo de ejecución entre todos los procesos
double tiempo_total = 0.0;

MPI_Reduce(&tiempo_local,
           &tiempo_total,
           1,
           MPI_DOUBLE,
           MPI_MAX,
           0,
           MPI_COMM_WORLD);


//imprimir ambas 

if(rank == 0)
{
    cout << "Numero de procesos: " << size << endl;

    cout << "Producto punto = "
         << suma_global
         << endl;

    cout << "Tiempo de ejecucion = "
         << tiempo_total
         << " segundos"
         << endl;
}

MPI_Finalize();

return 0;
}