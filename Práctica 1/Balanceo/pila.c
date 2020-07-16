#include <stdio.h>
#include <stdlib.h>
#include "pila.h"

void InicializarPila(pila *s)
{
  s -> tope = NULL;
}


void Push(pila *s, elementos e)
{
  nodos *aux;
  aux = malloc(sizeof(nodos));

  if(aux == NULL)
  {
    printf("ERROR://void Push(pila *s, elemento e) No fue posible crear el nodo");
    exit(1);
  }

  aux -> e = e;
  aux -> abajo = s-> tope;
  s -> tope = aux;
}


void Pop(pila *s)
{
  if(s -> tope == NULL)
  {
    printf("ERROR://void Pop(pila *s) Subdesbordamiento de pila");
    exit(1);
  }

  s -> tope = s -> tope -> abajo;
  free(s->tope);
}

boolean PilaVacia(pila *s)
{
  boolean r = FALSE;

  if(s -> tope == NULL)
    r = TRUE;

  return r;
}

elementos Tope(pila *s)
{
  return s -> tope->e;
}

void DestruirPila(pila *s)
{
  if(s -> tope != NULL)
  {
    while(s -> tope != NULL)
    {
      s -> tope = s -> tope -> abajo;
      free(s -> tope);
    }
  }
}
