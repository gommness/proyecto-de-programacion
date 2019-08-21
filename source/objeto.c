/* 
 * File:   objeto.h
 * Author: Carlos Li Hu 
 *
 * Created on 30 de septiembre de 2015, 13:05
 */

#include "objeto.h"

struct _OBJ {
    char* name; /*nombre*/
    char* descr; /*descripcion*/
    char* dial; /*dialogo*/
    BOOL cogible; /*1 si es cogible, 0 si no*/
    BOOL activable; /*1 si es activable, 0 si no*/
    BOOL ilum; /*1 si puede iluminar, 0 si no*/
    BOOL activado; /*1 si esta activado, 0 si no*/
};

/**
 * @BRIEF inicializa un objeto 
 * @PARAM NULL
 * @RETURN el objeto con la memoria reservada
 */
OBJ* ini_obj() {
    OBJ* obj;

    /*reservamos memoria para el objeto*/
    obj = (OBJ*) malloc(sizeof (OBJ));
    if (obj == NULL)
        return NULL;
    /*hacemos que los punteros apunten a NULL*/
    obj->name = NULL;
    obj->dial = NULL;
    obj->descr = NULL;

    return obj;

}

/**
 * @BRIEF libera la memoria del objeto
 * @PARAM el objeto a destruir
 * @RETURN OK si ha ido todo bien, ERROR en caso contrario 
 */
STATUS destroy_obj(OBJ* objeto) {
    if (objeto == NULL) return ERROR;

    /*libera el puntero de la descripcion*/
    if (objeto->descr != NULL) {
        free(objeto->descr);
        objeto->descr = NULL;
    }
    /*libera el puntero del dialogo*/
    if (objeto->dial != NULL) {
        free(objeto->dial);
        objeto->dial = NULL;
    }
    /*libera el puntero del nombre*/
    if (objeto->name != NULL) {
        free(objeto->name);
        objeto->name = NULL;
    }
    /*libera el objeto*/
    free(objeto);
    objeto = NULL;
    return OK;
}

/**
 * @BRIEF settea el name de un objeto
 * @PARAM el objeto a settear 
 * @PARAM el nombre
 * @RETURN OK si ha ido todo bien, ERROR en caso contrario 
 */
STATUS set_obj_name(OBJ* objeto, char* name) {

    if (objeto == NULL) return ERROR;

    /*reservamos memoria para el nombre de nuestro objeto*/
    objeto->name = (char*) malloc((strlen(name) + 1) * sizeof (char));
    if (objeto->name == NULL) return ERROR;
    /*copiamos el nombre pasado como argumento a nuestro objeto*/
    strcpy(objeto->name, name);

    return OK;
}

/**
 * @BRIEF settea la descripcion de un objeto
 * @PARAM el objeto a settear 
 * @PARAM la descripcion
 * @RETURN OK si ha ido todo bien, ERROR en caso contrario 
 */
STATUS set_obj_descr(OBJ* objeto, char*descr) {

    if (objeto == NULL) return ERROR;

    /*reservamos memoria para la descripcion de nuestro objeto*/
    objeto->descr = (char*) malloc(sizeof (char)* (strlen(descr) + 1));
    if (objeto->descr == NULL) return ERROR;
    /*copiamos la descripcion pasada como argumento a nuestro objeto*/
    strcpy(objeto->descr, descr);

    return OK;
}

/**
 * @BRIEF settea el dialogo de un objeto
 * @PARAM el objeto a settear 
 * @PARAM el dialogo
 * @RETURN OK si ha ido todo bien, ERROR en caso contrario 
 */
STATUS set_obj_dial(OBJ* objeto, char*dial) {

    if (objeto == NULL) return ERROR;

    /*reservamos memoria para eldialogo de nuestro objeto*/
    objeto->dial = (char*) malloc(sizeof (char)* (strlen(dial) + 1));
    if (objeto->dial == NULL) return ERROR;
    /*copiamos el dialogo pasado como argumento a nuestro objeto*/
    strcpy(objeto->dial, dial);

    return OK;
}

/**
 * @BRIEF settea el estado "cogible" de un objeto
 * @PARAM el objeto a settear 
 * @PARAM el estado "cogible"
 * @RETURN OK si ha ido todo bien, ERROR en caso contrario 
 */
STATUS set_obj_cogible(OBJ* objeto, BOOL cogible) {

    if (objeto == NULL) return ERROR;

    /*asignamos si es "cogible" o no el objeto*/
    objeto->cogible = cogible;

    return OK;
}

/**
 * @BRIEF settea el estado "activable" de un objeto
 * @PARAM el objeto a settear 
 * @PARAM el estado "activable"
 * @RETURN OK si ha ido todo bien, ERROR en caso contrario 
 */
STATUS set_obj_activable(OBJ* objeto, BOOL activable) {

    if (objeto == NULL) return ERROR;

    /*asignamos si es "activable" o no el objeto*/
    objeto->activable = activable;

    return OK;
}

/**
 * @BRIEF settea el estado "iluminador" de un objeto
 * @PARAM el objeto a settear 
 * @PARAM el estado "iluminador"
 * @RETURN OK si ha ido todo bien, ERROR en caso contrario 
 */
STATUS set_obj_ilum(OBJ* objeto, BOOL ilum) {
    if (objeto == NULL) return ERROR;

    /*asignamos si puede iluminar o no el objeto*/
    objeto->ilum = ilum;

    return OK;
}

/**
 * @BRIEF settea el estado "activado" de un objeto
 * @PARAM el objeto a settear 
 * @PARAM el estado activado
 * @RETURN OK si ha ido todo bien, ERROR en caso contrario 
 */
STATUS set_obj_activado(OBJ* objeto, BOOL activado) {

    if (objeto == NULL || objeto->activable == FALSE) return ERROR;

    /*asignamos si esta activado o no el objeto*/
    objeto->activado = activado;

    return OK;
}

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
STATUS set_obj(OBJ* objeto, char*name, char* descr, char* dial, BOOL cogible, BOOL activable, BOOL ilum, BOOL activado) {

    /*comprobamos que todos los set individuales se realizan correctamente*/
    if (set_obj_name(objeto, name) == ERROR)return ERROR;
    if (set_obj_descr(objeto, descr) == ERROR)return ERROR;
    if (set_obj_dial(objeto, dial) == ERROR)return ERROR;
    if (set_obj_cogible(objeto, cogible) == ERROR)return ERROR;
    if (set_obj_activable(objeto, activable) == ERROR)return ERROR;
    if (set_obj_ilum(objeto, ilum) == ERROR)return ERROR;
    if (set_obj_activado(objeto, activado) == ERROR)return ERROR;

    return OK;
}

/**
 * @Brief indica si el objeto puede iluminar o no
 * @Param el objeto
 * @Return True si puede iluminar, False en caso contrario
 */
BOOL get_obj_ilum(OBJ* objeto) {

    if (objeto == NULL) return FALSE;

    return (objeto->ilum);


}

/**
 * @BRIEF indica si el objeto es activable o no
 * @PARAM el objeto 
 * @RETURN True si es activable, False en caso contrario
 */
BOOL get_obj_active(OBJ* objeto) {

    if (objeto == NULL) return FALSE;

    return (objeto->activable);

}

/**
 * @BRIEF indica el nombre del objeto
 * @PARAM el objeto
 * @RETURN el nombre del objeto
 */
char* get_obj_name(OBJ* objeto) {

    if (objeto == NULL) return NULL;

    return (objeto->name);

}

/**
 * @BRIEF indica la descripcion del objeto
 * @PARAM el objeto
 * @RETURN la descripcion del objeto
 */
char* get_obj_descr(OBJ* objeto) {

    if (objeto == NULL) return NULL;

    return (objeto->descr);
}

/**
 * @BRIEF indica el dialogo del objeto
 * @PARAM el objeto
 * @RETURN el dialogo del objeto
 */
char* get_obj_dial(OBJ* objeto) {

    if (objeto == NULL) return NULL;

    return (objeto->dial);
}

/**
 * @BRIEF indica si el objeto es cogible o no
 * @PARAM el objeto
 * @RETURN True si es cogible, False en caso contrario
 */
BOOL get_obj_cogible(OBJ* objeto) {

    if (objeto == NULL) return FALSE;

    return (objeto->cogible);
}

/**
 * @BRIEF copia un objeto en otro (no reserva memoria)
 * @PARAM objeto destino 
 * @PARAM objeto fuente
 * @RETURN OK si ha ido todo bien, ERROR en caso contrario 
 */
STATUS copy_obj(OBJ* destino, OBJ* fuente) {

    if (fuente == NULL || destino == NULL) return ERROR;

    /*comprobamos que la copia se ha realizado correctamente*/
    if (set_obj(destino, fuente->name, fuente->descr,
            fuente->dial, fuente->cogible, fuente->activable,
            fuente->ilum, fuente->activado) == ERROR) return ERROR;

    return OK;
}

/**
 * @BRIEF indica si el objeto esta activado o no
 * @PARAM el objeto 
 * @RETURN True si esta activado, False en caso contrario
 */
BOOL get_obj_activado(OBJ* obj) {

    if (obj == NULL) return FALSE;

    return (obj->activado);
}

/**
 * @BRIEF comprueba que dos objetos son iguales
 * @PARAM primer objeto a comparar
 * @PARAM segundo objeto a comparar
 * @RETURN True si son iguales, False en caso contrario
 */
BOOL obj_cmp(OBJ* obj1, OBJ* obj2) {

    if (obj1 == NULL && obj2 == NULL)return 1;

    else if ((obj1 == NULL && obj2 != NULL) || (obj1 != NULL && obj2 == NULL)) return 0;

        /*comprobamos campo a campo que los objetos son iguales*/
    else {
        if (strcmp(obj1->name, obj2->name))
            return 0;
        if (strcmp(obj1->descr, obj2->descr))
            return 0;
        if (strcmp(obj1->dial, obj2->dial))
            return 0;
        if (obj1->activable != obj2->activable)
            return 0;
        if (obj1->activado != obj2->activado)
            return 0;
        if (obj1->cogible != obj2->cogible)
            return 0;
        if (obj1->ilum != obj2->ilum)
            return 0;
        return 1;
    }
}
