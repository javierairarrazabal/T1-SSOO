#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "../file_manager/manager.h"

int main(int argc, char const *argv[])
{
  printf("I'm the DCCUBER process and my PID is: %i\n", getpid());

  char *filename = "input.txt";
  InputFile *data_in = read_file(filename);

  printf("Leyendo el archivo %s...\n", filename);
  printf("- Lineas en archivo: %i\n", data_in->len);
  printf("- Contenido del archivo:\n");

  printf("\t- ");
  for (int i = 0; i < 4; i++)
  {
    printf("%s, ", data_in->lines[0][i]);
  }
  printf("\n");

  printf("\t- ");
  for (int i = 0; i < 5; i++)
  {
    printf("%s, ", data_in->lines[1][i]);
  }
  printf("\n");

  // inicializar variables
  pid_t fabrica_pid;
  pid_t* semaforos_pid = calloc(3, sizeof(pid_t));
  int cant_repartidores = strtol(data_in->lines[1][1], NULL, 10);
  pid_t* repartidores_pid = calloc(cant_repartidores, sizeof(pid_t));
  char* fabrica_id = malloc(sizeof(char));
  // Crear fábrica
  fabrica_pid = fork();
  *fabrica_id = fabrica_pid;

  if (!fabrica_pid) // Solo el fabrica cumple el if
  {
    printf("Hola soy la fabrica\n");

    // Crear RePARTIDORES
    // for (int i = 0; i < cant_repartidores; i++)
    // {
    //   repartidores_id[i] = fork();
    //   execlp("../repartidor/main", "", NULL);
    // }
  } else {
    for (int i = 0; i < 3; i++)
    {
      semaforos_pid[i] = fork();
      if (!semaforos_pid[i])
      {
        printf("Hola soy el semaforo %d\n", i);
        char* myargs[5];
        //char id_semaforo = i+'0';
        //char parent_id = fabrica_id+'0';
        myargs[0] = strdup("./semaforo");
        myargs[1] = &i;
        myargs[2] = data_in->lines[1][2+i];
        myargs[3] = &fabrica_id;
        myargs[4] = NULL;
        execvp(myargs[0], myargs);
      }
    }
    printf("Liberando memoria...\n");
    input_file_destroy(data_in);
    free(repartidores_pid);
    free(semaforos_pid);
  }
}
