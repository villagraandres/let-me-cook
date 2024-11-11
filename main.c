#include <stdio.h>
#include <stdbool.h>
#include "articulos.h"
#include "ventas.h"


int main()
{
    int opcion;


    printf(" ____  _                           _     _               \n");
    printf("| __ )(_) ___ _ ____   _____ _ __ (_) __| | ___     __ _ \n");
    printf("|  _ \\| |/ _ \\ '_ \\ \\ / / _ \\ '_ \\| |/ _` |/ _ \\   / _` |\n");
    printf("| |_) | |  __/ | | \\ V /  __/ | | | | (_| | (_) | | (_| |\n");
    printf("|____/|_|\\___|_| |_|\\_/ \\___|_| |_|_|\\__,_|\\___/   \\__,_|\n");
    printf(" / ___|_ __ __ _ _ __  (_) __ _   ___                    \n");
    printf("| |  _| '__/ _` | '_ \\ | |/ _` | / __|                   \n");
    printf("| |_| | | | (_| | | | || | (_| || (__                    \n");
    printf(" \\____|_|  \\__,_|_| |_|/ |\\__,_(_)___|                  \n");
    printf("                     |__/                                \n\n");
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

    // Escribir logs
    EscribirLogProvedor();
    EscribirLogInsumo();
    EscribirLogArticulo();
    EscribirLogMercado();



    return 0;
}
