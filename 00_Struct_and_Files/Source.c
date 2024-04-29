#include<stdio.h>
#include<string.h>
#include<stdlib.h>
// #include<malloc.h>
#define LINESIZE 128

typedef struct Supercar Supercar;

struct Supercar {
    int id;
    char* brand;
    float engineSize;
    int price;
};

void printSupercarToConsole(Supercar supercar) {
    printf("\n-----\nId: %d\nBrand: %s\nEngine size: %.2f\nPrice: %d\n",
           supercar.id, supercar.brand, supercar.engineSize, supercar.price);
}

Supercar readCarFromFile(FILE* f) {
    Supercar supercar;
    char buffer[LINESIZE];

    fgets(buffer, LINESIZE, f);
    supercar.id = (int)strtol(buffer, NULL, 10);

    fgets(buffer, LINESIZE, f);
    buffer[strcspn(buffer, "\n")] = '\0';
    supercar.brand = malloc(strlen(buffer) + 1);
    strcpy(supercar.brand, buffer);

    fgets(buffer, LINESIZE, f);
    supercar.engineSize = strtof(buffer, NULL);

    fgets(buffer, LINESIZE, f);
    supercar.price = (int)strtol(buffer, NULL, 10);

    return supercar;
}

void readCarsFromFile(const char* fileName, Supercar** carsArray, int* carsNumber) {
    FILE* f = fopen(fileName, "r");
    char buffer[LINESIZE];

    fgets(buffer, LINESIZE, f);
    *carsNumber = (int)strtol(buffer, NULL, 10);

    *carsArray = malloc((*carsNumber) * sizeof(Supercar));
    for(int i = 0; i < (*carsNumber); i++) {
        (*carsArray)[i] = readCarFromFile(f);
    }

    fclose(f);
}

int main() {
    Supercar* carsArray;
    int carsNumber;

    readCarsFromFile("supercar.txt", &carsArray, &carsNumber);

    for(int i = 0; i < carsNumber; i++) {
        printSupercarToConsole(carsArray[i]);
    }

    return 0;
}