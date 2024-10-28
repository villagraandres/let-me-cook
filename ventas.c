#include <stdio.h>
#include "ventas.h"



void menuVenta(){
    FILE *archivoPtr;
    struct Venta venta;
    archivoPtr=fopen("mercados.dat","rb");
    if (archivoPtr==NULL) {
        printf("No exisxte ningun mercado registrado");
    }else {
        printf("Control de Ventas");
        printf("Numero de Articulo: ");
        scanf("%d",venta.numeroMercado);
        //Ver que la clave exista en mercados
    }





}