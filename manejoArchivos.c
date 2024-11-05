#include <stdio.h>
#include "manejoArchivos.h"

// Verifica si el archivo existe
int existeArchivo(FILE* fptr, char* fArchivo) {
    fptr = fopen(fArchivo, "rb");

    if (fptr == NULL) {
        return 1;  // El archivo no existe
    } else {
        fclose(fptr);
        return 0;  // El archivo existe
    }
}

// Crea el archivo con estructuras iniciales
int crearArchivo(FILE* fptr, char* fArchivo, void* estructura, int cantidadEstructuras, int tamañoEstructura) {
    fptr = fopen(fArchivo, "wb");

    if (fptr == NULL) {
        return 1;  // Error al abrir el archivo para escritura
    }

    for (int i = 0; i < cantidadEstructuras; ++i) {
        fwrite(estructura, tamañoEstructura, 1, fptr);
    }

    fclose(fptr);

    return 0;
}
