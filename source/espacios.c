/* 
 * File:   espacio.c
 * Author: Javier Gómez
 *
 * Created on 3 de octubre de 2015, 10:27
 */

#include "espacios.h"

typedef struct _node {
    char* direction; /*direccion de una de las salidas del espacio*/
    OBJ* door; /*objeto con el que se puede abrir esa direccion*/
    ESPACIO * conexion; /*conexion de la salida*/
} node;

struct _ESPACIO {
    int coord[2]; /*las coordenadas del espacio*/
    char* descr; /*la descripcion del espacio*/
    int estado; /*el estado del espacio*/
    List* list_obj; /*lista de los objetos que tiene el espacio*/
    node * exit[4]; /*las cuatro posibles salidas que tiene el espacio*/
};

/*estructuras auxiliares*/
typedef struct _LISTNODE {
    struct _LISTNODE * padre;
    struct _LISTNODE * hijo;
    ESPACIO* room;
} LISTNODE;

typedef struct _AUXLIST {
    LISTNODE* first;
} AUXLIST;

typedef struct _NODEAB {
    struct _NODEAB * father;
    struct _NODEAB * son[3];
    ESPACIO* info;
} NODEAB;

typedef struct _ARBOL {
    NODEAB* root;
} ARBOL;

/*
 estado = 0     =>      oscudirad
 estado = 1     =>      luz
 estado = 2     =>      lluvia
 */

/*
 * @BRIEF crea un nodo de "salidas" y reserva memoria para el
 * @PARAM nada
 * @RETURN el nodo inicializado
 */
node * createNode() {

    node* aux;
    /*reserva memoria para un nodo*/
    aux = (node*) malloc(sizeof (node));
    if (!aux)return NULL;
    /*pone el resto de punteros a NULL sin reservar memoria para ellos*/
    aux->conexion = NULL;
    aux->direction = NULL;
    aux->door = NULL;
    return aux;
}

/*
 * @BRIEF destruye un nodo "salida" 
 * @PARAM el nodo a destruir
 * @RETURN nada
 */
void destroyNode(node* nodo) {

    if (!nodo)return;
    /*destruimos el campo objeto del nodo*/
    destroy_obj(nodo->door);
    nodo->door = NULL;
    /*liberamos la memoria del campo direccion*/
    free(nodo->direction);
    nodo->direction = NULL;
    free(nodo);
    nodo = NULL;
}

/*
 * @BRIEF reserva memoria para un ESPACIO. Tambien para la lista de objetos que tendra dentro, aunque esta este vacia
 * @PARAM nada
 * @RETURN la memoria del espacio
 */
ESPACIO* iniEspacio() {

    ESPACIO * room = NULL;
    int i;
    /*reserva memoria para el espacio*/
    room = (ESPACIO*) malloc(sizeof (ESPACIO));
    if (!room)return NULL;
    /*pone el resto de punteros a NULL*/
    for (i = 0; i < 4; i++)
        room->exit[i] = NULL;
    room->descr = NULL;
    /*inicializa la lista de objetos*/
    room->list_obj = iniList();
    return room;
}

/*
 * @BRIEF libera la memoria asignada a un espacio
 * @PARAM el espacio cuya memoria va a ser liberada
 * @RETURN OK si se libero correctamente. Si no, ERROR
 */
STATUS destroyEspacio(ESPACIO* room) {

    int i;
    if (!room)return OK;
    /*liberamos los nodos de las salidas del espacio*/
    for (i = 0; i < 4; i++) {
        if (room->exit[i] != NULL) {
            destroyNode(room->exit[i]);
            room->exit[i] = NULL;
        }
    }
    /*liberamos la lista de objetos*/
    if (room->list_obj != NULL) {
        freeList(room->list_obj);
        room->list_obj = NULL;
    }
    /*liberamos la memoria de la descripcion del espacio*/
    if (room->descr != NULL) {
        free(room->descr);
        room->descr = NULL;
    }
    free(room);
    room = NULL;
    return OK;
}



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
STATUS room_set_coords(ESPACIO* room, int* coords) {

    if (!coords || !room) return ERROR;
    if ((sizeof (coords) / sizeof (*coords)) != 2) return ERROR;
    /*asignamos a nuestro espacio las coordenadas que nos pasan como argumento*/
    room->coord[0] = coords[0];
    room->coord[1] = coords[1];
    return OK;
}

/*
 * @BRIEF asigna una descripcion a un espacio
 * @PARAM el espacio 
 * @PARAM la descripcion a asignar
 * @RETURN devuelve OK si se asigno correctamente, ERROR si no
 */
STATUS room_set_descr(ESPACIO* room, char* descr) {

    if (!room || !descr)return ERROR;
    if (room->descr != NULL)
        free(room->descr);
    /*reservamos memoria para la descripcion de nuestro espacio*/
    room->descr = (char*) malloc((strlen(descr) + 1) * sizeof (char));
    if (!room->descr)return ERROR;
    /*copiamos en la descripcion de nuestro espacio la que nos pasan por argumento*/
    strcpy(room->descr, descr);
    return OK;
}

/*
 * @BRIEF asigna un valor entero a modo de estado a un espacio
 * @PARAM el espacio 
 * @PARAM el valor a asignar
 * @RETURN OK si se asigno y ERROR si no
 */
STATUS room_set_estado(ESPACIO* room, int estado) {

    if (!room || estado < 0 || estado > 2)return ERROR;
    /*asignamos al estado de nuestro espacio el estado que nos pasan por argumento*/
    room->estado = estado;
    return OK;
}

/*
 * @BRIEF inserta un objeto en la lista de objetos de un espacio
 * @PARAM el espacio 
 * @PARAM el objeto a insertar
 * @RETURN OK si lo inserto y ERROR si no
 */
STATUS room_insert_in_objlist(ESPACIO* room, OBJ* obj) {

    if (!room || !obj)return ERROR;
    /*insertamos el objeto pasado como argumento en la lista de objetos de nuestro espacio*/
    return insertFirstOBJ(room->list_obj, obj);
}

/*
 * @BRIEF extrae un objeto de la lista de objetos de un espacio
 * @PARAM el espacio de cuya lista se va a extraer el objeto 
 * @PARAM el nombre del objeto a extraer
 * @RETURN el objeto extraido
 */
OBJ* room_extract_from_objlist(ESPACIO* room, char* obj_name) {

    if (!room || !obj_name)return NULL;
    /*extrae el objeto pasado como argumento de la lista de objetos de nuestro espacio*/
    return extractOBJ(room->list_obj, obj_name);
}

/*
 * @BRIEF comprueba que el objeto deseado esta o no en la lista de objetos de la habitacion
 * @PARAM la habitacion 
 * @PARAM el nombre del objeto a buscar
 * @RETURN OK si esta, ERROR si no esta
 */
BOOL is_obj_in_room(ESPACIO* room, char* obj_name) {

    OBJ* aux;
    if (!room || !obj_name)return FALSE;
    /*guardamos en el objeto auxiliar el objeto que nos pasan como argumento que ha sido extraido de la lista de objetos del espacio*/
    aux = extractOBJ(room->list_obj, obj_name);
    /*comprobamos si el objeto esta en nuestro espacio*/
    if (!aux)return FALSE;
    /*volvemos a insertar el objeto en la lista de objetos del espacio, en caso afirmativo*/
    insertFirstOBJ(room->list_obj, aux);
    /*liberamos el objeto auxiliar porque no lo necesitamos mas*/
    destroy_obj(aux);
    return TRUE;
}

/*
 * @BRIEF asigna un objeto (generalmente una puerta o un muro) a una salida de una habitacion
 * @PARAM la habitacion
 * @PARAM el numero de la salida 
 * @PARAM el objeto a asignar
 * @RETURN OK si lo hizo correctamente, ERROR si no
 */
STATUS room_set_exit_door(ESPACIO* room, unsigned int exit_num, OBJ* obj) {

    if (!room || !obj || exit_num < 0 || exit_num > 3)return ERROR;
    /*comprobamos si existe el numero de salida en nuestro espacio, en caso negativo inicializamos ese nodo*/
    if (room->exit[exit_num] == NULL)
        room->exit[exit_num] = createNode();
    /*inicializamos el objeto de esa salida*/
    room->exit[exit_num]->door = ini_obj();
    /*copiamos el objeto pasado como argumento en nuestro esapcio*/
    copy_obj(room->exit[exit_num]->door, obj);
    return OK;
}

/*
 * @BRIEF asigna una "direccion" a una salida de una habitacion
 * @PARAM el espacio
 * @PARAM el numero de salida 
 * @PARAM la "direccion" (por ejemplo, norte o biblioteca)
 * @RETURN OK si lo hizo correctamente, ERROR si no
 */
STATUS room_set_exit_direction(ESPACIO* room, unsigned int exit_num, char* direction) {

    if (!room || !direction || exit_num < 0 || exit_num > 3) return ERROR;
    /*comprobamos si existe el numero de salida en nuestro espacio, en caso negativo inicializamos ese nodo*/
    if (room->exit[exit_num] == NULL)
        room->exit[exit_num] = createNode();
    /*reservamos memoria para esa direccion*/
    room->exit[exit_num]->direction = (char*) malloc(sizeof (char)*(strlen(direction) + 1));
    /*copiamos la direccion pasada como argumento en nuestro esapcio*/
    strcpy(room->exit[exit_num]->direction, direction);
    return OK;
}

/*
 * @BRIEF asigna una conexion a otro espacio a traves de la salida escogida
 * @PARAM el espacio actual
 * @PARAM el numero de salida del espacio actual 
 * @PARAM las coordenadas del espacio conexion
 * @RETURN OK si se hizo correctamente, ERROR si no
 */
STATUS room_set_exit_connection(ESPACIO* room, unsigned int exit_num, ESPACIO* ady) {

    if (!room || !ady || exit_num < 0 || exit_num > 3) return ERROR;
    /*asigmanos la conexion pasada como argumento a nuestro espacio*/
    room->exit[exit_num]->conexion = ady;
    return OK;
}



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
STATUS room_get_exit_directions(ESPACIO* room, char* output[4]) {
    int i;
    char* aux;

    /*obtenemos las direcciones del espacio*/
    for (i = 0; i < 4; i++) {
        if (room->exit[i] != NULL) {
            aux = (char*) malloc(sizeof (char)*(strlen(room->exit[i]->direction) + 1));
            strcpy(aux, room->exit[i]->direction);
            output[i] = aux;
        } else {
            output[i] = NULL;
        }
    }
    return OK;
}

/*
 * @BRIEF devuelve el objeto "puerta" que se encuentra en la salida en la direccion indicada
 * @PARAM el espacio y la direccion
 * @RETURN devuelve el objeto en cuestion (puerta o muro en general)
 */
OBJ* room_get_exit_door(ESPACIO* room, char* direction) {
    int i;
    if (!room || !direction)return NULL;
    
    /*obtenemos la puerta en la direccion pasada como argumento*/
    for (i = 0; i < 4; i++) {
        if (room->exit[i] != NULL)
            if (!strcmp(direction, room->exit[i]->direction))
                return room->exit[i]->door;
    }
    return NULL;
}

/*
 * @BRIEF devuelve un puntero al espacio que esta conectado al actual por la salida en la direccion especificada
 * @PARAM el espacio y la direccion
 * @RETURN puntero al espacio conectado
 */
ESPACIO* room_get_room_connection(ESPACIO* room, char*direccion) {
    int i;
    if (!room || !direccion)return NULL;

    /*obtenemos el espacio conectado a la direccion pasada como argumento*/
    for (i = 0; i < 4; i++) {
        if (room->exit[i] != NULL)
            if (!strcmp(direccion, room->exit[i]->direction))return room->exit[i]->conexion;
    }
    return NULL;
}

/*
 * @BRIEF devuelve el numero de objetos que hay en la sala
 * @PARAM la habitacion
 * @RETURN el numero de objetos que hay
 */
int n_objs_in_room(ESPACIO* room) {
    if (!room)return -1;
    /*obtenemos el numero de objetos*/
    return (sizeOfList(room->list_obj));
}

/*
 * @BRIEF devuelve el estado de la sala (en forma de int)
 * @PARAM la sala
 * @RETURN el estado (en forma de int)
 */
int get_room_estado(ESPACIO* room) {
    if (!room)return -1;
    /*estado del espacio*/
    return room->estado;
}

/*
 * @BRIEF devuelve la descripcion de la sala
 * @PARAM la sala
 * @RETURN la descripcion de esta sala
 */
char* get_room_descr(ESPACIO* room) {
    if (!room)return NULL;
    /*descripcion del espacio*/
    return room->descr;
}

/*
 * @BRIEF devuelve las coordenadas de la sala
 * @PARAM la sala
 * @RETURN las coordenadas de la sala
 */
int* get_room_coord(ESPACIO* room) {
    if (!room)return NULL;
    /*coordenadas del espacio*/
    return room->coord;
}



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
double coords_distance(int* coords1, int* coords2) {
    int out, aux;
    if (!coords1 || !coords2)return -1;
    out = coords1[0] - coords2[0];
    /*multiplicamos por -1 para tener siempre distancias positivas*/
    if (out < 0)out *= -1;
    aux = coords1[1] - coords2[1];
    if (aux < 0)aux *= -1;
    out += aux;
    return out;
}


/*funciones hechas exclusivamente para poder realizar una busqueda en anchura de las salas*/
/*________________________________________________________________________________________*/

/*_______________W E L C O M E   T O   H E L L   M O T H E R F U C K E R__________________*/

/*________________________________________________________________________________________*/

/*
 * @BRIEF inicializa una lista doblemente enlazada de ESPACIOS
 * @PARAM nada
 * @RETURN memoria para la lista Y TODOS SUS CAMPOS A NULL
 */
AUXLIST* INILIST() {
    AUXLIST* aux;
    aux = (AUXLIST*) malloc(sizeof (AUXLIST));
    if (!aux)return NULL;
    aux->first = NULL;
    return aux;
}

/*
 * @BRIEF inicializa un nodo de la lista de espacios
 * @PARAM nada
 * @RETURN memoria para el nodo Y TODOS SUS CAMPOS A NULL
 */
LISTNODE* INILISTNODE() {
    LISTNODE* aux;
    aux = (LISTNODE*) malloc(sizeof (LISTNODE));
    if (!aux)return NULL;
    aux->hijo = NULL;
    aux->padre = NULL;
    aux->room = NULL;
    return aux;
}

/*
 * @BRIEF comprueba si la lista de espacios esta vacia
 * @PARAM la lista
 * @RETURN true si esta vacia, false si no lo esta
 */
BOOL ISEMPTYLIST(AUXLIST* list) {
    if (!list) return TRUE; /* Caso de error*/
    if (!list->first) return TRUE; /* Caso de lista vacía*/
    return FALSE; /* Caso de lista no vacía*/
}

/*
 * @BRIEF destruye un nodo de la lista
 * @PARAM el nodo
 * @RETURN nada
 */
void DESTROYLISTNODE(LISTNODE* node) {
    if (!node)return;
    if (node->hijo)
        node->hijo->padre = NULL;
    free(node);
}

/*
 * @BRIEF destruye la lista
 * @PARAM la lista
 * @RETURN nada
 */
void DESTROYLIST(AUXLIST* list) {
    LISTNODE * aux;
    if (!list)return;
    while (list->first != NULL) {
        aux = list->first;
        list->first = list->first->hijo;
        DESTROYLISTNODE(aux);
    }
    free(list);
}

/*
 * @BRIEF inserta un elemento en la primera posicion de la lista
 * @PARAM la lista y el ESPACIO
 * @RETURN OK o ERROR
 */
STATUS INSERTONLIST(AUXLIST* list, ESPACIO *elem) {
    LISTNODE *pn = NULL;
    if (!list || !elem) return ERROR;
    pn = INILISTNODE();
    if (!pn) return ERROR;
    pn->room = elem;
    if (ISEMPTYLIST(list) == TRUE) {
        list->first = pn;
        return OK;
    }
    pn->hijo = list->first;
    list->first = pn;
    pn->padre = NULL;
    return OK;
}

/*
 * @BRIEF extrae Y DESTRUYE un elemento de la lista
 * @PARAM la lista y el contenido del elemento a destruir
 * @RETURN OK o ERROR
 */
STATUS EXTRACTFROMLIST(AUXLIST* list, ESPACIO* elem) {
    LISTNODE * aux = NULL;
    LISTNODE * preaux;
    if (!list || !elem || ISEMPTYLIST(list))return ERROR;

    if (elem == list->first->room) {
        aux = list->first;
        list->first = aux->hijo;
        DESTROYLISTNODE(aux);
        return OK;
    }

    for (aux = list->first->hijo, preaux = list->first; aux != NULL; preaux = preaux->hijo, aux = aux->hijo) {
        if (aux->room == elem) {
            preaux->hijo = aux->hijo;
            DESTROYLISTNODE(aux);
            return OK;
        }
    }
    return ERROR;
}

/*
 * @BRIEF comprueba si un elemento esta o no en la lista
 * @PARAM la lista y el elemento
 * @RETURN true si esta, false si no esta
 */
BOOL ISONLIST(AUXLIST* list, ESPACIO* elem) {
    LISTNODE * aux = NULL;
    LISTNODE * preaux;
    if (!list || !elem || ISEMPTYLIST(list))return FALSE;

    if (elem == list->first->room) {
        return TRUE;
    }

    for (aux = list->first->hijo, preaux = list->first; aux != NULL; preaux = preaux->hijo, aux = aux->hijo) {
        if (aux->room == elem) {
            return TRUE;
        }
    }
    return FALSE;
}

/*
 * @BRIEF inicializa un nodo de un ARBOL
 * @PARAM nada
 * @RETURN la memoria para el nodo Y TODOS SUS CAMPOS A NULL
 */
NODEAB* ININODEAB() {
    NODEAB* aux;
    int i;
    aux = (NODEAB*) malloc(sizeof (NODEAB));
    if (!aux)return NULL;
    aux->father = NULL;
    aux->info = NULL;
    for (i = 0; i < 3; i++)
        aux->son[i] = NULL;
    return aux;
}

/*
 * @BRIEF inicializa un arbol
 * @PARAM nada
 * @RETURN la memoria para el arbol Y TODOS SUS CAMPOS A NULL
 */
ARBOL* INIARBOL() {
    ARBOL* aux;
    aux = (ARBOL*) malloc(sizeof (ARBOL));
    if (!aux) return NULL;
    aux->root = NULL;
    return aux;
}
/*
 * @BRIEF funcion recursiva para insertar un ESPACIO room que ha sido explorado desde padre en el nodo correcto. Para construir el Arbol de busqueda en anchura
 * @PARAM el nodo que del arbol que se esta examinando, la habitacion a introducir y la habitacion desde la que se ha exlporado la otra habitacion
 * @RETURN OK si consigue encontrar el padre y por tanto introducirlo en su lugar correctamente. ERROR si no fue posible
 */

/*notese que esta funcion pretende construir el arbol de busqueda en anchura*/
STATUS INSERTONARBOLREC(NODEAB*nodo, ESPACIO*room, ESPACIO* padre) {
    int i;
    STATUS out;
    if (!nodo || !room || !padre)return ERROR;
    /*caso de que el nodo tenga la habitacion padre. CASO BASE*/
    if (nodo->info == padre) {
        for (i = 0; i < 3; i++) {
            if (nodo->son[i] == NULL) {
                nodo->son[i] = ININODEAB();
                nodo->son[i]->info = room;
                nodo->son[i]->father = nodo;
                return OK;
            }
        }
        return ERROR;
    }
    /*caso de que alguno de los nodos hijos contenga la habitacion padre*/
    for (i = 0; i < 3; i++) {
        if (nodo != NULL)
            if (nodo->son[i] != NULL)
                if (nodo->son[i]->info == padre) {
                    return INSERTONARBOLREC(nodo->son[i], room, padre);
                }
    }
    /*caso de que todos los nodos esten vacios. DEAD END*/
    if (nodo->son[0] == NULL)return ERROR;
    /*caso de que ningun nodo hijo contenga la habitacion padre*/
    for (i = 0; i < 3; i++) {
        out = INSERTONARBOLREC(nodo->son[i], room, padre);
        if (out == OK)return out;
    }
    return ERROR;
}

/*
 * @BRIEF counstruir el arbol como un arbol de busqueda en anchura
 * @PARAM el arbol, el espacio a introducir y el espacio desde el cual se ha explorado ese espacio anteriormente
 * @RETURN OK si todo fue bien, ERROR si no
 */
STATUS INSERTONARBOL(ARBOL* arbol, ESPACIO*room, ESPACIO* padre) {
    if (!arbol || !room || !padre)return ERROR;
    if (!arbol->root) {
        arbol->root = ININODEAB();
        arbol->root->info = room;
        return OK;
    }
    return INSERTONARBOLREC(arbol->root, room, padre);
}

/*
 * @BRIEF encuentra el nodo del arbol en el que se encuentra el espacio destino
 * @PARAM el arbol donde buscar y el espacio a encontrar (destino)
 * @RETURN devuelve el nodo del arbol que contiene al destino
 */
NODEAB* FINDSUBARBOLWITH(NODEAB* nodo, ESPACIO*destino) {
    int i;
    NODEAB* aux;
    if (!nodo || !destino)return NULL;
    if (nodo->info == destino)return nodo;
    if (nodo->son[0] == NULL)return NULL;
    for (i = 0; i < 3; i++) {
        aux = FINDSUBARBOLWITH(nodo->son[i], destino);
        if (aux != NULL)return aux;
    }
    return NULL;
}

/*
 * @BRIEF encontrar el nodo hijo de la raiz que sea raiz del subarbol que contenga a destino.
 * En otras palabras, encontrar la rama que contiene a destino. Y de esta forma conseguir encontrar
 * el espacio con el que comenzar el "camino" hacia el ESPACIO destino
 * @PARAM el arbol donde buscar y el destino que buscar
 * @RETURN el espacio con el que comenzar el "camino" hacia el ESPACIO destino
 */
ESPACIO* FINDFIRSTSTEPTO(ARBOL*arbol, ESPACIO*destino) {
    NODEAB* found, *aux;
    if (!arbol || !destino)return NULL;
    found = FINDSUBARBOLWITH(arbol->root, destino);
    if (!found)return NULL;
    aux = found->father;
    while (aux->father->father != NULL)aux = aux->father;
    return aux->info;
}

/*
 * @BRIEF explora las habitaciones adyacentes al origen y va llenando el arbol de busqueda en
 * anchura hasta que no quedan mas o bien se ha encontrado el ESPACIO destino que se buscaba
 * @PARAM un arbol que construir como arbol de busqueda en anchura
 * una lista para guardar todos los espacios abiertos conocidos (es decir, visitables
 * desde los ESPACIOS ya visitados)
 * una lista para guardar todos los espacios ya visitados (cerrados)
 * y el espacio destino que se busca
 * @RETURN nada. Esta funcion SOLO sirve para crear el arbol de busqueda en anchura (FUNDAMENTAL)
 */
void EXPLORE(ARBOL*arbol, AUXLIST* open, AUXLIST* closed, ESPACIO* destino) {
    ESPACIO **aux;
    ESPACIO * exploring;
    int i;
    aux = (ESPACIO**) malloc(sizeof (ESPACIO*)*4);
    if (!aux)return;
    while (ISEMPTYLIST(open) == FALSE && open->first->room) {
        exploring = open->first->room;
        INSERTONLIST(closed, exploring);
        for (i = 0; i < 4; i++) {
            if (open->first && exploring->exit[i]) {
                aux[i] = exploring->exit[i]->conexion;
                if (ISONLIST(closed, aux[i]) == FALSE && ISONLIST(open, aux[i]) == FALSE) {
                    INSERTONLIST(open, aux[i]);
                    INSERTONARBOL(arbol, aux[i], exploring);
                    if (aux[i] == destino) {
                        EXTRACTFROMLIST(open, exploring);
                        free(aux);
                        return;
                    }
                }
            }
        }
        EXTRACTFROMLIST(open, exploring);
    }
    free(aux);
}

/*
 * @BRIEF destruye recursivamente todos los nodos del arbol
 * @PARAM el nodo en el que se esta ejecutando la recursion
 * @RETURN nada
 */
void DESTROYNODEABREC(NODEAB* node) {
    int i;
    if (!node) return;
    for (i = 0; i < 3; i++) {
        if (node->son[i])
            DESTROYNODEABREC(node->son[i]);
    }
    free(node);
}

/*
 * @BRIEF destruye el arbo y todos sus nodos
 * @PARAM el arbol
 * @RETURN nada
 */
void DESTROYAB(ARBOL *arbol) {
    if (!arbol)return;
    DESTROYNODEABREC(arbol->root);
    free(arbol);
}

/*
 * @BRIEF calcula el camino mas corto para ir de una sala a otra y devuelve el primero de los "pasos" de este camino
 * @PARAM el espacio de origen 
 * @PARAM el espacio de destino
 * @RETURN el espacio con el que comienza el camino mas corto
 */

/*si, todas las funciones en mayusculas y todo el follon de los arboles y las listas de espacios
 son por esta jodida funcion*/
ESPACIO* move_to_room(ESPACIO* origen, ESPACIO* destino) {
    AUXLIST *open, *closed;
    ARBOL * arbol;
    ESPACIO* out;

    open = INILIST();
    if (!open)return NULL;
    open->first = INILISTNODE();
    if (!open->first) {
        DESTROYLIST(open);
        return NULL;
    }
    open->first->hijo = NULL;
    open->first->padre = NULL;
    open->first->room = origen;
    closed = INILIST();
    if (!closed) {
        DESTROYLIST(open);
        return NULL;
    }
    closed->first = INILISTNODE();
    if (!closed->first) {
        DESTROYLIST(open);
        DESTROYLIST(closed);
        return NULL;
    }
    closed->first->padre = NULL;
    closed->first->hijo = NULL;
    closed->first->room = origen;
    arbol = INIARBOL();
    if (!arbol) {
        DESTROYLIST(open);
        DESTROYLIST(closed);
        return NULL;
    }
    arbol->root = ININODEAB();
    if (!arbol->root) {
        DESTROYLIST(open);
        DESTROYLIST(closed);
        DESTROYAB(arbol);
        return NULL;
    }
    arbol->root->info = origen;

    EXPLORE(arbol, open, closed, destino);
    out = FINDFIRSTSTEPTO(arbol, destino);

    DESTROYLIST(open);
    DESTROYLIST(closed);
    DESTROYAB(arbol);

    return out;
}
/*fin de este maldito infierno*/

/*
 * @BRIEF explora las habitaciones adyacentes a la pasada en la primera posicion de la lista open
 * y las va guardando en un arbol hasta que la exploracion ha llegado a ser de depth movimientos
 * @PARAM una lista de ESPACIOS open, una lista de ESPACIOS closed, un arbol y un entero depth
 * @RETURN nada
 */
void DEPTHEXPLORE(AUXLIST* open, AUXLIST* closed, ARBOL* arbol, int depth) {
    ESPACIO **aux;
    ESPACIO * exploring;
    int i;
    if (!open || !closed || !arbol || depth < 1)return;
    aux = (ESPACIO**) malloc(sizeof (ESPACIO*)*4);
    if (!aux)return;
    while (ISEMPTYLIST(open) == FALSE && depth > 0) {
        exploring = open->first->room;
        ;
        INSERTONLIST(closed, exploring);
        for (i = 0; i < 4; i++) {
            if (open->first && exploring->exit[i]) {
                aux[i] = exploring->exit[i]->conexion;
                if (ISONLIST(closed, aux[i]) == FALSE && ISONLIST(open, aux[i]) == FALSE) {
                    INSERTONLIST(open, aux[i]);
                    INSERTONARBOL(arbol, aux[i], exploring);
                }
            }
        }
        EXTRACTFROMLIST(open, exploring);
        depth--;
    }
    free(aux);
}
/*
 _________________________________________________________________________________________
 _________________________funciones para cosas aleatorias_________________________________
 _________________________________________________________________________________________
 ______________cambiar de .c cuando sea oportuno a otro mas apropiado_____________________
 _________________________________________________________________________________________
 */

/*
 * @BRIEF genera un numero aleatorio entero en un rango de [inf,sup]
 * @PARAM el numero entero inferior del rango y el superior
 * @RETURN devuelve un numero aleatorio
 */
int aleat_num(int inf, int sup) {
    return (inf + (int) (((double) (sup - inf + 1) * rand()) / (RAND_MAX + 1.0)));
}

/*
 * @BRIEF genera una permutacion aleatoria de enteros numeros desde 0 hasta n-1
 * @PARAM el tamaño de la tabla que contendra la parmutacion. es decir, el numero de elementos
 * @RETURN una tabla que contiene una permutacion aleatora de numeros desde el 0 hasta el n-1
 */
int* genera_perm(int n) {
    int * perm;
    int aux1, aux2;
    int i;

    perm = (int*) malloc(n * sizeof (int));
    if (!perm)return NULL;

    for (i = 0; i < n; i++) {
        perm[i] = i;
    }
    for (i = 0; i < n; i++) {
        aux1 = perm[i];
        aux2 = aleat_num(i, n - 1);
        perm[i] = perm[aux2];
        perm[aux2] = aux1;
    }
    return perm;
}

/*
 _______________________________________________________________________________________
 _______________________________________________________________________________________
 ____________________________fin de funciones aleatorias________________________________
 _______________________________________________________________________________________
 _______________________________________________________________________________________
 */

/*
 * @BRIEF funcion recursiva que busca aleatoriamente por las ramas de un arbol hasta que llega
 * a la profundidad depth deseada o no puede seguir avanzando (por lo que tiene que busar en otra rama)
 * @PARAM el nodo de la recursion y las capas de profundidad que quedan para llegar a la deseada
 * @RETURN el espacio que se encuentra en esa posicion aleatoria del arbol (pero de profundidad establecida)
 */
ESPACIO* RANDOMARBOLSEARCHREC(NODEAB* node, int depth) {
    ESPACIO* aux;
    int *permutacion;

    if (!node) return NULL;
    if (depth == 0)return node->info;
    depth--;
    permutacion = genera_perm(3);
    aux = RANDOMARBOLSEARCHREC(node->son[permutacion[0]], depth);
    if (aux != NULL) {
        free(permutacion);
        return aux;
    }
    aux = RANDOMARBOLSEARCHREC(node->son[permutacion[1]], depth);
    if (aux != NULL) {
        free(permutacion);
        return aux;
    }
    aux = RANDOMARBOLSEARCHREC(node->son[permutacion[2]], depth);
    free(permutacion);
    return aux;
}

/*
 * @BRIEF busca aleatoriamente en un arbol un nodo cualquiera de profundidad depth deseada
 * @PARAM el arbol en el que buscar y la profundidad deseada
 * @RETURN el espacio encontrado en una de las hojas de profundidad depth deseada
 */
ESPACIO* RANDOMARBOLSEARCH(ARBOL* arbol, int depth) {
    if (!arbol || depth < 0) return NULL;
    return RANDOMARBOLSEARCHREC(arbol->root, depth);
}

/*
 * @BRIEF calcula los espacios que hay a dist movimientos de distancia
 * @PARAM el espacio "raiz" y la distancia de movimentos de las salas que buscamos
 * @RETURN uno de los espacios que se hayan a dist movimientos de distancia del espacio room
 */
ESPACIO* rooms_at_dist(ESPACIO* room, unsigned int dist) {
    AUXLIST *open, *closed;
    ARBOL * arbol;
    ESPACIO* out;

    if (!room || dist == 0)return NULL;
    open = INILIST();
    if (!open)return NULL;

    open->first = INILISTNODE();
    if (!open->first) {
        DESTROYLIST(open);
        return NULL;
    }
    open->first->hijo = NULL;
    open->first->padre = NULL;
    open->first->room = room;
    closed = INILIST();
    if (!closed) {
        DESTROYLIST(open);
        return NULL;
    }
    closed->first = INILISTNODE();
    if (!closed->first) {
        DESTROYLIST(open);
        DESTROYLIST(closed);
        return NULL;
    }
    closed->first->padre = NULL;
    closed->first->hijo = NULL;
    closed->first->room = room;
    arbol = INIARBOL();
    if (!arbol) {
        DESTROYLIST(open);
        DESTROYLIST(closed);
        return NULL;
    }
    arbol->root = ININODEAB();
    if (!arbol->root) {
        DESTROYLIST(open);
        DESTROYLIST(closed);
        DESTROYAB(arbol);
        return NULL;
    }
    arbol->root->info = room;

    DEPTHEXPLORE(open, closed, arbol, dist);
    out = RANDOMARBOLSEARCH(arbol, dist);

    DESTROYLIST(open);
    DESTROYLIST(closed);
    DESTROYAB(arbol);

    return out;
}

/* @BRIEF devuelve la lista de objetos de la sala
 * @PARAM la sala
 * @RETURN dicha lista
 */
List* get_room_list(ESPACIO* room) {
    if (room)
        return room->list_obj;
    else return NULL;
}
