#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include  "ventas.h"
#include "articulos.h"


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
	}
	while(fArticulo->claveArticulo < 0 || fArticulo->claveArticulo > 1000);


	if (!claveExiste(fArticulo->claveArticulo,cfptr,"articulos.dat"))
		actualizarDatos = true;
	else
		actualizarDatos = false;
	
	if(actualizarDatos == true)
	{

		validarCadena(fArticulo->descripcion);


		//Temporada de siembra
		char c;
		while ((c = getchar()) != '\n' && c != EOF); 
		//fflush(stdin);
		printf("\nIngresa la temporada de siembra: ");
		fgets(fArticulo->temporadaSiembra,20,stdin);
		fArticulo->temporadaSiembra[strlen(fArticulo->temporadaSiembra) -1 ]= '\0';

		// Temporada de cosecha
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
							//Preguntarle a que provedor desea comprarle
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
		// Buscar clave
		fseek(fptr,sizeof(struct Articulo) * (clave - 1) ,SEEK_SET);		
		fread(&articulo,sizeof(struct Articulo),1,fptr);


		// Si está vacio no hay nada que actuaizar
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


			printf("%s %ld",datos.nombre,strlen(datos.nombre));

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
		
		// Validar nombre
	validarNombre(datos.nombre);

		// Validar RFC
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
		printf("[DEBUG MESSAJE Descripcion value] : %s\n",fInsumo->descripcion);

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

					// Comprobar que no esté vacío
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

		// Buscar clave
		fseek(fptr,sizeof(struct Insumo) * (clave - 1) ,SEEK_SET);		
		fread(&insumo,sizeof(struct Insumo),1,fptr);

		printf("[DEBUG MESSAJE] Search clave : %d\n",insumo.claveInsumo);

		// Si está vacio no hay nada que actuaizar
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
        // Si regresa false salir del programa
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

		// Descuento
		do
		{
			printf("Ingresa el porcentaje de descuento\n");
			scanf("%f",&fProvedor->descuento);

			if (fProvedor->descuento < 0 && fProvedor->descuento > 100)
				printf("Ingresa un porcentaje válido\n");

		}
		while(fProvedor->descuento < 0 || fProvedor->descuento > 100);

		fProvedor->descuento/=100;
		// RFC
		while ((c = getchar()) != '\n' && c != EOF);
			validarRFC(fProvedor->rfc);


		validarFecha(&fProvedor->anio,&fProvedor->mes,&fProvedor->dia);
		

		// Validar dirección
		validarDireccion(fProvedor->calle,fProvedor->numero,fProvedor->colonia,fProvedor->municipio,fProvedor->estado);
		
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
		}
		fclose(cfptr);
    }
};



void validarFecha(int* ano, int* mes ,int* dia)
{	
	bool valido;

	// Año de nacimiento
	do
	{
		printf("Ingresa año de nacimiento\n");
		scanf("%d",ano);

		if (*ano < 1950 || *ano > 2006)
			printf("Ingresa un año entre 1950 y 2006\n");

	} 
	while (*ano < 1950 || *ano > 2006);


	// Mes de nacimiento
	// Mes
	do
	{
		printf("Ingresa número del mes de nacimiento\n");
		scanf("%d",mes);

		if (*mes < 1 || *mes > 12)
			printf("Ingresa un mes válido\n");

	} 
	while (*mes < 1 || *mes > 12);


	// Nacimiento
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
				printf("[DEBUG MESSAGE] : Fecha registrada");
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
				printf("[DEBUG MESSAGE] : Fecha registrada");
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
				printf("[DEBUG MESSAGE] : Fecha registrada");
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

		printf("[DEBUG MESSAJE] Search clave : %d\n",provedor.claveProvedor);

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
		}
	} 
	while (!valido);
}


void validarDireccion(char* calle,char* numero, char* colonia,char* municipio, char* estado)
{
	bool valido;
	int i,nEspacios;
	char c;

	// Calle
	while ((c = getchar()) != '\n' && c != EOF);

	do
	{	
		valido = true;
		nEspacios = 0;

		printf("\nIngresa la calle donde vives\n");
		fgets(calle,sizeof(calle),stdin);
		calle[strlen(calle)-1] = '\0';
		
		//fflush(stdin);
		//gets(datos.calle);
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

		// Checar que no sea una cadena Vacia
		if (strlen(calle) == nEspacios)
		{
			printf("Nombre de calle inválida\n");
			valido = false;
		}
			
	}
	while (!valido);

	// Número
	while ((c = getchar()) != '\n' && c != EOF);
	do
	{	
		printf("Ingresa el número de tú casa\n");
		//fflush(stdin);
		fgets(numero,sizeof(numero),stdin);
		valido = true;

		//printf("%s\n",fProvedor->numero);
		//printf("%ld\n",strlen(fProvedor->numero));
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
				//printf("\n%s\n",&fProvedor->numero[i]);
				valido = false;
			}	
		}
	}
	while (!valido);

	while ((c = getchar()) != '\n' && c != EOF);
	// Colonia
	do
	{	
		valido = true;
		nEspacios = 0;
		printf("Ingresa el nombre de la colonia\n");
		fgets(colonia,sizeof(colonia),stdin);
		colonia[strlen(colonia)-1] = '\0';
		
		//fflush(stdin);
		//gets(datos.calle);
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

		// Checar que no sea una cadena Vacia
		if (strlen(colonia) == nEspacios)
		{
			printf("Nombre de colonia inválida\n");
			valido = false;
		}
	}
	while (!valido);
	
	while ((c = getchar()) != '\n' && c != EOF);
	// Municipio
	do
	{	
		valido = true;
		nEspacios = 0;
		printf("Ingresa el nombre del municipio\n");
		fgets(municipio, sizeof(municipio), stdin);
		municipio[strlen(municipio)-1] = '\0';
		
		//fflush(stdin);
		//gets(datos.calle);
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

		// Checar que no sea una cadena Vacia
		if (strlen(municipio) == nEspacios)
		{
			printf("Nombre de municipio inválida\n");
			valido = false;
		}
	}
	while (!valido);

	while ((c = getchar()) != '\n' && c != EOF);
	// Estado
	do
	{	
		valido = true;
		nEspacios = 0;
		printf("Ingresa el nombre del estado\n");
		fgets(estado, sizeof(estado), stdin);
		estado[strlen(estado)-1] = '\0';
		
		//fflush(stdin);
		//gets(datos.calle);
		for (i = 0; i < strlen(estado) && valido; i++)
		{
			if (estado[i] == ' ')
				nEspacios++;
			if ((estado[i] < 'A' || estado[i] > 'Z') && (estado[i] < 'a' || estado[i] > 'z'))
			{
				printf("Error, nombre inválido\n");
				valido = false;
			}
		}
		// Checar que no sea una cadena Vacia
		if (strlen(estado) == nEspacios)
		{
			printf("Nombre de estado inválida\n");
			valido = false;
		}
	}
	while (!valido);
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
			// Primeras 4 letras 
			for ( i = 0; i < 4 && valido; i++)
			{
				if (rfc[i] < 'A' || rfc[i] > 'Z')
				{
					valido = false;
					printf("Estructura invalida del rfc\n");
				}
					
			}

			// 6 números siguientes
			for ( i = 4; i < 10 && valido; i++)
			{
				if (rfc[i] < '0' || rfc[i] > '9')
				{
					valido = false;
					printf("Estructurá inválida del rfc\n");
				}
			}

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

	}
	while (!valido);
	
	printf("[DEBUGG MESSAGE] - RFC valido\n");	
	printf("[RFC VALUE] : %s\n",rfc);
}



// Imprime datos del provedor
void EscribirLogProvedor()
{
	
	FILE* fptr = fopen("provedor.dat","rb");
	FILE *archivo = fopen("Logs/Provedor", "w");

	struct Provedor provedor = {};

	fprintf(archivo,"%-20s %-20s %-20s %-40s %-20s %-20s %-20s %-20s %-20s %-20s %-20s %-20s %-20s\n",
	"Clave","Nombre","Rfc","Correo",
	"descuento","Año","Mes","Dia","Calle","Numero","Colonia","Municipio","Estado");

	while (fread(&provedor, sizeof(struct Provedor), 1, fptr) == 1)
	{
		if (provedor.claveProvedor != 0)
			fprintf(archivo,"%-20d %-20s %-20s %-40s %-20.2f %-20d %-20d %-20d %-20s %-20s %-20s %-20s %-20s\n",
			provedor.claveProvedor,provedor.nombre,provedor.rfc,provedor.correo,provedor.descuento,
			provedor.anio,provedor.mes,provedor.dia,provedor.calle,provedor.numero,provedor.colonia,
			provedor.municipio,provedor.estado);
	}

	fclose(fptr);
	fclose(archivo);
}

void EscribirLogInsumo()
{
	FILE* fptr = fopen("insumos.dat","rb");
	if (fptr == NULL) 
	{
		printf("[ERROR] - No se pudo abrir el archivo insumos.dat\n");
		return;
	}

	FILE *archivo = fopen("Logs/Insumo", "w");
	if (archivo == NULL) 
	{
		printf("[ERROR] - No se pudo abrir el archivo Logs/Insumo\n");
		fclose(fptr);
		return;
	}

	struct Insumo insumo= {};

	fprintf(archivo,"%-20s %-100s %-20s %-20s\n",
	"Clave","Descipcion","Punto Reorden" ,"Inventario");

	while (fread(&insumo, sizeof(struct Insumo), 1, fptr) == 1)
	{
		if (insumo.claveInsumo != 0)
		{
			fprintf(archivo,"%-20d%-100s%-20d%-20d\n",insumo.claveInsumo,insumo.descripcion,insumo.puntoReorden,insumo.inventario);
			fprintf(archivo,"%-20s %-20s\n","Provedore Clave","Precio");
			for ( int i = 0; i < 10; i++)
			{	

				if (insumo.provedores[i] != 0)
					fprintf(archivo,"%-20d %-20.2f\n",insumo.provedores[i],insumo.precios[i]);
			}

			fprintf(archivo,"\n\n");
		}
	}
	fclose(fptr);
	fclose(archivo);
}


// Imprimir datos de Articulos

void EscribirLogArticulo()
{

	FILE* fptr = fopen("articulos.dat","rb");
	FILE *archivo = fopen("Logs/Articulo", "w");

	struct Articulo articulo = {};

	fprintf(archivo,"%-20s %-20s %-20s %-20s %-20s %-20s %-20s\n",
	"Clave","Nombre","Temporada Siembra","Temporada Cosecha","Costo","Precio","Inventario");

	while (fread(&articulo, sizeof(struct Articulo), 1, fptr) == 1)
	{
		if (articulo.claveArticulo != 0)
		{	
			fprintf(archivo,"%-20d %-20s %-20s %-20s %-20.2f %-20.2f %-20d\n",
			articulo.claveArticulo,articulo.descripcion,articulo.temporadaSiembra,articulo.temporadaCosecha,
			articulo.costo,articulo.precio,articulo.inventario);
			
			fprintf(archivo,"%-20s\n","Clave Mercados");
			for ( int i = 0; i < 10; i++)
			{	
				if (articulo.claveMercados[i] != 0)
					fprintf(archivo,"%-20d\n",articulo.claveMercados[i]);
			}

			fprintf(archivo,"%-20s\n","Clave Insumos");
			for ( int i = 0; i < 10; i++)
			{	
				if (articulo.insumosRequeridos[i] != 0)
					fprintf(archivo,"%-20d\n",articulo.insumosRequeridos[i]);
			}
			fprintf(archivo,"\n\n");
		}
	}
	
	fclose(fptr);
	fclose(archivo);
};

void EscribirLogMercado()
{
	FILE* fptr = fopen("mercado.dat","rb");
	if (fptr == NULL) 
	{
		printf("[ERROR] - No se pudo abrir el archivo mercado.dat\n");
		return;
	}

	FILE *archivo = fopen("Logs/Mercado", "w");
	if (archivo == NULL) 
	{
		printf("[ERROR] - No se pudo abrir el archivo Logs/Insumo\n");
		fclose(fptr);
		return;
	}

	struct Mercado mercado= {};

	fprintf(archivo,"%-20s %-20s %-20s %-20s %-20s %-20s  %-20s %-20s %-20s %-20s %-20s %-20s %-20s \n"
	,"Clave","Nombre","Rfc","Correo","Descuento","Año","Mes","Dia","Calle","Numero","Colonia","Municipio"
	, "Estado");

	while (fread(&mercado, sizeof(struct Mercado), 1, fptr))
	{
		if (mercado.clave != 0 || mercado.anio != 0)
		{
			fprintf(archivo,"%-20d %-20s %-20s %-20s %-20.2f %-20d  %-20d %-20d %-20s %-20s %-20s %-20s %-20s \n\n"
			,mercado.clave,mercado.nombre,mercado.RFC,mercado.correo_electronico,
			mercado.descuento,mercado.anio,mercado.mes,mercado.dia,
			mercado.calle,mercado.numero,mercado.colonia,mercado.municipio,mercado.estado
			);
		}
	}
	fclose(fptr);
	fclose(archivo);
}