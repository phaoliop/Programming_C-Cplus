/**
    Autor: PaoloRamirez
    Tema: Debilidad cifrado RC4 - Reutilizacion del KeyStream
    Link: https://www.facebook.com/PaoloProgrammer/
**/

#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "rc4.h"

int maximo(int a, int b)
{
    if (a>b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

int main(int argc, char **argv) 
{
    int i=1;
    int indice=0; //Indica el texto que utilizamos (texto 1, texto2)

    int len;
    len=maximo(strlen(argv[1]), strlen(argv[3])); //Tamaño maximo de los 2 textos del parametro
    unsigned char text_cifrado[2][len+1];
    memset(text_cifrado[0],0,sizeof(text_cifrado[0]));
    memset(text_cifrado[1],0,sizeof(text_cifrado[1]));

    for (i = 1; i < 5; i+=2)
    {

        int len_texto,len_clave;
        len_texto=strlen(argv[i]);
        len_clave=strlen(argv[i+1]);

        /**
            Texto inicial
            Clave de cifrado
        **/
        //Tamaño de cadena = len+fincadena \0
        char texto[len_texto+1];
        char clave[len_clave+1];

        //Format
        memset(texto,0,sizeof(texto));
        memset(clave,0,sizeof(clave));

        //Copiar a variables
        strcpy(texto,argv[i]);
        strcpy(clave,argv[i+1]);
     
        
        int x;
        rc4_generar_vector(clave, strlen(clave));
        printf("Texto cifrado(%i):\n",indice+1);
        for (x = 0; x < strlen(texto); x++)
        {
            //Cifrado por flujo
            text_cifrado[indice][x] = texto[x] ^ rc4_salida();
            printf("%02X", text_cifrado[indice][x]);
        }

        indice++;
        printf("\n\n");
    }

    /**
        Suponiendo que sabemos el texto 1
        Y tenemos el texto cifrado de 1 (C1) y el texto cifrado de 2 (C2)
        Obtendremos el texto 2
    **/
    int x;

    /*Texto 1*/
    int len_texto_1;
    len_texto_1 = strlen(argv[1]);
    char texto_1[len_texto_1+1];
    
    //Format
    memset(texto_1,0,sizeof(texto_1));
    
    //Agregando contenido del texto 1 a nuestra cadena
    strcpy(texto_1, argv[1]);

    printf("Texto 1:\n%s\n\n",texto_1);

    /**
        1. Obtener el resultado de aplicar XOR entre textos cifrados-> C1 XOR C2
    **/

    /*Resultado del XOR entre C1 y C2*/
    unsigned char c1_xor_c2[len+1];
    memset(c1_xor_c2, 0, sizeof(c1_xor_c2));

    
    printf("XOR entre textos cifrados:\n");
    for (x = 0; x < len; x++)
    {
        c1_xor_c2[x] = text_cifrado[0][x] ^ text_cifrado[1][x]; //Obteniendo C1 XOR C2
        printf("%02X", c1_xor_c2[x]);
    }
    printf("\n\n");

    
    /**
        2. Obtener el texto 2 al aplicar XOR entre texto 1 XOR c1_xor_c2
    **/

    /*Texto 2*/
    int len_texto_2;
    len_texto_2 = len;
    char texto_2[len_texto_2+1];
    //Format
    memset(texto_2,0,sizeof(texto_2));

    printf("Texto 2 obtenido:\n");
    for (x = 0; x < len; x++)
    {
        texto_2[x] = c1_xor_c2[x] ^ texto_1[x]; //Obteniendo texto 2
        printf("%c", texto_2[x]);
    }
    printf("\n");    

}
