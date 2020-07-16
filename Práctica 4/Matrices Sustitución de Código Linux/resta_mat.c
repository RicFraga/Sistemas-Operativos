#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  int mat1[10][10];
  int mat2[10][10];
  char lectura;
  unsigned char i,j;
  FILE *a;
  FILE *b;
  FILE *resta;

  a = fopen("Matriz 1","r");
  b = fopen("Matriz 2","r");
  resta = fopen("Resta","w");

  printf("%s\n",argv[1]);

  // Leemos los valores de la matriz 1
  for(i = 0; i < 10; i++)
  {
    for(j = 0; j < 10; j++)
      if((lectura = fgetc(a)) != EOF)
        mat1[i][j] = (int)lectura - 48;
  }

  // Leemos los valores de la matriz 2
  for(i = 0; i < 10; i++)
  {
    for(j = 0; j < 10; j++)
      if((lectura = fgetc(b)) != EOF)
        mat2[i][j] = (int)lectura - 48;
  }

  // Realizamos la suma de las matrices y la imprimimos en un archivo
  fprintf(resta,"\tResta de Matrices\n");
  for(i = 0; i < 10; i++)
  {
    for(j = 0; j < 10; j++)
      fprintf(resta,"%d ",mat1[i][j] - mat2[i][j]);

    fprintf(resta,"\n");
  }

  fclose(a);
  fclose(b);
  fclose(resta);

  return 0;
}
