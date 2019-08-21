/* 
 * File:   reglas.h
 * Author: Carlos Li Hu
 *
 * Created on 26 de noviembre de 2015, 19:28
 */

#ifndef REGLAS_H
#define	REGLAS_H
#include "guardar_cargar.h"
/**
 * @BRIEF lee los comandos del fichero y los guarda en una tabla de comandos
 * cada uno de estos comandos compuesto por un array de palabras
 * @AUTHOR Carlos Li Hu
 * @PARAM el fichero de donde lee los comandos
 * @PARAM el número de comandos
 * @RETURN devuelve el array de comandos si ha ido bien, NULL si falla
 */
char*** leer_condiciones(FILE* f,int n_cond);

/**
 * @BRIEF pasándole un comando ejecuta las modificaciones pertinentes si se cumplen las condiciones especificadas.
 * @AUTHOR Carlos Li Hu
 * @PARAM un comandos (compuesto de palabras por separado)
 * @PARAM el número de comandos
 * @RETURN OK si ha ido bien, ERROR si falla
 */
STATUS reglas(char*** regla, int n_cond, ESPACIO ***mapa, PERS** personajes, OBJ**objetos);

/**
 * @BRIEF libera memoria de los comandos
 * @AUTHOR Carlos Li Hu
 * @PARAM el número de comandos
 * @PARAM el número de comandos
 * @RETURN devuelve el array de comandos si ha ido bien, NULL si falla
 */
STATUS free_reglas(char*** palabras,int n_cond);




#endif	/* REGLAS_H */

