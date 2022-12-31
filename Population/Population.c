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

//croiser les individus de la population aléatoirement deux à deux
Population croiserPopulation(Population population, float pCroise) {
    // Croiser la population aléatoirement deux à deux
    Population p = population;
    Population q = NULL;
    Population newPopulation = NULL;
    Population newPopLast = NULL;

    while (p != NULL && nbIndividus(p) > 1) {
        q = getIndividuAtIndex(p, rand() % (nbIndividus(p) - 1) + 1);
        croiserIndividus(pCroise, p->individu, q->individu);
        if (newPopulation != NULL) {
            newPopLast = newPopulation;
            while (newPopLast->next != NULL) {
                newPopLast = newPopLast->next;
            }
            newPopLast->next = q;
        } else {
            newPopulation = q;
            newPopLast = q;
        }
        Population prevQ = p;
        while (prevQ->next != q && prevQ->next != NULL) {
            prevQ = prevQ->next;
        }
        prevQ->next = q->next;
        newPopLast->next->next = p;
        p = p->next;
        newPopLast->next->next->next = NULL;
    }
    if (nbIndividus(p) == 1) {
        newPopLast = newPopulation;
        while (newPopLast != NULL) {
            newPopLast = newPopLast->next;
        }
        newPopLast = p;
        newPopLast->next = NULL;
    }
    return newPopulation;
}

Population getIndividuAtIndex(Population population, int index) {
    // Retourne l'individu à l'index donné
    for (int i = 0; i < index; i++) {
        population = population->next;
    }
    return population;
}

int getIndexOfIndividu(Population population, Individu individu) {
    // Retourne l'index de l'individu donné
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

Population partition(Population first, Population last) {
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
    Population pivot = partition(first, last);

    if (pivot != NULL && pivot->next != NULL) {
        quick_sort(pivot->next, last);
    }

    if (pivot != NULL && first != pivot) {
        quick_sort(first, pivot);
    }
}