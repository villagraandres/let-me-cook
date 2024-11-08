#include <stdbool.h>

struct Venta {
    int numeroMercado;
    int numeroArticulo;
    int cantidad;
    float precio;
    int empleado;


};
void menuVenta();
bool validarExistencia(int clave, int modo, FILE *archivoMercados, FILE *archivoArticulos);
bool validarCantidad(int numeroArticulo, int cantidad, FILE *archivo);
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