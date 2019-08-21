/* 
 * File:   objeto.h
 * Author: Carlos Li Hu && Javier Gómez && David López
 *
 * Created on 28 de septiembre de 2015, 11:09
 */

#ifndef OBJETO_H
#define	OBJETO_H
#include "types.h"

typedef struct _OBJ OBJ; /*Asigna un nuevo nombre a la estructura original (primer argumento)*/

/**
 * @BRIEF inicializa un objeto 
 * @PARAM NULL
 * @RETURN el objeto con la memoria reservada
 */
OBJ* ini_obj();

/**
 * @BRIEF libera la memoria del objeto
 * @PARAM el objeto a destruir
 * @RETURN OK si ha ido todo bien, ERROR en caso contrario 
 */
STATUS destroy_obj(OBJ* objeto);

/**
 * @BRIEF settea el name de un objeto
 * @PARAM el objeto a settear 
 * @PARAM el nombre
 * @RETURN OK si ha ido todo bien, ERROR en caso contrario 
 */
STATUS set_obj_name(OBJ* objeto, char* name);

/**
 * @BRIEF settea la descripcion de un objeto
 * @PARAM el objeto a settear 
 * @PARAM la descripcion
 * @RETURN OK si ha ido todo bien, ERROR en caso contrario 
 */
STATUS set_obj_descr(OBJ* objeto, char* descr);

/**
 * @BRIEF settea el dialogo de un objeto
 * @PARAM el objeto a settear 
 * @PARAM el dialogo
 * @RETURN OK si ha ido todo bien, ERROR en caso contrario 
 */
STATUS set_obj_dial(OBJ* objeto, char* dial);

/**
 * @BRIEF settea el estado "cogible" de un objeto
 * @PARAM el objeto a settear 
 * @PARAM el estado "cogible"
 * @RETURN OK si ha ido todo bien, ERROR en caso contrario 
 */
STATUS set_obj_cogible(OBJ* objeto, BOOL cogible);

/**
 * @BRIEF settea el estado "activable" de un objeto
 * @PARAM el objeto a settear 
 * @PARAM el estado "activable"
 * @RETURN OK si ha ido todo bien, ERROR en caso contrario 
 */
STATUS set_obj_activable(OBJ* objeto, BOOL activable);

/**
 * @BRIEF settea el estado "iluminador" de un objeto
 * @PARAM el objeto a settear 
 * @PARAM el estado "iluminador"
 * @RETURN OK si ha ido todo bien, ERROR en caso contrario 
 */
STATUS set_obj_ilum(OBJ* objeto, BOOL ilum);

/**
 * @BRIEF settea el estado "activado" de un objeto
 * @PARAM el objeto a settear 
 * @PARAM el estado activado
 * @RETURN OK si ha ido todo bien, ERROR en caso contrario 
 */
STATUS set_obj_activado(OBJ* objeto, BOOL activado);

/**
 * @BRIEF actualiza los campos usando las funciones individuales de set anteriores
 * @PARAM el objeteo a settear
 * @PARAM el nombre
 * @PARAM la descripcion
 * @PARAM el dialogo
 * @PARAM el estado "cogible"
 * @PARAM el estado "activable"
 * @PARAM el estado "iluminador"
 * @PARAM el estado "activado"
 * @RETURN OK si ha ido todo bien, ERROR en caso contrario 
 */
STATUS set_obj(OBJ* objeto, char*name, char* descr, char* dial, BOOL cogible, BOOL activable, BOOL ilum, BOOL activado);

/**
 * @Brief indica si el objeto puede iluminar o no
 * @Param el objeto
 * @Return True si puede iluminar, False en caso contrario
 */
BOOL get_obj_ilum(OBJ* objeto);

/**
 * @BRIEF indica si el objeto es activable o no
 * @PARAM el objeto 
 * @RETURN True si es activable, False en caso contrario
 */
BOOL get_obj_active(OBJ* objeto);

/**
 * @BRIEF indica el nombre del objeto
 * @PARAM el objeto
 * @RETURN el nombre del objeto
 */
char* get_obj_name(OBJ* objeto);

/**
 * @BRIEF indica la descripcion del objeto
 * @PARAM el objeto
 * @RETURN la descripcion del objeto
 */
char* get_obj_descr(OBJ* objeto);

/**
 * @BRIEF indica el dialogo del objeto
 * @PARAM el objeto
 * @RETURN el dialogo del objeto
 */
char* get_obj_dial(OBJ* objeto);

/**
 * @BRIEF indica si el objeto es cogible o no
 * @PARAM el objeto
 * @RETURN True si es cogible, False en caso contrario
 */
BOOL get_obj_cogible(OBJ* objeto);

/**
 * @BRIEF copia un objeto en otro (no reserva memoria)
 * @PARAM objeto destino 
 * @PARAM objeto fuente
 * @RETURN OK si ha ido todo bien, ERROR en caso contrario 
 */
STATUS copy_obj(OBJ* destino, OBJ* fuente);

/**
 * @BRIEF indica si el objeto esta activado o no
 * @PARAM el objeto 
 * @RETURN True si esta activado, False en caso contrario
 */
BOOL get_obj_activado(OBJ* obj);

/**
 * @BRIEF comprueba que dos objetos son iguales
 * @PARAM primer objeto a comparar
 * @PARAM segundo objeto a comparar
 * @RETURN True si son iguales, False en caso contrario
 */
BOOL obj_cmp(OBJ* obj1, OBJ* obj2);

#endif	/* OBJETO_H */

