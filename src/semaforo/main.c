#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>

int cambios = 0;
int id;

void handle_sigabrt(int sig)
{
  printf("Semaforo %i ESCRIBIR ARCHIVO Y SALIR\n", id);
  char file;
  sprintf(&file, "semaforo_%d.txt", id);
  FILE *output = fopen(file, "w");
  fprintf(output, "%i", cambios);
  fclose(output);
  printf("SEMAFORO YA ESCRIBIO\n");
  exit(0);
}

int main(int argc, char const *argv[])
{
  connect_sigaction(SIGABRT, handle_sigabrt);
  int parent_pid = strtol(argv[3], NULL, 10);
  id = strtol(argv[1], NULL, 10);
  int delay = strtol(argv[2], NULL, 10);
  bool prendido = true;
  printf("I'm the SEMAFORO process and my PID is: %i\n", getpid());
  while (true)
  {
    sleep(delay);
    prendido = !prendido;
    cambios++;
    send_signal_with_int(parent_pid, id);
  };
}
