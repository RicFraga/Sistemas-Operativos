#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
  pid_t pid;
  char lectura;
  char *argv[3];
  unsigned char i,j;
  FILE *a;
  FILE *b;
  argv[0] = "/home/ricardo/Documents/Materias/Sistemas Operativos/Práctica 4/Matrices Sustitución de Código Linux/suma_mat";
  argv[1] = "Se creo el hijo encargado de sumar";
  argv[2] = NULL;
  srand(time(NULL));

  // Abrimos los archivos para guardar las matrices
  if((a = fopen("Matriz 1","w")) == NULL)
  {
    printf("Error al abrir el archivo de la matriz 1\n");
    return 0;
  }

  if((b = fopen("Matriz 2","w")) == NULL)
  {
    printf("Error al abrir el archivo de la matriz 2\n");
    return 0;
  }

  // Llenamos la primera matriz
  for(i = 0; i < 10; i++)
  {
    for(j = 0; j < 10; j++)
      fprintf(a,"%d",rand()%10);
  }

  // Llenamos la segunda matriz
  for(i = 0; i < 10; i++)
  {
    for(j = 0; j < 10; j++)
      fprintf(b,"%d",rand()%10);
  }

  // Creamos un hijo que realice la suma
  if((pid = fork()) == 0)
    execv(argv[0],argv);

  // Creamos un hijo que realice la resta
  argv[0] = "/home/ricardo/Documents/Materias/Sistemas Operativos/Práctica 4/Matrices Sustitución de Código Linux/resta_mat";
  argv[1] = "Se creo el hijo encargado de restar";
  if((pid = fork()) == 0)
    execv(argv[0],argv);

  // Creamos un hijo que realice la multiplicación
  argv[0] = "/home/ricardo/Documents/Materias/Sistemas Operativos/Práctica 4/Matrices Sustitución de Código Linux/multiplic_mat";
  argv[1] = "Se creo el hijo encargado de multiplicar";
  if((pid = fork()) == 0)
    execv(argv[0],argv);

    // Creamos un hijo que realice la transpuesta
    argv[0] = "/home/ricardo/Documents/Materias/Sistemas Operativos/Práctica 4/Matrices Sustitución de Código Linux/transp_mat";
    argv[1] = "Se creo el hijo encargado de hacer las transpuestas";
    if((pid = fork()) == 0)
      execv(argv[0],argv);

    // Creamos un hijo que realice la inversa
    argv[0] = "/home/ricardo/Documents/Materias/Sistemas Operativos/Práctica 4/Matrices Sustitución de Código Linux/inversa_mat";
    argv[1] = "Se creo el hijo encargado de hacer las inversas";
    if((pid = fork()) == 0)
      execv(argv[0],argv);

  return 0;
}
