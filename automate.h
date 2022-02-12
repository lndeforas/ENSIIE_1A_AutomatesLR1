#ifndef _automate_ 
#define _automate_
#include "create_automate.h"

typedef struct stack_etats stack_etats;

struct stack_etats{
    etat e_tat;
    stack_etats* next;
};

/*
@requires : nothing
@assigns : stack
@ensures : la pile d'état stack a été créée, et l'état initial est 0
*/

stack_etats *create_pile();


/*
@requires : 0<=s<n
@assigns : stack
@ensures : L'élément s a été empilé dans stack 

On empile au début ! Donc l'élément le plus ancien (état 0) est le dernier.
*/

stack_etats *empile(stack_etats *stack, etat s);


/*
@requires : nothing
@assigns : stack
@ensures : Le premier élément de stack a été enlevé, depile retourne la nouvelle pile

Par le principe FIFO, on dépile le premier élément.
*/

stack_etats *depile(stack_etats *stack);


/*
@requires : c>=0, 0<=s<n
@assigns : nothing
@ensures : Renvoie l'action associée à l'état s et au caractère c
*/

n_action action(etat s, char c, automate *my_automate);


/*
@requires : c>=0, 0<=s<n
@assigns : nothing
@ensures : Renvoie l'état associé à l'état s et au caractère c par la fonction decale
*/

etat function_decale(etat s, char c,automate *my_automate);


/*
@requires : 0<=s<n
@assigns : l_return
@ensures : Renvoie le nombre d'état à dépiler et le caractère non terminal pour le branchement 
            dans une list_reduit associé à l'état s
            par la fonction réduit
*/

list_reduit *function_reduit(etat s, automate *my_automate);


/*
@requires : 0<=s<n
@assigns : nothing
@ensures : Renvoie l'état associé à l'état s et au caractère non terminal sym 
            par la fonction branchement
*/

etat function_branch(etat s, char sym, automate* my_automate);


/*
@requires : nothing
@assigns : nothing
@ensures : Renvoie si le mot fait partie du langage décrit par l'automate

Cette fonction est appelée dans le main, elle fait appel aux autres fonctions de autom.c
*/

char* result(char* word, automate* my_automate);


/*
@requires : nothing
@assigns : nothing
@ensures : affiche la pile passée en argument
*/

void disp_stack(stack_etats *pile);


/*
@requires : nothing
@assigns : pile
@ensures : libère la mémoire occupée par la pile 
*/

void free_stack(stack_etats *pile);


/*
@requires : nothing
@assigns : reduit
@ensures : libère la mémoire occupée par la list_reduit 
*/

void free_reduit(list_reduit *reduit);


/*
@requires : nothing
@assigns : my_automate
@ensures : libère la mémoire occupée par l'automate
*/

void free_automate(automate *my_automate);

#endif 