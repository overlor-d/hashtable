#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

struct obj_and_free
{
    void *obj;
    void (*free)(void *obj);
};

struct ht_item
{
    struct obj_and_free key;
    struct obj_and_free value;
    struct ht_item *next;
};

struct hashtable
{
    struct ht_item **items;
    size_t size;
    size_t (*hash)(char *key);
};

/*
** Cette fonction doit initialiser la table de hachage et la retourner. Si la
*fonction de hachage est NULL ou si la taille est 0, vous devez
** retourner un pointeur NULL.
*/
struct hashtable *hashtable_init(size_t size, size_t (*hash)(char *key));

/*
** Cette fonction doit libérer la table de hachage donnée ainsi que chaque
*élément ayant une fonction de libération.
*/
void hashtable_del(struct hashtable *ht);

/*
** Cette fonction doit insérer en ajoutant un nœud à la liste chaînée appropriée
*si la clé n'existe pas, ou en remplaçant la valeur du nœud approprié si la clé
*existe.
** Si l'insertion réussit, vous devez renvoyer 1, sinon vous renvoyez 0.
*/
int hashtable_insert(struct hashtable *ht, struct obj_and_free key,
                     struct obj_and_free value);

/*
** Cette fonction doit supprimer les éléments de la table de hachage et la
*libérer.
** Si cela réussit, vous devez renvoyer 1, sinon vous renvoyez 0.
*/
int hashtable_remove(struct hashtable *ht, char *key);

/*
** Cette fonction renvoie la valeur associée à la clé donnée.
*/
void *hashtable_get(struct hashtable *ht, char *key);

/*
** Cette fonction doit vérifier si une clé est déjà présente dans la table de
*hachage.
** Si cela réussit, vous devez renvoyer 1, sinon vous renvoyez 0.
*/
int hashtable_contains(struct hashtable *ht, char *key);

// size_t hash(char *key);

#endif /*HASHTABLE_H*/
