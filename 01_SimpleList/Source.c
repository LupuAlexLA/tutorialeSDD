#include<stdio.h>
#include<string.h>
#include<stdlib.h>
// #include<malloc.h>
#define LINESIZE 128

typedef struct Supercar Supercar;
typedef struct Node Node;

struct Supercar {
    int id;
    char* brand;
    float engineSize;
    int price;
};

struct Node {
    Supercar supercar;
    Node* next;
};

void printSupercarToConsole(Supercar supercar) {
    printf("\n-----\nId: %d\nBrand: %s\nEngine size: %.2f\nPrice: %d\n",
           supercar.id, supercar.brand, supercar.engineSize, supercar.price);
}

Supercar initSupercar(int id, char* brand, float engineSize, int price) {
    Supercar supercar = { .id = id, .brand = brand, .engineSize = engineSize, .price = price };

    supercar.brand = malloc(strlen(brand) + 1);
    strcpy(supercar.brand, brand);

    return supercar;
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

void insertAtB(Node** head, Supercar supercar) {
    Node* newNode = malloc(sizeof(Node));

    newNode->supercar = supercar;
    newNode->next = *head;

    *head = newNode;
}

void insertAtE(Node** head, Supercar supercar) {
    if(*head) {
        Node* aux = *head;

        while (aux->next) {
            aux = aux->next;
        }

        Node* newNode = malloc(sizeof(Node));

        newNode->supercar = supercar;
        newNode->next = NULL;

        aux->next = newNode;
    }
    else
        insertAtB(head, supercar);
}

void parseListAndPrint(Node* head) {
    if(head) {
        while (head) {
            printSupercarToConsole(head->supercar);
            head = head->next;
        }
    }
    else {
        printf("\nLista este goala!\n");
    }
}

Supercar deleteFromB(Node** head) {
    if(*head) {
        Supercar deleted;
        Node* oldHead = *head;

        (*head) = (*head)->next;
        deleted = oldHead->supercar;
        free(oldHead);

        return deleted;
    }
    else {
        return initSupercar(0, "???", 0.0f, 0);
    }
}

Supercar deleteFromE(Node** head) {
    if(*head) {
        if((*head)->next){
            Node* aux = *head;

            while(aux->next->next) {
                aux = aux->next;
            }

            Supercar deleted = aux->next->supercar;
            free(aux->next);
            aux->next = NULL;
            return deleted;
        }
        else {
            Supercar deleted = (*head)->supercar;
            free(*head);
            *head = NULL;
            return deleted;
        }
    }
    else {
        return initSupercar(0, "???", 0.0f, 0);
    }
}

int main() {
    Supercar* carsArray;
    int carsNumber;

    readCarsFromFile("supercar.txt", &carsArray, &carsNumber);

    printf("\n-----\nAfisare elemente din fisier\n");
    for(int i = 0; i < carsNumber; i++) {
        printSupercarToConsole(carsArray[i]);
    }

    Node* head = NULL;
    for(int i = 0; i < carsNumber; i++) {
        insertAtE(&head, carsArray[i]);
    }

    printf("\n-----\nAfisare elemente din lista simpla\n");
    parseListAndPrint(head);

    printf("\n---------------------\n");

    printf("\nBuggati Chiron is available in the parking lot at the entrance!\n");
    insertAtB(&head, initSupercar(0, "Bugatti Chiron", 8.0f, 3000000));
    printf("\nPagani Huayra is available in the parking lot at exit!\n");
    insertAtE(&head, initSupercar(9, "Pagani Huayra", 6.0, 3300000));
    printf("\n-----\nAfisare elemente din lista simpla\n");
    parseListAndPrint(head);

    printf("\nThe first car was sold!\n");
    Supercar deletedFromB =  deleteFromB(&head);
    printSupercarToConsole(deletedFromB);

    printf("\nThe last car was sold!\n");
    Supercar deletedFromE = deleteFromE(&head);
    printSupercarToConsole(deletedFromE);

    printf("\n-----\nAfisare elemente din lista simpla\n");
    parseListAndPrint(head);

    return 0;
}