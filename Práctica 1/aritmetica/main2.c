#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "TADArbolBin.h"

#define longitud 31   // Longitud maxima de la expresion a evaluar

/* REGLAS DE EVALUACION:
    - Si se lee un ( se agrega un nuevo nodo como hijo izquierdo del nodo actual
    - Si se lee un operando (+,-,*,/) se añade al nodo actual, se crea un hijo
      derecho y se mueve la posicio a este
    - Si se lee un numero se añade el valor al nodo actual y se mueve la posicion
      al padre de este nodo
    - Si se lee un ) se mueve la posicion al padre del nodo actual
    - Una vez terminada la construccion del arbol se procede a realizar un recorrido
      postorden para realizar la evaluacion */

/* Funcion para recorrer el arbol (postorden) e ir operando los valores en el mismo
   Recibe: un apuntador a arbol y una posicion p
   Devuelve: un flotante resultado de evaluar la expresion guardada en el arbol */
float RecorridoDeEvaluacion(arbol_bin *a,posicion p);

int main(void)
{
  char expresion[longitud];
  unsigned char i;  // auxiliar para los ciclos
  arbol_bin arbol;
  elementoa e;    // elemento auxiliar para almacenar datos en el arbol
  posicion p;     // posicion auxiliar para recorrer el arbol binario

  // Llenamos la expresion de caracteres nulos para evitar guardar basura
  for(i = 0; i < longitud; i++)
    expresion[i] = '\0';

  // Inicializamos el arbol y creamos el nodo raiz
  Initialize(&arbol);
  NewLeftSon(&arbol,p,e);
  p = Root(&arbol);

  printf("Recuerda que la expresion debe estar totalmente contenida entre parentesis\n");
  printf("Ingresa la expresion a evaluar (maximo %d caracteres): ",longitud-1);
  scanf("%s",expresion);

  // Recorremos la expresion para leerla
  for(i = 0; i < longitud; i++)
  {
    if(expresion[i] == '\0')
      break;

    // Si encontramos un ( creamos un nuevo nodo como hijo del actual
    else if(expresion[i] == '(')
    {
      e.caracter = '\0';
      NewLeftSon(&arbol,p,e);
      p = LeftSon(&arbol,p);
    }

    /* Si leemos un operador lo asignamos al nodo actual, creamos un hijo derecho
       y movemos la posicion a este nuevo hijo
    POR VALORES DE ASCII
        - 42 = *
        - 43 = +
        - 45 = -
        - 47 = /  */
    else if(expresion[i] == 42 || expresion[i] == 43 || expresion[i] == 45 || expresion[i] == 47)
    {
      e.caracter = expresion[i];
      ReplaceNode(&arbol,p,e);
      e.caracter = '\0';
      NewRightSon(&arbol,p,e);
      p = RightSon(&arbol,p);
    }

    // Si leemos un numero se añade el valor al nodo actual y se mueve la posicion al padre de este
    else if(isdigit(expresion[i]))
    {
      if(expresion[i] == 48)
        e.valor = 0;

      else if(expresion[i] == 49)
        e.valor = 1;

      else if(expresion[i] == 50)
        e.valor = 2;

      else if(expresion[i] == 51)
        e.valor = 3;

      else if(expresion[i] == 52)
        e.valor = 4;

      else if(expresion[i] == 53)
        e.valor = 5;

      else if(expresion[i] == 54)
        e.valor = 6;

      else if(expresion[i] == 55)
        e.valor = 7;

      else if(expresion[i] == 56)
        e.valor = 8;

      else if(expresion[i] == 57)
        e.valor = 9;

      ReplaceNode(&arbol,p,e);
      p = Parent(&arbol,p);
    }

    // Si se lee un ) se mueve la posicion al padre del nodo actual
    else if(expresion[i] == ')')
    {
      if(Root(&arbol) != p)
          p = Parent(&arbol,p);
    }

    /* Si no entra a ninguna de las condiciones anteriores entonces el caracter no es valido para
    evaluar */
    else
    {
      printf("ERROR:// Se ingreso un caracter invalido para evaluar: %c\n",expresion[i]);
      exit(1);
    }

    //e.valor = 0;
    //e.caracter = '\0';
  }

  p = Root(&arbol);
  printf("Resultado = %f\n",RecorridoDeEvaluacion(&arbol,p));

  return 0;
}

float RecorridoDeEvaluacion(arbol_bin *a,posicion p)
{
	elementoa e;
  float resul;
	if(!NullNode(a,p))
	{
		e = ReadNode(a,p);
    resul = e.valor;

    if(e.caracter == '+')
      resul = RecorridoDeEvaluacion(a,LeftSon(a,p)) + RecorridoDeEvaluacion(a,RightSon(a,p));

    else if(e.caracter == '-')
      resul = RecorridoDeEvaluacion(a,LeftSon(a,p)) - RecorridoDeEvaluacion(a,RightSon(a,p));

    else if(e.caracter == '*')
      resul = RecorridoDeEvaluacion(a,LeftSon(a,p)) * RecorridoDeEvaluacion(a,RightSon(a,p));

    else if(e.caracter == '/')
      resul = RecorridoDeEvaluacion(a,LeftSon(a,p)) / RecorridoDeEvaluacion(a,RightSon(a,p));
	}

	return resul;
}
