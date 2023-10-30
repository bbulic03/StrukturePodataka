#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Person;
typedef struct Person* Position;
typedef struct Person {
	char ime[50];
	char prezime[50];
	int godina_rodenja;
	Position next;
}person;

Position CreatePerson();
int AddInFront(Position P);
int ListDisplay(Position P);
int AddAtEnd(Position P);
Position FindLast(Position P);
int AddAtEnd(Position P);
Position findsurname(Position P);
int deletePerson(Position P);
Position findprev(Position P);
int InsertAfter(Position P);
int printperson(Position P);
int menu(Position Head);
int bubblesort(Position P);


int main() {
	person Head;
	Head.next = NULL;

	menu(&Head);

	return EXIT_SUCCESS;
}

int menu(Position Head) {
	int choice = 0;
	Position P = NULL;
	Position prev = NULL;
	while (1) {
		printf("Za unos na pocetak liste unesi 1 \nZa unos na kraj liste unesi 2 \nZa ispis liste unesi 3 \nZa trazenje osobe unesi 4 \nZa brisanje osobe unesi 5 \nZa unos nakon osobe unesi 6 \nZa unos prije osobe unesi 7 \nZa sortiranje liste unesi 8");
		scanf("%d", &choice);

		switch (choice) {
			case '1':
				AddInFront(Head);
				continue;
			case '2':
				AddAtEnd(Head);
				continue;
			case '3':
				ListDisplay(Head);
				continue;
			case '4':
				P=findsurname(Head->next);
				if (P) {
					printperson(P);
				}
				else {
					printf("Can't find wanted person in the list! ");
				}
				continue;
			case '5':
				deletePerson(Head);
				continue;
			case '6':
				P = findsurname(Head->next);
				if (P) {
					InsertAfter(P);
				}
				else {
					printf("Can't find wanted person in the list! ");
				}
				continue;
			case '7':
				prev = findprev(Head);
				if (prev) {
					InsertAfter(prev);
				}
				else {
					printf("Can't find wanted person in the list! ");
				}
				continue;
			case '8':
				bubblesort(Head->next);
				continue;
		}
	}


	return EXIT_SUCCESS;
}
	
Position CreatePerson() {
	Position newperson = NULL;
	char ime[50] = {'0'};
	char prezime[50] = { '0' };
	int godina_rodenja = 0;

	newperson = (Position)malloc(sizeof(person));

	if (newperson == NULL) {
		printf("Neuspjesna alokacija memorije");
		return -1;
	}

	printf("Unesi ime: ");
	scanf("%s", ime);
	printf("Unesi prezime: ");
	scanf("%s", prezime);
	printf("Unesi godinu rodenja: ");
	scanf("%d", &godina_rodenja);

	strcpy(newperson->ime, ime);
	strcpy(newperson->prezime, prezime);
	strcpy(newperson->godina_rodenja, godina_rodenja);

	return newperson;
}

int AddInFront(Position P) {
	Position newperson = NULL;
	newperson=CreatePerson();

	newperson->next = P->next;
	P->next = newperson;
	return EXIT_SUCCESS;
}

Position FindLast(Position P) {
	Position prev = NULL;
	while (P->next != NULL) {
		prev = P;
		P = P->next;
	}
	return prev;
}
int AddAtEnd(Position P) {
	Position newperson = NULL;
	Position last = FindLast(P);
	newperson = CreatePerson();
	
	if (newperson) {
		newperson->next = last->next;
		last->next = newperson;
	}

	return EXIT_SUCCESS;
}

int ListDisplay(Position P) {
	while (P != NULL) {
		printf("%s %s %d \n", P->ime, P->prezime, P->godina_rodenja);
		P = P->next;
	}
	return EXIT_SUCCESS;
}

char getsurname() {
	char surname = { '0' };
	printf("Enter surname: ");
	scanf("%s", surname);
	return surname;
}
Position findsurname(Position P) {
	char surname[50] = { '0' };
	strcpy (surname,getsurname());

	do {
		if (strcmp(P->prezime, surname) == 0) {
			return P;
		}
		else {
			P = P->next;
		}
	} while (P != NULL);

	return -1;
}

int deletePerson(Position head) {
	char surname[50] = { '0' };
	Position P = head;

	strcpy(surname, getsurname());

	if (P->next) {
		Position prev = NULL;
		while (P->next && strcmp(P->prezime,surname) != 0) {
			prev = P;
			P = P->next;
		}
		if (prev && prev->next && strcmp(P->prezime, surname) == 0) {
			printperson(P);
			prev->next = P->next;
			free(P);
		}
		else {
			return -1;
		}
	}
	else {
		return -1;
	}

	return EXIT_SUCCESS;
}

int InsertAfter(Position P) {
	Position newperson = NULL;
	newperson = CreatePerson();

	if (newperson) {
		newperson->next = P->next;
		P->next = newperson;
	}
	return EXIT_SUCCESS;
}

Position findprev(Position P) {
	
	char surname[50] = { '0' };
	strcpy(surname, getsurname());

	if (!P->next) {
		printf("Empty list!\n");
		return -1;
	}

	do {
		if (strcmp(P->next->prezime, surname) == 0) {
			return P;
		}
		else {
			P = P->next;
		}
	} while (P->next != NULL);

	return -1;
}

int printperson(Position P) {
	printf("Ime: %s\t Prezime: %s\t Godina roðenja: %d", P->ime, P->prezime, P->godina_rodenja);
	return EXIT_SUCCESS;
}

int bubblesort(Position P) {
	int brz = 0;
	Position last = NULL;
	
	if (!P) {
		printf("Empty list! ");
		return -1;
	}
	else if (!P->next) {
		printf("One element in list, can't sort! ");
		return -1;
	}
	do {
		brz = 0;
		while (P->next != last) {
			if (strcmp(P->prezime, P->next->prezime) > 0) {
				char tempime[50];
				char tempprezime[50];
				int tempgodrod;

				strcpy(tempime, P->ime);
				strcpy(tempprezime, P->prezime);
				tempgodrod = P->godina_rodenja;

				strcpy(P->ime, P->next->ime);
				strcpy(P->prezime, P->next->prezime);
				P->godina_rodenja = P->next->godina_rodenja;

				strcpy(P->next->ime, tempime);
				strcpy(P->next->prezime, tempprezime);
				P->next->godina_rodenja = tempgodrod;

				brz = 1;
			}
			P = P->next;
		}
		last = P;
	} while (brz);

	return EXIT_SUCCESS;
}