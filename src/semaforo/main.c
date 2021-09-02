#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
  printf("I'm the SEMAFORO process and my PID is: %i\n", getpid());
  printf("id: %i\n", argv[1]);
  printf("delay: %i\n", argv[2]);
  printf("parent: %i\n", argv[3]);
}
