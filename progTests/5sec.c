#include <stdio.h>
#include <time.h>

int main(){

    int debut = clock();
    int tempsPasse = (double)(clock() - debut) / CLOCKS_PER_SEC;
    while(tempsPasse<5){
        tempsPasse = (double)(clock() - debut) / CLOCKS_PER_SEC;
    }

    printf("Fin des 5sec\n");
    return 0;
}