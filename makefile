# Compilateur et options 
CC = gcc #choix du compilateur
CFLAGS = -Wall -Wextra -std=c11 `pkg-config --cflags gtk+-3.0`
LDFLAGS = `pkg-config --libs gtk+-3.0`
INCLUDE = -Iinclude

# Fichiers sources et objets
SRC = src/stack.c src/testStack.c src/main.c src/liste.c src/formule.c src/feuille.c src/cellule.c src/token.c  #var contient all files sources .c du projet.
OBJ = $(SRC:.c=.o) # $(VAR:pattern=replacement)	var qui contient all files objets .o correspondants.
# Fichiers sources et objets pour GTK
SRC_GTK = src/stack.c src/testStack.c src/liste.c src/formule.c src/feuille.c src/cellule.c src/token.c src/bind.c src/main_gtk.c#var contient all files sources .c du projet.
OBJ_GTK = $(SRC_GTK:.c=.o) # $(VAR:pattern=replacement)	var qui contient all files objets .o correspondants.

# Nom de l'exécutable
EXEC = programme
EXEC_GTK = monoplan
# Règle par défaut : compiler tout
all: $(EXEC_GTK)
# Compiler les deux versions
both: $(EXEC) $(EXEC_GTK)
# Création de l'exécutable à partir des objets
$(EXEC):$(OBJ)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJ) -o $(EXEC)
# Création de l'exécutable GTK (interface graphique)
$(EXEC_GTK): $(OBJ_GTK)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJ_GTK) -o $(EXEC_GTK) $(LDFLAGS)
# Compilation des fichiers .c en .o
%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
# Exécuter la version GTK
run: $(EXEC_GTK)
	./$(EXEC_GTK)
# Nettoyage
clean:
	rm -f $(OBJ) $(EXEC) $(OBJ_GTK) $(EXEC_GTK)