/* 
 * File:   pespacios.c
 * Author: Carlos Li Hu
 *
 * Created on 6 de octubre de 2015, 1:07
 */

#include "espacios.h"

int main(int argc, char** argv) {
    ESPACIO * space[2][3];
    ESPACIO* aux;
    int i, j, k;
    int coord[6][2], *coordaux;
    OBJ* objeto = NULL;
    char*comoquieras[4];
    /*definimos una coordenadas*/
    coord[0][0] = 0;
    coord[0][1] = 0;
    coord[1][0] = 0;
    coord[1][1] = 1;
    coord[2][0] = 0;
    coord[2][1] = 2;
    coord[3][0] = 1;
    coord[3][1] = 0;
    coord[4][0] = 1;
    coord[4][1] = 1;
    coord[5][0] = 1;
    coord[5][1] = 2;
    objeto = ini_obj();
    if (objeto)printf("OK\t1\n");
    if (!set_obj(objeto, "puerta", ".", "(...)", 0, 1, 0, 0))printf("OK\t2\n");

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 3; j++) {
            space[i][j] = iniEspacio();
            if (space[i][j] != NULL)printf("OK\t3 [%d %d] (hay muchos, por el bucle)\n", i, j);
        }
    }

    for (k = 0, i = 0; i < 2; i++)
        for (j = 0; j < 3; j++, k++)
            if (room_set_coords(space[i][j], coord[k]) == OK)
                printf("OK\t4 [%d %d] (hay mas aun, por el MEGAULTRAWOMBOCOMBOTANGOMAMBO-bucle anidado)\n", k, j);

    /*comprobamos que las funciones del modulo espacios funcione para cada coordenada definida*/

    /*_________________________________________________________________________________________________________________________*/
    /*_________________________________________________________________________________________________________________________*/
    /*_________________________________________________________________________________________________________________________*/
    if (room_set_descr(space[0][0], "esta es la sala 0,0") == OK)printf("OK\t5\n");
    if (!room_set_estado(space[0][0], 0))printf("OK\t6\n");
    if (!room_insert_in_objlist(space[0][0], objeto))printf("OK\t7\n");
    if (!room_set_exit_door(space[0][0], 0, objeto))printf("OK\t8\n");
    if (!room_set_exit_direction(space[0][0], 0, "NORTE"))printf("OK\t9\n");
    if (!room_set_exit_connection(space[0][0], 0, space[0][1]))printf("OK\t10\n");
    if (is_obj_in_room(space[0][0], "puerta") == TRUE)printf("OK\t11\n");
    room_set_exit_door(space[0][0], 1, objeto);
    room_set_exit_direction(space[0][0], 1, "ESTE");
    room_set_exit_connection(space[0][0], 1, space[1][0]);
    /*_________________________________________________________________________________________________________________________*/
    room_set_descr(space[1][0], "esta es la sala 1,0");
    room_set_estado(space[1][0], 1);
    room_set_exit_door(space[1][0], 3, objeto);
    room_set_exit_direction(space[1][0], 3, "OESTE");
    room_set_exit_connection(space[1][0], 3, space[0][0]);
    /*_________________________________________________________________________________________________________________________*/
    room_set_descr(space[1][1], "esta es la sala 1,1");
    room_set_estado(space[1][1], 1);
    room_set_exit_door(space[1][1], 3, objeto);
    room_set_exit_direction(space[1][1], 3, "OESTE");
    room_set_exit_connection(space[1][1], 3, space[0][1]);
    room_set_exit_door(space[1][1], 1, objeto);
    room_set_exit_direction(space[1][1], 1, "NORTE");
    room_set_exit_connection(space[1][1], 1, space[1][2]);
    /*_________________________________________________________________________________________________________________________*/
    room_set_descr(space[0][1], "esta es la sala 0,1");
    room_set_estado(space[0][1], 1);
    room_set_exit_door(space[0][1], 1, objeto);
    room_set_exit_direction(space[0][1], 1, "ESTE");
    room_set_exit_connection(space[0][1], 1, space[1][1]);
    room_set_exit_door(space[0][1], 2, objeto);
    room_set_exit_direction(space[0][1], 2, "SUR");
    room_set_exit_connection(space[0][1], 2, space[0][0]);
    room_set_exit_door(space[0][1], 0, objeto);
    room_set_exit_direction(space[0][1], 0, "NORTE");
    room_set_exit_connection(space[0][1], 0, space[0][2]);
    /*_________________________________________________________________________________________________________________________*/
    room_set_descr(space[0][2], "esta es la sala 0,2");
    room_set_estado(space[0][2], 1);
    room_set_exit_door(space[0][2], 1, objeto);
    room_set_exit_direction(space[0][2], 1, "ESTE");
    room_set_exit_connection(space[0][2], 1, space[1][2]);
    room_set_exit_door(space[0][2], 2, objeto);
    room_set_exit_direction(space[0][2], 2, "SUR");
    room_set_exit_connection(space[0][2], 2, space[0][1]);
    /*_________________________________________________________________________________________________________________________*/
    room_set_descr(space[1][2], "esta es la sala 1,2");
    room_set_estado(space[1][2], 1);
    room_set_exit_door(space[1][2], 3, objeto);
    room_set_exit_direction(space[1][2], 3, "OESTE");
    room_set_exit_connection(space[1][2], 3, space[0][2]);
    room_set_exit_door(space[1][2], 2, objeto);
    room_set_exit_direction(space[1][2], 2, "SUR");
    room_set_exit_connection(space[1][2], 2, space[1][1]);
    /*_________________________________________________________________________________________________________________________*/
    /*_________________________________________________________________________________________________________________________*/
    /*_________________________________________________________________________________________________________________________*/


    if (!room_get_exit_directions(space[0][0], comoquieras))printf("OK\t12\n");
    if (!strcmp(comoquieras[0], "NORTE"))printf("OK\t12-0\n");
    if (!strcmp(comoquieras[1], "ESTE"))printf("OK\t12-1\n");
    if (obj_cmp(objeto, room_get_exit_door(space[0][0], "NORTE")))printf("OK\t13\n");
    if (room_get_room_connection(space[0][0], "NORTE") == space[0][1])printf("OK\t14\n");

    if (n_objs_in_room(space[0][0]) == 1)printf("OK\t15\n");
    if (get_room_estado(space[0][0]) == 0)printf("OK\t16\n");
    if (strcmp(get_room_descr(space[0][0]), "esta es la sala 0,0") == 0)printf("OK\t17\n");

    coordaux = get_room_coord(space[0][0]);
    if (coordaux[0] == coord[0][0] && coordaux[1] == coord[0][1])printf("OK\t18\n");

    if (move_to_room(space[0][2], space[1][0]) == space[0][1])printf("OK\t19\n");

    aux = rooms_at_dist(space[0][0], 1);
    if (aux == space[0][1] || aux == space[1][0])printf("OK\t20\n");

    destroy_obj(objeto);
    objeto = room_extract_from_objlist(space[0][0], "puerta");
    if (strcmp(get_obj_name(objeto), "puerta") == 0)printf("OK\t21\n");

    if (coords_distance(get_room_coord(space[0][0]), get_room_coord(space[1][2])) == 3)
        printf("OK\t22\n");

    if (!destroy_obj(objeto))printf("OK\t23\n");
    for (i = 0; i < 2; i++)
        for (j = 0; j < 3; j++)
            if (!destroyEspacio(space[i][j]))printf("OK\t24 - %d,%d\n", i, j);

    for (i = 0; i < 4; i++) {
        if (comoquieras[i] != NULL)free(comoquieras[i]);
    }

    return 0;
}

