#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Poli* Position;
typedef struct Poli {
	int pot;
	int koef;
	Position next;
}poli;

int unosprvi(Position Head1);
int unosdrugi(Position Head2);
int ispis(Position First);

int main() {
	poli Head1;
	Head1.next == NULL;
	poli Head2;
	Head2.next == NULL;

	unosprvi(&Head1);
	unosdrugi(&Head2);
	ispis(Head1.next);
	ispis(Head2.next);

	return EXIT_SUCCESS;
}

int unosprvi(Position Head1) {
	FILE* fp = NULL;
	fp = fopen("pol1.txt", "r");

	if (!fp) {
		printf("Greska u otvranju datoteke! ");
		return -1;
	}

	while (!feof(fp)) {
		Position q = NULL;
		q = (Position)malloc(sizeof(poli));
		if (q == NULL) {
			printf("Greska u alokaciji memorije! ");
			return -1;
		}

		Position temp, prev;
		temp = Head1->next;
		prev = Head1;

		fscanf(fp, "%d %d", &q->koef, &q->pot);
		while (temp != NULL && temp->pot<q->pot) {
			prev = temp;
			temp = temp->next;
		}
		prev->next = q;
		if (temp != NULL) {
			q->next = temp;
		}
		else {
			q->next = NULL;
		}
	}
	return EXIT_SUCCESS;
}

int unosdrugi(Position Head2) {
	FILE* fp = NULL;
	fp = fopen("pol2.txt", "r");

	if (!fp) {
		printf("Greska u otvranju datoteke! ");
		return -1;
	}

	while (!feof(fp)) {
		Position q = NULL;
		q = (Position)malloc(sizeof(poli));
		if (q == NULL) {
			printf("Greska u alokaciji memorije! ");
			return -1;
		}

		Position temp, prev;
		temp = Head2->next;
		prev = Head2;

		fscanf(fp, "%d %d", &q->koef, &q->pot);
		while (temp != NULL && temp->pot < q->pot) {
			prev = temp;
			temp = temp->next;
		}
		prev->next = q;
		if (temp != NULL) {
			q->next = temp;
		}
		else {
			q->next = NULL;
		}
	}
	return EXIT_SUCCESS;
}

int ispis(Position First) {
	Position current = First;

	if (current == NULL) {
		printf("Prazan polinom! ");
		return -1;
	}
	while (current != NULL) {
		printf("%d x a^%d\n", &current->koef, &current->pot);
		current = current->next;
	}

	return EXIT_SUCCESS;
}