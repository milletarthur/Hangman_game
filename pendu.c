#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include "string.c"

// parcours le fichier pour en déterminer son nombre de lignes
int f_nb_lignes(FILE* f){
    int nb_lignes = 0;
    char* ligne;
    char* p = fgets(ligne, 256, f);
    while(p != NULL && ligne != "\n"){
        nb_lignes++;
        p = fgets(ligne, 256, f);
    }
    return nb_lignes;
}

// renvoie le mot au numéro de ligne correspondant
char* find_word(int num_ligne, FILE* f){
    char* word = malloc(256*sizeof(char));
    fscanf(f, "%s\n", word);
    int count = 1;
    while(count < num_ligne){
	fscanf(f, "%s\n", word);
        count++;
    }
    return word;
}

// accède à un fichier afin de retourner un mot au hasard (1 ligne = 1 mot)
char* dico(char* nom_dico){
    FILE* f = fopen(nom_dico, "r");
    int nb_lignes = f_nb_lignes(f);
    fclose(f);
    f = fopen(nom_dico, "r");
    int random = rand() % nb_lignes + 1;
    char* mot_a_deviner = find_word(random, f);
    fclose(f);
    return mot_a_deviner;
}

// transforme ci-besoin un caractère en minuscule
char lowcase(char c){
  if('A'<=c && c<='Z'){
    return 'a'+(c-'A');
  }
  else{
    return c;
  }
}

// renvoie 1 si le caractère est présent dans le tableau, renvoie 0 sinon et l'ajoute dans le tableau dans l'ordre alphabétique
int essais(char c, char* list_c){
  for(int i=0; i<strlen(list_c); i++){
    if(*(list_c + i) == c){
      return 1;
    }
  }
  *(list_c + (int)c - 'a') = c;
  return 0;
}

// met à jour le mot si le caractère c est présent dans le mot et renvoie 0 sinon 1 si le caractère n'est pas présent dans le mot_a_deviner
int verifier_mot(char* mot_a_deviner, char* mot, char c){
  char* string = malloc(strlen(mot)*sizeof(char));
  strcpy(string, mot);
  for (int i=0; i<strlen(mot_a_deviner); i++){
    if (*(mot_a_deviner + i) == c){
      *(mot + i) = c;
    } 
  }
  if (strcmp(string, mot) == 0){
    return 1;
  }
  return 0;
}

int main(int nargs, char** args) {

  // initlalize the random generator
  srand(clock());
  // on récupère le nom du fichier servant de dictionnaire
  char* nom_dico = *(args + 1);
  // on sélectionne aléatoirement le mot à faire deviner
  char* mot_a_deviner = dico(nom_dico);
  printf("\n");
  // c'est le mot composé des lettres trouvé jusqu'à présent
  char* mot = malloc((1 + strlen(mot_a_deviner))*sizeof(char));
  int nb_essais = 0;
  char c,dump;
  // petit bonus : tableau des caractères utilisés au cours de la partie pour éviter les doublons
  char* list_c = malloc(27*sizeof(char));
  int test = 0;
  
  printf("Vous avez 10 coups pour deviner le mot :\n");
  
  // permet de créer le mot à deviner sous forme de tirets '-' et de le transformer en minuscule ci-besoin
  for (int i=0; i<strlen(mot_a_deviner); i++){
    *(mot + i) = '-';
    *(mot_a_deviner + i) = lowcase(*(mot_a_deviner + i));
  }

  // on crée le tableau qui stockera les lettres saisies par l'utilisateur
  for(int j=0; j<26; j++){
    *(list_c + j) = '-';
  }
  *(list_c + 26) = '\0';
  
  printf("\n%s\n",mot);
  
  // boucle principale permettant de saisir un caractère et de vérifier s'il est dans le mot
  while((nb_essais < 10) && (strcmp(mot, mot_a_deviner) != 0)){
    c = '\0';
    printf("\n? ");
    c = getchar();
    // le dump sert à prendre le '\n'
    dump = getchar();
    c = lowcase(c);
    test = essais(c, list_c);
    
    // cas où le caractère saisi par l'utilisateur n'est pas une lettre minuscule
    while (!('a' <= c && c <= 'z')){
      printf("\nMerci de saisir un caractère entre 'a' et 'z'.\n");
      c = '\0';
      printf("\n? ");
      c = getchar();
      dump = getchar();
      c = lowcase(c);
      test = essais(c, list_c);      
    }
    
    // cas où l'utilisateur saisi un caractère qu'il a déjà saisi auparavant
    while(test == 1){
      printf("\nVous avez déjà testé ce caractère\n");
      c = '\0';
      printf("\n? ");
      c = getchar();
      dump = getchar();
      c = lowcase(c);
      test = essais(c, list_c);
    }

    nb_essais += verifier_mot(mot_a_deviner, mot, c);
    printf("\n%s\n",mot);
    printf("\nlettres utilisées : %s\n", list_c);
  }
  
  // au bout de 10 essais, la partie s'arrete
  if(nb_essais == 10){
  	printf("Perdu, le mot à deviner était : %s\n", mot_a_deviner);
  }
  
  // ou bien l'utilisateur a trouvé le mot_a_deviner avant
  if (strcmp(mot, mot_a_deviner) == 0){
    printf("Bravo vous avez deviné le mot %s en seulement %d erreur(s).\n", mot, nb_essais);
  }
  
  printf("Bye.\n");
  return 0;
}
