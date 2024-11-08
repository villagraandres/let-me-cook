#include <stdio.h>

int existeArchivo(FILE*,char*);

int crearArchivo(FILE* fptr,char* fArchivo, void* estructura,int cantidadEstructuras,int tamanoEstructura);

//Librera que utliza funciones de uso general como por ejemplo validar una cadena

void validarCadena(char*);

// Checa si la clave x existe en el registro

void validarNombre(char*);

void clear_input_buffer();
