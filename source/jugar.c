/* 
 * File:   jugar.c
 * Author: Elvira Vegas && Carlos Li Hu && David Lopez
 *
 * Created on 26 de noviembre de 2015, 19:00
 */

#include "reglas.h"
#include "interprete.h"
#include "gestor.h"

#define DIM 10

int main() {
    List* list, * list_esp;
    OBJ** obj = NULL, *obj_pers = NULL, **objeto_esp; /* array con todos los objetos del juego*/
    PERS** pers = NULL; /*array con todos los personajes del juego*/
    ESPACIO*** espacio = NULL; /*array con el mapa del juego*/
    int tabla[4], tamanio, i = 0, b, j = 0, flag, num_part = 0,
            flag2, * aux = NULL, *aux2 = NULL, num_sin[DIM], q; /*array con el número de objetos 0, el numero de personajes 1, el numero de espacios: filas 2; columnas 3*/
    FILE* fichero = NULL, *f_part, *f_sin, *f_write, *f_reglas; /*fichero con los datos del juego, fichero con las particulas a eliminar y fichero con los sinonimos, fichero para guardar o cargar la partida*/
    STATUS check; /*variable para ir checkeando el codigo*/
    char verbo[30], directo[30], indirecto[30], comando[50], nombre[50]; /*variable donde se guarda el verbo, el directo, el indirecto y el comando del usuario*/
    char** part = NULL, *** sin = NULL, *** regla;
    Ventana* window_total = NULL, * window1 = NULL, * window2 = NULL, * window3 = NULL;

    /*inicializamos la pantalla inicial*/
    check = print_pantalla_inicial(&window_total, &window1, &window2, &window3);

    /*comprobamos si la ventana es visible o no*/
    check = pantalla_visible(&window1, &window2, &window3);
    if (check == ERROR)
        return -1;

    /*limpiamos la pantalla*/
    check = limpiar_pantalla(&window_total, &window1, &window2, &window3);
    if (check == ERROR)
        return -1;

    /*abrimos los ficheros del juego*/
    check = abrir_ficheros(&fichero, &obj, &pers, &espacio, tabla, &f_part, &f_sin, &f_reglas);
    if (check == ERROR)
        return -1;

    fscanf(f_part, "%d", &num_part);
    part = (char**) malloc(num_part * sizeof (char*));
    if (!part)
        return ERROR;
    for (i = 0; i < num_part; i++) {
        part[i] = (char*) malloc(27 * sizeof (char));
        fscanf(f_part, "%s", part[i]);
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

    regla = leer_condiciones(f_reglas, 4);

    cerrar_ficheros(&fichero, &f_sin, &f_part, &f_reglas);

    print_marco_ventana_pequena(window2, '*');
    print_bienvenida(&window2);
    print_sala_inicial(pers, &window1, espacio);

    do {
        /*se comprueban las reglas en cada accion y si hay final de juego o no*/
        reglas(regla, 4, espacio, pers, obj);
        print_final_juego(pers, espacio, &window2);

        /*por cada accion llamamos a su funcion asociada, imprimimos en la 
         * ventana correspondiente y limpiamos la ventana si es necesario*/
        print_comando(&window3);

        fgets(comando, 50, stdin);
        strtok(comando, "\n");
        interprete(comando, verbo, directo, indirecto, part, sin, num_part, num_sin);

        if (strcmp("mover", verbo) == 0) {
            limpiar_ventana(window2);
            print_marco_ventana_pequena(window2, '*');
            mover(espacio, pers[0], directo, stdout);
            limpiar_ventana(window1);
            print_marco_ventana_pequena(window1, '*');
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
                b = 11;
                for (i = 1; i < tabla[1]; i++) {
                    aux2 = get_pers_ubic(pers[i]);

                    if (aux[0] == aux2[0] && aux[1] == aux2[1]) {
                        print_cadena_ventana(window1, "Personajes de la sala:", 10, 3);
                        print_cadena_ventana(window1, get_pers_name(pers[i]), b, 3);
                        b++;
                    }
                }
            }

        } else if (strcmp("coger", verbo) == 0) {
            limpiar_ventana(window2);
            print_marco_ventana_pequena(window2, '*');
            check = coger(espacio, pers[0], directo, stdout);
            if (check == ERROR)
                print_cadena_ventana(window2, "No puedes coger ese objeto", 3, 3);
            else {
                print_cadena_ventana(window2, "Has cogido el objeto correctamente", 3, 3);
                limpiar_ventana(window1);
                print_marco_ventana_pequena(window1, '*');
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

        } else if (strcmp("dejar", verbo) == 0) {
            limpiar_ventana(window2);
            print_marco_ventana_pequena(window2, '*');
            check = dejar(espacio, pers[0], directo, stdout);
            if (check == ERROR)
                print_cadena_ventana(window2, "No puedes dejar ese objeto.", 3, 3);
            else {
                print_cadena_ventana(window2, "Has dejado el objeto correctamente", 3, 3);
                limpiar_ventana(window1);
                print_marco_ventana_pequena(window1, '*');
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
        } else if (strcmp("encender", verbo) == 0) {
            limpiar_ventana(window2);
            print_marco_ventana_pequena(window2, '*');
            check = encender(pers[0], directo, stdout);
            if (check == ERROR)
                print_cadena_ventana(window2, "No puedes encender ese objeto.", 5, 3);
            else {
                print_cadena_ventana(window2, "has encendido el objeto correctamente o ya estaba encendido", 5, 3);
                limpiar_ventana(window1);
                print_marco_ventana_pequena(window1, '*');
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
        } else if (strcmp("apagar", verbo) == 0) {
            limpiar_ventana(window2);
            print_marco_ventana_pequena(window2, '*');
            check = apagar(pers[0], directo, stdout);
            if (check == ERROR)
                print_cadena_ventana(window2, "No puedes apagar ese objeto.", 5, 3);
            else {
                print_cadena_ventana(window2, "has apagado el objeto correctamente.", 5, 3);
                limpiar_ventana(window1);
                print_marco_ventana_pequena(window1, '*');
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
        } else if (strcmp("abrir", verbo) == 0) {
            limpiar_ventana(window2);
            print_marco_ventana_pequena(window2, '*');
            if (abrir_puerta(espacio, pers[0], indirecto, directo, stdout) == ERROR)
                print_cadena_ventana(window2, "El personaje no puede abrir esa puerta", 4, 3);

        } else if (strcmp("hablar", verbo) == 0) {
            flag = 0;
            limpiar_ventana(window2);
            print_marco_ventana_pequena(window2, '*');
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
                print_marco_ventana_pequena(window1, '*');
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
                    b = 11;
                    for (i = 1; i < tabla[1]; i++) {
                        aux2 = get_pers_ubic(pers[i]);

                        if (aux[0] == aux2[0] && aux[1] == aux2[1]) {
                            print_cadena_ventana(window1, "Personajes de la sala:", 10, 3);
                            print_cadena_ventana(window1, get_pers_name(pers[i]), b, 3);
                            b++;
                        }
                    }
                }
            }
            if (strcmp("inventario", directo) == 0) {
                List* list_aux2/*=iniList()*/;
                OBJ**objeto_aux2;
                int y, tamanio2, x;
                limpiar_ventana(window2);
                print_marco_ventana_pequena(window2, '*');
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
            if (flag == 1) {
                limpiar_ventana(window2);
                print_marco_ventana_pequena(window2, '*');
                check = examinar_obj(espacio, pers[0], directo, stdout);
            } else if (flag == 2) {
                limpiar_ventana(window2);
                print_marco_ventana_pequena(window2, '*');
                check = examinar_pers(pers[0], pers, directo, tabla[1], stdout);
            } else
                check = ERROR;

        } else if (strcmp("dormir", verbo) == 0) {
            if (get_pers_ubic(pers[0])[0] == 3 && get_pers_ubic(pers[0])[1] == 0) {
                limpiar_ventana(window2);
                print_marco_ventana_pequena(window2, '*');
                dormir(pers[0], stdout);
                print_cadena_ventana(window2, "El personaje se ha dormido", 5, 3);
                limpiar_ventana(window1);
                print_marco_ventana_pequena(window1, '*');
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
                    b = 11;
                    for (i = 1; i < tabla[1]; i++) {
                        aux2 = get_pers_ubic(pers[i]);

                        if (aux[0] == aux2[0] && aux[1] == aux2[1]) {
                            print_cadena_ventana(window1, "Personajes de la sala:", 10, 3);
                            print_cadena_ventana(window1, get_pers_name(pers[i]), b, 3);
                            b++;
                        }
                    }
                }
            } else {
                limpiar_ventana(window2);
                print_marco_ventana_pequena(window2, '*');
                print_cadena_ventana(window2, "El personaje no se puede dormir aquí", 5, 3);
            }
        } else if (strcmp("despertar", verbo) == 0) {
            if (get_pers_ubic(pers[0])[0] == 2 && get_pers_ubic(pers[0])[1] == 0) {
                limpiar_ventana(window2);
                print_marco_ventana_pequena(window2, '*');
                despertar(pers[0], stdout);
                print_cadena_ventana(window2, "SE ACABÓ EL JUEGO, tus albondigas esperan", 5, 3);
                if (get_pers_ubic(pers[0])[0] == 3 && get_pers_ubic(pers[0])[1] == 3)
                    return OK;


            } else {
                limpiar_ventana(window2);
                print_marco_ventana_pequena(window2, '*');
                print_cadena_ventana(window2, "El personaje no se puede despertar en esta sala", 5, 3);
            }
        } else if (strcmp("guardar", verbo) == 0) {
            limpiar_ventana(window2);
            print_marco_ventana_pequena(window2, '*');
            print_cadena_ventana(window2, "Introduce un nombre para guardar partida:", 3, 3);
            fgets(nombre, 50, stdin);
            strtok(nombre, "\n\r");
            f_write = fopen(nombre, "w");
            if (f_write == NULL)
                return ERROR;
            if (guardar(obj, pers, espacio, tabla, f_write) == ERROR)
                print_cadena_ventana(window2, "La partida no se pudo guardar correctamente", 4, 3);
            else
                print_cadena_ventana(window2, "La partida se pudo guardar", 4, 3);
            fclose(f_write);


        } else if (strcmp("cargar", verbo) == 0) {
            limpiar_ventana(window2);
            print_marco_ventana_pequena(window2, '*');
            print_cadena_ventana(window2, "Introduzca el nombre de la partida que se desea cargar:", 3, 3);
            fgets(nombre, 50, stdin);
            strtok(nombre, "\n\r");
            f_write = fopen(nombre, "r");
            if (f_write == NULL)
                print_cadena_ventana(window2, "El fichero no existe", 6, 3);
            list = get_pers_list(pers[0]);
            tamanio = sizeOfList(list);
            if (tamanio > 0) {
                for (i = 0; i < tamanio; i++) {
                    obj_pers = extractFirstOBJ(list);
                    if ((get_obj_activado(obj_pers)) == TRUE)
                        flag2 = 1;
                }
            }

            /*liberamos la memoria porque en la funcion cargar volvemos a reservarla*/
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

            if (cargar(&obj, &pers, &espacio, tabla, f_write) == ERROR)
                print_cadena_ventana(window2, "La partida no se pudo cargar correctamente", 4, 3);
            else
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
            print_marco_ventana_pequena(window2, '*');
            print_cadena_ventana(window2, "Vaya vaya has sobrevivido... Pasa un buen dia", 10, 3);

            /*liberamos toda la memoria*/
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
            free_reglas(regla, 4);

        } else {
            limpiar_ventana(window2);
            print_marco_ventana_pequena(window2, '*');
            print_cadena_ventana(window2, "Opcion incorrecta", 10, 3);
        }
    } while (strcmp(verbo, "salir") != 0);
    return 0;
}
