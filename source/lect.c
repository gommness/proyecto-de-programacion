/* 
 * File:   lect.c
 * Author: Javier Gomez 
 */

#include "lect.h"

/*
 * @BRIEF reserva memoria para un personaje, inicializa sus campos leyendolos del fichero
 * @PARAM el fichero del que leer, la mega-tabla de objetos de donde buscar los objetos que pueda tener el personaje y el numero de  
 * objetos de dicha mega-tabla
 * @RETURN el personaje con memoria ya inicializada
 */
PERS* leer_personaje(FILE* file, OBJ*** objetos, int n_objs) {
    PERS* pers;
    char * token;
    char c;
    char line[500];
    int ubic[2], i;

    /*asumo que file ha sido abierto en modo "r" desde la funcion que llamara a esta otra funcion*/

    if (!file || !objetos)return NULL;
    pers = ini_pers();
    if (!pers)return NULL;

    /*lee cada campo del personaje*/
    fscanf(file, "%s\n", line);
    set_pers_name(pers, line);
    fgets(line, 500, file);
    set_pers_descr(pers, line);
    fgets(line, 500, file);
    set_pers_dial(pers, line);
    /*fgets(line,500,file);*/
    fscanf(file, "[%d,%d]\n", &ubic[0], &ubic[1]);
    set_pers_ubic(pers, ubic);
    fgets(line, 500, file);
    c = line[0];
    while (c != '\n' && c != '\r') {
        if (strcmp(line, "X") != 0) {
            token = strtok(line, "\n\r");
            for (i = 0; i < n_objs; i++) {
                if (!strcmp(get_obj_name(objetos[0][i]), token)) {
                    set_pers_obj(pers, objetos[0][i]);
                    break;
                }
            }
        }
        fgets(line, 500, file);
        c = line[0];
    }
    return pers;
}

/*
 * @BRIEF lee todos y cada uno de los personajes, los inicializa y los introduce en la mega-tabla de personajes
 * @PARAM el archivo del que leer, las mega-tablas personajes y objetos y el  numero de objetos de la mega-tabla objetos
 * @RETURN ok si consigue leerlos todos, error si ocurre algun problema
 */
int leer_personajes(FILE* file, PERS*** personajes, OBJ*** objetos, int n_objs) {
    int n_pers, i;

    if (!file || !objetos)
        return -1;
    /*leemos el numero de personajes que hay en el juego*/
    fscanf(file, "%d\n", &n_pers);
    *personajes = (PERS**) malloc(sizeof (PERS*) * n_pers);
    for (i = 0; i < n_pers; i++)
        personajes[0][i] = leer_personaje(file, objetos, n_objs);
    return n_pers;
}

/*
 * @BRIEF reserva memoria para un objeto e inicializa todos sus campos leyendolos del fichero
 * @PARAM el archivo del que leer
 * @RETURN el objeto con memoria ya inicializada
 */
OBJ* leer_objeto(FILE* file) {
    OBJ* obj;
    char line[250];
    if (!file)return NULL;
    obj = ini_obj();
    if (!obj)return NULL;

    /*leemos cada campo del objeto*/
    fscanf(file, "%s", line);
    set_obj_name(obj, line);
    fgets(line, 250, file);
    fgets(line, 250, file);
    set_obj_descr(obj, line);
    fgets(line, 250, file);
    set_obj_dial(obj, line);
    fgets(line, 250, file);
    if (strcmp(line, "X") != 0)
        set_obj_cogible(obj, atoi(line));
    fgets(line, 250, file);
    if (strcmp(line, "X") != 0)
        set_obj_activable(obj, atoi(line));
    fgets(line, 250, file);
    if (strcmp(line, "X") != 0)
        set_obj_ilum(obj, atoi(line));
    fgets(line, 250, file);
    if (strcmp(line, "X") != 0)
        set_obj_activado(obj, atoi(line));
    fgetc(file);
    fgetc(file);
    return obj;
}

/*
 * @BRIEF lee todos y cada uno de los objetos y los introduce en la mega-tabla objetos
 * @PARAM el fichero del que leer y la mega-tabla en la que meter los objetos
 * @RETURN el numero de objetos que han sido leidos
 */
int leer_objetos(FILE* file, OBJ*** objetos) {
    int n_objs, i;
    if (!file)return 0;

    /*leemos el numero de objetos que hay en el juego*/
    fscanf(file, "%d\n", &n_objs);
    *objetos = (OBJ**) malloc(sizeof (OBJ*) * n_objs);
    if (!objetos)return 0;
    for (i = 0; i < n_objs; i++)
        objetos[0][i] = leer_objeto(file);
    return n_objs;
}

/*
 * @BRIEF reserva memoria para un espacio y rellena sus campos leyendolos del fichero
 * @PARAM el fichero del que leer, la mega-tabla de objetos donde buscar los objetos que se encuentren en la habitacion, el numero de  
 * objetos de dicha tabla y la mega-tabla de espacios (mapa) de donde se van a referenciar las salas "conexion" del espacio leido y donde 
 * se va a introducir el espacio leido
 * @RETURN ok si todo fue bien, error si hubo algun fallo a lo largo del proceso
 */
STATUS leer_espacio(FILE* file, OBJ*** objetos, int n_objs, ESPACIO*** mapa) {
    ESPACIO* pers;
    OBJ* obj;
    char line[250], line2[250];
    char descr [1000], c;
    char * exit, * exit2;
    int ubic[2], coords[2], i, k, aux;
    ubic[0] = 0;
    ubic[1] = 0;
    coords[0] = 0;
    coords[1] = 0;

    /*asumo que file ha sido abierto en modo "r" desde la funcion que llamara a esta otra funcion*/

    if (!file || !objetos || !mapa)return ERROR;
    /*leemos cada campo del espacio*/
    fscanf(file, "[%d,%d]\n", &ubic[0], &ubic[1]);
    pers = mapa[ubic[0]][ubic[1]];
    if (!pers)return ERROR;
    room_set_coords(pers, ubic);
    fgets(line, 250, file);
    fgets(line, 250, file);
    if (line != NULL)
        strcpy(descr, line);
    fgets(line, 250, file);
    c = line[0];
    while (c != 'X') {
        strcat(descr, line);
        fgets(line, 250, file);
        c = line[0];
    }
    room_set_descr(pers, descr);
    fgets(line, 250, file);
    if (line[0] == 'o' && line[1] == 's' && line[2] == 'c')
        room_set_estado(pers, 0);
    else if (line[0] == 'l' && line[1] == 'u' && line[2] == 'z')
        room_set_estado(pers, 1);
    else if (line[0] == 'l' && line[1] == 'l' && line[2] == 'u')
        room_set_estado(pers, 2);
    fgets(line, 250, file);
    fscanf(file, "%s\r\n", line);
    c = line[0];
    while (c != 'X') {
        for (i = 0; i < n_objs; i++) {
            if (strcmp(get_obj_name(objetos[0][i]), line) == 0) {
                room_insert_in_objlist(pers, objetos[0][i]);
                break;
            }
        }
        fscanf(file, "%s\r\n", line);
        c = line[0];
    }
    /*leemos las direccion del espacio*/
    for (i = 0; i <= 4; i++) {
        fscanf(file, "%s\t", line);
        c = line[0];
        if (c == 'X')break;
        room_set_exit_direction(pers, i, line);
        c = line[0];
        fscanf(file, "[%s %d %d %d]\n", line2, &aux, &coords[0], &coords[1]);
        k = sizeof (char)*(strlen(line2) + 1);
        exit = (char*) malloc(sizeof (char)*(strlen(line2) + 1));
        strcpy(exit, line2);
        for (k = 0; k < n_objs; k++) {
            if (!strcmp(get_obj_name(objetos[0][k]), exit)) {
                room_set_exit_door(pers, i, objetos[0][k]);
                exit2 = (char*) malloc(sizeof (char)*(strlen(line) + 1));
                strcpy(exit2, line);
                obj = room_get_exit_door(pers, exit2);
                set_obj_activado(obj, aux);
                free(exit2);
                break;
            }
        }
        free(exit);
        room_set_exit_connection(pers, i, mapa[coords[0]][coords[1]]);
    }
    return OK;
}

/*
 *@BRIEF lee todos y cada uno de los espacios del fichero y los introduce en el mapa
 *@PARAM el fichero, la mega-tabla de objetos en donde mas adelante se buscaran los objetos que pueda haber en el espacio, el numero de objetos de dicha tabla y el mapa donde se guardan todos los espacios
 *@RETURN ok si todo fue bien, error si hubo algun fallo en el proceso
 */
int leer_espacios(FILE* file, ESPACIO**** mapa, OBJ*** objetos, int n_objs, int* nums) {
    int i, k, num_esp;
    if (!file || !objetos || !mapa)return -1;

    /*leemos el tamaño de la matriz de los espacio*/
    fscanf(file, "%d %d\n", &nums[2], &nums[3]);
    num_esp = nums[2] * nums[3];
    *mapa = (ESPACIO***) malloc(sizeof (ESPACIO**) * nums[2]);
    /*leemos cada espacio*/
    for (i = 0; i < nums[2]; i++) {
        (*mapa)[i] = (ESPACIO**) malloc(sizeof (ESPACIO*) * nums[3]);
        for (k = 0; k < nums[3]; k++)
            (*mapa)[i][k] = iniEspacio();
    }

    for (i = 0; i < num_esp; i++)
        leer_espacio(file, objetos, n_objs, *mapa);
    return num_esp;
}

/*
 *@BRIEF lee del fichero los objetos personajes y espacios y los guarda en sus tablas correspondientes.
 *@PARAM fichero de lectura, arrays de objetos personajes y espacios para guardarlos
 *@RETURN ok o error si sale bien
 */
STATUS leer_fichero(FILE* file, OBJ***objeto, PERS*** personaje, ESPACIO****space, int nums[4]) {
    if (!file || !space)return ERROR;
    /*cargamos los datos del juego*/
    nums[0] = leer_objetos(file, objeto);
    if (nums[0] == 0)return ERROR;
    nums[1] = leer_personajes(file, personaje, objeto, nums[0]);
    if (nums[1] == -1)return ERROR;
    if (leer_espacios(file, space, objeto, nums[0], nums) == -1)return ERROR;

    return OK;
}

/**
 * @BRIEF abre todos los ficheros del juego
 * @AUTHOR Elvira Vegas Maganto
 * @PARAM fichero de lectura, arrays de objetos personajes y espacios para guardarlos
 * @RETURN ok o error si sale bien
 */

STATUS abrir_ficheros(FILE** f1, OBJ*** obj, PERS*** pers, ESPACIO**** espacio, int tabla[4], FILE** f2, FILE** f3, FILE** f4){
    
    STATUS check;
    int i = 0;
    
    /*abrimos el fichero con los datos del juego*/
    *f1 = fopen("inicio.txt", "r");
    if (f1 == NULL) {
        printf("Error al abrir el fichero datos.\n");
        return ERROR;
    }
    
    /*cargamos los datos del juego*/
    check = leer_fichero(*f1, obj, pers, espacio, tabla);
    if (check == ERROR){
        printf("Error al cargar los datos.\n");
        return ERROR;
    }
    
    /*abrimos el fichero de las particulas*/
    *f2 = fopen("particulas.txt", "r");
    if (f2 == NULL) {
        printf("Error al abrir el fichero particulas.\n");
        return -1;
    }

    /*abrimos el fichero de los sinonimos*/
    *f3 = fopen("sinonimos.txt", "r");
    if (f3 == NULL) {
        printf("Error al abrir el fichero sinonimos.\n");
        return -1;
    }
    
    /*abrimos el fichero de las reglas*/
    *f4 = fopen("reglas.txt", "r");
    if (f4 == NULL) {
        printf("Error al abrir el fichero reglas.\n");
        return -1;
    }    
    return OK;
}

/**
 * @BRIEF cierra los ficheros del juego
 * @AUTHOR Elvira Vegas Maganto
 * @PARAM los ficheros
 * @RETURN ok o error si sale bien
 */
STATUS cerrar_ficheros(FILE** f1, FILE** f2, FILE** f3, FILE** f4){
    
    fclose(*f1);
    fclose(*f2);
    fclose(*f3);
    fclose(*f4);
    
    return OK;
}
