#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include  "ventas.h"
#include "articulos.h"
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
				fseek(cfptr,sizeof(struct Articulo) * (fArticulo->claveArticulo-1) ,SEEK_SET);
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

//EMPLEADOS





void inicializar_registrosEmpleado();

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
    inicializar_registrosEmpleado();
    struct Empleado datos = {0, "", "", "", 0, 0, 0, 0, "", 0, "", "", ""};
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

        do
        {
            printf("Nombre: ");
            clear_input_buffer();
            fgets(datos.nombre, sizeof(datos.nombre), stdin);
            datos.nombre[strcspn(datos.nombre, "\n")] = 0;
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

        printf("RFC: ");
        while (getchar() != '\n');
        fgets(datos.rfc, sizeof(datos.rfc), stdin);
        datos.rfc[strcspn(datos.rfc, "\n")] = 0;


        printf("Correo electrónico: ");
        clear_input_buffer();
        fgets(datos.correo_electronico, sizeof(datos.correo_electronico), stdin);
        datos.correo_electronico[strcspn(datos.correo_electronico, "\n")] = 0;




        do
        {
            printf("Comisión: ");
            scanf("%f", &datos.comision);
            if (datos.comision < 0 || datos.comision > 100)
                printf("Comision inválida\n");
        }
        while (datos.comision < 0 || datos.comision > 100);

        do
        {
            printf("Año de nacimiento: ");
            scanf("%d", &datos.year);
            if (datos.year < 1950 || datos.year > 2006)
                printf("Dato inválido\n");
        }
        while (datos.year < 1950 || datos.year > 2006);

        do
        {
            printf("Mes de nacimiento: ");
            scanf("%d", &datos.mes);
            if (datos.mes < 1 || datos.mes > 12)
                printf("Dato inválido\n");
        }
        while (datos.mes < 1 || datos.mes > 12);

        do
        {
            printf("Día de nacimiento: ");
            scanf("%d", &datos.dia);
            cont3 = 0;
            if (datos.mes == 2)
            {
                if (datos.dia < 1 || datos.dia > 28)
                {
                    printf("Dato inválido\n");
                    cont3 = 1;
                }
            }
            else if (datos.mes == 1 || datos.mes == 3 || datos.mes == 5 || datos.mes == 7 || datos.mes == 8 || datos.mes == 10 || datos.mes == 12)
            {
                if (datos.dia < 1 || datos.dia > 31)
                {
                    printf("Dato inválido\n");
                    cont3 = 1;
                }
            }
            else if (datos.mes == 4 || datos.mes == 6 || datos.mes == 9 || datos.mes == 11)
            {
                if (datos.dia < 1 || datos.dia > 30)
                {
                    printf("Dato inválido\n");
                    cont3 = 1;
                }
            }
        }
        while (cont3 == 1);

        do
        {
            printf("Calle: ");
            clear_input_buffer();
            fgets(datos.calle, sizeof(datos.calle), stdin);
            datos.calle[strcspn(datos.calle, "\n")] = 0;
            cont1 = 0;
            for (i = 0; i < strlen(datos.calle); i++)
            {
                if (!isalpha(datos.calle[i]) && datos.calle[i] != ' ')
                {
                    printf("Hay datos inválidos\n");
                    cont1 = 1;
                    break;
                }
            }
        }
        while (cont1 == 1);

        do
        {
            printf("Número de calle: ");
            scanf("%d", &datos.numero);
            if (datos.numero < 1)
                printf("Dato inválido\n");
        }
        while (datos.numero < 1);

        do
        {
            printf("Colonia: ");
            clear_input_buffer();
            fgets(datos.colonia, sizeof(datos.colonia), stdin);
            datos.colonia[strcspn(datos.colonia, "\n")] = 0;
            cont1 = 0;
            for (i = 0; i < strlen(datos.colonia); i++)
            {
                if (!isalpha(datos.colonia[i]) && datos.colonia[i] != ' ')
                {
                    printf("Hay datos inválidos\n");
                    cont1 = 1;
                    break;
                }
            }
        }
        while (cont1 == 1);

        do
        {
            printf("Municipio: ");
            clear_input_buffer();
            fgets(datos.municipio, sizeof(datos.municipio), stdin);
            datos.municipio[strcspn(datos.municipio, "\n")] = 0;
            cont1 = 0;
            for (i = 0; i < strlen(datos.municipio); i++)
            {
                if (!isalpha(datos.municipio[i]) && datos.municipio[i] != ' ')
                {
                    printf("Hay datos inválidos\n");
                    cont1 = 1;
                    break;
                }
            }
        }
        while (cont1 == 1);

        do
        {
            printf("Estado: ");
            clear_input_buffer();
            fgets(datos.estado, sizeof(datos.estado), stdin);
            datos.estado[strcspn(datos.estado, "\n")] = 0;
            cont1 = 0;
            for (i = 0; i < strlen(datos.estado); i++)
            {
                if (!isalpha(datos.estado[i]) && datos.estado[i] != ' ')
                {
                    printf("Hay datos inválidos\n");
                    cont1 = 1;
                    break;
                }
            }
        }
        while (cont1 == 1);

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

void inicializar_registrosEmpleado()
{
    char nombreArchivo[] = "empleados.dat";
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







void inicializar_registros();

void mercados_main()
{
    inicializar_registros();
    struct Mercado datos = {0, "", "", "", 0, 0, 0, 0, "", 0, "", "", ""};
    FILE *archivo;
    bool registros = true;
    char opcion;
    int i, cont1;

    archivo = fopen("mercado.dat", "rb+");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo\n");
        return;
    }

    while (registros)
    {
        do
        {
            printf("Clave: ");
            scanf("%d", &datos.clave);
            if (datos.clave <= 0)
                printf("Clave invalida\n");
        }
        while (datos.clave <= 0);

        clear_input_buffer();

        do
        {
            printf("Nombre: ");
            fgets(datos.nombre, sizeof(datos.nombre), stdin);
            datos.nombre[strcspn(datos.nombre, "\n")] = '\0';
        }
        while (strlen(datos.nombre) == 0);

        do
        {
            printf("RFC: ");
            fgets(datos.RFC, sizeof(datos.RFC), stdin);
            datos.RFC[strcspn(datos.RFC, "\n")] = '\0';
        }
        while (strlen(datos.RFC) == 0);

        do
        {
            printf("Correo Electronico: ");
            fgets(datos.correo_electronico, sizeof(datos.correo_electronico), stdin);
            datos.correo_electronico[strcspn(datos.correo_electronico, "\n")] = '\0';
        }
        while (strlen(datos.correo_electronico) == 0);

        printf("Descuento: ");
        scanf("%f", &datos.descuento);
        clear_input_buffer();

        printf("Fecha (YYYY MM DD): ");
        scanf("%d %d %d", &datos.year, &datos.mes, &datos.dia);
        clear_input_buffer();

        do
        {
            printf("Calle: ");
            fgets(datos.calle, sizeof(datos.calle), stdin);
            datos.calle[strcspn(datos.calle, "\n")] = '\0';
        }
        while (strlen(datos.calle) == 0);

        printf("Numero: ");
        scanf("%d", &datos.numero);
        clear_input_buffer();

        do
        {
            printf("Colonia: ");
            fgets(datos.colonia, sizeof(datos.colonia), stdin);
            datos.colonia[strcspn(datos.colonia, "\n")] = '\0';
            cont1 = 0;
            for (i = 0; i < strlen(datos.colonia); i++)
            {
                if (!((datos.colonia[i] >= 'A' && datos.colonia[i] <= 'Z') ||
                      (datos.colonia[i] >= 'a' && datos.colonia[i] <= 'z') ||
                      datos.colonia[i] == ' '))
                {
                    printf("Hay datos invalidos\n");
                    cont1 = 1;
                    break;
                }
            }
        }
        while (cont1 == 1);

        do
        {
            printf("Municipio: ");
            fgets(datos.municipio, sizeof(datos.municipio), stdin);
            datos.municipio[strcspn(datos.municipio, "\n")] = '\0';
            cont1 = 0;
            for (i = 0; i < strlen(datos.municipio); i++)
            {
                if (!((datos.municipio[i] >= 'A' && datos.municipio[i] <= 'Z') ||
                      (datos.municipio[i] >= 'a' && datos.municipio[i] <= 'z') ||
                      datos.municipio[i] == ' '))
                {
                    printf("Hay datos invalidos\n");
                    cont1 = 1;
                    break;
                }
            }
        }
        while (cont1 == 1);

        do
        {
            printf("Estado: ");
            fgets(datos.estado, sizeof(datos.estado), stdin);
            datos.estado[strcspn(datos.estado, "\n")] = '\0';
            cont1 = 0;
            for (i = 0; i < strlen(datos.estado); i++)
            {
                if (!((datos.estado[i] >= 'A' && datos.estado[i] <= 'Z') ||
                      (datos.estado[i] >= 'a' && datos.estado[i] <= 'z') ||
                      datos.estado[i] == ' '))
                {
                    printf("Hay datos invalidos\n");
                    cont1 = 1;
                    break;
                }
            }
        } while (cont1 == 1);

        fseek(archivo,sizeof(struct Mercado)*(datos.clave-1),SEEK_SET);
        if (fwrite(&datos, sizeof(struct Mercado), 1, archivo) != 1)
        {
            printf("Error al escribir en el archivo\n");
        }

        do
        {
            printf("¿Hay más registros? S/N: ");
            clear_input_buffer();
            opcion = getchar();
            if (opcion == 'N' || opcion == 'n')
                registros = false;
            else if (opcion != 'N' && opcion != 'n' && opcion != 'S' && opcion != 's')
                printf("Opción invalida\n");
        }
        while (opcion != 'N' && opcion != 'n' && opcion != 'S' && opcion != 's');
    }

    fclose(archivo);
}

void inicializar_registros()
{
    char nombreArchivo[] = "mercado.dat";
    FILE* cfptr;
    struct Mercado mercadoInfo = {0};

    if (existeArchivo(cfptr, nombreArchivo) == 1)
    {
        if (crearArchivo(cfptr, nombreArchivo, &mercadoInfo, 100, sizeof(struct Mercado)) != 0)
        {
            printf("Error al crear el archivo\n");
            return;
        }
    }
}




