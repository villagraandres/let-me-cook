
struct Articulo
{
    int claveArticulo;
    char descripcion[200];
    char temporadaSiembra;
    char temporadaCosecha;
    int claveMercados;
    int insumosRequeridos;  
    int costo;
    int precios;
    int invenrario;

};


void menuArticulos();


void lecturaArticulo();


void inicializarRegistros();