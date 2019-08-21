/* 
 * File:   types.h
 * Author: e321112
 *
 * Created on 28 de septiembre de 2015, 11:19
 */

#ifndef _TYPES_H
#define _TYPES_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <memory.h>  

#define MAX 20

/* Constantes y tipos de retorno de funciones */
typedef enum {
    FALSE = 0, TRUE = 1
} BOOL;

typedef enum {
    ERROR = -1, OK = 0, MAS_MENOS= 1
} STATUS;

/*typedef enum {
		mov = 1, cog, dej, enc, apa, abr, hablar_obj, hablar_pers, exao, exap, exae, dor, des, inv, sal}Menu_inicial;
*/
#endif
