#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int matriz1[10][10], matriz2[10][10];
void* procesar(void* id);
void suma();
void resta();
void multi();
void inversa();
void transpuesta();
void imprimir();

int main (void)
{
	pthread_t *thread;
	int j,i,k;
	thread = malloc(6*sizeof(pthread_t));	

	for(j=0;j<10;j++){
		for(k=0;k<10;k++){
			matriz1[j][k]=rand()%10+1;
			matriz2[j][k]=rand()%10+1;
		}
	}

	for (i=1; i<6; i++) 
            {
                //Crear los threads que se comportaran segun la funcion procesar.

                if (pthread_create(&thread[i], NULL, procesar,(void*)i) != 0) 
                {
                    perror("El thread no  pudo crearse");
                    exit(-1);
                }
            }
    procesar(0);
      //  Esperar a que terminen los threads.
    for (i=1; i<6; i++) pthread_join (thread[i], NULL);


    exit(0);

}

void* procesar(void* id)
{   
    int n_thread=(int)id;

    if(n_thread==0) suma();
    else if (n_thread==1) resta();
    else if (n_thread==2) multi();
    else if (n_thread==3) transpuesta();
    else if (n_thread==4) inversa();
    else imprimir();

    pthread_exit(0);
    
}

void suma()
{

	char numeros[10];
	int j,k,m;
	FILE* suma= fopen("suma.txt", "wt");
	for(j=0;j<10;j++)
	{
		for(k=0;k<10;k++)
		{
			sprintf(numeros, "%d", matriz1[j][k]+matriz2[j][k]);
			fputs(numeros, suma);
			fputs("\t", suma);
			for(m=0;m<10;m++)
				numeros[m]='\0';
		}
		fputs("\n", suma);
	}
	fclose(suma);
}

void resta()
{
	char numeros[10];
	int j,k,m;
	FILE* resta= fopen("resta.txt", "wt");
	for(j=0;j<10;j++)
	{
		for(k=0;k<10;k++){
			sprintf(numeros, "%d", matriz1[j][k]-matriz2[j][k]);
			fputs(numeros, resta);
			fputs("\t", resta);
			for(m=0;m<10;m++)
				numeros[m]='\0';
		}
		fputs("\n", resta);
	}
	fclose(resta);
}

void multi()
{
	char numeros[10];
	int j,k,l,m,aux=0;
	FILE* multiplicacion= fopen("multiplicacion.txt", "wt");
	for(j=0;j<10;j++)
	{
		for(k=0;k<10;k++)
		{
			for(l=0;l<10;l++)
			{
				aux=aux+(matriz1[j][l]*matriz2[l][k]);
			}
			sprintf(numeros, "%d", aux);
			fputs(numeros, multiplicacion);
			fputs("\t", multiplicacion);
			for(m=0;m<10;m++)
				numeros[m]='\0';
			aux=0;
		}
			fputs("\n", multiplicacion);
	}
	fclose(multiplicacion);
}

void transpuesta()
{
	int j,k,m;
	char numeros[10];
	FILE* transpuesta1= fopen("transpuesta1.txt", "wt");
	for(j=0;j<10;j++){
		for(k=0;k<10;k++){
			sprintf(numeros, "%d", matriz1[k][j]);
			fputs(numeros, transpuesta1);
			fputs("\t", transpuesta1);
			for(m=0;m<10;m++)
				numeros[m]='\0';
		}
		fputs("\n", transpuesta1);
	}
	fclose(transpuesta1);
	
	//2
	FILE* transpuesta2= fopen("transpuesta2.txt", "wt");
	for(j=0;j<10;j++){
		for(k=0;k<10;k++){
			sprintf(numeros, "%d", matriz2[k][j]);
			fputs(numeros, transpuesta2);
			fputs("\t", transpuesta2);
			for(m=0;m<10;m++)
				numeros[m]='\0';
		}
		fputs("\n", transpuesta2);
	}
	fclose(transpuesta2);
}

void inversa()
{
	char numeros[10];
	int pivote, divisor=1, j,k,m,l;
	int anterior[10][20],matrizInversa1[10][20], matrizInversa2[10][20];
	
	for(j=0;j<10;j++){
		for(k=0;k<20;k++){
			if(k<10){
				matrizInversa1[j][k]=matriz1[j][k];
				matrizInversa2[j][k]=matriz2[j][k];
			}else{
				if(j+10==k)
				{
					matrizInversa1[j][k]=1;
					matrizInversa2[j][k]=1;
				}else{
					matrizInversa1[j][k]=0;
					matrizInversa2[j][k]=0;
				}
			}
		}
	}
	
	for(j=0;j<10;j++){
		pivote=matrizInversa1[j][j];
		for(k=0;k<10;k++){
			for(m=0; m<10; m++)
				for(l=0;l<20;l++){
					anterior[m][l]=matrizInversa1[m][l];
				}
			if(k!=j)
			for(l=0;l<20;l++){
				matrizInversa1[k][l]=((pivote*anterior[k][l])-(anterior[k][j]*anterior[j][l]))/(divisor);
			}
		}
		divisor=pivote;
	}
	
	FILE* inversa1= fopen("inversa1.txt", "wt");
	for(j=0;j<10;j++){
		for(k=10;k<20;k++){
			sprintf(numeros, "%d",matrizInversa1[j][k]);
			fputs(numeros, inversa1);
			fputs("\t", inversa1);
			for(m=0;m<10;m++)
				numeros[m]='\0';
		}
		fputs("\n", inversa1);
	}
	fputs("\nDividir entre: ", inversa1);
	sprintf(numeros, "%d",pivote);
	fputs(numeros, inversa1);
	fputs("\n", inversa1);
	for(m=0;m<10;m++)
		numeros[m]='\0';
	fclose(inversa1);
	
	divisor=1;
	for(j=0;j<10;j++){
		pivote=matrizInversa2[j][j];
		for(k=0;k<10;k++){
			for(m=0; m<10; m++)
				for(l=0;l<20;l++){
					anterior[m][l]=matrizInversa2[m][l];
				}
			if(k!=j)
			for(l=0;l<20;l++){
				matrizInversa2[k][l]=((pivote*anterior[k][l])-(anterior[k][j]*anterior[j][l]))/(divisor);
			}
		}
		divisor=pivote;
	}
	
	FILE* inversa2= fopen("inversa2.txt", "wt");
	for(j=0;j<10;j++){
		for(k=10;k<20;k++){
			sprintf(numeros, "%d",matrizInversa2[j][k]);
			fputs(numeros, inversa2);
			fputs("\t", inversa2);
			for(m=0;m<10;m++)
				numeros[m]='\0';
		}
		fputs("\n", inversa2);
	}
	fputs("\nDividir entre: ", inversa2);
	sprintf(numeros, "%d",pivote);
	fputs(numeros, inversa2);
	fputs("\n", inversa2);
	for(m=0;m<10;m++)
		numeros[m]='\0';

	fclose(inversa2);
}

void imprimir()
{
	FILE * lectura=fopen("suma.txt","rb");
	printf("Suma: \n\n");
	while( !feof(lectura) )
		printf("%c",getc(lectura));
	fclose(lectura);
	
	lectura=fopen("resta.txt","rb");
	printf("\n\nResta: \n\n");
	while( !feof(lectura) )
		printf("%c",getc(lectura));
	fclose(lectura);
	
	lectura=fopen("multiplicacion.txt","rb");
	printf("\n\nMultiplicacion: \n\n");
	while( !feof(lectura) )
		printf("%c",getc(lectura));
	fclose(lectura);
	
	lectura=fopen("transpuesta1.txt","rb");
	printf("\n\nTranspuesta1: \n\n");
	while( !feof(lectura) )
		printf("%c",getc(lectura));
	fclose(lectura);
	
	lectura=fopen("transpuesta2.txt","rb");
	printf("\n\nTranspuesta2: \n\n");
	while( !feof(lectura) )
		printf("%c",getc(lectura));
	fclose(lectura);
	
	lectura=fopen("inversa1.txt","rb");
	printf("\n\nInversa1: \n\n");
	while( !feof(lectura) )
		printf("%c",getc(lectura));
	fclose(lectura);
	
	lectura=fopen("inversa2.txt","rb");
	printf("\n\nInversa2: \n\n");
	while( !feof(lectura) )
		printf("%c",getc(lectura));
	fclose(lectura);
}
