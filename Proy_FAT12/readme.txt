**README**

**NOTAS**

-CARPETA "disco" ES LA CARPETA QUE USAMOS DE EJEMPLO PARA MONTAR EL ARCHIVO "nueva.fat" con el sistema de archivos FAT12.
-LOS ARCHIVOS CONTENIDOS EN LA CARPETA "test" SON PARA VISUALIZAR AL INTERIOR DE NUESTRO ARCHIVO "nueva.fat" QUE ARCHIVOS SE ENCUENTRAN.

**CREACION Y EJECUCION DEL ARCHIVO .fat**
1.Abrir la consola
2.Ubicarnos en la carpeta que contiene el proyecto fat12 (Proy_FAT12)
3.Hacer make (generará el ejecutable) :
	$ make

4.Ejecutar el archivo generado:
	$ ./fat12 [nom_disco] [bytes_sector] [sector_por_cluster] [entradas_dirRaiz] [num_Sectores] [nom_Salida.fat]

  *Indicar los parametros mencionados
5.Montar el archivo fat a una carpeta de ejemplo ("disco").

**description fat12**

3 bytes = salto a la rutina del BIOS (EB EC 90)  --- LITTLE ENDIAN *
8 bytes = fabricante y numero de version (6D 6B 66 73 2E 66 61 74) *


2 bytes = bytes por sector ( 00 02 ) *
1 byte  = sectores por cluster (02) *
2 bytes = numero de sectores reservados (01 00) *
1 byte  = numero de fat's ( 02 ) *


2 bytes = numero de entradas en el directorio raiz (70 00) *
2 bytes = numero de sectores del volumen (40 0B)
1 byte  = media descriptor (F9) *


2 bytes = numero de sectores por FAT (05 00) *
2 bytes = sectores por pista (12 00) *
2 bytes = numero de cabezales de lectura-escritura (02 00) *

4 bytes = instancia de primer sector en el volumen del primer sector 
en el medio de almacenamiento. (00 00 00 00)
Numero de sectores ocultos en el volumen. Se refiere al numero de sectores
de disco que preceden el inicio del volumen.

4 bytes = numero de sectores que ocupa la particion. (se utiliza con discos duros) (00 00 00 00)
1 byte = numero de dispositivo fisico 00 para FDD - 80 para Discos duros (00)
1 byte = cabezal actual. lo utiliza WinNT internamente (00)

1 byte = Firma del sistema operativo que creo el disco. (29) = WinNT *
4 bytes = id del volumen (6e ff d2 08) *
11 bytes = nombre, completar con 20(espacio) si no completa los 11 bytes *
3 bytes = FAT *
4 bytes = version (12), completar con 20(espacio) si no completa los 4 bytes *

------------------------------------
** FAT **
sector 1,2,3,4,5 (5 sectores)
sector 6,7,8,9,10 (5 sectores)
0x0 = cluster libre
0xFF0-0xFF6 = cluster reservado para uso interno
0xFF7 = cluster con sectores erroneos
0xFF8-0xFFF= ultimo cluster del archivo

Si es un numero indica cual es el siguiente cluster del archivo


------------------------------------
** Directorio Raiz **

sector 11,12,13,14,15,16,17,18,19 (9 sectores)

**sector 11:**
11 bytes = nombre del volumen
1 byte = atributos
10 bytes = reservados 
(2 bytes, 2 bytes hora, 2 bytes fecha, 2 bytes fecha, 2 bytes)
2 bytes = hora
2 bytes = fecha
2 bytes = primer cluster
4 bytes = tamaño del archivo

==== total 32 bytes
Para un directorio 32 bytes
describir
**32 bytes datos**
(8 bytes = nombre del archivo
3 bytes = extension del archivo
1 byte = atributos
10 bytes = reservados 
2 bytes = hora ( Hora%2048 Min%32 Seg%2) 33686 =>16horas <>918=>28m <>22=>11s
2 bytes = fecha (Año-1980%512 Mes%32 Dia) 18790 =>36+1980año <>358=>11mes <>6dias
2 bytes = primer cluster
4 bytes = tamaño del archivo)
--------------------------------------

** Datos **
1 sector = arranque
5 sectores = fat
5 sectores = fat'
7 sectores = directorio raiz
====18 sectores usados
cluster 0 = reservado
cluster 1 = reservado
====2 cluster reservados (*)
Datos inician en el cluster 2
**Formula para hallar el sector que inicia el cluster(donde inicia el cluster)**
Cluster_N = (tamaño_sector)*(sector_por_cluster*(num_cluster-2))


---------------------------------------
