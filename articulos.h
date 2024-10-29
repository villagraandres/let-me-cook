
struct Articulo
{
    int claveArticulo;
    char descripcion[200];
    
    char temporadaSiembra[20];
    char temporadaCosecha[20];
    
    int claveMercados[10];
    int insumosRequeridos[10];  
    
    int costo;
    int precio;
    int inventario;

};


void menuArticulos();


void lecturaArticulo();


void inicializarRegistrosArticulos();

int claveExiste(int , FILE* ,char* );

// Función generica para visualizar los elementos de un archivo secuencial

void viewElements();

