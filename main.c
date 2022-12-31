//
// Created by natha on 08/12/2022.
//
#include
<stdlib.h>
#include
<stdio.h>
#include
<time.h>
#include
"Individu/Individu.h"
#include
"Population/Population.h"

#define
taillePopulation 100
#define
tailleIndividu 16
#define
nGen 200
#define
pCroise 0.5


int main() {

srand(time(NULL));
Population population = createPopulation(taillePopulation, tailleIndividu);
Population last;

for (int i = 0; i < nGen; i++) {
population = croiserPopulation(population, pCroise);
last = population;
while (last->next != NULL) {
last = last->next;
}
quick_sort(population, NULL);
}
afficherPopulation(population, "Population");
quick_sort(population, last);
afficherPopulation(population, "Population triée");

return 0;
}