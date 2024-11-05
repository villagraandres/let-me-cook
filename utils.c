#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

//Regresa 0 si es una cadena valida
void clear_input_buffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

void validarCadena(char* cadena)
{	
	bool valido = true;
	int i;
	
	int c;
    while ((c = getchar()) != '\n' && c != EOF); 

	//Tener en cuenta que la ultima letra no tiene /n al utilizar gets
	do
	{	
		//Leer cadena
		printf("Descripcion:\n");
		fflush(stdin);

		fgets(cadena,200,stdin);
		cadena[strlen(cadena)-1] = '\0';

		i = 0;
		valido = true;

		while(i < strlen(cadena) && valido)
		{
			//Eliminar el uso de esas funciones e implementar por mi cuenta las funciones
			if(!isspace(cadena[i]) && !isalnum(cadena[i]))
				valido = false;

			i++;
		};

		//printf("%d %ld\n",valido,strlen(cadena));

	}while(!valido || strlen(cadena) < 9);

	//printf("fin\n");
	
};

void validarNombre(char* nombre)
{
	bool valido = true;
	int i;
	int c;
    while ((c = getchar()) != '\n' && c != EOF);


	//Tener en cuenta que la ultima letra no tiene /n al utilizar gets
	do
	{	
		//Leer cadena
		printf("Nombre:\n");
		fflush(stdin);

		fgets(nombre,200,stdin);
		nombre[strlen(nombre)-1] = '\0';

		i = 0;
		valido = true;

		while(i < strlen(nombre) && valido)
		{
			//Eliminar el uso de esas funciones e implementar por mi cuenta las funciones
			if(!isalpha(nombre[i]) && !isspace(nombre[i]))
				valido = false;

			i++;
		};

		//printf("%d %ld\n",valido,strlen(cadena));

	}while(!valido || strlen(nombre) < 9);

};



