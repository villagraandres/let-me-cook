#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "empleados.h"

void empleadoMenu() {
    struct empleado datos = {0, "", "", "", 0, 0, 0, 0, "", 0, "", "", ""};
    FILE *archivo;
    bool registros = true;
    int i, cont1, cont3;
    char opcion;

    archivo = fopen("empleados.dat", "a");
    if (archivo == NULL) {
        printf("Error al abrir el archivo\n");
        return;
    }

    while (registros) {
        do {
            printf("Clave: ");
            scanf("%d", &datos.numero_empleado);
            if (datos.numero_empleado < 1 || datos.numero_empleado > 1000)
                printf("Número inválido\n");
        } while (datos.numero_empleado < 1 || datos.numero_empleado > 1000);

        do {
            printf("Nombre: ");
            fflush(stdin);
            fgets(datos.nombre, sizeof(datos.nombre), stdin);
            datos.nombre[strcspn(datos.nombre, "\n")] = 0; 
            cont1 = 0;
            if (strlen(datos.nombre) < 10) {
                printf("Longitud inválida, asegúrese de que sean más de 10 caracteres\n");
            } else {
                for (i = 0; i < strlen(datos.nombre); i++) {
                    if (!isalpha(datos.nombre[i]) && datos.nombre[i] != ' ') {
                        printf("Hay datos inválidos\n");
                        cont1 = 1;
                        break;
                    }
                }
            }
        } while (strlen(datos.nombre) < 10 || cont1 == 1);

        do {
            printf("RFC: ");
            fflush(stdin);
            fgets(datos.rfc, sizeof(datos.rfc), stdin);
            datos.rfc[strcspn(datos.rfc, "\n")] = 0;
            cont3 = 0;
            if (strlen(datos.rfc) != 13) {
                printf("Longitud inválida, asegúrese de que sean 13 caracteres\n");
                cont3 = 1;
            }
            for (i = 0; i < 13; i++) {
                if (!isalnum(datos.rfc[i])) {
                    printf("RFC inválido, asegúrese de que solo contenga caracteres alfanuméricos\n");
                    cont3 = 1;
                    break;
                }
            }
        } while (cont3);

        do {
            printf("Correo electrónico: ");
            fflush(stdin);
            fgets(datos.correo_electronico, sizeof(datos.correo_electronico), stdin);
            datos.correo_electronico[strcspn(datos.correo_electronico, "\n")] = 0; 
            if (strchr(datos.correo_electronico, '@') == NULL || strchr(datos.correo_electronico, '.') == NULL)
                printf("Correo inválido\n");
        } while (strchr(datos.correo_electronico, '@') == NULL || strchr(datos.correo_electronico, '.') == NULL);

        do {
            printf("Comisión: ");
            scanf("%f", &datos.comision);
            if (datos.comision < 0 || datos.comision > 100)
                printf("Descuento inválido\n");
        } while (datos.comision < 0 || datos.comision > 100);

        do {
            printf("Año de nacimiento: ");
            scanf("%d", &datos.year);
            if (datos.year < 1950 || datos.year > 2006)
                printf("Dato inválido\n");
        } while (datos.year < 1950 || datos.year > 2006);

        do {
            printf("Mes de nacimiento: ");
            scanf("%d", &datos.mes);
            if (datos.mes < 1 || datos.mes > 12)
                printf("Dato inválido\n");
        } while (datos.mes < 1 || datos.mes > 12);

        do {
            printf("Día de nacimiento: ");
            scanf("%d", &datos.dia);
            cont3 = 0;
            if (datos.mes == 2) {
                if (datos.dia < 1 || datos.dia > 28) {
                    printf("Dato inválido\n");
                    cont3 = 1;
                }
            } else if (datos.mes == 1 || datos.mes == 3 || datos.mes == 5 || datos.mes == 7 || datos.mes == 8 || datos.mes == 10 || datos.mes == 12) {
                if (datos.dia < 1 || datos.dia > 31) {
                    printf("Dato inválido\n");
                    cont3 = 1;
                }
            } else if (datos.mes == 4 || datos.mes == 6 || datos.mes == 9 || datos.mes == 11) {
                if (datos.dia < 1 || datos.dia > 30) {
                    printf("Dato inválido\n");
                    cont3 = 1;
                }
            }
        } while (cont3 == 1);

        do {
            printf("Calle: ");
            fflush(stdin);
            fgets(datos.calle, sizeof(datos.calle), stdin);
            datos.calle[strcspn(datos.calle, "\n")] = 0; 
            cont1 = 0;
            for (i = 0; i < strlen(datos.calle); i++) {
                if (!isalpha(datos.calle[i]) && datos.calle[i] != ' ') {
                    printf("Hay datos inválidos\n");
                    cont1 = 1;
                    break;
                }
            }
        } while (cont1 == 1);

        do {
            printf("Número de calle: ");
            scanf("%d", &datos.numero);
            if (datos.numero < 1)
                printf("Dato inválido\n");
        } while (datos.numero < 1);

        do {
            printf("Colonia: ");
            fflush(stdin);
            fgets(datos.colonia, sizeof(datos.colonia), stdin);
            datos.colonia[strcspn(datos.colonia, "\n")] = 0; 
            cont1 = 0;
            for (i = 0; i < strlen(datos.colonia); i++) {
                if (!isalpha(datos.colonia[i]) && datos.colonia[i] != ' ') {
                    printf("Hay datos inválidos\n");
                    cont1 = 1;
                    break;
                }
            }
        } while (cont1 == 1);

        do {
            printf("Municipio: ");
            fflush(stdin);
            fgets(datos.municipio, sizeof(datos.municipio), stdin);
            datos.municipio[strcspn(datos.municipio, "\n")] = 0; 
            cont1 = 0;
            for (i = 0; i < strlen(datos.municipio); i++) {
                if (!isalpha(datos.municipio[i]) && datos.municipio[i] != ' ') {
                    printf("Hay datos inválidos\n");
                    cont1 = 1;
                    break;
                }
            }
        } while (cont1 == 1);

        do {
            printf("Estado: ");
            fflush(stdin);
            fgets(datos.estado, sizeof(datos.estado), stdin);
            datos.estado[strcspn(datos.estado, "\n")] = 0; 
            cont1 = 0;
            for (i = 0; i < strlen(datos.estado); i++) {
                if (!isalpha(datos.estado[i]) && datos.estado[i] != ' ') {
                    printf("Hay datos inválidos\n");
                    cont1 = 1;
                    break;
                }
            }
        } while (cont1 == 1);

        fseek(archivo, (datos.numero_empleado - 1) * sizeof(struct empleado), SEEK_SET);
        fwrite(&datos, sizeof(struct empleado), 1, archivo);

        do {
            printf("¿Hay más registros? S/N: ");
            fflush(stdin);
            scanf(" %c", &opcion);
            if (opcion == 'N' || opcion == 'n')
                registros = false;
            else if (opcion != 'N' && opcion != 'n' && opcion != 'S' && opcion != 's')
                printf("Opción inválida\n");
        } while (opcion != 'N' && opcion != 'n' && opcion != 'S' && opcion != 's');
    }

    fclose(archivo);
}
