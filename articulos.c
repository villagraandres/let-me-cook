#include <stdio.h>
#include <stdbool.h>
#include "manejoArchivos.h"
#include "articulos.h"
#include "utils.h"
#include "mercados.h"
#include "insumos.h"

void menuArticulos(){

	bool continuar;
	char c;
	struct Articulo articulo = {};

	//Comprobar que los archivos correspondientes existan
	inicializarRegistrosArticulos();

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

	writeOutput1();

};


void lecturaArticulo(struct Articulo* fArticulo){

	FILE* cfptr;
	bool actualizarDatos;
	bool continuar;
	int i = 0;
	int clave;
	char c;

	// Funciona solo para pasarlo a claveExiste y guardar la info en el
	struct Articulo articulo = {};
	struct Mercado mercado = {};
	struct Insumo insumo = {};
	

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
		char c;
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
		/*i = 0;
		do
		{	
			do
			{
				printf("Ingresa la clave del mercado %d\n> ",i+1);
				scanf("%d",&clave);

				if (clave <= 0)
					printf("Ingresa una clave mayor que 0\n");
				else
				{
					// Validar que existan
					cfptr = fopen("mercados.dat","rb");
					if (cfptr == NULL)
						printf("Error al abrir archivo mercados.dat\n");
					else
					{
						fseek(cfptr,sizeof(struct Mercado) * (clave - 1) ,SEEK_SET);		
						fread(&mercado,sizeof(struct Mercado),1,cfptr);

						// Si está vacio no hay nada que actuaizar
						if (mercado.clave == 0)
							printf("Ingresa una clave registrada\n");
						else{
							fArticulo->claveMercados[i] = clave;
							i++;
							printf("Clave %d registrada con éxito\n",mercado.clave);
						}
					}
				}
			} while (clave <= 0);

			do
			{
				printf("Desea agregar otro mercado S/N)\n");
				scanf(" %c",&c);

				if (c=='S' || c=='s')
						continuar = true;
				else if(c=='N' || c == 'n')
						continuar = false;
				else
					printf("Ingrese una opción válida");

			}while(c!='S' && c!= 's' && c!= 'N' && c!= 'n');
			

		} while (i<10 && continuar);*/
		
		
		// Clave de los insumos
		i = 0;
		do
		{	
			do
			{
				printf("Ingresa la clave del insumo %d\n> ",i+1);
				scanf("%d",&clave);

				if (clave < 1 || clave > 100)
					printf("Ingresa una clave mayor entre 1 y 100\n");
				else
				{
					// Validar que existan
					cfptr = fopen("insumos.dat","rb");
					if (cfptr == NULL)
						printf("Error al abrir archivo insumos.dat\n");
					else
					{
						fseek(cfptr,sizeof(struct Insumo) * (clave - 1) ,SEEK_SET);		
						fread(&insumo,sizeof(struct Insumo),1,cfptr);

						// Si está vacio no hay nada que actualizar
						//Si no entonces preguntarle por e provedor al que le desea comprar
						if (insumo.claveInsumo == 0)
							printf("Ingresa una clave registrada\n");
						else{

							fArticulo->insumosRequeridos[i] = clave;

							//Preguntarle a que provedor desea comprarle
							preguntarProvedor(fArticulo,&insumo);

							i++;
							printf("Clave %d registrada con éxito\n",insumo.claveInsumo);
						}
					}
				}
			} while (clave <= 0);

			printf("[DEBUG MESSAGE] - El articulo tiene un costo de producción de %.2f pesos\n",fArticulo->costo);


			do
			{
				printf("Desea agregar un insumo S/N)");
				scanf(" %c",&c);

				if (c=='S' || c=='s')
						continuar = true;
				else if(c=='N' || c == 'n')
						continuar = false;
				else
					printf("Ingrese una opción válida");

			}while(c!='S' && c!= 's' && c!= 'N' && c!= 'n');
			

		} while (i<10 && continuar);



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
			scanf("%f",&fArticulo->precio);

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
	

};




void inicializarRegistrosArticulos(){

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
	struct Articulo articulo = {};
	

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

};


// Función generica para visualizar los elementos de un archivo secuencial

void viewElements()
{

	FILE* fptr;
	fptr = fopen("articulos.dat","rb");
	struct Articulo articulo = {};

	for(int i = 0;i<1000;i++){
		fread(&articulo,sizeof(struct Articulo),1,fptr);
		printf("%d\n",articulo.claveArticulo);

	}

	
};


void preguntarProvedor(struct Articulo* fArticulo,struct Insumo* fInsumo)
{	
	int i,provedor;
	float precio;
	bool valido;

	do
	{	
		printf("%-20s %-20s\n","Provedor","Precio");

		// Imprimir provedores y precios
		i = 0;
		while (i<10 && fInsumo->provedores[i] != 0)
		{
			printf("%-20d %-20.2f\n",fInsumo->provedores[i],fInsumo->precios[i]);
			i++;
		}
			
		printf("Ingresa la clave del provedor a comprar\n");
		scanf("%d",&provedor);

		if (provedor < 0 || provedor > 10 || fInsumo->provedores[provedor-1] == 0)
		{
			printf("Por favor selecciona un valor válido\n");
			valido = false;
		}
		else
		{
			valido = true;
			fArticulo->costo+=fInsumo->precios[provedor-1];
		}

	} while (!valido);
	

}

void writeOutput1()
{

	FILE* fptr = fopen("articulos.dat","rb");
	FILE *archivo = fopen("Logs/Articulo", "w");

	struct Articulo articulo = {};

	printf("%-10s %-20s\n","Clave","Nombre");

	while (fread(&articulo, sizeof(struct Articulo), 1, fptr) == 1)
	{
		if (articulo.claveArticulo != 0)
		{
			fprintf(archivo,"%d %s\n",articulo.claveArticulo,articulo.descripcion);
			for ( int i = 0; i < 10; i++)
			{
				fprintf(archivo,"%d:%d\n",articulo.claveMercados[i],articulo.insumosRequeridos[i]);
			}
			

		}
			
		
	}

	fclose(fptr);
	fclose(archivo);


}
