#include<stdio.h>
#include<stdlib.h>

void hanoi(int n, char origen, char destino, char aux)
{
    if (n == 1)
    {
        printf("\n Se movio el aro 1 de la torre %c a la torre %c", origen, destino);
        return;
    }
    hanoi(n-1, origen, aux, destino);
    printf("\n Se movio el aro %d de la torre %c a la torre %c", n, origen, destino);
    hanoi(n-1, aux, destino, origen);
}

int main(){
	int num;
	printf("Introduce el numero de aros \n");
	scanf("%d",&num);

	hanoi(num,'A','B','C');
    printf("\n");
}
