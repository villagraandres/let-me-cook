#ifndef ARTICULOS_H
#define ARTICULOS_H

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

#endif // ARTICULOS_H

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



