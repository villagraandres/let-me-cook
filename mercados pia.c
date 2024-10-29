//la parte de los mercados
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "mercados.h"

//esto si quieren lo ponen en una funcion, yo lo hare asi por comodidad mia


main ()
{
	//si quieren que le cambie el nombre a la variable estructura avisenme
	struct Mercado datos = {};
	FILE *archivo;
	bool registros = true;
	int i, cont1, cont2, cont3;
	char opcion;
	
	archivo = fopen("mercado.dat", "a");
	if (archivo == NULL)
		printf("error al abrir");
	else
	{
		while (registros)
		{
			do
			{
				printf("clave: ");
				scanf("%d", &datos.clave);
				if (datos.clave <= 0)
					printf("clave invalida\n");
			}
			while (datos.clave <= 0);
			
			do 
			{
				printf("nombre: ");
				fflush(stdin);
				gets (datos.nombre);
				cont1 = 0;
				if (strlen(datos.nombre) < 10)
					printf("longitud invalida, asegurese de que sean mas de 10 caracteres\n");
				else
				{
					for (i = 0; i < strlen(datos.nombre); i++)
					{
						if ((datos.nombre[i] < 'A' && datos.nombre > 'Z') || (datos.nombre[i] < 'a' && datos.nombre > 'z') || datos.nombre == ' ')
						{
							printf("hay datos invalidos\n");
							cont1 = 1;
						}
					}
				}
			}
			while (strlen(datos.nombre) < 10 || cont1 == 1);
			
			do
			{
				printf("RFC: ");
				fflush(stdin);
				gets (datos.RFC);
				if (strlen(datos.RFC != 13))
					printf("introduzca su RFC de manera correcta\n");
			}
			while (strlen(datos.RFC != 13));
			
			do
			{
				printf("correo electronico: ");
				fflush(stdin);
				gets(datos.correo_electronico);
				if (strchr(datos.correo_electronico, '@') == NULL || strchr(datos.correo_electronico, '.') == NULL)
					printf("correo invalido\n");
			}
			while (strchr(datos.correo_electronico, '@') == NULL || strchr(datos.correo_electronico, '.') == NULL);
			
			do
			{
				printf("descuento: ");
				scanf("%f", &datos.descuento);
				if (datos.descuento < 0 || datos.descuento > 1)
					printf("dascuento invalido\n");
			}
			while (datos.descuento < 0 || datos.descuento > 1);
			
			do
			{
				printf("a�o de nacimiento: ");
				scanf("%d", &datos.year);
				if (datos.year < 1950 || datos.year > 2006)
					printf("dato invalida\n");
			}
			while (datos.year < 1950 || datos.year > 2006);
			
			do
			{
				printf("mes de nacimiento: ");
				scanf("%d", &datos.mes);
				if (datos.mes < 1 || datos.mes > 12)
					printf("dato invalido\n");
			}
			while(datos.mes < 1 || datos.mes > 12);
			
			do
			{
				printf("dia de nacimiento: ");
				scanf ("%d", &datos.dia);
				cont3 = 0;
				if (datos.mes == 2)
				{
					if (datos.dia < 1 || datos.mes > 28)
					{
						printf("dato invalido\n");
						cont3 = 1;
					}
				}
				
				else if (datos.mes == 1 || datos.mes == 3 || datos.mes == 5 || datos.mes == 7 || datos.mes == 8 || datos.mes == 10 || datos.mes == 12)//31
				{
					if (datos.dia < 1 || datos.mes > 31)
					{
						printf("dato invalido\n");
						cont3 = 1;
					}
				}
				
				else if (datos.mes == 4 || datos.mes == 6 || datos.mes == 9 || datos.mes == 11 )//30
				{
					if (datos.dia < 1 || datos.mes > 31)
					{
						printf("dato invalido\n");
						cont3 = 1;
					}
				}
			}
			while (cont3 == 1);
			
			do
			{
				printf("calle: ");
				fflush(stdin);
				gets(datos.calle);
				cont1 = 0;
				for (i = 0; i < strlen(datos.calle); i++)
				{
					if ((datos.calle[i] < 'A' && datos.calle > 'Z') || (datos.calle[i] < 'a' && datos.calle > 'z') || datos.calle == ' ')
					{
						printf("hay datos invalidos\n");
						cont1 = 1;
					}
				}
			}
			while (cont1 == 1);
			
			do
			{
				printf("numero de calle: ");
				fflush(stdin);
				gets(datos.numero);
				cont1 = 0;
				for (i = 0; i < strlen(datos.numero); i++)
				{
					if (datos.numero[i] < '0' || datos.numero[i] > '9')
						printf("dato invalido\n");
						cont1 = 1;
				}
			}
			while (cont1 == 1);
			
			do
			{
				printf("colonia: ");
				fflush(stdin);
				gets(datos.colonia);
				cont1 = 0;
				for (i = 0; i < strlen(datos.colonia); i++)
				{
					if ((datos.colonia[i] < 'A' && datos.colonia[i] > 'Z') || (datos.colonia[i] < 'a' && datos.colonia[i] > 'z') || datos.colonia[i] == ' ')
					{
						printf("hay datos invalidos\n");
						cont1 = 1;
					}
				}
			}
			while (cont1 == 1);
			do
			{
				printf("municipio: ");
				fflush(stdin);
				gets(datos.municipio);
				cont1 = 0;
				for (i = 0; i < strlen(datos.municipio); i++)
				{
					if ((datos.municipio[i] < 'A' && datos.municipio[i] > 'Z') || (datos.municipio[i] < 'a' && datos.municipio[i] > 'z') || datos.municipio[i] == ' ')
					{
						printf("hay datos invalidos\n");
						cont1 = 1;
					}
				}
			}
			while (cont1 == 1);
			do
			{
				printf("estado: ");
				fflush(stdin);
				gets(datos.estado);
				cont1 = 0;
				for (i = 0; i < strlen(datos.estado); i++)
				{
					if ((datos.estado[i] < 'A' && datos.estado[i] > 'Z') || (datos.estado[i] < 'a' && datos.estado[i]> 'z') || datos.estado[i] == ' ')
					{
						printf("hay datos invalidos\n");
						cont1 = 1;
					}
				}
			}
			while (cont1 == 1);
			
			fseek(archivo, (datos.clave - 1) * sizeof(struct Mercado), SEEK_SET);
			fwrite(&datos, sizeof(struct Mercado), 1, archivo);
			
			do
			{
				printf("hay mas registros? S/N  ");
				scanf("%c", &opcion);
				if (opcion == 'N' || opcion == 'n')
					registros = false;
				else if (opcion != 'N' && opcion != 'n' && opcion != 'S' && opcion != 's')
					printf("opcion invalida\n");
			}
			while(opcion != 'N' && opcion != 'n' && opcion != 'S' && opcion != 's');
		}	
	}
}
