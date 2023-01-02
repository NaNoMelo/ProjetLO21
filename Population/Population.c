//
// Created by natha on 08/12/2022.
//

#include "Population.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * Crée une population de taille toCreate avec des individus de taille individuSize
 * @param toCreate
 * @param individuSize
 * @return
 */
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

/**
 * Croise la population en fonction de la probabilité pCroise
 * @param population
 * @param pCroise
 * @return
 */
Population croiserPopulation(Population population, float pCroise) {
    // Croiser la population aléatoirement deux à deux
    Population newPopulation = NULL;

    while (population != NULL && nbIndividus(population) > 1) {
        // Select a random individual from the population
        int index = rand() % (nbIndividus(population) - 1) + 1;
        Population q = getIndividuAtIndex(population, index);

        // Perform crossover between the current individual and the selected individual
        croiserIndividus(pCroise, population->individu, q->individu);

        // Add the selected individual to the new population
        Population newPopLast = newPopulation;
        if (newPopulation == NULL) {
            newPopulation = q;
        } else {
            while (newPopLast->next != NULL) {
                newPopLast = newPopLast->next;
            }
            newPopLast->next = q;
        }

        // Remove the selected individual from the original population
        Population prevQ = population;
        while (prevQ->next != q && prevQ->next != NULL) {
            prevQ = prevQ->next;
        }
        prevQ->next = q->next;
        q->next = NULL;

        // Move on to the next individual in the original population
        population = population->next;
    }

    // Add the remaining individual (if any) to the new population
    if (population != NULL) {
        if (newPopulation == NULL) {
            newPopulation = population;
        } else {
            Population newPopLast = newPopulation;
            while (newPopLast->next != NULL) {
                newPopLast = newPopLast->next;
            }
            newPopLast->next = population;
            population->next = NULL;
        }
    }

    return newPopulation;
}

/**
 * Retourne le nombre d'individus dans la population
 * @param population
 * @param index
 * @return
 */
Population getIndividuAtIndex(Population population, int index) {
    // Retourne l'individu à l'index donné
    for (int i = 0; i < index; i++) {
        population = population->next;
    }
    return population;
}

/**
 * Retourne l'index de l'individu donné
 * @param population
 * @param individu
 * @return
 */
int getIndexOfIndividu(Population population, Individu individu) {
    int i = 0;
    while (population != NULL) {
        if (population->individu == individu) {
            return i;
        }
        population = population->next;
        i++;
    }
    return -1;
}

/**
 * Retourne le nombre d'individus dans la population
 * @param population
 * @return
 */
int nbIndividus(Population population) {
// Retourne le nombre d'individus de la population
    int i = 0;
    while (population != NULL) {
        population = population->next;
        i++;
    }
    return i;
}

/**
 * Affiche la population
 * @param population
 * @param nom
 */
void afficherPopulation(Population population, char nom[]) {
    // Affiche la population
    Population p = population;
    int i = 0;
    printf("%s : \n", nom);
    while (p != NULL) {
        afficherIndividu(p->individu, "Individu");
        p = p->next;
        i++;
    }
}

/**
 * clone une population et ses individus
 * @param population
 * @return
 */
Population clonePopulation(Population population) {
    Population clone = (Population) malloc(sizeof(IndivElem));
    clone->individu = cloneIndividu(population->individu);
    if (population->next != NULL) {
        clone->next = clonePopulation(population->next);
    } else {
        clone->next = NULL;
    }
    return clone;
}

Population populationVide(int nbIndividus) {
    Population population = (Population) malloc(sizeof(IndivElem));
    population->individu = NULL;
    if (nbIndividus > 1) {
        population->next = populationVide(nbIndividus - 1);
    } else {
        population->next = NULL;
    }
    return population;
}

/**
 * supprime une population et ses individus
 * @param population
 */
void deletePopulation(Population population) {
    if (population->next != NULL) {
        deletePopulation(population->next);
    }
    if (population->individu != NULL) {
        deleteIndividu(population->individu);
    }
    free(population);
}

/**
 * Coupe la population en deux
 * @param first
 * @param last
 * @return
 */
Population partition(Population first, Population last) {
    // Get first node of given linked list
    Population pivot = first;
    Population front = first;
    Individu temp;
    while (front != NULL && front != last) {
        if (quality(front->individu) < quality(last->individu)) {
            // Swapping  node values
            temp = first->individu;
            first->individu = front->individu;
            front->individu = temp;
            pivot = first;

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

/**
 * Trie la population par qualité
 * @param first
 * @param last
 */
void quick_sort(Population first, Population last) {
    if (first == NULL || first == last) {
        return;
    }
    Population pivot = partition(first, last);
    quick_sort(first, pivot);
    quick_sort(pivot->next, last);
}