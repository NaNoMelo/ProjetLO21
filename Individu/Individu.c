#include "Individu.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define pow2(n) (1 << (n))

#define F(X) (-log(X))

void afficherIndividu(Individu individu, char nom[], float A, float B, float pCroise, int nbSelect) {
    Individu p = individu;
    printf("pCroise : %.1f, nbSelect: %d :", pCroise, nbSelect);
    while (p != NULL) {
        printf("%d", p->val);
        p = p->next;
    }
    printf("\n\tValeur: %d\n\tQualite: %f\n", decodeIndividu(individu), quality(individu, A, B));
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
        pow2 = pow2(i);
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

float quality(Individu individu, float a, float b) {
    // Retourne la qualité de l'individu
    int x = decodeIndividu(individu);
    int pow = pow2(nbBits(individu));
    float X = ((float) x / pow) * (b - a) + a;
    return -log(X);
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

void copyIndividu(Individu source, Individu destination) {
    // Copie l'source dans l'destination
    while (source != NULL && destination != NULL) {
        destination->val = source->val;
        source = source->next;
        destination = destination->next;
    }
}

//supprime l'individu
void deleteIndividu(Individu individu) {
    if (individu->next != NULL) {
        deleteIndividu(individu->next);
    }
    free(individu);
}