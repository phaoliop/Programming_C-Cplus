#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define cluster_tamano 1024
#define sector_tamano 512
#define sector_por_cluster 2
#define linea 16

int main( int argc, char **argv){
	char acSector[cluster_tamano];
	int  iArchivo;
	int iLeido;
	int i,j;
	char c;
	int inum_cluster=0;
	int iPosSector;

	/* Abriendo el archivo */
	iArchivo=open(argv[2],O_RDONLY);
	if(argc<2)
	{
	perror("Faltan argumentos");
	exit(3);
	}

	/*Convertir el argv[1] a entero */
	inum_cluster= atoi(argv[1]);
	printf("Numero de cluster a leer:%i\n",inum_cluster);
	if(inum_cluster>=1431 || inum_cluster<0)
	{	
		perror("Cluster invalido.");
		exit(1);
	}
	/*Cambiando la posicion del cabezal de lectura*/
	//Moviendonos al cluster 0 (sector 18)
//	lseek(iArchivo,cluster_tamano*9,SEEK_SET);
	//Moviendonos al cluster indicado
	iPosSector=sector_tamano*(2*(inum_cluster-2)+18);
	lseek(iArchivo,iPosSector,SEEK_SET);


	/*Leyendo archivo desde la posicion actual*/
	iLeido=read(iArchivo,acSector,cluster_tamano);
	printf("Leidos:%i bytes.\n",iLeido);
	
	if(iLeido<=0)
	{
		perror("No se ha podido leer el cluster");
		exit(2);
	}	

	/*Tamaño a mostrar 512 bytes
	   Mostrando hexadecimal \t ASCCI */
	for(i=0;i<cluster_tamano/linea;i++)
	{	
		for(j=0;j<linea;j++)
		{
			c= acSector[i*linea +j];
			printf("%02x ",c & 0x00000FF);
		}

		for(j=0; j<linea; j++)
		{
			c= acSector[i*linea +j];
			if(isprint(c))
				{ printf("%c",c); }
			else
				{printf("-");}
		}

			printf("\n");
	}
	
	close(iArchivo);

}
