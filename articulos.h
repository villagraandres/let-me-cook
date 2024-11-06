#ifndef ARTICULOS_H
#define ARTICULOS_H

#include "insumos.h"

struct Articulo
{
    int claveArticulo;
    char descripcion[200];
    
    char temporadaSiembra[20];
    char temporadaCosecha[20];
    
    int claveMercados[10];
    int insumosRequeridos[10];  
    
    float costo;
    float precio;
    int inventario;

};


void menuArticulos();


void lecturaArticulo();


void inicializarRegistrosArticulos();

int claveExiste(int , FILE* ,char* );

// Función generica para visualizar los elementos de un archivo secuencial

void viewElements();

// Funcion para registrar el provedor dado x insumo
void preguntarProvedor(struct Articulo*,struct Insumo*);

void writeOutput1();


#endif //  ARTICULOS_H
