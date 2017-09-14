#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	int num;
	puts( "Escriba un numero entero:" );
	scanf( "%d", &num );
	printf( "abs( %d ) = %d\n", num, abs(num) );
	
}