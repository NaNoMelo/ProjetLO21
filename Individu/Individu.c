#include "Individu.h"
#include <stdio.h>
#include <stdlib.h>

#define A (-1)
#define B 1

int intPow(int base, int exp) {
    int result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

void afficherIndividu(Individu individu, char nom[]) {
    Individu p = individu;
    printf("%s : ", nom);
    while (p != NULL) {
        printf("%d", p->val);
        p = p->next;
    }
    printf("\n\tValeur: %d\n\tQualite: %f\n", decodeIndividu(individu), quality(individu));
}

Individu createIndividu(int toCreate) {
    // Créer l'individu et le remplir avec 8 bits aléatoires
    Individu individu = (Individu) malloc(sizeof(BitElem));
    individu->val = (Bit) rand() % 2;
    if (toCreate > 1) {
        individu->next = createIndividu(toCreate - 1);
    } else {
        individu->next = NULL;
    }
    return individu;
}

int decodeIndividu(Individu individu) {
    // Décode l'individu pour obtenir la valeur des bits en décimal
    int i = nbBits(individu) - 1;
    int val = 0;
    double pow2;
    while (individu != NULL) {
        pow2 = intPow(2, i);
        val += individu->val * pow2;
        individu = individu->next;
        i--;
    }
    return val;
}


int nbBits(Individu individu) {
    // Retourne le nombre de bits de l'individu
    int i = 0;
    while (individu != NULL) {
        individu = individu->next;
        i++;
    }
    return i;
}

float quality(Individu individu) {
    // Retourne la qualité de l'individu
    int x = decodeIndividu(individu);
    int pow = intPow(2, nbBits(individu));
    float X = ((float) x / pow) * (B - A) + A;
    return X * X;
}

void croiserIndividus(float pCroise, Individu individu1, Individu individu2) {
    // Croise aléatoirement les éléments de deux individus
    while (individu1 != NULL && individu2 != NULL) {
        if (rand() % 100 < pCroise * 100) {
            Bit tmp = individu1->val;
            individu1->val = individu2->val;
            individu2->val = tmp;
        }
        individu1 = individu1->next;
        individu2 = individu2->next;
    }
}

//retourne un clone de l'individu
Individu cloneIndividu(Individu individu) {
    Individu clone = (Individu) malloc(sizeof(BitElem));
    clone->val = individu->val;
    if (individu->next != NULL) {
        clone->next = cloneIndividu(individu->next);
    } else {
        clone->next = NULL;
    }
    return clone;
}

//supprime l'individu
void deleteIndividu(Individu individu) {
    if (individu->next != NULL) {
        deleteIndividu(individu->next);
    }
    free(individu);
}

//quciksort pour trier les individus d'une population par qualité
void quickSort2(Individu *population, int debut, int fin) {
    int gauche = debut - 1;
    int droite = fin + 1;
    const float pivot = quality(population[debut]);
    if (debut >= fin) {
        return;
    }
    while (1) {
        do droite--; while (quality(population[droite]) > pivot);
        do gauche++; while (quality(population[gauche]) < pivot);
        if (gauche < droite) {
            Individu tmp = population[gauche];
            population[gauche] = population[droite];
            population[droite] = tmp;
        } else break;
    }
    quickSort2(population, debut, droite);
    quickSort2(population, droite + 1, fin);
}