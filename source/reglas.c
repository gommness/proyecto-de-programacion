/* 
 * File:   reglas.c
 * Author: Carlos Li Hu
 */

#include "reglas.h"
#define N_COM 10 /*numero de comandos por condición*/
#define DIM 50 /*tamaño palabras*/
#define NUM 40 /*numero consecuencias*/

/**
 * @BRIEF lee los comandos del fichero y los guarda en una tabla de comandos
 * cada uno de estos comandos compuesto por un array de palabras
 * @AUTHOR Carlos Li Hu
 * @PARAM el fichero de donde lee los comandos
 * @PARAM el número de comandos
 * @RETURN devuelve el array de comandos si ha ido bien, NULL si falla
 */
char*** leer_condiciones(FILE* f, int n_cond) {
    char*** cond = NULL;
    char**aux = NULL;
    char*token = NULL;
    int i, j;
    /*creamos la memoria auxiliar necesaria*/
    aux = (char**) malloc(n_cond * sizeof (char*));
    cond = (char***) malloc(n_cond * sizeof (char**));
    /*lee cada condicion*/
    for (i = 0; i < n_cond; i++) {
        cond[i] = (char**) malloc(N_COM * sizeof (char*));
        aux[i] = (char*) malloc(DIM * sizeof (char));
        fscanf(f, "%s", aux[i]);

        token = strtok(aux[i], ";");
        cond[i][0] = (char*) malloc(DIM * sizeof (char));
        strcpy(cond[i][0], token);
        for (j = 1; j < N_COM; j++) {
            cond[i][j] = (char*) malloc(DIM * sizeof (char));
            token = strtok(NULL, ";");
            strcpy(cond[i][j], token);
        }

    }
    /*libera la memoria auxiliar creada*/
    for (i = 0; i < n_cond; i++)
        free(aux[i]);
    free(aux);
    return cond;
}

/**
 * @BRIEF pasándole un comando ejecuta las modificaciones pertinentes si se cumplen las condiciones especificadas.
 * @AUTHOR Carlos Li Hu
 * @PARAM los comandos (compuesto de palabras por separado)
 * @PARAM el número de comandos
 * @RETURN OK si ha ido bien, ERROR si falla
 */
STATUS reglas(char*** regla, int n_cond, ESPACIO ***mapa, PERS** personajes, OBJ**objetos) {
    int i, *ubic, act;
    OBJ* aux;
    for (i = 0; i < n_cond; i++) {
        ubic = get_pers_ubic(personajes[atoi(regla[i][0])]);
        aux = get_pers_obj(personajes[atoi(regla[i][0])], regla[i][3]);
        act = get_obj_activado(aux);
        /*comprueba que se cumplen las condiciones*/
        if ((atoi(regla[i][1]) == ubic[0]) && (atoi(regla[i][2]) == ubic[1])
                && aux && atoi(regla[i][4]) == act) {
            /*si se cumplen las condiciones se pone a efectuar la consecuencia que le corresponde*/
            if (strcmp(regla[i][5], "X") != 0) {
                ubic[0] = atoi(regla[i][5]);
                ubic[1] = atoi(regla[i][6]);
                set_pers_ubic(personajes[0], ubic);
            } else if (strcmp(regla[i][7], "X") != 0) {
                if (atoi(regla[i][7]) == 0)
                    set_pers_obj(personajes[0], objetos[atoi(regla[i][8])]);
                if (atoi(regla[i][7]) == 1) {
                    destroy_obj(extract_pers_obj(personajes[0], get_obj_name(objetos[atoi(regla[i][8])])));
                }

            } else if (strcmp(regla[i][9], "X") != 0) {
                set_pers_obj(personajes[0], objetos[6]);
                abrir_puerta(mapa, personajes[0], regla[i][9], "puerta", stdout);
            }
        }

        destroy_obj(aux);

    }

    return OK;
}

/**
 * @BRIEF libera memoria de los comandos
 * @AUTHOR Carlos Li Hu
 * @PARAM los comandos
 * @PARAM el número de comandos
 * @RETURN devuelve el array de comandos si ha ido bien, NULL si falla
 */
STATUS free_reglas(char*** regla, int n_cond) {
    int i, j;
    for (i = 0; i < n_cond; i++)
        for (j = 0; j < N_COM; j++)
            free(regla[i][j]);
    for (i = 0; i < n_cond; i++)
        free(regla[i]);
    free(regla);
    return OK;
}

