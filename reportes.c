#include <stdio.h>
#include "reportes.h"
#include "articulos.h"
#include "empleados.h"
#include "ventas.h"

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
    FILE *ptrEmpleados=fopen("empleados.txt","r");
    struct Empleado empleado = {};
    struct Venta venta = {};

    int i,dia,mes,año,ocurrencias;    

    if(ptrVentas==NULL)
        printf("No se pudo abrir el archivo ventas.txt\n");

    else if (ptrEmpleados == NULL)
        printf("No se pudo abrir el archivo empleados.txt\n");
    else
    {

        for (i = 0; i < 1000; i++)
        {
            fread(&empleado,sizeof(struct Empleado),1,ptrEmpleados);

            if (empleado.numero_empleado > 0)
            {   
                ocurrencias = 0;
                while(fscanf(ptrVentas,"%d %d %f %d %d %d %d",&venta.numeroArticulo,&venta.cantidad,&venta.precio,&venta.empleado,&dia,&mes,&año) != EOF)
                {

                    if (venta.empleado == empleado.numero_empleado)
                        ocurrencias++;
                }
                
                if (ocurrencias>0)
                    printf("El número de ventas del empeado %d fueron de %d\n",empleado.numero_empleado,ocurrencias);

            }

        }
        

    }


}