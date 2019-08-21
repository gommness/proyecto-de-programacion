/* 
 * File:   objeto.h
 * Author: Javier Gomez
 */

#include "objeto.h"

int main() {

    OBJ* objeto = NULL, *objeto2 = NULL;
    BOOL aux;
    STATUS check;
    char *cadena = (char *) malloc(50 * sizeof (char));

    /*prueba inicializar objeto*/
    objeto = ini_obj();
    if (objeto == NULL) {
        printf("Falla la funcion que inicializa un objeto.\n");
        return -1;
    }

    objeto2 = ini_obj();
    if (objeto2 == NULL) {
        printf("Falla la funcion que inicializa un objeto.\n");
        return -1;
    }

    /*pruebas de set y get de los campos del objeto*/
    check = set_obj(objeto, "Pepe", "Soy el mas guay", "Holaaaaaa", 1, 1, 0, 0);
    if (check == ERROR)
        printf("Error en las funciones de set.\n");
    aux = get_obj_ilum(objeto);
    if (aux == TRUE)
        printf("Error en el set del campo cogible.\n");
    aux = get_obj_active(objeto);
    if (aux == FALSE)
        printf("Error en el set del campo activable.\n");
    cadena = get_obj_name(objeto);
    if (strcmp(cadena, "pepe") == 1)
        printf("Error en el set del nombre.\n");
    cadena = get_obj_descr(objeto);
    if (strcmp(cadena, "Soy el mas guay") == 1)
        printf("Error en el set de la descripcion.\n");
    cadena = get_obj_dial(objeto);
    if (strcmp(cadena, "Holaaaaaa") == 1)
        printf("Error en el set del dialogo.\n");
    aux = get_obj_cogible(objeto);
    if (aux == FALSE)
        printf("Error en el set del campo cogible.\n");
    check = copy_obj(objeto2, objeto);
    if (check == ERROR)
        printf("Error en la funcion de copiar.\n");
    aux = get_obj_activado(objeto);
    if (aux == TRUE)
        printf("Error en el set del campo activado.\n");
    aux = obj_cmp(objeto, objeto2);
    if (aux == FALSE)
        printf("Error en la funcion de comparar.\n");

    /*prueba de destruir el objeto*/
    check = destroy_obj(objeto);
    if (check == ERROR) {
        printf("Error en la funcion de liberar memoria.\n");
        return -1;
    }

    check = destroy_obj(objeto2);
    if (check == ERROR) {
        printf("Error en la funcion de liberar memoria.\n");
        return -1;
    }

    printf("Las pruebas se han realizado con exito.\n");

	return 0;
}
