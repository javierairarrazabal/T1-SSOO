#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
  int parent_pid = strtol(argv[3], NULL, 10);
  printf("I'm the SEMAFORO process and my PID is: %i\n", getpid());
  printf("delay semaforo %c: %c\n", *argv[1], *argv[2]);
  printf("parent semaforo %c: %d\n", *argv[1], parent_pid);
}
