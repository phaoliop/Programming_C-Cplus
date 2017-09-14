#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "funfat.h"

//Crear archivo fat12
	void ft_crear(char nom_archivo[])
	{
	int fat12;
	/*Si no existe el archivo lo creamos
	Permisos de lectura y escritura para el usuario*/
	if((fat12=open(nom_archivo,O_CREAT,S_IRUSR|S_IWUSR))==-1)
	{
	perror("open");exit(1);
	}
	/*Cerramos el archivo*/
	close(fat12);
	}

//Leer del fat12
	void ft_leer(char *buffer,int *tam_buffer)
	{
	int fat12;
	if((fat12=open("salida.fat",O_RDONLY))==-1)
	{
	perror("open");exit(2);
	}
	*tam_buffer=read(fat12,buffer,*tam_buffer);
	close(fat12);
	}
//Leer(2) del fat12
	void ft_leer_desde(int pos_ini,char *buffer,int *tam_buffer)
	{
	int fat12;
	if((fat12=open("salida.fat",O_RDONLY))==-1)
	{
	perror("open");exit(2);
	}
	lseek(fat12,pos_ini,SEEK_SET);
	*tam_buffer=read(fat12,buffer,*tam_buffer);
	close(fat12);
	}


//Funcion de escritura del fat12
	void ft_escribir(int iArchivo,char buffer[],int tam_buffer)
	{	
		write(iArchivo,buffer,tam_buffer);
	}

//Funcion de escritura hexadecimal del fat12
	void ft_escribirH(int iArchivo,unsigned int valor,int tam_valor)
	{
		write(iArchivo,&valor,tam_valor);
	}
//Funcion completar espacios 0x20
	void ft_add_espacios(int iArchivo,int cantidad)
	{
		int i;
		for(i=0;i<cantidad;i++)
		{
			ft_escribirH(iArchivo,ESPACIO,1);
		}

	}

