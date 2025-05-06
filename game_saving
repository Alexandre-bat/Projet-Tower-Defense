#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
 } Position;
  
typedef struct{
    Position pos;
    int dmg;
    int mana;
    int level;
} Defender;
  
typedef struct{
    Position pos;
    int dmg;
    int hp;
    int level;
} Attacker;

void save_in_file(
    int*** t,
    int* size,
    int* size_c,
    int* size_m,
    int* banana,
    Attacker*** crab,
    Defender*** monkey,
    int* size_pos,
    char* output_file
) {
	FILE* file = fopen(output_file, "w");
	if (file == NULL) {
		perror("Erreur ouverture fichier");
		return;
	}

	fwrite(size, sizeof(int), 1, file);

	for (int i = 0; i < *size; i++) {
		fwrite(&(*size), sizeof(int), 1, file);
		for (int j = 0; j < *size; j++) {
		    fwrite(&(*t)[i][j], sizeof(int), 1, file);
		}
	}

	fwrite(size_c, sizeof(int), 1, file);
	fwrite(size_m, sizeof(int), 1, file);
	fwrite(banana, sizeof(int), 1, file);

	fwrite(size_pos, sizeof(int), 1, file);

	for (int i = 0; i < *size_c; i++) {
		fwrite(&(*crab)[i]->pos.x, sizeof(int), 1, file);
		fwrite(&(*crab)[i]->pos.y, sizeof(int), 1, file);
		fwrite(&(*crab)[i]->dmg, sizeof(int), 1, file);
		fwrite(&(*crab)[i]->hp, sizeof(int), 1, file);
		fwrite(&(*crab)[i]->level, sizeof(int), 1, file);
	}

	for (int i = 0; i < *size_m; i++) {
		fwrite(&(*monkey)[i]->pos.x, sizeof(int), 1, file);
		fwrite(&(*monkey)[i]->pos.y, sizeof(int), 1, file);
		fwrite(&(*monkey)[i]->dmg, sizeof(int), 1, file);
		fwrite(&(*monkey)[i]->mana, sizeof(int), 1, file);
		fwrite(&(*monkey)[i]->level, sizeof(int), 1, file);
	}

	fclose(file);
}

void load_from_file(
    int*** t, 
    int* size, 
    int* size_c, 
    int* size_m, 
    int* banana, 
    Attacker*** crab, 
    Defender*** monkey, 
    int* size_pos, 
    char* input_file
) {
    FILE* file = fopen(input_file, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    // Lire 'size' de t
    fread(size, sizeof(int), 1, file);

    // Allouer de la mémoire pour t (tableau de pointeurs vers des tableaux d'entiers)
    *t = (int**)malloc(*size * sizeof(int*));
    for (int i = 0; i < *size; i++) {
        (*t)[i] = (int*)malloc(*size * sizeof(int));
    }

    // Lire les données de t (tableau de pointeurs vers des tableaux d'entiers)
    for (int i = 0; i < *size; i++) {
        int sub_size;
        fread(&sub_size, sizeof(int), 1, file);  // Taille du sous-tableau
        if (sub_size != *size) {
            perror("Incohérence dans la taille des sous-tableaux");
            return;
        }
        for (int j = 0; j < *size; j++) {
            fread(&(*t)[i][j], sizeof(int), 1, file);
        }
    }

    // Lire les entiers supplémentaires
    fread(size_c, sizeof(int), 1, file);
    fread(size_m, sizeof(int), 1, file);
    fread(banana, sizeof(int), 1, file);

    // Lire les tableaux crab (Attacker) et monkey (Defender)
    fread(size_pos, sizeof(int), 1, file);  // Taille des tableaux

    *crab = (Attacker**)malloc(*size_c * sizeof(Attacker*));
    for (int i = 0; i < *size_c; i++) {
        (*crab)[i] = (Attacker*)malloc(sizeof(Attacker));
        fread(&(*crab)[i]->pos.x, sizeof(int), 1, file);
        fread(&(*crab)[i]->pos.y, sizeof(int), 1, file);
        fread(&(*crab)[i]->dmg, sizeof(int), 1, file);
        fread(&(*crab)[i]->hp, sizeof(int), 1, file);
        fread(&(*crab)[i]->level, sizeof(int), 1, file);
    }

    *monkey = (Defender**)malloc(*size_m * sizeof(Defender*));
    for (int i = 0; i < *size_m; i++) {
        (*monkey)[i] = (Defender*)malloc(sizeof(Defender));
        fread(&(*monkey)[i]->pos.x, sizeof(int), 1, file);
        fread(&(*monkey)[i]->pos.y, sizeof(int), 1, file);
        fread(&(*monkey)[i]->dmg, sizeof(int), 1, file);
        fread(&(*monkey)[i]->mana, sizeof(int), 1, file);
        fread(&(*monkey)[i]->level, sizeof(int), 1, file);
    }

    fclose(file);
}


int exemple_function() {
    // Test de la fonction save_in_file

    // Créer un tableau t de pointeurs vers des tableaux d'entiers
    int size = 3;
    int** t = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        t[i] = (int*)malloc(size * sizeof(int));
        for (int j = 0; j < size; j++) {
            t[i][j] = i * size + j; // Remplir avec des valeurs simples pour le test
        }
    }

    // Créer des entiers supplémentaires
    int size_c = 2;  // Taille du tableau crab
    int size_m = 2;  // Taille du tableau monkey
    int banana = 42;
    int size_pos = 7;

    // Créer des tableaux crab (Attacker) et monkey (Defender)
    Attacker** crab = malloc(1000 * sizeof(Defender*));;
    crab[0] = (Attacker*)malloc(sizeof(Attacker));
    crab[1] = (Attacker*)malloc(sizeof(Attacker));

    crab[0]->pos.x = 1; crab[0]->pos.y = 1;
    crab[0]->dmg = 10; crab[0]->hp = 100; crab[0]->level = 1;

    crab[1]->pos.x = 2; crab[1]->pos.y = 2;
    crab[1]->dmg = 15; crab[1]->hp = 150; crab[1]->level = 2;

    Defender** monkey = malloc(1000 * sizeof(Defender*));
    monkey[0] = (Defender*)malloc(sizeof(Defender));
    monkey[1] = (Defender*)malloc(sizeof(Defender));

    monkey[0]->pos.x = 3; monkey[0]->pos.y = 3;
    monkey[0]->dmg = 5; monkey[0]->mana = 50; monkey[0]->level = 1;

    monkey[1]->pos.x = 4; monkey[1]->pos.y = 4;
    monkey[1]->dmg = 8; monkey[1]->mana = 80; monkey[1]->level = 2;

    // Appeler la fonction save_in_file pour enregistrer les données dans un fichier
    char* output_file = "test_output.txt";
    save_in_file(&t, &size, &size_c, &size_m, &banana, &crab, &monkey, &size_pos, output_file);
    

    // Libération de la mémoire allouée
    for (int i = 0; i < size; i++) {
        free(t[i]);
    }
    free(t);

    for (int i = 0; i < 2; i++) {
        free(crab[i]);
        free(monkey[i]);
    }

    printf("Les données ont été enregistrées dans '%s'.\n", output_file);
    
    
    int** t_loaded;
    int size_loaded, size_c_loaded, size_m_loaded, banana_loaded, size_pos_loaded;
    Attacker** crab_loaded;
    Defender** monkey_loaded;
    load_from_file(&t_loaded, &size_loaded, &size_c_loaded, &size_m_loaded, &banana_loaded, &crab_loaded, &monkey_loaded, &size_pos_loaded, output_file);
    
    // Afficher une partie des données pour vérifier
    printf("banana: %d\n", banana_loaded);
    printf("crab[0]: pos=(%d,%d) dmg=%d hp=%d level=%d\n",
           crab_loaded[0]->pos.x, crab_loaded[0]->pos.y,
           crab_loaded[0]->dmg, crab_loaded[0]->hp, crab_loaded[0]->level);

    printf("monkey[1]: pos=(%d,%d) dmg=%d mana=%d level=%d\n",
           monkey_loaded[1]->pos.x, monkey_loaded[1]->pos.y,
           monkey_loaded[1]->dmg, monkey_loaded[1]->mana, monkey_loaded[1]->level);

    // Libérations
    for (int i = 0; i < size_loaded; i++) free(t_loaded[i]);
    free(t_loaded);

    for (int i = 0; i < size_c_loaded; i++) free(crab_loaded[i]);
    free(crab_loaded);


    return 0;
}










