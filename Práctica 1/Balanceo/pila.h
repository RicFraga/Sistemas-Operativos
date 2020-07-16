#define TRUE 1
#define FALSE 0

typedef unsigned char boolean;

typedef struct elementos
{
  int valor;
  char caracter;
  struct nodos* arbol;
}elementos;

typedef struct nodos
{
  elementos e;
  struct nodos* abajo;
}nodos;

typedef struct pila
{
  nodos* tope;
}pila;

void InicializarPila(pila *s);
void Push(pila *s, elementos e);
void Pop(pila *s);
boolean PilaVacia(pila *s);
elementos Tope(pila *s);
void DestruirPila(pila *s);
