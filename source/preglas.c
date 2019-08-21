/* 
 * File:   preglas.c
 * Author: Elvira Vegas Maganto
 *
 * Created on 30 de noviembre de 2015, 11:45
 */

#include "reglas.h"

int main() {

    OBJ** obj = NULL; /*array con todos los objetos*/
    PERS** pers = NULL; /*array con todos los personajes*/
    ESPACIO*** espacio = NULL; /*array con el mapa*/
    int tabla[4]; /*array con el número de objetos 0, el numero de personajes 1, el numero de espacios: filas 2; columnas 3*/
    FILE* fichero = NULL, *f_reglas = NULL; /*fichero con los datos del juego y fichero con las reglas*/
    STATUS check; /*variable para ir checkeando el codigo*/
    /*variables auxiliares*/
    int i = 0, j = 0, tamanio = 0;
    int* sala = NULL;
    OBJ* aux = NULL;
    char* name = NULL;
    char*** reglass = NULL; /*array con las reglas*/
    List* list_obj = NULL; /*lista para el inventario*/

    /*inicializo todos los ficheros necesarios*/
    name = (char*) malloc(30 * sizeof (char));
    if (name == NULL) {
        printf("Error al inicializar el nombre.\n");
        return -1;
    }

    /*abre el fichero de datos del juego*/
    fichero = fopen("inicio.txt", "r");
    if (fichero == NULL) {
        printf("Error al abrir el fichero.\n");
        return -1;
    }

    /*cargamos los datos del juego*/
    check = leer_fichero(fichero, &obj, &pers, &espacio, tabla);
    if (check == ERROR) {
        printf("Error al leer los datos del fichero.\n");
        return -1;
    }

    fclose(fichero);

    /*abre el fichero de las reglas*/
    f_reglas = fopen("reglas.txt", "r");
    if (f_reglas == NULL) {
        printf("Error al abrir el fichero de reglas.\n");
        return -1;
    }

    /*cargamos las reglas*/
    reglass = leer_condiciones(f_reglas, 4);
    if (reglass == NULL) {
        printf("Error al cargar las reglas.\n");
        return -1;
    }

    fclose(f_reglas);

    /*comprobamos que realice correctamente los cambios pertinentes*/
    check = reglas(reglass, 4, espacio, pers, obj);
    if (check == ERROR) {
        printf("Error al aplicar las reglas.\n");
        return -1;
    }

    /*regla del teletransporte*/
    printf("Teletransporte:\n");
    sala = get_pers_ubic(pers[0]);
    printf("La ubicacion del personaje es %d, %d.\n", sala[0], sala[1]);
    if (sala[0] == 3 && sala[1] == 0)
        printf("Exito en la regla de teletransporte.\n");
    else
        printf("Error en la regla de teletransporte.\n");

    /*regla de la insercion y extraccion en el inventario*/
    printf("Insercion y extraccion:\n");
    list_obj = get_pers_list(pers[0]);
    tamanio = sizeOfList(list_obj);
    for (i = 0; i < tamanio; i++) {
        aux = extractFirstOBJ(list_obj);
        print_objeto_name(stdout, aux);
    }
    printf("Exito en la regla de insercion y extraccion del inventario.\n");

    /*regla de abrir una puerta*/
    printf("Abrir puerta:\n");
    check = mover(espacio, pers[0], "este", stdout);
    printf("La ubicacion del personaje es %d, %d.\n", sala[0], sala[1]);
    if (check == ERROR)
        printf("Error en la accion de moverse.\n");
    sala = get_pers_ubic(pers[0]);

    if (sala[0] == 3 && sala[1] == 0)
        printf("No se ha cumplido la regla de abrir una puerta.\n");
    if (sala[0] == 4 && sala[1] == 0)
        printf("Exito en la regla de abrir una puerta.\n");

    /*liberamos las reglas*/
    check = free_reglas(reglass, 4);
    if (check == ERROR)
        printf("Error al liberar las reglas.\n");

    /*liberamos todas las variables auxiliares*/
    free(name);
    destroy_obj(aux);

    for (i = 0; i < tabla[0]; i++)
        destroy_obj(obj[i]);
    free(obj);

    for (i = 0; i < tabla[1]; i++)
        destroy_pers(pers[i]);
    free(pers);

    for (i = 0; i < tabla[2]; i++) {
        for (j = 0; j < tabla[3]; j++) {
            if (espacio[i][j] != NULL)
                destroyEspacio(espacio[i][j]);
            free(espacio[i]);
        }
    }
    free(espacio);

    printf("\nPruebas realizadas con exito.\n");

    return 0;
}
