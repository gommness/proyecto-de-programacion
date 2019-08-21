/** 
 * @BRIEF Las funciones de la interfaz
 *
 * @FILE ventana.c
 * @AUTHOR Carlos Li Hu
 * @DATE 14-11-2015 
 */

#include "ventana.h"

struct _Ventana {
    int nfilas; /*Indica el numero de filas que ocupa la ventana*/
    int ncolums; /*Indica el numero de columnas que ocupa la ventana*/

    int start_fila; /*Indica la primera fila de la ventana*/
    int fila_actual; /*Indica en que fila se encuentra el cursor en ese momento*/

    int start_colum; /*Indica la primera columna de la ventana*/
    int colum_actual; /*Indica la primera columna de la ventana*/
    int last_line; /*última linea*/
};

/**
 * @BRIEF Inicializa una ventana de la pantalla.  
 * @AUTHOR Carlos Li Hu
 * @RETURN la ventana creada o NULL si no se ha podido crear correctamente.
 */
Ventana* ini_ventana(int nfilas, int ncolums, int start_fila, int start_colum) {
    Ventana* window = NULL;
    /*reservamos memoria para la ventana*/
    window = (Ventana*) malloc(sizeof (Ventana));
    if (!window)
        return NULL;
    /*ponemos el resto de campos a NULL*/
    window->nfilas = nfilas;
    window->ncolums = ncolums;
    window->start_fila = start_fila;
    window->start_colum = start_colum;
    return window;
}

/**
 * @BRIEF Destruye y libera la memoria reservada para una ventana de la pantalla.  
 * @AUTHOR Carlos Li Hu
 * @PARAM la ventana que se quiere borrar.
 * @RETURN void
 */
void destroy_ventana(Ventana* window) {
    if (window)
        free(window);
}

/**
 * @BRIEF comprueba si una ventana tiene valores válidos 
 * @AUTHOR Carlos Li Hu
 * @PARAM la ventana a comprobar.
 * @RETURN OK si todo ha ido bien, ERROR sino.
 */
STATUS ventana_visible(Ventana* window) {
    if (!window)
        return ERROR;
    if (window->start_colum < 0 || window->start_fila < 0 || window->nfilas <= 0
            || window->ncolums <= 0)
        return ERROR;
    return OK;
}

/**
 * @BRIEF Limpia una ventana.  
 * @AUTHOR Carlos Li Hu
 * @PARAM la ventana que se quiere limpiar.
 * @RETURN OK si todo ha ido bien, ERROR sino.
 */
STATUS limpiar_ventana(Ventana* window) {
    char *buf;
    int i;

    window->last_line = 0;
    /*se dedica a imprimir espacios en la ventana para simular que la limpia*/
    buf = (char *) malloc((window->ncolums + 1) * sizeof (char));
    memset(buf, ' ', window->ncolums);
    buf[window->ncolums] = 0;
    for (i = window->start_fila; i < window->start_fila + window->nfilas; i++) {
        colocar_cursor_write_ventana(window, i - window->start_fila, 0);
        printf("%s", buf);
    }
    fflush(stdout);
    free(buf);
    return OK;
}

/**
 * @BRIEF Coloca el cursor donde se quiere escribir.  
 * @AUTHOR Carlos Li Hu
 * @PARAM la ventana en la cual se quiere colocar el cursor.
 * @PARAM la ultima fila escrita.
 * @PARAM la ultima columna escrita.
 * @RETURN OK si todo ha ido bien, ERROR sino.
 */

STATUS colocar_cursor_write_ventana(Ventana* window, int fila, int colum) {
    if (fila < 0) fila = 0;
    if (colum < 0) colum = 0;
    /*comprueba que no se salga de los bordes*/
    if (fila >= window->nfilas) fila = window->nfilas - 1;
    if (colum >= window->ncolums) colum = window->ncolums - 1;
    /*coloca el cursor en la posicion siguiente*/
    fila += (window->start_fila + 1);
    colum += (window->start_colum + 1);
    printf("%c[%d;%dH", 27, fila, colum);
    return OK;
}

/**
 * @BRIEF Imprime un caracter en la ventana correspondiente.  
 * @AUTHOR Carlos Li Hu
 * @PARAM la ventana en la cual se quiere escribir el caracter.
 * @PARAM el caracter que se quiere escribir.
 * @PARAM la ultima fila escrita.
 * @PARAM la ultima columna escrita.
 * @RETURN OK si todo ha ido bien, ERROR sino.
 */
STATUS print_caracter_ventana(Ventana* window, char caracter, int fila, int colum) {
    if (ventana_visible(window) == ERROR) return ERROR;
    if (fila >= window->nfilas || colum >= window->ncolums) return ERROR;
    /*escribe el caracter donde ponemos el cursor*/
    colocar_cursor_write_ventana(window, fila, colum);
    printf("%c", caracter);
    fflush(stdout);
    return OK;
}

/**
 * @BRIEF Imprime a cierta velocidad el texto que se quiere escribir.  
 * @AUTHOR Carlos Li Hu
 * @PARAM la ventana en la cual se quiere escribir.
 * @PARAM la cadena que se quiere escribir.
 * @PARAM la ultima fila escrita.
 * @PARAM la ultima columna escrita.
 * @PARAM la velocidad de escritura.
 * @RETURN OK si todo ha ido bien, ERROR sino.
 */
STATUS print_cadena_ventana(Ventana* window, char* cadena, int fila, int colum) {
    char *nl_p;
    char save, av_space, ret;
    int i;
    int j;
    int k;
    int l;
    int m;
    int longitud;
    char aux[500];

    /*comprobamos si la ventana es visible o no*/
    if (ventana_visible(window) == ERROR) return ERROR;
    if (fila >= window->nfilas || fila >= window->ncolums) return ERROR;
    nl_p = strchr(cadena, '\n');
    if (nl_p) *nl_p = 0;

    av_space = window->ncolums - colum;
    av_space = av_space - 3;
    save = -1;

    longitud = strlen(cadena);

    if (strlen(cadena) > av_space) {
        for (i = 0; i < av_space; i++)
            aux[i] = cadena[i];

        aux[i] = 0;
        colocar_cursor_write_ventana(window, fila, colum);
        printf("%s", aux);
        fflush(stdout);

        if (strlen(cadena) > 2 * av_space) {
            for (j = 0, i = av_space; i < longitud && i < 2 * av_space; i++, j++)
                aux[j] = cadena[i];

            aux[j] = 0;
            colocar_cursor_write_ventana(window, fila + 1, colum);
            printf("%s", aux);
            fflush(stdout);
        } else if (longitud <= 2 * av_space && longitud >= av_space) {
            for (j = 0, i = av_space; i < longitud; i++, j++)
                aux[j] = cadena[i];
            aux[j] = 0;
            colocar_cursor_write_ventana(window, fila + 1, colum);
            printf("%s", aux);
            fflush(stdout);
        }

        if (strlen(cadena) > 3 * av_space) {
            for (k = 0, i = 2 * av_space; i < longitud && i < 3 * av_space; i++, k++)
                aux[k] = cadena[i];

            aux[k] = 0;
            colocar_cursor_write_ventana(window, fila + 2, colum);
            printf("%s", aux);
            fflush(stdout);
        } else if (longitud <= 3 * av_space && longitud >= 2 * av_space) {
            for (k = 0, i = 2 * av_space; i < longitud; i++, k++)
                aux[k] = cadena[i];
            aux[k] = 0;
            colocar_cursor_write_ventana(window, fila + 2, colum);
            printf("%s", aux);
            fflush(stdout);
        }


        if (strlen(cadena) > 4 * av_space) {
            for (l = 0, i = 3 * av_space; i < longitud && i < 4 * av_space; i++, l++)
                aux[l] = cadena[i];
            /*coloca el cursor en el lugar donde escribir*/
            aux[l] = 0;
            colocar_cursor_write_ventana(window, fila + 3, colum);
            printf("%s", aux);
            fflush(stdout);
        } else if (longitud <= 4 * av_space && longitud >= 3 * av_space) {
            for (l = 0, i = 3 * av_space; i < longitud; i++, l++)
                aux[l] = cadena[i];
            aux[l] = 0;
            colocar_cursor_write_ventana(window, fila + 3, colum);
            printf("%s", aux);
            fflush(stdout);
        }


        if (strlen(cadena) > 5 * av_space) {
            for (m = 0, i = 4 * av_space; i < longitud && i < 5 * av_space; i++, m++)
                aux[m] = cadena[i];

            aux[m] = 0;
            colocar_cursor_write_ventana(window, fila + 4, colum);
            printf("%s", aux);
            fflush(stdout);
        } else if (longitud <= 5 * av_space && longitud >= 4 * av_space) {
            for (l = 0, i = 4 * av_space; i < longitud; i++, m++)
                aux[m] = cadena[i];
            aux[m] = 0;
            colocar_cursor_write_ventana(window, fila + 4, colum);
            printf("%s", aux);
            fflush(stdout);
        }


    }

    if (strlen(cadena) < av_space) {
        colocar_cursor_write_ventana(window, fila, colum);
        printf("%s", cadena);
        fflush(stdout);
    }
    if (save > 0) {
        cadena[av_space - 1] = save;
        ret = av_space;
    } else
        ret = strlen(cadena);
    if (nl_p) *nl_p = '\n';
    window->last_line = fila;
    return ret;
}

/**
 * @BRIEF Imprime el marco de una ventana grande
 * @AUTHOR David Lopez Ramos
 * @PARAM la ventana en la cual se quiere escribir.
 * @PARAM el caracter del marco que se quiere escribir.
 * @RETURN OK si todo ha ido bien, ERROR sino.
 */
STATUS print_marco_ventana_grande(Ventana* window, char caracter) {

    int z;
    if (!window) return ERROR;

    for (z = 1; z < 102; z++) print_caracter_ventana(window, caracter, 1, z);
    for (z = 1; z < 102; z++) print_caracter_ventana(window, caracter, 49, z);
    for (z = 1; z < 50; z++) print_caracter_ventana(window, caracter, z, 1);
    for (z = 1; z < 50; z++) print_caracter_ventana(window, caracter, z, 101);


    return OK;

}

/**
 * @BRIEF Imprime el marco de una ventana pequeña
 * @AUTHOR David Lopez Ramos
 * @PARAM la ventana en la cual se quiere escribir.
 * @PARAM el caracter del marco que se quiere escribir.
 * @RETURN OK si todo ha ido bien, ERROR sino.
 */
STATUS print_marco_ventana_pequena(Ventana* window, char caracter) {

    int z;
    if (!window) return ERROR;

    for (z = 1; z < 60; z++) print_caracter_ventana(window, caracter, 1, z);
    for (z = 1; z < 60; z++) print_caracter_ventana(window, caracter, 24, z);
    for (z = 1; z < 25; z++) print_caracter_ventana(window, caracter, z, 1);
    for (z = 1; z < 25; z++) print_caracter_ventana(window, caracter, z, 59);

    return OK;

}

/**
 * @BRIEF Imprime la pantalla inicial
 * @AUTHOR Elvira Vegas Maganto
 * @PARAM la ventanas ventanas que se quieren imprimir 
 * @RETURN OK si todo ha ido bien, ERROR sino.
 */

STATUS print_pantalla_inicial(Ventana** v1, Ventana** v2, Ventana** v3, Ventana** v4) {
    *v1 = ini_ventana(100, 150, 0, 0);
    if (v1 == NULL)
        return ERROR;
    *v2 = ini_ventana(25, 60, 0, 0);
    if (!v2)
        return ERROR;
    *v3 = ini_ventana(25, 60, 0, 62);
    if (!v3)
        return ERROR;
    *v4 = ini_ventana(50, 102, 28, 10);
    if (!v4)
        return ERROR;

    return OK;
}

/**
 * @BRIEF Comprueba si las ventanas de la pantalla son visibles o no
 * @AUTHOR Elvira Vegas Maganto
 * @PARAM la ventanas ventanas de la pantalla
 * @RETURN OK si todo ha ido bien, ERROR sino.
 */

STATUS pantalla_visible(Ventana** w1, Ventana** w2, Ventana** w3) {

    STATUS check;

    check = ventana_visible(*w1);
    if (check == ERROR)
        printf("Error en los valores 1\n");
    check = ventana_visible(*w2);
    if (check == ERROR)
        printf("Error en los valores 2\n");
    check = ventana_visible(*w3);
    if (check == ERROR)
        printf("Error en los valores 3\n");

    return OK;
}

/**
 * @BRIEF Limpia las ventanas de una pantalla
 * @AUTHOR Elvira Vegas Maganto
 * @PARAM la ventanas ventanas de la pantalla
 * @RETURN OK si todo ha ido bien, ERROR sino.
 */

STATUS limpiar_pantalla(Ventana** v1, Ventana** v2, Ventana** v3, Ventana** v4) {

    STATUS check;

    check = limpiar_ventana(*v1);
    if (check == ERROR)
        printf("Error al limpiar v1\n");
    check = limpiar_ventana(*v2);
    if (check == ERROR)
        printf("Error al limpiar v2\n");
    check = limpiar_ventana(*v3);
    if (check == ERROR)
        printf("Error al limpiar v3\n");
    check = limpiar_ventana(*v4);
    if (check == ERROR)
        printf("Error al limpiar v4\n");

    return OK;
}

/**
 * @BRIEF Imprime la bienvenida del juego
 * @AUTHOR Elvira Vegas Maganto
 * @PARAM la ventana donde se imprime
 * @RETURN OK si todo ha ido bien, ERROR sino.
 */
STATUS print_bienvenida(Ventana** window) {

    print_cadena_ventana(*window, "Mm...muy interesante un loco mas para la familia.", 3, 3);
    print_cadena_ventana(*window, "Pero ya no hay vuelta atras...", 4, 3);
    print_cadena_ventana(*window, "Tengo ganas de albóndigas vamos a casa de la abuela!", 5, 3);
    print_cadena_ventana(*window, "Te deseo buena suerte compañero Sacha.", 6, 3);

    return OK;
}

/**
 * @BRIEF Imprime la bienvenida del juego
 * @AUTHOR Elvira Vegas Maganto
 * @PARAM la ventana donde se imprime
 * @RETURN OK si todo ha ido bien, ERROR sino.
 */
STATUS print_comando(Ventana** window) {

    limpiar_ventana(*window);
    print_marco_ventana_grande(*window, '*');
    print_cadena_ventana(*window, "introduzca una opcion: ", 3, 3);

    return OK;
}
