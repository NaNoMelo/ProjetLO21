//
// Created by natha on 08/12/2022.
//

#include "Population.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Crée une population de taille toCreate et lui assigne des individus aléatoires de taille individuSize
 * @param toCreate
 * @param individuSize
 * @return la population créée
 */
Population createPopulation(int toCreate, int individuSize) {
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
 * @brief croise les individus de la population 2 à 2 aléatoirement
 * @param population
 * @param pCroise
 * @return la population croisée
 */
Population croiserPopulation(Population population, float pCroise) {
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

/**
 * @brief Retourne la population à l'index donné
 * @param population
 * @return la population à l'index donné
 */
Population getIndividuAtIndex(Population population, int index) {
    for (int i = 0; i < index; i++) {
        population = population->next;
    }
    return population;
}

/**
 * @brief Sélectionne les nbSelect premiers individus de la population et remplace le reste par des copies de ces individus
 * @param population
 * @param nbSelect
 * @return la population sélectionnée
 */
Population selectPopulation(Population population, int nbSelect) {
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

/**
 * @brief Retourne le nombre d'individus dans une population
 * @param population
 * @return le nombre d'individus dans la population
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
 * @brief Affiche la population et ses individus
 * @param population
 * @param nom
 * @param a
 * @param b
 */
void afficherPopulation(Population population, char nom[], float a, float b) {
    // Affiche la population
    Population p = population;
    int i = 0;
    printf("%s : \n", nom);
    while (p != NULL) {
        afficherIndividu(p->individu, "Individu", a, b);
        p = p->next;
        i++;
    }
    printf("\n");
}

/**
 * @brief Crée une population sans en créer les individus
 * @param nbIndividus
 * @return
 */
Population populationVide(int nbIndividus) {
    // Créer une population dont les individus ne sont pas définis
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
 * @brief libère l'espace mémoire assigné à une population et ses individus
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
 * @brief Partitionne la population de sorte à ce que tous les éléments à droite du pivot soient plus grands que le pivot et tous les éléments à gauche du pivot soient plus petits que le pivot
 * @param first
 * @param last
 * @param a
 * @param b
 * @return la population partitionnée
 */
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

/**
 * @brief Trie la population par ordre décroissant de qualité
 * @param first
 * @param last
 * @param a
 * @param b
 * @return la population triée
 */
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