#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
  int parent_pid = strtol(argv[3], NULL, 10);
  int id = strtol(argv[1], NULL, 10);
  int delay = strtol(argv[2], NULL, 10);
  printf("I'm the SEMAFORO process and my PID is: %i\n", getpid());
  printf("delay semaforo %d: %d\n", id, delay);
  printf("parent semaforo %d: %d\n", id, parent_pid);
}
