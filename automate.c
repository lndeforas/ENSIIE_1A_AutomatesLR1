#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "automate.h"
#include "create_automate.h"
#include "utile.h"

/////////////////////////////////////////////////////////////////////

/*
@requires : nothing
@assigns : stack
@ensures : la pile d'état stack a été créée, et l'état initial est 0
*/

stack_etats *create_pile(){
    stack_etats *stack=malloc(sizeof(stack_etats));
    //On vérifie que l'allocation mémoire s'est bien passée
    if (stack == NULL){
        printf("erreur dans create_pile \n");
        exit(-1);
    }
    stack->e_tat=0;
    stack->next=NULL;
    return stack;
}

/////////////////////////////////////////////////////////////////////

/*
@requires : 0<=s<n
@assigns : stack
@ensures : L'élément s a été empilé dans stack 

On empile au début ! Donc l'élément le plus ancien (état 0) est le dernier.
*/

stack_etats *empile(stack_etats *stack, etat s){
    stack_etats *sta=malloc(sizeof(stack_etats));
    //On vérifie que l'allocation mémoire s'est bien passée
    if (sta == NULL){
        printf("erreur dans empile \n");
        exit(-1);
    }
    sta->e_tat=s;
    sta->next=stack;
    return sta;
}

/////////////////////////////////////////////////////////////////////

/*
@requires : nothing
@assigns : stack
@ensures : Le premier élément de stack a été enlevé, depile retourne la nouvelle pile

Par le principe FIFO, on dépile le premier élément.
*/

stack_etats *depile(stack_etats *stack){
    stack_etats *s_return = NULL;
    stack_etats *l=stack;
    if (stack!=NULL){
        s_return = stack->next;
        free(l);    
    }
    else {
        printf("PILE VIDE");
    }
    return s_return;
}

/////////////////////////////////////////////////////////////////////

/*
@requires : c>=0, 0<=s<n
@assigns : nothing
@ensures : Renvoie l'action associée à l'état s et au caractère c
*/

n_action action(etat s, char c, automate *my_automate){
    list_action* l_a=my_automate->actions_values;
    int ch=c;
    int end=128*s+ch;
    for (int i=0;i<end;i++){
        l_a=l_a->next;
    }
    n_action acti=l_a->act;
    return acti;
}

/////////////////////////////////////////////////////////////////////

/*
@requires : c>=0, 0<=s<n
@assigns : nothing
@ensures : Renvoie l'état associé à l'état s et au caractère c par la fonction decale
*/

etat function_decale(etat s, char c, automate *my_automate){
    list_decale *l_decale=my_automate->decale_values;
    list_decale *l_first=l_decale;
    while ((l_decale->etat_s!=s)||(l_decale->letter_c!=c))
        l_decale=l_decale->next;
    etat s_decale=l_decale->etat_s2;
    l_decale=l_first;
    return s_decale;
}

/////////////////////////////////////////////////////////////////////

/*
@requires : 0<=s<n
@assigns : l_return
@ensures : Renvoie le nombre d'état à dépiler et le caractère non terminal pour le branchement 
            dans une list_reduit associé à l'état s
            par la fonction réduit
*/

list_reduit *function_reduit(etat s, automate *my_automate){
    list_reduit* l_reduit=my_automate->reduits_values;
    list_reduit *l_first=l_reduit;
    for (int i=0; i<s;i++){
        l_reduit=l_reduit->next;
    }
    int nb_a_depiler=l_reduit->nb_etats;
    char sym=l_reduit->sym_non_term;
    l_reduit=l_first;
    list_reduit *l_return=malloc(sizeof(list_reduit));
    //On vérifie que l'allocation mémoire s'est bien passée
    if (l_return == NULL){
        printf("erreur dans list_reduit \n");
        exit(-1);
    }
    l_return->nb_etats=nb_a_depiler;
    l_return->sym_non_term=sym;
    l_return->next=NULL;
    return l_return;
}

/////////////////////////////////////////////////////////////////////

/*
@requires : 0<=s<n
@assigns : nothing
@ensures : Renvoie l'état associé à l'état s et au caractère non terminal sym 
            par la fonction branchement
*/

etat function_branch(etat s, char sym, automate* my_automate){
    list_branchement *l_branch=my_automate->branch_values;
    list_branchement *l_first=l_branch;
    while ((l_branch->etat_s != s) || (l_branch->sym_non_term != sym)){
        l_branch = l_branch->next;
        //On vérifie que l'allocation mémoire s'est bien passée
        if (l_branch == NULL){
            printf("erreur dans function_branch \n");
            exit(-1);
        }
    }
    etat s_branch=l_branch->etat_s2;
    l_branch=l_first;
    return s_branch;
}

/////////////////////////////////////////////////////////////////////

/*
@requires : nothing
@assigns : nothing
@ensures : Renvoie si le mot fait partie du langage décrit par l'automate

Cette fonction est appelée dans le main, elle fait appel aux autres fonctions de autom.c
*/

char* result(char* word, automate* my_automate){
    stack_etats *pile=create_pile();
    int length=length_string(word);
    int i=0;
    while (i<length+1){
        n_action acti=action(pile->e_tat,word[i],my_automate);
        if (acti==Rejette){
            printf("L'erreur est au caractère %i \n",i);
            free_stack(pile);
            return "Rejected \n";
        }
        if (acti==Accepte){
            free_stack(pile);
            return "Accepted \n";
        }
        if (acti==Decale){
            pile=empile(pile,function_decale(pile->e_tat,word[i],my_automate));
            i++;
        }
        //else correspond au cas où act==Reduit.
        else{
            list_reduit *l=function_reduit(pile->e_tat,my_automate);
            int n_depile=l->nb_etats;
            char A=l->sym_non_term;
            for (int j=0;j<n_depile;j++){
                pile=depile(pile);
            }
            pile=empile(pile,function_branch(pile->e_tat,A,my_automate));
            free_reduit(l);
        }
    }
    return 0;
}

/////////////////////////////////////////////////////////////////////

/*
@requires : nothing
@assigns : nothing
@ensures : affiche la pile passée en argument
*/

void disp_stack(stack_etats *pile){
    stack_etats *p_first=pile;
    if (pile==NULL){
        printf("VIDE \n");
    }
    else{
        while (pile!=NULL){
            printf("%i  ",pile->e_tat);
            pile=pile->next;
        }
        pile=p_first;
        printf("\n");
    }
}

/////////////////////////////////////////////////////////////////////

/*
@requires : nothing
@assigns : pile
@ensures : libère la mémoire occupée par la pile 
*/

void free_stack(stack_etats *pile){
    while (pile!=NULL){
        stack_etats *sta=pile->next;
        free(pile);
        pile=sta;
    }
}

/////////////////////////////////////////////////////////////////////

/*
@requires : nothing
@assigns : reduit
@ensures : libère la mémoire occupée par la list_reduit 
*/

void free_reduit(list_reduit *reduit){
    while (reduit!=NULL){
        list_reduit *red=reduit->next;
        free(reduit);
        reduit=red; 
    }
}

/////////////////////////////////////////////////////////////////////

/*
@requires : nothing
@assigns : my_automate
@ensures : libère la mémoire occupée par l'automate
*/

void free_automate(automate *my_automate){
    //Les boucles while terminent car les éléments de my_automate sont des listes chaines finies.
    //Le dernier élément a pour next NULL
    while (my_automate->branch_values!=NULL){
        list_branchement *l=(my_automate->branch_values->next);
        free(my_automate->branch_values);
        my_automate->branch_values=l;
    }
    while (my_automate->decale_values!=NULL){
        list_decale *m=(my_automate->decale_values->next);
        free(my_automate->decale_values);
        my_automate->decale_values=m;
    }
    while (my_automate->reduits_values!=NULL){
        list_reduit *n=(my_automate->reduits_values->next);
        free(my_automate->reduits_values);
        my_automate->reduits_values=n;
    }
    while (my_automate->actions_values!=NULL){
        list_action *o=(my_automate->actions_values->next);
        free(my_automate->actions_values);
        my_automate->actions_values=o;
    }
    free(my_automate->description);
    free(my_automate);
}

/////////////////////////////////////////////////////////////////////