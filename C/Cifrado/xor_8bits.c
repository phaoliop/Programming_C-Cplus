/**
	Autor: PaoloRamirez
	Tema: Aplicar XOR a una cadena con una clave de 8bits
	Link: https://www.facebook.com/PaoloProgrammer/
**/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
 
int main(int argc, char *argv[])
{
	if(argc!=3)
	{
		perror("Insertar 2 parametros (p1:texto, p2:clave)");
		exit(0);
	}

	int len_texto,len_clave;
	len_texto=strlen(argv[1]);
	len_clave=strlen(argv[2]);

	/**
		Texto inicial
		Clave de cifrado
	**/
	//Tamaño de cadena = len+fincadena \0
	char texto[len_texto+1]; //L+R
	char clave[len_clave+1]; //Ki

	//Format
	memset(texto,0,sizeof(texto));
	memset(clave,0,sizeof(clave));

	//Copiar a variables
	strcpy(texto,argv[1]);
	strcpy(clave,argv[2]);

	printf("Texto: %s\n", texto);
	printf("Clave: %s\n\n", clave);

	//Aplicando XOR;  texto[i] XOR clave[0]
	int i;
	for (i = 0; i < len_texto; i++)
	{
		/* code */
		texto[i] = texto[i]^clave[0]; //Tomamos clave[0] pues la entrada solo deberia ser de 8bits=1 byte=1 caracter
	}

	printf("Texto cifrado: %s\n", texto);
}