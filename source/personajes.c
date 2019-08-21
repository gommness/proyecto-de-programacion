/* 
 * File:   personajes.c
 * Author: David Lopez
 */


#include "personajes.h"

struct _PERS {
    char* name; /*el nombre*/
    char* descr; /*la descripcion*/
    char* dial; /*el dialogo*/
    int* ubicacion; /*la ubicacion*/
    List* lista_obj; /*inventario*/

};

/*@BRIEF Inicializa un personaje
 *@PARAM Ninguno
 *@RETURN El personaje con la memoria reservada
 */
PERS* ini_pers() {
    PERS* pers = NULL;

    /*reservamos memoria para el personaje*/
    pers = (PERS*) malloc(sizeof (PERS));
    if (pers == NULL)
        return NULL;
    /*ponemos el resto de campos a NULL*/
    pers->name = NULL;
    pers->descr = NULL;
    pers->dial = NULL;
    /*reservamos la memoria exacta para la ubicacion*/
    pers->ubicacion = (int*) malloc(sizeof (int)* 2);
    pers->lista_obj = iniList();

    return pers;

}

/*@BRIEF libera la memoria del personaje
 *@PARAM El personaje a liberar
 *@RETURN OK si se ha destruido o ERROR
 */
STATUS destroy_pers(PERS* personaje) {

    if (personaje == NULL) return ERROR;
    if (personaje->descr != NULL) {
        free(personaje->descr);
        personaje->descr = NULL;
    }
    if (personaje->dial) {
        free(personaje->dial);
        personaje->dial = NULL;
    }
    if (personaje->name) {
        free(personaje->name);
        personaje->name = NULL;
    }
    if (personaje->ubicacion) {
        free(personaje->ubicacion);
        personaje->ubicacion = NULL;
    }
    if (personaje->lista_obj != NULL) {
        freeList(personaje->lista_obj);
        personaje->lista_obj = NULL;
    }

    free(personaje);
    personaje = NULL;
    return OK;

}

/*
 *@BRIEF Establece el tipo de personaje
 *@PARAM El personaje y su nombre
 *@RETURN OK si se ha setteado correctamente o ERROR
 */
STATUS set_pers_name(PERS* personaje, char* name) {
    if (personaje == NULL) return ERROR;
    /*reservamos memoria para el campo nombre del personaje*/
    personaje->name = (char*) malloc((strlen(name) + 1) * sizeof (char));
    if (personaje->name == NULL) return ERROR;
    strcpy(personaje->name, name);

    return OK;

}

/*
 *@BRIEF Establece la descripcion del personaje
 *@PARAM el personaje y la descripcion
 *@RETURN OK si se ha setteado bien o ERROR
 */
STATUS set_pers_descr(PERS* personaje, char* descr) {
    if (personaje == NULL) return ERROR;
    /*reservamos memoria para el campo descripcion del personaje*/
    personaje->descr = (char*) malloc(sizeof (char)* (strlen(descr) + 1));
    if (personaje->descr == NULL) return ERROR;
    strcpy(personaje->descr, descr);

    return OK;


}

/*
 *@BRIEF Establece el dialogo del personaje
 *@PARAM el personaje y su dialogo
 *@RETURN OK si se ha setteado bien o ERROR
 */
STATUS set_pers_dial(PERS* personaje, char* dial) {
    if (personaje == NULL) return ERROR;
    /*reservamos memoria para el campo dialogo del personaje*/
    personaje->dial = (char*) malloc(sizeof (char)* (strlen(dial) + 1));
    if (personaje->dial == NULL) return ERROR;
    strcpy(personaje->dial, dial);

    return OK;

}

/*
 *@BRIEF Establece la ubicación del personaje
 *@PARAM el personaje y su ubicacion
 *@RETURN OK si se ha setteado bien o ERROR
 */
STATUS set_pers_ubic(PERS* personaje, int* ubic) {
    if (personaje == NULL) return ERROR;
    if (personaje->ubicacion == NULL) return ERROR;
    /*asignamos la ubicacion actual al personaje*/
    personaje->ubicacion[0] = ubic[0];
    personaje->ubicacion[1] = ubic[1];

    return OK;

}

/*
 *@BRIEF Establece el objeto del personaje
 *@PARAM el personaje y su objeto
 *@RETURN OK si se ha setteado bien o ERROR
 */
STATUS set_pers_obj(PERS* personaje, OBJ* obj) {
    if (personaje == NULL) return ERROR;
    /*añade un objeto al inventario*/
    if (personaje->lista_obj == NULL) return ERROR;
    insertFirstOBJ(personaje->lista_obj, obj);

    return OK;

}

/*@BRIEF establece los campos usando las funciones individuales de set anteriores
 *@PARAM los campos del personaje, y que personaje se settea
 *@RETURN OK si se ha seteado bien, si no, ERROR
 */
STATUS set_pers(PERS* personaje, char* name, char* descr, char* dial, int* ubic, OBJ* obj) {
    /*set general de todos los campos del personaje*/
    if (set_pers_name(personaje, name) == ERROR) return ERROR;
    if (set_pers_descr(personaje, descr) == ERROR) return ERROR;
    if (set_pers_dial(personaje, dial) == ERROR) return ERROR;
    if (set_pers_ubic(personaje, ubic) == ERROR) return ERROR;
    if (set_pers_obj(personaje, obj) == ERROR) return ERROR;

    return OK;

}

/*@BRIEF nos da el nombre del personaje 
 *@PARAM el personaje
 *@RETURN el nombre
 */
char* get_pers_name(PERS* personaje) {
    if (personaje == NULL) return NULL;

    return (personaje->name);
}

/*@BRIEF nos da la descripcion del personaje
 *@PARAM el personaje
 *@RETURN la descripcion
 */
char* get_pers_descr(PERS* personaje) {
    if (personaje == NULL) return NULL;

    return (personaje->descr);

}

/*
 * @BRIEF nos da el dialogo del personaje
 * @PARAM el personaje
 * @RETURN el dialogo
 */
char* get_pers_dial(PERS* personaje) {
    if (personaje == NULL) return NULL;

    return (personaje->dial);

}

/*
 * @BRIEF nos da la ubicacion del personaje
 * @PARAM el personaje
 * @RETURN la ubicacion
 */
int* get_pers_ubic(PERS* personaje) {
    if (personaje == NULL) return NULL;

    return (personaje->ubicacion);

}

/*
 * @BRIEF nos da el objeto del personaje
 * @PARAM el personaje y el nombre del objeto
 * @RETURN el objeto
 */
OBJ* get_pers_obj(PERS* personaje, char* nombre) {
    OBJ* aux = NULL;
    if (personaje == NULL) return NULL;
    /*comprobamos que el objeto este en el inventario del personaje*/
    aux = extractOBJ(personaje->lista_obj, nombre);
    if (!aux) return NULL;
    if (insertFirstOBJ(personaje->lista_obj, aux) == ERROR) return NULL;

    return aux;

}

/*
 * @BRIEF extrae el objeto del personaje
 * @PARAM el personaje y el nombre del objeto
 * @RETURN el objeto
 */
OBJ* extract_pers_obj(PERS* personaje, char* nombre) {
    OBJ* aux = NULL;
    if (personaje == NULL) return NULL;
    /*extraemos el personaje del inventario*/
    aux = extractOBJ(personaje->lista_obj, nombre);
    if (!aux) return NULL;
    return aux;
}

/* @BRIEF comprueba que dos personajes son iguales
 * @PARAM los personajes a comparar
 * @RETURN True si son iguales False si son diferentes
 */
BOOL pers_cmp(PERS* pers1, PERS* pers2) {

    if (pers1 == NULL && pers2 == NULL) return 1;
    else if ((pers1 == NULL && pers2 != NULL) || (pers1 != NULL && pers2 == NULL)) return 0;
        /*comparamos cada campo de ambos personajes*/
    else {
        if (strcmp(pers1->name, pers2->name))
            return 0;
        if (strcmp(pers1->descr, pers2->descr))
            return 0;
        if (strcmp(pers1->dial, pers2->dial))
            return 0;
        if (pers1->ubicacion[0] != pers2->ubicacion[0] || pers1->ubicacion[1] != pers2->ubicacion[1])
            return 0;

        return 1;
    }
}

/* @BRIEF imprime un personaje
 * @PARAM el personaje
 * @RETURN nada
 */
void pers_print(PERS* personaje) {
    /*imprimios cada campo del personaje*/
    fprintf(stdout, "Nombre: %s\n", personaje->name);
    fprintf(stdout, "Descripcion: %s\n", personaje->descr);
    fprintf(stdout, "Dialogo: %s\n", personaje->dial);
    fprintf(stdout, "Ubicacion: [%d, %d]\n", personaje->ubicacion[0], personaje->ubicacion[1]);

    return;

}

/* @BRIEF devuelve la lista de objetos del personaje
 * @PARAM el personaje
 * @RETURN la lista
 */
List* get_pers_list(PERS* personaje) {
    /*si el personaje no tiene objetos en el inventario devuelve NULL*/
    if (personaje)
        return personaje->lista_obj;
    else return NULL;
}

