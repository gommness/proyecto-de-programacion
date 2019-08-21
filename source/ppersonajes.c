/* 
 * File:   ppersonajes.c
 * Author: Javier Gomez
 */
#include "personajes.h"

int main(int argc, char** argv) {
    int ubic[2] = {2, 7};
    OBJ* objeto = NULL;
    OBJ* objeto2 = NULL;
    OBJ* aux = NULL;
    PERS* persona = NULL;
    PERS* persona2 = NULL;
    /*inicializo los campos de dos objetos*/
    objeto = ini_obj();
    if (objeto)printf("OK0\n");
    if (!set_obj_cogible(objeto, 1)) printf("OK0.1\n");
    if (!set_obj_activable(objeto, 1)) printf("OK0.2\n");
    if (!set_obj_ilum(objeto, 1)) printf("OK0.3\n");
    if (!set_obj_activado(objeto, 1)) printf("OK0.4\n");
    if (!set_obj_name(objeto, "Antorcha")) printf("OK1\n");
    if (!set_obj_descr(objeto, "Que se arregle el fallo")) printf("OK1.1\n");
    if (!set_obj_dial(objeto, "por favor")) printf("OK1.2\n");

    objeto2 = ini_obj();
    if (objeto2)printf("OK1.3\n");
    if (!set_obj_cogible(objeto2, 1)) printf("OK1.3.1\n");
    if (!set_obj_activable(objeto2, 1)) printf("OK1.3.2\n");
    if (!set_obj_ilum(objeto2, 1)) printf("OK1.3.3\n");
    if (!set_obj_activado(objeto2, 1)) printf("OK1.3.4\n");
    if (!set_obj_name(objeto2, "Patito")) printf("OK1.4\n");
    if (!set_obj_descr(objeto2, "Es de goma")) printf("OK1.5\n");
    if (!set_obj_dial(objeto2, "Cuac cuac")) printf("OK1.6\n");

    /*inicializo dos personajes iguales con los objetos creados*/
    persona = ini_pers();
    if (persona) printf("OK2\n");
    persona2 = ini_pers();
    if (persona2) printf("OK3\n");

    if (!set_pers_name(persona, "Ataulfo"))printf("OK4\n");
    if (!set_pers_descr(persona, "Este tío es feo de cojones"))printf("OK5\n");
    if (!set_pers_dial(persona,
            "Mi mamá me dice que soy el más guapo del mundo mundial"))
        printf("OK6\n");
    if (!set_pers_ubic(persona, ubic))printf("OK7\n");
    if (!set_pers_obj(persona, objeto))printf("OK8\n");
    if (!set_pers(persona2, "Ataulfo", "Este tío es feo de cojones",
            "Mi mamá me dice que soy el más guapo del mundo mundial",
            ubic, objeto2))printf("OK9\n");
    /*comprobamos que hemos creado dos personajes iguales*/
    if (pers_cmp(persona, persona2) == TRUE)printf("OK10\n");
    if (strcmp(get_pers_name(persona), "Ataulfo") == 0)printf("OK11\n");
    if (strcmp(get_pers_descr(persona), "Este tío es feo de cojones") == 0)
        printf("OK12\n");
    if (strcmp(get_pers_dial(persona),
            "Mi mamá me dice que soy el más guapo del mundo mundial") == 0)
        printf("OK13\n");
    /*comprobamos que contienen los mismos objetos*/
    if (strcmp((const char*) get_pers_ubic(persona), (const char*) ubic) == 0)printf("OK14\n");
    /*compruebo que los objetos insertados son correctos*/
    aux = get_pers_obj(persona, "Antorcha");
    if (obj_cmp(aux, objeto) == TRUE) printf("OK15\n");
    destroy_obj(aux);
    if (!destroy_obj(objeto))printf("OK16\n");
    objeto = extract_pers_obj(persona, "Antorcha");
    if (objeto)printf("OK18\n");
    pers_print(persona);

    if (!destroy_obj(objeto2))printf("OK18.1\n");
    objeto2 = extract_pers_obj(persona2, "Patito");
    if (objeto2)printf("OK18.3\n");
    /*libero memoria*/


    if (destroy_obj(objeto) == OK)printf("OK19\n");
    if (destroy_pers(persona) == OK)printf("OK20\n");
    if (destroy_obj(objeto2) == OK)printf("OK21\n");
    if (destroy_pers(persona2) == OK)printf("OK22\n");

    return 0;
}



