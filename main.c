#include <stdio.h>
#include <stdbool.h>
#include "articulos.h"
#include "manejoArchivos.h"
#include "utils.h"
#include "insumos.h"

int main()
{

    // Declaración de variables
    int opcion;

    printf("#### Bienvenido al sistema más moderno del mundo mundial ####\n");
    do
    {
        do
        {
            printf("Ingresa una de las siguientes opciones\n");
            printf("1) Artículos\n");
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
                //viewElements();
                break;

            case 2:
                menuInsumos();
                break;

            case 3:
                break;

            case 4:
                break;

            case 5:
                break;

            case 6:
                break;

            case 7:
                break;

            case 8:
                break;

            case 9:
                break;

            }


        } while (opcion < 1 || opcion > 10);

    }while(opcion != 10);


    return 0;
}