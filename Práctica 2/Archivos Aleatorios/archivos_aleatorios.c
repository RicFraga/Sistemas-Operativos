#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>
extern int errno;

int main(void)
{
	int fd,status;
	char archivo[] = "Numero";	// (6)
	char *const mensaje = "Estamos que es lo importante";	//Cadena que se escribira en los archivos
	char directorio[] = "/home/ricardo/Documents/Materias/Sistemas Operativos/Práctica 2/Archivos Aleatorios/";
	char carpeta[16];
	char aux[100];

	printf("Ingresa el nombre de la carpeta que deseas crear: ");
	scanf("%s",carpeta);

	/*Creamos el directorio 0777 para que todo posible usuario tenga permisos
	sobre el directorio */
	status = mkdir(carpeta,0777);

	// Si no es posible crear el directorio mandamos un error
	if(status == -1)
	{
		printf("Error status : %d\n",errno);
		perror("Programa");
	}

	// Construimos las ruta en la que se guardaran los archivos
	strcpy(aux,directorio);
	strcat(aux,carpeta);
	strcat(aux,"/");

	for(unsigned char i = 0; i < 10; i++)
	{
		// Cambiamos el nombre del archivo para c/u de los que se van a crear
		archivo[6] = i + '0';

		// Reconstruimos las ruta en la que se guardaran los archivos
		strcpy(aux,directorio);
		strcat(aux,carpeta);
		strcat(aux,"/");
		strcat(aux,archivo);

		// Abrimos el archivo
		fd = open(aux, O_CREAT | O_WRONLY, 0644);

		// Si no es posible crearlo mandamos un error
		if(fd == -1)
		{
			printf("Error fd : %d\n",errno);
			perror("Programa");
		}

		// Escribimos el mensaje en los archivos
		write(fd,mensaje,strlen(mensaje));
		// Cerramos el archivo
		close(fd);
	}

  return 0;
}
