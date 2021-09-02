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
  pid_t fabrica_id;
  //pid_t *semaforos_id = calloc(3, sizeof(pid_t));
  pid_t semaforo_id;
  int cant_repartidores = strtol(data_in->lines[1][1], NULL, 10);
  pid_t *repartidores_id = calloc(cant_repartidores, sizeof(pid_t));
  int parent = 0;

  // Crear fábrica
  fabrica_id = fork();

  if (!fabrica_id) // Solo el fabrica cumple el if
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
      semaforo_id = fork();
      if (!semaforo_id)
      {
        printf("Hola soy la semaforo %d\n", i);
        //execlp("../semaforo/main", "", NULL);
      } else {
        parent = 1;
      }
    }
    if (parent)
    {
      printf("Liberando memoria...\n");
      input_file_destroy(data_in);
      free(repartidores_id);
    }
  }

  
}
