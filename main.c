#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FPS 1

int main() {
	
	int game_run = 1;
	int t = 0;

	srand(time(NULL)); // Initialisation de la graine pour les nombres aléatoires
    int** path = generatePath();
	
	while (game_run) {

        //--------
	
		    // Ici mettre fonction affichage + gérer logique du jeu.

        //--------
	
		t += 1;
    		sleep(1);
    		system("clear");
    	}
    	
		free(path);

    	return 0;
}
