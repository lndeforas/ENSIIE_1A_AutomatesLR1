
#ifndef _utile_
#define _utile_

/*
@requires : nothing
@assigns : buf
@ensures : lit le flux stdin et le renvoie dans un char*

Cette fonction est appelée dans le main, 
on peut ensuite utiliser la chaine lue pour vérifier si elle appartient au langage de l'automate
*/

char *read_input();


/*
@requires : nothing
@assigns : nothing
@ensures : renvoie true si les chaines sont égales, false sinon
*/

int equal(char* s1, char* s2);


/*
@requires : nothing
@assigns : nothing
@ensures : Renvoie la longueur de word
*/

int length_string(char *word);

#endif