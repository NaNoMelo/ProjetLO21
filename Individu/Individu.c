#include "Individu.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define pow2(n) (1 << (n))

#define F(X) (-log(X))

/**
 * @brief affiche un individu ainsi que sa valeur décimale et sa qualité
 * @param individu
 * @param nom
 * @param A
 * @param B
 */
void afficherIndividu(Individu individu, char nom[], float A, float B) {
    Individu p = individu;
    printf("%s : ", nom);
    while (p != NULL) {
        printf("%d", p->val);
        p = p->next;
    }
    printf("\n\tValeur: %d\n\tQualite: %f\n", decodeIndividu(individu), quality(individu, A, B));
}

/**
 * @brief Crée un individu et le remplit avec toCreate bits aléatoires
 * @param toCreate
 * @return
 */
Individu createIndividu(int toCreate) {
    Individu individu = (Individu) malloc(sizeof(BitElem));
    individu->val = (Bit) rand() % 2;
    if (toCreate > 1) {
        individu->next = createIndividu(toCreate - 1);
    } else {
        individu->next = NULL;
    }
    return individu;
}

/**
 * @brief décode un individu en un entier
 * @param individu
 * @return
 */
int decodeIndividu(Individu individu) {
    int i = nbBits(individu) - 1;
    int val = 0;
    double pow2;
    while (individu != NULL) {
        pow2 = pow2(i);
        val += individu->val * pow2;
        individu = individu->next;
        i--;
    }
    return val;
}

/**
 * @brief Retourne le nombre de bits d'un individu
 * @param individu
 * @return
 */
int nbBits(Individu individu) {
    // Retourne le nombre de bits de l'individu
    int i = 0;
    while (individu != NULL) {
        individu = individu->next;
        i++;
    }
    return i;
}

/**
 * @brief Retourne la qualité d'un individu
 * @param individu
 * @param a
 * @param b
 * @return
 */
float quality(Individu individu, float a, float b) {
    // Retourne la qualité de l'individu
    int x = decodeIndividu(individu);
    int pow = pow2(nbBits(individu));
    float X = ((float) x / pow) * (b - a) + a;
    return F(X);
}

/**
 * @brief croise deux individus entre-eux
 * @param pCroise
 * @param individu1
 * @param individu2
 */
void croiserIndividus(float pCroise, Individu individu1, Individu individu2) {
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

/**
 * @brief copie les bits d'un individu source dans un individu destination
 * @param source
 * @param destination
 */
void copyIndividu(Individu source, Individu destination) {
    // Copie l'source dans l'destination
    while (source != NULL && destination != NULL) {
        destination->val = source->val;
        source = source->next;
        destination = destination->next;
    }
}

/**
 * @brief libère l'espace mémoire assigné à un individu
 * @param individu
 */
void deleteIndividu(Individu individu) {
    if (individu->next != NULL) {
        deleteIndividu(individu->next);
    }
    free(individu);
}