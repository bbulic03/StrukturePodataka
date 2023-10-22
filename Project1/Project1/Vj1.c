#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE (1024)
#define MAX_SIZE (128)
#define MAX_POINTS (15)
#define FILE_NOT_OPEN (-1)

typedef struct _student{
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	double points;
} Student;

int readNoRowsInFile();
Student* allocateMemoryAndReadStudents(int );
int showStudents(int );
double calculateRelativePoints(FILE* filePointer, int );


int main(){
	int noRows=0;
	Student* students= NULL;

	noRows=readNoRowsInFile();
	if(noRows>0){
		students=allocateMemoryAndReadStudents(noRows);
		showStudents(noRows,students);

		free(students);
	}
	return EXIT_SUCCESS;
}

int readNoRowsInFile(){
	int counter = 0;
	FILE* filePointer=NULL;
	char buffer[MAX_LINE]={0};

	filePointer=fopen("Students.txt", "r");
	if(!filePointer){
		printf("Neuspjesno otvaranje datoteke \n");
		return FILE_NOT_OPEN;
	}

	while(!feof(filePointer)){
		fgets(buffer, MAX_LINE, filePointer);
		counter++;
	}

	fclose(filePointer);
	return counter;
}

Student* allocateMemoryAndReadStudents(int noStudents){
	int counter=0;
	FILE* filePointer=NULL;
	Student* students=NULL;

	students=(Student*)malloc(noStudents*sizeof(Student*));
	if(!students){
		printf("Neuspjesna alokacija memorije \n";)
		return NULL;
	}

	filePointer=fopen("Students.txt", "r");
	if(!filePointer){
		printf("Neuspjesno otvaranje datoteke \n");
		return FILE_NOT_OPEN;
	}

	while(!feof(filePointer)){
		fscanf(filePointer, " %s %s %lf",students[counter].name, students[counter].surname, &students[counter].points);
		counter++;
	}

	fclose(filePointer);

	return students;
}

int showStudents(int noStudents, Student* students){
	for(int counter=0;counter<noStudents;counter++){
		printf("Ime: %s\t Prezime: %s\t Bodovi: %lf\t Relativni bodovi: %lf\n", students[i].name, students[i].surname, &students[i].points, relativePoints(filePointer));
	return EXIT_SUCCESS;
	}
}

double calculateRelativePoints(FILE* filePointer, Student* students, int counter){
	counter=noStudents(filePointer);
	double relativePoints=0;
	int i;
	for(i=0;i<counter;i++){
		relativePoints=students[i].points/MAX_POINTS*100;
	}

	return relativePoints;
}
