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

Population createPopulation(int toCreate, int individuSize);

Population croiserPopulation(Population population, float pCroise);

int nbIndividus(Population population);

void afficherPopulation(Population population, char nom[], float a, float b);

Population partition(Population first, Population last, float a, float b);

void quick_sort(Population first, Population last, float a, float b);

Population getIndividuAtIndex(Population population, int index);

Population populationVide(int nbIndividus);

void deletePopulation(Population population);

Population selectPopulation(Population population, int nbSelect);

#endif //PROJETLO21_POPULATION_H
