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

void handle_sigusr1(int sig, siginfo_t *siginfo, void *context)
{
  int number_received = siginfo->si_value.sival_int;
  estado_semaforos[number_received] = !estado_semaforos[number_received];
  printf("Repartidor de pid %d: Recibi semaforo id %i en estado %i\n", getpid(), number_received, estado_semaforos[number_received]);
}

int main(int argc, char const *argv[])
{
  connect_sigaction(SIGUSR1, handle_sigusr1);
  int id = strtol(argv[1], NULL, 10);
  estado_semaforos[0] = strtol(argv[2], NULL, 10);
  estado_semaforos[1] = strtol(argv[3], NULL, 10);
  estado_semaforos[2] = strtol(argv[4], NULL, 10);
  ubicacion_semaforos[0] = strtol(argv[5], NULL, 10);
  ubicacion_semaforos[1] = strtol(argv[6], NULL, 10);
  ubicacion_semaforos[2] = strtol(argv[7], NULL, 10);
  ubicacion_bodega = strtol(argv[8], NULL, 10);
  printf("I'm the REPARTIDOR process and my PID is: %i, my id is %i\n", getpid(), id);
  printf("semaforo 1 %i, semaforo 2 %i, semaforo 3 %i, bodega %i\n", ubicacion_semaforos[0], ubicacion_semaforos[1], ubicacion_semaforos[2], ubicacion_bodega);
  while (true)
  {
    sleep(200);

  };
}
