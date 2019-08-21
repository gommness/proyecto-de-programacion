/* 
 * File:   pgestor.c
 * Author: Javier Gomez
 *
 * Created on 15 de octubre de 2015, 2:33
 */

#include "gestor.h"

/*
 * 
 */
int main() {
    OBJ* obj, *puerta;
    PERS* pers;
    ESPACIO* room;
    int ubic[2];
    FILE * pf;

    /*abrimos el fichero e inicializamos variables auxiliares*/
    pf = fopen("resultado.txt", "w");
    obj = ini_obj();
    puerta = ini_obj();
    pers = ini_pers();
    room = iniEspacio();

    /*comprobamos que cada funcion del modulo gestor funcione*/
    set_obj(obj, "ANTORCHA", "ilumina y eso", "no habla, es una antorcha", 1, 1, 1, 0);
    set_obj(puerta, "PUERTA", "es un artefacto arcano capaz de conectar espacios", "(...) no habla, se toma muy en serio su trabajo", 0, 1, 0, 0);
    ubic[0] = 0;
    ubic[1] = 0;
    set_pers(pers, "carlos", "es chino", "esa descripcion es racista!", ubic, obj);
    room_set_coords(room, ubic);
    room_set_descr(room, "la misma clase de siempre... paso mas tiempo aqui que en casa...\nestoy pensando en mudarme a vivir aqui");
    room_set_estado(room, 1);
    room_insert_in_objlist(room, obj);
    room_set_exit_door(room, 0, puerta);
    room_set_exit_direction(room, 0, "norte");
    room_set_exit_connection(room, 0, room); /*oh dios mio, saliendo por el norte vuelves al mismo lugar (ToT)*/

    print_objeto(pf, obj);
    print_personaje(pf, pers);
    print_espacio(pf, room);

    print_objeto_name(pf, obj);
    print_objeto_descr(pf, obj);
    print_objeto_dial(pf, obj);
    print_objeto_activable(pf, obj);
    print_objeto_cogible(pf, obj);
    print_objeto_iluminador(pf, obj);
    print_objeto_activado(pf, obj);

    print_personaje_nombre(pf, pers);
    print_personaje_descr(pf, pers);
    print_personaje_dial(pf, pers);
    print_personaje_ubic(pf, pers);
    print_personaje_obj(pf, pers);

    print_espacio_coord(pf, room);
    print_espacio_desc(pf, room);
    print_espacio_estado(pf, room);
    print_espacio_obj(pf, room);
    print_espacio_exit(pf, room);

    return 0;

}

