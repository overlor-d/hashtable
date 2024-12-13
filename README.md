# HashTable

## Description
Ce programme implémente une table de hachage en C. Une table de hachage est une structure de données permettant de stocker et de rechercher des paires clé-valeur de manière efficace. Elle utilise une fonction de hachage pour mapper les clés à des emplacements spécifiques dans une table.

## Fonctionnalités principales

1. **Initialisation de la table de hachage** :
   - La fonction `hashtable_init` initialise une table de hachage avec une taille donnée et une fonction de hachage personnalisée.

2. **Insertion de paires clé-valeur** :
   - La fonction `hashtable_insert` insère une paire clé-valeur dans la table de hachage.

3. **Suppression de paires clé-valeur** :
   - La fonction `hashtable_remove` supprime une paire clé-valeur basée sur la clé spécifiée.

4. **Recherche de valeurs** :
   - La fonction `hashtable_get` retourne la valeur associée à une clé donnée.

5. **Vérification de l'existence d'une clé** :
   - La fonction `hashtable_contains` vérifie si une clé existe dans la table de hachage.

6. **Suppression complète** :
   - La fonction `hashtable_del` libère la mémoire allouée à la table de hachage.

## Utilisation

### Exemple d'exécution
Voici un exemple d'utilisation du programme dans la fonction `main` :

```c
#include "hashtable.h"

size_t custom_hash(char *key) {
    unsigned long hash = 5381;
    int c;
    while ((c = *key++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}

int main() {
    struct hashtable *ht = hashtable_init(10, custom_hash);

    struct obj_and_free key = {"example", NULL};
    struct obj_and_free value = {"value", NULL};

    hashtable_insert(ht, key, value);
    printf("Contains key 'example': %d\n", hashtable_contains(ht, "example"));
    printf("Value for 'example': %s\n", (char *)hashtable_get(ht, "example"));

    hashtable_remove(ht, "example");
    printf("Contains key 'example' after removal: %d\n", hashtable_contains(ht, "example"));

    hashtable_del(ht);
    return 0;
}
```

### Résultat attendu
L'exemple ci-dessus affiche :
```
Contains key 'example': 1
Value for 'example': value
Contains key 'example' after removal: 0
```

## Structure du code

1. **Initialisation** :
   - `hashtable_init` : Alloue et initialise une table de hachage.

2. **Opérations principales** :
   - `hashtable_insert` : Insère une paire clé-valeur.
   - `hashtable_remove` : Supprime une clé et sa valeur associée.
   - `hashtable_get` : Récupère la valeur associée à une clé.
   - `hashtable_contains` : Vérifie si une clé est présente.

3. **Gestion de mémoire** :
   - `hashtable_del` : Libère la mémoire allouée à la table et ses éléments.

## Points d'amélioration

- **Gestion des collisions** :
  - Actuellement, une gestion simple des collisions est mise en place via des listes chaînées.
- **Optimisation des performances** :
  - Une redimension dynamique de la table pourrait être ajoutée pour éviter les ralentissements dus aux collisions.
- **Extensions possibles** :
  - Support pour d'autres types de données clés ou valeurs.

## Compilation et exécution
Pour compiler et exécuter le programme :

```bash
gcc -o hashtable main.c hashtable.c
./hashtable
```

## Auteur
jean lepeltier
