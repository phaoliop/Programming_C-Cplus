/**
	Autor: PaoloRamirez
	Tema: Cifrado de Feistel
	Link: https://www.facebook.com/PaoloProgrammer/
**/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void fun_aplicada(char dato[],char pwd);
void fun_xor(char dato1[], char dato2[]);

int main(int argc, char **argv)
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
	printf("Clave: %s\n\n\n", clave);

	/**
		CIFRADO
	**/
	char izquierda[(len_texto/2)+1]; //L
	char derecha[(len_texto/2)+1]; //R

	//Format
	memset(izquierda,0,sizeof(izquierda));
	memset(derecha,0,sizeof(derecha));

	strncpy(izquierda,texto,len_texto/2);
	strcpy(derecha,texto+len_texto/2);

	//Valores iniciales
	//printf("Texto[0]---> L(0) = %s\tR(0) = %s\n", izquierda, derecha);

	//Ciclo iterativo de L0-N y R0-N)
	int i;
	char temp_fun[(len_texto/2)+1];
	char temp_xor[(len_texto/2) +1];
	memset(temp_fun,0,sizeof(temp_fun));
	memset(temp_xor,0,sizeof(temp_xor));


	for (i = 0; i < len_texto; i++)
	{
		//Asignar a Li+1 <- Ri
		strcpy(temp_xor,izquierda); //Obtengo en temp_xor: Li
		strcpy(izquierda,derecha); //Obtengo en izquierda: Li+1

		//Aplicar f(Ri, Ki) ; donde Ri: derecha , Ki: clave
		strcpy(temp_fun,derecha);
		fun_aplicada(temp_fun,clave[i]); //Obtengo en temp_fun: f(Ri, Ki)

		//Aplicar XOR: Li XOR f(Ri,Ki)
		fun_xor(temp_xor,temp_fun); //Obtengo en temp_xor: Li XOR f(Ri,Ki)

		//Asignar a Ri+1 <- Resultado de Li XOR f(Ri,Ki)
		strcpy(derecha,temp_xor); //Obtengo en derecha: Ri+1

		//Mostrar valores i+1
		//printf("Texto[%i]---> L(%i) = %s\tR(%i) = %s\n", i+1, i+1, izquierda, i+1, derecha);
	}

	printf("Cifrado: L() = %s\tR() = %s\n", izquierda, derecha);
	printf("%s\n", "--------------------------------------");

	/**
		DESCRIFRADO
	**/
	for (i = len_texto-1; i >= 0; i--)
	{
		//Asignar a Ri-1 <- Li
		strcpy(temp_xor,derecha); //Obtengo en temp_xor: Ri
		strcpy(derecha,izquierda); //Obtengo en derecha: Ri-1

		//Aplicar f(Li, Ki) ; donde Li: izquierda , Ki: clave
		strcpy(temp_fun,izquierda);
		fun_aplicada(temp_fun,clave[i]); //Obtengo en temp_fun: f(Li, Ki)

		//Aplicar XOR: Ri XOR f(Li,Ki)
		fun_xor(temp_xor,temp_fun); //Obtengo en temp_xor: Ri XOR f(Li,Ki)

		//Asignar a Li-1 <- Resultado de Ri XOR f(Li,Ki)
		strcpy(izquierda,temp_xor); //Obtengo en izquierda: Li-1

		//Mostrar valores i+1
		//printf("Texto[%i]---> L(%i) = %s\tR(%i) = %s\n", i, i, izquierda, i, derecha);
	}

	printf("Descrifrado: L() = %s\tR() = %s\n", izquierda, derecha);
	printf("%s\n", "--------------------------------------");
}


//Ascii dato[i] + Ascii residuo pwd/17
void fun_aplicada(char dato[],char pwd)
{
	int len_dato;
	len_dato = strlen(dato);
	int pwd_ki;
	pwd_ki= pwd%17;

	int i;
	for (i = 0; i < len_dato; i++)
	{
		dato[i] = dato[i] + pwd_ki;
	}
}


void fun_xor(char dato1[], char dato2[])
{
	int tam;
	tam = strlen(dato1);

	int i;
	for (i = 0; i < tam; i++)
	{
		dato1[i] = dato1[i]^dato2[i];
	}
}
