#include <stdio.h>
#include <stdbool.h>
#include "manejoArchivos.h"
#include "articulos.h"
#include "utils.h"

void menuArticulos(){

	bool continuar;
	char c;
	//Comprobar que los archivos correspondientes existan

	struct Articulo articulo = {};
	inicializarRegistros(&articulo);

	do{
		printf("Desea agregar un articulo S/N)");
		scanf(" %c",&c);

		if (c=='S' || c=='s')
				continuar = true;
		else if(c=='N' || c == 'n')
				continuar = false;
		else
			printf("Ingrese una opción válida");

	}while(c!='S' && c!= 's' && c!= 'N' && c!= 'n');

	while(continuar){


		do{
			printf("Desea agregar un articulo S/N)");
			scanf(" %c",&c);

			if (c=='S' || c=='s')
					continuar = true;
			else if(c=='N' || c == 'n')
					continuar = false;
			else
				printf("Ingrese una opción válida");

		}while(c!='S' && c!= 's' && c!= 'N' && c!= 'n');

	}

};


void lecturaArticulo(struct Articulo* fArticulo){

	// Clave del articulo
	do
	{
		printf("Clave del articulo:\n");
		scanf("%d",&fArticulo->claveArticulo);

		if (fArticulo->claveArticulo < 0 || fArticulo->claveArticulo > 1000)
			printf("Ingresa un número entre 1 y 1000");
	}while(fArticulo->claveArticulo < 0 || fArticulo->claveArticulo > 1000);

	//Descripcion
	//Al utilizar gets no recibe salto de linea la cadena
	validarCadena(fArticulo->descripcion);

	//Temporada de siembra

	//P - Primavera
	// V - Verano
	// O - Otono
	// I - Invierno 

}

void inicializarRegistros(){

	// Comprobar si el registro corespondiente exista sino crearlo

	char nombreArchivo[] = "archivos.dat";
	FILE* cfptr;
	struct Articulo articulo = {};	

	if (!existeArchivo(cfptr,nombreArchivo))
		// Si regresa false salir del programa
		crearArchivo(cfptr,nombreArchivo,&articulo,1000,sizeof(struct Articulo));

}