//
// Created by natha on 08/12/2022.
//
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Individu/Individu.h"
#include "Population/Population.h"

#define taillePopulation 10
#define tailleIndividu 8
#define nGen 200
#define pCroise 0.5
#define tSelect 5

int main() {
    srand(time(NULL));
    Population last;

    Population population = createPopulation(taillePopulation, tailleIndividu);
    afficherPopulation(population, "Population initiale");

    for (int i = 0; i < nGen; i++) {
        population = croiserPopulation(population, pCroise);
//        afficherPopulation(population, "Population croisée");

        last = population;
        while (last->next != NULL) {
            last = last->next;
        }
        quick_sort(population, last);
//        afficherPopulation(population, "Population triée");

        population = selectPopulation(population, tSelect);
//        afficherPopulation(population, "Population sélectionnée");
    }
    afficherPopulation(population, "Population finale");

    return 0;
}