#include <stdio.h>
#include <stdbool.h>
#include "ventas.h"


bool validarExistencia(int ,int);

void menuVenta(){
    FILE *archivoPtr;
    struct Venta venta;
    //aqui iria la structu mercado
    archivoPtr=fopen("mercados.dat","rb");
    if (archivoPtr==NULL) {
        printf("No exisxte ningun mercado registrado");
    }else {
        printf("Control de Ventas");
        printf("Numero de Mercado: ");
        printf("Numero de Articulo: ");
        scanf("%d",venta.numeroMercado);
        //Ver que la clave exista en mercados
        fseek(archivoPtr,sizeof(struct Venta)*(venta.numeroMercado-1),SEEK_SET);
        //guardar en variable de mercado
        //ver si es 0, poner no existe, de lo contrario guardar
        printf("Ingrese la cantidad del Articulo");
    }

}
//modo 1 sera validar clave mercado, modo 2 sera validar el articulo y las existencias
bool validarExistencia(int clavef,int modo) {

}