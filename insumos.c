#include <stdio.h>
#include <stdbool.h>
#include "insumos.h"
#include "manejoArchivos.h"
#include "utils.h"

void menuInsumos()
{


	bool continuar;
	char c;
	struct Insumo insumo = {};

	//Comprobar que los archivos correspondientes existan
	inicializarRegistrosInsumos();

	do{
		printf("Desea agregar un insumo S/N)");
		scanf(" %c",&c);

		if (c=='S' || c=='s')
				continuar = true;
		else if(c=='N' || c == 'n')
				continuar = false;
		else
			printf("Ingrese una opción válida");

	}while(c!='S' && c!= 's' && c!= 'N' && c!= 'n');

	while(continuar)
	{

		lecturaInsumo(&insumo);

		do{
			printf("Desea agregar un insumo S/N)");
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


void inicializarRegistrosInsumos()
{

	// Comprobar si el registro corespondiente exista sino crearlo

	char nombreArchivo[] = "insumos.dat";
	FILE* cfptr;
	struct Insumo insumo = {};	

	if (existeArchivo(cfptr,nombreArchivo))
		// Si regresa false salir del programa
		crearArchivo(cfptr,nombreArchivo,&insumo,100,sizeof(struct Insumo));

};


void lecturaInsumo(struct Insumo* fInsumo){

	FILE* cfptr;
	bool actualizarDatos;

	// Funciona solo para pasarlo a claveExiste y guardar la info en el
	struct Insumo insumo;

	// Clave del insumo
	do
	{
		printf("Clave del insumo:\n");
		scanf("%d",&fInsumo->claveInsumo);

		if (fInsumo->claveInsumo < 0 || fInsumo->claveInsumo > 100)
			printf("Ingresa un número entre 1 y 100\n");
	}while(fInsumo->claveInsumo < 0 || fInsumo->claveInsumo > 100);

	if (claveInsumoExiste(fInsumo->claveInsumo,cfptr,"insumos.dat"))
		actualizarDatos = false;
	else
		actualizarDatos = true;
	

	if(actualizarDatos == true)
	{

		//Descripcion
		//Al utilizar gets no recibe salto de linea la cadena
		validarCadena(fInsumo->descripcion);
		printf("[DEBUG MESSAJE Descripcion value] : %s\n",fInsumo->descripcion);


		// Punto de reorden
		do
		{
			printf("\n3) Punto de reorden: \n");
			scanf("%d",&fInsumo->puntoReorden);

			if (fInsumo->puntoReorden <= 0)
				printf("\n[ERROR] agrega un valor mayor que 0\n");

		}while(fInsumo->puntoReorden <= 0);


		// Inventario

		do
		{
			printf("\n4) Inventario: \n");
			scanf("%d",&fInsumo->inventario);

			if (fInsumo->inventario < 0)
				printf("\n[ERROR] agrega un valor mayor o igual a 0\n");
		
		}while(fInsumo->inventario < 0);


		// Preguntar 10 veces para los provedores y sus respectivos precios



		// Escribir estructura en el archivo	
		cfptr = fopen("insumos.dat","r+b");
		if (cfptr == NULL)
			{
				printf("[ERROR] - No se pudo escribir en el archivo insumos.dat\n");
				return;
			}
		
		else
			{
				fseek(cfptr,sizeof(struct Insumo) * fInsumo->claveInsumo ,SEEK_SET);		
				fwrite(fInsumo,sizeof(struct Insumo),1,cfptr);
		};

		fclose(cfptr);

	}


	
};


int claveInsumoExiste(int clave, FILE* fptr,char* fArchivo)
{

	fptr = fopen(fArchivo,"rb");
	bool sobreescrbir;
	char c;
	struct Insumo insumo = {};

	if (fptr == NULL)
		return 1;

	else{

		// Buscar clave
		fseek(fptr,sizeof(struct Insumo) * clave ,SEEK_SET);		
		fread(&insumo,sizeof(struct Insumo),1,fptr);

		printf("[DEBUG MESSAJE] Search clave : %d\n",insumo.claveInsumo);

		// Si está vacio no hay nada que actuaizar
		if (insumo.claveInsumo == 0)
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

};