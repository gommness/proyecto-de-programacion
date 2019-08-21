#Carpetas del proyecto
SOURCE_FOLDER=source
BUILD_FOLDER=build
EXECUTABLE_FOLDER=executable
TEST_FOLDER=test
TXT_FOLDER=txt

#macros

CC = gcc
CFLAGS = -g -Wall -ansi -pedantic -lm
SRC = source/pespacios.c source/espacios.c source/objeto.c source/list.c source/personajes.c source/plector.c source/lect.c source/plist.c source/gestor.c source/pgestor.c source/ppersonajes.c source/gestor.h source/lect.h source/personajes.h source/espacios.h source/objeto.h source/list.h source/types.h source/interprete.c source/jugar.c source/ventana.h source/ventana.c source/guardar_cargar.h source/guardar_cargar.c source/reglas.h source/reglas.c source/pruebasventana.c source/preglas.c source/pguardar_cargar.c source/pruebasinterprete.c source/pobjeto.c
OBJ1 = source/pespacios.o source/espacios.o source/objeto.o source/list.o
OBJ2 = source/ppersonajes.o source/personajes.o source/objeto.o source/list.o
OBJ3 = source/lect.o source/espacios.o source/personajes.o source/objeto.o source/list.o source/plector.o source/gestor.o source/ventana.o
OBJ4 = source/pgestor.o source/gestor.o source/espacios.o source/personajes.o source/objeto.o source/list.o source/ventana.o
OBJ6 = source/jugar.o source/acciones.o source/lect.o source/gestor.o source/espacios.o source/personajes.o source/objeto.o source/list.o source/interprete.o source/ventana.o source/guardar_cargar.o source/reglas.o
OBJ = source/lect.o source/gestor.o source/espacios.o source/personajes.o source/objeto.o source/list.o source/acciones.o source/jugar.o source/interprete.o source/ventana.o source/guardar_cargar.o source/reglas.o source/pruebasventana.o source/preglas.o source/pguardar_cargar.o source/pespacios.o source/ppersonajes.o source/plector.o source/pgestor.o source/plist.o source/pruebasinterprete.o source/pobjeto.o
OBJ8 = source/ventana.o source/pruebasventana.o
OBJ9 = source/pguardar_cargar.o source/acciones.o source/lect.o source/gestor.o source/espacios.o source/personajes.o source/objeto.o source/list.o source/interprete.o source/guardar_cargar.o source/ventana.o source/reglas.o
OBJ10 = source/preglas.o source/acciones.o source/lect.o source/gestor.o source/espacios.o source/personajes.o source/objeto.o source/list.o source/reglas.o source/ventana.o
OBJ11 = txt/inicio.txt txt/reglas.txt txt/sinonimos.txt txt/particulas.txt
OBJ12 = executable/inicio.txt executable/reglas.txt executable/sinonimos.txt executable/particulas.txt
OBJ13 = source/plist.o source/list.o source/objeto.o 
OBJ14 = source/interprete.o source/pruebasinterprete.o source/ventana.o
OBJ15 = source/objeto.o source/pobjeto.o

.PHONY: folders

#reglas explicitas
all: $(OBJ) folders
	$(CC) $(CFLAGS) -o test/pespacios $(OBJ1)
	$(CC) $(CFLAGS) -o test/ppersonajes $(OBJ2)
	$(CC) $(CFLAGS) -o test/plector $(OBJ3)
	$(CC) $(CFLAGS) -o test/pgestor $(OBJ4)
	$(CC) $(CFLAGS) -o test/plist $(OBJ13)
	$(CC) $(CFLAGS) -o test/pruebasinterprete $(OBJ14)
	$(CC) $(CFLAGS) -o test/pobjeto $(OBJ15)
	$(CC) $(CFLAGS) -o test/pruebasventana $(OBJ8)
	$(CC) $(CFLAGS) -o test/pguardar_cargar $(OBJ9)
	$(CC) $(CFLAGS) -o test/preglas $(OBJ10)
	$(CC) $(CFLAGS) -o executable/jugar $(OBJ6)
	mv $(OBJ) build 
	cp $(OBJ11) test
	mv $(OBJ11) executable 
	@echo "#-------------------------------------------------------------#"
	@echo "# Compilados el ejecutable jugar y las pruebas de los modulos #"
	@echo "# Para ejecutar el juego moverse a la carpeta executable      #"
	@echo "# Para ejecutar las pruebas moverse a la carpete test         #"
	@echo "#                                                             #"
	@echo "# Autores:                                                    #"                  
	@echo "# Carlos Li Hu                                                #"
	@echo "# Deivid Lopez Ramos                                          #"
	@echo "# Elvira Vegas Maganto                                        #"
	@echo "#                                                             #"
	@echo "# Colaboracion: Javier Gomez                                  #"
	@echo "#-------------------------------------------------------------#"

clean:
	$(RM) $(OBJ) pespacios ppersonajes plector pgestor plist pruebasinterprete pobjeto pruebasventana pguardar_cargar preglas jugar
	rm -r $(BUILD_FOLDER) 
	mv $(OBJ12) $(TXT_FOLDER) 
	rm -r $(EXECUTABLE_FOLDER)
	rm -r $(TEST_FOLDER) 
	@echo "#-------------------------------------------------------------#"
	@echo "# Gracias por jugar a nuestro juego esperamos que te haya     #"
	@echo "# gustado.                                                    #"
	@echo "# ¡Hasta la proxima!                                          #"
	@echo "#-------------------------------------------------------------#"
folders: 
	mkdir $(BUILD_FOLDER) -p 
	mkdir $(EXECUTABLE_FOLDER) -p 
	mkdir $(TEST_FOLDER) -p 
	mkdir $(TXT_FOLDER) -p
	mkdir $(SOURCE_FOLDER) -p

#reglas implicitas

objeto.o: source/objeto.c source/objeto.h source/types.h
list.o: source/list.c source/objeto.c source/objeto.h source/types.h source/list.h
espacios.o: source/espacios.c source/list.c source/objeto.c source/espacios.h source/list.h source/objeto.h source/types.h
pespacios.o: source/pespacios.c source/espacios.c source/list.c source/objeto.c source/espacios.h source/list.h source/objeto.h source/types.h
personajes.o: source/personajes.c source/objeto.c source/list.c source/personajes.h source/objeto.h source/list.h source/types.h
ppersonajes.o: source/ppersonajes.c source/personajes.c source/objeto.c source/list.c source/personajes.h source/objeto.h source/list.h source/types.h
gestor.o: source/gestor.c source/espacios.c source/personajes.c source/list.c source/objeto.c source/gestor.h source/espacios.h source/personajes.h source/list.h source/objeto.h source/types.h source/ventana.h source/ventana.c
pgestor.o: source/pgestor.c source/gestor.c source/espacios.c source/personajes.c source/list.c source/objeto.c source/gestor.h source/espacios.h source/personajes.h source/list.h source/objeto.h source/types.h source/ventana.c source/ventana.h
lect.o: source/lect.c source/espacios.c source/personajes.c source/list.c source/objeto.c source/espacios.h source/personajes.h source/list.h source/objeto.h source/types.h source/lect.h
plector.o: source/gestor.c source/plector.c source/lect.c source/espacios.c source/personajes.c source/list.c source/objeto.c source/espacios.h source/personajes.h source/list.h source/objeto.h source/types.h source/lect.h source/ventana.c source/ventana.h
plist.o: source/list.h source/list.c source/objeto.h source/objeto.c source/plist.c
pruebasinterprete.o: source/interprete.h source/interprete.c source/types.h source/pruebasinterprete.c source/ventana.h source/ventana.c
pobjeto.o: source/objeto.c source/objeto.h source/types.h source/pobjeto.c
acciones.o: source/acciones.c source/gestor.c source/lect.c source/espacios.c source/personajes.c source/list.c source/objeto.c source/espacios.h source/personajes.h source/list.h source/objeto.h source/types.h source/lect.h source/acciones.h source/ventana.h source/ventana.c
interprete.o: source/acciones.c source/gestor.c source/lect.c source/espacios.c source/personajes.c source/list.c source/objeto.c source/espacios.h source/personajes.h source/list.h source/objeto.h source/types.h source/lect.h source/acciones.h source/interprete.h source/interprete.c source/ventana.h source/ventana.c
jugar.o: source/jugar.c source/acciones.c source/gestor.c source/lect.c source/espacios.c source/personajes.c source/list.c source/objeto.c source/espacios.h source/personajes.h source/list.h source/objeto.h source/types.h source/lect.h source/acciones.h source/interprete.h source/interprete.c source/ventana.h source/ventana.c source/guardar_cargar.h source/guardar_cargar.c source/reglas.h source/reglas.c
ventana.o: source/types.h source/ventana.h source/ventana.c
guardar_cargar.o: source/acciones.c source/gestor.c source/lect.c source/espacios.c source/personajes.c source/list.c source/objeto.c source/espacios.h source/personajes.h source/list.h source/objeto.h source/types.h source/lect.h source/acciones.h source/interprete.h source/interprete.c source/guardar_cargar.h source/guardar_cargar.c source/ventana.h source/ventana.c
reglas.o: source/acciones.c source/gestor.c source/lect.c source/espacios.c source/personajes.c source/list.c source/objeto.c source/espacios.h source/personajes.h source/list.h source/objeto.h source/types.h source/lect.h source/acciones.h source/ventana.h source/ventana.c
pruebasventana.o: source/ventana.h source/ventana.c source/pruebasventana.c source/types.h
pguardar_cargar.o: source/acciones.c source/gestor.c source/lect.c source/espacios.c source/personajes.c source/list.c source/objeto.c source/espacios.h source/personajes.h source/list.h source/objeto.h source/types.h source/lect.h source/acciones.h source/interprete.h source/interprete.c source/ventana.h source/ventana.c source/guardar_cargar.h source/guardar_cargar.c source/funciones_pguardar_cargar.h source/funciones_pguardar_cargar.c source/reglas.h source/reglas.c source/pruebasventana.c source/preglas.c source/pguardar_cargar.c
preglas.o: source/acciones.c source/gestor.c source/lect.c source/espacios.c source/personajes.c source/list.c source/objeto.c source/espacios.h source/personajes.h source/list.h source/objeto.h source/types.h source/lect.h source/acciones.h source/reglas.h source/reglas.c source/ventana.h source/ventana.c
