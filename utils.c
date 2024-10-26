#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

//Regresa 0 si es una cadena valida
void validarCadena(char* cadena)
{	
	bool valido = true;
	int i;
	
	//Tener en cuenta que la ultima letra no tiene /n al utilizar gets
	do
	{	
		//Leer cadena
		printf("Descripcion:\n");
		fflush(stdin);
		fgets(cadena,200,stdin);
		i = 0;
		valido = true;

		while(i < strlen(cadena) && valido)
		{
			//Eliminar el uso de esas funciones e implementar por mi cuenta las funciones
			if(!isspace(cadena[i]) && !isalnum(cadena[i]))
				valido = false;

			i++;
		};

	}while(!valido && strlen(cadena) > 9);
	
}

