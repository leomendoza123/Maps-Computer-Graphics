#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
void cargarArchivo (char* nombreArchivo){
  FILE *stream;
  double puntos[1000][2];
  char *xValue;
  char *yValue;
  char xV;
  char yV;
  //char line[] = "SEVERAL WORDS";
  char *search = ",";
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
               
               xValue = strtok(line, search); // X
               yValue = strtok(NULL, search); //Y
               yValue[strlen(yValue) - 1] = '\0'; //se elimina el enter

               puntos[indexPuntos][0] =  atof(xValue);
               puntos[indexPuntos][1] =  atof(yValue); 
                printf("x: %f",puntos[indexPuntos][0]);
                printf("y: %f",puntos[indexPuntos][1]);
                
                printf("\n");
               indexPuntos = indexPuntos + 1;
           }

           free(line);
           fclose(stream);
           exit(EXIT_SUCCESS);
}
