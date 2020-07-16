#include <stdio.h>
#include "pila.h"

#define longitud 30

int main(void)
{
  char expresion[longitud+1];
  unsigned char i;
  pila par1,par2,par3;  //par -> '()', par2 = '{}', par3 = '[]'
  elementos e;

  for(i = 0 ; i < longitud; i++)
    expresion[i] = '\0';

  printf("Ingresa la expresion a revisar (maximo %d caracteres): ",longitud);
  scanf("%s",expresion);

  InicializarPila(&par1);
  InicializarPila(&par2);
  InicializarPila(&par3);

  for(i = 0; i < longitud; i++)
  {
    // Para la forma '()'
    if(expresion[i] == '(')
    {
      e.caracter = expresion[i];
      Push(&par1,e);
    }

    else if(expresion[i] == ')')
      Pop(&par1);

    // Para la forma '{}'
    else if(expresion[i] == '{')
    {
      e.caracter = expresion[i];
      Push(&par2,e);
    }

    else if(expresion[i] == '}')
      Pop(&par2);

    // Para la forma '[]'
    else if(expresion[i] == '[')
    {
      e.caracter = expresion[i];
      Push(&par3,e);
    }

    else if(expresion[i] == ']')
      Pop(&par3);
  }

  if(!PilaVacia(&par1))
    printf("Los parentesis de la forma '()' no estan balanceados\n");

  else
    printf("Los parentesis de la forma '()' estan balanceados\n");

  if(!PilaVacia(&par2))
    printf("Los parentesis de la forma '{}' no estan balanceados\n");

  else
    printf("Los parentesis de la forma '{}' estan balanceados\n");

  if(!PilaVacia(&par3))
    printf("Los parentesis de la forma '[]' no estan balanceados\n");

  else
    printf("Los parentesis de la forma '[]' estan balanceados\n");
  return 0;

}
