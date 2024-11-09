#ifndef ARTICULOS_H
#define ARTICULOS_H
#include <stdio.h>


struct Articulo;
struct Insumo; // Declare struct Insumo here

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
int claveExiste(int, FILE*, char*);
void viewElements();
void preguntarProvedor(struct Articulo*, struct Insumo*); // Use the declared struct Insumo here


void writeOutput1();

void writeOutput5();


struct Empleado{
    int numero_empleado;
    char nombre[200];
    char rfc[14];
    char correo_electronico[200];
    float comision;
    int year;
    int mes;
    int dia;
    char calle[150];
    int numero;
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
    int year;
    int mes;
    int dia;
    char calle[150];
    int numero;
    char colonia[100];
    char municipio[100];
    char estado[100];
};
void mercados_main();


// Insumos
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


void inicializarRegistrosInsumos();

void lecturaInsumo(struct Insumo*);

int claveInsumoExiste(int , FILE* ,char*);

void writeOutput2();

// Provedor

struct Provedor
{
    int claveProvedor;
    char nombre[100];
    char rfc[50];
    char correo[100];
    float descuento;

    int año;
    int mes;
    int dia;

    char calle[150];
	char numero [10];
	char colonia[100];
	char municipio[100];
	char estado[100];
};


void menuProvedor();


void inicializarRegistrosProvedor();

void lecturaProvedor(struct Provedor*);

void validarRFC(struct Provedor*);

void validarCorreo(char*);

void validarDireccion(struct Provedor*);

int claveProvedorExiste(int , FILE* ,char* );


void writeOutput();





#endif // ARTICULOS_H