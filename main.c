//
// Created by natha on 08/12/2022.
//
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Individu/Individu.h"
#include "Population/Population.h"

#define tailleIndividu 16
#define nGen 200
#define A 0.1
#define B 5
#define MODE 0
#define taillePopulation 100
#define pCroise 0.5
#define nbSelect 50

int main() {
#if MODE == 0
    srand(time(NULL));
    Population last;
    Population population = createPopulation(taillePopulation, tailleIndividu);
    for (int k = 1; k <= nGen; k++) {
        population = croiserPopulation(population, pCroise);
        last = population;
        while (last->next != NULL) {
            last = last->next;
        }
        quick_sort(population, last, A, B);
        population = selectPopulation(population, nbSelect);
        last = population;
        while (last->next != NULL) {
            last = last->next;
        }
        quick_sort(population, last, A, B);
        printf("Generation %d : ", k);
        afficherIndividu(population->individu, "Meilleur individu", A, B);
    }
    deletePopulation(population);
#endif
#if MODE == 1
    // Crée un fichier .csv avec les résultats de la simulation
    FILE *f = fopen("result.csv", "w");
    if (f == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    srand(time(NULL));
    Population last;
    float pCroiseS[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
    float tSelectS[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
    fprintf(f, "Valeur, Qualite, Probabilite de Croisement, Taux de selection, Taille Population, N°Generation\n");
    for (int taillePopulation = 20; taillePopulation <= 200; taillePopulation += 20) {
        for (int i = 0; i < sizeof(pCroiseS) / sizeof(float); i++) {
            for (int j = 0; j < sizeof(tSelectS) / sizeof(float); j++) {
                float pCroise = pCroiseS[i];
                int nbSelect = tSelectS[j] * taillePopulation;
                Population population = createPopulation(taillePopulation, tailleIndividu);
                for (int k = 1; k <= nGen; k++) {
                    population = croiserPopulation(population, pCroise);
                    last = population;
                    while (last->next != NULL) {
                        last = last->next;
                    }
                    quick_sort(population, last, A, B);
                    population = selectPopulation(population, nbSelect);

                    if (k % 20 == 0) {
                        last = population;
                        while (last->next != NULL) {
                            last = last->next;
                        }
                        quick_sort(population, last, A, B);
                        fprintf(f, "%d, %.5f, %.1f, %.1f, %d, %d\n", decodeIndividu(population->individu),
                                quality(population->individu, A, B), pCroise, tSelectS[j], taillePopulation, k);
                    }
                }
                deletePopulation(population);
            }
        }
    }
    fclose(f);
#endif
    return 0;
}