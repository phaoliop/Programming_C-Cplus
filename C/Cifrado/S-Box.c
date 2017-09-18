/**
 Autor: PaoloRamirez
 Tema: S-Box o Cajas-S (ejemplo S-Box de 6x4bits)
 Link: https://www.facebook.com/PaoloProgrammer/
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	if(argc!=2)
	{
		perror("Insertar 1 parametro (p1:texto)");
		exit(0);
	}

	int len_texto,len_resultado;
	len_texto=strlen(argv[1]);
	len_resultado=len_texto*2/3;

	printf("\nresultado:%i\n", len_resultado);

	/**
		Texto inicial que ingresa al S-Box
	**/
	//Tamaño de cadena = len+fincadena \0
	char texto[len_texto+1];
	char resultado[len_resultado+1];

	//Format
	memset(texto,0,sizeof(texto));
	memset(resultado,0,sizeof(resultado));

	//Copiar a variable
	strcpy(texto,argv[1]);


	printf("Entrada: %s\n", texto);


	/**
		Tabla prefijada 6x4 bits
	**/
	char tabla[4][16]; //Externo x Interno


	tabla[0][0]=2;tabla[0][1]=12;tabla[0][2]=4;tabla[0][3]=1;tabla[0][4]=7;tabla[0][5]=10;tabla[0][6]=11;tabla[0][7]=6;
	tabla[0][8]=8;tabla[0][9]=5;tabla[0][10]=3;tabla[0][11]=15;tabla[0][12]=13;tabla[0][13]=0;tabla[0][14]=14;tabla[0][15]=9;
	tabla[1][0]=14;tabla[1][1]=11;tabla[1][2]=2;tabla[1][3]=12;tabla[1][4]=4;tabla[1][5]=7;tabla[1][6]=13;tabla[1][7]=1;
	tabla[1][8]=5;tabla[1][9]=0;tabla[1][10]=15;tabla[1][11]=12;tabla[1][12]=3;tabla[1][13]=9;tabla[1][14]=8;tabla[1][15]=6;
	tabla[2][0]=4;tabla[2][1]=2;tabla[2][2]=1;tabla[2][3]=11;tabla[2][4]=12;tabla[2][5]=13;tabla[2][6]=7;tabla[2][7]=8;
	tabla[2][8]=15;tabla[2][9]=9;tabla[2][10]=12;tabla[2][11]=5;tabla[2][12]=6;tabla[2][13]=3;tabla[2][14]=0;tabla[2][15]=14;
	tabla[3][0]=11;tabla[3][1]=8;tabla[3][2]=12;tabla[3][3]=7;tabla[3][4]=1;tabla[3][5]=14;tabla[3][6]=2;tabla[3][7]=13;
	tabla[3][8]=6;tabla[3][9]=15;tabla[3][10]=0;tabla[3][11]=9;tabla[3][12]=12;tabla[3][13]=4;tabla[3][14]=5;tabla[3][15]=3;

	/**
		Entrada[6] - Salida[4]
	**/

	int i,j,interno=0,externo=0; // variables "interno" y "externo" para acceder a la tabla prefijada
	int xbit=0x80; //variable temporal para saber el binario al aplicar un &
	int suma_int=0x8; //suma interna varia entre 0 y 15 (0x8 para iniciar sabiendo el bit en la posicion 4)
	int suma_ext=0x2; //suma externa varia entre 0 y 3  (0x2 para iniciar sabiendo el bit en la posicion 2)
	int cont=0;

	int ind_resultado=0; //indice de la variable resultado (que sera el resultado final)
	int temp_resultado;
	int agregar=0;

	for (i = 0; i < len_texto; i++)
	{

		for (j = 0; j < 8; j++)
		{			
			
			/**
				Obtener valores de "interno" y "externo"
			**/

			//Aplicar & para saber si existe el bit en esa posicion, donde xbit tiene como valor la posicion a evaluar
			if(texto[i] & xbit)
			{
				//Sumarle el valor de "suma_x" en caso exista el bit en esa posicion
				if(cont==0 || cont==5)
				{
					externo+=suma_ext;
				}
				else
				{
					interno+=suma_int;
				}
			}


			//Hacer desplazamiento a la derecha >>
			xbit=xbit>>1;

			//Bits 0 y 5 para externo
			if(cont==0)	{ suma_ext=suma_ext>>1;}

			//Bits 1,2,3,4 para interno
			else { suma_int=suma_int>>1; }

			//Control de 6 bits de entrada
			if (cont==5)
			{
				//Obtener primeros 4 bits
				if (agregar==0)
				{
					temp_resultado=tabla[externo][interno]<<4;
					agregar++;
				}
				//Obtener los siguientes 4 bits y agregar al resultado de salida
				else
				{
					temp_resultado+=tabla[externo][interno];
					resultado[ind_resultado]=temp_resultado;
					agregar=0;
					ind_resultado++;
				}
				//Test para mostrar valores de acceso a la tabla
				printf("Interno:%x - Externo:%x - Valor-Tabla:%x - %x\n", interno,externo,tabla[externo][interno],temp_resultado);

				//Inicializar variables cada 6 bits evaluados
				cont=0;
				suma_int=0x8;
				suma_ext=0x2;
				interno=0;
				externo=0;
			}
			else
			{
				cont++;
			}
		}
		//reiniciar temporal a bit 8: 0b1000 0000 -> 0x80 -> 128
		xbit=0x80;
	}
	printf("\nSalida: %s\n",resultado);
	
}
