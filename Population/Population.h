//
// Created by natha on 08/12/2022.
//
#ifndef PROJETLO21_POPULATION_H
#define PROJETLO21_POPULATION_H

#include "../Individu/Individu.h"

typedef struct IndivElem {
    Individu individu;
    struct IndivElem *next;
} IndivElem;

typedef struct IndivElem *Population;

Population createPopulation(int toCreate);

Population croiserPopulation(Population population, float pCroise);

int nbIndividus(Population population);

void afficherPopulation(Population population, char nom[]);

Population parition(Population first, Population last);

void quick_sort(Population first, Population last);

#endif //PROJETLO21_POPULATION_H
