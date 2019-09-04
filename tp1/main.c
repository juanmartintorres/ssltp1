#include <stdio.h>
#include <stdlib.h>
#include "main.h"


int main(void)
{
    int input=0;

    printf("*******************************************  ¡Hola Bienvenido!  *******************************************\n");
    printf("                                             Eligir un reporte:                                            \n");
    printf("\n");
    printf("Ingrese el numero 1 si desea listar en pantalla las especies cuyo %% de variacion supera el 0.5%%          \n");
    printf("Ingrese el numero 2 para exportar a información a una tabla csv.                                           \n");
    printf("Ingrese el numero 3 si desea listar el mismo reporte que la opcion 1 pero en una tabla html.               \n");
    printf("Ingrese el numero 4 si desea salir.                                                                        \n");
    scanf("\n%d", &input);

    while(input != 4){
        obtenerHTMLDeArchivo();

        switch(input){
            case 1:
                    listarEspecieVariacion();
                    break;
            case 2:
                    listarAcciones();
                    break;
            case 3:
                    generarTablaHTML();
                    break;

            default: printf("Opcion Incorrecta, por favor volver a ingresar una opcion correcta.\n");
        }

        printf("Ingrese una nueva opcion:");

        scanf("\n%d", &input);
    }
    printf("Gracias por utilizar nuestro sistema.\n");

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
    FILE *tabla = fopen("BOLSAR.csv","w");
    fprintf(tabla,"; Especie; Precio de compra; Precio de venta; Apertura; Precio Máximo; Precio Mínimo\n");
    if (tabla == NULL) return -1;
    for(int i=0;i<20;i++){
        fprintf(tabla,"%i;%s;%f;%f;%f;%f;%f\n",i,
                listadoAcciones[i].nombre,listadoAcciones[i].precioCompra,listadoAcciones[i].precioVenta,
                listadoAcciones[i].apertura,listadoAcciones[i].maximo,listadoAcciones[i].minimo);
    }
    printf("Se ha creado la tabla con exito.\n");
    fclose(tabla);
}

void listarEspecieVariacion(){
    double variacionMaxima = 0.5;
    printf("ESPECIE|VARIACION\n");
    for(int i=0;i<20;i++){
        if(listadoAcciones[i].variacion > variacionMaxima){
            printf("%7s|%9.2f\n",listadoAcciones[i].nombre, listadoAcciones[i].variacion);
        }
    }
}

void generarTablaHTML(){
    FILE *tablaHTML = fopen("Variaciones.html","w");
    fprintf(tablaHTML,"<table border = \"1\"> <tr> <th>Especie</th> <th>Variacion</th> </tr>\n");
    double variacionMaxima = 0.5;
    for(int i=0;i<20;i++){
        if(listadoAcciones[i].variacion > variacionMaxima){
            if(listadoAcciones[i].precioCompra < listadoAcciones[i].apertura && listadoAcciones[i].precioVenta < listadoAcciones[i].apertura)
                fprintf(tablaHTML,"<tr style=\"color:red;\">");
            else
                fprintf(tablaHTML,"<tr>");
            fprintf(tablaHTML,"<td> %7s </td> <td>%9.2f</td> </tr>\n",listadoAcciones[i].nombre, listadoAcciones[i].variacion);
        }
    }
    fprintf(tablaHTML,"</tr> </table>");
    fclose(tablaHTML);
    printf("Se ha generado con exito la tabla en formato HTML\n");
}
