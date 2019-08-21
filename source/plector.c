/* 
 * File:   objeto.h
 * Author: David Lopez
 *
 * Created on 30 de septiembre de 2015, 13:05
 */

#include "gestor.h"

int main(int argc, char** argv) {
    FILE * pf;

    FILE * file;
    OBJ** objetos;
    PERS** personajes;
    ESPACIO*** mapa;
    int i, k, nums[4];

    file = fopen("inicio.txt", "r");


    k = leer_fichero(file, &objetos, &personajes, &mapa, nums);
    if (k == 0)printf("UNICO OK\n");
    else printf("ALGO FALLA TIO\n");
    fclose(file);
    if (get_obj_active(objetos[0]) == 1)printf("OKKOKOKOK\n");
    if (get_pers_name(personajes[0]) != NULL)printf("OKKOKOKOK\n");
    if (get_room_descr(mapa[0][0]) != NULL)printf("OKOKOKOKOKOKKOK\n");
    pf = fopen("resultado.txt", "w");

    for (i = 0; i < nums[0]; i++)
        print_objeto(pf, objetos[i]);
    for (i = 0; i < nums[1]; i++)
        print_personaje(pf, personajes[i]);
    for (i = 0; i < nums[2]; i++)
        for (k = 0; k < nums[3]; k++)
            print_espacio(pf, mapa[i][k]);
    /*imprimos cada campo del objeto*/
    print_objeto_name(pf, objetos[0]);
    print_objeto_descr(pf, objetos[0]);
    print_objeto_dial(pf, objetos[0]);
    print_objeto_activable(pf, objetos[0]);
    print_objeto_cogible(pf, objetos[0]);
    print_objeto_iluminador(pf, objetos[0]);
    print_objeto_activado(pf, objetos[0]);
    /*imprimos cada campo del personaje*/
    print_personaje_nombre(pf, personajes[0]);
    print_personaje_descr(pf, personajes[0]);
    print_personaje_dial(pf, personajes[0]);
    print_personaje_ubic(pf, personajes[0]);
    print_personaje_obj(pf, personajes[0]);
    /*imprimos cada campo del espacio*/
    print_espacio_coord(pf, mapa[0][0]);
    print_espacio_desc(pf, mapa[0][0]);
    print_espacio_estado(pf, mapa[0][0]);
    print_espacio_obj(pf, mapa[0][0]);
    print_espacio_exit(pf, mapa[0][0]);

    fclose(pf);

    /*liberamos la memoria usada*/
    for (i = 17; i >= 0; i--)
        destroy_pers(personajes[i]);
    free(personajes);
    destroy_obj(objetos[0]);
    destroy_obj(objetos[1]);
    free(objetos);

    for (i = 6; i >= 0; i--) {
        for (k = 6; k >= 0; k--)
            if (mapa[i][k] != NULL)
                destroyEspacio(mapa[i][k]);
        free(mapa[i]);
    }
    free(mapa);


    return 0;
}

