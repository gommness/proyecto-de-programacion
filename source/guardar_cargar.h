/* 
 * File:   guardar_cargar.h
 * Author: Carlos Li Hu
 *
 * Created on 21 de noviembre de 2015, 13:26
 */

#ifndef GUARDAR_CARGAR_H
#define	GUARDAR_CARGAR_H
#include "acciones.h"

/**
 * @BRIEF guarda la partida escribiendo en un fichero el estado actual de la partida.
 * @PARAM los objetos a guardar
 * @PARAM los personajes a guardar
 * @PARAM el estado del mapa
 * @PARAM el número de objetos 0, el numero de personajes 1, el numero de espacios: filas 2; columnas 3
 * @PARAM el fichero donde escribimos
 * @RETURN OK si ha ido bien, ERROR si falla
 */
STATUS guardar(OBJ**objeto, PERS** personaje, ESPACIO***mapa, int nums[4], FILE* f);
/**
 * @BRIEF  carga los datos de una partida leyéndolos de un fichero.
 * @PARAM los objetos a cargar
 * @PARAM los personajes a cargar
 * @PARAM el mapa donde cargarlo
 * @PARAM el número de objetos 0, el numero de personajes 1, el numero de espacios: filas 2; columnas 3
 * @PARAM el fichero de donde leemos.
 * @RETURN OK si ha ido bien, ERROR si falla
 */
STATUS cargar(OBJ***objeto, PERS*** personaje, ESPACIO****mapa, int nums[4], FILE* f);


#endif	/* GUARDAR_CARGAR_H */

