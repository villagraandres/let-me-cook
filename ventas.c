#include <stdio.h>
#include <stdbool.h>
#include "ventas.h"

#include "articulos.h"


bool validarExistencia(int ,int, FILE *);

void menuVenta(){
    FILE *archivoPtr;
    struct Venta venta;
    //aqui iria la structu mercado
    archivoPtr=fopen("mercados.dat","rb");
    if (archivoPtr==NULL) {
        printf("No exisxte ningun mercado registrado");
    }else {
        printf("\nControl de Ventas");
        printf("Numero de Mercado: ");
        do {
            scanf("%d",&venta.numeroMercado);
        }while (!validarExistencia(venta.numeroMercado,1,archivoPtr));
        printf("\nNumero de Articulo: ");
        do {
            scanf("%d",&venta.numeroArticulo);
        }while (!validarExistencia(venta.numeroArticulo,2,archivoPtr));

        printf("\nCantidad:");
        scanf("%d",&venta.cantidad);




        printf("\nIngrese la cantidad del Articulo");
    }

}
//modo 1 sera validar clave mercado, modo 2 sera validar el articulo y las existencias
bool validarExistencia(int clavef,int modo, FILE *archivof) {
    if(clavef<0) {
        return false;
    }
    if(modo==1) {
        fseek(archivof,sizeof(struct Venta)*(clavef-1),SEEK_SET);
        //Ver que la clave exista en mercados

        //guardar en variable de mercado
        //ver si es 0, poner no existe, de lo contrario guardar

    }else {
        struct Articulo articulo;
        fseek(archivof,sizeof(struct Articulo)*(clavef-1),SEEK_SET);
        fread(&articulo,sizeof(struct Articulo),1,archivof);

        if(articulo.claveArticulo==0) {
            printf("La clave del producto no existe");
            return false;
        }

        if(articulo.claveArticulo!=0) {
            if(articulo)
        }

    }
}