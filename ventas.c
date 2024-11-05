#include <stdio.h>
#include <stdbool.h>
#include "ventas.h"
#include "articulos.h"
#include "mercados.h"
#include "empleados.h"
#include "manejoArchivos.h"

// Function to print the contents of archivoMercados
void printArchivoMercados(FILE *archivoMercados) {
    struct mercado mercadoInfo;
    rewind(archivoMercados);
    printf("\nContenido de archivoMercados:\n");
    while (fread(&mercadoInfo, sizeof(struct mercado), 1, archivoMercados)) {
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
        if(articuloInfo.claveArticulo!=0) {
            printf("Clave: %d, Inventario: %d, Precio: %d\n", articuloInfo.claveArticulo, articuloInfo.inventario, articuloInfo.precio);
        }

    }
    rewind(archivoArticulos);
}

bool validarExistencia(int clave, int modo, FILE *archivoMercados, FILE *archivoArticulos);
bool validarCantidad(int numeroArticulo, int cantidad, FILE *archivo);
float obtenerPrecioArticulo(int claveArticulo, FILE *archivo);
bool validarEmpleado(FILE *archivoEmpleado, int empleadoId);
void generarFactura(struct Venta ventas[], int numVentas, float total, int empleadoId);

void menuVenta() {
    FILE *archivoMercados, *archivoArticulos, *archivoEmpleados;
    struct Venta ventas[100]; 
    int numVentas = 0;
    float precioTotal = 0;
    char respuesta;

    archivoMercados = fopen("mercado.dat", "rb+"); // Corrected file name
    if (archivoMercados == NULL) {
        printf("No existe ningun mercado registrado\n");
        return;
    }

    // Print the contents of archivoMercados
    printArchivoMercados(archivoMercados);

    archivoArticulos = fopen("articulos.dat", "rb+");
    if (archivoArticulos == NULL) {
        printf("No existe ningún artículo registrado\n");
        fclose(archivoMercados);
        return;
    }
    printArchivoArticulos(archivoArticulos);

    archivoEmpleados = fopen("empleados.dat", "rb+");
    if (archivoEmpleados == NULL) {
        printf("No hay ningún empleado registrado\n");
        fclose(archivoMercados);
        fclose(archivoArticulos);
        return;
    }

    printf("\nControl de Ventas\n");

    do {
        printf("Número de Mercado: ");
        do {
            scanf("%d", &ventas[numVentas].numeroMercado);
        } while (!validarExistencia(ventas[numVentas].numeroMercado, 1, archivoMercados, archivoArticulos));

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

    do {
        printf("Ingresa el número de empleado: ");
        scanf("%d", &ventas[0].empleado);
    } while (!validarEmpleado(archivoEmpleados, ventas[0].empleado));

    for (int i = 0; i < numVentas; i++) {
        precioTotal += obtenerPrecioArticulo(ventas[i].numeroArticulo, archivoArticulos) * ventas[i].cantidad;
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
    struct empleado empleadoInfo;
    fseek(archivoEmpleado, sizeof(struct empleado) * (empleadoId - 1), SEEK_SET);
    fread(&empleadoInfo, sizeof(struct empleado), 1, archivoEmpleado);

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
        struct mercado mercado;
        fseek(archivoMercados, sizeof(struct mercado) * (clave - 1), SEEK_SET);
        fread(&mercado, sizeof(struct mercado), 1, archivoMercados);

        if (mercado.clave == 0) {
            printf("El mercado no existe\n");
            return false;
        }
        return true;
    } else {
        struct Articulo articulo;
        fseek(archivoArticulos, sizeof(struct Articulo) * (clave - 1), SEEK_SET);
        fread(&articulo, sizeof(struct Articulo), 1, archivoArticulos);

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