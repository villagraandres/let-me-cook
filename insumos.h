#ifndef INSUMOS_H
#define INSUMOS_H


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

#endif // INSUMOS_H
