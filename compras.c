#include <stdio.h>
#include <stdbool.h>
#include "compras.h"
#include "provedor.h"
#include "insumos.h"

bool validarExistenciaPI(FILE *, int, int, int);
float obtenerPrecio(int, int, FILE *);
void menuCompra() {
    FILE *archivoProv, *archivoIns;
    int numeroProvedor, numeroInsumo, cantidad, comprasCont = 0;
    char respuesta;
    float precioTotal = 0;

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

    } while (respuesta == 'S' || respuesta == 's');

    printf("El precio total es: %.2f\n", precioTotal);
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
