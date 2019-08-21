/* 
 * File:   gestor.h
 * Author: Javier Gomez && David Lopez
 *
 * Created on 9 de octubre de 2015, 17:06
 */

#include "gestor.h"

/*@BRIEF Imprime todos los campos de un objeto
 *@PARAM El objeto y un fichero destino
 *@RETURN Nada
 */
void print_objeto(FILE* fichero, OBJ* objeto) {
    /*imprimimos todos los campos del objeto*/
    print_objeto_name(fichero, objeto);
    print_objeto_descr(fichero, objeto);
    print_objeto_dial(fichero, objeto);
    print_objeto_activable(fichero, objeto);
    print_objeto_cogible(fichero, objeto);
    print_objeto_iluminador(fichero, objeto);
    print_objeto_activado(fichero, objeto);
}

/*@BRIEF Imprime todos los campos de un personaje
 *@PARAM El personaje y un fichero destino
 *@RETURN Nada
 */
void print_personaje(FILE* fichero, PERS* personaje) {
    /*imprimimos todos los campos del personaje*/
    print_personaje_nombre(fichero, personaje);
    print_personaje_descr(fichero, personaje);
    print_personaje_dial(fichero, personaje);
    print_personaje_ubic(fichero, personaje);
    print_personaje_obj(fichero, personaje);
}

/*@BRIEF Imprime todos los campos de un espacio
 *@PARAM el espacio y un fichero destino
 *@RETURN Nada
 */
void print_espacio(FILE* fichero, ESPACIO* espacio) {
    /*imprimimos todos los campos del espacio*/
    print_espacio_coord(fichero, espacio);
    print_espacio_desc(fichero, espacio);
    print_espacio_estado(fichero, espacio);
    print_espacio_obj(fichero, espacio);
    print_espacio_exit(fichero, espacio);
}

/*OBJETOS*/

/*@BRIEF Imprime el nombre de un objeto
 *@PARAM el objeto y un fichero destino
 *@RETURN Nada
 */
void print_objeto_name(FILE* fichero, OBJ* objeto) {
    fprintf(fichero, "%s\n", get_obj_name(objeto));
}

/*@BRIEF Imprime la descripcion de un objeto
 *@PARAM el objeto y un fichero destino
 *@RETURN Nada
 */
void print_objeto_descr(FILE* fichero, OBJ* objeto) {
    fprintf(fichero, "%s", get_obj_descr(objeto));
}

/*@BRIEF Imprime el dialogo de un objeto
 *@PARAM el objeto y un fichero destino
 *@RETURN Nada
 */
void print_objeto_dial(FILE* fichero, OBJ* objeto) {
    fprintf(fichero, "%s", get_obj_dial(objeto));
}

/*@BRIEF Imprime  si un objeto es activable o no
 *@PARAM el objeto y un fichero destino
 *@RETURN Nada
 */
void print_objeto_activable(FILE* fichero, OBJ* objeto) {
    /*comprobamos si el objeto es activable o no*/
    if (get_obj_active(objeto))
        fprintf(fichero, "%s es activable\n", get_obj_name(objeto));
    else
        fprintf(fichero, "%s no es activable\n", get_obj_name(objeto));
}

/*@BRIEF Imprime  si un objeto es cogible o no
 *@PARAM el objeto y un fichero destino
 *@RETURN Nada
 */
void print_objeto_cogible(FILE* fichero, OBJ* objeto) {
    /*comprobamos si el objeto es cogible o no*/
    if (get_obj_cogible(objeto))
        fprintf(fichero, "%s es cogible\n", get_obj_name(objeto));
    else
        fprintf(fichero, "%s no es cogible\n", get_obj_name(objeto));
}

/*@BRIEF Imprime  si un objeto puede iluminar o no
 *@PARAM el objeto y un fichero destino
 *@RETURN Nada
 */
void print_objeto_iluminador(FILE* fichero, OBJ* objeto) {
    /*comprobamos si el objeto es iluminable o no*/
    if (get_obj_ilum(objeto))
        fprintf(fichero, "%s es iluminador\n", get_obj_name(objeto));
    else
        fprintf(fichero, "%s no es iluminador\n", get_obj_name(objeto));
}

/*@BRIEF Imprime  si un objeto esta activado o no
 *@PARAM el objeto y un fichero destino
 *@RETURN Nada
 */
void print_objeto_activado(FILE* fichero, OBJ* objeto) {
    if (!objeto)
        return;
    /*comprobamos si el objeto esta activado o no*/
    if (get_obj_activado(objeto))
        fprintf(fichero, "%s está activado\n", get_obj_name(objeto));
    else
        fprintf(fichero, "%s no está activado\n", get_obj_name(objeto));
}


/*PERSONAJES*/

/*@BRIEF Imprime el nombre de un personaje
 *@PARAM el personaje y un fichero destino
 *@RETURN Nada
 */
void print_personaje_nombre(FILE* fichero, PERS* personaje) {
    fprintf(fichero, "%s\n", get_pers_name(personaje));
}

/*@BRIEF Imprime la descripcion de un personaje
 *@PARAM el personaje y un fichero destino
 *@RETURN Nada
 */
void print_personaje_descr(FILE* fichero, PERS* personaje) {
    fprintf(fichero, "%s", get_pers_descr(personaje));

}

/*@BRIEF Imprime el dialogo de un personaje
 *@PARAM el personaje y un fichero destino
 *@RETURN Nada
 */
void print_personaje_dial(FILE* fichero, PERS* personaje) {
    fprintf(fichero, "%s", get_pers_dial(personaje));

}

/*@BRIEF Imprime la ubicacion de un personaje
 *@PARAM el personaje y un fichero destino
 *@RETURN Nada
 */
void print_personaje_ubic(FILE* fichero, PERS* personaje) {
    int *ubic;
    ubic = get_pers_ubic(personaje);
    fprintf(fichero, "[%d][%d] es la ubicación de %s\n", ubic[0], ubic[1], get_pers_name(personaje));
}

/*@BRIEF Imprime los objetos de un personaje
 *@PARAM el personaje y un fichero destino
 *@RETURN Nada
 */
void print_personaje_obj(FILE* fichero, PERS* personaje) {
    List* list/*=iniList()*/;
    OBJ**objeto;
    int i, tamanio;
    /*obtenemos la lista con los objetos del inventario*/
    list = get_pers_list(personaje);
    tamanio = sizeOfList(list);
    objeto = (OBJ**) malloc(tamanio * sizeof (OBJ*));
    /*imprimimos cada objeto del inventario*/
    for (i = 0; i < tamanio; i++) {
        objeto[i] = extractFirstOBJ(list);
        print_objeto(fichero, objeto[i]);
    }
    for (i = 0; i < tamanio; i++)
        insertFirstOBJ(list, objeto[i]);
    for (i = 0; i < tamanio; i++)
        destroy_obj(objeto[i]);
    free(objeto);
}

/*ESPACIOS*/

/*@BRIEF Imprime las coordenadas de un espacio
 *@PARAM el espacio y un fichero destino
 *@RETURN Nada
 */
void print_espacio_coord(FILE* fichero, ESPACIO* espacio) {
    fprintf(fichero, "[%d][%d] es la ubicacion de la sala actual", get_room_coord(espacio)[0], get_room_coord(espacio)[1]);
}

/*@BRIEF Imprime la descripcion de un espacio
 *@PARAM el espacio y un fichero destino
 *@RETURN Nada
 */
void print_espacio_desc(FILE* fichero, ESPACIO* espacio) {
    fprintf(fichero, "%s", get_room_descr(espacio));

}

/*@BRIEF Imprime el estado de un espacio
 *@PARAM el espacio y un fichero destino
 *@RETURN Nada
 */
void print_espacio_estado(FILE* fichero, ESPACIO* espacio) {
    /*comprobamos si la sala esta abierta o no*/
    if (get_room_estado(espacio))
        fprintf(fichero, "la sala actual está activada");
    else
        fprintf(fichero, "la sala actual no está activada");
}

/*@BRIEF Imprime los objetos de un espacio
 *@PARAM el espacio y un fichero destino
 *@RETURN Nada
 */
void print_espacio_obj(FILE* fichero, ESPACIO* espacio) {
    List* list; /*=iniList();*/
    OBJ**objeto;
    int i, tamanio;
    /*obtenemos la lista de los objetos de un espacio*/
    list = get_room_list(espacio);
    tamanio = sizeOfList(list);
    objeto = (OBJ**) malloc(tamanio * sizeof (OBJ*));
    /*imprimimos cada objeto del espacio*/
    for (i = 0; i < tamanio; i++) {
        objeto[i] = extractFirstOBJ(list);
        print_objeto(fichero, objeto[i]);
    }
    for (i = 0; i < tamanio; i++)
        insertFirstOBJ(list, objeto[i]);
    for (i = 0; i < tamanio; i++)
        destroy_obj(objeto[i]);
    free(objeto);
}

/*@BRIEF Imprime las salidas de un espacio
 *@PARAM el espacio y un fichero destino
 *@RETURN Nada
 */
void print_espacio_exit(FILE* fichero, ESPACIO* espacio) {
    char**direcciones = (char**) malloc(4 * sizeof (char*));
    int i;
    /*comprobamos que direcciones tiene el espacio*/
    room_get_exit_directions(espacio, direcciones);
    fprintf(fichero, "las direcciones disponibles son:\n");
    for (i = 0; i < 4; i++)
        fprintf(fichero, "%s\n", direcciones[i]);
    free(direcciones);
}

/*@BRIEF Imprime los nombres de los personajes que haya en un espacio
 *@PARAM el espacio, un fichero destino y la tabla con todos los personajes
 *@RETURN Nada
 */
void print_pers_en_espacio(FILE* fichero, ESPACIO* espacio, PERS**personajes, int num_pers) {
    int i, *coord;
    if (!fichero || !espacio || !personajes)return;
    /*obtenemos las coordenadas del espacio actual*/
    coord = get_room_coord(espacio);
    /*imprimimos cada personaje del espacio actual*/
    for (i = 0; i < num_pers; i++) {
        if (coord[0] == get_pers_ubic(personajes[i])[0] && coord[1] == get_pers_ubic(personajes[i])[1])
            fprintf(fichero, "%s\n", get_pers_name(personajes[i]));
    }
}

/**
 * @BRIEF Imprime la bienvenida del juego
 * @AUTHOR Elvira Vegas Maganto
 * @PARAM la ventana donde se imprime
 * @RETURN OK si todo ha ido bien, ERROR sino.
 */
STATUS print_sala_inicial(PERS** pers, Ventana** v1, ESPACIO*** mapa) {

    int* sala = NULL;
    char* desc = NULL;
    List* list_aux = NULL;
    int tamanio = 0, m = 0, w = 0;
    OBJ** objeto_aux = NULL;

    /*obtenemos la sala inicial del jugador*/
    sala = get_pers_ubic(pers[0]);
    /*imprimimos la descripcion del espacio donde el jugador empieza o continua la partida*/
    print_marco_ventana_pequena(*v1, '*');
    desc = get_room_descr(mapa[sala[0]][sala[1]]);
    print_cadena_ventana(*v1, desc, 3, 3);

    print_cadena_ventana(*v1, "Objetos del espacio inicial:", 7, 3);
    list_aux = get_room_list(mapa[sala[0]][sala[1]]);
    tamanio = sizeOfList(list_aux);
    objeto_aux = (OBJ**) malloc(tamanio * sizeof (OBJ*));
    for (m = 0, w = 8; m < tamanio; m++, w++) {
        objeto_aux[m] = extractFirstOBJ(list_aux);
        print_cadena_ventana(*v1, get_obj_name(objeto_aux[m]), w, 3);
    }
    for (m = 0; m < tamanio; m++)
        insertFirstOBJ(list_aux, objeto_aux[m]);
    for (m = 0; m < tamanio; m++)
        destroy_obj(objeto_aux[m]);
    free(objeto_aux);

    return OK;
}

/**
 * @BRIEF Imprime el fin del juego
 * @AUTHOR Elvira Vegas Maganto
 * @PARAM la ventana donde se imprime
 * @RETURN OK si todo ha ido bien, ERROR sino.
 */
STATUS print_final_juego(PERS** pers, ESPACIO*** espacio, Ventana** window) {
    int ubic[2]={3,0};
    int* aux = NULL;
    List* list_aux = NULL;
    OBJ* obj_aux = NULL, *door = NULL;

    aux = get_pers_ubic(pers[0]);
    list_aux = get_room_list(espacio[1][2]);
    obj_aux = extractOBJ(list_aux, "estatua_de_padre");
    if (aux[0] == 1 && aux[1] == 2 && obj_aux) {
        destroy_obj(obj_aux);
        limpiar_ventana(*window);
        print_marco_ventana_pequena(*window, '*');
        print_cadena_ventana(*window, "la estatua ha desparecido, y la ana triste parece alegrarse", 3, 3);
        print_cadena_ventana(*window, "Ana_triste: muchas gracias por alegrarme, te abriré la puerta para que te despiertes, adios!", 5, 3);
        print_cadena_ventana(*window, "oigo como una puerta se abre", 7, 3);
        set_pers_ubic(pers[8],ubic);
                
        
        door = room_get_exit_door(espacio[1][0], "este");
        set_obj_activado(door, TRUE);
    }
    if (aux[0] == 2 && aux[1] == 0) {
	
        limpiar_ventana(*window);
        print_marco_ventana_pequena(*window, '*');
        print_cadena_ventana(*window, "SE ACABÓ MUTHAFUCKA, TOCA DESPERTARSE A COMERSE ESAS ALBÓNDIGAS", 7, 3);
    }

    return OK;
}
