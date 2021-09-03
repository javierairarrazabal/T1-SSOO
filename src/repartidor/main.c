// #include <stdio.h>
// #include <unistd.h>
// #include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdbool.h>

void handle_sigusr1(int sig, siginfo_t *siginfo, void *context)
{
  int number_received = siginfo->si_value.sival_int;
  printf("Hijo: Recibi %i\n", number_received);
}

int main(int argc, char const *argv[])
{
  //connect_sigaction(SIGUSR1, handle_sigusr1);
  int id = strtol(argv[1], NULL, 10);
  int turnos[4];
  turnos[0] = 0;
  turnos[1] = 0;
  turnos[2] = 0;
  turnos[3] = 0;
  int distancia = 0;
  printf("I'm the REPARTIDOR process and my PID is: %i, my id is %i\n", getpid(), id);
  int semaforo = 0;
  sleep(200);
}
