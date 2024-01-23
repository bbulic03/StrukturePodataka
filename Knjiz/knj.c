#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Book;
typedef struct Book* book_position;
typedef struct Book {
	char title[100];
	char authorname[100];
	char authorsurname[100];
	int available;
	int year;
	book_position next;
}book;

struct User;
typedef struct User* user_position;
typedef struct User {
	char name[50];
	char surname[50];
	int borrowed_count;
	int ID;
	user_position next;
}user;

int addBook(book_position head, char title[], char authorname[], char authorsurname[], int year, int copies);
int addUser(user_position Head);
int printBooks(book_position Head);
int printUsers(user_position head);
int searchBooksByYear(book_position head, int year);
int searchBooksByAuthor(book_position head, char name[], char surname[]);
void borrowBook(book_position b_head, user_position u_head);
int freeBooks(book_position head);
int freeUsers(user_position head);
void returnBook(book_position b_head, user_position u_head);
int addUserFromFile(user_position head, char name[50], char surname[50], int ID, int borrowedcount);
int writeBooksToFile(book_position head);
int readBooksFromFile(book_position head);
int readUsersFromFile(user_position head);
int writeUsersToFile(user_position head);
user_position findUser(user_position head, int userID);



int main() {
	book b_head = { .next = NULL, .title = {0}, .authorname = {0}, .authorsurname = {0}, .available = 0, .year = 0 };
	user u_head = { .next = NULL, .name = {0}, .surname = {0}, .borrowed_count = 0, .ID = 0 };

	addBook(&b_head, "Pride_and_prejudice", "Jane", "Austen", 1813, 5);
	addBook(&b_head, "Crime_and_punishment", "Fyodor", "Dostoevsky", 1866, 7);
	addBook(&b_head, "Don_Quixote", "Miguel" ,"Cervantes", 1615, 8);

	while (1) {
		int choice = 0;
		int year = 0;
		char name[100] = { 0 };
		char surname[100] = { 0 };

		printf("\nInput your choice:\n 1)Add User\n 2)PrintBooks\n 3)PrintUsers\n 4)SearchBooksByYear\n 5)SearchBooksByAuthor\n 6)BorrowBook\n 7)ReturnBook\n 8)Save\n 9)Load\n 10)Exit\n\n");
		scanf("%d", &choice);

		if (choice==1) {
			addUser(&u_head);
		}
		else if (choice == 2) {
			printBooks(&b_head);
		}
		else if (choice == 3) {
			printUsers(&u_head);
		}
		else if (choice == 4) {
			printf("Insert what year would you like to search by: ");
			scanf("%d", &year);
			searchBooksByYear(&b_head, year);
		}
		else if (choice == 5) {
			printf("Insert author you want to search for (name surname): ");
			scanf("%s %s", &name, &surname);
			searchBooksByAuthor(&b_head, name, surname);
		}
		else if (choice == 6) {
			borrowBook(&b_head, &u_head);
		}
		else if (choice == 7) {
			returnBook(&b_head, &u_head);
		}
		else if (choice == 8) {
			writeBooksToFile(&b_head);
			writeUsersToFile(&u_head);
		}
		else if (choice == 9){
			readBooksFromFile(&b_head);
			readUsersFromFile(&u_head);
		}
		else if (choice == 10) {
			freeBooks(&b_head);
			freeUsers(&u_head);
			break;
		}
	}

	return 0;
}

int addBook(book_position head, char title[], char authorname[], char authorsurname[], int year, int copies) {
	book_position newBook = (book_position)malloc(sizeof(book));

	if (newBook == NULL) {
		printf("Error allocating memory for a new book.\n");
		return -1;
	}

	strcpy(newBook->title, title);
	strcpy(newBook->authorname, authorname);
	strcpy(newBook->authorsurname, authorsurname);

	newBook->year = year;
	newBook->available = copies;

	book_position current = head;
	while (current->next != NULL && strcmp(title, current->next->title) > 0) {
		current = current->next;
	}

	newBook->next = current->next;
	current->next = newBook;

	return 0;
}

int addUser(user_position head) {
	char name[50] = { 0 };
	char surname[50] = { 0 };
	int ID = 0;
	user_position newUser = (user_position)malloc(sizeof(user));

	if (newUser == NULL) {
		printf("Error allocating memory for a new user.\n");
		return -1;
	}

	printf("User name: ");
	scanf("%s", name);
	strcpy(newUser->name, name);

	printf("User surname: ");
	scanf("%s", surname);
	strcpy(newUser->surname, surname);

	printf("User ID: ");
	scanf("%d", &ID);
	newUser->ID = ID;

	newUser->borrowed_count = 0;

	user_position current = head;
	while (current->next != NULL &&
		(strcmp(name, current->next->name) > 0 ||
			(strcmp(name, current->next->name) == 0 &&
				(strcmp(surname, current->next->surname) > 0 ||
					(strcmp(surname, current->next->surname) == 0 && ID > current->next->ID))))) {
		current = current->next;
	}

	newUser->next = current->next;
	current->next = newUser;

	printf("User added: %s %s, ID: %d\n", newUser->name, newUser->surname, newUser->ID);

	return 0;
}

int printBooks(book_position head) {
	if (head->next == NULL) {
		printf("No books found\n");
		return -1;
	}

	head = head->next;
	while (head != NULL) {
		printf("%s by %s %s from year %d, Available copies: %d\n", head->title, head->authorname, head->authorsurname, head->year, head->available);
		head = head->next;
	}
	return 0;
}

int printUsers(user_position head) {
	if (head->next == NULL) {
		printf("No users found");
		return -1;
	}
	head = head->next;
	while (head != NULL) {
		printf("Name: %s\nSurname: %s\nID: %d\nBorrowed books:%d\n", head->name, head->surname, head->ID,head->borrowed_count);
		head = head->next;
	}

	return 0;
}

int searchBooksByYear(book_position head, int year) {
	head = head->next;
	int count = 0;

	printf("Books from year %d:\n", year);
	while (head != NULL) {
		if (head->year == year) {
			printf("\t%s by %s %s, Available copies: %d\n", head->title, head->authorname, head->authorsurname, head->available);
			count = count + 1;
		}
		head = head->next;
	}
	if (!count) {
		printf("\tSorry, no books with wanted year found.\n ");
	}

	return 0;
}

int searchBooksByAuthor(book_position head, char name[], char surname[]) {
	head = head->next;
	int count = 0;

	printf("Books from author %s %s:\n", name, surname);
	while (head != NULL) {
		if (strcmp(head->authorname, name) == 0 && strcmp(head->authorsurname, surname) == 0) {
			printf("\t%s by %s %s, Available copies: %d\n", head->title, head->authorname, head->authorsurname, head->available);
			count = count + 1;
		}
		head = head->next;
	}
	if (!count) {
		printf("\tSorry, no books by the wanted author found.\n ");
	}

	return 0;
}

void borrowBook(book_position b_head, user_position u_head) {
	int ID = 0;
	char title[100] = { 0 };
	char authorname[100] = { 0 };
	char authorsurname[100] = { 0 };
	int year = 0;
	int amount = 0;
	int choice = 0;

	printf("Insert user ID and book information below.\n ");
	printf("\nUser ID:\t");
	scanf("%d", &ID);
	printf("\nBook title:\t");
	scanf("%s", &title);
	printf("\nAuthor name:\t");
	scanf("%s", &authorname);
	printf("\nAuthor surname:\t");
	scanf("%s", &authorsurname);
	printf("\nYear:\t");
	scanf("%d", &year);
	printf("\nHow many copies do you want to borrow?:\t");
	scanf("%d", &amount);
	
	user_position currentUser=findUser(u_head, ID);

	book_position current = b_head->next;

	while (current != NULL) {
		if (strcmp(current->title, title) == 0 && strcmp(current->authorname, authorname) == 0 && strcmp(current->authorsurname, authorsurname) == 0 && current->year == year) {
			if (current->available < amount) {
				printf("There are not that many copies available, we have %d copies available.\nWould you like all the available copies?\nWarning: User can't borrow more than 5 books\n", current->available);
				printf("If your choice is yes, input 1, else, input 2:\t");
				scanf("%d", &choice);
				if (choice == 1) {
					if (currentUser->borrowed_count+current->available<=5) {
						printf("\nUser %s %s ID: %d borrowed %d copies of %s\n", currentUser->name, currentUser->surname, currentUser->ID, current->available, current->title);
						currentUser->borrowed_count += current->available;
						current->available = 0;
						return;
					}
					else {
						printf("User can't borrow that many copies.\n");
						return;
					}
				}
				else {
					return;
				}
			}
			if (currentUser->borrowed_count + amount > 4) {
				printf("%s %s (ID: %d) already borrowed the maximum number of books.\n",
					currentUser->name, currentUser->surname, currentUser->ID);
				return;
			}
			
			if (current->available >= amount) {
				currentUser->borrowed_count += amount;
				current->available -= amount;
				printf("\nUser %s %s ID: %d borrowed %d copies of %s\n", currentUser->name, currentUser->surname, currentUser->ID, amount, current->title);
				return;
			}
		}
		current = current->next;
	}
	printf("Book not found.\n");
}
int freeBooks(book_position head) {
	book_position current = head->next;
	while (current != NULL) {
		book_position temp = current;
		current = current->next;
		head->next = current;
		free(temp);
	}

	return 0;
}

int freeUsers(user_position head) {
	user_position current = head->next;
	while (current != NULL) {
		user_position temp = current;
		current = current->next;
		head->next = current;
		free(temp);
	}

	return 0;
}

void returnBook(book_position b_head, user_position u_head) {
	int ID = 0;
	char title[100] = { 0 };
	char authorname[100] = { 0 };
	char authorsurname[100] = { 0 };
	int year = 0;
	int amount = 0;

	printf("Insert user ID and book information below.\n ");
	printf("\nUser ID:\t");
	scanf("%d", &ID);
	printf("\nBook title:\t");
	scanf("%s", &title);
	printf("\nAuthor name:\t");
	scanf("%s", &authorname);
	printf("\nAuthor surname:\t");
	scanf("%s", &authorsurname);
	printf("\nYear:\t");
	scanf("%d", &year);
	printf("\nHow many copies do you want to return?:\t");
	scanf("%d", &amount);

	user_position currentUser = findUser(u_head,ID);

	book_position current = b_head->next;

	while (current != NULL) {
		if (strcmp(current->title, title) == 0 && strcmp(current->authorname, authorname) == 0 && strcmp(current->authorsurname, authorsurname) == 0 && current->year == year) {
			currentUser->borrowed_count -= amount;
			b_head->available += amount;
			printf("%s %s (ID: %d) returned the book %s.\n",
				currentUser->name, currentUser->surname, currentUser->ID, title);
			return;
		}
		current = current->next;
	}
	printf("Book not found\n");
}

int addUserFromFile(user_position head, char name[50], char surname[50], int ID, int borrowedcount) {
	user_position newUser = (user_position)malloc(sizeof(user));

	strcpy(newUser->name, name);
	strcpy(newUser->surname, surname);
	newUser->ID = ID;
	newUser->borrowed_count = borrowedcount;

	user_position current = head;
	while (current->next != NULL &&
		(strcmp(name, current->next->name) > 0 ||
			(strcmp(name, current->next->name) == 0 &&
				(strcmp(surname, current->next->surname) > 0 ||
					(strcmp(surname, current->next->surname) == 0 && ID > current->next->ID))))) {
		current = current->next;
	}

	newUser->next = current->next;
	current->next = newUser;

	return 0;
}

#include <stdio.h>

int writeBooksToFile(book_position head) {
	char filename[50] = { 0 };
	printf("\nInsert filename to write books in: ");
	scanf("%s", filename);
	FILE* file = fopen(filename, "w");

	if (file == NULL) {
		printf("Error opening file for writing.\n");
		return;
	}

	head = head->next;

	while (head != NULL) {
		fprintf(file, "%s %s %s %d %d\n", head->title, head->authorname, head->authorsurname, head->year, head->available);
		head = head->next;
	}

	fclose(file);

	return 0;
}

int readBooksFromFile(book_position head) {
	char filename[50] = { 0 };
	printf("\nInsert filename to read books from: ");
	scanf("%s", filename);
	FILE* file = fopen(filename, "r");

	if (file == NULL) {
		printf("Error opening file for reading.\n");
		return;
	}
	freeBooks(head);
	char title[100], authorname[100], authorsurname[100];
	int year, available;

	while (fscanf(file, "%s %s %s %d %d", title, authorname, authorsurname, &year, &available) == 5) {
		addBook(head, title, authorname, authorsurname, year, available);
	}

	fclose(file);

	return 0;
}

int writeUsersToFile(user_position head) {
	char filename[50] = { 0 };
	printf("\nInsert filename to write users in: ");
	scanf("%s", filename);
	FILE* file = fopen(filename, "w");

	if (file == NULL) {
		printf("Error opening file for writing.\n");
		return;
	}

	head = head->next;

	while (head != NULL) {
		fprintf(file, "%s %s %d %d\n", head->name, head->surname, head->ID, head->borrowed_count);
		head = head->next;
	}

	fclose(file);

	return 0;
}

int readUsersFromFile(user_position head) {
	char filename[50] = { 0 };
	printf("\nInsert filename to read users from: ");
	scanf("%s", filename);
	FILE* file = fopen(filename, "r");

	if (file == NULL) {
		printf("Error opening file for reading.\n");
		return;
	}

	char name[50], surname[50];
	int ID, borrowed_count;

	while (fscanf(file, "%s %s %d %d", name, surname, &ID, &borrowed_count) == 4) {
		addUserFromFile(head, name, surname, ID, borrowed_count);
	}

	fclose(file);

	return 0;
}

user_position findUser(user_position head, int userID) {
	user_position current = head->next;

	while (current != NULL) {
		if (current->ID == userID) {
			return current;
		}
		else {
			current = current->next;
		}
	}

	if (current == NULL) {
		printf("\nUser not found\n");
		return NULL;
	}
}




