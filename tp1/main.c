#include <stdio.h>
#include "main.h"


int main(void)
{
    obtenerHTMLDeArchivo();
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

    while (fgets(result, sizeof(result), cmd) != NULL)
        printf("%s", result);
    fclose(cmd);
}

