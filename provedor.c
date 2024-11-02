#include "provedor.h"
#include "manejoArchivos.h"
#include "utils.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

void menuProvedor()
{

    bool continuar;
	char c;
	struct Provedor provedor = {};

    //Comprobar que los archivos correspondientes existan
	inicializarRegistrosProvedor();


    do
    {
		printf("Desea agregar un provedor S/N)");
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

		lecturaProvedor(&provedor);

		do{
			printf("Desea agregar otro provedor S/N)");
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


void inicializarRegistrosProvedor()
{

    // Comprobar si el registro corespondiente exista sino crearlo

	char nombreArchivo[] = "provedor.dat";
	FILE* cfptr;
	struct Provedor provedor = {};	

	if (existeArchivo(cfptr,nombreArchivo))
		
        // Si regresa false salir del programa
		crearArchivo(cfptr,nombreArchivo,&provedor,100,sizeof(struct Provedor));
};


void lecturaProvedor(struct Provedor* fProvedor)
{

    FILE* cfptr;
	bool actualizarDatos;

	// Funciona solo para pasarlo a claveExiste y guardar la info en el
	struct Provedor provedor;

    // Numero del provedor
	do
	{
		printf("Clave del Provedor:\n");
		scanf("%d",&fProvedor->claveProvedor);

		if (fProvedor->claveProvedor < 0 || fProvedor->claveProvedor > 100)
			printf("Ingresa un número entre 1 y 100\n");
	}while(fProvedor->claveProvedor < 0 || fProvedor->claveProvedor > 100);

    if (claveProvedorExiste(fProvedor->claveProvedor,cfptr,"provedor.dat"))
		actualizarDatos = true;
	else
		actualizarDatos = false;

    if(actualizarDatos == true)
    {

        // Leer nombre
        validarNombre(fProvedor->nombre);

        // RFC


        // Correo
        validarCorreo(fProvedor->correo);

		// Descuento
		do
		{
			printf("Ingresa el porcentaje de descuento\n");
			scanf("%f",&fProvedor->descuento);

			if (fProvedor->descuento < 0 && fProvedor->descuento > 100)
				printf("Ingresa un porcentaje válido\n");

		}while(fProvedor->descuento < 0 && fProvedor->descuento > 100);

		fProvedor->descuento/=100;
        
		// Año de nacimiento

		do
		{
			printf("Ingresa año de nacimiento\n");
			scanf("%d",&fProvedor->año);

			if (fProvedor->año < 1950 || fProvedor->año > 2006)
				printf("Ingresa un año entre 1950 y 2006\n");

		} while (fProvedor->año < 1950 || fProvedor->año > 2006);


		// Mes
		do
		{
			printf("Ingresa número del mes de nacimiento\n");
			scanf("%d",&fProvedor->mes);

			if (fProvedor->mes < 1 || fProvedor->mes > 12)
				printf("Ingresa un mes válido\n");

		} while (fProvedor->mes < 1 || fProvedor->mes > 12);

		// Día

		do
		{
			printf("Ingresa el día del mes");
			scanf("%d",&fProvedor->dia);

			if (fProvedor->dia < 1 || fProvedor->dia > 31)
				printf("Ingresa un día válido");

			else if (fProvedor->mes == 2)
			{
				if (fProvedor->año%4 == 0 && fProvedor->dia > 29)
					printf("Fecha inválida\n");
				else if(fProvedor->dia > 28)
					printf("Fecha inválida");
				else
					printf("[DEBUG MESSAGE] : Fecha registrada");


			}
			else if(fProvedor->mes != 1 && (fProvedor->mes%5 == 1 || fProvedor->mes%5 == 4))
			{
				if(fProvedor->dia > 30)
					printf("Fecha inválida\n");
				else
					printf("[DEBUG MESSAGE] : Fecha registrada");
			}
			else
			{

				if(fProvedor->dia > 31)
					printf("Fecha inválida\n");
				else
					printf("[DEBUG MESSAGE] : Fecha registrada");
			};





		} while (fProvedor->dia < 1 || fProvedor->dia > 31);

		// Validar dirección
		validarDireccion(fProvedor);
		
		

    }



};

int claveProvedorExiste(int clave, FILE* fptr,char* fArchivo)
{

	fptr = fopen(fArchivo,"rb");
	bool sobreescrbir;
	char c;
	struct Provedor provedor = {};

	if (fptr == NULL)
		return 1;

	else{

		// Buscar clave
		fseek(fptr,sizeof(struct Provedor) * (clave - 1) ,SEEK_SET);		
		fread(&provedor,sizeof(struct Provedor),1,fptr);

		printf("[DEBUG MESSAJE] Search clave : %d\n",provedor.claveProvedor);

		// Si está vacio no hay nada que actuaizar
		if (provedor.claveProvedor == 0)
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



void validarCorreo(char* correo)
{

    bool valido;
    int i,c,arrobaPos;
    while ((c = getchar()) != '\n' && c != EOF);


	do
	{
		printf("Ingresa tu correo electronico:\n");
		fgets(correo,100,stdin);
		correo[strlen(correo)-1] = '\0';

		i = 0;
		valido = true;

		// Buscar hasta el primer arroba
		while(i<strlen(correo) && i!='@' && isalnum(correo[i]))i++;
		
		if (correo[i] != '@' || i<1)
			valido = false;

		
		// Buscar los caracteres entre el arroba y el punto, Validar que el punto no sea el fin de la cadena
		if (valido)
		{	
			arrobaPos = i;
			i++;
			while(i<strlen(correo) && i!='.' && isalnum(correo[i]))i++;

			printf("%d %d \n",arrobaPos,i);


			if (correo[i] != '.' || (i-arrobaPos)<2 || i+1==strlen(correo))
				valido = false;

		};



	} while (!valido);
	

};


void validarDireccion(struct Provedor* fProvedor)
{
	bool valido;
	int i;

	// Calle
	do
	{	valido = true;
		printf("calle: ");
		fgets(fProvedor->calle,sizeof(fProvedor->calle),stdin);
		fProvedor->calle[strlen(fProvedor->calle)-1] = '\0';
		
		//fflush(stdin);
		//gets(datos.calle);
		for (i = 0; i < strlen(fProvedor->calle); i++)
		{
			if ((fProvedor->calle[i] < 'A' || fProvedor->calle[i] > 'Z') && (fProvedor->calle[i] < 'a' || fProvedor->calle[i] > 'z') && fProvedor->calle[i] != ' ')
			{
				printf("hay datos invalidos\n");
				valido = false;
				
			}
		}
	}
	while (!valido);

	// Número
	do
	{
		printf("numero de calle: ");
		//fflush(stdin);
		fgets(&fProvedor->numero,sizeof(fProvedor->calle),stdin);
		valido = true;

		for (i = 0; i < strlen(fProvedor->numero); i++)
		{
			if (fProvedor->numero[i] < '0' || fProvedor->numero[i] > '9')
			{
				printf("dato invalido\n");
				valido = false;
			}	
		}
	}
	while (!valido);

	// Colonia
	do
	{	valido = true;
		printf("Colonia: ");
		fgets(fProvedor->colonia,sizeof(fProvedor->colonia),stdin);
		fProvedor->colonia[strlen(fProvedor->colonia)-1] = '\0';
		
		//fflush(stdin);
		//gets(datos.calle);
		for (i = 0; i < strlen(fProvedor->colonia); i++)
		{
			if ((fProvedor->colonia[i] < 'A' || fProvedor->colonia[i] > 'Z') && (fProvedor->colonia[i] < 'a' || fProvedor->colonia[i] > 'z') && fProvedor->colonia[i] != ' ')
			{
				printf("hay datos invalidos\n");
				valido = false;
				
			}
		}
	}
	while (!valido);
	

	// Municipio
	do
	{	valido = true;
		printf("Municipio: ");
		fgets(fProvedor->municipio, sizeof(fProvedor->municipio), stdin);
		fProvedor->municipio[strlen(fProvedor->municipio)-1] = '\0';
		
		//fflush(stdin);
		//gets(datos.calle);
		for (i = 0; i < strlen(fProvedor->municipio); i++)
		{
			if ((fProvedor->municipio[i] < 'A' || fProvedor->municipio[i] > 'Z') && (fProvedor->municipio[i] < 'a' || fProvedor->municipio[i] > 'z') && fProvedor->municipio[i] != ' ')
			{
				printf("hay datos invalidos\n");
				valido = false;
				
			}
		}
	}
	while (!valido);

	// Estado
	// Municipio
	do
	{	valido = true;
		printf("Estado: ");
		fgets(fProvedor->estado, sizeof(fProvedor->estado), stdin);
		fProvedor->estado[strlen(fProvedor->estado)-1] = '\0';
		
		//fflush(stdin);
		//gets(datos.calle);
		for (i = 0; i < strlen(fProvedor->estado); i++)
		{
			if ((fProvedor->estado[i] < 'A' || fProvedor->estado[i] > 'Z') && (fProvedor->estado[i] < 'a' || fProvedor->estado[i] > 'z') && fProvedor->estado[i] != ' ')
			{
				printf("hay datos invalidos\n");
				valido = false;
				
			}
		}
	}
	while (!valido);

}