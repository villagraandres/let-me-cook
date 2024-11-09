#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include  "ventas.h"
#include "articulos.h"



void menuArticulos(){

	bool continuar;
	char c;
	struct Articulo articulo = {};

	//Comprobar que los archivos correspondientes existan
	inicializarRegistrosArticulos();
    writeOutput5();

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
	if (!claveExiste(fArticulo->claveArticulo,cfptr,"articulos.dat"))
		actualizarDatos = true;
	else
		actualizarDatos = false;
	
	if(actualizarDatos == true)
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
		//Leer a lo más 10 claves y checar si existen en el archivo de claves de mercado*/
		
        cfptr = fopen("mercado.dat","rb");
		if (cfptr == NULL)
            printf("Error al abrir archivo mercado.dat\n");
        
        else
        {
            i = 0;
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

                        // Si está vacio no hay nada que actualizar
                        if (mercado.clave == 0)
                            printf("Ingresa una clave registrada\n");
                        else{
                            fArticulo->claveMercados[i] = clave;
                            i++;
                            printf("Clave %d registrada con éxito\n",mercado.clave);
                        }
                        
                    }
                } while (clave <= 0);

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

        
		// Clave de los insumos
        cfptr = fopen("insumos.dat","rb");
		if (cfptr == NULL)
			printf("Error al abrir archivo insumos.dat\n");
        else
        {
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
                } while (clave <= 0);


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
                    

            } while (i<10 && continuar);

            printf("[DEBUG MESSAGE] - El articulo tiene un costo de producción de %.2f pesos\n",fArticulo->costo);
            fclose(cfptr);

        }



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
		return 2;

	else{

		// Buscar clave
		fseek(fptr,sizeof(struct Articulo) * clave ,SEEK_SET);		
		fread(&articulo,sizeof(struct Articulo),1,fptr);

		printf("%d",articulo.claveArticulo);

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

        datos.comision /= 100;

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

void  mercados_main()
{
    inicializar_registros();
    struct Mercado datos = {};
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
            printf("\nClave: ");
            scanf("%d", &datos.clave);
            if (datos.clave <= 0)
                printf("Clave invalida\n");
        }
        while (datos.clave <= 0);

        clear_input_buffer();

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

		} while (datos.descuento < 0 || datos.descuento > 100);
		
		datos.descuento /= 100; 
        
        clear_input_buffer();

        printf("Fecha (YYYY MM DD): ");
        scanf("%d %d %d", &datos.year, &datos.mes, &datos.dia);
        clear_input_buffer();


		validarDireccion(datos.calle,datos.numero,datos.colonia,datos.municipio,datos.estado);


        fseek(archivo,sizeof(struct Mercado)*(datos.clave-1),SEEK_SET);
        if (fwrite(&datos, sizeof(struct Mercado), 1, archivo) != 1)
        {
            printf("Error al escribir en el archivo\n");
        }

        do
        {
            printf("¿Hay más registros? S/N: ");
            
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

void inicializar_registros()
{
    char nombreArchivo[] = "mercado.dat";
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




void writeOutput5()
{
	FILE* fptr = fopen("mercado.dat","rb");
	if (fptr == NULL) {
		printf("[ERROR] - No se pudo abrir el archivo mercado.dat\n");
		return;
	}

	FILE *archivo = fopen("Logs/Mercado", "w");
	if (archivo == NULL) {
		printf("[ERROR] - No se pudo abrir el archivo Logs/Insumo\n");
		fclose(fptr);
		return;
	}

	struct Mercado mercado= {};

	//printf("%-10s %-20s\n","Clave","Nombre");

	while (fread(&mercado, sizeof(struct Insumo), 1, fptr) == 1)
	{
		if (mercado.clave != 0)
		{
			fprintf(archivo,"%d_%s\n",mercado.clave,mercado.nombre);
			
		}
	}

	fclose(fptr);
	fclose(archivo);
}


// Insumos

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
	writeOutput2();


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
	bool continuar;
	int i,clave;
	float precio;
	char c;

	// Funciona solo para pasarlo a claveExiste y guardar la info en el
	struct Insumo insumo;
	struct Provedor provedor = {};

	// Clave del insumo
	do
	{
		printf("Clave del insumo:\n");
		scanf("%d",&fInsumo->claveInsumo);

		if (fInsumo->claveInsumo < 1 || fInsumo->claveInsumo > 100)
			printf("Ingresa un número entre 1 y 100\n");
	}while(fInsumo->claveInsumo < 1 || fInsumo->claveInsumo > 100);

	if (claveInsumoExiste(fInsumo->claveInsumo,cfptr,"insumos.dat"))
		actualizarDatos = true;
	else
		actualizarDatos = false;
	

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
		i = 0;

		// Comprobar que se pueda abrir archivo para leer
		cfptr = fopen("provedor.dat","rb");
		if (cfptr == NULL)
		{
			printf("[ERROR] - No se pudo leer el archivo provedor.dat\n");
		}
		
		else
		{
			printf("[DEBUG MESSAGE ]- File provedor.dat open from insumos.c\n");
			do
			{	
				// Checar que exista la clave
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

						// Preguntar precio
						do
						{
							printf("Ingresa el precio del provedor\n");
							scanf("%f",&precio);

							if (precio<=0)
								printf("Ingresa un valor mayor que 0\n");

						} while (precio <= 0);

						*(fInsumo->precios+i) = precio;
						i++;

					}
						
					// Preguntar si desean continuar
					do{
						printf("Desea agregar otro provedor al insumo? S/N)");
						scanf(" %c",&c);

						if (c=='S' || c=='s')
								continuar = true;
						else if(c=='N' || c == 'n')
								continuar = false;
						else
							printf("Ingrese una opción válida");

					}while(c!='S' && c!= 's' && c!= 'N' && c!= 'n');

				} while (clave < 1 || clave > 100);
			

			} while (i<10 && continuar);


			fclose(cfptr);
		}

		// Escribir estructura en el archivo	
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
		fseek(fptr,sizeof(struct Insumo) * (clave - 1) ,SEEK_SET);		
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


void writeOutput2()
{
	FILE* fptr = fopen("insumos.dat","rb");
	if (fptr == NULL) {
		printf("[ERROR] - No se pudo abrir el archivo insumos.dat\n");
		return;
	}

	FILE *archivo = fopen("Logs/Insumo", "w");
	if (archivo == NULL) {
		printf("[ERROR] - No se pudo abrir el archivo Logs/Insumo\n");
		fclose(fptr);
		return;
	}

	struct Insumo insumo= {};

	//printf("%-10s %-20s\n","Clave","Nombre");

	while (fread(&insumo, sizeof(struct Insumo), 1, fptr) == 1)
	{
		if (insumo.claveInsumo != 0)
		{
			fprintf(archivo,"%d_%s\n",insumo.claveInsumo,insumo.descripcion);
			
			for ( int i = 0; i < 10; i++)
			{
				fprintf(archivo,"%d::%.2f\n",insumo.provedores[i],insumo.precios[i]);
			}
		}
	}

	fclose(fptr);
	fclose(archivo);
}


// Provedor



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

		validarRFC(fProvedor->rfc);

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


void validarDireccion(char* calle,char* numero, char* colonia,char* municipio, char* estado)
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
		};

		// Checar que no sea una cadena Vacia
		if (strlen(calle) == nEspacios)
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

	// Colonia
	do
	{	valido = true;
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
		};

		// Checar que no sea una cadena Vacia
		if (strlen(colonia) == nEspacios)
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
		};

		// Checar que no sea una cadena Vacia
		if (strlen(municipio) == nEspacios)
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
		};

		// Checar que no sea una cadena Vacia
		if (strlen(estado) == nEspacios)
		{
			printf("Nombre de estado inválida\n");
			valido = false;
		}

		
	}
	while (!valido);


}

/*void validarDireccion(struct Provedor* fProvedor)
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
*/


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
			fprintf(archivo,"%d %s %s\n",provedor.claveProvedor,provedor.nombre,provedor.rfc);
		}
			
		
	}

	fclose(fptr);
	fclose(archivo);


};


void validarRFC(char* rfc)
{
	bool valido;
	int i;

	printf("[DEBUG MESSAGE] - Se la estamos metiendo a Andres disculpe las molestias\n");

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

/*void validarRFC(struct Provedor* fProvedor)
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

*/