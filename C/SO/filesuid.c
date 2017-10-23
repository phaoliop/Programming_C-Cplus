/**
	Autor: PaoloRamirez
	Tema: Ejemplo de escala de privilegios de archivos con el bit suid activo
	Link: https://www.facebook.com/PaoloProgrammer/
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SBUFFER 256

int main (int argc, char **argv)
{
	char buffer[SBUFFER];
	char comando[SBUFFER];
	do
	{
		memset(buffer, 0, sizeof(buffer)); //Format buffer
		memset(comando, 0, sizeof(comando)); //Format buffer

		printf("my_shell > ");
		fgets(buffer, SBUFFER, stdin); //Obtener comando shell

		system(buffer); //Ejecutar comando shell
	}
	while(strcmp(buffer,"salir\n")!=0);

}