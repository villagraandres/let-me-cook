#include "provedor.h"
#include "ventas.h"
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

	};

	writeOutput();

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

	char c;
    FILE* cfptr;
	bool actualizarDatos,valido;

	// Funciona solo para pasarlo a claveExiste y guardar la info en el
	struct Provedor provedor;

    // Numero del provedor
	do
	{
		printf("Clave del Provedor:\n");
		scanf("%d",&fProvedor->claveProvedor);

		if (fProvedor->claveProvedor < 1 || fProvedor->claveProvedor > 100)
			printf("Ingresa un número entre 1 y 100\n");
	}while(fProvedor->claveProvedor < 1 || fProvedor->claveProvedor > 100);

    if (claveProvedorExiste(fProvedor->claveProvedor,cfptr,"provedor.dat"))
		actualizarDatos = false;
	else
		actualizarDatos = true;

    if(actualizarDatos == true)
    {

        // Leer nombre
        validarNombre(fProvedor->nombre);

        // Correo
        validarCorreo(fProvedor->correo);

		// Descuento
		do
		{
			printf("Ingresa el porcentaje de descuento\n");
			scanf("%f",&fProvedor->descuento);

			if (fProvedor->descuento < 0 && fProvedor->descuento > 100)
				printf("Ingresa un porcentaje válido\n");

		}while(fProvedor->descuento < 0 || fProvedor->descuento > 100);

		fProvedor->descuento/=100;
        

		// RFC
		while ((c = getchar()) != '\n' && c != EOF);

		validarRFC(fProvedor);

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

		// Nacimiento

		do
		{
			printf("Ingresa el día del mes\n");
			scanf("%d",&fProvedor->dia);

			if (fProvedor->dia < 1 || fProvedor->dia > 31)
			{
				printf("Ingresa un día válido");
				valido = false;
			}
				
			else if (fProvedor->mes == 2)
			{
				if (fProvedor->año%4 == 0 && fProvedor->dia > 29)
				{
					printf("Fecha inválida\n");
					valido = false;
				}
					
				else if(fProvedor->año%4 != 0 && fProvedor->dia > 28)
				{
					printf("Fecha inválida");
					valido = false;
				}
					
				else
				{
					printf("[DEBUG MESSAGE] : Fecha registrada");
					valido = true;
				}

			}
			else if(fProvedor->mes != 1 && (fProvedor->mes%5 == 1 || fProvedor->mes%5 == 4))
			{
				if(fProvedor->dia > 30)
				{
					printf("Fecha inválida\n");
					valido =  false;
				}
					
				else
				{
					printf("[DEBUG MESSAGE] : Fecha registrada");
					valido = true;
				}	
					
			}
			else
			{

				if(fProvedor->dia > 31)
				{
					printf("Fecha inválida\n");
					valido = false;
				}
					
				else
				{
					printf("[DEBUG MESSAGE] : Fecha registrada");
					valido = true;
				}
					
			};


		} while(!valido);


		// Validar dirección
		validarDireccion(fProvedor);
		
		// Escribir estructura en el archivo
		cfptr = fopen("provedor.dat","r+b");
		if (cfptr == NULL)
			{
				printf("[ERROR] - No se pudo escribir en el archivo provedor.dat\n");
				return;
			}
		
		else
			{
				fseek(cfptr,sizeof(struct Provedor) * (fProvedor->claveProvedor - 1) ,SEEK_SET);		
				fwrite(fProvedor,sizeof(struct Provedor),1,cfptr);
				printf("[DEBUG MESSAGE] : Escritura concretada\n");
		};

		fclose(cfptr);
		
    }


};

int claveProvedorExiste(int clave, FILE* fptr,char* fArchivo)
{

	fptr = fopen(fArchivo,"rb");
	bool sobreescrbir;
	char c;
	struct Provedor provedor = {};

	if (fptr == NULL)
		return 2;

	else{

		// Buscar clave
		fseek(fptr,sizeof(struct Provedor) * (clave - 1) ,SEEK_SET);		
		fread(&provedor,sizeof(struct Provedor),1,fptr);

		printf("[DEBUG MESSAJE] Search clave : %d\n",provedor.claveProvedor);

		// Si está vacio no hay nada que actuaizar
		if (provedor.claveProvedor == 0)
			return 0;

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
    //while ((c = getchar()) != '\n' && c != EOF);


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

			//printf("%d %d \n",arrobaPos,i);


			if (correo[i] != '.' || (i-arrobaPos)<2 || i+1==strlen(correo))
				valido = false;

		};



	} while (!valido);
	

};


void validarDireccion(struct Provedor* fProvedor)
{
	bool valido;
	int i,nEspacios;
	char c;

	// Calle
	while ((c = getchar()) != '\n' && c != EOF);

	do
	{	valido = true;
		nEspacios = 0;

		printf("\nIngresa la calle donde vives\n");
		fgets(fProvedor->calle,sizeof(fProvedor->calle),stdin);
		fProvedor->calle[strlen(fProvedor->calle)-1] = '\0';
		
		//fflush(stdin);
		//gets(datos.calle);
		for (i = 0; i < strlen(fProvedor->calle) && valido; i++)
		{	
			if (fProvedor->calle[i] == ' ')
				nEspacios++;

			else if ((fProvedor->calle[i] < 'A' || fProvedor->calle[i] > 'Z') && (fProvedor->calle[i] < 'a' || fProvedor->calle[i] > 'z'))
			{
				printf("Nombre de calle inválida\n");
				valido = false;
				
			}
		};

		// Checar que no sea una cadena Vacia
		if (strlen(fProvedor->calle) == nEspacios)
		{
			printf("Nombre de calle inválida\n");
			valido = false;
		}
			
	}
	while (!valido);

	// Número
	do
	{	
		printf("Ingresa el número de tú casa\n");
		//fflush(stdin);
		fgets(fProvedor->numero,sizeof(fProvedor->numero),stdin);
		valido = true;

		//printf("%s\n",fProvedor->numero);
		//printf("%ld\n",strlen(fProvedor->numero));
		fProvedor->numero[strlen(fProvedor->numero) - 1] = '\0';
		if(strlen(fProvedor->numero) == 0)
		{
			printf("Número de casa incorrecto\n");
			valido = false;
		}

		for (i = 0; i < strlen(fProvedor->numero) && valido; i++)
		{
			if (fProvedor->numero[i] < '0' || fProvedor->numero[i] > '9')
			{
				printf("Número de casa incorrecto\n");
				//printf("\n%s\n",&fProvedor->numero[i]);
				valido = false;
			}	
		}
	}
	while (!valido);

	// Colonia
	do
	{	valido = true;
		nEspacios = 0;
		printf("Ingresa el nombre de la colonia\n");
		fgets(fProvedor->colonia,sizeof(fProvedor->colonia),stdin);
		fProvedor->colonia[strlen(fProvedor->colonia)-1] = '\0';
		
		//fflush(stdin);
		//gets(datos.calle);
		for (i = 0; i < strlen(fProvedor->colonia) && valido; i++)
		{	

			if(fProvedor->colonia[i] == ' ')
				nEspacios++;

			else if ((fProvedor->colonia[i] < 'A' || fProvedor->colonia[i] > 'Z') && (fProvedor->colonia[i] < 'a' || fProvedor->colonia[i] > 'z'))
			{
				printf("Error, nombre inválido\n");
				valido = false;
				
			}
		};

		// Checar que no sea una cadena Vacia
		if (strlen(fProvedor->colonia) == nEspacios)
		{
			printf("Nombre de colonia inválida\n");
			valido = false;
		}
	}
	while (!valido);
	

	// Municipio
	do
	{	valido = true;
		nEspacios = 0;
		printf("Ingresa el nombre del municipio\n");
		fgets(fProvedor->municipio, sizeof(fProvedor->municipio), stdin);
		fProvedor->municipio[strlen(fProvedor->municipio)-1] = '\0';
		
		//fflush(stdin);
		//gets(datos.calle);
		for (i = 0; i < strlen(fProvedor->municipio) && valido; i++)
		{	

			if (fProvedor->municipio[i] == ' ')
				nEspacios++;

			else if ((fProvedor->municipio[i] < 'A' || fProvedor->municipio[i] > 'Z') && (fProvedor->municipio[i] < 'a' || fProvedor->municipio[i] > 'z'))
			{
				printf("Error, nombre inválido\n");
				valido = false;
				
			}
		};

		// Checar que no sea una cadena Vacia
		if (strlen(fProvedor->municipio) == nEspacios)
		{
			printf("Nombre de municipio inválida\n");
			valido = false;
		}
	}
	while (!valido);

	// Estado
	do
	{	valido = true;
		nEspacios = 0;
		printf("Ingresa el nombre del estado\n");
		fgets(fProvedor->estado, sizeof(fProvedor->estado), stdin);
		fProvedor->estado[strlen(fProvedor->estado)-1] = '\0';
		
		//fflush(stdin);
		//gets(datos.calle);
		for (i = 0; i < strlen(fProvedor->estado) && valido; i++)
		{

			if (fProvedor->estado[i] == ' ')
				nEspacios++;

			if ((fProvedor->estado[i] < 'A' || fProvedor->estado[i] > 'Z') && (fProvedor->estado[i] < 'a' || fProvedor->estado[i] > 'z'))
			{
				printf("Error, nombre inválido\n");
				valido = false;
				
			}
		};

		// Checar que no sea una cadena Vacia
		if (strlen(fProvedor->estado) == nEspacios)
		{
			printf("Nombre de estado inválida\n");
			valido = false;
		}

		
	}
	while (!valido);


}

void writeOutput()
{
	//printf("xd");
	FILE* fptr = fopen("provedor.dat","rb");
	FILE *archivo = fopen("Logs/Provedor", "w");

	struct Provedor provedor = {};


	while (fread(&provedor, sizeof(struct Provedor), 1, fptr) == 1)
	{
		if (provedor.claveProvedor != 0)
		{
			fprintf(archivo,"%d %s\n",provedor.claveProvedor,provedor.nombre);
		}
			
		
	}

	fclose(fptr);
	fclose(archivo);


};

void validarRFC(struct Provedor* fProvedor)
{
	bool valido;
	char *rfc = fProvedor->rfc;
	int i;

	printf("[DEBUG MESSAGE] - Se la estamos metiendo a Andres disculpe las molestias\n");

	do
	{	
		valido = true;

		printf("Ingrese su rfc\n");
		fgets(rfc,sizeof(fProvedor->rfc),stdin);
		fProvedor->rfc[strlen(fProvedor->rfc)-1] = '\0';


		if (strlen(rfc) != 13)
		{
			printf("Longitud inválida %ld %s\n",strlen(rfc),rfc);
			valido = false;
		}
			
		else
		{

			// Primeras 4 letras 
			for ( i = 0; i < 4 && valido; i++)
			{
				if (rfc[i] < 'A' || rfc[i] > 'Z')
				{
					valido = false;
					printf("Estructurá inválida del rfc\n");
				}
					
			};

			// 6 números siguientes
			for ( i = 4; i < 10 && valido; i++)
			{
				if (rfc[i] < '0' || rfc[i] > '9')
				{
					valido = false;
					printf("Estructurá inválida del rfc\n");
				}
			};

			// 3 caracteres aleatorios
			for (i = 10; i < 13 && valido; i++)
			{
				if (!isalnum(rfc[i]))
				{
					valido = false;
					printf("Estructurá inválida del rfc\n");
				}
			}
		}

	} while (!valido);
	
	printf("[DEBUGG MESSAGE] - RFC valido\n");
			
	printf("[RFC VALUE] : %s\n",rfc);

}

