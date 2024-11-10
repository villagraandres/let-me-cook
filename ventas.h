#include <stdbool.h>
#include <stdio.h>

#ifndef VENTAS_H
#define VENTAS_H



struct Venta {
    int numeroMercado;
    int numeroArticulo;
    int cantidad;
    float precio;
    int empleado;
};

void menuVenta();
bool validarExistencia(int clave, int modo, FILE *archivoMercados, FILE *archivoArticulos);
bool validarCantidad(int numeroArticulo, int *cantidad, FILE *archivo);
float obtenerPrecioArticulo(int claveArticulo, FILE *archivo);
bool validarEmpleado(FILE *archivoEmpleado, int empleadoId);
void generarFactura(struct Venta ventas[], int numVentas, float total, int empleadoId);

void printArchivoMercados();
void printArchivoArticulos();
void printArchivoEmpleados();

bool validarExistenciaPI(FILE *, int, int, int);
float obtenerPrecio(int, int, FILE *);
int obtenerUltimoID(FILE *);
void menuCompra();

void listadoArticulos();
void listadoEmpleadosComision();
void menuReporte();

// MANEJO DE ARCHIVOS
int existeArchivo(FILE*, char*);
int crearArchivo(FILE* fptr, char* fArchivo, void* estructura, int cantidadEstructuras, int tamanoEstructura);

// Librera que utliza funciones de uso general como por ejemplo validar una cadena
void validarCadena(char*);

// Checa si la clave x existe en el registro
void validarNombre(char*);

void clear_input_buffer();
void menuControl();
bool validarProvedor(int, FILE *);

int existeNumero(int arreglo[], int tam, int numero);

void ventaFecha();


#endif // VENTAS_H