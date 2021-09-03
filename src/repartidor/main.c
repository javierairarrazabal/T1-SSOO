// #include <stdio.h>
// #include <unistd.h>
// #include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdbool.h>

bool* semaforos[3];

int main(int argc, char const *argv[])
{
  //connect_sigaction(SIGUSR1, handle_sigusr1);
  int id = strtol(argv[1], NULL, 10);
  int semaforo0 = strtol(argv[2], NULL, 10);
  int semaforo1 = strtol(argv[3], NULL, 10);
  int semaforo2 = strtol(argv[4], NULL, 10);
  semaforos[0] = &semaforo0;
  semaforos[1] = &semaforo1;
  semaforos[2] = &semaforo2;
  int distancia = 0;
  printf("I'm the REPARTIDOR process and my PID is: %i, my id is %i\n", getpid(), id);
  int semaforo = 0;
  sleep(200);
}
