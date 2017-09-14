#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define sector_tamano 512
#define linea 16

int main( int argc, char **argv){
	char acSector[sector_tamano];
	int  iArchivo;
	int iLeido;
	int i,j;
	char c;
	int inum_sector=0;

	/* Abriendo el archivo */
	iArchivo=open(argv[1],O_RDONLY);

	/*Determinar donde hay caracteres*/
	for(j=0;j<1440;j++)
	{
	/*Cambiando la posicion del cabezal de lectura*/
	lseek(iArchivo,sector_tamano*j,SEEK_SET);

	/*Leyendo archivo desde la posicion actual*/
	iLeido=read(iArchivo,acSector,sector_tamano);
		
		for(i=0;i<sector_tamano;i++)
		{	
			c= acSector[i];
			if(c!=0)
			{
			printf("Sector no vacio:%i\n",j);
			i=sector_tamano;
			}
		}
	}
	
	close(iArchivo);

}
