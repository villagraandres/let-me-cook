#ifndef ARTICULOS_H
#define ARTICULOS_H
#include <stdio.h>
#include <stdbool.h>

struct Articulo;
struct Insumo; 

struct Articulo
{
    int claveArticulo;
    char descripcion[200];
    
    char temporadaSiembra[20];
    char temporadaCosecha[20];

    char ddd[20];
    
    int claveMercados[10];
    int insumosRequeridos[10];  
    
    float costo;
    float precio;
    int inventario;
};


void inicializarRegistrosArticulos(char*);
void inicializarRegistrosInsumos(char *);
void inicializarRegistrosMercados(char*);
void inicializarRegistrosEmpleados(char*);
void inicializarRegistrosProvedor(char*);


void menuArticulos();
void lecturaArticulo();

int claveExiste(int, FILE*, char*);
void preguntarProvedor(struct Articulo*, struct Insumo*); 


struct Empleado{
    int numero_empleado;
    char nombre[200];
    char rfc[14];
    char correo_electronico[200];
    float comision;
    int anos;
    int mes;
    int dia;
    char calle[150];
    char numero[20];
    char colonia[100];
    char municipio[100];
    char estado[100];
};
void empleadoMenu();


struct Mercado{
    int clave;
    char nombre[200];
    char RFC[14];
    char correo_electronico[200];
    float descuento;
    int anio;
    int mes;
    int dia;
    char calle[150];
    char numero[12];
    char colonia[100];
    char municipio[100];
    char estado[100];
};
void mercados_main();



struct Insumo
{
	
	int claveInsumo;
	char descripcion[200];
	int puntoReorden;
	int inventario;
	
	int provedores[10];
	float precios[10]; 

};


void menuInsumos();




void lecturaInsumo(struct Insumo*);

int claveInsumoExiste(int , FILE* ,char*);




struct Provedor
{
    int claveProvedor;
    char nombre[100];
    char rfc[15];
    char correo[100];
    float descuento;

    int anio;
    int mes;
    int dia;

    char calle[150];
	char numero [12];
	char colonia[100];
	char municipio[100];
	char estado[100];
};


void menuProvedor();



void lecturaProvedor(struct Provedor*);

void validarRFC(char *);

void validarCorreo(char*);

void validarDireccion(char* ,char* , char* ,char* , char* );

void validarFecha(int*,int*,int*);

int claveProvedorExiste(int , FILE* ,char* );



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


int existeArchivo(FILE*, char*);
int crearArchivo(FILE* fptr, char* fArchivo, void* estructura, int cantidadEstructuras, int tamanoEstructura);


void validarCadena(char*);


void validarNombre(char*);

void clear_input_buffer();
void menuControl();
bool validarProvedor(int, FILE *);

int existeNumero(int arreglo[], int tam, int numero, int modo);

void ventaFecha();

void listadoventaArticulos(FILE *archivoV);
bool validarArticulo(FILE *,int);
void listadoInsumos(FILE *);
void listadoSaldos(FILE *);
void listadoPendientes(FILE *);



#endif 
