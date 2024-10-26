#include <stdio.h>
#include "manejoArchivos.h"

int existeArchivo(FILE* fptr,char* fArchivo){

	fptr = fopen(fArchivo,"rb");

	if (fptr == NULL){
		return 1;

	}else{
		fclose(fptr);
		return 0;
	}
};


int crearArchivo(FILE* fptr,char* fArchivo, void* estructura,int cantidadEstructuras,int tamañoEstructura){

	int i;
	fptr = fopen(fArchivo,"wb");

	if(fptr == NULL){
		return 1;
	};

	for (i = 0; i < cantidadEstructuras; ++i)
		fwrite(estructura,tamañoEstructura,1,fptr);

	fclose(fptr);

	return 0;

}
