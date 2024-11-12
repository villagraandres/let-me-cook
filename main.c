#include <stdio.h>
#include <stdbool.h>
#include "articulos.h"
#include "ventas.h"


int main()
{
    int opcion;

    inicializarRegistrosArticulos("articulos.dat");
    inicializarRegistrosInsumos("insumos.dat");
    inicializarRegistrosMercados("mercado.dat");
    inicializarRegistrosEmpleados("empleados.dat");
    inicializarRegistrosProvedor("provedor.dat");

    printf("#### Bienvenido al sistema más moderno del mundo mundial ####\n");
    do
    {
        do
        {
            printf("Ingresa una de las siguientes opciones\n");
            printf("1) Articulos\n");
            printf("2) Insumos\n");
            printf("3) Mercados\n");
            printf("4) Empleados\n");
            printf("5) Proveedores\n");
            printf("6) Ventas\n");
            printf("7) Compras\n");
            printf("8) Control de Inventario\n");
            printf("9) Reportes\n");
            printf("10) Salir\n\n> ");

            scanf("%d",&opcion);

            if (opcion < 1 || opcion > 10)
                printf("\nIngresa un número de opción válida\n\n");


            switch (opcion)
            {
                case 1:
                    
            	    menuArticulos();
                    break;

                case 2:
                    menuInsumos();
                    break;

                case 3:
                    mercados_main();
                    break;

                case 4:
                    empleadoMenu();
                    break;
    
                case 5:
                    menuProvedor();
                    break;
    
                case 6:
                    menuVenta();
                    break;
    
                case 7:
                    menuCompra();
                    break;
                case 8:
                    menuControl();
                    break;
    
                case 9:
                    menuReporte();
                    break;
            }
        }
        while (opcion < 1 || opcion > 10);
    }
    while(opcion != 10);


    return 0;
}
