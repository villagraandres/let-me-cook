#include <stdio.h>

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