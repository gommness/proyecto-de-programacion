/* 
 * File:   list.h
 * Author: Carlos Li Hu 
 */

#ifndef LIST_H
#define	LIST_H

#include "objeto.h"

typedef struct _List List;

/* FUNCIONES PÚBLICAS DECLARADAS EN list.h Y DEFINIDAS EN list.c  */

/*------------------------------------------------------------------
Nombre: iniList
Descripcion: Inicializa una lista
Entrada:
Salida: puntero a la lista creada o NULL si ha habido error
------------------------------------------------------------------*/
List* iniList();

/*------------------------------------------------------------------
Nombre: insertFirstOBJ
Descripcion: inserta un objeto al principio de la lista
Entrada: un objeto y la lista donde insertarlo
Salida: OK o ERROR si ha habido error
------------------------------------------------------------------*/
STATUS insertFirstOBJ(List* list, OBJ *objeto);


/*------------------------------------------------------------------
Nombre: extractOBJ
Descripcion: Extrae un objeto específico de la lista
Entrada: la lista de donde extraerlo y el nombre del objeto
Salida: puntero al objeto extraido o NULL si ha habido error
------------------------------------------------------------------*/
OBJ* extractOBJ(List* list, char*nombre);

/*------------------------------------------------------------------
Nombre: isEmptyList
Descripcion: Comprueba si la lista está vacía
Entrada: la lista
Salida: TRUE si la lista está vacía y FALSE en caso contrario
------------------------------------------------------------------*/
BOOL isEmptyList(const List* list);

/*------------------------------------------------------------------
Nombre: sizeOfList
Descripcion: Devuelve el número de objetos de la lista
Entrada: la lista
Salida: el número de objetos de la lista
------------------------------------------------------------------*/
int sizeOfList(const List* list);


/*------------------------------------------------------------------
Nombre: freeList
Descripcion: Libera la lista
Entrada: la lista
Salida: OK o ERROR si ha habido error
------------------------------------------------------------------*/
STATUS freeList(List* list);

OBJ* extractFirstOBJ(List* list);

#endif
