#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  int mat1[10][10];
  int mat2[10][10];
  int res;
  char lectura;
  unsigned char i,j,k;
  FILE *a;
  FILE *b;
  FILE *multiplic;

  a = fopen("Matriz 1","r");
  b = fopen("Matriz 2","r");
  multiplic = fopen("Multiplicación","w");

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
  fprintf(multiplic,"\tMultiplicación de Matrices\n");
  for(i = 0; i < 10; i++)
  {
    for(j = 0; j < 10; j++)
    {
      res = 0;
      for(k = 0; k < 10; k++)
        res += mat1[i][k] * mat2[k][j];

      fprintf(multiplic,"\t%d",res);
    }

    fprintf(multiplic,"\n");
  }

  fprintf(multiplic,"\n");
  fclose(multiplic);
  return 0;

  fclose(a);
  fclose(b);
  fclose(multiplic);

  return 0;
}
