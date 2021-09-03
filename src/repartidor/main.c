#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
  int id = strtol(argv[1], NULL, 10);
  printf("I'm the REPARTIDOR process and my PID is: %i, my id is %i\n", getpid(), id);
  exit(0);
}
