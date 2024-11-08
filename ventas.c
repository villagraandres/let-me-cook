#include <stdio.h>
#include <stdbool.h>
#include "ventas.h"
#include "articulos.h"
#include "insumos.h"
#include <time.h>
#include "provedor.h"


void obtenerFecha(struct tm *fecha);
void menuVenta() {
    FILE *archivoMercados, *archivoArticulos, *archivoEmpleados,*archivoVentas;
    struct Venta ventas[100];
    struct Mercado datosMercado;
    int numVentas = 0;
    float precioTotal = 0,precioArt;
    char respuesta;
    struct tm fecha;
    obtenerFecha(&fecha);

    archivoVentas=fopen("ventas.txt","a");
    if(archivoVentas==NULL) {
        archivoVentas=fopen("ventas.txt","w");
    }

    archivoMercados = fopen("mercado.dat", "rb+"); // Corrected file name
    if (archivoMercados == NULL) {
        printf("No existe ningun mercado registrado\n");
        return;
    }




    archivoArticulos = fopen("articulos.dat", "rb+");
    if (archivoArticulos == NULL) {
        printf("No existe ningún artículo registrado\n");
        fclose(archivoMercados);
        return;
    }


    archivoEmpleados = fopen("empleados.dat", "rb+");
    if (archivoEmpleados == NULL) {
        printf("No hay ningún empleado registrado\n");
        fclose(archivoMercados);
        fclose(archivoArticulos);
        return;
    }


    printf("\nControl de Ventas\n");
    printArchivoMercados(archivoMercados);
    do {
        printf("Número de Mercado: ");
        do {
            scanf("%d", &ventas[numVentas].numeroMercado);
        } while (!validarExistencia(ventas[numVentas].numeroMercado, 1, archivoMercados, archivoArticulos));

        printArchivoArticulos(archivoArticulos);
        printf("\nNúmero de Artículo: ");
        do {

            scanf("%d", &ventas[numVentas].numeroArticulo);
        } while (!validarExistencia(ventas[numVentas].numeroArticulo, 2, archivoMercados, archivoArticulos));

        printf("\nIngrese la cantidad del Artículo: ");
        do {
            scanf("%d", &ventas[numVentas].cantidad);
        } while (!validarCantidad(ventas[numVentas].numeroArticulo, ventas[numVentas].cantidad, archivoArticulos));

        printf("¿Desea agregar otro artículo? (S/N): ");
        scanf(" %c", &respuesta);

        numVentas++;
    } while (respuesta == 'S' || respuesta == 's');

    printArchivoEmpleados(archivoEmpleados);
    do {
        printf("Ingresa el número de empleado: ");
        scanf("%d", &ventas[0].empleado);
    } while (!validarEmpleado(archivoEmpleados, ventas[0].empleado));

    for (int i = 0; i < numVentas; i++) {
        fseek(archivoMercados,sizeof(struct Mercado)*(ventas[i].numeroMercado-1),SEEK_SET);
        fread(&datosMercado,sizeof(struct Mercado),1,archivoMercados);
        precioArt=( obtenerPrecioArticulo(ventas[i].numeroArticulo, archivoArticulos) * ventas[i].cantidad)*datosMercado.descuento;
        precioTotal +=precioArt;
        fprintf(archivoVentas,"%d %d %f %d %d %d %d\n",ventas[i].numeroArticulo,ventas[i].cantidad,precioArt,ventas[i].empleado,fecha.tm_mday, fecha.tm_mon + 1, fecha.tm_year + 1900);
    }

    printf("El precio total de la venta es: %.2f\n", precioTotal);


    printf("¿Requiere factura? (S/N): ");
    scanf(" %c", &respuesta);
    if (respuesta == 'S' || respuesta == 's') {
        generarFactura(ventas, numVentas, precioTotal, ventas[0].empleado);
    }

    fclose(archivoArticulos);
    fclose(archivoMercados);
    fclose(archivoEmpleados);
}

bool validarEmpleado(FILE *archivoEmpleado, int empleadoId) {
    struct Empleado empleadoInfo;
    fseek(archivoEmpleado, sizeof(struct Empleado) * (empleadoId - 1), SEEK_SET);
    fread(&empleadoInfo, sizeof(struct Empleado), 1, archivoEmpleado);

    if (empleadoInfo.numero_empleado == 0) {
        printf("El empleado no existe\n");
        return false;
    }
    return true;
}

bool validarCantidad(int claveArticulo, int cantidad, FILE *archivo) {
    struct Articulo articulo;
    int opcion;

    fseek(archivo, sizeof(struct Articulo) * (claveArticulo - 1), SEEK_SET);
    fread(&articulo, sizeof(struct Articulo), 1, archivo);

    if (cantidad <= 0) {
        printf("Debes ingresar una cantidad mayor a 0\n");
        return false;
    }

    if (articulo.inventario < cantidad) {
        printf("No hay suficientes unidades para el producto que quieres\n");
        printf("Cantidad actual: %d\n", articulo.inventario);
        printf("1) Elegir otro producto \n2) Actualizar cantidad del producto actual\n");
        scanf("%d", &opcion);

        if (opcion == 1) {
            return false;
        } else if (opcion == 2) {
            do {
                printf("Ingresa la nueva cantidad: ");
                scanf("%d", &cantidad);
            } while (cantidad <= 0 || cantidad > articulo.inventario);
        }
    }

    articulo.inventario -= cantidad;
    fseek(archivo, sizeof(struct Articulo) * (claveArticulo - 1), SEEK_SET);
    fwrite(&articulo, sizeof(struct Articulo), 1, archivo);
    fflush(archivo); // Ensure data is written to the file

    return true;
}

bool validarExistencia(int clave, int modo, FILE *archivoMercados, FILE *archivoArticulos) {
    if (clave <= 0) {
        printf("Clave inválida\n");
        return false;
    }

    if (modo == 1) {
        struct Mercado mercado;
        fseek(archivoMercados, sizeof(struct Mercado) * (clave-1), SEEK_SET);
        fread(&mercado, sizeof(struct Mercado), 1, archivoMercados);
        
        // Debugging print statement
        printf("Debug: Leyendo mercado con clave %d, encontrado clave %d\n", clave, mercado.clave);

        if (mercado.clave == 0) {
            printf("El mercado no existe\n");
            return false;
        }
        return true;
    } else {
        struct Articulo articulo;
        fseek(archivoArticulos, sizeof(struct Articulo) * (clave - 1), SEEK_SET);
        fread(&articulo, sizeof(struct Articulo), 1, archivoArticulos);
        
        // Debugging print statement
        printf("Debug: Leyendo articulo con clave %d, encontrado clave %d\n", clave, articulo.claveArticulo);

        if (articulo.claveArticulo == 0) {
            printf("La clave del producto no existe\n");
            return false;
        }
        return true;
    }
}

float obtenerPrecioArticulo(int claveArticulo, FILE *archivo) {
    struct Articulo articulo;

    fseek(archivo, sizeof(struct Articulo) * (claveArticulo - 1), SEEK_SET);
    fread(&articulo, sizeof(struct Articulo), 1, archivo);

    return articulo.precio;
}

void generarFactura(struct Venta ventas[], int numVentas, float total, int empleadoId) {
    printf("\nFactura:\n");
    printf("Empleado ID: %d\n", empleadoId);
    for (int i = 0; i < numVentas; i++) {
        printf("Artículo %d: %d unidades\n", ventas[i].numeroArticulo, ventas[i].cantidad);
    }
    printf("Total: %.2f\n", total);
}

// Function to print the contents of archivoMercados
void printArchivoMercados(FILE *archivoMercados) {
    struct Mercado mercadoInfo;
    rewind(archivoMercados);
    printf("\nContenido de archivoMercados:\n");
    while (fread(&mercadoInfo, sizeof(struct Mercado), 1, archivoMercados)) {

        printf("Clave: %d\n", mercadoInfo.clave);
    }
    rewind(archivoMercados);
}

// Function to print the contents of archivoArticulos
void printArchivoArticulos(FILE *archivoArticulos) {
    struct Articulo articuloInfo;
    rewind(archivoArticulos);
    printf("\nContenido de archivoArticulos:\n");
    while (fread(&articuloInfo, sizeof(struct Articulo), 1, archivoArticulos)) {
        if(articuloInfo.claveArticulo!=0)
            printf("Clave: %d, Inventario: %d, Precio: %f\n", articuloInfo.claveArticulo, articuloInfo.inventario, articuloInfo.precio);


    }
    rewind(archivoArticulos);
}

// Function to print the contents of archivoEmpleados
void printArchivoEmpleados(FILE *archivoEmpleados) {
    struct Empleado empleadoInfo;
    rewind(archivoEmpleados);
    printf("\nContenido de archivoEmpleados:\n");
    while (fread(&empleadoInfo, sizeof(struct Empleado), 1, archivoEmpleados)) {
        if(empleadoInfo.numero_empleado!=0) {
            printf("Número de Empleado: %d\n", empleadoInfo.numero_empleado);
        }

    }
    rewind(archivoEmpleados);
}


void obtenerFecha(struct tm *fecha) {
    time_t t = time(NULL);
    *fecha = *localtime(&t);

    mktime(fecha);
}



//COMPRASSSS





void menuCompra() {
    FILE *archivoProv, *archivoIns,*archivoCompras;
    int numeroProvedor, numeroInsumo, cantidad, comprasCont = 0;
    char respuesta;
    float precioTotal = 0;
    struct Insumo insumoInfo;
    int idCompra;

    archivoCompras=fopen("compras.txt","a");
    if(archivoCompras==NULL) {
        printf("Error al abrir el archivo de compras");
        return;
    }
    idCompra = obtenerUltimoID(archivoCompras)+1;

    archivoProv = fopen("provedor.dat", "rb+");
    if (archivoProv == NULL) {
        printf("No existe ningun provedor registrado\n");
        return;
    }

    archivoIns = fopen("insumos.dat", "rb+");
    if (archivoIns == NULL) {
        printf("No existe ningun insumo registrado\n");
        return;
    }

    do {
        printf("Ingrese el numero del provedor: ");
        scanf("%d", &numeroProvedor);
    } while (!validarExistenciaPI(archivoProv, 1, numeroProvedor, -1));

    do {
        do {
            printf("Ingrese el numero del insumo: ");
            scanf("%d", &numeroInsumo);
        } while (!validarExistenciaPI(archivoIns, 2, numeroInsumo, -1) ||
                 !validarExistenciaPI(archivoIns, 3, numeroInsumo, numeroProvedor));

        do {
            printf("Ingrese la cantidad deseada: ");
            scanf("%d", &cantidad);
        } while (cantidad < 0);

        precioTotal += obtenerPrecio(numeroInsumo, numeroProvedor, archivoIns) * cantidad;

        printf("\nDesea agregar otro insumo? (S/N): ");
        scanf(" %c", &respuesta);
        idCompra++;

        fseek(archivoIns,sizeof(struct Insumo)*(numeroInsumo-1),SEEK_SET);
        fread(&insumoInfo,sizeof(struct Insumo),1,archivoIns);
        fprintf(archivoCompras, "%d %d %s %d\n", idCompra, numeroInsumo, insumoInfo.descripcion,cantidad);

    } while (respuesta == 'S' || respuesta == 's');

    printf("El precio total es: %.2f\n", precioTotal);
    fclose(archivoCompras);
    fclose(archivoIns);
}

float obtenerPrecio(int idInsumo, int idProvedor, FILE *insumoArch) {
    struct Insumo insumoInfo;
    fseek(insumoArch, sizeof(struct Insumo) * (idInsumo - 1), SEEK_SET);
    fread(&insumoInfo, sizeof(struct Insumo), 1, insumoArch);

    for (int i = 0; i < 10; i++) {
        if (insumoInfo.provedores[i] == idProvedor) {
            return insumoInfo.precios[i];
        }
    }

    printf("El insumo %d no tiene un precio asociado para el proveedor %d\n", idInsumo, idProvedor);
    return 0.0;
}

bool validarExistenciaPI(FILE *archivoPtr, int modo, int id, int idProvedor) {
    if (modo == 1) {
        struct Provedor provInfo;
        fseek(archivoPtr, sizeof(struct Provedor) * (id - 1), SEEK_SET);
        fread(&provInfo, sizeof(struct Provedor), 1, archivoPtr);
        if (provInfo.claveProvedor == 0) {
            printf("El provedor seleccionado no existe\n");
            return false;
        }
    } else if (modo == 2) {
        struct Insumo insumoInfo;
        fseek(archivoPtr, sizeof(struct Insumo) * (id - 1), SEEK_SET);
        fread(&insumoInfo, sizeof(struct Insumo), 1, archivoPtr);
        if (insumoInfo.claveInsumo == 0) {
            printf("El insumo seleccionado no existe\n");
            return false;
        }
    } else if (modo == 3) {
        struct Insumo insumoInfo;
        fseek(archivoPtr, sizeof(struct Insumo) * (id - 1), SEEK_SET);
        fread(&insumoInfo, sizeof(struct Insumo), 1, archivoPtr);

        for (int i = 0; i < 10; i++) {
            if (insumoInfo.provedores[i] == idProvedor) {
                return true;
            }
        }
        printf("El proveedor %d no ofrece el insumo %d\n", idProvedor, id);
        return false;
    }
    return true;
}


int obtenerUltimoID(FILE *archivoCompras) {
    int ultimoID = 0, tempID;
    rewind(archivoCompras); // Volver al inicio del archivo
    while (fscanf(archivoCompras, "%d", &tempID) == 1) {
        ultimoID = tempID;
        // Leer el resto de la línea para avanzar en el archivo
        fscanf(archivoCompras, "%*[^\n]\n");
    }
    return ultimoID;
}

//REPORTES



void menuReporte() {
    char opcion;

    do
    {
        do {
            printf("Reportes\n");
            printf("a) Listado de artículos\n");
            printf("b) Total de venta por fecha\n");
            printf("c) Total de venta por artículo\n");
            printf("d) Listado de artículos a solicitar\n");
            printf("e) Saldos por pagar\n");
            printf("f) Cálculo de comisiones\n");
            printf("g) Compras pendientes de recepción\n");
            printf("h) Salir\n\n");
            scanf("%c",&opcion);

        }while (opcion<'a' || opcion>'h');

        switch (opcion) {
            case 'a':
                listadoArticulos();
                break;
            case 'f':
                listadoEmpleadosComision();
                break;

        }

    }while(opcion != 'h' && opcion != 'H');
}


void listadoArticulos() {
    FILE *archivoArt=fopen("articulos.dat","rb");
    if(archivoArt==NULL) {
        printf("No existe ningun articulo registrado");
    }else {
        struct Articulo articuloInfo;
        rewind(archivoArt);
        printf("\nContenido de archivoArticulos:\n");
        while (fread(&articuloInfo, sizeof(struct Articulo), 1, archivoArt)) {
            if(articuloInfo.claveArticulo!=0)
                printf("Clave: %d, Inventario: %d, Precio: %f\n", articuloInfo.claveArticulo, articuloInfo.inventario, articuloInfo.precio);
        }
        rewind(archivoArt);
    }
};


void listadoEmpleadosComision()
{
    FILE *ptrVentas=fopen("ventas.txt","r");
    FILE *ptrEmpleados=fopen("empleados.dat","rb");
    struct Empleado empleado = {};
    struct Venta venta = {};

    int i,dia,mes,año,ocurrencias;

    if(ptrVentas==NULL)
        printf("No se pudo abrir el archivo ventas.txt\n");

    else if (ptrEmpleados == NULL)
        printf("No se pudo abrir el archivo empleados.dat\n");
    else
    {

        for (i = 0; i < 10; i++)
        {
            rewind(ptrVentas);
            fread(&empleado,sizeof(struct Empleado),1,ptrEmpleados);


            if (empleado.numero_empleado > 0)
            {
                //printf("%s%d\n",empleado.nombre,empleado.numero_empleado);
                ocurrencias = 0;
                while(fscanf(ptrVentas,"%d %d %f %d %d %d %d",&venta.numeroArticulo,&venta.cantidad,&venta.precio,&venta.empleado,&dia,&mes,&año) != EOF)
                {
                    //printf("pepe\n");
                    if (venta.empleado == empleado.numero_empleado)
                        ocurrencias++;
                }

                if (ocurrencias>0)
                    printf("El número de ventas del empeado %d fueron de %d\n",empleado.numero_empleado,ocurrencias);

            }

        }

    fclose(ptrEmpleados);
    fclose(ptrVentas);
    }


}

//MANEJO DE ARCHIVOS


// Verifica si el archivo existe
int existeArchivo(FILE* fptr, char* fArchivo) {
    fptr = fopen(fArchivo, "rb");

    if (fptr == NULL) {
        return 1;  // El archivo no existe
    } else {
        fclose(fptr);
        return 0;  // El archivo existe
    }
}

// Crea el archivo con estructuras iniciales
int crearArchivo(FILE* fptr, char* fArchivo, void* estructura, int cantidadEstructuras, int tamanoEstructura) {
    fptr = fopen(fArchivo, "wb");

    if (fptr == NULL) {
        return 1;  // Error al abrir el archivo para escritura
    }

    for (int i = 0; i < cantidadEstructuras; ++i) {
        fwrite(estructura, tamanoEstructura, 1, fptr);
    }

    fclose(fptr);

    return 0;
}


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





