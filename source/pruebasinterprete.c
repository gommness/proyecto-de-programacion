/* 
 * File:   pruebasinterprete.c
 * Author: David Lopez && Elvira Vegas
 */

#include "interprete.h"
#define DIM 10

int main() {

    FILE *f_part, *f_sin;
    char comando[50];
    char verbo[30];
    char directo[30];
    char indirecto[30];
    char** part;
    char*** sin;
    int num_part = 0, i = 0, j = 0, num_sin[DIM];

    /*abre el fichero de las particulas*/
    f_part = fopen("particulas.txt", "r");
    if (f_part == NULL) {
        printf("Error al abrir el fichero.\n");
        return -1;
    }

    fscanf(f_part, "%d", &num_part);
    part = (char**) malloc(num_part * sizeof (char*));
    if (!part)
        return ERROR;
    for (i = 0; i < num_part; i++) {
        part[i] = (char*) malloc(27 * sizeof (char));
        fscanf(f_part, "%s", part[i]);
    }

    /*abrimos el fichero de sinonimos*/
    f_sin = fopen("sinonimos.txt", "r");
    if (f_sin == NULL) {
        printf("Error al abrir el fichero.\n");
        return -1;
    }
    for (i = 0; i < DIM; i++)
        fscanf(f_sin, "%d", &num_sin[i]);

    sin = (char***) malloc(DIM * sizeof (char**));
    for (i = 0; i < DIM; i++) {
        sin[i] = (char**) malloc(num_sin[i] * sizeof (char*));
        for (j = 0; j < num_sin[i]; j++) {
            sin[i][j] = (char*) malloc(27 * sizeof (char));
            fscanf(f_sin, "%s", sin[i][j]);
        }
    }

    fclose(f_sin);
    fclose(f_part);

    /*guardamos el comando que introduce el usuario*/
    printf("Introduzca un comando:\n");
    fgets(comando, 50, stdin);
    strtok(comando, "\n");
    if (interprete(comando, verbo, directo, indirecto, part, sin, num_part, num_sin) == ERROR) {
        printf("Error en el interprete");
        return -1;
    }

    printf("Las pruebas se han realizado con exito.\n");


    return 0;
}
