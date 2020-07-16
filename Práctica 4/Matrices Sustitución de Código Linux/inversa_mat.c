#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  int mat1[10][10];
  int mat2[10][10];
  float determinant = 0;
  char lectura;
  unsigned char i,j;
  FILE *a;
  FILE *b;
  FILE *inversa;

  a = fopen("Matriz 1","r");
  b = fopen("Matriz 2","r");
  inversa = fopen("Inversa","w");

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

  // Realizamos la inversa de las matrices y la imprimimos en un archivo
  fprintf(inversa,"\tInversa de la Matriz 1\n");
  // Calculando el determinante de la matriz 1
  for(i = 0; i < 10; i++)
    determinant = determinant + (mat1[0][i] * (mat1[1][(i+1)%3] * mat1[2][(i+2)%3] - mat1[1][(i+2)%3] * mat1[2][(i+1)%3]));

   fprintf(inversa,"\tMatriz Inversa de la Matriz 1\n");
   for(i = 0; i < 10; i++)
   {
       for(j = 0; j < 10; j++)
          fprintf(inversa,"%.2f\t",((mat1[(j+1)%3][(i+1)%3] * mat1[(j+2)%3][(i+2)%3]) - (mat1[(j+1)%3][(i+2)%3] * mat1[(j+2)%3][(i+1)%3]))/ determinant);
       fprintf(inversa,"\n");
   }
   determinant = 0;
   // Calculando el determinante de la matriz 2
  for(i = 0; i < 10; i++)
    determinant = determinant + (mat2[0][i] * (mat2[1][(i+1)%3] * mat2[2][(i+2)%3] - mat2[1][(i+2)%3] * mat2[2][(i+1)%3]));

   fprintf(inversa,"\tMatriz Inversa de la Matriz 2\n");
   for(i = 0; i < 10; i++)
    {
       for(j = 0; j < 10; j++)
          fprintf(inversa,"%.2f\t",((mat2[(j+1)%3][(i+1)%3] * mat2[(j+2)%3][(i+2)%3]) - (mat2[(j+1)%3][(i+2)%3] * mat2[(j+2)%3][(i+1)%3]))/ determinant);
       fprintf(inversa,"\n");
   }

  fclose(a);
  fclose(b);
  fclose(inversa);

  return 0;
}
