/* 
 * File:   acciones.c
 * Author: Carlos Li Hu 
 *
 * Created on 30 de septiembre de 2015, 13:05
 */

#include "acciones.h"

/*
 * @BRIEF dado un mapa un personaje a mover (usualmente el jugador) y una direccion en la que moverse, 
 * se comprobara si es posible moverse en dicha direccion desde la sala en la que se encuentre el personaje en cuestión.
 * de ser posible, la ubicacion del jugador se actualizara. de lo contrario, se devolvera error
 * @PARAM el mapa de espacios. El personaje que se movera (tipicamente el jugador) y la direccion en la que desea moverse
 * @RETURN ok si ha conseguido moverse sin problemas. De lo contrario, error
 */
STATUS mover(ESPACIO*** mapa, PERS* personaje, char* direccion, FILE *f) {
    int* ubic;
    ESPACIO* espacio;
    Ventana* window2 = NULL;


    if (!mapa || !personaje || !direccion || !f) return ERROR;
    /*para que se imprima en la ventana correspondiente*/
    window2 = ini_ventana(25, 60, 0, 62);
    ubic = get_pers_ubic(personaje);
    /*comprueba si puedes moverte en esa direccion*/
    if (room_get_exit_door(mapa[ubic[0]][ubic[1]], direccion) == NULL)
        print_cadena_ventana(window2, "no te puedes mover en esa dirección", 2, 3);
    else if (get_obj_activado(room_get_exit_door(mapa[ubic[0]][ubic[1]], direccion)) == FALSE)
        print_cadena_ventana(window2, "Hay puerta en esa dirección, usa llave", 2, 3);
    else {
        espacio = room_get_room_connection(mapa[ubic[0]][ubic[1]], direccion);
        if (!espacio) {
            print_cadena_ventana(window2, "en esa dirección no hay salas", 2, 3);

            return ERROR;
        }
        set_pers_ubic(personaje, get_room_coord(espacio));
        print_cadena_ventana(window2, "te has movido correctamente", 2, 3);
        return OK;
    }
    return ERROR;

}

/*
 * @BRIEF dado un mapa, un personaje (tipicamente el jugador) y el nombre de un objeto, se buscara un objeto con ese nombre en la sala  
 * actual del personaje. de existir, el personaje copiara dicho objeto en su inventario (list) y lo eliminara de la lista de objetos de la
 * sala en la que se encuentra.
 * @PARAM el mapa de espacios, el personaje que guardara un objeto en su inventario y el nombre del objeto a buscar en la sala y guardar
 * @RETURN ok si se consiguio guardar correctamente, error si no
 */
STATUS coger(ESPACIO *** mapa, PERS* personaje, char* nombre, FILE* f) {
    int*ubic;
    List*list;
    OBJ*objeto;
    Ventana* window2 = NULL;

    if (!mapa || !personaje || !nombre || !f) return ERROR;
    /*imprime en la ventana correspondiente*/
    window2 = ini_ventana(25, 60, 0, 62);
    ubic = get_pers_ubic(personaje);
    /*obtenemos la lista de objetos del espacio*/
    list = get_room_list(mapa[ubic[0]][ubic[1]]);
    objeto = extractOBJ(list, nombre);
    if (!objeto) {
        print_cadena_ventana(window2, "el objeto no esta en la sala", 2, 3);
        return ERROR;
    }
    /*obtenemos la lista de objetos del personaje*/
    list = get_pers_list(personaje);
    insertFirstOBJ(list, objeto);

    return OK;
}

/*
 * @BRIEF dado un mapa, un personaje(tipicamente el jugador) y el nombre de un objeto, se buscara un objeto con ese nombre en el  
 * inventario del personaje (una lista) y de existir, se eliminara de su inventario y se insertara en la lista de objetos de la sala en  
 * la que se encuentra
 * @PARAM el mapa de espacios, el personaje que dejara un objeto de su inventario (tipicamente el jugador) y el nombre del objeto
 * @RETURN ok si se "traslado" el objeto desde el inventario del personaje hasta el espacio. error de lo contrario
 */
STATUS dejar(ESPACIO *** mapa, PERS* personaje, char* nombre, FILE* f) {
    int*ubic;
    List*list;
    OBJ*objeto;
    Ventana* window2 = NULL;
    if (!mapa || !personaje || !nombre || !f) return ERROR;
    /*imprime en la ventana correspondiente*/
    window2 = ini_ventana(25, 60, 0, 62);
    /*obtenemos la ubicacion del personaje*/
    ubic = get_pers_ubic(personaje);
    /*obtenemos la lista del personaje*/
    list = get_pers_list(personaje);
    objeto = extractOBJ(list, nombre);
    if (!objeto) {
        print_cadena_ventana(window2, "el objeto no esta en el inventario", 2, 3);
        return ERROR;
    }
    insertFirstOBJ(get_room_list(mapa[ubic[0]][ubic[1]]), objeto);

    return OK;
}

/*
 * @BRIEF dado un personaje (tipicamente el jugador) y el nombre de un objeto, se buscara en el inventario del personaje dicho objeto
 * y de existir, se "encendera" de ser posible. (esta funcion solo actuara sobre objetos como linterna, antorcha, etc. que basicamente  
 * sirvan para iluminar).
 * @PARAM el personaje que encendera el objeto (cuyo nombre se especifica en el segundo argumento)
 * @RETURN devuleve ok si se consigue encender el objeto. error en cualquier otro caso (e.j. que el jugador no tenga ese objeto)
 */
STATUS encender(PERS* personaje, char*nombre, FILE* f) {
    OBJ* objeto = NULL, *objeto2;
    Ventana* window2 = NULL;
    if (!personaje || !nombre || !f)
        return ERROR;
    /*imprime en la ventana correspondiente*/
    window2 = ini_ventana(25, 60, 0, 62);
    objeto = get_pers_obj(personaje, nombre);
    if (!objeto || get_obj_ilum(objeto) == FALSE) {
        print_cadena_ventana(window2, "Este objeto no ilumina", 2, 3);
        return ERROR;
    }
    if (get_obj_activado(objeto) == TRUE) {
        print_cadena_ventana(window2, "El objeto ya está activado", 3, 3);
        return OK;
    }

    if (set_obj_activado(objeto, TRUE)) {
        print_cadena_ventana(window2, "el objeto no se puede encender", 4, 3);
        return ERROR;
    }
    /*obtenemos el objeto que queremos encender*/
    objeto2 = extract_pers_obj(personaje, nombre);
    if (objeto2 == NULL)
        return ERROR;
    if (set_pers_obj(personaje, objeto)) {
        destroy_obj(objeto2);
        return ERROR;
    }
    destroy_obj(objeto2);
    return OK;
}

/*
 * @BRIEF dado un personaje (tipicamente el jugador) y el nombre de un objeto, se buscara en el inventario del personaje dicho objeto
 * y de existir, se "apagara" de ser posible. (esta funcion solo actuara sobre objetos como linterna, antorcha, etc. que basicamente  
 * sirvan para iluminar)
 * @PARAM el personaje que apagara el objeto (cuyo nombre se especifica en el segundo argumento)
 * @RETURN devuleve ok si se consigue encender el objeto. error en cualquier otro caso (e.j. que el jugador no tenga ese objeto)
 */
STATUS apagar(PERS* personaje, char*nombre, FILE *f) {
    OBJ* objeto = NULL, *objeto2;
    Ventana* window2 = NULL;
    if (!personaje || !nombre || !f)
        return ERROR;
    /*imprime en la ventana correspondiente*/
    window2 = ini_ventana(25, 60, 0, 62);
    objeto = get_pers_obj(personaje, nombre);
    if (!objeto || get_obj_ilum(objeto) == FALSE) {
        print_cadena_ventana(window2, "Este objeto no ilumina", 2, 3);
        return ERROR;
    }
    if (get_obj_activado(objeto) == FALSE) {
        print_cadena_ventana(window2, "Este objeto ya esta apagado", 3, 3);
        return OK;
    }

    if (set_obj_activado(objeto, FALSE)) {
        print_cadena_ventana(window2, "El objeto no se puede apagar", 4, 3);
        return ERROR;
    }
    /*obtenemos el objeto que queremos apagar*/
    objeto2 = extract_pers_obj(personaje, nombre);
    if (objeto2 == NULL)
        return ERROR;
    if (set_pers_obj(personaje, objeto)) {
        destroy_obj(objeto2);
        return ERROR;
    }
    destroy_obj(objeto2);
    return OK;
}

/*
 * @BRIEF dado el mapa de espacios, un personaje (tipicamente el jugador) y la direccion en la que se encuentra la puerta que quiera  
 * abrirse, siempre, claro esta, en la sala en la que se encuentre el personaje, se abrira la puerta de la sala en la direccion  
 * especificada cabe la posibilidad de que cierta puerta solo pueda ser abierta bajo ciertas circunstancias (usualmente que el jugador  
 * posea una llave en su inventario, la cual se usara automaticamente sin necesidad de ser especificado por el usuario). Tras esto, toda  
 * llave que haya sido empleada, SE ELIMINARA del inventario del jugador
 * @PARAM el mapa de los espacios, el personaje (tipicamente el jugador) y la direccion en la que abrir la puerta
 * @RETURN ok si se abrio la puerta, error si no se abrio
 */
STATUS abrir_puerta(ESPACIO*** mapa, PERS* personaje, char* direccion, char*obj, FILE*f) {
    int *ubic;
    OBJ* objeto, *puerta;
    Ventana* window2 = NULL;

    if (!mapa || !personaje || !direccion || !f) return ERROR;
    /*imprime en la ventana correspondiente*/
    window2 = ini_ventana(25, 60, 0, 62);
    /*obtenemos la ubicacion del personaje*/
    ubic = get_pers_ubic(personaje);
    /*obtenemos la puerta que hay en la direccion indicada*/
    puerta = room_get_exit_door(mapa[ubic[0]][ubic[1]], direccion);
    if (!puerta)
        print_cadena_ventana(window2, "Tu, que no hay puertas ahi", 2, 3);
    else {
        if (strcmp(obj, "llave_zanahoria") != 0) {
            print_cadena_ventana(window2, "solo puedes abrir puertas con una llave -.-", 2, 3);
        }
        objeto = extract_pers_obj(personaje, "llave_zanahoria");
        if (!objeto)
            print_cadena_ventana(window2, "No tienes llaves, así que te fastidias XD", 3, 3);
        else {
            /*abrimos la puerta*/
            set_obj_activado(puerta, 1);
            print_cadena_ventana(window2, "La puerta ha sido abierta", 3, 3);
            if (strcmp("norte", direccion) == 0)
                set_obj_activado(room_get_exit_door(room_get_room_connection(mapa[ubic[0]][ubic[1]], direccion), "sur"), 1);
            else if (strcmp("sur", direccion) == 0)
                set_obj_activado(room_get_exit_door(room_get_room_connection(mapa[ubic[0]][ubic[1]], direccion), "norte"), 1);
            else if (strcmp("este", direccion) == 0)
                set_obj_activado(room_get_exit_door(room_get_room_connection(mapa[ubic[0]][ubic[1]], direccion), "oeste"), 1);
            else if (strcmp("oeste", direccion) == 0)
                set_obj_activado(room_get_exit_door(room_get_room_connection(mapa[ubic[0]][ubic[1]], direccion), "este"), 1);
            else
                return ERROR;
        }

    }
    return OK;
}

/*
 * @BRIEF dado el mapa de espacios, un personaje (el jugador) y el nombre de un objeto, se buscara el objeto con el nombre especificado
 * primero en el inventario del jugador y de no encontrarse ahi, en los objetos que haya en la sala. De encontrarse en alguno de esos  
 * lugares, se imprimira por pantalla el dialogo de dicho objeto (por muy raro que pueda sonar)
 * @PARAM el mapa de espacios, el personaje (jugador) y el nombre del objeto con el que se desea hablar.
 * @RETURN devuelve ok si el dialogo del objeto fue mostrado por pantalla y error en cualquier otro caso
 */
STATUS talk_obj(ESPACIO*** mapa, PERS* personaje, char* nombre, FILE *f) {
    OBJ* objeto, *objeto2;
    List*list;
    int*ubic;
    Ventana* window2 = NULL;
    if (!mapa || !personaje || !nombre || !f) return ERROR;
    /*imprimimos en la ventana correspondiente*/
    window2 = ini_ventana(25, 60, 0, 62);
    /*obtenemos el objeto del personaje*/
    objeto = get_pers_obj(personaje, nombre);
    if (objeto)
        print_cadena_ventana(window2, get_obj_dial(objeto), 2, 3);
    else {
        ubic = get_pers_ubic(personaje);
        if (!ubic) {
            destroy_obj(objeto);
            return ERROR;
        }
        list = get_room_list(mapa[ubic[0]][ubic[1]]);
        if (!list) {
            destroy_obj(objeto);
            return ERROR;
        }
        objeto2 = extractOBJ(list, nombre);
        if (!objeto2) {
            destroy_obj(objeto);
            return ERROR;
        }
        print_cadena_ventana(window2, get_obj_dial(objeto2), 3, 3);
        insertFirstOBJ(list, objeto2);
        destroy_obj(objeto2);
    }
    destroy_obj(objeto);

    return OK;
}

/*
 * @BRIEF dado un personaje(jugador) la lista de todos los personajes del juego y el nombre del personaje con el que se desea hablar, 
 * se comprobara uno a uno si se encuentran en la misma sala que el jugador y de ser asi si tienen el nombre especificado. Si se cumplen  
 * ambos requisitos, se imprimira por pantalla el dialogo de dicho personaje
 * @PARAM el jugador, la lista de todos los personajes del juego ,el nombre del personaje con el que se desea hablar, el número de  
 * personajes en la lista, f de escritura
 * @RETURN ok si se ha impreso por pantalla el dialogo deseado, error de lo contrario
 */
STATUS talk_persona(PERS* jugador, PERS** personajes, char* nombre, int num_personajes, FILE* f) {
    int i, *aux, *aux2;
    Ventana* window2 = NULL;
    if (!jugador || !personajes || !nombre || !f) return ERROR;
    /*imprimimos en la ventana correspondiente*/
    window2 = ini_ventana(25, 60, 0, 62);
    /*hablamos con la persona elegida*/
    for (i = 0; i < num_personajes; i++) {
        if (strcmp(nombre, get_pers_name(personajes[i])) == 0) {
            aux = get_pers_ubic(personajes[i]);
            aux2 = get_pers_ubic(jugador);

            if (aux[0] == aux2[0] && aux[1] == aux2[1])
                print_cadena_ventana(window2, get_pers_dial(personajes[i]), 4, 3);
        }
    }
    return OK;
}

/*
 * @BRIEF dado un personaje (el jugador) y el nombre de un objeto, se buscara un objeto con dicho nombre en el inventario
 * del jugador. De encontrarlo, se imprimira por pantalla su descripcion y su estado, si no, pues se buscará en el espacio donde se   
 * encuentra.
 * @PARAM un personaje (el jugador) y el nombre de un objeto
 * @RETURN ok si se pudo imprimir por pantalla la descripcion del objeto. error de lo contrario
 */
STATUS examinar_obj(ESPACIO*** mapa, PERS* jugador, char* nombre, FILE* f) {
    OBJ*objeto, *objeto2;
    int*ubic;
    List* list;
    Ventana* window2 = NULL;
    if (!mapa || !jugador || !nombre || !f) return ERROR;
    window2 = ini_ventana(25, 60, 0, 62);
    /*obtenemos el objeto a examinar*/
    objeto = get_pers_obj(jugador, nombre);
    if (objeto)
        print_cadena_ventana(window2, get_obj_descr(objeto), 4, 3);
    else {
        ubic = get_pers_ubic(jugador);
        if (!ubic)
            return ERROR;
        list = get_room_list(mapa[ubic[0]][ubic[1]]);
        if (!list)
            return ERROR;
        objeto2 = extractOBJ(list, nombre);
        if (!objeto2)
            return ERROR;
        /*imprimimos la descripcion del objeto*/
        print_cadena_ventana(window2, get_obj_descr(objeto2), 5, 3);
        if (insertFirstOBJ(list, objeto2) == ERROR)
            return ERROR;
        destroy_obj(objeto2);
    }
    destroy_obj(objeto);

    return OK;
}

/*
 * @BRIEF dada la lista de todos los personajes del juego, el personaje (jugador) y el nombre del personaje al que examinar,
 * se comprobara uno a uno si se encuentran en la misma sala que el jugador y de ser asi si tienen el nombre especificado. Si se cumplen  
 * ambos requisitos, se imprimira por pantalla la descripcion de dicho personaje
 * @PARAM la lista de todos los personajes del juego, el personaje (jugador) y el nombre del personaje con el que se desea hablar
 * @RETURN ok si se imprimio por pantalla la descripcion deseada, error de lo contrario
 */
STATUS examinar_pers(PERS* jugador, PERS** personajes, char* nombre, int num_personajes, FILE*f) {
    int i, *aux, *aux2;
    Ventana *window2 = NULL;
    if (!jugador || !personajes || !nombre || !f) return ERROR;
    window2 = ini_ventana(25, 60, 0, 62);
    /*comprobamos que el personaje este en el espacio*/
    for (i = 0; i < num_personajes; i++) {
        if (strcmp(nombre, get_pers_name(personajes[i])) == 0) {
            aux = get_pers_ubic(personajes[i]);
            aux2 = get_pers_ubic(jugador);

            if (aux[0] == aux2[0] && aux[1] == aux2[1])
                /*imprimimos la descripcion del personaje*/
                print_cadena_ventana(window2, get_pers_descr(personajes[i]), 4, 3);
        }
    }
    return OK;
}

/*
 * @BRIEF dado el mapa de espacios y un personaje (el jugador), se imprimira por pantalla la descripcion de la sala en la que se encuentre
 * el jugador.
 * @PARAM el mapa de espacios y el personaje (jugador)
 * @RETURN ok si se imprimio por pantalla la descripcion del espacio. error de lo contrario
 */
STATUS examinar_esp(ESPACIO*** mapa, PERS* jugador, FILE*f) {
    int *ubic, i;
    OBJ* aux;
    Ventana* window1 = NULL;
    char**direcciones;
    if (!mapa || !jugador || !f) return ERROR;
    /*imprimos en la ventana correspondiente la descripcion del espacio*/
    window1 = ini_ventana(25, 60, 0, 0);
    ubic = get_pers_ubic(jugador);
    direcciones = (char**) malloc(4 * sizeof (char*));
    /*comprobamos si el espacio esta iluminado o no o si el personaje lleva una antorcha encendida*/
    if (get_room_estado(mapa[ubic[0]][ubic[1]]) == 1)/*iluminado*/ {
        print_cadena_ventana(window1, get_room_descr(mapa[ubic[0]][ubic[1]]), 2, 3);
        room_get_exit_directions(mapa[ubic[0]][ubic[1]], direcciones);
        print_cadena_ventana(window1, "las direcciones disponibles son:", 19, 3);
        for (i = 0; i < 4; i++)
            if (direcciones[i])
                print_cadena_ventana(window1, direcciones[i], 20 + i, 3);
        free(direcciones);
    } else if (get_room_estado(mapa[ubic[0]][ubic[1]]) == 2)/*lloviendo*/ {
        print_cadena_ventana(window1, get_room_descr(mapa[ubic[0]][ubic[1]]), 2, 3);
        room_get_exit_directions(mapa[ubic[0]][ubic[1]], direcciones);
        print_cadena_ventana(window1, "las direcciones disponibles son:", 19, 3);
        for (i = 0; i < 4; i++)
            if (direcciones[i])
                print_cadena_ventana(window1, direcciones[i], 20 + i, 3);
        free(direcciones);

    } else if (get_room_estado(mapa[ubic[0]][ubic[1]]) == 0) { /*apagado*/
        aux = get_pers_obj(jugador, "antorcha");
        if (aux) {
            if (get_obj_activado(aux) == FALSE) {
                print_cadena_ventana(window1, "El espacio no esta iluminado", 4, 3);
                destroy_obj(aux);
                return MAS_MENOS;
            }
            print_cadena_ventana(window1, get_room_descr(mapa[ubic[0]][ubic[1]]), 2, 3);
            room_get_exit_directions(mapa[ubic[0]][ubic[1]], direcciones);
            print_cadena_ventana(window1, "las direcciones disponibles son:", 19, 3);
            for (i = 0; i < 4; i++)
                if (direcciones[i])
                    print_cadena_ventana(window1, direcciones[i], 20 + i, 3);
            free(direcciones);
            destroy_obj(aux);

        } else {
            print_cadena_ventana(window1, "El espacio no esta iluminado", 4, 3);
            return MAS_MENOS;
        }
    } else {
        print_cadena_ventana(window1, "El espacio no esta iluminado", 2, 3);
        return MAS_MENOS;
    }
    return OK;
}

/*
 * @BRIEF dado un personaje (jugador) si se encuentra actualmente fuera de la mazmorra (su ubicacion x es mayor que 6) se "dormira" y
 * sera transportado automaticamente a la sala 3,3 dela mazmorra.
 * @PARAM el personaje (jugador) que se "dormira" y sera transportado a la sala 3,3
 * @RETURN ok si se llego a dicha sala. error de lo contrario
 */
STATUS dormir(PERS* jugador, FILE* f) {
    int*ubic, ubic2[2] = {1, 2};
    Ventana* window2 = NULL;
    if (!jugador || !f) return ERROR;
    /*imprimimos en la ventana correspondiente*/
    window2 = ini_ventana(25, 60, 0, 62);
    /*comprobamos que el personaje pueda dormir en esa sala*/
    ubic = get_pers_ubic(jugador);
    if (ubic[0] < 3)
        print_cadena_ventana(window2, "Ya estás dormido", 2, 3);
    else
        set_pers_ubic(jugador, ubic2);

    return OK;
}

/*
 * @BRIEF dado un personaje, se comprobara si en su inventario posee on objeto que seria capaz de despertarlo (p.e. un despertador (duh))
 * en caso de que lo posea Y se encuentre actualmente en la mazmorra (su ubicacion x sea menor que 6) se "despertara" y sera transportado
 * automaticamente a la sala que sera su dormitorio << AUN POR DETERMINAR >>. Tras esto, el objeto SERA ELIMINADO del inventario del  
 * jugador
 * @PARAM el personaje (jugador) que se despertara si cumple las condiciones necesarias
 * @RETURN ok si se desperto sin problemas, error de lo contrario
 */
STATUS despertar(PERS* jugador, FILE*f) {
    int ubic[2] = {3, 3};
    OBJ* objeto = NULL;
    Ventana* window2 = NULL;
    if (!jugador || !f) return ERROR;
    /*imprimimos en la ventana correspondiente*/
    window2 = ini_ventana(25, 60, 0, 62);
    if (get_pers_ubic(jugador)[0] > 2) {
        print_cadena_ventana(window2, "Estás ya despierto madafaka", 2, 3);
        return ERROR;
    }
    /*comprobamos que el personaje tenga un despertador para poder despertarse*/
    objeto = extract_pers_obj(jugador, "despertador");
    if (!objeto)
        print_cadena_ventana(window2, "No posees un despertador", 3, 3);
    else {
        destroy_obj(objeto);
        set_pers_ubic(jugador, ubic);
    }
    return OK;
}
