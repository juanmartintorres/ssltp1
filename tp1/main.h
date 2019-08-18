#ifndef MAIN_H_
#define MAIN_H_

FILE *popen(const char *command, const char *mode);
int pclose(FILE *stream);
int main();
void obtenerHTMLDeWget();
void obtenerHTMLDeArchivo();

#endif /* MAIN_H_ */
