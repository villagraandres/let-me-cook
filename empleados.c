#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "empleados.h"
#include "manejoArchivos.h"

void inicializar_registrosEmpleado();

bool validarCorreoE(const char* correo)
{
    const char* at = strchr(correo, '@');
    if (at == NULL) 
        return false;
    const char* dot = strrchr(at, '.');
    if (dot == NULL) 
        return false;
    return dot > at; 
}

void empleadoMenu() 
{
    inicializar_registrosEmpleado();
    struct Empleado datos = {0, "", "", "", 0, 0, 0, 0, "", 0, "", "", ""};
    FILE *archivo;
    bool registros = true;
    int i, cont1, cont3;
    char opcion;

    archivo = fopen("empleados.dat", "rb+");
    if (archivo == NULL) 
    {
        printf("Error al abrir el archivo\n");
        return;
    }

    setbuf(stdout, NULL);

    while (registros) 
    {
        do 
        {
            printf("Clave: ");
            scanf("%d", &datos.numero_empleado);
            if (datos.numero_empleado < 1 || datos.numero_empleado > 1000)
                printf("Número inválido\n");
        } 
        while (datos.numero_empleado < 1 || datos.numero_empleado > 1000);

        do 
        {
            printf("Nombre: ");
            clear_input_buffer(); 
            fgets(datos.nombre, sizeof(datos.nombre), stdin);
            datos.nombre[strcspn(datos.nombre, "\n")] = 0; 
            cont1 = 0; 

            if (strlen(datos.nombre) < 10)
            {
                printf("Longitud inválida, asegúrese de que sean más de 10 caracteres\n");
                cont1 = 1; 
            } 
            else 
            {
                for (i = 0; i < strlen(datos.nombre); i++) 
                {
                    if (!isalpha(datos.nombre[i]) && datos.nombre[i] != ' ') 
                    {
                        printf("Hay datos inválidos\n");
                        cont1 = 1; 
                        break; 
                    }
                }
            }
        } 
        while (cont1 == 1);

        printf("RFC: ");
        while (getchar() != '\n');
        fgets(datos.rfc, sizeof(datos.rfc), stdin);
        datos.rfc[strcspn(datos.rfc, "\n")] = 0;


        printf("Correo electrónico: ");
        clear_input_buffer();
        fgets(datos.correo_electronico, sizeof(datos.correo_electronico), stdin);
        datos.correo_electronico[strcspn(datos.correo_electronico, "\n")] = 0;




        do 
        {
            printf("Comisión: ");
            scanf("%f", &datos.comision);
            if (datos.comision < 0 || datos.comision > 100)
                printf("Comision inválida\n");
        } 
        while (datos.comision < 0 || datos.comision > 100);

        do 
        {
            printf("Año de nacimiento: ");
            scanf("%d", &datos.year);
            if (datos.year < 1950 || datos.year > 2006)
                printf("Dato inválido\n");
        } 
        while (datos.year < 1950 || datos.year > 2006);

        do 
        {
            printf("Mes de nacimiento: ");
            scanf("%d", &datos.mes);
            if (datos.mes < 1 || datos.mes > 12)
                printf("Dato inválido\n");
        } 
        while (datos.mes < 1 || datos.mes > 12);

        do 
        {
            printf("Día de nacimiento: ");
            scanf("%d", &datos.dia);
            cont3 = 0;
            if (datos.mes == 2) 
            {
                if (datos.dia < 1 || datos.dia > 28) 
                {
                    printf("Dato inválido\n");
                    cont3 = 1;
                }
            } 
            else if (datos.mes == 1 || datos.mes == 3 || datos.mes == 5 || datos.mes == 7 || datos.mes == 8 || datos.mes == 10 || datos.mes == 12) 
            {
                if (datos.dia < 1 || datos.dia > 31) 
                {
                    printf("Dato inválido\n");
                    cont3 = 1;
                }
            } 
            else if (datos.mes == 4 || datos.mes == 6 || datos.mes == 9 || datos.mes == 11) 
            {
                if (datos.dia < 1 || datos.dia > 30) 
                {
                    printf("Dato inválido\n");
                    cont3 = 1;
                }
            }
        } 
        while (cont3 == 1);

        do 
        {
            printf("Calle: ");
            clear_input_buffer();
            fgets(datos.calle, sizeof(datos.calle), stdin);
            datos.calle[strcspn(datos.calle, "\n")] = 0; 
            cont1 = 0;
            for (i = 0; i < strlen(datos.calle); i++) 
            {
                if (!isalpha(datos.calle[i]) && datos.calle[i] != ' ') 
                {
                    printf("Hay datos inválidos\n");
                    cont1 = 1;
                    break;
                }
            }
        } 
        while (cont1 == 1);

        do 
        {
            printf("Número de calle: ");
            scanf("%d", &datos.numero);
            if (datos.numero < 1)
                printf("Dato inválido\n");
        } 
        while (datos.numero < 1);

        do
        {
            printf("Colonia: ");
            clear_input_buffer();
            fgets(datos.colonia, sizeof(datos.colonia), stdin);
            datos.colonia[strcspn(datos.colonia, "\n")] = 0; 
            cont1 = 0;
            for (i = 0; i < strlen(datos.colonia); i++) 
            {
                if (!isalpha(datos.colonia[i]) && datos.colonia[i] != ' ') 
                {
                    printf("Hay datos inválidos\n");
                    cont1 = 1;
                    break;
                }
            }
        } 
        while (cont1 == 1);

        do 
        {
            printf("Municipio: ");
            clear_input_buffer();
            fgets(datos.municipio, sizeof(datos.municipio), stdin);
            datos.municipio[strcspn(datos.municipio, "\n")] = 0; 
            cont1 = 0;
            for (i = 0; i < strlen(datos.municipio); i++) 
            {
                if (!isalpha(datos.municipio[i]) && datos.municipio[i] != ' ') 
                {
                    printf("Hay datos inválidos\n");
                    cont1 = 1;
                    break;
                }
            }
        } 
        while (cont1 == 1);

        do 
        {
            printf("Estado: ");
            clear_input_buffer();
            fgets(datos.estado, sizeof(datos.estado), stdin);
            datos.estado[strcspn(datos.estado, "\n")] = 0; 
            cont1 = 0;
            for (i = 0; i < strlen(datos.estado); i++) 
            {
                if (!isalpha(datos.estado[i]) && datos.estado[i] != ' ') 
                {
                    printf("Hay datos inválidos\n");
                    cont1 = 1;
                    break;
                }
            }
        } 
        while (cont1 == 1);

        fseek(archivo, (datos.numero_empleado - 1) * sizeof(struct Empleado), SEEK_SET);
        fwrite(&datos, sizeof(struct Empleado), 1, archivo);

        do 
        {
            printf("¿Hay más registros? S/N: ");
            clear_input_buffer();
            scanf(" %c", &opcion);
            if (opcion == 'N' || opcion == 'n')
                registros = false;
            else if (opcion != 'N' && opcion != 'n' && opcion != 'S' && opcion != 's')
                printf("Opción inválida\n");
        } 
        while (opcion != 'N' && opcion != 'n' && opcion != 'S' && opcion != 's');
    }

    fclose(archivo);
}

void inicializar_registrosEmpleado()
{
    char nombreArchivo[] = "empleados.dat";
    FILE* cfptr;
    struct Empleado empleadoInfo = {};

    if (existeArchivo(cfptr, nombreArchivo) == 1) 
    {
        if (crearArchivo(cfptr, nombreArchivo, &empleadoInfo, 1000, sizeof(struct Empleado)) != 0) 
        {
            printf("Error al crear el archivo\n");
            return;
        }
    }
}







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




