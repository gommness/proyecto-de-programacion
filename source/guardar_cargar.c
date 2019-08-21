/* 
 * File:   guardar_cargar.c
 * Author: David Lopez Ramos
 *
 */

#include "guardar_cargar.h"

/**
 * @BRIEF guarda la partida escribiendo en un fichero el estado actual de la partida.
 * @PARAM los objetos a guardar
 * @PARAM los personajes a guardar
 * @PARAM el estado del mapa
 * @PARAM el número de objetos 0, el numero de personajes 1, el numero de espacios: filas 2; columnas 3
 * @PARAM el fichero donde escribimos
 * @RETURN OK si ha ido bien, ERROR si falla
 */
STATUS guardar(OBJ**objeto, PERS** personaje, ESPACIO***mapa, int nums[4], FILE* f) {

    int i;
    int *ubic = NULL;
    int *coord = NULL;
    List* list/*=iniList()*/;
    OBJ**obj_pers;
    OBJ** obj_esp;
    OBJ* puerta = NULL;
    ESPACIO* conexion;
    int j, tamanio;
    int estado;
    int k;
    char** direcciones = NULL;
    int p;
    int r;
    int variable;
    int aux;

    if (!f || !mapa) return ERROR;
    direcciones = (char**) malloc(4 * sizeof (char*));

    /*imprimirmos cada objeto en el formato correspondiente*/

    fprintf(f, "23\r\n");
    /*imprimirmos cada uno de sus campos*/
    for (i = 0; i < 23; i++) {
        print_objeto_name(f, objeto[i]);
        /*fprintf(f, "\r\n");*/
        print_objeto_descr(f, objeto[i]);
        print_objeto_dial(f, objeto[i]);
        variable = get_obj_cogible(objeto[i]);
        if (variable == 0 || variable == 1) fprintf(f, "%d\r\n", variable);
        else fprintf(f, "X\r\n");
        variable = get_obj_active(objeto[i]);
        if (variable == 0 || variable == 1) fprintf(f, "%d\n", variable);
        else fprintf(f, "X\r\n");
        variable = get_obj_ilum(objeto[i]);
        if (variable == 0 || variable == 1) fprintf(f, "%d\r\n", variable);
        else fprintf(f, "X\r\n");
        variable = get_obj_activado(objeto[i]);
        if (variable == 0 || variable == 1) fprintf(f, "%d\r\n\r\n", variable);
        else fprintf(f, "X\r\n\r\n");

    }

    /*imprimirmos cada personaje en el formato correspondiente*/

    fprintf(f, "10\r\n");
    for (i = 0; i < 10; i++) {
        /*imprimimos cada uno de sus campos*/
        print_personaje_nombre(f, personaje[i]);
        print_personaje_descr(f, personaje[i]);
        print_personaje_dial(f, personaje[i]);
        ubic = get_pers_ubic(personaje[i]);
        if (ubic) fprintf(f, "[%d,%d]\r\n", ubic[0], ubic[1]);
        else fprintf(f, "X\r\n");

        /*imprimimos el inventario*/
        list = get_pers_list(personaje[i]);
        tamanio = sizeOfList(list);
        obj_pers = (OBJ**) malloc(tamanio * sizeof (OBJ*));

        if (tamanio <= 0) fprintf(f, "X\r\n");
        else {

            for (j = 0; j < tamanio; j++) {
                obj_pers[j] = extractFirstOBJ(list);
                print_objeto_name(f, obj_pers[j]);
            }
            for (j = 0; j < tamanio; j++)
                insertFirstOBJ(list, obj_pers[j]);
            for (j = 0; j < tamanio; j++)
                destroy_obj(obj_pers[j]);
            free(obj_pers);
        }

        fprintf(f, "\r\n");
    }

    /*imprimirmos cada espacio en el formato correspondiente*/

    fprintf(f, "4 4\r\n");

    for (i = 0; i < 4; i++) {
        /*imprimimos cada uno de sus campos*/
        for (j = 0; j < 4; j++) {
            fprintf(f, "[%d,%d]\r\n", get_room_coord(mapa[i][j])[0], get_room_coord(mapa[i][j])[1]);
            fprintf(f, "X\r\n");
            print_espacio_desc(f, mapa[i][j]);
            fprintf(f, "X\r\n");
            estado = get_room_estado(mapa[i][j]);
            if (estado == 0) fprintf(f, "oscuridad\r\n");
            else if (estado == 1) fprintf(f, "luz\r\n");
            else fprintf(f, "lluvia\r\n");
            fprintf(f, "X\r\n");

            /*la lista de objetos de cada espacio*/
            list = get_room_list(mapa[i][j]);
            tamanio = sizeOfList(list);
            obj_esp = (OBJ**) malloc(tamanio * sizeof (OBJ*));
            for (k = 0; k < tamanio; k++) {
                obj_esp[k] = extractFirstOBJ(list);
                print_objeto_name(f, obj_esp[k]);
            }
            for (k = 0; k < tamanio; k++)
                insertFirstOBJ(list, obj_esp[k]);

            for (k = 0; k < tamanio; k++)
                destroy_obj(obj_esp[k]);
            free(obj_esp);

            fprintf(f, "X\r\n");
            /*imprimismos las direecciones que tiene cada espacio*/
            room_get_exit_directions(mapa[i][j], direcciones);
            for (p = 0; p < 4; p++) {
                if (direcciones[p]) {
                    fprintf(f, "%s\t", direcciones[p]);
                    puerta = room_get_exit_door(mapa[i][j], direcciones[p]);
                    fprintf(f, "[");
                    aux = get_obj_activado(puerta);
                    fprintf(f, "%s %d ", get_obj_name(puerta), aux);
                    conexion = room_get_room_connection(mapa[i][j], direcciones[p]);
                    coord = get_room_coord(conexion);
                    fprintf(f, "%d %d", coord[0], coord[1]);
                    fprintf(f, "]\r\n");

                }
            }

            for (r = 0; r < 4; r++)
                free(direcciones[r]);

            fprintf(f, "X\r\n");
            fprintf(f, "\r\n");


        }
    }
    return OK;
}

/**
 * @BRIEF  carga los datos de una partida leyéndolos de un fichero.
 * @PARAM los objetos a cargar
 * @PARAM los personajes a cargar
 * @PARAM el mapa donde cargarlo
 * @PARAM el número de objetos 0, el numero de personajes 1, el numero de espacios: filas 2; columnas 3
 * @PARAM el fichero de donde leemos.
 * @RETURN OK si ha ido bien, ERROR si falla
 */
STATUS cargar(OBJ***objeto, PERS*** personaje, ESPACIO****mapa, int nums[4], FILE* f) {
    STATUS check;
    /*leemos el fichero correspondiente y cargamos los datos*/
    check = leer_fichero(f, objeto, personaje, mapa, nums);

    return check;

}



