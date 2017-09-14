/**
	Autor: PaoloRamirez
	Tema: Aplicar XOR a un Archivo
	Link: https://www.facebook.com/PaoloProgrammer/
**/
#include <stdlib.h>
#include <stdio.h>
 
int main(int argc, char *argv[]){
    int dato;
    int avance=0;
    FILE *f;

    /**
	Consistencia de archivo
    **/
    if((f=fopen(argv[1],"rb+"))==NULL){ //escritura binaria
	perror(argv[1]);
        return 1;
    }
    fread(&dato,sizeof(int),1,f);
    while(!feof(f))
    {   
        //Hasta final de fichero
        dato=dato^0xFF; // XOR con todos 1s (FF en hexadecimal)
        fseek(f,sizeof(int)*avance,SEEK_SET); //recolocamos el cursor
        avance++;
        fwrite(&dato,sizeof(int),1,f);
        fread(&dato,sizeof(int),1,f);
    }
 
}
