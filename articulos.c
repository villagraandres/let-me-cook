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
	inicializarRegistros();


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

		lecturaArticulo(&articulo);

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

	FILE* cfptr;
	bool actualizarDatos;

	// Funciona solo para pasarlo a claveExiste y guardar la info en el
	struct Articulo articulo;
	

	// Clave del articulo
	do
	{
		printf("Clave del articulo:\n");
		scanf("%d",&fArticulo->claveArticulo);

		if (fArticulo->claveArticulo < 0 || fArticulo->claveArticulo > 1000)
			printf("Ingresa un número entre 1 y 1000");
	}while(fArticulo->claveArticulo < 0 || fArticulo->claveArticulo > 1000);

	// Comprobar que la clave no exista y si existe preguntar si desea rescribir o no los datos
	if (claveExiste(fArticulo->claveArticulo,cfptr,"articulos.dat"))
		actualizarDatos = false;
	else
		actualizarDatos = true;
	
	if(actualizarDatos == false)
	{
		//Descripcion
		//Al utilizar gets no recibe salto de linea la cadena
		validarCadena(fArticulo->descripcion);

		printf("[DEBUG MESSAJE Descripcion value] : %s\n",fArticulo->descripcion);

		//Temporada de siembra
		int c;
		while ((c = getchar()) != '\n' && c != EOF); 
		fflush(stdin);
		printf("\n3) Temporada de siembra: ");
		fgets(fArticulo->temporadaSiembra,20,stdin);

		// Temporada de cosecha
		while ((c = getchar()) != '\n' && c != EOF); 
		printf("\n4) Temporada de cosecha: ");
		fflush(stdin);
		fgets(fArticulo->temporadaCosecha,20,stdin);
		
		// Clave de los mercados

		/* Leer a lo más 10 claves y checar si existen en el archivo de claves de mercado*/

		// Clave de los insumos

		/* Leer a lo más 10 claves y checar si existen en el archivo de claves de insumos
			Y calcular el costo de producción a partir de ellos
		*/

		// Inventario

		do
		{
			printf("\n5) Inventario: ");
			scanf("%d",&fArticulo->inventario);

			if (fArticulo->inventario < 0 )
				printf("Ingrese una cantidad válida\n");

		} while (fArticulo->inventario < 0 );

		// Precio de venta
		do
		{
			printf("6) Precio de venta: ");
			scanf("%d",&fArticulo->precio);

			if (fArticulo->precio < 0 )
				printf("Ingrese una cantidad válida\n");

		} while (fArticulo->precio < 0 );

		// Escribir estructura en el archivo
		cfptr = fopen("articulos.dat","r+b");
		if (cfptr == NULL)
			{
				printf("[ERROR] - No se pudo escribir en el archivo articulos.dat\n");
				return;
			}
		
		else
			{
				fseek(cfptr,sizeof(struct Articulo) * fArticulo->claveArticulo ,SEEK_SET);		
				fwrite(fArticulo,sizeof(struct Articulo),1,cfptr);
		};

		fclose(cfptr);

	}
	


}

void inicializarRegistros(){

	// Comprobar si el registro corespondiente exista sino crearlo

	char nombreArchivo[] = "articulos.dat";
	FILE* cfptr;
	struct Articulo articulo = {};	

	if (existeArchivo(cfptr,nombreArchivo))
		// Si regresa false salir del programa
		crearArchivo(cfptr,nombreArchivo,&articulo,1000,sizeof(struct Articulo));

};

int claveExiste(int clave, FILE* fptr,char* fArchivo)
{
	fptr = fopen(fArchivo,"rb");
	bool sobreescrbir;
	char c;
	struct Articulo articulo;
	

	if (fptr == NULL)
		return 1;

	else{

		// Buscar clave
		fseek(fptr,sizeof(struct Articulo) * clave ,SEEK_SET);		
		fread(&articulo,sizeof(struct Articulo),1,fptr);

		printf("%d",articulo.claveArticulo);

		// Si está vacio no hay nada que actuaizar
		if (articulo.claveArticulo == 0)
			return 1;

		do
		{
			printf("La clave %d ya existe en el registro %s, desea sobreescibir los datos S-N\n",clave,fArchivo);
			scanf(" %c",&c);

			if (c=='S' || c == 's')
				sobreescrbir = true;
			else if(c=='N' || c == 'n')
				sobreescrbir = false;

			else
				printf("Ingresa una opción válida\n");

		} while (c!='S' && c!= 's' && c!= 'N' && c!= 'n');

		fclose(fptr);

		if(sobreescrbir)
			return 0;

		else 
			return 1;

	}

}