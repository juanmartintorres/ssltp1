#ifndef MAIN_H_
#define MAIN_H_

FILE *popen(const char *command, const char *mode);
int pclose(FILE *stream);
int main();
void obtenerHTMLDeWget();
void obtenerHTMLDeArchivo();

typedef struct{
    char nombre[255];
    char vto[255];
    int cantidadNominal;
    double precioCompra;
    double precioVenta;
    int cantNominal2; //(no se porque esta repetido)
    double ultimo;
    double variacion;
    double apertura;
    double maximo;
    double minimo;
    double cierreAnt;
    int volNominal;
    int montoOperado;
    int cantOperada;
    char horaCotizacion[255];
} Accion;

Accion listadoAcciones[20];

#endif /* MAIN_H_ */
