# Compilateur et options 
CC = gcc #choix du compilateur
CFLAGS = -Wall -Wextra -std=c11
INCLUDE = -Iinclude

# Fichiers sources et objets
SRC = src/stack.c src/testStack.c src/main.c src/liste.c src/formule.c src/feuille.c src/cellule.c src/token.c #var contient all files sources .c du projet.
OBJ = $(SRC:.c=.o) # $(VAR:pattern=replacement)	var qui contient all files objets .o correspondants.
# Nom de l'exécutable
EXEC = programme
# Règle par défaut : compiler tout
all: $(EXEC)
# Création de l'exécutable à partir des objets
$(EXEC):$(OBJ)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJ) -o $(EXEC)
# Compilation des fichiers .c en .o
%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
# Nettoyage
clean:
	rm -f $(OBJ) $(EXEC)