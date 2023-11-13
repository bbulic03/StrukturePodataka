#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGTH 1024

struct Stog;
typedef struct Stog* position;
typedef struct Stog {
	int element;
	position next;
}stog;

int readFile(char filename, position stog);
position createNewEl(double element);
int push(position head, position newel);
int pop(position head, double* result);
int addToBeg(position head, double element);
int addAfter(position head, position newel);
int deleteAfter(position head);
int deleteAll(position stog);
int calcPostfix(position stog, char op);
int printAll(position head);

int main() {
	stog head;
	head.element = 0;
	head.next = NULL;
	char filename[50];

	printf("Unesite ime datoteke iz koje zelite procitati postfix: \n");

	scanf(" %s", filename);

	readFile(filename, &head);

	return EXIT_SUCCESS;
}

int readFile(char filename[], position stog) {
	FILE* fp = NULL;
	double element = 0;
	int numByt = 0;
	char* row = NULL;
	int value = 0;
	char op = 0;
	char temprow[MAX_LENGTH] = { 0 };

	fp = fopen(filename, "r");

	row = (char*)malloc(sizeof(char));

	if (!row) {
		printf("Nemoguca alokacija memorije! ");
		return -1;
	}
	if (!fp) {
		printf("File not found! ");
		return -1;
	 }
	fgets(temprow, MAX_LENGTH, fp);
	row = temprow;

	while (strlen(row) > 0) {
		value = sscanf(row, "%lf %n", &element, &numByt);
		if (value != 0) {
			deleteAll(stog);
		}
		else {
			sscanf(row, " %c %n", &op, &numByt);
			value = calcPostfix(stog, op);

			if (value != 0) {
				deleteAll(stog);
			}
		}
		row += numByt;
	}
	printf("Rezultat: ");
	printAll(stog);

	fclose(fp);

	return EXIT_SUCCESS;
}

position createNewEl(double element) {
	position newel = NULL;

	newel = (position)malloc(sizeof(stog));
	if (!newel) {
		printf("Error while allocating memory! ");
		return -1;
	}
	newel->element = element;
	newel->next = NULL;

	return newel;
}

int push(position head, position newel) {
	newel->next = head->next;
	head->next = newel;

	return EXIT_SUCCESS;
}

int pop(position head, double* result) {
	if (head->next==NULL) {
		printf("Empty list! ");
		return -1;
	}
	*result = head->next->element;

	deleteAfter(head);

	return EXIT_SUCCESS;
}

int addToBeg(position head,double element) {
	position newel = NULL;
	newel = createNewEl(element);

	if (!newel) {
		printf("New element not created! ");
		return -1;
	}

	addAfter(head ,newel);

	return EXIT_SUCCESS;
}

int addAfter(position head, position newel) {
	newel->next = head->next;
	head->next = newel;

	return EXIT_SUCCESS;
}

int deleteAfter(position head) {
	position temp = NULL;

	temp = head->next;

	if (!temp) {
		return -1;
	}
	head->next = temp->next;

	free(temp);

	return EXIT_SUCCESS;
}

int deleteAll(position stog) {
	while (stog->next != NULL) {
		deleteAfter(stog);
	}

	return EXIT_SUCCESS;
}

int calcPostfix(position stog, char op) {
	double el1 = 0;
	double el2 = 0;
	int status = 0;
	double result = 0;

	status = pop(stog, &el2);
	if (status != 0) {
		return -1;
	}
	status = pop(stog, &el1);
	if (status != 0) {
		return -1;
	}
	switch (op) {
	case '+':
		result = el1 + el2;
		break;
	case '*':
		result = el1 * el2;
		break;
	case '-':
		result = el1 - el2;
		break;
	case '/':
		if (el2 == 0) {
			printf("Not possible to divide with 0! ");
			return -1;
		}
		else {
			result = el1 / el2;
			break;
		}
	default:
		break;
	}
	addToBeg(stog, result);

	return EXIT_SUCCESS;
}

int printAll(position head) {
	while (head->next != NULL) {
		head = head->next;

		printf("%.2f\n", head->element);
	}

	return EXIT_SUCCESS;
}