/* 
 * File:   gestor.h
 * Author: Javier Gomez && David Lopez
 *
 * Created on 9 de octubre de 2015, 17:06
 */


#ifndef GESTOR_H
#define	GESTOR_H

#include "espacios.h"
#include "personajes.h"
#include "lect.h"
#include "ventana.h"

/*@BRIEF Imprime todos los campos de un objeto
 *@PARAM El objeto y un fichero destino
 *@RETURN Nada
 */
void print_objeto(FILE* fichero, OBJ* objeto);


/*@BRIEF Imprime todos los campos de un personaje
 *@PARAM El personaje y un fichero destino
 *@RETURN Nada
 */
void print_personaje(FILE* fichero, PERS* personaje);


/*@BRIEF Imprime todos los campos de un espacio
 *@PARAM el espacio y un fichero destino
 *@RETURN Nada
 */
void print_espacio(FILE* fichero, ESPACIO* espacio);

/*OBJETOS*/

/*@BRIEF Imprime el nombre de un objeto
 *@PARAM el objeto y un fichero destino
 *@RETURN Nada
 */
void print_objeto_name(FILE* fichero, OBJ* objeto);


/*@BRIEF Imprime la descripcion de un objeto
 *@PARAM el objeto y un fichero destino
 *@RETURN Nada
 */
void print_objeto_descr(FILE* fichero, OBJ* objeto);

/*@BRIEF Imprime el dialogo de un objeto
 *@PARAM el objeto y un fichero destino
 *@RETURN Nada
 */
void print_objeto_dial(FILE* fichero, OBJ* objeto);


/*@BRIEF Imprime  si un objeto es activable o no
 *@PARAM el objeto y un fichero destino
 *@RETURN Nada
 */
void print_objeto_activable(FILE* fichero, OBJ* objeto);

/*@BRIEF Imprime  si un objeto es cogible o no
 *@PARAM el objeto y un fichero destino
 *@RETURN Nada
 */
void print_objeto_cogible(FILE* fichero, OBJ* objeto);


/*@BRIEF Imprime  si un objeto puede iluminar o no
 *@PARAM el objeto y un fichero destino
 *@RETURN Nada
 */
void print_objeto_iluminador(FILE* fichero, OBJ* objeto);


/*@BRIEF Imprime  si un objeto esta activado o no
 *@PARAM el objeto y un fichero destino
 *@RETURN Nada
 */
void print_objeto_activado(FILE* fichero, OBJ* objeto);

/*@BRIEF Imprime el estado de un objeto
 *@PARAM el objeto y un fichero destino
 *@RETURN Nada
 */
void print_objeto_estado(FILE* fichero, OBJ* objeto);

/*PERSONAJES*/

/*@BRIEF Imprime el nombre de un personaje
 *@PARAM el personaje y un fichero destino
 *@RETURN Nada
 */
void print_personaje_nombre(FILE* fichero, PERS* personaje);


/*@BRIEF Imprime la descripcion de un personaje
 *@PARAM el personaje y un fichero destino
 *@RETURN Nada
 */
void print_personaje_descr(FILE* fichero, PERS* personaje);


/*@BRIEF Imprime el dialogo de un personaje
 *@PARAM el personaje y un fichero destino
 *@RETURN Nada
 */
void print_personaje_dial(FILE* fichero, PERS* personaje);


/*@BRIEF Imprime la ubicacion de un personaje
 *@PARAM el personaje y un fichero destino
 *@RETURN Nada
 */
void print_personaje_ubic(FILE* fichero, PERS* personaje);


/*@BRIEF Imprime los objetos de un personaje
 *@PARAM el personaje y un fichero destino
 *@RETURN Nada
 */
void print_personaje_obj(FILE* fichero, PERS* personaje);


/*ESPACIOS*/


/*@BRIEF Imprime las coordenadas de un espacio
 *@PARAM el espacio y un fichero destino
 *@RETURN Nada
 */
void print_espacio_coord(FILE* fichero, ESPACIO* espacio);


/*@BRIEF Imprime la descripcion de un espacio
 *@PARAM el espacio y un fichero destino
 *@RETURN Nada
 */
void print_espacio_desc(FILE* fichero, ESPACIO* espacio);


/*@BRIEF Imprime el estado de un espacio
 *@PARAM el espacio y un fichero destino
 *@RETURN Nada
 */
void print_espacio_estado(FILE* fichero, ESPACIO* espacio);


/*@BRIEF Imprime los objetos de un espacio
 *@PARAM el espacio y un fichero destino
 *@RETURN Nada
 */
void print_espacio_obj(FILE* fichero, ESPACIO* espacio);


/*@BRIEF Imprime las salidas de un espacio
 *@PARAM el espacio y un fichero destino
 *@RETURN Nada
 */
void print_espacio_exit(FILE* fichero, ESPACIO* espacio);

/*@BRIEF Imprime los nombres de los personajes que haya en un espacio
 *@PARAM el espacio, un fichero destino y la tabla con todos los personajes
 *@RETURN Nada
 */
void print_pers_en_espacio(FILE* fichero, ESPACIO* espacio, PERS**personajes, int num_pers);

/**
 * @BRIEF Imprime la bienvenida del juego
 * @AUTHOR Elvira Vegas Maganto
 * @PARAM la ventana donde se imprime 
 * @RETURN OK si todo ha ido bien, ERROR sino.
 */
STATUS print_sala_inicial(PERS** pers, Ventana** v1, ESPACIO*** mapa);

/**
 * @BRIEF Imprime el fin del juego
 * @AUTHOR Elvira Vegas Maganto
 * @PARAM la ventana donde se imprime
 * @RETURN OK si todo ha ido bien, ERROR sino.
 */
STATUS print_final_juego(PERS** pers, ESPACIO*** espacio, Ventana** window);


#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* GESTOR_H */

