#Executable name 
PROG = PROJET-TOWER-DEFENSE 

# Source files
SRC = main.c MapFiles.c Player.c

# Compilation options
CFLAGS = -Wall -Wextra -g 
LDFLAGS = -I. 

# Règle par défaut : compile puis exécute 
all: $(PROG) 
	./$(PROG) 
	
# Default rule: compile then run  
$(PROG): $(SRC) Biblio.h 
	gcc $(CFLAGS) -o $(PROG) $(SRC) $(LDFLAGS) 
	
# Cleaning generated files
clean: 
	rm -f $(PROG)
