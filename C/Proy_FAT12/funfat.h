#define SIZE_BUFFER 512
#define ESPACIO 0x20

void ft_crear(char nom_archivo[]);
void ft_leer(char *buffer,int *tam_buffer);
void ft_leer_desde(int pos_ini,char *buffer,int *tam_buffer);

void ft_escribir(int iArchivo,char buffer[],int tam_buffer);
void ft_escribirH(int iArchivo,unsigned int valor,int tam_valor);

/**
Agrega espacios en la fat 0x20
**/
void ft_add_espacios(int iArchivo,int cantidad);
