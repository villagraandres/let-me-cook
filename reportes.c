#include <stdio.h>
#include "reportes.h"
#include "articulos.h"
void menuReporte() {
    char opcion;
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
    }
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
                printf("Clave: %d, Inventario: %d, Precio: %d\n", articuloInfo.claveArticulo, articuloInfo.inventario, articuloInfo.precio);


        }
        rewind(archivoArt);
    }
}