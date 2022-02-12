#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "create_automate.h"
//LENGTH_  MAX_STRING est la taille maximum du fichier .aut
#define LENGTH_MAX_STRING (40000)
#define CHAR255 (173)

/////////////////////////////////////////////////////////////////////

/*
@requires : chemin de fichier depuis le CWD
@assignes : my_automate 
@ensures  : remplit my_automate avec les éléments du fichier .aut

Cette fonction est appelée dans le main. Elle fait appel aux autres fonctions de create_automate.c et c'est elle qui permet d'avoir my_automate rempli correctement.
*/

automate* decode_file(char* f){
    automate* my_automate=malloc(sizeof(automate));
    //On vérifie que l'allocation mémoire s'est bien passée
    if (my_automate == NULL) {
        printf("ERREUR decode_file \n");
        exit(-1);
    }
    my_automate->description=file_to_string(f,&my_automate->length);
    my_automate->n=val_n(my_automate);
    my_automate->actions_values=make_list_action(my_automate);
    my_automate->reduits_values=make_reduit(my_automate);
    my_automate->decale_values=make_decale(my_automate);
    my_automate->branch_values=make_branch(my_automate);
    return my_automate;
}

/////////////////////////////////////////////////////////////////////

/*
@requires : chemin de fichier f depuis le CWD, 
            nombre de caractères dans le fichier<LENGTH_MAX_STRING
@assignes : string s
@ensures  : le contenu de f dans une chaine de caractères
*/

string file_to_string(char * f, int* length){
    FILE* point_file=fopen(f,"rb");
    if (point_file==NULL){
        printf("ERREUR file_to_string : le fichier demandé n'existe pas \n");
        exit(-1);
    }
    string s=malloc(LENGTH_MAX_STRING*sizeof(char));
    //On vérifie que l'allocation mémoire s'est bien passée
    if (s == NULL) {
        printf("ERREUR file_to_string s \n");
        fclose(point_file); 
        exit(-1);
    }
    //On lit le fichier jusqu'à LENGTH_MAX_STRING puis on le ferme
    int readn=(int) fread(s,sizeof(char),LENGTH_MAX_STRING,point_file);
    fclose(point_file);
    if (readn==LENGTH_MAX_STRING){
        printf("FICHIER TROP VOLUMINEUX");
        return NULL; 
    }
    *length=readn;
    return s;
}

/////////////////////////////////////////////////////////////////////

/*
@requires : l'automate correspond à la description de l'énoncé
@assignes : n
@ensures  : le nombre contenu dans chaine
*/

int val_n(automate *my_automate){
    int i=0;
    string s = my_automate-> description;
    //La boucle while termine car  dans la description du fichier .aut, n est précédé par 'a'
    while (s[i]!='a')
        i++;
    char* chaine=malloc(3*sizeof(char));
    //On vérifie que l'allocation mémoire s'est bien passée
    if (chaine == NULL) {
        printf("ERREUR val_n chaine \n");
        exit(-1);
    }
    //Les 10 lignes suivantes permettent de mettre exactement les chiffres de n dans chaine
    chaine[0]=s[i+2];
    if (s[i+3]!=10){
        chaine[1]=s[i+3];
        if (s[i+4]!=10){
            chaine[2]=s[i+4];
            my_automate->first_line_break=i+5;
        }
        else
            my_automate->first_line_break=i+4;
    }
    else
        my_automate->first_line_break=i+3;
    int n=atoi(chaine);
    free(chaine);
    return n;
}

/////////////////////////////////////////////////////////////////////

/*
@requires : my_automate contient length et description 
@assignes : nothing
@ensures  : affiche le contenu de la description 
            (=string du contenu du fichier .aut)
*/

void aff_string(automate * my_automate){
    int i=0;
    int l=my_automate->length;
    for (i=0;i<l;i++){
        printf("%i : %i : %c\n",i,my_automate->description[i],my_automate->description[i]);
    }
}

/////////////////////////////////////////////////////////////////////

/*
@requires : l'automate correspond à la description de l'énoncé
@assignes : l_actions
@ensures  : renvoie la liste chainee des actions 
action(etat s, char c) est l'élément c*127+s
*/

list_action* make_list_action(automate *my_automate){
    int i=(my_automate->first_line_break)+1;
    string s=my_automate->description;
    list_action *l_actions=malloc(sizeof(list_action));
    //On vérifie que l'allocation mémoire s'est bien passée
    if (l_actions == NULL) {
        printf("ERREUR make_list_action l_actions \n");
        exit(-1);
    }
    list_action* l_first=l_actions;
    l_actions->act=s[i];
    l_actions->next=NULL;
    i++;
    //La boucle while termine car le bloc d'actions se finit par un retour à la ligne
    while (s[i]!=10){
        list_action *l=malloc(sizeof(list_action)); 
        //On vérifie que l'allocation mémoire s'est bien passée
        if (l == NULL) {
            printf("ERREUR make_list_action l \n");
            exit(-1);
        }
        l->act=s[i]; 
        l_actions->next=l;
        l_actions=l_actions->next;
        i++;
    }
    my_automate->second_line_break=i;;
    return l_first;
}

/////////////////////////////////////////////////////////////////////

/*
@requires : nothing
@assignes : l_reduits
@ensures  : listes chainée du nombre d'état qu'on doit dépiler et le caractère de branchement
*/

list_reduit* make_reduit(automate * my_automate){
    int i=(my_automate->second_line_break)+1;
    string s=my_automate->description;
    list_reduit *l_reduits=malloc(sizeof(list_reduit));
    //On vérifie que l'allocation mémoire s'est bien passée
    if (l_reduits == NULL) {
        printf("ERREUR make_reduit l_reduits \n");
        exit(-1);
    }
    list_reduit* l_first=l_reduits;
    l_reduits->nb_etats=s[i];
    l_reduits->next=NULL;
    i++;
    //La boucle while termine car le bloc d'actions se finit par un retour à la ligne
    while (s[i]!=10){
        list_reduit *l=malloc(sizeof(list_reduit));
        //On vérifie que l'allocation mémoire s'est bien passée
        if (l == NULL) {
            printf("ERREUR make_reduit l \n");
            exit(-1);
        }
        l->nb_etats=s[i];
        l_reduits->next=l;
        l_reduits=l_reduits->next;
        i++;
    }
    my_automate->third_line_break=i;
    l_reduits=l_first;
    l_reduits->sym_non_term=s[i];
    i++;
    //La boucle while termine car le bloc d'actions se finit par un retour à la ligne
    while (s[i]!=10){
        l_reduits->sym_non_term=s[i];
        l_reduits=l_reduits->next;
        i++;
    }
    my_automate->fourth_line_break=i;
    return l_first;
}

/////////////////////////////////////////////////////////////////////

/*
@requires : La partie decale de l'automate se finit bien par 255 255 255
@assigns : l_decale
@ensures : liste chainée de l'état de départ et le caractère lu avec l'état de sortie
*/

list_decale *make_decale(automate *my_automate){
    int i=(my_automate->fourth_line_break)+1;
    string s=my_automate->description;
    list_decale *l_decale=malloc(sizeof(list_decale));
    //On vérifie que l'allocation mémoire s'est bien passée
    if (l_decale == NULL) {
        printf("ERREUR make_decale l_decale \n");
        exit(-1);
    }
    list_decale *l_first=l_decale;
    l_decale->etat_s=s[i];
    i++;
    l_decale->letter_c=s[i];
    i++;
    l_decale->etat_s2=s[i];
    i++;
    l_decale->next=NULL;
    //La boucle while termine car le bloc d'actions se finit par 255 255 255
    while ((s[i]!=CHAR255)|(s[i+1]!=CHAR255)|(s[i+2]!=CHAR255)){
        list_decale *l=malloc(sizeof(list_decale));
        //On vérifie que l'allocation mémoire s'est bien passée
        if (l == NULL) {
            printf("ERREUR make_decale l \n");
            exit(-1);
        }
        l->etat_s=s[i];
        l->letter_c=s[i+1];
        l->etat_s2=s[i+2];
        l_decale->next=l;
        l_decale=l_decale->next;
        i=i+3;
    }
    my_automate->first_255=i;
    return l_first;
}

/////////////////////////////////////////////////////////////////////

/*
@requires : La partie branchement de l'automate se finit bien par 255 255 255
@assigns : l_branch
@ensures : liste chainée de l'état de départ et le caractère non terminal de branchement avec l'état de sortie
*/

list_branchement *make_branch(automate *my_automate){    
    int i=(my_automate->first_255)+3;
    string s=my_automate->description;
    list_branchement *l_branch=malloc(sizeof(list_branchement));
    //On vérifie que l'allocation mémoire s'est bien passée
    if (l_branch == NULL) {
        printf("ERREUR make_branch l_branch \n");
        exit(-1);
    }
    list_branchement *l_first=l_branch;
    l_branch->etat_s=s[i];
    i++;
    l_branch->sym_non_term=s[i];
    i++;
    l_branch->etat_s2=s[i];
    i++;
    l_branch->next=NULL;
    //La boucle while termine car le bloc d'actions se finit par 255 255 255
    while ((s[i]!=CHAR255)|(s[i+1]!=CHAR255)|(s[i+2]!=CHAR255)){
        list_branchement *l=malloc(sizeof(list_branchement));
        //On vérifie que l'allocation mémoire s'est bien passée
        if (l == NULL) {
            printf("ERREUR make_branch l \n");
            exit(-1);
        }
        l->etat_s=s[i];
        l->sym_non_term=s[i+1];
        l->etat_s2=s[i+2];
        l->next=NULL;
        l_branch->next=l;
        l_branch=l_branch->next;
        i=i+3;
    }
    return l_first;
}

/////////////////////////////////////////////////////////////////////