/* 
 * File:   pguardar_cargar.c
 * Author: Elvira Vegas Maganto
 *
 * Created on 26 de noviembre de 2015, 19:00
 */

#include "guardar_cargar.h"
#include "interprete.h"

#define DIM 10

/**
 * @BRIEF comprueba que la funcion guardar una partida funciona bien
 * @PARAM los objetos a guardar
 * @PARAM los personajes a guardar
 * @PARAM el estado del mapa
 * @PARAM el número de objetos 0, el numero de personajes 1, el numero de espacios: filas 2; columnas 3
 * @PARAM el fichero donde escribimos
 * @RETURN OK si ha ido bien, ERROR si falla
 */
STATUS prueba_guardar(OBJ**objeto, PERS** personaje, ESPACIO***mapa, int nums[4], FILE* f) {
	STATUS check;
	/*compruebo que la funcion guardar funcione*/
	check = guardar(objeto, personaje, mapa, nums, f);
	if (check == ERROR) {
		printf("Error en la funcion guardar\n");
		return ERROR;
	}
	return OK;
}

/**
 * @BRIEF  comprueba que la funcion cargar una partida funciona bien
 * @PARAM los objetos a cargar
 * @PARAM los personajes a cargar
 * @PARAM el mapa donde cargarlo
 * @PARAM el número de objetos 0, el numero de personajes 1, el numero de espacios: filas 2; columnas 3
 * @PARAM el fichero de donde leemos.
 * @RETURN OK si ha ido bien, ERROR si falla
 */
STATUS prueba_cargar(OBJ***objeto, PERS*** personaje, ESPACIO****mapa, int nums[4], FILE* f) {
	STATUS check;
	/*compruebo que la funcion cargar funcione*/
	check = cargar(objeto, personaje, mapa, nums, f);
	if (check == ERROR) {
		printf("Error en la funcion cargar\n");
		return ERROR;
	}
	return OK;
}

int main() {
    STATUS check; /*variable para ir checkeando el codigo*/
    List* list_aux, *list;
    OBJ**objeto_aux;
    int m, tamanio, w;
    OBJ** obj = NULL, *obj_pers = NULL; /* array con todos los objetos del juego*/
    PERS** pers = NULL; /*array con todos los personajes del juego*/
    ESPACIO*** espacio = NULL; /*array con el mapa del juego*/
    int tabla[4]; /*array con el número de objetos 0, el numero de personajes 1, el numero de espacios: filas 2; columnas 3*/
    FILE* fichero = NULL, *f_part, *f_sin, *f_write; /*f_reglas*/ /*fichero con los datos del juego, fichero con las particulas a eliminar y fichero con los sinonimos, fichero para guardar o cargar la partida*/
    char verbo[30], directo[30], indirecto[30], comando[50]; /*variable donde se guarda el verbo, el directo, el indirecto y el comando del usuario*/

    int* sala = NULL, *aux = NULL, *aux2 = NULL, num_sin[DIM]; /**/
    char** part = NULL;
    char*** sin = NULL;
    Ventana* window1 = NULL;
    Ventana* window2 = NULL;
    Ventana* window3 = NULL;
    STATUS error;
    int z = 0;
    char* descripcion = NULL;
    int b;
    List* list_esp;
    OBJ**objeto_esp;
    int q, i = 0, j = 0, flag, num_part = 0, flag2;
    /*variables para buqlues y bandera*/;

    /*imprimimos en la ventana correspondiente*/
    window1 = ini_ventana(25, 70, 0, 0);
    if (!window1) return -1;
    window2 = ini_ventana(25, 70, 0, 72);
    if (!window2) return -1;
    window3 = ini_ventana(50, 102, 28, 0);
    if (!window3) return -1;

    /*comprobamos si ha habido algun error con las ventanas*/
    error = ventana_visible(window1);
    if (error == ERROR) printf("Error en los valores 1\n");
    error = ventana_visible(window2);
    if (error == ERROR) printf("Error en los valores 2\n");
    error = ventana_visible(window3);
    if (error == ERROR) printf("Error en los valores 3\n");

    /*abre el fichero de datos del juego*/
    fichero = fopen("inicio.txt", "r");
    if (fichero == NULL) {
        printf("Error al abrir el fichero.\n");
        return -1;
    }

    /*comprueba que lea el fichero del juego y lo guarde en las variables correspondientes*/
    check = leer_fichero(fichero, &obj, &pers, &espacio, tabla);
    if (check == ERROR) {
        printf("Error al leer los datos del fichero.\n");
        return -1;
    }

    /*abrimos el fichero de las particulas*/
    f_part = fopen("particulas.txt", "r");
    if (f_part == NULL) {
        printf("Error al abrir el fichero.\n");
        return -1;
    }

    fscanf(f_part, "%d", &num_part);
    part = (char**) malloc(num_part * sizeof (char*));
    if (!part)
        return ERROR;
    for (i = 0; i < num_part; i++) {
        part[i] = (char*) malloc(27 * sizeof (char));
        fscanf(f_part, "%s", part[i]);
    }

    /*abrimos el fichero de los sinonimos*/
    f_sin = fopen("sinonimos.txt", "r");
    if (fichero == NULL) {
        printf("Error al abrir el fichero.\n");
        return -1;
    }
    for (i = 0; i < DIM; i++)
        fscanf(f_sin, "%d", &num_sin[i]);

    sin = (char***) malloc(DIM * sizeof (char**));
    for (i = 0; i < DIM; i++) {
        sin[i] = (char**) malloc(num_sin[i] * sizeof (char*));
        for (j = 0; j < num_sin[i]; j++) {
            sin[i][j] = (char*) malloc(27 * sizeof (char));
            fscanf(f_sin, "%s", sin[i][j]);
        }
    }

    fclose(fichero);
    fclose(f_sin);
    fclose(f_part);



    for (z = 1; z < 70; z++) print_cadena_ventana(window2, "*", 1, z);
    for (z = 1; z < 70; z++) print_cadena_ventana(window2, "*", 24, z);
    for (z = 1; z < 25; z++) print_cadena_ventana(window2, "*", z, 1);
    for (z = 1; z < 25; z++) print_cadena_ventana(window2, "*", z, 68);
    print_cadena_ventana(window2, "Mm...muy interesante un loco mas para la familia.", 3, 3);
    print_cadena_ventana(window2, "Pero ya no hay vuelta atras,tendras que jugar, Carlos quiere su 10", 4, 3);
    print_cadena_ventana(window2, "Te deseo buena suerte compañero Sacha", 5, 3);

    /*guardamos la ubicacion inicial del jugador*/
    sala = get_pers_ubic(pers[0]);
    /*imprimimos la descripcion del espacio donde el jugador empieza o continua la partida*/
    for (z = 1; z < 70; z++) print_cadena_ventana(window1, "*", 1, z);
    for (z = 1; z < 70; z++) print_cadena_ventana(window1, "*", 24, z);
    for (z = 1; z < 25; z++) print_cadena_ventana(window1, "*", z, 1);
    for (z = 1; z < 25; z++) print_cadena_ventana(window1, "*", z, 68);
    descripcion = get_room_descr(espacio[sala[0]][sala[1]]);
    print_cadena_ventana(window1, descripcion, 3, 3);

    print_cadena_ventana(window1, "Objetos del espacio inicial:", 7, 3);
    list_aux = get_room_list(espacio[sala[0]][sala[1]]);
    tamanio = sizeOfList(list_aux);
    objeto_aux = (OBJ**) malloc(tamanio * sizeof (OBJ*));
    for (m = 0, w = 8; m < tamanio; m++, w++) {
        objeto_aux[m] = extractFirstOBJ(list_aux);
        print_cadena_ventana(window1, get_obj_name(objeto_aux[m]), w, 3);
    }
    for (m = 0; m < tamanio; m++)
        insertFirstOBJ(list_aux, objeto_aux[m]);
    for (m = 0; m < tamanio; m++)
        destroy_obj(objeto_aux[m]);
    free(objeto_aux);



    do {

        /*imprimos en la ventana correspondiente*/
        limpiar_ventana(window3);
        for (z = 1; z < 102; z++) print_cadena_ventana(window3, "*", 1, z);
        for (z = 1; z < 102; z++) print_cadena_ventana(window3, "*", 49, z);
        for (z = 1; z < 50; z++) print_cadena_ventana(window3, "*", z, 1);
        for (z = 1; z < 50; z++) print_cadena_ventana(window3, "*", z, 100);
        print_cadena_ventana(window3, "introduzca una opcion ", 3, 3);

        fgets(comando, 50, stdin);
        strtok(comando, "\n");
        if (interprete(comando, verbo, directo, indirecto, part, sin, num_part, num_sin) == ERROR)
            print_cadena_ventana(window2, "Error en el interprete", 3, 3);

        /*cada accion por separado, en cada accion llamamos a la funccion relacionada con esa accion y hacemos los printf necesarios en la ventana correspondiente, si hay alguna modificacion limpiamos la ventana cada vez*/
        if (strcmp("mover", verbo) == 0) {
            limpiar_ventana(window2);
            for (z = 1; z < 70; z++) print_cadena_ventana(window2, "*", 1, z);
            for (z = 1; z < 70; z++) print_cadena_ventana(window2, "*", 24, z);
            for (z = 1; z < 25; z++) print_cadena_ventana(window2, "*", z, 1);
            for (z = 1; z < 25; z++) print_cadena_ventana(window2, "*", z, 68);
            check = mover(espacio, pers[0], directo, stdout);
            if (check == ERROR)
                print_cadena_ventana(window2, "No puedes moverte en esa direccion", 3, 3);

            else
                print_cadena_ventana(window2, "te has movido correctamente", 3, 3);

        } else if (strcmp("coger", verbo) == 0) {
            limpiar_ventana(window2);
            for (z = 1; z < 70; z++) print_cadena_ventana(window2, "*", 1, z);
            for (z = 1; z < 70; z++) print_cadena_ventana(window2, "*", 24, z);
            for (z = 1; z < 25; z++) print_cadena_ventana(window2, "*", z, 1);
            for (z = 1; z < 25; z++) print_cadena_ventana(window2, "*", z, 68);
            check = coger(espacio, pers[0], directo, stdout);
            if (check == ERROR)
                print_cadena_ventana(window2, "No puedes coger ese objeto", 3, 3);
            else
                print_cadena_ventana(window2, "Has cogido el objeto correctamente", 3, 3);

        } else if (strcmp("dejar", verbo) == 0) {
            limpiar_ventana(window2);
            for (z = 1; z < 70; z++) print_cadena_ventana(window2, "*", 1, z);
            for (z = 1; z < 70; z++) print_cadena_ventana(window2, "*", 24, z);
            for (z = 1; z < 25; z++) print_cadena_ventana(window2, "*", z, 1);
            for (z = 1; z < 25; z++) print_cadena_ventana(window2, "*", z, 68);
            check = dejar(espacio, pers[0], directo, stdout);
            if (check == ERROR)
                print_cadena_ventana(window2, "No puedes dejar ese objeto.", 3, 3);
            else
                print_cadena_ventana(window2, "Has dejado el objeto correctamente", 3, 3);

        } else if (strcmp("encender", verbo) == 0) {
            limpiar_ventana(window2);
            for (z = 1; z < 70; z++) print_cadena_ventana(window2, "*", 1, z);
            for (z = 1; z < 70; z++) print_cadena_ventana(window2, "*", 24, z);
            for (z = 1; z < 25; z++) print_cadena_ventana(window2, "*", z, 1);
            for (z = 1; z < 25; z++) print_cadena_ventana(window2, "*", z, 68);
            check = encender(pers[0], directo, stdout);
            if (check == ERROR)
                print_cadena_ventana(window2, "No puedes encender ese objeto.", 5, 3);
            else
                print_cadena_ventana(window2, "has encendido el objeto correctamente", 5, 3);

        } else if (strcmp("apagar", verbo) == 0) {
            limpiar_ventana(window2);
            for (z = 1; z < 70; z++) print_cadena_ventana(window2, "*", 1, z);
            for (z = 1; z < 70; z++) print_cadena_ventana(window2, "*", 24, z);
            for (z = 1; z < 25; z++) print_cadena_ventana(window2, "*", z, 1);
            for (z = 1; z < 25; z++) print_cadena_ventana(window2, "*", z, 68);
            check = apagar(pers[0], directo, stdout);
            if (check == ERROR)
                print_cadena_ventana(window2, "No puedes apagar ese objeto.", 5, 3);
            else
                print_cadena_ventana(window2, "has apagado el objeto correctamente.", 5, 3);

        } else if (strcmp("abrir", verbo) == 0) {
            limpiar_ventana(window2);
            for (z = 1; z < 70; z++) print_cadena_ventana(window2, "*", 1, z);
            for (z = 1; z < 70; z++) print_cadena_ventana(window2, "*", 24, z);
            for (z = 1; z < 25; z++) print_cadena_ventana(window2, "*", z, 1);
            for (z = 1; z < 25; z++) print_cadena_ventana(window2, "*", z, 68);
            check = abrir_puerta(espacio, pers[0], indirecto, directo, stdout);
            if (check == ERROR)
                print_cadena_ventana(window2, "El personaje no puede abrir esa puerta", 4, 3);

        } else if (strcmp("hablar", verbo) == 0) {
            flag = 0;
            limpiar_ventana(window2);
            for (z = 1; z < 70; z++) print_cadena_ventana(window2, "*", 1, z);
            for (z = 1; z < 70; z++) print_cadena_ventana(window2, "*", 24, z);
            for (z = 1; z < 25; z++) print_cadena_ventana(window2, "*", z, 1);
            for (z = 1; z < 25; z++) print_cadena_ventana(window2, "*", z, 68);
            for (i = 0; flag == 0 && i < tabla[0]; i++)
                if (strcmp(get_obj_name(obj[i]), directo) == 0)
                    flag = 1;

            for (i = 0; flag == 0 && i < tabla[1]; i++)
                if (strcmp(get_pers_name(pers[i]), directo) == 0)
                    flag = 2;
            if (flag == 1)
                check = talk_obj(espacio, pers[0], directo, stdout);
            if (flag == 2)
                check = talk_persona(pers[0], pers, directo, tabla[1], stdout);
            else
                check = ERROR;

        } else if (strcmp("examinar", verbo) == 0) {
            flag = 0;

            if (strcmp("espacio", directo) == 0) {
                limpiar_ventana(window1);
                for (z = 1; z < 70; z++) print_cadena_ventana(window1, "*", 1, z);
                for (z = 1; z < 70; z++) print_cadena_ventana(window1, "*", 24, z);
                for (z = 1; z < 25; z++) print_cadena_ventana(window1, "*", z, 1);
                for (z = 1; z < 25; z++) print_cadena_ventana(window1, "*", z, 68);
                check = examinar_esp(espacio, pers[0], stdout);
                if (check == 0) {
                    aux = get_pers_ubic(pers[0]);
                    /*Objetos del espacio*/


                    list_esp = get_room_list(espacio[aux[0]][aux[1]]);
                    tamanio = sizeOfList(list_esp);
                    objeto_esp = (OBJ**) malloc(tamanio * sizeof (OBJ*));
                    b = 15;
                    for (q = 0; q < tamanio; q++) {
                        objeto_esp[q] = extractFirstOBJ(list_esp);
                        print_cadena_ventana(window1, "Objetos de la sala:", 14, 3);
                        print_cadena_ventana(window1, get_obj_name(objeto_esp[q]), b, 3);
                        b++;
                    }
                    for (q = 0; q < tamanio; q++)
                        insertFirstOBJ(list_esp, objeto_esp[q]);
                    for (q = 0; q < tamanio; q++)
                        destroy_obj(objeto_esp[q]);
                    free(objeto_esp);

                    /*Personajes del espacio*/
                    for (i = 1; i < tabla[1]; i++) {
                        aux2 = get_pers_ubic(pers[i]);
                        b = 11;
                        if (aux[0] == aux2[0] && aux[1] == aux2[1]) {
                            print_cadena_ventana(window1, "Personajes de la sala:", 10, 3);
                            print_cadena_ventana(window1, get_pers_name(pers[i]), b, 3);
                            b++;
                        }
                    }
                }
            }
            if (strcmp("inventario", directo) == 0) {
                List * list_aux2;
                OBJ**objeto_aux2;
                int y, tamanio2, x;
                limpiar_ventana(window2);
                for (z = 1; z < 70; z++) print_cadena_ventana(window2, "*", 1, z);
                for (z = 1; z < 70; z++) print_cadena_ventana(window2, "*", 24, z);
                for (z = 1; z < 25; z++) print_cadena_ventana(window2, "*", z, 1);
                for (z = 1; z < 25; z++) print_cadena_ventana(window2, "*", z, 68);
                print_cadena_ventana(window2, "Este es tu inventario:", 3, 3);
                list_aux2 = get_pers_list(pers[0]);
                tamanio2 = sizeOfList(list_aux2);
                objeto_aux2 = (OBJ**) malloc(tamanio2 * sizeof (OBJ*));
                for (y = 0, x = 5; y < tamanio2; y++, x++) {
                    objeto_aux2[y] = extractFirstOBJ(list_aux2);
                    print_cadena_ventana(window2, get_obj_name(objeto_aux2[y]), x, 3);
                }
                for (y = 0; y < tamanio2; y++)
                    insertFirstOBJ(list_aux2, objeto_aux2[y]);
                for (y = 0; y < tamanio2; y++)
                    destroy_obj(objeto_aux2[y]);
                free(objeto_aux2);

            }
            for (i = 0; flag == 0 && i < tabla[0]; i++)
                if (strcmp(get_obj_name(obj[i]), directo) == 0) {
                    flag = 1;
                }
            for (i = 1; flag == 0 && i < tabla[1]; i++)
                if (strcmp(get_pers_name(pers[i]), directo) == 0) {
                    flag = 2;
                }
            if (flag == 1)
                check = examinar_obj(espacio, pers[0], directo, stdout);
            else if (flag == 2)
                check = examinar_pers(pers[0], pers, directo, tabla[1], stdout);

            else
                check = ERROR;

        } else if (strcmp("dormir", verbo) == 0) {
            limpiar_ventana(window2);
            for (z = 1; z < 70; z++) print_cadena_ventana(window2, "*", 1, z);
            for (z = 1; z < 70; z++) print_cadena_ventana(window2, "*", 24, z);
            for (z = 1; z < 25; z++) print_cadena_ventana(window2, "*", z, 1);
            for (z = 1; z < 25; z++) print_cadena_ventana(window2, "*", z, 68);
            check = dormir(pers[0], stdout);
            if (check == ERROR)
                print_cadena_ventana(window2, "El personaje no se puede dormir", 5, 3);

        } else if (strcmp("despertar", verbo) == 0) {
            limpiar_ventana(window2);
            for (z = 1; z < 70; z++) print_cadena_ventana(window2, "*", 1, z);
            for (z = 1; z < 70; z++) print_cadena_ventana(window2, "*", 24, z);
            for (z = 1; z < 25; z++) print_cadena_ventana(window2, "*", z, 1);
            for (z = 1; z < 25; z++) print_cadena_ventana(window2, "*", z, 68);
            check = despertar(pers[0], stdout);
            if (check == ERROR)
                print_cadena_ventana(window2, "El personaje no se puede despertar", 5, 3);

        } else if (strcmp("guardar", verbo) == 0) {
            limpiar_ventana(window2);
            for (z = 1; z < 70; z++) print_cadena_ventana(window2, "*", 1, z);
            for (z = 1; z < 70; z++) print_cadena_ventana(window2, "*", 24, z);
            for (z = 1; z < 25; z++) print_cadena_ventana(window2, "*", z, 1);
            for (z = 1; z < 25; z++) print_cadena_ventana(window2, "*", z, 68);
            f_write = fopen("hola_elvi.txt", "w");
            if (f_write == NULL)
                return ERROR;
            check = prueba_guardar(obj, pers, espacio, tabla, f_write);
            if (check == ERROR)
                print_cadena_ventana(window2, "La partida no se pudo guardar correctamente", 4, 3);
            fclose(f_write);
            print_cadena_ventana(window2, "La partida se pudo guardar", 4, 3);

        } else if (strcmp("cargar", verbo) == 0) {
            limpiar_ventana(window2);
            for (z = 1; z < 70; z++) print_cadena_ventana(window2, "*", 1, z);
            for (z = 1; z < 70; z++) print_cadena_ventana(window2, "*", 24, z);
            for (z = 1; z < 25; z++) print_cadena_ventana(window2, "*", z, 1);
            for (z = 1; z < 25; z++) print_cadena_ventana(window2, "*", z, 68);
            f_write = fopen("hola_elvi.txt", "r");
            if (f_write == NULL)
                return ERROR;

            list = get_pers_list(pers[0]);
            tamanio = sizeOfList(list);

            if (tamanio > 0) {

                for (i = 0; i < tamanio; i++) {
                    obj_pers = extractFirstOBJ(list);
                    if ((get_obj_activado(obj_pers)) == TRUE)
                        flag2 = 1;
                }
            }

            for (i = 0; i < tabla[0]; i++)
                destroy_obj(obj[i]);
            free(obj);

            for (i = 0; i < tabla[1]; i++)
                destroy_pers(pers[i]);
            free(pers);

            for (i = 0; i < tabla[2]; i++) {
                for (j = 0; j < tabla[3]; j++)
                    if (espacio[i][j] != NULL)
                        destroyEspacio(espacio[i][j]);
                free(espacio[i]);
            }
            free(espacio);

            check = prueba_cargar(&obj, &pers, &espacio, tabla, f_write);
            if (check == ERROR)
                print_cadena_ventana(window2, "La partida no se pudo cargar correctamente", 4, 3);

            print_cadena_ventana(window2, "La partida se pudo cargar", 4, 3);
            fclose(f_write);

            if (flag2 == 1) {
                obj_pers = get_pers_obj(pers[0], "antorcha");
                set_obj_activado(obj_pers, TRUE);
                extract_pers_obj(pers[0], "antorcha");
                set_pers_obj(pers[0], obj_pers);
            }


        } else if (strcmp("salir", verbo) == 0) {
            limpiar_ventana(window2);
            for (z = 1; z < 70; z++) print_cadena_ventana(window2, "*", 1, z);
            for (z = 1; z < 70; z++) print_cadena_ventana(window2, "*", 24, z);
            for (z = 1; z < 25; z++) print_cadena_ventana(window2, "*", z, 1);
            for (z = 1; z < 25; z++) print_cadena_ventana(window2, "*", z, 68);
            print_cadena_ventana(window2, "Vaya vaya has sobrevivido... Pasa un buen dia", 10, 3);

            for (i = 0; i < tabla[0]; i++)
                destroy_obj(obj[i]);
            free(obj);

            for (i = 0; i < tabla[1]; i++)
                destroy_pers(pers[i]);
            free(pers);

            for (i = 0; i < tabla[2]; i++) {
                for (j = 0; j < tabla[3]; j++)
                    if (espacio[i][j] != NULL)
                        destroyEspacio(espacio[i][j]);
                free(espacio[i]);
            }
            free(espacio);

        } else {
            limpiar_ventana(window2);
            for (z = 1; z < 70; z++) print_cadena_ventana(window2, "*", 1, z);
            for (z = 1; z < 70; z++) print_cadena_ventana(window2, "*", 24, z);
            for (z = 1; z < 25; z++) print_cadena_ventana(window2, "*", z, 1);
            for (z = 1; z < 25; z++) print_cadena_ventana(window2, "*", z, 68);
            print_cadena_ventana(window2, "Opcion incorrecta", 10, 3);

        }

    } while (strcmp(verbo, "salir") != 0);
    return 0;
}
