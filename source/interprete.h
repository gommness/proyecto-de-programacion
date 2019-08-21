/* 
 * File:   interprete.h
 * Author: Carlos Li Hu && David Lopez && Elvira Vegas
 */

#include "types.h"


/* @BRIEF Transforma una cadena en el formato mas adecuado
 * @PARAM La cadena a transformar
 * @RETURN Ok si se ha transformado correctamente o Error
 */
STATUS mayus(char* cadena); 

/* @BRIEF Eliminar espacios innecesarios de una cadena
 * @PARAM La cadena para transformar
 * @RETURN Ok si se ha transformado correctamente o Error
 */
STATUS elim_espac(char* cadena);

/* @BRIEF Elimina las particulas de union entre palabras clave
 * @PARAM La cadena y un fichero con las palabras que se deben omitir
 * @RETURN Ok si se ha transformado correctamente o Error
 */
STATUS elim_part(char* cadena, char** part, int num_part);

/* @BRIEF Relaciona palabras clave con sinonimos
 * @PARAM La cadena y un fichero con los sinonimos de las palabras
 * @RETURN Ok si se ha transformado correctamente o Error
 */
STATUS sinonimos(char* cadena, char***sin, int* num_sin);


/* @BRIEF Distingue la clases de palabras que hay en la cadena
 * @PARAM La cadena a analizar y tres fragmentos de cadena para guardar los respectivos campos
 * @RETURN Ok si se ha analizado correctamente o Error
 */
STATUS gramatica (char* cadena, char* verbo, char* directo, char* indirecto);
/* @BRIEF Aúna todas las funciones anteriores
 * @PARAM La cadena a analizar,tres fragmentos de cadena para guardar cada clase y dos ficheros con las partículas y los sinónimos  
 * respectivamente
 * @RETURN Ok si se ha realizado correctamente o Error
 */

STATUS interprete(char *cadena, char* verbo, char* directo, char* indirecto, char**part, char***sin,int num_part,int*num_sin);
