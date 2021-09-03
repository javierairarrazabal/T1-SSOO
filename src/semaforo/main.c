#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

int main(int argc, char const *argv[])
{
  int parent_pid = strtol(argv[3], NULL, 10);
  int id = strtol(argv[1], NULL, 10);
  int delay = strtol(argv[2], NULL, 10);
  bool prendido = true;
  printf("I'm the SEMAFORO process and my PID is: %i\n", getpid());
  while (true)
  {
    sleep(delay);
    prendido = !prendido;
    printf("SEMAFORO %i prendido: %d\n", id, prendido);
  };
  
}
