/**
    Autor: PaoloRamirez
    Tema: Cifrado RC4
    Link: https://www.facebook.com/PaoloProgrammer/
**/

#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "rc4.h"

unsigned char S[256];
unsigned int i, j;

/**
    Intercambiar valores entre i y j
**/
void intercambiar(unsigned char *s, unsigned int i, unsigned int j) 
{
    unsigned char temp = s[i];
    s[i] = s[j];
    s[j] = temp;
}

/**
    KSA - Algoritmo de programacion de claves
**/
void rc4_generar_vector(unsigned char *key, unsigned int key_length) 
{

    //Asignar valores iniciales al Array S[]
    for (i = 0; i < 256; i++)
    {   
        S[i] = i;
    }
 
    //Genera semilla con la clave ingresada, altera los valores de S[]
    for (i = j = 0; i < 256; i++) 
    {   
        j = (j + key[i % key_length] + S[i]) & 255;
        intercambiar(S, i, j);  
    }
 
    i = j = 0;
}
 
/**
    PRGA - Algoritmo de generacion Pseudo-Aleatoria
**/
unsigned char rc4_salida() 
{
    i = (i + 1) & 255;
    j = (j + S[i]) & 255;

    intercambiar(S, i, j);

    return S[(S[i] + S[j]) & 255];
}

