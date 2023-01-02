#ifndef linkedlist
#define linkedlist

typedef unsigned char Bit;
typedef struct BitElem {
    Bit val;
    struct BitElem *next;
} BitElem;

typedef BitElem *Individu;

void copyIndividu(Individu source, Individu destination);

void afficherIndividu(Individu individu, char nom[]);

Individu createIndividu(int toCreate);

int decodeIndividu(Individu individu);

int nbBits(Individu individu);

float quality(Individu individu);

void croiserIndividus(float pCroise, Individu individu1, Individu individu2);

Individu cloneIndividu(Individu individu);

void deleteIndividu(Individu individu);

#endif