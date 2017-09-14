#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main (int argc, char **argv)
{
	float num=0;
	puts( "Escriba un numero:" );
	scanf( "%f", &num);
	if(num<-1 || num>1)
	{
		perror("Rango invalido, [-1,1]");
		exit(1);
	}
	printf( "acos( %f ) = %f\n", num, acos(num) );
}