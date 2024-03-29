#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 64
#define MAX_LINE 1024
#define ERROR_MESSAGE -1
#define TABLE_SIZE 11

typedef struct _city {
    char ct_name[MAX_STRING];
    int pop;
    struct _city* left;
    struct _city* right;
} city;

typedef struct _country {
    char co_name[MAX_STRING];
    char file_name[MAX_STRING];
    struct _country* next;
    struct _city* root;
} country;

country* hash_table[TABLE_SIZE];

// Function prototypes
int read_co_from_file(country* head);
int country_insert_sorted(country* head, country* for_insert);
country* country_add(country* head, char* line);
int print_country_list(country* head);
int read_city_from_file(city* root, char* file_name);
city* city_add(city* root, char* buffer);
int city_insert_sorted(city* root, city* for_insert);
void print_all(country* head);
void print_cities_sorted(city* to_print);
int query(char* s_country, int pop, country* head);
int find_cities(city* root, int pop);
int interaction(country* head);
int delete_all(country* head);
int delete_after(country* head);
int hash_table_init();
int hash(char* name);
int hash_table_insert(country* head);
void print_hash_table();

int main() {
    country head = {
        .co_name = {0},
        .file_name = {0},
        .next = NULL,
        .root = NULL
    };

    int end = 0;

    end = interaction(&head);

    if (!end) {
        printf("Success!\n");
    }
    else {
        return ERROR_MESSAGE;
    }

    return 0;
}

int read_co_from_file(country* head) {
    FILE* f = NULL;
    country* temp = head;
    char buffer[MAX_STRING] = { 0 };
    char fileName[MAX_STRING] = { 0 };

    printf("Enter the filename: (e.g drzave.txt)\n");
    scanf(" %s", fileName);
    f = fopen(fileName, "r");

    if (!f) {
        perror("Can't open file!\n");
        return ERROR_MESSAGE;
    }

    while (fgets(buffer, MAX_LINE, f) != NULL) {
        temp = country_add(head, buffer);
    }

    fclose(f);
    return 0;
}

int country_insert_sorted(country* head, country* for_insert) {
    country* temp = head;

    if (temp->next == NULL) {
        temp->next = for_insert;
        for_insert->next = NULL;
        return 1;
    }

    while (temp->next != NULL) {
        if (strcmp(temp->next->co_name, for_insert->co_name) > 0) {
            for_insert->next = temp->next;
            temp->next = for_insert;
            return 0;
        }
        temp = temp->next;
    }

    temp->next = for_insert;
    for_insert->next = NULL;
    return 1;
}

country* country_add(country* head, char* line) {
    char* pointer = line;
    country* new_co = NULL;
    int b = 0;

    new_co = malloc(sizeof(country));

    if (!new_co) {
        printf("malloc failed\n");
        return NULL;
    }

    if (sscanf(pointer, " %s %n", new_co->co_name, &b) == 1) {
        pointer += b;
        sscanf(pointer, " %s %n", new_co->file_name, &b);
        country_insert_sorted(head, new_co);

        new_co->root = malloc(sizeof(city));
        new_co->root->pop = 0;
        new_co->root->right = NULL;
        new_co->root->left = NULL;

        read_city_from_file(new_co->root, new_co->file_name);
    }

    return new_co;
}

int print_country_list(country* head) {
    country* temp = head->next;

    printf("Lists of countries/cities read:\n\n");

    while (temp != NULL) {
        printf("%s\n", temp->co_name);
        print_cities_sorted(temp->root);
        printf("\n");
        temp = temp->next;
    }

    return 0;
}

int read_city_from_file(city* root, char* file_name) {
    city* temp = root;
    char buffer[MAX_LINE];

    FILE* f = fopen(file_name, "r");
    if (!f) {
        printf("Unable to open file\n");
        return ERROR_MESSAGE;
    }

    while (fgets(buffer, MAX_LINE, f) != NULL) {
        temp = city_add(root, buffer);
    }

    fclose(f);
    return 0;
}

city* city_add(city* root, char* buffer) {
    char* pointer = buffer;
    city* new_city;
    int b = 0;

    new_city = malloc(sizeof(city));
    new_city->pop = 0;
    new_city->right = NULL;
    new_city->left = NULL;

    if (!new_city) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    if (sscanf(pointer, "%s %d", new_city->ct_name, &new_city->pop) == 2) {
        city_insert_sorted(root, new_city);
    }

    return new_city;
}

int city_insert_sorted(city* root, city* for_insert) {
    city* temp = root;
    city* temp_parent = NULL;

    while (temp != NULL) {
        temp_parent = temp;
        if (temp->pop > for_insert->pop) {
            temp = temp->left;
        }
        else if (temp->pop < for_insert->pop) {
            temp = temp->right;
        }
        else {
            if (strcmp(temp->ct_name, for_insert->ct_name) > 0) {
                temp = temp->left;
            }
            else {
                temp = temp->right;
            }
        }
    }

    if (temp_parent == NULL) {
        root = for_insert;
    }
    else if (temp_parent->pop > for_insert->pop) {
        temp_parent->left = for_insert;
    }
    else {
        temp_parent->right = for_insert;
    }

    return 1;
}

void print_cities_sorted(city* to_print) {
    if (to_print == NULL) {
        return;
    }

    print_cities_sorted(to_print->left);
    printf("%s %d\n", to_print->ct_name, to_print->pop);
    print_cities_sorted(to_print->right);
}

int query(char* s_country, int pop, country* head) {
    country* temp = head;

    while (temp != NULL) {
        if (strcmp(temp->co_name, s_country) == 0) {
            find_cities(temp->root->right, pop);
        }
        temp = temp->next;
    }

    return 0;
}

int find_cities(city* root, int pop) {
    city* temp = root;

    while (temp != NULL) {
        if (temp->pop > pop) {
            printf("%s %d\n", temp->ct_name, temp->pop);
            print_cities_sorted(temp->right);
        }
        temp = temp->left;
    }

    return 0;
}

int delete_all(country* head) {
    while (head->next != NULL) {
        delete_after(head);
    }
    return 0;
}

int delete_after(country* head) {
    country* toDelete = head->next;

    if (toDelete == NULL) {
        return 0;  // Nothing to delete
    }

    head->next = toDelete->next;
    free(toDelete);

    return 0;
}

int hash_table_init() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_table[i] = NULL;
    }

    return 0;
}

int hash(char* name) {
    int i = 0;
    int hash_value = 0;

    while (name[i] != '\0' && i < 5) {
        hash_value += name[i];
        i++;
    }

    return hash_value % TABLE_SIZE;
}

int hash_table_insert(country* head) {
    country* temp = head->next;

    while (temp != NULL) {
        int index = hash(temp->co_name);
        temp->next = hash_table[index];
        hash_table[index] = temp;
        temp = temp->next;
    }

    return 0;
}

void print_hash_table() {
    printf("Start\n");

    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("\t%i\t---\n", i);

        country* forPrint = hash_table[i];
        while (forPrint != NULL) {
            printf("\t\t%s - ", forPrint->co_name);
            print_cities_sorted(forPrint->root);
            printf("\n");

            forPrint = forPrint->next;
        }
    }

    printf("End\n");
}


int interaction(country* head) {
    char s_name[MAX_STRING] = { 0 };
    int s_pop = 0;

    read_co_from_file(head);
    print_country_list(head);

    printf("Input country name and desired population: \n");
    scanf(" %s %d", s_name, &s_pop);

    hash_table_init();
    hash_table_insert(head);
    print_hash_table();

    query(s_name, s_pop, head);
    delete_all(head);

    return 0;
}


