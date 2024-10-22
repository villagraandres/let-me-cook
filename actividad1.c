#include <stdio.h>
#include <stdbool.h>
int main() {
    struct Alumno{
        char nombre[60];
        int matricula;
        float promedio;
        float calf1,calf2,calf3;
    };

    struct Alumno datos_alumnos[20];
    int n;
    float promedioT,promediop;
    printf("Ingrese la cantidad de alumnos: ");
    scanf("%d",&n);
    for(int i=0;i<n;i++) {
        printf("Ingrese su nombre: ");
        getchar();
        fgets(datos_alumnos[i].nombre,60,stdin);

        printf(" \n Ingrese su matricula: ");
        scanf("%d",&datos_alumnos[i].matricula);

        do {
            printf("Ingrese la calificacion 1: ");
            scanf("%f",&datos_alumnos[i].calf1);
            if(datos_alumnos[i].calf1>100 || datos_alumnos[i].calf1<0) {
                printf("Dato invalido");
            }
        }while(datos_alumnos[i].calf1>100 || datos_alumnos[i].calf1<0);

        do {
            printf("Ingrese la calificacion 2  ");
            scanf("%f",&datos_alumnos[i].calf2);
            if(datos_alumnos[i].calf2>100 || datos_alumnos[i].calf2<0) {
                printf("Dato invalido");
            }
        }while(datos_alumnos[i].calf2>100 || datos_alumnos[i].calf2<0);


        do {
            printf("Ingrese la calificacion 3 ");
            scanf("%f",&datos_alumnos[i].calf3);
            if(datos_alumnos[i].calf3>100 || datos_alumnos[i].calf3<0) {
                printf("Dato invalido");
            }
        }while(datos_alumnos[i].calf3>100 || datos_alumnos[i].calf3<0);
        datos_alumnos[i].promedio=datos_alumnos[i].calf1+datos_alumnos[i].calf2+datos_alumnos[i].calf3;
        promedioT+=datos_alumnos[i].promedio;
    }

    for(int i=0;i<n;i++) {
        printf("\nNombre: %s Matricula: %d",datos_alumnos[i].nombre,datos_alumnos[i].matricula);
        printf("\nPromedio: %f",datos_alumnos[i].promedio/3);
        printf("\nCalificacion 1, 2, 3: %f %f %f",datos_alumnos[i].calf1,datos_alumnos[i].calf2,datos_alumnos[i].calf3);
        printf("\n___________________________________");

    }

    printf("\nPromedio total: %f",promedioT/n);


}