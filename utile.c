#include <stdio.h>
#include <stdlib.h>
#include "automate.h"
#include "create_automate.h"
#include "utile.h"

/////////////////////////////////////////////////////////////////////

/*
@requires : nothing
@assigns : buf
@ensures : lit le flux stdin et le renvoie dans un char*

Cette fonction est appelée dans le main, 
on peut ensuite utiliser la chaine lue pour vérifier si elle appartient au langage de l'automate
*/

char *read_input(){
    char *buf=malloc(256*sizeof(char));
    if (buf == NULL){
        printf("ERREUR read_input buf \n");
        exit(-1);
    }
    fgets(buf,256,stdin); 
    int length=length_string(buf);
    for (int i=0; i<length;i++){
        //Les caractères étant signés on vérifie qu'ils sont bien entre 0 et 127.
        if (buf[i]<0){
            printf("ERREUR Caractère non ASCII \n");
            buf[0]='\0';
            return buf;
        }
    }
    return buf;
}

/////////////////////////////////////////////////////////////////////

/*
@requires : nothing
@assigns : nothing
@ensures : renvoie true si les chaines sont égales, false sinon
*/

int equal(char* s1, char* s2){
    int l1=length_string(s1);
    int l2=length_string(s2);
    if (l1!=l2)
        return 0;
    for (int i=0;i<l1;i++){
        if (s1[i]!=s2[i])
            return 0;
    } 
    return 1;
}

/////////////////////////////////////////////////////////////////////

/*
@requires : nothing
@assigns : nothing
@ensures : Renvoie la longueur de word
*/

int length_string(char *word){
    int i=0;
    while (word[i]!='\0')
        i++;
    return i;
}

/////////////////////////////////////////////////////////////////////