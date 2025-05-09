#Nom de l'exécutable 
PROG = PROJET-TOWER-DEFENSE 

# Fichiers sources 
SRC = Main.c MapFiles.c Player.c

# Options de compilation 
CFLAGS = -Wall -Wextra -g 
LDFLAGS = -I. 

# Règle par défaut : compile puis exécute 
all: $(PROG) 
	./$(PROG) 
	
# Compilation de l'exécutable 
$(PROG): $(SRC) Biblio.h 
	gcc $(CFLAGS) -o $(PROG) $(SRC) $(LDFLAGS) 
	
# Nettoyage des fichiers générés 
clean: 
	rm -f $(PROG)
