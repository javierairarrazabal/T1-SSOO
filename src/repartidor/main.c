// #include <stdio.h>
// #include <unistd.h>
// #include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdbool.h>

int estado_semaforos[3];
int ubicacion_semaforos[3];
int cant_turnos[4];
int distancia = 0;
int ubicacion_bodega;
int id_repartidor;

void handle_sigusr1(int sig, siginfo_t *siginfo, void *context)
{
  int number_received = siginfo->si_value.sival_int;
  estado_semaforos[number_received] = !estado_semaforos[number_received];
  // printf("Repartidor: de pid %d: Recibi semaforo id %i en estado %i\n", getpid(), number_received, estado_semaforos[number_received]);
}

void handle_sigabrt(int sig)
{
  char file[sizeof "repartidor_0.txt"];
  sprintf(file, "repartidor_%d.txt", id_repartidor);
  FILE *output = fopen(file, "w");
  fprintf(output, "%i", cant_turnos[0]);
  fprintf(output, ",");
  fprintf(output, "%i", cant_turnos[1]);
  fprintf(output, ",");
  fprintf(output, "%i", cant_turnos[2]);
  fprintf(output, ",");
  fprintf(output, "%i", cant_turnos[3]);
  fclose(output);
  printf("Fin repartidor id %i\n", id_repartidor);
  exit(0);
}

int main(int argc, char const *argv[])
{
  connect_sigaction(SIGUSR1, handle_sigusr1);
  connect_sigaction(SIGABRT, handle_sigabrt);
  estado_semaforos[0] = strtol(argv[1], NULL, 10);
  estado_semaforos[1] = strtol(argv[2], NULL, 10);
  estado_semaforos[2] = strtol(argv[3], NULL, 10);
  ubicacion_semaforos[0] = strtol(argv[4], NULL, 10);
  ubicacion_semaforos[1] = strtol(argv[5], NULL, 10);
  ubicacion_semaforos[2] = strtol(argv[6], NULL, 10);
  ubicacion_bodega = strtol(argv[7], NULL, 10);
  int ultimo = strtol(argv[8], NULL, 10);
  int parent_pid = strtol(argv[9], NULL, 10);
  id_repartidor = strtol(argv[10], NULL, 10);
  printf("I'm the REPARTIDOR process and my PID is: %i and my ID is: %i\n", getpid(), id_repartidor);
  sleep(1);
  while (true)
  {
    if (distancia < ubicacion_semaforos[0])
    {
      cant_turnos[0]++;
      cant_turnos[1]++;
      cant_turnos[2]++;
      cant_turnos[3]++;
      // printf("entro al primer caso distancia %i\n", distancia);
    }
    else if ((ubicacion_semaforos[0] <= distancia) && (distancia < ubicacion_semaforos[1]))
    {
      cant_turnos[1]++;
      cant_turnos[2]++;
      cant_turnos[3]++;
      // printf("entro al segundo caso distancia %i\n", distancia);
    }
    else if ((ubicacion_semaforos[1] <= distancia) && (distancia < ubicacion_semaforos[2]))
    {
      cant_turnos[2]++;
      cant_turnos[3]++;
      // printf("entro al tercer caso distancia %i\n", distancia);
    }
    else if ((ubicacion_semaforos[2] <= distancia) && (distancia < ubicacion_semaforos[3]))
    {
      cant_turnos[3]++;
      // printf("entro al cuarto caso distancia %i\n", distancia);
    }
    else
    {
      printf("Repartidor %i llegó a la bodega\n", id_repartidor);
      if (ultimo)
      {
        kill(parent_pid, SIGUSR2);
      }
      while(true);
      
    }
    if (distancia == ubicacion_semaforos[0] - 1)
    {
      if (estado_semaforos[0])
      {
        distancia++;
        // printf("Repartidor %i: Semaforo 1 verde ubicado en %i\n", id, distancia);
      }
      else
      {
        // printf("Repartidor %i: Semaforo 1 rojo ubicado en %i\n", id, distancia);
      }
    }
    else if (distancia == ubicacion_semaforos[1] - 1)
    {
      if (estado_semaforos[1])
      {
        distancia++;
        // printf("Repartidor %i: Semaforo 2 verde ubicado en %i\n", id, distancia);
      }
      else
      {
        // printf("Repartidor %i: Semaforo 2 rojo ubicado en %i\n", id, distancia);
      }
    }
    else if (distancia == ubicacion_semaforos[2] - 1)
    {
      if (estado_semaforos[2])
      {
        distancia++;
        // printf("Repartidor %i: Semaforo 3 verde ubicado en %i\n", id, distancia);
      }
      else
      {
        // printf("Repartidor %i: Semaforo 3 rojo ubicado en %i\n", id, distancia);
      }
    }
    else
    {
      distancia++;
    }
    sleep(1);
  };
}
