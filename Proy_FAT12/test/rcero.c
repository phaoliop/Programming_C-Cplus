#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define tamano 512
#define linea 16
int main (int argc ,  char **argv)
{
	int archivo;
	int leido;
	int i;
	int j;
	char buffer[tamano];
	char c; 
	int n;
	archivo=open(argv[2],O_RDONLY);

	n=atoi(argv[1]);
	lseek(archivo,n*tamano,SEEK_SET);

	leido=read(archivo,buffer,tamano);
	for(i=0; i<tamano/linea ; i++)
	{
		for(j=0;j<linea;j++)
		{
			c= buffer[i*linea +j];
			printf("%02x ",c & 0x00000FF);
		}
		
		for(j=0;j<linea;j++)
		{
			c=buffer[i*linea+j];
			if(isprint(c))
			{
				printf("%c",c);
			}else{
			printf("-");}

		
		}
		printf("\n");	
	}
	close(archivo);

}
