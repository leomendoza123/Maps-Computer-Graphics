#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
void cargarArchivo (char* nombreArchivo){
  FILE *stream;
  double puntos[1000][2];
  char *xValue;
  char *yValue;
  //char line[] = "SEVERAL WORDS";
  char *search = " ";
  int indexPuntos = 0;
  
           char *line = NULL;
           size_t len = 0;
           ssize_t read;

           stream = fopen(nombreArchivo, "r");
           if (stream == NULL)
               exit(EXIT_FAILURE);

           while ((read = getline(&line, &len, stream)) != -1) {
              // printf("Retrieved line of length %zu :\n", read);
              // printf("%s", line);
               
               // Token will point to "SEVERAL".
               xValue = strtok(line, search); // X
               // Token will point to "WORDS".
               yValue = strtok(NULL, search); //Y
               
               puntos[indexPuntos][0] =  strtod(xValue,NULL);
               puntos[indexPuntos][1] =  strtod(yValue,NULL);
               indexPuntos = indexPuntos + 1;
           }

           free(line);
           fclose(stream);
           exit(EXIT_SUCCESS);
}