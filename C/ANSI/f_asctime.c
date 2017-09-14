#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv )
{
	long int i,j,k;
	time_t comienzo, final;
	struct tm *tiempoComienzoPtr, *tiempoFinalPtr;

	/*Comienzo*/
	comienzo = time( NULL );
	/*Codigo*/
	for( i=0; i<1000; i++ )
		for( j=0; j<1000; j++ )
			for( k=0; k<1000; k++ )
	/*Final*/
	final = time( NULL );

	printf( "Comienzo: %u s\n", comienzo );
	printf( "Final: %u s\n", final );
	printf( "Número de segundos transcurridos desde el comienzo del programa: %f s\n",
	difftime(final, comienzo) );
	/*Tiempo inicio*/
	tiempoComienzoPtr = gmtime( &comienzo );
	/*Tiempo final*/
	tiempoFinalPtr = gmtime( &final );

	printf( "Comienzo: %s\n", asctime(tiempoComienzoPtr) );
	printf( "Final: %s\n", asctime(tiempoFinalPtr) );
	
	/*Struct tm 
	{
	   int tm_sec;         // 0-59
	   int tm_min;         // 0-59
	   int tm_hour;        // 0-23
	   int tm_mday;        // 1-31
	   int tm_mon;         // 0-11
	   int tm_year;        // 1900-
	   int tm_wday;        // 0-6
	   int tm_yday;        //0-365
	   int tm_isdst;       //Hora de verano
	}
	*/

	return 0;
}