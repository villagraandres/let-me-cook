#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "articulos.h"
#include <time.h>
#include <stdlib.h>


void menuArticulos()
{
	bool continuar;
	char c;
	struct Articulo articulo = {};


	do
	{
		printf("Desea agregar un articulo S/N)");
		scanf(" %c",&c);

		if (c=='S' || c=='s')
			continuar = true;
		else if(c=='N' || c == 'n')
			continuar = false;
		else
			printf("Ingrese una opción válida");
	}
	while(c!='S' && c!= 's' && c!= 'N' && c!= 'n');

	while(continuar)
	{
		lecturaArticulo(&articulo);
		do
		{
			printf("Desea agregar un articulo S/N)");
			scanf(" %c",&c);

			if (c=='S' || c=='s')
				continuar = true;
			else if(c=='N' || c == 'n')
				continuar = false;
			else
				printf("Ingrese una opción válida");
		}
		while(c!='S' && c!= 's' && c!= 'N' && c!= 'n');
	}
}


void lecturaArticulo(struct Articulo* fArticulo)
{
	FILE* cfptr;
	bool actualizarDatos;
	bool continuar;
	int i = 0;
	int clave;
	char c;

	
	struct Articulo articulo = {};
	struct Mercado mercado = {};
	struct Insumo insumo = {};
	

	
	do
	{
		printf("Clave del articulo:\n");
		scanf("%d",&fArticulo->claveArticulo);

		if (fArticulo->claveArticulo < 0 || fArticulo->claveArticulo > 1000)
			printf("Ingresa un número entre 1 y 1000");
	}
	while(fArticulo->claveArticulo < 0 || fArticulo->claveArticulo > 1000);


	if (!claveExiste(fArticulo->claveArticulo,cfptr,"articulos.dat"))
		actualizarDatos = true;
	else
		actualizarDatos = false;
	
	if(actualizarDatos == true)
	{

		validarCadena(fArticulo->descripcion);


		
		char c;
		while ((c = getchar()) != '\n' && c != EOF); 
		
		printf("\nIngresa la temporada de siembra: ");
		fgets(fArticulo->temporadaSiembra,20,stdin);
		fArticulo->temporadaSiembra[strlen(fArticulo->temporadaSiembra) -1 ]= '\0';

		
		while ((c = getchar()) != '\n' && c != EOF); 
		printf("\n Ingresa la temporada de cosecha: ");
		fflush(stdin);
		fgets(fArticulo->temporadaCosecha,20,stdin);
		fArticulo->temporadaCosecha[strlen(fArticulo->temporadaCosecha) -1 ]= '\0';
		

        cfptr = fopen("mercado.dat","rb");
		if (cfptr == NULL)
            printf("Error al abrir archivo mercado.dat\n");
		else
		{
			i = 0;
			continuar = true;
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
						fseek(cfptr,sizeof(struct Mercado) * (clave - 1) ,SEEK_SET);		
						fread(&mercado,sizeof(struct Mercado),1,cfptr);
	

						if (mercado.clave == 0)
							printf("Ingresa una clave registrada\n");
						else
							{
								fArticulo->claveMercados[i] = clave;
								i++;
								printf("Clave %d registrada con éxito\n",mercado.clave);
							}
					}
				}while (clave <= 0);

					if (i<10)
					{
						do
						{
							printf("Desea agregar otro mercado S/N)");
							scanf(" %c",&c);

							if (c=='S' || c=='s')
									continuar = true;
							else if(c=='N' || c == 'n')
									continuar = false;
							else
									printf("Ingrese una opción válida");
							}while(c!='S' && c!= 's' && c!= 'N' && c!= 'n');
					}
				} while (i<10 && continuar);    
		
			fclose(cfptr);
		}

        
		cfptr = fopen("insumos.dat","rb");
		if (cfptr == NULL)
			printf("Error al abrir archivo insumos.dat\n");
		else
		{
			i = 0;
			continuar = true;
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

						fseek(cfptr,sizeof(struct Insumo) * (clave - 1) ,SEEK_SET);		
						fread(&insumo,sizeof(struct Insumo),1,cfptr);


						if (insumo.claveInsumo == 0)
							printf("Ingresa una clave registrada\n");
						else
						{
							fArticulo->insumosRequeridos[i] = clave;
							
							preguntarProvedor(fArticulo,&insumo);
							i++;
							printf("Clave %d registrada con éxito\n",insumo.claveInsumo);
						}
						
					}
				}while (clave <= 0);


				if (i<10)
				{
				
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
				}
			}while (i<10 && continuar);

        	fclose(cfptr);
        }
		do
		{
			printf("\n5) Inventario: ");
			scanf("%d",&fArticulo->inventario);

			if (fArticulo->inventario < 0 )
				printf("Ingrese una cantidad válida\n");

		} 
		while (fArticulo->inventario < 0 );

		do
		{
			printf("6) Precio de venta: ");
			scanf("%f",&fArticulo->precio);

			if (fArticulo->precio < 0 )
				printf("Ingrese una cantidad válida\n");

		} 
		while (fArticulo->precio < 0 );

		cfptr = fopen("articulos.dat","r+b");
		if (cfptr == NULL)
		{
			printf("[ERROR] - No se pudo escribir en el archivo articulos.dat\n");
			return;
		}
		else
		{	
			fseek(cfptr,sizeof(struct Articulo) * (fArticulo->claveArticulo - 1) ,SEEK_SET);
			fwrite(fArticulo,sizeof(struct Articulo),1,cfptr);
		}
		fclose(cfptr);
	}
}

void inicializarRegistrosArticulos(char* nombreArchivo)
{
	FILE* cfptr;
	struct Articulo articulo = {};	

	if (existeArchivo(cfptr,nombreArchivo))
		crearArchivo(cfptr,nombreArchivo,&articulo,1000,sizeof(struct Articulo));
}

int claveExiste(int clave, FILE* fptr,char* fArchivo)
{
	fptr = fopen(fArchivo,"rb");
	bool sobreescrbir;
	char c;
	struct Articulo articulo = {};
	
	if (fptr == NULL)
		return 2;

	else
	{
		
		fseek(fptr,sizeof(struct Articulo) * (clave - 1) ,SEEK_SET);		
		fread(&articulo,sizeof(struct Articulo),1,fptr);


		
		if (articulo.claveArticulo == 0)
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

		}
		while (c!='S' && c!= 's' && c!= 'N' && c!= 'n');

		fclose(fptr);

		if(sobreescrbir)
			return 0;
		else 
			return 1;
	}
}

void preguntarProvedor(struct Articulo* fArticulo,struct Insumo* fInsumo)
{	
	int i,provedor;
	float precio;
	bool valido;

	do
	{	
		printf("%-20s %-20s\n","Provedor","Precio");

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

	} 
	while (!valido);
}




bool validarCorreoE(const char* correo)
{
    const char* at = strchr(correo, '@');
	
    if (at == NULL)
        return false;
    const char* dot = strrchr(at, '.');
    if (dot == NULL)
        return false;
    return dot > at;
}

void empleadoMenu()
{
    struct Empleado datos = {};
    FILE *archivo;
    bool registros = true;
    int i, cont1, cont3;
    char opcion;

    archivo = fopen("empleados.dat", "rb+");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo\n");
        return;
    }

    setbuf(stdout, NULL);

    while (registros)
    {
        do
        {
            printf("Clave: ");
            scanf("%d", &datos.numero_empleado);
            if (datos.numero_empleado < 1 || datos.numero_empleado > 1000)
                printf("Número inválido\n");
        }
        while (datos.numero_empleado < 1 || datos.numero_empleado > 1000);


		clear_input_buffer();

        do
        {
            printf("Nombre: \n");
            
            fgets(datos.nombre, sizeof(datos.nombre), stdin);
            datos.nombre[strlen(datos.nombre) - 1] = '\0';
            cont1 = 0;

            if (strlen(datos.nombre) < 10)
            {
                printf("Longitud inválida, asegúrese de que sean más de 10 caracteres\n");
                cont1 = 1;
            }
            else
            {
                for (i = 0; i < strlen(datos.nombre); i++)
                {
                    if (!isalpha(datos.nombre[i]) && datos.nombre[i] != ' ')
                    {
                        printf("Hay datos inválidos\n");
                        cont1 = 1;
                        break;
                    }
                }
            }
        }
        while (cont1 == 1);


		validarRFC(datos.rfc);

        clear_input_buffer();
		validarCorreo(datos.correo_electronico);

        do
        {
            printf("Comisión: ");
            scanf("%f", &datos.comision);
            if (datos.comision < 0 || datos.comision > 100)
                printf("Comision inválida\n");
        }
        while (datos.comision < 0 || datos.comision > 100);

        datos.comision /= 100;

        validarFecha(&datos.anos,&datos.mes,&datos.dia);

		validarDireccion(datos.calle,datos.numero,datos.colonia,datos.municipio,datos.estado);


        fseek(archivo, (datos.numero_empleado - 1) * sizeof(struct Empleado), SEEK_SET);
        fwrite(&datos, sizeof(struct Empleado), 1, archivo);

        do
        {
            printf("¿Hay más registros? S/N: ");
            clear_input_buffer();
            scanf(" %c", &opcion);
            if (opcion == 'N' || opcion == 'n')
                registros = false;
            else if (opcion != 'N' && opcion != 'n' && opcion != 'S' && opcion != 's')
                printf("Opción inválida\n");
        }
        while (opcion != 'N' && opcion != 'n' && opcion != 'S' && opcion != 's');
    }

    fclose(archivo);
}

void inicializarRegistrosEmpleados(char* nombreArchivo)
{
    FILE* cfptr;
    struct Empleado empleadoInfo = {};

    if (existeArchivo(cfptr, nombreArchivo) == 1)
    {
        if (crearArchivo(cfptr, nombreArchivo, &empleadoInfo, 1000, sizeof(struct Empleado)) != 0)
        {
            printf("Error al crear el archivo\n");
            return;
        }
    }
}




void  mercados_main()
{	
    struct Mercado datos = {};
    FILE *archivo;
    bool registros = true;
    char opcion;
    bool valido;
    int i, cont1;

    archivo = fopen("mercado.dat", "r+b");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo\n");
        return;
    }


    while (registros)
    {
        do
        {
            printf("\nClave: ");
            scanf("%d", &datos.clave);
            if (datos.clave <= 0)
                printf("Clave invalida\n");
        }
        while (datos.clave <= 0);
		
		
	validarNombre(datos.nombre);

		
	validarRFC(datos.RFC);
	
        validarCorreo(datos.correo_electronico);

	do
	{
		printf("\nDescuento: ");
		scanf("%f", &datos.descuento);

		if (datos.descuento < 0 || datos.descuento > 100)
			printf("Ingresa un porcentaje\n");

	} 
	while (datos.descuento < 0 || datos.descuento > 100);
		
	datos.descuento /= 100;
    clear_input_buffer();



	do
	{
		printf("Ingresa año de nacimiento\n");
		scanf("%d",&datos.anio);

		if (datos.anio < 1950 || datos.anio > 2006)
			printf("Ingresa un año entre 1950 y 2006\n");

	} 
	while (datos.anio < 1950 || datos.anio > 2006);



	do
	{
		printf("Ingresa número del mes de nacimiento\n");
		scanf("%d",&datos.mes);

		if (datos.mes < 1 || datos.mes > 12)
			printf("Ingresa un mes válido\n");

	} 
	while (datos.mes < 1 || datos.mes > 12);



	do
	{
		printf("Ingresa el día del mes\n");
		scanf("%d",&datos.dia);

		if (datos.dia < 1 || datos.dia > 31)
		{
			printf("Ingresa un día válido");
			valido = false;
		}
				
		else if (datos.mes == 2)
		{
			if (datos.anio%4 == 0 && datos.dia > 29)
			{
				printf("Fecha inválida\n");
				valido = false;
			}
					
			else if(datos.anio%4 != 0 && datos.dia > 28)
			{
				printf("Fecha inválida");
				valido = false;
			}
					
			else
			{

				valido = true;
			}

		}
		else if(datos.mes != 1 && (datos.mes%5 == 1 || datos.mes%5 == 4))
		{
			if(datos.dia > 30)
			{
				printf("Fecha inválida\n");
				valido =  false;
			}
					
			else
			{

				valido = true;
			}	
					
		}
		else
		{
			if(datos.dia > 31)
			{
				printf("Fecha inválida\n");
				valido = false;
			}
					
			else
			{

				valido = true;
			}		
		}
	} 
	while(!valido);


	validarDireccion(datos.calle,datos.numero,datos.colonia,datos.municipio,datos.estado);


        fseek(archivo,sizeof(struct Mercado)*(datos.clave-1),SEEK_SET);
        if (fwrite(&datos, sizeof(struct Mercado), 1, archivo) != 1)
            printf("Error al escribir en el archivo\n");
	else
	    printf("CORRECTA ESCRITUTA\n");

	printf("%s %d\n",datos.nombre,datos.clave);

        do
        {

            printf("¿Hay más registros? S/N: ");
        	clear_input_buffer();

            scanf(" %c",&opcion);
            printf("%c\n",opcion);
            if (opcion == 'S' || opcion == 's')
                registros = true;
            
            else if (opcion == 'N' || opcion == 'n')
                registros = false;
            else if (opcion != 'N' && opcion != 'n' && opcion != 'S' && opcion != 's')
                printf("Opción invalida\n");
        }
        while (opcion != 'N' && opcion != 'n' && opcion != 'S' && opcion != 's');
    }
    fclose(archivo);
}

void inicializarRegistrosMercados(char *nombreArchivo)
{
    FILE* cfptr;
    struct Mercado mercadoInfo = {0};

    if (existeArchivo(cfptr, nombreArchivo) == 1)
    {
        if (crearArchivo(cfptr, nombreArchivo, &mercadoInfo, 1000, sizeof(struct Mercado)) != 0)
        {
            printf("Error al crear el archivo\n");
            return;
        }
    }
}





void menuInsumos()
{
	bool continuar;
	char c;
	struct Insumo insumo = {};


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

	}
	while(c!='S' && c!= 's' && c!= 'N' && c!= 'n');

	while(continuar)
	{

		lecturaInsumo(&insumo);

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

		}
		while(c!='S' && c!= 's' && c!= 'N' && c!= 'n');

	}
}


void inicializarRegistrosInsumos(char* nombreArchivo)
{
	FILE* cfptr;
	struct Insumo insumo = {};	

	if (existeArchivo(cfptr,nombreArchivo))
		crearArchivo(cfptr,nombreArchivo,&insumo,100,sizeof(struct Insumo));
}

void lecturaInsumo(struct Insumo* fInsumo)
{
	FILE* cfptr;
	bool actualizarDatos;
	bool continuar;
	int i,clave;
	float precio;
	char c;

	struct Insumo insumo;
	struct Provedor provedor = {};

	do
	{
		printf("Clave del insumo:\n");
		scanf("%d",&fInsumo->claveInsumo);

		if (fInsumo->claveInsumo < 1 || fInsumo->claveInsumo > 100)
			printf("Ingresa un número entre 1 y 100\n");
	}
	while(fInsumo->claveInsumo < 1 || fInsumo->claveInsumo > 100);

	if (!claveInsumoExiste(fInsumo->claveInsumo,cfptr,"insumos.dat"))
		actualizarDatos = true;
	else
		actualizarDatos = false;
	

	if(actualizarDatos == true)
	{

		validarCadena(fInsumo->descripcion);
		

		do
		{
			printf("\n3) Punto de reorden: \n");
			scanf("%d",&fInsumo->puntoReorden);

			if (fInsumo->puntoReorden <= 0)
				printf("\n[ERROR] agrega un valor mayor que 0\n");

		}
		while(fInsumo->puntoReorden <= 0);

		do
		{
			printf("\n4) Inventario: \n");
			scanf("%d",&fInsumo->inventario);

			if (fInsumo->inventario < 0)
				printf("\n[ERROR] agrega un valor mayor o igual a 0\n");
		
		}
		while(fInsumo->inventario < 0);

		i = 0;

		cfptr = fopen("provedor.dat","rb");
		if (cfptr == NULL)
		{
			printf("[ERROR] - No se pudo leer el archivo provedor.dat\n");
		}
		
		else
		{
			do
			{	
				do
				{
					printf("Ingresa la clave del provedor\n >");
					scanf("%d",&clave);

					if(clave < 1 || clave > 100)
					{
						printf("Ingresa una clave entre 1 y 100\n");
						continue;
					}
						
					fseek(cfptr,(clave - 1) * sizeof(struct Provedor),SEEK_SET);
					fread(&provedor,sizeof(struct Provedor),1,cfptr);

					
					if(provedor.claveProvedor == 0)
						printf("[ERROR MESSAGE] - Clave %d no registrada\n ",clave);
					else
					{
						printf("CLAVE REGISTRADA\n");
						fInsumo->provedores[i] = provedor.claveProvedor;

						do
						{
							printf("Ingresa el precio del provedor\n");
							scanf("%f",&precio);

							if (precio<=0)
								printf("Ingresa un valor mayor que 0\n");

						} 
						while (precio <= 0);

						*(fInsumo->precios+i) = precio;
						i++;

					}
						
					do
					{
						printf("Desea agregar otro provedor al insumo? S/N)");
						scanf(" %c",&c);

						if (c=='S' || c=='s')
							continuar = true;
						else if(c=='N' || c == 'n')
							continuar = false;
						else
							printf("Ingrese una opción válida");

					}
					while(c!='S' && c!= 's' && c!= 'N' && c!= 'n');

				}
				while (clave < 1 || clave > 100);
			} 
			while (i<10 && continuar);
			fclose(cfptr);
		}

		cfptr = fopen("insumos.dat","r+b");
		if (cfptr == NULL)
		{
			printf("[ERROR] - No se pudo escribir en el archivo insumos.dat\n");
			return;
		}
		
		else
		{
			fseek(cfptr,sizeof(struct Insumo) * (fInsumo->claveInsumo - 1) ,SEEK_SET);		
			fwrite(fInsumo,sizeof(struct Insumo),1,cfptr);
		}
		fclose(cfptr);
	}	
}

int claveInsumoExiste(int clave, FILE* fptr,char* fArchivo)
{
	fptr = fopen(fArchivo,"rb");
	bool sobreescrbir;
	char c;
	struct Insumo insumo = {};

	if (fptr == NULL)
		return 1;

	else
	{

		
		fseek(fptr,sizeof(struct Insumo) * (clave - 1) ,SEEK_SET);		
		fread(&insumo,sizeof(struct Insumo),1,fptr);

		

		
		if (insumo.claveInsumo == 0)
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

		} 
		while (c!='S' && c!= 's' && c!= 'N' && c!= 'n');

		fclose(fptr);

		if(sobreescrbir)
			return 0;

		else 
			return 1;
	}
}





void menuProvedor()
{
    bool continuar;
    char c;
    struct Provedor provedor = {};


    do
    {   
        clear_input_buffer();
        printf("Desea agregar un provedor S/N)");
        scanf(" %c",&c);

        if (c=='S' || c=='s')
            continuar = true;
        else if(c=='N' || c == 'n')
            continuar = false;
        else
            printf("Ingrese una opción válida");

	}
	while(c!='S' && c!= 's' && c!= 'N' && c!= 'n');

    while(continuar)
    {
        clear_input_buffer();
	    lecturaProvedor(&provedor);

        do
        {
            printf("Desea agregar otro provedor S/N)");
            scanf(" %c",&c);

            if (c=='S' || c=='s')
                continuar = true;
            else if(c=='N' || c == 'n')
                continuar = false;
            else
                printf("Ingrese una opción válida");

            }
            while(c!='S' && c!= 's' && c!= 'N' && c!= 'n');
	}

}


void inicializarRegistrosProvedor(char* nombreArchivo)
{
	FILE* cfptr;
	struct Provedor provedor = {};	

	if (existeArchivo(cfptr,nombreArchivo))
        
		crearArchivo(cfptr,nombreArchivo,&provedor,100,sizeof(struct Provedor));
}



void lecturaProvedor(struct Provedor* fProvedor)
{
	char c;
	FILE* cfptr;
	bool actualizarDatos,valido;

	struct Provedor provedor = {};

	do
	{
		printf("Clave del Provedor:\n");
		scanf("%d",&fProvedor->claveProvedor);

		if (fProvedor->claveProvedor < 1 || fProvedor->claveProvedor > 100)
			printf("Ingresa un número entre 1 y 100\n");
	}
	while(fProvedor->claveProvedor < 1 || fProvedor->claveProvedor > 100);

	if (claveProvedorExiste(fProvedor->claveProvedor,cfptr,"provedor.dat"))
		actualizarDatos = false;
	else
		actualizarDatos = true;

	if(actualizarDatos == true)
    {
        validarNombre(fProvedor->nombre);

        validarCorreo(fProvedor->correo);

		
		do
		{
			printf("Ingresa el porcentaje de descuento\n");
			scanf("%f",&fProvedor->descuento);

			if (fProvedor->descuento < 0 && fProvedor->descuento > 100)
				printf("Ingresa un porcentaje válido\n");

		}
		while(fProvedor->descuento < 0 || fProvedor->descuento > 100);

		fProvedor->descuento/=100;
		
		while ((c = getchar()) != '\n' && c != EOF);
		
        validarRFC(fProvedor->rfc);


		validarFecha(&fProvedor->anio,&fProvedor->mes,&fProvedor->dia);
		
		validarDireccion(fProvedor->calle,fProvedor->numero,fProvedor->colonia,fProvedor->municipio,fProvedor->estado);
		
		
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
			
		}
		fclose(cfptr);
    }
};



void validarFecha(int* ano, int* mes ,int* dia)
{	
	bool valido;

	
	do
	{
		printf("Ingresa año de nacimiento\n");
		scanf("%d",ano);

		if (*ano < 1950 || *ano > 2006)
			printf("Ingresa un año entre 1950 y 2006\n");

	} 
	while (*ano < 1950 || *ano > 2006);


	
	
	do
	{
		printf("Ingresa número del mes de nacimiento\n");
		scanf("%d",mes);

		if (*mes < 1 || *mes > 12)
			printf("Ingresa un mes válido\n");

	} 
	while (*mes < 1 || *mes > 12);


	
	do
	{
		printf("Ingresa el día del mes\n");
		scanf("%d",dia);

		if (*dia < 1 || *dia > 31)
		{
			printf("Ingresa un día válido");
			valido = false;
		}
			
		else if (*mes == 2)
		{
			if (*ano%4 == 0 && *dia > 29)
			{
				printf("Fecha inválida\n");
				valido = false;
			}
				
			else if(*ano%4 != 0 && *dia > 28)
			{
				printf("Fecha inválida");
				valido = false;
			}
				
			else
			{
				
				valido = true;
			}

		}
		else if(*mes != 1 && (*mes%5 == 1 || *mes%5 == 4))
		{
			if(*dia > 30)
			{
				printf("Fecha inválida\n");
				valido =  false;
			}
				
			else
			{
				
				valido = true;
			}	
				
		}
		else
		{

			if(*dia > 31)
			{
				printf("Fecha inválida\n");
				valido = false;
			}
				
			else
			{
				
				valido = true;
			}
				
		}

	} 
	while(!valido);

};



int claveProvedorExiste(int clave, FILE* fptr,char* fArchivo)
{
	fptr = fopen(fArchivo,"rb");
	bool sobreescrbir;
	char c;
	struct Provedor provedor = {};

	if (fptr == NULL)
		return 2;

	else
	{
		fseek(fptr,sizeof(struct Provedor) * (clave - 1) ,SEEK_SET);
		fread(&provedor,sizeof(struct Provedor),1,fptr);

		

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

		} 
		while (c!='S' && c!= 's' && c!= 'N' && c!= 'n');

		fclose(fptr);

		if(sobreescrbir)
			return 0;

		else 
			return 1;
	}
}



void validarCorreo(char* correo)
{
    	bool valido;
	int i,c,arrobaPos;
    
	do
	{
		printf("Ingresa tu correo electronico:\n");
		fgets(correo,100,stdin);
		correo[strlen(correo)-1] = '\0';

		i = 0;
		valido = true;

		
		while(i<strlen(correo) && i!='@' && isalnum(correo[i]))i++;
		
		if (correo[i] != '@' || i<1)
			valido = false;

		
		if (valido)
		{	
			arrobaPos = i;
			i++;
			while(i<strlen(correo) && i!='.' && isalnum(correo[i]))i++;

			
			if (correo[i] != '.' || (i-arrobaPos)<2 || i+1==strlen(correo))
				valido = false;
		}
	}while (!valido);
}


void validarDireccion(char* calle,char* numero, char* colonia,char* municipio, char* estado)
{
	bool valido;
	int i,nEspacios;
	char c;

	
	while ((c = getchar()) != '\n' && c != EOF);

	do
	{	
		valido = true;
		nEspacios = 0;

		printf("\nIngresa la calle donde vives\n");
		fgets(calle,sizeof(calle),stdin);
		calle[strlen(calle)-1] = '\0';
		
		
		
		for (i = 0; i < strlen(calle) && valido; i++)
		{	
			if (calle[i] == ' ')
				nEspacios++;
			else if ((calle[i] < 'A' || calle[i] > 'Z') && (calle[i] < 'a' || calle[i] > 'z'))
			{
				printf("Nombre de calle inválida\n");
				valido = false;
			}
		}

		
		if (strlen(calle) == nEspacios)
		{
			printf("Nombre de calle inválida\n");
			valido = false;
		}
			
	}while (!valido);

	
	while ((c = getchar()) != '\n' && c != EOF);
	do
	{	
		printf("Ingresa el número de tú casa\n");
		
		fgets(numero,sizeof(numero),stdin);
		valido = true;

		
		
		numero[strlen(numero) - 1] = '\0';
		if(strlen(numero) == 0)
		{
			printf("Número de casa incorrecto\n");
			valido = false;
		}

		for (i = 0; i < strlen(numero) && valido; i++)
		{
			if (numero[i] < '0' || numero[i] > '9')
			{
				printf("Número de casa incorrecto\n");
				
				valido = false;
			}	
		}
	}while (!valido);

    clear_input_buffer();
	do
	{	
		valido = true;
		nEspacios = 0;
		printf("Ingresa el nombre de la colonia\n");
		fgets(colonia,sizeof(colonia),stdin);
		colonia[strlen(colonia)-1] = '\0';
		
		
		
		for (i = 0; i < strlen(colonia) && valido; i++)
		{	

			if(colonia[i] == ' ')
				nEspacios++;

			else if ((colonia[i] < 'A' || colonia[i] > 'Z') && (colonia[i] < 'a' || colonia[i] > 'z'))
			{
				printf("Error, nombre inválido\n");
				valido = false;
				
			}
		}

		
		if (strlen(colonia) == nEspacios)
		{
			printf("Nombre de colonia inválida\n");
			valido = false;
		}
	}while (!valido);
	
	while ((c = getchar()) != '\n' && c != EOF);
	
	do
	{	
		valido = true;
		nEspacios = 0;
		printf("Ingresa el nombre del municipio\n");
		fgets(municipio, sizeof(municipio), stdin);
		municipio[strlen(municipio)-1] = '\0';
		
		
		
		for (i = 0; i < strlen(municipio) && valido; i++)
		{	
			if (municipio[i] == ' ')
				nEspacios++;
			else if ((municipio[i] < 'A' || municipio[i] > 'Z') && (municipio[i] < 'a' || municipio[i] > 'z'))
			{
				printf("Error, nombre inválido\n");
				valido = false;
			}
		}

		
		if (strlen(municipio) == nEspacios)
		{
			printf("Nombre de municipio inválida\n");
			valido = false;
		}
	}while (!valido);

	while ((c = getchar()) != '\n' && c != EOF);
	
	do
	{	
		valido = true;
		nEspacios = 0;
		printf("Ingresa el nombre del estado\n");
		fgets(estado, 100, stdin);
		estado[strlen(estado)-1] = '\0';
		
		
		for (i = 0; i < strlen(estado) && valido; i++)
		{
			if (estado[i] == ' ')
				nEspacios++;
			else if ((estado[i] < 'A' || estado[i] > 'Z') && (estado[i] < 'a' || estado[i] > 'z'))
			{
				printf("Error, nombre inválido\n");
				valido = false;
			}
		}
		
		if (strlen(estado) == nEspacios)
		{
			printf("Nombre de estado inválida\n");
			valido = false;
		}
	}while (!valido);

    clear_input_buffer();
}


void validarRFC(char* rfc)
{
	bool valido;
	int i;


	do
	{	
		valido = true;

		printf("Ingrese su rfc\n");
		fgets(rfc,15,stdin);
		rfc[strlen(rfc)-1] = '\0';


		if (strlen(rfc) != 13)
		{
			printf("Longitud inválida %ld %s\n",strlen(rfc),rfc);
			valido = false;
		}
			
		else
		{
			
			for ( i = 0; i < 4 && valido; i++)
			{
				if (rfc[i] < 'A' || rfc[i] > 'Z')
				{
					valido = false;
					printf("Estructura invalida del rfc\n");
				}
					
			}

			
			for ( i = 4; i < 10 && valido; i++)
			{
				if (rfc[i] < '0' || rfc[i] > '9')
				{
					valido = false;
					printf("Estructurá inválida del rfc\n");
				}
			}

			
			for (i = 10; i < 13 && valido; i++)
			{
				if (!isalnum(rfc[i]))
				{
					valido = false;
					printf("Estructurá inválida del rfc\n");
				}
			}
		}

	}
	while (!valido);
	
	
	printf("[RFC VALUE] : %s\n",rfc);
}



void obtenerFecha(struct tm *fecha);

void menuVenta() 
{
    FILE *archivoMercados, *archivoArticulos, *archivoEmpleados, *archivoVentas;
    struct Venta ventas[100];
    struct Mercado datosMercado;
    int numVentas = 0;
    float precioTotal = 0, precioArt;
    char respuesta;
    struct tm fecha;
    
    obtenerFecha(&fecha);

    archivoVentas = fopen("ventas.txt", "a");
    if (archivoVentas == NULL)
    {
        printf("Error al abrir el archivo de ventas\n");
        return;
    }

    archivoMercados = fopen("mercado.dat", "rb+"); 
    if (archivoMercados == NULL) 
    {
        printf("No existe ningun mercado registrado\n");
        fclose(archivoVentas);
        return;
    }

    archivoArticulos = fopen("articulos.dat", "rb+");
    if (archivoArticulos == NULL) 
    {
        printf("No existe ningún artículo registrado\n");
        fclose(archivoMercados);
        fclose(archivoVentas);
        return;
    }

    archivoEmpleados = fopen("empleados.dat", "rb+");
    if (archivoEmpleados == NULL) 
    {
        printf("No hay ningún empleado registrado\n");
        fclose(archivoMercados);
        fclose(archivoArticulos);
        fclose(archivoVentas);
        return;
    }

    printf("\nControl de Ventas\n");
    printArchivoMercados(archivoMercados);
    do 
    {
        printf("Número de Mercado: ");
        do 
        {
            scanf("%d", &ventas[numVentas].numeroMercado);
        } 
        while (!validarExistencia(ventas[numVentas].numeroMercado, 1, archivoMercados, archivoArticulos));

        printArchivoArticulos(archivoArticulos);
        printf("\nNúmero de Artículo: ");
        do
        {
            scanf("%d", &ventas[numVentas].numeroArticulo);
        } 
        while (!validarExistencia(ventas[numVentas].numeroArticulo, 2, archivoMercados, archivoArticulos));

        printf("\nIngrese la cantidad del Artículo: ");
        do 
        {
            scanf("%d", &ventas[numVentas].cantidad);
        } 
        while (!validarCantidad(ventas[numVentas].numeroArticulo, &ventas[numVentas].cantidad, archivoArticulos));

        printf("¿Desea agregar otro artículo? (S/N): ");
        scanf(" %c", &respuesta);

        numVentas++;
    } 
    while (respuesta == 'S' || respuesta == 's');

    printArchivoEmpleados(archivoEmpleados);
    do 
    {
        printf("Ingresa el número de empleado: ");
        scanf("%d", &ventas[0].empleado);
    } 
    while (!validarEmpleado(archivoEmpleados, ventas[0].empleado));

    for (int i = 0; i < numVentas; i++) 
    {
        fseek(archivoMercados, sizeof(struct Mercado) * (ventas[i].numeroMercado - 1), SEEK_SET);
        fread(&datosMercado, sizeof(struct Mercado), 1, archivoMercados);
        precioArt = (obtenerPrecioArticulo(ventas[i].numeroArticulo, archivoArticulos) * ventas[i].cantidad) * datosMercado.descuento;
        precioTotal += precioArt;
        fprintf(archivoVentas, "%d %d %f %d %d %d %d\n", ventas[i].numeroArticulo, ventas[i].cantidad, precioArt, ventas[i].empleado, fecha.tm_mday, fecha.tm_mon + 1, fecha.tm_year + 1900);
        fflush(archivoVentas); 
    }

    printf("El precio total de la venta es: %.2f\n", precioTotal);

    printf("¿Requiere factura? (S/N): ");
    scanf(" %c", &respuesta);
    if (respuesta == 'S' || respuesta == 's') 
    {
        generarFactura(ventas, numVentas, precioTotal, ventas[0].empleado);
    }

    fclose(archivoArticulos);
    fclose(archivoMercados);
    fclose(archivoEmpleados);
    fclose(archivoVentas);
}

bool validarEmpleado(FILE *archivoEmpleado, int empleadoId) 
{
    struct Empleado empleadoInfo = {};
    fseek(archivoEmpleado, sizeof(struct Empleado) * (empleadoId - 1), SEEK_SET);
    fread(&empleadoInfo, sizeof(struct Empleado), 1, archivoEmpleado);

    if (empleadoInfo.numero_empleado == 0) 
    {
        printf("El empleado no existe\n");
        return false;
    }
    return true;
}

bool validarCantidad(int claveArticulo, int *cantidad, FILE *archivo) 
{
    struct Articulo articulo;
    int opcion;

    fseek(archivo, sizeof(struct Articulo) * (claveArticulo - 1), SEEK_SET);
    fread(&articulo, sizeof(struct Articulo), 1, archivo);

    if (*cantidad <= 0) 
    {
        printf("Debes ingresar una cantidad mayor a 0\n");
        return false;
    }

    if (articulo.inventario < *cantidad) 
    {
        printf("No hay suficientes unidades para el producto que quieres\n");
        printf("Cantidad actual: %d\n", articulo.inventario);
        printf("1) Elegir otro producto \n2) Actualizar cantidad del producto actual\n");
        scanf("%d", &opcion);

        if (opcion == 1) 
        {
            return false;
        } 
        else if (opcion == 2) 
        {
            do 
            {
                printf("Ingresa la nueva cantidad: ");
                scanf("%d", cantidad);
            } 
            while (*cantidad <= 0 || *cantidad > articulo.inventario);
        }
    }

    articulo.inventario -= *cantidad;
    fseek(archivo, sizeof(struct Articulo) * (claveArticulo - 1), SEEK_SET);
    fwrite(&articulo, sizeof(struct Articulo), 1, archivo);
    fflush(archivo); 

    return true;
}

bool validarExistencia(int clave, int modo, FILE *archivoMercados, FILE *archivoArticulos) 
{
    if (clave <= 0) 
    {
        printf("Clave inválida\n");
        return false;
    }

    if (modo == 1) 
    {
        struct Mercado mercado;
        fseek(archivoMercados, sizeof(struct Mercado) * (clave-1), SEEK_SET);
        fread(&mercado, sizeof(struct Mercado), 1, archivoMercados);
        


        if (mercado.clave == 0) 
        {
            printf("El mercado no existe\n");
            return false;
        }
        return true;
    } 
    else 
    {
        struct Articulo articulo;
        fseek(archivoArticulos, sizeof(struct Articulo) * (clave - 1), SEEK_SET);
        fread(&articulo, sizeof(struct Articulo), 1, archivoArticulos);

        if (articulo.claveArticulo == 0) 
        {
            printf("La clave del producto no existe\n");
            return false;
        }
        return true;
    }
}

float obtenerPrecioArticulo(int claveArticulo, FILE *archivo) 
{
    struct Articulo articulo;

    fseek(archivo, sizeof(struct Articulo) * (claveArticulo - 1), SEEK_SET);
    fread(&articulo, sizeof(struct Articulo), 1, archivo);

    return articulo.precio;
}

void generarFactura(struct Venta ventas[], int numVentas, float total, int empleadoId)
{
	printf("\n====================================\n");
	printf("               FACTURA              \n");
	printf("====================================\n");
	printf("Empleado ID: %d\n\n", empleadoId);
	printf("Artículo       Cantidad\n");
	printf("------------------------------------\n");

	for (int i = 0; i < numVentas; i++)
	{
		printf("%-15d %d unidades\n", ventas[i].numeroArticulo, ventas[i].cantidad);
	}

	printf("------------------------------------\n");
	printf("Total a pagar: $%.2f\n", total);
	printf("====================================\n\n");
}


void printArchivoMercados(FILE *archivoMercados) 
{
    struct Mercado mercadoInfo;
    rewind(archivoMercados);
    printf("\nContenido de archivoMercados:\n");
    while (fread(&mercadoInfo, sizeof(struct Mercado), 1, archivoMercados)) 
    {
        if(mercadoInfo.clave!=0) {
            printf("Clave: %d\n", mercadoInfo.clave);

        }
    }
    rewind(archivoMercados);
}


void printArchivoArticulos(FILE *archivoArticulos) 
{
    struct Articulo articuloInfo;
    rewind(archivoArticulos);
    printf("\nContenido de archivoArticulos:\n");
    while (fread(&articuloInfo, sizeof(struct Articulo), 1, archivoArticulos)) 
    {
        if(articuloInfo.claveArticulo!=0)
            printf("Clave: %d, Inventario: %d, Precio: %f\n", articuloInfo.claveArticulo, articuloInfo.inventario, articuloInfo.precio);
    }
    rewind(archivoArticulos);
}


void printArchivoEmpleados(FILE *archivoEmpleados) 
{
    FILE *archivo = fopen("empleados.dat", "rb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo\n");
        return;
    }

    struct Empleado empleado;
    while (fread(&empleado, sizeof(struct Empleado), 1, archivo) == 1) {
        if (empleado.numero_empleado != 0) {
            printf("Número de Empleado: %d\n", empleado.numero_empleado);
        }
    }
    fclose(archivo);
}


void obtenerFecha(struct tm *fecha) 
{
    time_t t = time(NULL);
    *fecha = *localtime(&t);

    mktime(fecha);
}





void menuCompra() 
{
    FILE *archivoProv, *archivoIns,*archivoCompras;
    int numeroProvedor, numeroInsumo, cantidad, comprasCont = 0;
    char respuesta;
    float precioTotal = 0;
    struct Insumo insumoInfo;
    int idCompra;

    archivoCompras=fopen("compras.txt","a+");
    if(archivoCompras==NULL) 
    {
        printf("Error al abrir el archivo de compras");
        return;
    }
    idCompra = obtenerUltimoID(archivoCompras)+1;

    archivoProv = fopen("provedor.dat", "rb+");
    if (archivoProv == NULL) 
    {
        printf("No existe ningun provedor registrado\n");
        return;
    }

    archivoIns = fopen("insumos.dat", "rb+");
    if (archivoIns == NULL) 
    {
        printf("No existe ningun insumo registrado\n");
        return;
    }

    do 
    {
        printf("Ingrese el numero del provedor: ");
        scanf("%d", &numeroProvedor);
    } 
    while (!validarExistenciaPI(archivoProv, 1, numeroProvedor, -1));

    do 
    {
        do 
        {
            printf("Ingrese el numero del insumo: ");
            scanf("%d", &numeroInsumo);
        } 
        while (!validarExistenciaPI(archivoIns, 2, numeroInsumo, -1) ||
                !validarExistenciaPI(archivoIns, 3, numeroInsumo, numeroProvedor));

        do 
        {
            printf("Ingrese la cantidad deseada: ");
            scanf("%d", &cantidad);
        } 
        while (cantidad < 0);

        precioTotal += obtenerPrecio(numeroInsumo, numeroProvedor, archivoIns) * cantidad;

        printf("\nDesea agregar otro insumo? (S/N): ");
        scanf(" %c", &respuesta);


        fseek(archivoIns,sizeof(struct Insumo)*(numeroInsumo-1),SEEK_SET);
        fread(&insumoInfo,sizeof(struct Insumo),1,archivoIns);
        fprintf(archivoCompras, "%d %d |%s| %d %d %d\n", idCompra, numeroInsumo, insumoInfo.descripcion,cantidad,numeroProvedor,0);

    }
    while (respuesta == 'S' || respuesta == 's');

    printf("El precio total es: %.2f\n", precioTotal);
    fclose(archivoCompras);
    fclose(archivoIns);
}

float obtenerPrecio(int idInsumo, int idProvedor, FILE *insumoArch) {
    struct Insumo insumoInfo;
    fseek(insumoArch, sizeof(struct Insumo) * (idInsumo - 1), SEEK_SET);
    fread(&insumoInfo, sizeof(struct Insumo), 1, insumoArch);

    for (int i = 0; i < 10; i++) 
    {
        if (insumoInfo.provedores[i] == idProvedor) 
            return insumoInfo.precios[i];
    }

    printf("El insumo %d no tiene un precio asociado para el proveedor %d\n", idInsumo, idProvedor);
    return 0.0;
}

bool validarExistenciaPI(FILE *archivoPtr, int modo, int id, int idProvedor) 
{
    if (modo == 1) 
    {
        struct Provedor provInfo;
        fseek(archivoPtr, sizeof(struct Provedor) * (id - 1), SEEK_SET);
        fread(&provInfo, sizeof(struct Provedor), 1, archivoPtr);
        if (provInfo.claveProvedor == 0) 
        {
            printf("El provedor seleccionado no existe\n");
            return false;
        }
    } 
    else if (modo == 2) 
    {
        struct Insumo insumoInfo;
        fseek(archivoPtr, sizeof(struct Insumo) * (id - 1), SEEK_SET);
        fread(&insumoInfo, sizeof(struct Insumo), 1, archivoPtr);
        if (insumoInfo.claveInsumo == 0) 
        {
            printf("El insumo seleccionado no existe\n");
            return false;
        }
    } 
    else if (modo == 3) 
    {
        struct Insumo insumoInfo;
        fseek(archivoPtr, sizeof(struct Insumo) * (id - 1), SEEK_SET);
        fread(&insumoInfo, sizeof(struct Insumo), 1, archivoPtr);

        for (int i = 0; i < 10; i++) 
        {
            if (insumoInfo.provedores[i] == idProvedor) 
                return true;
        }
        printf("El proveedor %d no ofrece el insumo %d\n", idProvedor, id);
        return false;
    }
    return true;
}


int obtenerUltimoID(FILE *archivoCompras) 
{
    int ultimoID = 0, tempID;
    char buffer[256];  
    rewind(archivoCompras);  

    
    while (fgets(buffer, sizeof(buffer), archivoCompras) != NULL) 
    {
        
        if (sscanf(buffer, "%d", &tempID) == 1) 
            ultimoID = tempID;
    }
    return ultimoID;
}


void menuReporte() 
{
    char opcion;

    do
    {
        do 
        {
            printf("Reportes\n");
            printf("a) Listado de articulos\n");
            printf("b) Total de venta por fecha\n");
            printf("c) Total de venta por articulo\n");
            printf("d) Listado de insumos a solicitar\n");
            printf("e) Saldos por pagar\n");
            printf("f) Calculo de comisiones\n");
            printf("g) Compras pendientes de recepcion\n");
            printf("h) Salir\n\n");
            scanf(" %c",&opcion);
            printf("Opcion seleccionada: %c\n", opcion);
        }
        while (opcion<'a' || opcion>'h');

        switch (opcion) 
        {
            case 'a':
                listadoArticulos();
            break;
            case 'b':
                ventaFecha();
            break;
            case 'c': {
	            FILE *archivoV=fopen("ventas.txt","r+");
            	if(archivoV==NULL)
            	{
            		printf("No existe ninguna venta registrada");
            	}
            	else
            	{
            		listadoventaArticulos(archivoV);
            	}
            }
            break;
            
            case 'd':

            {
            	FILE *archivoI = fopen("insumos.dat", "rb+");
            	if (archivoI == NULL)
            	{
            		printf("No existe ningun insumo registrado\n");
            	}
            	else
            	{
            		listadoInsumos(archivoI);
            	}
            }
                break;

            case 'e':
            {
	            FILE *archivoC=fopen("compras.txt","r+");
            	if(archivoC==NULL)
            	{
            		printf("No existe ninguna compra registrada");
            	}
            	else
            	{
            		listadoSaldos(archivoC);
            	}
            	fclose(archivoC);
            }
                break;

            case 'f':
                listadoEmpleadosComision();
            break;
            case 'g': {
	            FILE *archivoCo=fopen("compras.txt","r+");
            	if(archivoCo==NULL)
            	{
            		printf("No existe ninguna compra registrada");
            	}
            	else
            	{
            		listadoPendientes(archivoCo);
            	}
            	fclose(archivoCo);
            }
                break;



        }

    }
    while(opcion != 'h' && opcion != 'H');
}

void listadoPendientes(FILE *archivo) {
    int idCompra, numeroInsumo, cantidad, numeroProvedor, cero;
    char descripcion[100];
    int vistos[1000];
    printf("\n%-10s %-20s %-25s %-12s %-15s\n", "Clave", "Numero Insumo", "descripcion", "Cantidad", "Provedor");

    while (fscanf(archivo, "%d %d |%[^|]| %d %d %d\n", &idCompra, &numeroInsumo, descripcion, &cantidad, &numeroProvedor, &cero) == 6)
    {
        if(cero==0)
        {
            printf("\n%-10d %-20d %-25s %-12d %-15d\n", idCompra, numeroInsumo, descripcion, cantidad, numeroProvedor);

        }

    }
}
void listadoSaldos(FILE *archivoC)
{
    int idCompra, numeroInsumo, cantidad, numeroProvedor, cero;
    char descripcion[100];
    int vistos[1000];
    int i=0,j;
    FILE *archivoProveedores=fopen("provedor.dat","rb");

    while (fscanf(archivoC, "%d %d |%[^|]| %d %d %d\n", &idCompra, &numeroInsumo, descripcion, &cantidad, &numeroProvedor, &cero) == 6)
    {
        if(!existeNumero(vistos,i,numeroProvedor,0) && cero==0)
        {
            vistos[i]=numeroProvedor;
            i++;
        }
    }

    struct Provedor provedorInfo;
    printf("\n%-10s %-20s %-25s %-12s %-15s\n", "Clave", "Nombre", "Correo", "Descuento", "RFC");
    printf("----------------------------------------------------------------------------------------\n");

    for (j = 0; j < i; j++) {
        fseek(archivoProveedores, sizeof(struct Provedor) * (vistos[j] - 1), SEEK_SET);
        fread(&provedorInfo, sizeof(struct Provedor), 1, archivoProveedores);
        printf("%-10d %-20s %-25s %-12.2f %-15s\n",
               provedorInfo.claveProvedor,
               provedorInfo.nombre,
               provedorInfo.correo,
               provedorInfo.descuento,
               provedorInfo.rfc);
    }
    if(i==0) {
        printf("No existen registros\n");
    }
    fclose(archivoProveedores);

}

void listadoInsumos(FILE *archivoInsumos) 
{
    FILE *archivoCompras = fopen("compras.txt", "r");
    if (archivoCompras == NULL) 
    {
        printf("No hay ninguna compra registrada\n");
        return;
    }

    struct Insumo insumo;
    int idCompra, numeroInsumo, cantidad, numeroProvedor, cero;
    bool yaOrdenado;
	char descripcion[100];

    printf("\nInsumos a solicitar:\n");

    rewind(archivoInsumos);
    while (fread(&insumo, sizeof(struct Insumo), 1, archivoInsumos)) 
    {
        if (insumo.inventario < insumo.puntoReorden) 
        {
            yaOrdenado = false;
            rewind(archivoCompras);
            while (fscanf(archivoCompras, "%d %d |%[^|]| %d %d %d\n", &idCompra, &numeroInsumo, descripcion, &cantidad, &numeroProvedor, &cero) == 6) {
                if (numeroInsumo == insumo.claveInsumo) 
                {
                    yaOrdenado = true;
                    break;
                }
            }
            if (!yaOrdenado) 
            {
                printf("Insumo ID: %d, Descripcion: %s, Inventario: %d, Punto de Reorden: %d\n", insumo.claveInsumo, insumo.descripcion, insumo.inventario, insumo.puntoReorden);
            }
        }
    }
    fclose(archivoCompras);
}

void listadoventaArticulos(FILE *archivoV) 
{
    int articuloId;
    int mes,dia,numeroArticulo,cantidad,empleado,ano;
    float precio,total=0;
    FILE *archivoArt=fopen("articulos.dat","rb+");
    if(archivoArt==NULL) 
    {
        printf("Error al abrir el archivo de articulos");
    }

    do 
    {
        printf("Ingrese el id del articulo que desea buscar");
        scanf("%d",&articuloId);
    }
    while (!validarArticulo(archivoArt,articuloId));

    while (fscanf(archivoV,"%d %d %f %d %d %d %d",&numeroArticulo,&cantidad,&precio,&empleado,&dia,&mes,&ano) == 7) 
    {
        if(numeroArticulo==articuloId)
            total+=precio;
    }
    if(total!=0) 
        printf("En total se ha vendido $%f\n",total);
    else 
        printf("No hay ventas registradas para ese articulo\n");
    fclose(archivoArt);
}

bool validarArticulo(FILE *archivof,int id) 
{
    struct Articulo articulo;
    fseek(archivof, sizeof(struct Articulo) * (id - 1), SEEK_SET);
    fread(&articulo, sizeof(struct Articulo), 1, archivof);

    if (articulo.claveArticulo == 0) 
    {
        printf("La clave del producto no existe\n");
        return false;
    }
    return true;
}

void ventaFecha() 
{
    FILE *archivoV=fopen("ventas.txt","r+");
    int mes,dia,mes2,dia2,numeroArticulo,cantidad,empleado,ano;
    float precio,total=0;

    if(archivoV==NULL) 
    {
        printf("No existe ninguna venta registrada\n");
        return;
    }
    do 
    {
        printf("Ingrese el mes de la venta que desea buscar\n");
        scanf("%d",&mes);
    }
    while(mes>12 || mes<0);

    do 
    {
        printf("Ingrese el dia de la venta que desea buscar\n");
        scanf("%d",&dia);
    }
    while(dia>31|| dia<0);

    while (fscanf(archivoV,"%d %d %f %d %d %d %d",&numeroArticulo,&cantidad,&precio,&empleado,&dia2,&mes2,&ano) == 7) 
    {
        if(dia2==dia || mes==mes2)
            total+=precio;
    }
    if(total!=0) 
        printf("el total fue de $%.2f\n",total);
    else 
        printf("No hay ninguna venta registrada en esa fecha");
}
void listadoArticulos()
{
	FILE *archivoArt = fopen("articulos.dat", "rb");
	if (archivoArt == NULL)
	{
		printf("No existe ningún artículo registrado\n");
	}
	else
	{
		struct Articulo articuloInfo;
		char *descripciones[100];  // Arreglo de apuntadores para descripciones
		int i = 0;

		printf("\n%-15s %-20s %-15s %-15s %-10s\n",
			   "Clave", "Descripcion", "Costo", "Precio", "Inventario");
		printf("-------------------------------------------------------------------------------\n");

		// Leer y almacenar descripciones
		while (fread(&articuloInfo, sizeof(struct Articulo), 1, archivoArt) && i < 100)
		{
			if (articuloInfo.claveArticulo != 0)
			{
				// Almacenar la descripción en el arreglo de apuntadores
				descripciones[i] = (char *)malloc(strlen(articuloInfo.descripcion) + 1);
				strcpy(descripciones[i], articuloInfo.descripcion);

				printf("%-15d %-20s %-15.2f %-15.2f %-10d\n",
					   articuloInfo.claveArticulo,
					   descripciones[i],
					   articuloInfo.costo,
					   articuloInfo.precio,
					   articuloInfo.inventario);

				i++;
			}
		}

		// Liberar la memoria asignada
		for (int j = 0; j < i; j++)
		{
			free(descripciones[j]);
		}

		fclose(archivoArt);
	}
}

void listadoEmpleadosComision()
{
    FILE *ptrVentas = fopen("ventas.txt", "r");
    FILE *ptrEmpleados = fopen("empleados.dat", "rb");
    struct Empleado empleado = {};
    struct Venta venta = {};

    int dia, mes, anio;
    float totalVentas;  

    if (ptrVentas == NULL)
        printf("No se pudo abrir el archivo ventas.txt\n");
    else if (ptrEmpleados == NULL)
        printf("No se pudo abrir el archivo empleados.dat\n");
    else
    {
        rewind(ptrEmpleados);

        while (fread(&empleado, sizeof(struct Empleado), 1, ptrEmpleados))
        {
            if (empleado.numero_empleado > 0)
            {
                printf("Empleado: %s, Numero: %d\n", empleado.nombre, empleado.numero_empleado);

                totalVentas = 0.0;

                rewind(ptrVentas);
                while (fscanf(ptrVentas, "%d %d %f %d %d %d %d", &venta.numeroArticulo, &venta.cantidad, &venta.precio, &venta.empleado, &dia, &mes, &anio) != EOF)
                {
                    if (venta.empleado == empleado.numero_empleado)
                    {

                        totalVentas += venta.cantidad * venta.precio;
                    }
                }


                if (totalVentas > 0)
                {
                    float comisionCalculada = totalVentas * empleado.comision;
                    printf("La comision correspondiente para %s es de %.2f pesos argentinos\n", empleado.nombre, comisionCalculada);
                }
                else
                {
                    printf("No hay ventas registradas para %s\n", empleado.nombre);
                }
            }
        }
        fclose(ptrEmpleados);
        fclose(ptrVentas);
    }
}




int existeArchivo(FILE* fptr, char* fArchivo)
{
    fptr = fopen(fArchivo, "rb");

    if (fptr == NULL) 
        return 1;  
    else 
    {
        fclose(fptr);
        return 0;  
    }
}

int crearArchivo(FILE* fptr, char* fArchivo, void* estructura, int cantidadEstructuras, int tamanoEstructura)
{
    fptr = fopen(fArchivo, "wb");

    if (fptr == NULL) 
        return 1;

    for (int i = 0; i < cantidadEstructuras; ++i) 
    {
        fwrite(estructura, tamanoEstructura, 1, fptr);
    }
    fclose(fptr);
    return 0;
}


void clear_input_buffer() 
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void validarCadena(char* cadena)
{
    bool valido = true;
    int i;
    int c;
    
    while ((c = getchar()) != '\n' && c != EOF);

    
    do
    {
        
        printf("Descripcion:\n");
        fflush(stdin);

        fgets(cadena,200,stdin);
        cadena[strlen(cadena)-1] = '\0';

        i = 0;
        valido = true;

        while(i < strlen(cadena) && valido)
        {
            
            if(!isspace(cadena[i]) && !isalnum(cadena[i]))
                valido = false;

            i++;
        }

        

    }
    while(!valido || strlen(cadena) < 9);
    
}

void validarNombre(char* nombre)
{
    bool valido = true;
    int i;
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    
    
    do
    {   
        
        printf("Nombre:\n");
        fflush(stdin);

        fgets(nombre,200,stdin);
        nombre[strlen(nombre)-1] = '\0';


        

        i = 0;
        valido = true;

        while(i < strlen(nombre) && valido)
        {
            
            if(!isalpha(nombre[i]) && !isspace(nombre[i]))
                valido = false;
                

            i++;
        }
        
    }
    while(!valido || strlen(nombre) < 9);
}




void menuControl() 
{
    FILE *archivoProv, *archivoCompras, *insumoArch;
    int idCompra, numeroInsumo, cantidad, numeroProvedor, cero, provedorId, ultimo = -1;
    char descripcion[100];
    int vistos[1000], i = 0, numeroCompra, recibida;
    float precio, total = 0;
    struct Insumo insumosInfo;

    archivoProv = fopen("provedor.dat", "rb");
    if (archivoProv == NULL) 
    {
        printf("No hay ningun provedor registrado\n");
        return;
    }

    archivoCompras = fopen("compras.txt", "r+");  
    if (archivoCompras == NULL) 
    {
        printf("No hay ninguna compra registrada\n");
        fclose(archivoProv);  
        return;
    }

    insumoArch = fopen("insumos.dat", "rb");
    if (insumoArch == NULL) 
    {
        printf("No hay ningun archivo de insumos\n");
        fclose(archivoProv);  
        fclose(archivoCompras);  
        return;
    }

    do 
    {
        printf("\n1) Numero de provedor: ");
        scanf("%d", &provedorId);
    } 
    while (!validarProvedor(provedorId, archivoProv));

    printf("\n%15s %15s %15s %15s\n", "ID Compra", "Numero Insumo", "Descripcion", "Proveedor");

    while (fscanf(archivoCompras, "%d %d |%[^|]| %d %d %d\n", &idCompra, &numeroInsumo, descripcion, &cantidad, &numeroProvedor, &cero) == 6) 
    {
        if (numeroProvedor == provedorId) 
        {
            if (ultimo != -1 && idCompra != ultimo) 
            {
                printf("Total: %.2f\n", total);
                total = 0;
            }

            total += obtenerPrecio(numeroInsumo, numeroProvedor, insumoArch) * cantidad;

            if (numeroProvedor == provedorId && cero == 0) 
                printf("%15d %15d %15s %15d\n", idCompra, numeroInsumo, descripcion, numeroProvedor);

            ultimo = idCompra;
            vistos[i] = idCompra;
            i++;
        }
    }

    if (ultimo != -1) 
        printf("Total: %.2f\n", total);

    do 
    {
        printf("\nNumero de compra: ");
        scanf("%d", &numeroCompra);

    } 
    while (!existeNumero(vistos, i, numeroCompra,1));

    printf("\nLa orden fue recibida? 1: si 2: no");
    scanf("%d", &recibida);

    if (recibida == 1) 
    {
        FILE *archivoTemp = fopen("compras_temp.txt", "w+");  
        if (archivoTemp == NULL) 
        {
            printf("No se pudo crear el archivo temporal\n");
            return;
        }

        rewind(archivoCompras);

        while (fscanf(archivoCompras, "%d %d |%[^|]| %d %d %d\n", &idCompra, &numeroInsumo, descripcion, &cantidad, &numeroProvedor, &cero) == 6) 
        {
            if (numeroCompra == idCompra) 
                cero = 1;

            fseek(insumoArch,sizeof(struct Insumo)*(numeroInsumo-1),SEEK_SET);
            fread(&insumosInfo,sizeof(struct Insumo),1,insumoArch);
            insumosInfo.inventario+=cantidad;
            fseek(insumoArch, sizeof(struct Insumo) * (numeroInsumo - 1), SEEK_SET);
            fwrite(&insumosInfo, sizeof(struct Insumo), 1, insumoArch);

            fprintf(archivoTemp, "%d %d |%s| %d %d %d\n", idCompra, numeroInsumo, descripcion, cantidad, numeroProvedor, cero);
        }

        fclose(archivoCompras);
        fclose(archivoTemp);

        remove("compras.txt");  
        rename("compras_temp.txt", "compras.txt");

        printf("La orden ha sido marcada como recibida.\n");
    }
    fclose(archivoProv);
    fclose(insumoArch);
}

bool validarProvedor(int id, FILE *archivof) 
{
    struct Provedor datosB;
    fseek(archivof, sizeof(struct Provedor) * (id-1), SEEK_SET);
    fread(&datosB, sizeof(struct Provedor), 1, archivof);

    if (datosB.claveProvedor == 0) 
    {
        printf("El provedor no existe\n");
        return false;
    }
    return true;
}


int existeNumero(int arreglo[], int tam, int numero,int modo)
{
    for (int i = 0; i < tam; i++) 
    {
        if (arreglo[i] == numero) 
            return 1;
    }
    if(modo==1) {
        printf("El numero indicado no existe");
    }

    return 0;
}
