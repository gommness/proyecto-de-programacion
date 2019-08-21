/* 
 * File:   acciones.h
 * Author: Javier Gomez && David Lopez
 *
 * Created on 16 de octubre de 2015, 16:51
 */

#ifndef ACCIONES_H
#define	ACCIONES_H
#include "ventana.h"
#include "gestor.h"

/*
 * @BRIEF dado un mapa un personaje a mover (usualmente el jugador) y una direccion en la que moverse, 
 * se comprobara si es posible moverse en dicha direccion desde la sala en la que se encuentre el personaje en cuestión.
 * de ser posible, la ubicacion del jugador se actualizara. de lo contrario, se devolvera error
 * @PARAM el mapa de espacios. El personaje que se movera (tipicamente el jugador) y la direccion en la que desea moverse
 * @RETURN ok si ha conseguido moverse sin problemas. De lo contrario, error
 */
STATUS mover(ESPACIO*** mapa, PERS* personaje, char* direccion, FILE*f);

/*
 * @BRIEF dado un mapa, un personaje (el jugador) y el nombre de un objeto, se buscara un objeto con ese nombre en la sala actual   
 * del personaje. de existir, el personaje copiara dicho objeto en su inventario (list) y lo eliminara de la lista de objetos de la
 * sala en la que se encuentra.
 * @PARAM el mapa de espacios, el personaje que guardara un objeto en su inventario y el nombre del objeto a buscar en la sala y guardar
 * @RETURN ok si se consiguio guardar correctamente, error si no
 */
STATUS coger(ESPACIO *** mapa, PERS* personaje, char* nombre, FILE*f);

/*
 * @BRIEF dado un mapa, un personaje(el jugador) y el nombre de un objeto, se buscara un objeto con ese nombre en el  inventario
 * del personaje (una lista) y de existir, se eliminara de su inventario y se insertara en la lista de objetos de la sala en la que se   	encuentra
 * @PARAM el mapa de espacios, el personaje que dejara un objeto de su inventario (tipicamente el jugador) y el nombre del objeto
 * @RETURN ok si se "traslado" el objeto desde el inventario del personaje hasta el espacio. error de lo contrario
 */
STATUS dejar(ESPACIO *** mapa, PERS* personaje, char* nombre, FILE*f);

/*
 * @BRIEF dado un personaje (el jugador) y el nombre de un objeto, se buscara en el inventario del personaje dicho objeto
 * y de existir, se "encendera" de ser posible. (Esta funcion solo actuara sobre objetos que sirvan para  iluminar).
 * @PARAM el personaje que encendera el objeto (cuyo nombre se especifica en el segundo argumento)
 * @RETURN devuleve ok si se consigue encender el objeto. error en cualquier otro caso (e.j. que el jugador no tenga ese objeto)
 */
STATUS encender(PERS* personaje, char*nombre, FILE*f);

/*
 * @BRIEF dado un personaje (tipicamente el jugador) y el nombre de un objeto, se buscara en el inventario del personaje dicho objeto
 * y de existir, se "apagara" de ser posible. (Esta funcion solo actuara sobre objetos que sirvan para iluminar)
 * @PARAM el personaje que apagara el objeto (cuyo nombre se especifica en el segundo argumento)
 * @RETURN devuleve ok si se consigue encender el objeto. error en cualquier otro caso (e.j. que el jugador no tenga ese objeto)
 */
STATUS apagar(PERS* personaje, char*nombre, FILE*f);

/*
 * @BRIEF dado el mapa de espacios, un personaje (el jugador) y la direccion en la que se encuentra la puerta que quiera abrirse,
 * siempre, claro esta, en la sala en la que se encuentre el personaje, se abrira la puerta de la sala en la direccion especificada
 * cabe la posibilidad de que cierta puerta solo pueda ser abierta bajo ciertas circunstancias (el jugador posea una llave en su
 * inventario, la cual se usara automaticamente sin necesidad de ser especificado por el usuario). 
 * Tras esto, toda llave que haya sido empleada, SE ELIMINARA del inventario del jugador
 * @PARAM el mapa de los espacios, el personaje (tipicamente el jugador) y la direccion en la que abrir la puerta
 * @RETURN ok si se abrio la puerta, error si no se abrio
 */
STATUS abrir_puerta(ESPACIO*** mapa, PERS* personaje, char* direccion,char*obj, FILE*f);

/*
 * @BRIEF dado el mapa de espacios, un personaje (el jugador) y el nombre de un objeto, se buscara el objeto con el nombre especificado
 * primero en el inventario del jugador y de no encontrarse ahi, en los objetos que haya en la sala. De encontrarse en alguno de esos    
 * lugares, se imprimira por pantalla el dialogo de dicho objeto (por muy raro que pueda sonar)
 * @PARAM el mapa de espacios, el personaje (jugador) y el nombre del objeto con el que se desea hablar.
 * @RETURN devuelve ok si el dialogo del objeto fue mostrado por pantalla y error en cualquier otro caso
 */
STATUS talk_obj(ESPACIO*** mapa, PERS* personaje, char* nombre, FILE*f);

/*
 * @BRIEF dado un personaje(jugador) la lista de todos los personajes del juego y el nombre del personaje con el que se desea hablar, se  
 * comprobara uno a uno si se encuentran en la misma sala que el jugador y de ser asi si tienen el nombre especificado. Si se cumplen  
 * ambos requisitos, se imprimira por pantalla el dialogo de dicho personaje
 * @PARAM el jugador, la lista de todos los personajes del juego y el nombre del personaje con el que se desea hablar
 * @RETURN ok si se ha impreso por pantalla el dialogo deseado, error de lo contrario
 */
STATUS talk_persona(PERS* jugador, PERS** personajes, char* nombre, int num_personajes, FILE* f);

/*
 * @BRIEF dado un personaje (el jugador) y el nombre de un objeto, se buscara un objeto con dicho nombre en el inventario
 * del jugador. De encontrarlo, se imprimira por pantalla su descripcion y su estado
 * @PARAM un personaje (el jugador) y el nombre de un objeto
 * @RETURN ok si se pudo imprimir por pantalla la descripcion del objeto. error de lo contrario
 */
STATUS examinar_obj(ESPACIO***mapa, PERS* jugador, char* nombre, FILE*f);

/*
 * @BRIEF dada la lista de todos los personajes del juego, el personaje (jugador) y el nombre del personaje al que examinar,
 * se comprobara uno a uno si se encuentran en la misma sala que el jugador y de ser asi si tienen el nombre especificado. Si se cumplen  
 * ambos requisitos, se imprimira por pantalla la descripcion de dicho personaje
 * @PARAM la lista de todos los personajes del juego, el personaje (jugador) y el nombre del personaje con el que se desea hablar
 * @RETURN ok si se imprimio por pantalla la descripcion deseada, error de lo contrario
 */
STATUS examinar_pers(PERS* jugador, PERS** personajes, char* nombre, int num_personajes, FILE*f);

/*
 * @BRIEF dado el mapa de espacios y un personaje (el jugador), se imprimira por pantalla la descripcion de la sala en la que se encuentre
 * el jugador.
 * @PARAM el mapa de espacios y el personaje (jugador)
 * @RETURN ok si se imprimio por pantalla la descripcion del espacio. error de lo contrario
 */
STATUS examinar_esp(ESPACIO*** mapa, PERS* jugador, FILE*f);

/*
 * @BRIEF dado un personaje (jugador) si se encuentra actualmente fuera de la mazmorra (su ubicacion x es mayor que 6) se "dormira" y
 * sera transportado automaticamente a la sala 3,3 dela mazmorra.
 * @PARAM el personaje (jugador) que se "dormira" y sera transportado a la sala 3,3
 * @RETURN ok si se llego a dicha sala. error de lo contrario
 */
STATUS dormir(PERS* jugador, FILE*f);

/*
 * @BRIEF dado un personaje, se comprobara si en su inventario posee on objeto que seria capaz de despertarlo (p.e. un despertador (duh))
 * en caso de que lo posea Y se encuentre actualmente en la mazmorra (su ubicacion x sea menor que 6) se "despertara" y sera transportado
 * automaticamente a la sala que sera su dormitorio << AUN POR DETERMINAR >>. Tras esto, el objeto SERA ELIMINADO del inventario del  
 * jugador
 * @PARAM el personaje (jugador) que se despertara si cumple las condiciones necesarias
 * @RETURN ok si se desperto sin problemas, error de lo contrario
 */
STATUS despertar(PERS* jugador, FILE*f);

#endif	/* ACCIONES_H */

