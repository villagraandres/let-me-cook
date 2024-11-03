#include <stdio.h>
#include <stdbool.h>
#include "ventas.h"
#include "articulos.h"
#include "mercados.h"
#include "manejoArchivos.h"

bool validarExistencia(int clave, int modo, FILE *archivoMercados, FILE *archivoArticulos);
bool validarCantidad(int numeroArticulo, int cantidad, FILE *archivo);

void menuVenta() {
    FILE *archivoMercados, *archivoArticulos;
    struct Venta venta;

    archivoMercados = fopen("mercados.dat", "rb+");
    if (archivoMercados == NULL) {
        printf("No existe ningún mercado registrado\n");
    } else {
        archivoArticulos = fopen("articulos.dat", "rb+");
        if (archivoArticulos == NULL) {
            printf("No existe ningún artículo registrado\n");
        } else {
            printf("\nControl de Ventas\n");

            printf("Número de Mercado: ");
            do {
                scanf("%d", &venta.numeroMercado);
            } while (!validarExistencia(venta.numeroMercado, 1, archivoMercados, archivoArticulos));

            printf("\nNúmero de Artículo: ");
            do {
                do {
                    scanf("%d", &venta.numeroArticulo);
                } while (!validarExistencia(venta.numeroArticulo, 2, archivoMercados, archivoArticulos));

                printf("\nIngrese la cantidad del Artículo: ");
                scanf("%d", &venta.cantidad);
            } while (!validarCantidad(venta.numeroArticulo, venta.cantidad, archivoArticulos));

            printf("")
        }

        fclose(archivoArticulos);
    }

    fclose(archivoMercados);
}

bool validarCantidad(int claveArticulo, int cantidad, FILE *archivo) {
    struct Articulo articulo;
    int opcion;

    fseek(archivo, sizeof(struct Articulo) * (claveArticulo - 1), SEEK_SET);
    fread(&articulo, sizeof(struct Articulo), 1, archivo);

    if (cantidad < 0) {
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
            } while (cantidad < 0 || cantidad > articulo.inventario);
        }
    }

    articulo.inventario -= cantidad;
    fseek(archivo, sizeof(struct Articulo) * (claveArticulo - 1), SEEK_SET);
    fwrite(&articulo, sizeof(struct Articulo), 1, archivo);

    return true;
}

bool validarExistencia(int clave, int modo, FILE *archivoMercados, FILE *archivoArticulos) {
    if (clave < 0) {
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
