//
// Created by natha on 08/12/2022.
//
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Individu/Individu.h"
#include "Population/Population.h"

int main() {
    srand(time(NULL));
    Population population = createPopulation(50);
    afficherPopulation(population, "Population");
    Population last = population;
    while (last->next != NULL) {
        last = last->next;
    }
    quick_sort(population, last);
    afficherPopulation(population, "Population triée");

    return 0;
}