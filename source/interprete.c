/* 
 * File:   interprete.c
 * Author: Carlos Li Hu && David Lopez && Elvira Vegas
 */

#include "interprete.h"

/* @BRIEF Transforma una cadena en el formato mas adecuado
 * @AUTHOR David Lopez
 * @PARAM La cadena a transformar
 * @RETURN Ok si se ha transformado correctamente o Error
 */
STATUS mayus(char* cadena) {

    int i = 0;

    if (!cadena) return ERROR;
    /*transformamos las mayusculas en minusculas*/
    for (i = 0; i <= strlen(cadena); i++) {
        if (cadena[i] >= 'A' && cadena[i] <= 'Z')
            cadena[i] = cadena [i] + 32;

    }

    return OK;

}

/* @BRIEF Eliminar espacios innecesarios de una cadena
 * @AUTHOR Elvira Vegas
 * @PARAM La cadena para transformar
 * @RETURN Ok si se ha transformado correctamente o Error
 */
STATUS elim_espac(char* cadena) {

    int i = 0, j = 0;
    char *aux = NULL;
    if (cadena == NULL)
        return ERROR;

    aux = (char *) malloc((strlen(cadena) + 1) * sizeof (char));
    if (aux == NULL)
        return ERROR;

    /*comprobamos si hay espacios demas y los elminamos*/
    if (cadena[0] == ' ') {
        while (cadena[i] == ' ') {
            i++;
        }
    }
    for (j = 0; i < (strlen(cadena) + 1); i++) {

        if (cadena[i] != ' ') {
            aux[j] = cadena[i];
            j++;
        } else {
            aux[j] = ' ';
            j++;
            while (cadena[i + 1] == ' ') {
                i++;
            }
        }
    }

    for (i = 0; i < (strlen(aux) + 1); i++)
        cadena[i] = aux[i];

    free(aux);

    return OK;
}

/* @BRIEF Elimina las particulas de union entre palabras clave
 * @AUTHOR Carlos Li Hu
 * @PARAM La cadena y un fichero con las palabras que se deben omitir
 * @RETURN Ok si se ha transformado correctamente o Error
 */
STATUS elim_part(char* cadena, char** part, int num_part) {
    char*token = NULL, aux[50];
    int i, flag, cont, j, tam_tok;
    if (!part || !cadena || num_part <= 0)
        return ERROR;

    /*partimos la cadena introducida*/
    token = strtok(cadena, " ");
    cont = 0;
    /*eliminamos las particulas*/
    while (token != NULL) {
        flag = 0;
        for (i = 0; i < num_part; i++)
            if (strcmp(token, part[i]) == 0) {
                flag = 1;
                break;
            }
        if (flag == 0) {
            tam_tok = strlen(token);
            /*strcat(aux,token);*/
            for (j = 0; j < tam_tok; j++)
                aux[j + cont] = token[j];
            aux[j + cont] = ' ';
            cont += tam_tok + 1;
        }
        token = strtok(NULL, " ");
    }
    aux[cont - 1] = '\0';
    /*copiamos la cadena buena*/
    strcpy(cadena, aux);
    return OK;
}

/* @BRIEF Relaciona palabras clave con sinonimos
 * @AUTHOR Elvira Vegas
 * @PARAM La cadena y un fichero con los sinonimos de las palabras
 * @RETURN Ok si se ha transformado correctamente o Error
 */

STATUS sinonimos(char* cadena, char***sin, int* num_sin) {
    int i = 0;


    /*obtenemos el numero de sinonimos que hay por cada accion y comprobamos si existe el sinonimo*/
    for (i = 0; i < num_sin[0]; i++) {
        if (strcmp(cadena, sin[0][i]) == 0) {
            strcpy(cadena, "mover");
            return OK;
        }
    }

    for (i = 0; i < num_sin[1]; i++) {
        if (strcmp(cadena, sin[1][i]) == 0) {
            strcpy(cadena, "coger");
            return OK;
        }
    }
    for (i = 0; i < num_sin[2]; i++) {
        if (strcmp(cadena, sin[2][i]) == 0) {
            strcpy(cadena, "dejar");
            return OK;
        }
    }
    for (i = 0; i < num_sin[3]; i++) {
        if (strcmp(cadena, sin[3][i]) == 0) {
            strcpy(cadena, "encender");
            return OK;
        }
    }
    for (i = 0; i < num_sin[4]; i++) {
        if (strcmp(cadena, sin[4][i]) == 0) {
            strcpy(cadena, "apagar");
            return OK;
        }
    }
    for (i = 0; i < num_sin[5]; i++) {
        if (strcmp(cadena, sin[5][i]) == 0) {
            strcpy(cadena, "abrir");
            return OK;
        }
    }
    for (i = 0; i < num_sin[6]; i++) {
        if (strcmp(cadena, sin[6][i]) == 0) {
            strcpy(cadena, "hablar");
            return OK;
        }
    }
    for (i = 0; i < num_sin[7]; i++) {
        if (strcmp(cadena, sin[7][i]) == 0) {
            strcpy(cadena, "examinar");
            return OK;
        }
    }
    for (i = 0; i < num_sin[8]; i++) {
        if (strcmp(cadena, sin[8][i]) == 0) {
            strcpy(cadena, "dormir");
            return OK;
        }
    }
    for (i = 0; i < num_sin[9]; i++) {
        if (strcmp(cadena, sin[9][i]) == 0) {
            strcpy(cadena, "despertar");
            return OK;
        }
    }
    return OK;
}

/* @BRIEF Distingue la clases de palabras que hay en la cadena
 * @AUTHOR David Lopez
 * @PARAM La cadena a analizar, y tres fragmentos de cadena para guardar cada clase
 * @RETURN Ok si se ha analizado correctamente o Error
 */

STATUS gramatica(char* cadena, char* verbo, char* directo, char* indirecto) {


    char separador[] = " ";
    char* trozo1 = NULL;
    char* trozo2 = NULL;
    char* trozo3 = NULL;
    char* trozo4 = NULL;

    if (!cadena) return ERROR;

    /*partimos la cadena*/
    trozo1 = strtok(cadena, separador);
    if (!trozo1) {
        return ERROR;
    }
    /*comprobamos en que accion nos encontramos*/
    if (strcmp("salir", trozo1) == 0) {
        strcpy(verbo, "salir");
        return OK;
    } else if (strcmp("guardar", trozo1) == 0) {
        strcpy(verbo, "guardar");
        return OK;
    } else if (strcmp("cargar", trozo1) == 0) {
        strcpy(verbo, "cargar");
        return OK;
    } else if (strcmp("despertar", trozo1) == 0) {
        strcpy(verbo, "despertar");
        return OK;
    } else if (strcmp("activarse", trozo1) == 0) {
        strcpy(verbo, "despertar");
        return OK;
    } else if (strcmp("despertarse", trozo1) == 0) {
        strcpy(verbo, "despertar");
        return OK;
    } else if (strcmp("despabilarse", trozo1) == 0) {
        strcpy(verbo, "despertar");
        return OK;
    } else if (strcmp("desadormecerse", trozo1) == 0) {
        strcpy(verbo, "despertar");
        return OK;
    } else if (strcmp("dormir", trozo1) == 0) {
        strcpy(verbo, "dormir");
        return OK;
    } else if (strcmp("dormitar", trozo1) == 0) {
        strcpy(verbo, "dormir");
        return OK;
    } else if (strcmp("reposar", trozo1) == 0) {
        strcpy(verbo, "dormir");
        return OK;
    } else if (strcmp("descansar", trozo1) == 0) {
        strcpy(verbo, "dormir");
        return OK;
    } else if (strcmp("yacer", trozo1) == 0) {
        strcpy(verbo, "dormir");
        return OK;
    } else if (strcmp("adormilarse", trozo1) == 0) {
        strcpy(verbo, "dormir");
        return OK;
    } else if (strcmp("dormirse", trozo1) == 0) {
        strcpy(verbo, "dormir");
        return OK;
    }

    /*comprobamos los casos de error*/
    trozo2 = strtok(NULL, separador);
    if (!trozo2) {
        return ERROR;
    }
    strcpy(directo, trozo2);
    trozo3 = strtok(NULL, separador);

    if (trozo3 != NULL) {
        trozo4 = strtok(NULL, separador);

        if (trozo4 != NULL) {
            return ERROR;
        }
    }

    strcpy(verbo, trozo1);

    /*si el verbo no tiene indirecto asignamos vacio a ese campo*/
    if (trozo3 != NULL) {
        strcpy(indirecto, trozo3);
    } else if (trozo3 == NULL) {
        strcpy(indirecto, "vacio");
    }


    return OK;


}

/* @BRIEF Aúna todas las funciones anteriores
 * @AUTHOR Carlos Li Hu
 * @PARAM La cadena a analizar,tres fragmentos de cadena para guardar cada clase y dos ficheros con las partículas y los sinónimos  
 * respectivamente
 * @RETURN Ok si se ha realizado correctamente o Error
 */
STATUS interprete(char *cadena, char* verbo, char* directo, char* indirecto, char**part, char***sin, int num_part, int*num_sin) {
    /*comprobamos que las funciones del interprete funcionen*/
    mayus(cadena);
    elim_espac(cadena);
    elim_part(cadena, part, num_part);
    gramatica(cadena, verbo, directo, indirecto);
    sinonimos(verbo, sin, num_sin);
    return OK;
}
