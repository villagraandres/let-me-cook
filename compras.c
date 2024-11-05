#include <stdio.h>
#include <stdbool.h>
#include "compras.h"
#include "provedor.h"
#include "insumos.h"
bool validarExistenciaPI(FILE *, int, int);
float obtenerPrecio(int, FILE *);
void menuCompra() {
    FILE *archivoProv, *archivoIns;
    struct Compra comprasArr[100];
    int comprasCont=0,respuesta,i;
    float precioTotal=0;
    archivoProv=fopen("provedores.dat","rb+");
    if(archivoProv==NULL) {
        printf("No existe ningun provedor registrado");
        return;
    }
    archivoIns=fopen("insumos.dat","rb+");
    if(archivoIns==NULL) {
        printf("No existe ningun insumo registrado");
        return;
    }

    do {
        printf("Ingrese el numero del provedor");
        scanf("%d",comprasArr[comprasCont].numeroProvedor);
    }while(!validarExistenciaPI(archivoProv,1,comprasArr[comprasCont].numeroProvedor));
    do {

        do {
            printf("Ingrese el numero del insumo");
            scanf("%d",comprasArr[comprasCont].numeroInsumo);
        }while(!validarExistenciaPI(archivoProv,1,comprasArr[comprasCont].numeroInsumo));


        do {
            printf("Ingrese la cantidad deseada");
            scanf("%d",comprasArr[comprasCont].cantidad);
        }while (comprasArr[comprasCont].cantidad<0);


        printf("\nDesea agregar otro insumo?");
        scanf("%d",&respuesta);
        comprasCont++;

    }while(respuesta=='S' || respuesta=='s');

    for(i=0;i<comprasCont;i++) {
        precioTotal+=obtenerPrecio(comprasArr[i].numeroInsumo,archivoIns);
    }




}
float obtenerPrecio(int id, FILE *insumoArch) {
    struct Insumo insumoInfo;
    fseek(insumoArch,sizeof(struct Insumo)*(id-1),SEEK_SET);
    fread(&insumoInfo,sizeof(struct Insumo),1,insumoArch);
    return ;
}
bool validarExistenciaPI(FILE *archivoPtr,int modo,int id) {
    if(modo==1) {
        struct Provedor provInfo;
        fseek(archivoPtr,sizeof(struct Provedor)*(id-1),SEEK_SET);
        fread(&provInfo,sizeof(struct Provedor),1,archivoPtr);
        if(provInfo.claveProvedor==0) {
            printf("El provedor seleccionado no existe");
            return false;
        }

    }else {
        //remplazar despues por insumos
        struct Insumo insumoInfo;
        fseek(archivoPtr,sizeof(struct Insumo)*(id-1),SEEK_SET);
        fread(&insumoInfo,sizeof(struct Insumo),1,archivoPtr);
        if(insumoInfo.claveInsumo==0) {
            printf("El insumo seleccionado no existe");
            return false;
        }


    }
    return true;

}