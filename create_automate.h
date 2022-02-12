#ifndef _create_automate_
#define _create_automate_

//Les caractères du fichier .aut seront lu comme non signés
typedef unsigned char* string;

enum n_action {Rejette=0,Accepte=1,Decale=2,Reduit=3};

typedef enum n_action n_action; 

// Toutes les listes du fichier .aut seront transformées en listes chainées

typedef struct list_action list_action;
struct list_action{
    n_action act;
    list_action* next;
};

typedef struct list_reduit list_reduit;
struct list_reduit{
    int nb_etats;
    char sym_non_term;
    list_reduit * next;
};

typedef int etat; 

typedef struct list_decale list_decale;
struct list_decale{
    etat etat_s;
    char letter_c;
    etat etat_s2;
    list_decale *next;
};

typedef struct list_branchement list_branchement;
struct list_branchement {
    etat etat_s;
    char sym_non_term;
    etat etat_s2;
    list_branchement *next;
};

//my_automate contient toutes les informations du fichier .aut 

typedef struct automate {
    int length;
    string description;
    int n;
    list_action *actions_values;
    int first_line_break;
    int second_line_break;
    int third_line_break;
    int fourth_line_break;
    list_reduit *reduits_values;
    list_decale *decale_values;
    int first_255;
    list_branchement *branch_values;
} automate;


/*
@requires : chemin de fichier depuis le CWD
@assignes : my_automate 
@ensures  : remplit my_automate avec les éléments du fichier .aut

Cette fonction est appelée dans le main. Elle fait appel aux autres fonctions de create_automate.c et c'est elle qui permet d'avoir my_automate rempli correctement.
*/

automate* decode_file(char* f);


/*
@requires : chemin de fichier f depuis le CWD, 
            nombre de caractères dans le fichier<LENGTH_MAX_STRING
@assignes : string s
@ensures  : le contenu de f dans une chaine de caractères
*/

string file_to_string(char *f, int* length);


/*
@requires : l'automate correspond à la description de l'énoncé
@assignes : n
@ensures  : le nombre contenu dans chaine
*/

int val_n(automate *my_automate);


/*
@requires : my_automate contient length et description 
@assignes : nothing
@ensures  : affiche le contenu de la description 
            (=string du contenu du fichier .aut)
*/

void aff_string(automate * my_automate);

/*
@requires : l'automate correspond à la description de l'énoncé
@assignes : l_actions
@ensures  : renvoie la liste chainee des actions 
action(etat s, char c) est l'élément c*127+s
*/

list_action* make_list_action(automate *my_automate);


/*
@requires : nothing
@assignes : l_reduits
@ensures  : listes chainée du nombre d'état qu'on doit dépiler et le caractère de branchement
*/

list_reduit* make_reduit(automate * my_automate);


/*
@requires : La partie decale de l'automate se finit bien par 255 255 255
@assigns : l_decale
@ensures : liste chainée de l'état de départ et le caractère lu avec l'état de sortie
*/

list_decale *make_decale(automate *my_automate);


/*
@requires : La partie branchement de l'automate se finit bien par 255 255 255
@assigns : l_branch
@ensures : liste chainée de l'état de départ et le caractère non terminal de branchement avec l'état de sortie
*/

list_branchement *make_branch(automate *my_automate);

#endif
