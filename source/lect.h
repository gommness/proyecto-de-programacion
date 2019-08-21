/* 
 * File:   lect.h
 * Author: Javier Gomez && Carlos Li Hu && David lopez
 */

#include "objeto.h"
#include "personajes.h"
#include "espacios.h"

/**
 * @BRIEF lee del fichero los objetos personajes y espacios y los guarda en sus tablas correspondientes.
 * @PARAM fichero de lectura, arrays de objetos personajes y espacios para guardarlos
 * @RETURN ok o error si sale bien
 */
STATUS leer_fichero(FILE* file, OBJ***objeto, PERS*** personaje, ESPACIO****space, int nums[4]);

/**
 * @BRIEF abre todos los ficheros y carga los datos del juego
 * @AUTHOR Elvira Vegas Maganto
 * @PARAM fichero de lectura, arrays de objetos personajes y espacios para guardarlos
 * @RETURN ok o error si sale bien
 */
STATUS abrir_ficheros(FILE** f1, OBJ*** obj, PERS*** pers, ESPACIO**** espacio, int tabla[4], FILE** f2, FILE** f3, FILE** f4);

/**
 * @BRIEF cierra los ficheros del juego
 * @AUTHOR Elvira Vegas Maganto
 * @PARAM los ficheros
 * @RETURN ok o error si sale bien
 */
STATUS cerrar_ficheros(FILE** f1, FILE** f2, FILE** f3, FILE** f4);