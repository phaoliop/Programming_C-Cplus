#include <stdlib.h>
#include <stdio.h>

int main (int argc, char **argv)
{
	puts( "Introduzca un caracter. Para salir, escriba \'q\':" );
	while( 1 )
	if( toupper(getchar()) == 'Q' )
		abort();
	
	return 0;
}