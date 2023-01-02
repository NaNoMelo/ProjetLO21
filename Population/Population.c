//
// Created by natha on 08/12/2022.
//

#include "Population.h"
#include <stdlib.h>
#include <stdio.h>

Population createPopulation(int toCreate, int individuSize) {
    // Créer la population et la remplir avec des individus aléatoires
    Population population = (Population) malloc(sizeof(IndivElem));
    population->individu = createIndividu(individuSize);
    if (toCreate > 1) {
        population->next = createPopulation(toCreate - 1, individuSize);
    } else {
        population->next = NULL;
    }
    return population;
}

Population croiserPopulation(Population population, float pCroise) {
    // Croise la population en fonction de la probabilité de croisement
    Population populationInitiale = population;
    Population newPopulation = populationVide(nbIndividus(population));
    Population newPopulationLast = newPopulation;
    Population populationLast = population;
    Population individu2;
    while (populationLast->next != NULL) {
        populationLast = populationLast->next;
    }
    while (population != NULL) {
        do {
            individu2 = getIndividuAtIndex(population, (rand() % (nbIndividus(population) - 1)) + 1);
        } while (individu2->individu == NULL);

        croiserIndividus(pCroise, population->individu, individu2->individu);

        newPopulationLast->individu = population->individu;
        population->individu = NULL;
        newPopulationLast = newPopulationLast->next;
        newPopulationLast->individu = individu2->individu;
        individu2->individu = NULL;
        newPopulationLast = newPopulationLast->next;

        while (population != NULL && population->individu == NULL) {
            population = population->next;
        }
    }
    deletePopulation(populationInitiale);
    return newPopulation;
}

Population getIndividuAtIndex(Population population, int index) {
    // Retourne l'individu à l'index donné
    for (int i = 0; i < index; i++) {
        population = population->next;
    }
    return population;
}

Population selectPopulation(Population population, int nbSelect) {
    // Sélectionne les nbSelect premiers individus de la population et remplace le reste par des copies de ces individus
    Population p = population;
    Population selection = populationVide(nbSelect);
    Population selectionLast = selection;
    for (int i = 0; i < nbSelect; i++) {
        selectionLast->individu = p->individu;
        p = p->next;
        if (selectionLast->next != NULL) {
            selectionLast = selectionLast->next;
        }
    }
    selectionLast->next = selection;

    for (int i = nbSelect; i < nbIndividus(population); i++) {
        copyIndividu(selection->individu, p->individu);
        selection = selection->next;
        p = p->next;
    }
    return population;
}

int nbIndividus(Population population) {
// Retourne le nombre d'individus de la population
    int i = 0;
    while (population != NULL) {
        population = population->next;
        i++;
    }
    return i;
}


void afficherPopulation(Population population, char nom[], float a, float b) {
    // Affiche la population
    Population p = population;
    int i = 0;
    printf("%s : \n", nom);
    while (p != NULL) {
        afficherIndividu(p->individu, "Individu", a, b, 0, 0);
        p = p->next;
        i++;
    }
    printf("\n");
}

Population populationVide(int nbIndividus) {
    // Créer une population vide
    Population population = (Population) malloc(sizeof(IndivElem));
    population->individu = NULL;
    if (nbIndividus > 1) {
        population->next = populationVide(nbIndividus - 1);
    } else {
        population->next = NULL;
    }
    return population;
}

//supprime une population et ses individus
void deletePopulation(Population population) {
    if (population->next != NULL) {
        deletePopulation(population->next);
    }
    if (population->individu != NULL) {
        deleteIndividu(population->individu);
    }
    free(population);
}

Population partition(Population first, Population last, float a, float b) {
    // Get first node of given linked list
    Population pivot = first;
    Population front = first;
    Individu temp;
    while (front != NULL && front != last) {
        if (quality(front->individu, a, b) > quality(last->individu, a, b)) {
            pivot = first;

            // Swapping  node values
            temp = first->individu;
            first->individu = front->individu;
            front->individu = temp;

            // Visiting the next node
            first = first->next;
        }

        // Visiting the next node
        front = front->next;
    }

    // Change last node value to current node
    temp = first->individu;
    first->individu = last->individu;
    last->individu = temp;
    return pivot;
}

void quick_sort(Population first, Population last, float a, float b) {
    if (first == last) {
        return;
    }
    Population pivot = partition(first, last, a, b);

    if (pivot != NULL && pivot->next != NULL) {
        quick_sort(pivot->next, last, a, b);
    }

    if (pivot != NULL && first != pivot) {
        quick_sort(first, pivot, a, b);
    }
}