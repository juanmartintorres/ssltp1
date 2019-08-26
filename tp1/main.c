#include <stdio.h>
#include <stdlib.h>
#include "main.h"


int main(void)
{
    obtenerHTMLDeArchivo();
    listarAcciones();
    return 0;
}

void obtenerHTMLDeWget(){
    /* wget -q = silent mode */
    FILE *cmd = popen(".\\GnuWin32\\bin\\wget -q -O - https://www.bolsar.com/VistasDL/PaginaLideres.aspx --no-check-certificate", "r");
    char result[1048576]; //1 MB de buffer

    while (fgets(result, sizeof(result), cmd) != NULL)
        printf("%s", result);
    pclose(cmd);
}

void obtenerHTMLDeArchivo(){
    FILE *cmd = fopen("lideres_bcba.html", "r");
    char result[1048576]; //1 MB de buffer
    int i=-1;
    while (fgets(result, sizeof(result), cmd) != NULL)
    {
        //Valido primero que los primeros 4 caracteres sean <td>, caso contrario desestimo la linea
        if(result[0] == '<' && result[1] == 't' && result[2] == 'd' && result[3] == '>'){
            //No leo la primer linea que es el titulo
            if(i != -1){
                parsearAccion(result,i);
            }
            i++;
        }
    }
    fclose(cmd);
}

void parsearAccion(char result[1048575],int posicion){
    int cursor = 0;
    //Me muevo un <td>
    cursor += 4;
    //Obtengo el nombre
    leerCampo(result,&cursor,listadoAcciones[posicion].nombre);
    //Me muevo un </td><td>
    cursor += 9;
    //Obtengo el vto
    leerCampo(result,&cursor,listadoAcciones[posicion].vto);
    //Me muevo un </td><td>
    cursor += 9;
    //Obtengo Cant Nominal
    char strCantidadNominal[255];
    leerCampoNumerico(result,&cursor,strCantidadNominal);
    listadoAcciones[posicion].cantidadNominal = atoi(strCantidadNominal);
    //Me muevo un </td><td>
    cursor += 9;
    //Obtengo Precio compra
    char strPrecioCompra[255];
    leerCampoNumerico(result,&cursor,strPrecioCompra);
    listadoAcciones[posicion].precioCompra = atof(strPrecioCompra);
    //Me muevo un </td><td>
    cursor += 9;
    //Obtengo Precio venta
    char strPrecioVenta[255];
    leerCampoNumerico(result,&cursor,strPrecioVenta);
    listadoAcciones[posicion].precioVenta = atof(strPrecioVenta);
    //Me muevo un </td><td>
    cursor += 9;
    //Obtengo Cantidad Nominal 2
    char strCantidadNominal2[255];
    leerCampoNumerico(result,&cursor,strCantidadNominal2);
    listadoAcciones[posicion].cantNominal2 = atoi(strCantidadNominal2);
    //Me muevo un </td><td>
    cursor += 9;
    //Obtengo Ultimo
    char strUltimo[255];
    leerCampoNumerico(result,&cursor,strUltimo);
    listadoAcciones[posicion].ultimo = atof(strUltimo);
    //Me muevo un </td><td>
    cursor += 9;
    //Obtengo Ultimo
    char strVariacion[255];
    leerCampoNumerico(result,&cursor,strVariacion);
    listadoAcciones[posicion].variacion = atof(strVariacion);
    //Me muevo un </td><td>
    cursor += 9;
    //Obtengo Ultimo
    char strApertura[255];
    leerCampoNumerico(result,&cursor,strApertura);
    listadoAcciones[posicion].apertura = atof(strApertura);
    //Me muevo un </td><td>
    cursor += 9;
    //Obtengo Maximo
    char strMaximo[255];
    leerCampoNumerico(result,&cursor,strMaximo);
    listadoAcciones[posicion].maximo = atof(strMaximo);
    //Me muevo un </td><td>
    cursor += 9;
    //Obtengo Maximo
    char strMinimo[255];
    leerCampoNumerico(result,&cursor,strMinimo);
    listadoAcciones[posicion].minimo = atof(strMinimo);
    //Me muevo un </td><td>
    cursor += 9;
    //Obtengo Cierre Anterior
    char strCierre[255];
    leerCampoNumerico(result,&cursor,strCierre);
    listadoAcciones[posicion].cierreAnt = atof(strCierre);
    //Me muevo un </td><td>
    cursor += 9;
    //Obtengo Volumen Nominal
    char strVol[255];
    leerCampoNumerico(result,&cursor,strVol);
    listadoAcciones[posicion].volNominal = atoi(strVol);
    //Me muevo un </td><td>
    cursor += 9;
    //Obtengo Volumen Nominal
    char strMonto[255];
    leerCampoNumerico(result,&cursor,strMonto);
    listadoAcciones[posicion].montoOperado = atoi(strMonto);
    //Me muevo un </td><td>
    cursor += 9;
    //Obtengo Volumen Nominal
    char strCant[255];
    leerCampoNumerico(result,&cursor,strCant);
    listadoAcciones[posicion].cantidadNominal = atoi(strCant);
    //Me muevo un </td><td>
    cursor += 9;
    //Obtengo Hora
    leerCampo(result,&cursor,listadoAcciones[posicion].horaCotizacion);
}

void leerCampo(char result[1048575], int* cursor,char campo[255]){
    int i=0;
    //Leo hasta que haya un caracter <
    while(result[*cursor] != '<'){
        campo[i] = result[*cursor];
        i++;
        (*cursor)++;
    }
    campo[i] = '\0';
}

void leerCampoNumerico(char result[1048575], int* cursor,char campo[255]){
    int i=0;
    //Leo hasta que haya un caracter <
    while(result[*cursor] != '<'){
        //Ignoro los . para los numericos
        if(result[*cursor] != '.'){
            if(result[*cursor] != ','){
                campo[i] = result[*cursor];
            }else{
                campo[i] = '.';
            }
            i++;
        }
        (*cursor)++;
    }
    campo[i] = '\0';
}

void listarAcciones(){
    for(int i=0;i<20;i++){
        printf("%i;%s;%s;%i;%f;%f;%i;%f;%f;%f;%f;%f;%f;%i;%i;%i;%s\n",i,listadoAcciones[i].nombre,listadoAcciones[i].vto,listadoAcciones[i].cantidadNominal,
               listadoAcciones[i].precioCompra,listadoAcciones[i].precioVenta,listadoAcciones[i].cantNominal2,
               listadoAcciones[i].ultimo,listadoAcciones[i].variacion,listadoAcciones[i].apertura,
               listadoAcciones[i].maximo,listadoAcciones[i].minimo,listadoAcciones[i].cierreAnt,
               listadoAcciones[i].volNominal,listadoAcciones[i].montoOperado,listadoAcciones[i].cantidadNominal,
               listadoAcciones[i].horaCotizacion);
    }
}
