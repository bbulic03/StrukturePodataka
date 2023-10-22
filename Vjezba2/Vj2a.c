#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE (1024)

struct Person;
typedef struct Person* Position;
typedef struct Person {
	char ime[MAX_LINE];
	char prezime[MAX_LINE];
	int godina_rodenja;
	Position next;
}person;

int createPersonAndAddInFront(Position P);
int ListDisplay(Position P);

int main() {
	person Head;
	Head.next = NULL;
	createPersonAndAddInFront(&Head);
	ListDisplay(&Head);
	return 0;
}

int createPersonAndAddInFront(Position P) {
	Position newperson = NULL;
	
	newperson = (Position)malloc(sizeof(person));

	if (newperson == NULL) {
		printf("Neuspjesna alokacija memorije");
		return -1;
	}

	printf("Unesi ime: ");
	scanf(" %s", newperson->ime);
	printf("Unesi prezime: ");
	scanf(" %s", newperson->prezime);
	printf("Unesi godinu rodenja: ");
	scanf("%d", &newperson->godina_rodenja);

	newperson->next = P->next;
	P->next = newperson;

	return EXIT_SUCCESS;
}

int ListDisplay(Position P) {
	while (P != NULL) {
		printf("%s %s %d \n", P->ime, P->prezime, P->godina_rodenja);
		P = P->next;
	}
	return EXIT_SUCCESS;
}
