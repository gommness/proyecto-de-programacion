/* 
 * File:   list.c
 * Author: Carlos Li Hu 
 */

#include "list.h"

typedef struct _Node {
    OBJ* data;
    struct _Node *next;
} Node;

struct _List {
    Node *node;
};

/* DECLARACIÓN DE FUNCIONES PRIVADAS PARA TRATAMIENTO DE LOS NODOS */

/*------------------------------------------------------------------
 Nombre: iniNode
 Descripcion: Reserva memoria e inicializa un nodo
 Salida: el nodo inicializado
 ------------------------------------------------------------------*/
Node* iniNode() {
    Node *pn = NULL;
    pn = (Node *) malloc(sizeof (Node));
    if (!pn) return NULL;
    pn->data = NULL;
    pn->next = NULL;
    return pn;
}

/*------------------------------------------------------------------
 Nombre: freeNode
 Descripcion: Libera un nodo de la lista
 Entrada: la lista 
 ------------------------------------------------------------------*/
void freeNode(Node* node) {
    if (node) {
        destroy_obj(node->data); /* Libera elemento de data*/
        node->data = NULL;
        free(node); /* Libera nodo*/
        node = NULL;
    }
}


/*                    DEFINICIÓN DE FUNCIONES                      */

/*******************************************************************
 * Escribir aquí el código asociado a la definición de funciones   *
 * tanto públicas como privadas.                                   *
 *******************************************************************/

/*------------------------------------------------------------------
Nombre: iniList
Descripcion: Inicializa una lista
Entrada: la lista a inicializar
Salida: puntero a la lista creada o NULL si ha habido error
------------------------------------------------------------------*/
List* iniList() {
    List *list = NULL;
    list = (List *) malloc(sizeof (List));
    if (!list) return NULL;
    list->node = NULL;
    return list;
}

/*------------------------------------------------------------------
Nombre: insertFirstOBJ
Descripcion: inserta un elemento al principio de la lista
Entrada: un elemento y la lista donde insertarlo
Salida: puntero a la lista modificada o NULL si ha habido error
------------------------------------------------------------------*/
STATUS insertFirstOBJ(List* list, OBJ *elem) {
    Node *pn = NULL;
    if (!list || !elem) return ERROR;
    pn = iniNode();
    if (!pn) {
        return ERROR;
    }
    /*inicializamos el objeto y lo insertamos en la lista*/
    pn->data = ini_obj();
    copy_obj(pn->data, elem);
    if (!pn->data) {
        freeNode(pn);
        return ERROR;
    }
    /*reasignamos punteros*/
    pn->next = list->node;
    list->node = pn;
    return OK;
}

/*------------------------------------------------------------------
Nombre: extractFirstOBJ
Descripcion: Extrae primer elemento de la lista
Entrada: la lista de donde extraerlo
Salida: puntero a la lista creada o NULL si ha habido error
------------------------------------------------------------------*/
OBJ* extractFirstOBJ(List* list) {
    Node *pn = NULL;
    OBJ *elem;
    if (!list || isEmptyList(list) == TRUE) {
        return NULL;
    }
    pn = list->node;
    /*inicializamos el objeto y lo copiamos en el auxiliar*/
    elem = ini_obj();
    copy_obj(elem, pn->data);
    if (!elem) {
        return NULL;
    }
    /*reasignamos punteros y destruimos el objeto auxliliar*/
    list->node = pn->next;
    freeNode(pn);
    return elem;
}

/*------------------------------------------------------------------
Nombre: isEmptyList
Descripcion: Comprueba si la lista está vacía
Entrada: la lista
Salida: TRUE si la lista está vacía y FALSE en caso contrario
------------------------------------------------------------------*/
BOOL isEmptyList(const List* list) {
    if (!list) return TRUE; /* Caso de error*/
    if (!list->node) return TRUE; /* Caso de lista vacía*/
    return FALSE; /* Caso de lista no vacía*/
}

/*------------------------------------------------------------------
Nombre: sizeOfList
Descripcion: Devuelve el número de elementos de la lista
Entrada: la lista
Salida: el número de elementos de la lista
------------------------------------------------------------------*/
int sizeOfList(const List* list) {
    int aux = 0;
    Node *pn = NULL;
    if (!list) return -1;
    /*recorremos toda la lista*/
    for (pn = list->node; pn != NULL; pn = pn->next, aux++);
    return aux;

}

/*------------------------------------------------------------------
Nombre: freeList
Descripcion: Libera la lista
Entrada: la lista
Salida: puntero a la lista creada o NULL si ha habido error
------------------------------------------------------------------*/
STATUS freeList(List* list) {
    if (!list) return ERROR;
    while (isEmptyList(list) == FALSE) {
        destroy_obj(extractFirstOBJ(list));
    }
    free(list);
    list = NULL;
    return OK;
}

/*------------------------------------------------------------------
Nombre: extractOBJ
Descripcion: Extrae un objeto específico de la lista
Entrada: la lista de donde extraerlo y el nombre del objeto
Salida: puntero al objeto extraido o NULL si ha habido error
------------------------------------------------------------------*/
OBJ* extractOBJ(List* list, char*nombre) {
    OBJ * out = NULL;
    Node * aux = NULL;
    Node * preaux;
    if (!list || !nombre || isEmptyList(list))return NULL;

    /*comprueba si el objeto esta en el inventario*/
    if (!strcmp(get_obj_name(list->node->data), nombre)) {
        aux = list->node;
        list->node = list->node->next;
        out = aux->data;
        free(aux);
        return out;
    }
    /*devolvemos el objeto del inventario*/
    for (aux = list->node->next, preaux = list->node; aux != NULL; preaux = preaux->next, aux = aux->next) {
        if (!strcmp(get_obj_name(aux->data), nombre)) {
            preaux->next = aux->next;
            return aux->data;
        }
    }
    return NULL;
}
