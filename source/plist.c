/* 
 * File:   ppersonajes.c
 * Author: Carlos Li Hu
 */

#include "list.h"

int main(int argc, char** argv) {
    List * list = NULL;
    OBJ* objeto = NULL;
    objeto = ini_obj();
    list = iniList();
    /*primero comprobamos que la lista esta bien creada*/
    if (objeto == NULL) printf("ERROR 1");
    if (list == NULL) printf("ERROR 2");
    if (isEmptyList(list) == FALSE) printf("ERROR 3");
    if (sizeOfList(list) != 0) printf("ERROR 4");
    /*creamos un objeto y lo insertamos en la lista*/
    if (set_obj(objeto, "antorcha", "Emana luces", "No habla",
            TRUE, TRUE, TRUE, TRUE) == ERROR)printf("ERROR 5");
    if (insertFirstOBJ(list, objeto) == ERROR) printf("ERROR 6");
    /*destruimos el objeto y creamos otro*/
    if (destroy_obj(objeto) == ERROR) printf("ERROR 7");
    objeto = ini_obj();
    if (objeto == NULL) printf("ERROR 8");
    /*miramos si el estado de la lista antes y despues de extraer un objeto*/
    if (isEmptyList(list) == TRUE) printf("ERROR 9");
    if (sizeOfList(list) != 1) printf("ERROR 10");

    objeto = extractOBJ(list, "antorcha");
    if (objeto == NULL) printf("ERROR 11");
    if (strcmp(get_obj_name(objeto), "antorcha") != 0) printf("ERROR 12");
    if (isEmptyList(list) == FALSE) printf("ERROR 13");
    if (sizeOfList(list) != 0) printf("ERROR 14");
    /*liberamos el resto de cosas*/
    if (destroy_obj(objeto) == ERROR) printf("ERROR 15");
    if (freeList(list) == ERROR)printf("ERROR 16");
    return 0;
}


