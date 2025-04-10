#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FPS 1

int main() {
	
	int game_run = 1;
	int time = 0;
	
	while (game_run) {

        //--------
	
		    // Ici mettre fonction affichage + gérer logique du jeu.

        //--------
	
		    time += 1;
    		sleep(1);
    		system("clear");
    	}
    	
    	return 0;
}
