/* 
 * File:   personajes.h
 * Author: David Lopez && Javier Gomez && Carlos Li Hu
 */


#ifndef PERSONAJES_H
#define	PERSONAJES_H
#include "list.h"

typedef struct _PERS PERS;


/* @BRIEF Inicializa un personaje
 * @PARAM Ninguno
 * @RETURN El personaje con la memoria reservada
 */
PERS* ini_pers();


/* @BRIEF libera la memoria del personaje
 * @PARAM El personaje a liberar
 * @RETURN OK si se ha destruido o ERROR
 */
STATUS destroy_pers(PERS* personaje);

/* @BRIEF Establece el tipo de personaje
 * @PARAM El personaje y su nombre
 * @RETURN OK si se ha setteado correctamente o ERROR
 */
STATUS set_pers_name(PERS* personaje, char* name);

/*
 * @BRIEF Establece la descripcion del personaje
 * @PARAM el personaje y la descripcion
 * @RETURN OK si se ha setteado bien o ERROR
 */
STATUS set_pers_descr(PERS* personaje, char* descr);

/*
 * @BRIEF Establece el dialogo del personaje
 * @PARAM el personaje y su dialogo
 * @RETURN OK si se ha setteado bien o ERROR
 */
STATUS set_pers_dial(PERS* personaje, char* dial);

/*
 * @BRIEF Establece la ubicación del personaje
 * @PARAM el personaje y su ubicacion
 * @RETURN OK si se ha setteado bien o ERROR
 */
STATUS set_pers_ubic(PERS* personaje, int* ubic);

/*
 * @BRIEF Establece el objeto del personaje
 * @PARAM el personaje y su objeto
 * @RETURN OK si se ha setteado bien o ERROR
 */
STATUS set_pers_obj(PERS* personaje, OBJ* obj);

/* @BRIEF establece los campos usando las funciones individuales de set anteriores
 * @PARAM los campos del personaje, y que personaje se settea
 * @RETURN OK si se ha seteado bien, si no, ERROR
 */
STATUS set_pers(PERS* personaje, char* name, char* descr, char* dial, int* ubic, OBJ* obj);

/* @BRIEF nos da el nombre del personaje 
 * @PARAM el personaje
 * @RETURN el nombre
 */
char* get_pers_name(PERS* personaje);

/* @BRIEF nos da la descripcion del personaje
 * @PARAM el personaje
 * @RETURN la descripcion
 */
char* get_pers_descr(PERS* personaje);

/*
 * @BRIEF nos da el dialogo del personaje
 * @PARAM el personaje
 * @RETURN el dialogo
 */
char* get_pers_dial(PERS* personaje);


/*
 * @BRIEF nos da la ubicacion del personaje
 * @PARAM el personaje
 * @RETURN la ubicacion
 */
int* get_pers_ubic(PERS* personaje);


/*
 * @BRIEF nos da el objeto del personaje
 * @PARAM el personaje y el nombre del objeto
 * @RETURN el objeto
 */
OBJ* get_pers_obj(PERS* personaje, char* nombre);

/* @BRIEF comprueba que dos personajes son iguales
 * @PARAM los personajes a comparar
 * @RETURN True si son iguales False si son diferentes
 */
BOOL pers_cmp(PERS* personaje1, PERS* personaje2);

/*
 * @BRIEF extrae el objeto del personaje
 * @PARAM el personaje y el nombre del objeto
 * @RETURN el objeto
 */
OBJ* extract_pers_obj(PERS* personaje, char* nombre);

/* @BRIEF imprime un personaje
 * @PARAM el personaje
 * @RETURN nada
 */
void pers_print(PERS* personaje);

/* @BRIEF devuelve la lista de objetos del personaje
 * @PARAM el personaje
 * @RETURN la lista
 */
List* get_pers_list(PERS* personaje);


#ifdef	__cplusplus

#endif

#endif	/* PERSONAJES_H */
