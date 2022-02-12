#include <stdio.h>
#include <stdlib.h>
#include "automate.h"
#include "create_automate.h"
#include "utile.h"

/////////////////////////////////////////////////////////////////////

/*
@requires : argv[1] est le chemin (depuis le CWD) vers le fichier .aut
@assigns : nothing
@ensures : Affiche si le fichier .aut a été lu correctement, 
            puis affiche si le mot est reconnu grâce à result
*/

int main(int argc, char **argv){
    if (argc == 1){
        printf("Pas de fichier .aut passé en argument \n");
    }
    if (argc>1){
        automate *my_automate=decode_file(argv[1]);
        printf("Le fichier %s a été correctement lu. Ecrivez des séquences de caractères ou 'quit \\n' pour quitter. \n", argv[1]);
        char* word=read_input();
        while (equal(word,"quit\n")==0){
            printf("%s",result(word,my_automate));
            free(word);
            word=read_input();
        }
        free(word);
        free_automate(my_automate);
    }    
    return 0;
}

/////////////////////////////////////////////////////////////////////
