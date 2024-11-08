#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "mercados.h"
#include "manejoArchivos.h"
#include "utils.h"


void inicializar_registros();

void mercados_main() 
{
    inicializar_registros();
    struct Mercado datos = {0, "", "", "", 0, 0, 0, 0, "", 0, "", "", ""};
    FILE *archivo;
    bool registros = true;
    char opcion;
    int i, cont1;

    archivo = fopen("mercado.dat", "rb+");
    if (archivo == NULL) 
    {
        printf("Error al abrir el archivo\n");
        return;
    }

    while (registros) 
    {
        do 
        {
            printf("Clave: ");
            scanf("%d", &datos.clave);
            if (datos.clave <= 0)
                printf("Clave invalida\n");
        } 
        while (datos.clave <= 0);

        clear_input_buffer();

        do 
        {
            printf("Nombre: ");
            fgets(datos.nombre, sizeof(datos.nombre), stdin);
            datos.nombre[strcspn(datos.nombre, "\n")] = '\0'; 
        } 
        while (strlen(datos.nombre) == 0);

        do 
        {
            printf("RFC: ");
            fgets(datos.RFC, sizeof(datos.RFC), stdin);
            datos.RFC[strcspn(datos.RFC, "\n")] = '\0';
        } 
        while (strlen(datos.RFC) == 0);

        do 
        {
            printf("Correo Electronico: ");
            fgets(datos.correo_electronico, sizeof(datos.correo_electronico), stdin);
            datos.correo_electronico[strcspn(datos.correo_electronico, "\n")] = '\0'; 
        } 
        while (strlen(datos.correo_electronico) == 0);

        printf("Descuento: ");
        scanf("%f", &datos.descuento);
        clear_input_buffer();

        printf("Fecha (YYYY MM DD): ");
        scanf("%d %d %d", &datos.year, &datos.mes, &datos.dia);
        clear_input_buffer();

        do 
        {
            printf("Calle: ");
            fgets(datos.calle, sizeof(datos.calle), stdin);
            datos.calle[strcspn(datos.calle, "\n")] = '\0';
        } 
        while (strlen(datos.calle) == 0);

        printf("Numero: ");
        scanf("%d", &datos.numero);
        clear_input_buffer();

        do 
        {
            printf("Colonia: ");
            fgets(datos.colonia, sizeof(datos.colonia), stdin);
            datos.colonia[strcspn(datos.colonia, "\n")] = '\0'; 
            cont1 = 0;
            for (i = 0; i < strlen(datos.colonia); i++) 
            {
                if (!((datos.colonia[i] >= 'A' && datos.colonia[i] <= 'Z') ||
                      (datos.colonia[i] >= 'a' && datos.colonia[i] <= 'z') ||
                      datos.colonia[i] == ' ')) 
                {
                    printf("Hay datos invalidos\n");
                    cont1 = 1;
                    break;
                }
            }
        } 
        while (cont1 == 1);

        do 
        {
            printf("Municipio: ");
            fgets(datos.municipio, sizeof(datos.municipio), stdin);
            datos.municipio[strcspn(datos.municipio, "\n")] = '\0'; 
            cont1 = 0;
            for (i = 0; i < strlen(datos.municipio); i++) 
            {
                if (!((datos.municipio[i] >= 'A' && datos.municipio[i] <= 'Z') ||
                      (datos.municipio[i] >= 'a' && datos.municipio[i] <= 'z') ||
                      datos.municipio[i] == ' ')) 
                {
                    printf("Hay datos invalidos\n");
                    cont1 = 1;
                    break;
                }
            }
        } 
        while (cont1 == 1);

        do 
        {
            printf("Estado: ");
            fgets(datos.estado, sizeof(datos.estado), stdin);
            datos.estado[strcspn(datos.estado, "\n")] = '\0'; 
            cont1 = 0;
            for (i = 0; i < strlen(datos.estado); i++) 
            {
                if (!((datos.estado[i] >= 'A' && datos.estado[i] <= 'Z') ||
                      (datos.estado[i] >= 'a' && datos.estado[i] <= 'z') ||
                      datos.estado[i] == ' ')) 
                {
                    printf("Hay datos invalidos\n");
                    cont1 = 1;
                    break;
                }
            }
        } while (cont1 == 1);

        fseek(archivo,sizeof(struct Mercado)*(datos.clave-1),SEEK_SET);
        if (fwrite(&datos, sizeof(struct Mercado), 1, archivo) != 1) 
        {
            printf("Error al escribir en el archivo\n");
        }

        do 
        {
            printf("¿Hay más registros? S/N: ");
            clear_input_buffer(); 
            opcion = getchar();
            if (opcion == 'N' || opcion == 'n')
                registros = false;
            else if (opcion != 'N' && opcion != 'n' && opcion != 'S' && opcion != 's')
                printf("Opción invalida\n");
        } 
        while (opcion != 'N' && opcion != 'n' && opcion != 'S' && opcion != 's');
    }

    fclose(archivo);
}

void inicializar_registros() 
{
    char nombreArchivo[] = "mercado.dat";
    FILE* cfptr;
    struct Mercado mercadoInfo = {0};

    if (existeArchivo(cfptr, nombreArchivo) == 1) 
    {
        if (crearArchivo(cfptr, nombreArchivo, &mercadoInfo, 100, sizeof(struct Mercado)) != 0) 
        {
            printf("Error al crear el archivo\n");
            return;
        }
    }
}
