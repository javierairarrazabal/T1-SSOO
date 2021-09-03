#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

#include "../file_manager/manager.h"

/** Connects a signal to a more powerful handler
 *
 * @param sig: Received signal (ex: SIGUSR1)
 * @param handler: Function to be called when the signal is received
*/

void handle_sigalarm(int sig)
{
  printf("alarma");
  // char *filename = "input.txt";
  // InputFile *data_in = read_file(filename);
  // int cantidad_restante = strtol(data_in->lines[1][1], NULL, 10);
  // int tiempo_generacion = strtol(data_in->lines[1][0], NULL, 10);
  // pid_t repartidor_pid;

  // for (int i = 1; i < cantidad_restante; i++)
  // {
  //   repartidor_pid = fork();
  //   if (!repartidor_pid)
  //   {
  //     char* myargs[3];
  //     sprintf(&repartidor_pid, "%d", i);
  //     myargs[0] = strdup("./repartidor");
  //     myargs[1] = &repartidor_pid;
  //     myargs[2] = NULL;
  //     execvp(myargs[0], myargs);
  //   }
  //   sleep(tiempo_generacion);
  // }
  
}

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
  char* pid_parent = malloc(sizeof(char));
  char* repartidores_id = calloc(cant_repartidores, sizeof(char));
  int status;
  // Crear fábrica
  fabrica_pid = fork();

  if (!fabrica_pid) // Solo el fabrica cumple el if
  {
    printf("Hola soy la fabrica mi pid es %i\n", getpid());
    // // Crear RePARTIDORES
    repartidores_pid[0] = fork();
    if (!repartidores_pid[0])
    {
      char* myargs[3];
      sprintf(&repartidores_id[0], "%d", 0);
      myargs[0] = strdup("./repartidor");
      myargs[1] = &repartidores_id[0];
      myargs[2] = NULL;
      execvp(myargs[0], myargs);
    } else {
      signal(SIGALRM, handle_sigalarm);
      alarm(1);
    }
  } else {
    sprintf(pid_parent, "%d", fabrica_pid);
    for (int i = 0; i < 3; i++)
    {
      semaforos_pid[i] = fork();
      if (!semaforos_pid[i])
      {
        char* myargs[5];
        char id_semaforo = i+'0';
        myargs[0] = strdup("./semaforo");
        myargs[1] = &id_semaforo;
        myargs[2] = data_in->lines[1][2+i];
        myargs[3] = pid_parent;
        myargs[4] = NULL;
        execvp(myargs[0], myargs);
      }
    }
    //waitpid(fabrica_pid, &status, 0);
    printf("Liberando memoria...\n");
    input_file_destroy(data_in);
    //free(repartidores_pid);
    //free(semaforos_pid);
  }
}
