
/* 
 * File:   espacio.h
 * Author: Carlos Li Hu && Javier Gómez && David López
 *
 * Created on 3 de octubre de 2015, 1:19
 */

#ifndef ESPACIO_H
#define	ESPACIO_H

#include "list.h"

typedef struct _ESPACIO ESPACIO; /*Asigna un nuevo nombre a la estructura original (primer argumento)*/

/*
 En el main habria que crear un ESPACIO*** mapa para guardar en el mapa un array de dos dimensiones
 todos los espacios del mapa de nuestro juego.
 * 
 TAD ESPACIO
 *      int coord[2]
 *      char * descr
 *      int estado
 *      list* list_obj
 *      node ** exit
 
 ESTRUCTURA NODO
 *      char* direction
 *      obj * door
 *      ESPACIO * conexion
 */




/*
 -----------------------------------------------------------------------------------------
 ------------------------------------MEMS-------------------------------------------------
 -----------------------------------------------------------------------------------------
 */



/*
 * @BRIEF reserva memoria para un ESPACIO. Tambien para la lista de objetos que tendra dentro, aunque esta este vacia
 * @PARAM nada
 * @RETURN la memoria del espacio
 */
ESPACIO* iniEspacio();

/*
 * @BRIEF libera la memoria asignada a un espacio
 * @PARAM el espacio cuya memoria va a ser liberada
 * @RETURN OK si se libero correctamente. Si no, ERROR
 */
STATUS destroyEspacio(ESPACIO* room);



/*
 --------------------------------------------------------------------------------------------
 -----------------------------------SETS-----------------------------------------------------
 --------------------------------------------------------------------------------------------
 */



/*
 * @BRIEF asigna un par de coordenadas al espacio introducido
 * @PARAM el espacio al cual asignarle las coordenadas
 * @PARAM coords[0] es la coordenada 'x' y coords[1] es la coordenada 'y'
 * @RETURN OK si lo hizo correctamente. ERROR si no
 */
STATUS room_set_coords(ESPACIO* room, int* coords);

/*
 * @BRIEF asigna una descripcion a un espacio
 * @PARAM el espacio 
 * @PARAM la descripcion a asignar
 * @RETURN devuelve OK si se asigno correctamente, ERROR si no
 */
STATUS room_set_descr(ESPACIO* room, char* descr);

/*
 * @BRIEF asigna un valor entero a modo de estado a un espacio
 * @PARAM el espacio 
 * @PARAM el valor a asignar
 * @RETURN OK si se asigno y ERROR si no
 */
STATUS room_set_estado(ESPACIO* room, int estado);

/*
 * @BRIEF inserta un objeto en la lista de objetos de un espacio
 * @PARAM el espacio 
 * @PARAM el objeto a insertar
 * @RETURN OK si lo inserto y ERROR si no
 */
STATUS room_insert_in_objlist(ESPACIO* room, OBJ* obj);

/*
 * @BRIEF extrae un objeto de la lista de objetos de un espacio
 * @PARAM el espacio de cuya lista se va a extraer el objeto 
 * @PARAM el nombre del objeto a extraer
 * @RETURN el objeto extraido
 */
OBJ* room_extract_from_objlist(ESPACIO* room, char* obj_name);

/*
 * @BRIEF comprueba que el objeto deseado esta o no en la lista de objetos de la habitacion
 * @PARAM la habitacion 
 * @PARAM el nombre del objeto a buscar
 * @RETURN OK si esta, ERROR si no esta
 */
BOOL is_obj_in_room(ESPACIO* room, char* obj_name);

/*
 * @BRIEF asigna un objeto (generalmente una puerta o un muro) a una salida de una habitacion
 * @PARAM la habitacion
 * @PARAM el numero de la salida 
 * @PARAM el objeto a asignar
 * @RETURN OK si lo hizo correctamente, ERROR si no
 */
STATUS room_set_exit_door(ESPACIO* room, unsigned int exit_num, OBJ* obj);

/*
 * @BRIEF asigna una "direccion" a una salida de una habitacion
 * @PARAM el espacio
 * @PARAM el numero de salida 
 * @PARAM la "direccion" (por ejemplo, norte o biblioteca)
 * @RETURN OK si lo hizo correctamente, ERROR si no
 */
STATUS room_set_exit_direction(ESPACIO* room, unsigned int exit_num, char* direction);

/*
 * @BRIEF asigna una conexion a otro espacio a traves de la salida escogida
 * @PARAM el espacio actual
 * @PARAM el numero de salida del espacio actual 
 * @PARAM las coordenadas del espacio conexion
 * @RETURN OK si se hizo correctamente, ERROR si no
 */
STATUS room_set_exit_connection(ESPACIO* room, unsigned int exit_num, ESPACIO* ady);



/*
 --------------------------------------------------------------------------------------------
 -------------------------------------GETS---------------------------------------------------
 --------------------------------------------------------------------------------------------
 */



/*
 * @BRIEF devuelve las "direcciones" de las salidas que el espacio tiene guardadas
 * @PARAM el espacio
 * @PARAM array para guardar esas "direcciones" (por ejemplo: norte o biblioteca)
 * @RETURN OK si lo hizo bien, ERROR si no 
 */
STATUS room_get_exit_directions(ESPACIO *room, char* output[]);

/*
 * @BRIEF devuelve el objeto "puerta" que se encuentra en la salida en la direccion indicada
 * @PARAM el espacio 
 * @PARAM la direccion
 * @RETURN el objeto en cuestion (puerta o muro en general)
 */
OBJ* room_get_exit_door(ESPACIO* room, char* direction);

/*
 * @BRIEF devuelve un puntero al espacio que esta conectado al actual por la salida en la direccion especificada
 * @PARAM el espacio 
 * @PARAM la direccion
 * @RETURN puntero al espacio conectado
 */
ESPACIO* room_get_room_connection(ESPACIO* room, char*direccion);

/*
 * @BRIEF devuelve el numero de objetos que hay en la sala
 * @PARAM la habitacion
 * @RETURN el numero de objetos que hay
 */
int n_objs_in_room(ESPACIO* room);

/*
 * @BRIEF devuelve el estado de la sala (en forma de int)
 * @PARAM la sala
 * @RETURN el estado (en forma de int)
 */
int get_room_estado(ESPACIO* room);

/*
 * @BRIEF devuelve la descripcion de la sala
 * @PARAM la sala
 * @RETURN la descripcion de esa sala
 */
char* get_room_descr(ESPACIO* room);

/*
 * @BRIEF devuelve las coordenadas de la sala
 * @PARAM la sala
 * @RETURN las coordenadas de la sala
 */
int* get_room_coord(ESPACIO* room);
/*
 * @BRIEF devuelve la lista de objetos de la sala
 * @PARAM la sala
 * @RETURN dicha lista de objetos
 */
List* get_room_list(ESPACIO* room);

/*
 --------------------------------------------------------------------------------------
 -----------------------------------OTHERS---------------------------------------------
 --------------------------------------------------------------------------------------
 */



/*
 * @BRIEF calcula la distancia entre dos salas mediante sus coordenadas
 * @PARAM tabla de enteros
 * @PARAM tabla de enteros
 * @RETURN la distancia entre ambas (pitagoras FTW)
 */
double coords_distance(int* coords1, int* coords2);

/*
 * @BRIEF calcula el camino mas corto para ir de una sala a otra y devuelve el primero de los "pasos" de este camino
 * @PARAM el espacio de origen 
 * @PARAM el espacio de destino
 * @RETURN el espacio con el que comienza el camino mas corto
 */
ESPACIO* move_to_room(ESPACIO* origen, ESPACIO* destino);

/*
 * @BRIEF calcula los espacios que hay a dist movimientos de distancia
 * @PARAM el espacio "raiz"
 * @PARAM la distancia de movimentos de las salas que buscamos
 * @RETURN uno de los espacios que se hayan a dist movimientos de distancia del espacio room
 */
ESPACIO* rooms_at_dist(ESPACIO* room, unsigned int dist);

#endif	/* ESPACIO_H */
