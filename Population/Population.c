//
// Created by natha on 08/12/2022.
//

#include "Population.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Population createPopulation(int toCreate) {
    // Créer la population et la remplir avec des individus aléatoires
    Population population = (Population) malloc(sizeof(IndivElem));
    population->individu = createIndividu(8);
    if (toCreate > 1) {
        population->next = createPopulation(toCreate - 1);
    } else {
        population->next = NULL;
    }
    return population;
}

/*Population croiserPopulation(Population population1, Population population2, float pCroise){
    //croiser deux individus aléatoire de la population 1
    //pCroise est la probabilité de croiser deux individus
    //retourne la population croisée
    Population croise = (Population) malloc(sizeof(IndivElem));
    croise->individu = croiserIndividus(pCroise,population1->individu, population2->individu);
    if (population1->next != NULL && population2->next != NULL) {
        croise->next = croiserPopulation(population1->next, population2->next, pCroise);
    } else {
        croise->next = NULL;
    }
}*/

//créer une deuxième population à partir de la première en croisant les individus aléatoirement
/*Population croiserPopulation(Population population, float pCroise) {
    //croiser deux individus aléatoire de la population 1
    //pCroise est la probabilité de croiser deux individus
    //retourne la population croisée
    Population croise = (Population) malloc(sizeof(IndivElem));
    croise->individu = croiserIndividus(pCroise, population->individu, population->next->individu);
    if (population->next->next != NULL) {
        croise->next = croiserPopulation(population->next->next, pCroise);
    } else {
        croise->next = NULL;
    }
    return croise;
}*/


int nbIndividus(Population population) {
// Retourne le nombre d'individus de la population
    int i = 0;
    while (population != NULL) {
        population = population->next;
        i++;
    }
    return i;
}


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

//clone une population et ses individus
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

//supprime une population et ses individus
void deletePopulation(Population population) {
    if (population->next != NULL) {
        deletePopulation(population->next);
    }
    deleteIndividu(population->individu);
    free(population);
}

Population parition(Population first, Population last) {
    // Get first node of given linked list
    Population pivot = first;
    Population front = first;
    Individu temp;
    while (front != NULL && front != last) {
        if (quality(front->individu) > quality(last->individu)) {
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

void quick_sort(Population first, Population last) {
    if (first == last) {
        return;
    }
    Population pivot = parition(first, last);

    if (pivot != NULL && pivot->next != NULL) {
        quick_sort(pivot->next, last);
    }

    if (pivot != NULL && first != pivot) {
        quick_sort(first, pivot);
    }
}