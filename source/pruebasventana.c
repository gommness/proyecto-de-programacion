/** 
 * @brief Pruebas unitarias de interfaz
 *
 * @file pruebasventana.c
 * @author David Lopez Ramos
 * @date 20-11-2015 
 */

#include "ventana.h"

int main() {

    Ventana* window1 = NULL;
    Ventana* window2 = NULL;
    Ventana* window3 = NULL;
    STATUS error;
    int i;

    /*creamos las ventanas*/
    window1 = ini_ventana(25, 50, 0, 0);
    if (!window1) return -1;
    window2 = ini_ventana(25, 50, 0, 52);
    if (!window2) return -1;
    window3 = ini_ventana(50, 102, 30, 0);
    if (!window3) return -1;
    /*comprobamos que las ventanas son visibles (es decir estan bien creadas)*/
    error = ventana_visible(window1);
    if (error == ERROR) printf("Error en los valores 1\n");
    error = ventana_visible(window2);
    if (error == ERROR) printf("Error en los valores 2\n");
    error = ventana_visible(window3);
    if (error == ERROR) printf("Error en los valores 3\n");


    /*imprimimos los asteriscos*/
    for (i = 1; i < 50; i++) print_cadena_ventana(window1, "*", 1, i);

    for (i = 1; i < 50; i++) print_cadena_ventana(window1, "*", 24, i);

    for (i = 1; i < 25; i++) print_cadena_ventana(window1, "*", i, 1);

    for (i = 1; i < 25; i++) print_cadena_ventana(window1, "*", i, 49);

    for (i = 1; i < 50; i++) print_cadena_ventana(window2, "*", 1, i);

    for (i = 1; i < 50; i++) print_cadena_ventana(window2, "*", 24, i);

    for (i = 1; i < 25; i++) print_cadena_ventana(window2, "*", i, 1);

    for (i = 1; i < 50; i++) print_cadena_ventana(window2, "*", i, 49);

    for (i = 1; i < 102; i++) print_cadena_ventana(window3, "*", 1, i);

    for (i = 1; i < 102; i++) print_cadena_ventana(window3, "*", 49, i);

    for (i = 1; i < 50; i++) print_cadena_ventana(window3, "*", i, 1);

    for (i = 1; i < 50; i++) print_cadena_ventana(window3, "*", i, 101);
    /*imprimimos palabras y comprobamos que funcionan*/
    error = print_cadena_ventana(window1, "Esta es la ventana1", 3, 3);
    if (error == ERROR) printf("Error 1\n");
    error = print_cadena_ventana(window1, "Sigo siendo la ventana1", 4, 4);
    if (error == ERROR) printf("Error 1.1\n");
    error = print_caracter_ventana(window1, 'E', 5, 5);

    error = print_cadena_ventana(window2, "Esta es la ventana2", 3, 3);
    if (error == ERROR) printf("Error 2\n");
    error = print_cadena_ventana(window3, "Esta es la ventana3", 3, 3);
    if (error == ERROR) printf("Error 3\n");


    /*liberamos las ventanas*/
    destroy_ventana(window1);
    destroy_ventana(window2);
    destroy_ventana(window3);

    return 0;

}
