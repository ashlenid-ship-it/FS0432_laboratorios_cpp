import matplotlib.pyplot as plt

procesos = [1, 2, 4, 8]
tiempos = [0.0022752, 0.0012984, 0.0008039, 0.0005405]

plt.plot(procesos, tiempos, marker='o')

plt.xlabel("Número de procesos")
plt.ylabel("Tiempo (segundos)")
plt.title("Tiempo vs procesos (MPI producto punto)")

plt.grid(True)

plt.savefig("tiempo_vs_procesos.png")
plt.show()