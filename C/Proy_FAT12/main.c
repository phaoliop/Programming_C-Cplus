#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "funfat.h"

/**
Definirlos en BIG-ENDIAN
**/
#define SALTO_RUTINA 0x903CEB
#define FABRICANTE 0x73666B6D
#define NUM_VERSION 0x7461662E

#define SECTORES_RESERVADOS 0x1
#define NUM_FATS 0x2

#define MEDIA_DESCRIPTOR 0xF9

#define NCABEZALES_RDWR 0x2

#define NSECTORES_OCULTOS 0x0
#define NSECTORES_PARTICION 0x0
#define NUM_DISP_FISICO 0x0
#define CABEZAL_ACTUAL 0x0

#define FIRMA_SO 0x29
#define ID_VOLUMEN 0x08D2FF6E
#define VERSION "FAT12"

#define FIN_SECTOR 0x1F0E
#define INI_FIN_RUTINA 0x5BBE
#define SIZE_RUTINA 0x7c

#define SECTOR_FIN 0xAA55

//Inicio FAT'S
#define INICIO_FAT 0xfffff9

int main (int argc,char **argv)
{
// ./fat12 [nom_disco] [bytes_sector] [sector_por_cluster] [entradas_dirRaiz] [num_Sectores] [nom_Salida.fat]

	int i;
/**
Datos ingresados
**/
	if(argc<7)
	{
		perror("Argumentos");
		exit(1);
	}

	int bytesporSector;
	bytesporSector=atoi(argv[2]);

	int nsectorporCluster;
	nsectorporCluster=atoi(argv[3]);

	int size_cluster;
	//Definiendo tamaño del cluster
	size_cluster=nsectorporCluster*bytesporSector;

	int numEntradas;
	int nSectoresDirRaiz;
	numEntradas=atoi(argv[4]);
	
	int numSectores;
	//Numero de sectores*Numero head's (por la media descriptor)
	numSectores=atoi(argv[5])*2;
	
	int nSectoresDisponibles;
	int numSectoresporFAT;
	int numSectoresporPISTA;
/**
Validando datos ingresados
**/
	//Bytes por sector
	if(bytesporSector%512!=0)
	{
		perror("Bytes por sector");
		exit(2);
	}
	//Entradas en el directorio raiz
	if((numEntradas*32)%bytesporSector!=0)
	{
		perror("Numero entradas");
		exit(3);
	}
	//Calculando el numero de sectores del Directorio Raiz
	nSectoresDirRaiz=numEntradas*32/bytesporSector;
	
	//Calculando el numero de sectores restantes
	nSectoresDisponibles=numSectores-(5*2)-nSectoresDirRaiz-1;
	//Calculando numero de Sectores que ocupará la FAT
	int numClusterDisponibles=(nSectoresDisponibles/2);
	numSectoresporFAT=(numClusterDisponibles*(1.5)/510)+1;
	//Calculando numero de Sectores por pista
	numSectoresporPISTA=atoi(argv[5])/80;

/**
Mostrando informacion
**/
	printf("Archivo generado: %s\n",argv[6]);
	printf("Tamaño logico del sector es %i con %i sectores en total,\n",bytesporSector,numSectores);
	printf("Tamaño del cluster es %i con %i sectores por cluster;\n",size_cluster,nsectorporCluster);
	printf("FAT usa %i sectores, y proporciona %i sectores.\n",numSectoresporFAT,nSectoresDisponibles/2);
	printf("El directorio raiz contiene %i slots y usa %i sectores.\n",numEntradas,nSectoresDirRaiz);
	printf("El ID del volumen es %02x, nombre del volumen %s.\n",ID_VOLUMEN,argv[1]);


/**
Rutina
**/
	//24 bytes
	int rutina0[6]={0x74c022ac, 0xeb4560b, 0xcd0007bb, 0xf0eb5e10, 0x16cde432, 0xfeeb19cd};
	//67bytes
	char rutina1[]="This is not a bootable disk.  Please insert a bootable floppy and\r\n";
	//33bytes
	char rutina2[]="press any key to try again ... \r\n";
	
/**
Creando cluster vacio
**/
	char cluster[size_cluster];
	
	for(i=0;i<size_cluster;i++)
	{
		cluster[i]=0;
	}

/**
Calcular tamaño del nombre del disco
**/
	int size_nomdisco=0;
	i=0;
	while(argv[1][i]!='\0')
	{
		size_nomdisco++;
		i++;
	}

/**
Crear archivo si no existe fat12.fat
**/
	ft_crear(argv[6]);
	int iArchivo;

	if((iArchivo=open(argv[6],O_WRONLY|O_CREAT|O_APPEND))==-1)
	{
		perror("open");
		printf("Borrar el archivo de salida,\npuede solucionar el problema.\n");
		exit(4);
	}

	ft_escribirH(iArchivo,SALTO_RUTINA,3);
	ft_escribirH(iArchivo,FABRICANTE,4);
	ft_escribirH(iArchivo,NUM_VERSION,4);

	ft_escribirH(iArchivo,bytesporSector,2);
	ft_escribirH(iArchivo,nsectorporCluster,1);
	ft_escribirH(iArchivo,SECTORES_RESERVADOS,2);
	ft_escribirH(iArchivo,NUM_FATS,1);

	ft_escribirH(iArchivo,numEntradas,2);
	ft_escribirH(iArchivo,numSectores,2);
	ft_escribirH(iArchivo,MEDIA_DESCRIPTOR,1);


	ft_escribirH(iArchivo,numSectoresporFAT,2);
	ft_escribirH(iArchivo,numSectoresporPISTA,2);
	ft_escribirH(iArchivo,NCABEZALES_RDWR,2);

	ft_escribirH(iArchivo,NSECTORES_OCULTOS,4);
	ft_escribirH(iArchivo,NSECTORES_PARTICION,4);
	ft_escribirH(iArchivo,NUM_DISP_FISICO,1);
	ft_escribirH(iArchivo,CABEZAL_ACTUAL,1);

	ft_escribirH(iArchivo,FIRMA_SO,1);
	ft_escribirH(iArchivo,ID_VOLUMEN,4);
	//11 bytes en total
	ft_escribir(iArchivo,argv[1],size_nomdisco);ft_add_espacios(iArchivo,11-size_nomdisco); 
	//8 bytes en total
	ft_escribir(iArchivo,VERSION,5);ft_add_espacios(iArchivo,8-5); 

	ft_escribirH(iArchivo,FIN_SECTOR,2);
	ft_escribirH(iArchivo,INI_FIN_RUTINA,2);
	ft_escribirH(iArchivo,SIZE_RUTINA,1);

	/**
	67 bytes escritos
	Escribir rutina de instrucciones
	124 bytes a escribir
	**/
	for(i=0;i<6;i++)
	{
		ft_escribirH(iArchivo,rutina0[i],4);
	}
	
	ft_escribir(iArchivo,rutina1,67);
	ft_escribir(iArchivo,rutina2,33);
	
	/**
	Completando sector con 0x0
	**/
	ft_escribir(iArchivo,cluster,bytesporSector-193);
	ft_escribirH(iArchivo,SECTOR_FIN,2);
	/**
	Agregando FAT-FAT'
	**/
	for(i=0;i<2;i++)
	{
		//Cluster reservados (0,1) => 0xfffff9
		ft_escribirH(iArchivo,INICIO_FAT,3);
		ft_escribir(iArchivo,cluster,bytesporSector-3);
		int j;
		//Agregando un sector vacio
		for(j=0;j<numSectoresporFAT-1;j++)
		{
			ft_escribir(iArchivo,cluster,size_cluster/2);
		}
	}

/**
Agregando Directorio raiz
**/
	//11 bytes para el nombre_disco
	ft_escribir(iArchivo,argv[1],size_nomdisco);ft_add_espacios(iArchivo,11-size_nomdisco);
	//1 byte para atributos
	ft_escribirH(iArchivo,0x8,1);
	//10 bytes reservados
	ft_escribir(iArchivo,cluster,2);
	ft_escribirH(iArchivo,0x8396,2);
	ft_escribirH(iArchivo,0x4966,2);
	ft_escribirH(iArchivo,0x4966,2);
	ft_escribir(iArchivo,cluster,2);
	//2 bytes hora
	ft_escribirH(iArchivo,0x8396,2);
	//2 bytes fecha
	ft_escribirH(iArchivo,0x4966,2);
	//2 bytes primer cluster
	ft_escribir(iArchivo,cluster,2);
	//4 bytes tamaño del archivo
	ft_escribir(iArchivo,cluster,4);

	ft_escribir(iArchivo,cluster,bytesporSector-32);
	//Completando directorio raiz ( +N sectores)
	for(i=0;i<nSectoresDirRaiz-1;i++)
	{
		ft_escribir(iArchivo,cluster,bytesporSector);
	}
	
	/**
	Agregando cluster disponibles (vacios)
	**/
	//10 sectores en fat, 1 sector de arranque , nSectoresDirRaiz
	if(nSectoresDisponibles%2!=0)
	{
		ft_escribir(iArchivo,cluster,bytesporSector);
	}
	for(i=0;i<nSectoresDisponibles/2;i++)
	{
		ft_escribir(iArchivo,cluster,size_cluster);
	}
	
	/** Cerrando el archivo **/
	close(iArchivo);
}

