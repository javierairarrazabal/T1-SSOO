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
  pid_t* semaforos_id = calloc(3, sizeof(pid_t));
  int cant_repartidores = strtol(data_in->lines[1][1], NULL, 10);
  pid_t* repartidores_id = calloc(cant_repartidores, sizeof(pid_t));;
  
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
      semaforos_id[i] = fork();
      if (!semaforos_id[i])
      {
        printf("Hola soy el semaforo %d\n", i);
        char *myargs[5];
        char id_semaforo = i+'0';
        char parent_id = fabrica_id+'0';
        myargs[0] = strdup("./semaforo");
        myargs[1] = id_semaforo;
        myargs[2] = data_in->lines[1][2+i];
        myargs[3] = parent_id;
        myargs[4] = NULL;
        execvp(myargs[0], myargs);
      }
    }
    printf("Liberando memoria...\n");
    input_file_destroy(data_in);
    free(repartidores_id);
    free(semaforos_id);
  }
}
