#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
  int mat1[10][10];
  int mat2[10][10];
  float inv[10][10];
  float determinant = 0;
  int id_pid;
  char lectura;
  unsigned char i,j,k,e,m,n;

  // Apuntadores a archivo en los cuales se guardarán los resultados de los procesos
  FILE *suma;
  FILE *resta;
  FILE *multiplic;
  FILE *transp;
  FILE *inversa;
  srand(time(NULL));

  // Abrimos los archivos
  if((suma = fopen("Suma","w")) == NULL)
    printf("Error al abrir el archivo de Suma\n");

  if((resta = fopen("Resta","w")) == NULL)
    printf("Error al abrir el archivo de Resta\n");

  if((multiplic = fopen("Multiplicación","w")) == NULL)
    printf("Error al abrir el archivo de Multiplicación\n");

  if((transp = fopen("Transpuesta","w")) == NULL)
    printf("Error al abrir el archivo de Transpuesta\n");

  if((inversa = fopen("Inversa","w")) == NULL)
    printf("Error al abrir el archivo de Inversa\n");

  // Llenamos la primera matriz
  for(i = 0; i < 10; i++)
  {
    for(j = 0; j < 10; j++)
      mat1[i][j] = rand() % 10;
  }

  // Llenamos la segunda matriz
  for(i = 0; i < 10; i++)
  {
    for(j = 0; j < 10; j++)
      mat2[i][j] = rand() % 10;
  }

  // Imprimimos la pimera matriz
  printf("  PRIMERA MATRIZ\n");
  for(i = 0; i < 10; i++)
  {
    for(j = 0; j < 10; j++)
      printf("%d ",mat1[i][j]);

    printf("\n");
  }

  printf("\n\n");

  // Imprimimos la segunda matriz
  printf("  SEGUNDA MATRIZ\n");
  for(i = 0; i < 10; i++)
  {
    for(j = 0; j < 10; j++)
      printf("%d ",mat2[i][j]);

    printf("\n");
  }
  printf("\n");


  // Realizamos la suma
  id_pid = fork();
  if(id_pid == 0)
  {
    fprintf(suma,"\t\t\t\tSuma de Matrices\n");
    for(i = 0; i < 10; i++)
    {
      for(j = 0; j < 10; j++)
      {
        fprintf(suma,"\t%d",mat1[i][j] + mat2[i][j]);
        fprintf(suma," ");
      }

      fprintf(suma,"\n");
    }
    fprintf(suma,"\n");
    fclose(suma);
    return 0;
  }

  // Realizamos la resta
  id_pid = fork();
  if(id_pid == 0)
  {
    fprintf(resta,"\t\t\t\tMatriz 1 - Matriz 2\n");
    for(i = 0; i < 10; i++)
    {
      for(j = 0; j < 10; j++)
      {
        fprintf(resta,"\t%d",mat1[i][j] - mat2[i][j]);
        fprintf(resta," ");
      }

      fprintf(resta,"\n");
    }

    fprintf(resta,"\n\t\t\t\tMatriz 2 - Matriz 1\n");
    for(i = 0; i < 10; i++)
    {
      for(j = 0; j < 10; j++)
      {
        fprintf(resta,"\t%d",mat2[i][j] - mat1[i][j]);
        fprintf(resta," ");
      }

      fprintf(resta,"\n");
    }
    fprintf(resta,"\n");
    fclose(resta);
    return 0;
  }

  // Realizamos la multiplicación
  id_pid = fork();
  if(id_pid == 0)
  {
      int res;
      fprintf(multiplic,"\t\t\t\tMultiplicación de Matrices\n");
      for(i = 0; i < 10; i++)
      {
        for(j = 0; j < 10; j++)
        {
          res = 0;
          for(k = 0; k < 10; k++)
          {
            res += mat1[i][k] * mat2[k][j];
          }
          fprintf(multiplic,"\t%d",res);
        }
        fprintf(multiplic,"\n");
      }
      fprintf(multiplic,"\n");
      fclose(multiplic);
      return 0;
  }

  // Realizamos la transpuesta
  id_pid = fork();
  if(id_pid == 0)
  {
    // Hacemos la transpuesta de la matriz 1
    fprintf(transp,"\t\t\tTRANPUESTA DE LA PRIMERA MATRIZ\n");
    for(i = 0; i < 10; i++)
    {
      for(j = 0; j < 10; j++)
      {
        fprintf(transp,"\t%d",mat1[j][i]);
      }
      fprintf(transp,"\n");
    }
    fprintf(transp,"\n");

    // Hacemos la transpuesta de la matriz 2
  fprintf(transp,"\t\t\tTRANPUESTA DE LA SEGUNDA MATRIZ\n");
    for(i = 0; i < 10; i++)
    {
      for(j = 0; j < 10; j++)
      {
        fprintf(transp,"\t%d",mat2[j][i]);
      }
      fprintf(transp,"\n");
    }
    fprintf(transp,"\n");
    fclose(transp);
    return 0;
  }

  // Realizamos la matriz inversa
  id_pid = fork();
  if(id_pid == 0)
  {
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

      fclose(inversa);
      return 0;
  }

  // Leemos los resultados de los archivos y los imprimimos en pantalla
  id_pid = fork();
  if(id_pid == 0)
  {
    FILE *a;

    // Imprimimos la Suma
    a = fopen("Suma","r");
    if(a == 0)
      printf("Error al abrir el archivo de Suma\n");

    else
    {
      while((lectura = fgetc(a)) != EOF)
        printf("%c",lectura);
    }
    fclose(a);

    // Imprimimos la Resta
    a = fopen("Resta","r");
    if(a == 0)
      printf("Error al abrir el archivo de Suma\n");

    else
    {
      while((lectura = fgetc(a)) != EOF)
        printf("%c",lectura);
    }
    fclose(a);

    // Imprimimos la Multiplicación
    a = fopen("Multiplicación","r");
    if(a == 0)
      printf("Error al abrir el archivo de Suma\n");

    else
    {
      while((lectura = fgetc(a)) != EOF)
        printf("%c",lectura);
    }
    fclose(a);

    // Imprimimos la Transpuesta
    a = fopen("Transpuesta","r");
    if(a == 0)
      printf("Error al abrir el archivo de Suma\n");

    else
    {
      while((lectura = fgetc(a)) != EOF)
        printf("%c",lectura);
    }
    fclose(a);

    // Imprimimos la Inversa
    a = fopen("Inversa","r");
    if(a == 0)
      printf("Error al abrir el archivo de Suma\n");

    else
    {
      while((lectura = fgetc(a)) != EOF)
        printf("%c",lectura);
    }
    fclose(a);
    return 0;
  }

  return 0;
}
