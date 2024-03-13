#include "hashtable.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// size_t hash(char *key)
// {
//     unsigned long hash = 7256;
//     int c;
//     while ((c = *key++))
//         hash = ((hash << 5) + hash) + c;
//     return hash;
// }

struct hashtable *hashtable_init(size_t size, size_t (*hash)(char *key))
{
    if ((size != 0) || (hash != NULL))
    {
        struct hashtable *structure_h = malloc(sizeof(struct hashtable));
        structure_h->size = size;
        structure_h->items = calloc(size, sizeof(struct ht_item));
        structure_h->hash = hash;

        return structure_h;
    }
    else
    {
        return NULL;
    }
}

void hashtable_del(struct hashtable *ht)
{
    if ((ht == NULL))
    {
        return;
    }
    for (size_t i = 0; i < ht->size; i++)
    {
        while (ht->items[i] != NULL)
        {
            struct ht_item *next = ht->items[i]->next;
            if (ht->items[i]->key.free != NULL)
            {
                ht->items[i]->key.free(ht->items[i]->key.obj);
            }

            if (ht->items[i]->value.free != NULL)
            {
                ht->items[i]->value.free(ht->items[i]->value.obj);
            }

            free(ht->items[i]);
            ht->items[i] = next;
        }
        ht->items[i] = NULL;
    }
    free(ht->items);
    free(ht);
}

int hashtable_insert(struct hashtable *ht, struct obj_and_free key,
                     struct obj_and_free value)
{
    if ((ht == NULL) || (key.obj == NULL) || (value.obj == NULL))
    {
        return 0;
    }

    if (hashtable_contains(ht, key.obj) == 1)
    {
        struct ht_item *tmp = ht->items[ht->hash(key.obj) % ht->size];
        while (tmp != NULL)
        {
            if (strcmp((char *)tmp->key.obj, key.obj) == 0)
            {
                tmp->value.obj = value.obj;
            }
            tmp = tmp->next;
        }
        free(tmp);
    }
    else
    {
        struct ht_item *nouv_elt = malloc(sizeof(struct ht_item));
        nouv_elt->key = key;
        nouv_elt->value = value;
        if (ht->items[ht->hash(key.obj) % ht->size] != NULL)
        {
            nouv_elt->next = ht->items[ht->hash(key.obj) % ht->size];
        }
        else
        {
            nouv_elt->next = NULL;
        }
        ht->items[ht->hash(key.obj) % ht->size] = nouv_elt;
    }
    return 1;
}

int hashtable_remove(struct hashtable *ht, char *key)
{
    if ((ht == NULL) || (key == NULL)
        || (ht->items[ht->hash(key) % ht->size] == NULL)
        || hashtable_contains(ht, key) == 0)
    {
        return 0;
    }

    struct ht_item *prec = ht->items[ht->hash(key) % ht->size];
    struct ht_item *actu = ht->items[ht->hash(key) % ht->size]->next;

    if (strcmp((char *)prec->key.obj, key) == 0)
    {
        if (actu == NULL)
        {
            ht->items[ht->hash(key) % ht->size] = NULL;
        }
        else
        {
            ht->items[ht->hash(key) % ht->size] = actu;
        }
        if (prec->key.free != NULL)
        {
            prec->key.free(prec->key.obj);
        }
        if (prec->value.free != NULL)
        {
            prec->value.free(prec->value.obj);
        }
        free(prec);
        return 1;
    }
    while (actu != NULL)
    {
        if (strcmp((char *)actu->key.obj, key) == 0)
        {
            prec->next = actu->next;
            if (actu->key.free != NULL)
            {
                actu->key.free(actu->key.obj);
            }

            if (actu->value.free != NULL)
            {
                actu->value.free(actu->value.obj);
            }
            free(actu);
            return 1;
        }

        prec = actu;
        actu = actu->next;
    }

    return 0;
}

void *hashtable_get(struct hashtable *ht, char *key)
{
    if ((hashtable_contains(ht, key) == 0) || (ht == NULL))
    {
        return NULL;
    }
    struct ht_item *tmp = ht->items[ht->hash(key) % ht->size];
    while (tmp != NULL)
    {
        struct ht_item *next = tmp->next;

        if (strcmp((char *)tmp->key.obj, key))
        {
            return tmp->value.obj;
        }
        tmp = next;
    }

    return NULL;
}

int hashtable_contains(struct hashtable *ht, char *key)
{
    if ((ht == NULL) || (key == NULL))
    {
        return 0;
    }

    struct ht_item *tmp = ht->items[ht->hash(key) % ht->size];

    while (tmp != NULL)
    {
        if (strcmp((char *)tmp->key.obj, key) == 0)
        {
            return 1;
        }
        tmp = tmp->next;
    }
    return 0;
}
