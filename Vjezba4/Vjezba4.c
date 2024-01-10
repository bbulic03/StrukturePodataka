#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define MAX_LINE (1024)
#define MAX_SIZE (50)

typedef struct Poli* Position;
typedef struct Poli {
    int pot;
    int koef;
    Position next;
} poli;

int unosprvi(Position Head1);
int unosdrugi(Position Head2);
int ispis(Position First);
int zbroj(Position p1, Position p2, Position z);
int umnozak(Position p1, Position p2, Position u);

int main() {
    poli Head1;
    Head1.pot = 0;
    Head1.koef = 0;
    Head1.next = NULL; 
    poli Head2;
    Head2.pot = 0;
    Head2.koef = 0;
    Head2.next = NULL;  
    poli HeadZ;
    HeadZ.next = NULL;
    poli HeadM;
    HeadM.next = NULL;

    unosprvi(&Head1);
    unosdrugi(&Head2);
    ispis(Head1.next);
    ispis(Head2.next);
    zbroj(&Head1, &Head2, &HeadZ);
    umnozak(&Head1, &Head2, &HeadM);

    return EXIT_SUCCESS;
}

int unosprvi(Position P) {
    FILE* fp = NULL;
    fp = fopen("pol1.txt", "r");

    if (!fp) {
        printf("Greska u otvaranju datoteke! ");
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
        temp = P->next;
        prev = P;

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

    fclose(fp);  
    return EXIT_SUCCESS;
}

int unosdrugi(Position Head2) {
    FILE* fp = NULL;
    fp = fopen("pol2.txt", "r");

    if (!fp) {
        printf("Greska u otvaranju datoteke! ");
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

    fclose(fp);  
    return EXIT_SUCCESS;
}

int ispis(Position First) {
    Position current = First;

    if (current == NULL) {
        printf("Prazan polinom! ");
        return -1;
    }
    while (current != NULL) {
        printf("%d x a^%d\n", current->koef, current->pot);
        current = current->next;
    }

    return EXIT_SUCCESS;
}

int zbroj(Position p1, Position p2, Position z)
{
    while (p1->next != NULL && p2->next != NULL)
    {
        Position s = NULL;
        s = (Position)malloc(sizeof(poli));
        if (s == NULL)
        {
            printf("Neuspjesna alokacija memorije!\n");
            return -1;
        }
        s->next = NULL;

        if (p1->next->pot < p2->next->pot)
        {
            s->pot = p1->next->pot;
            s->koef = p1->next->koef;
            p1 = p1->next;
        }
        else if (p1->next->pot > p2->next->pot)
        {
            s->pot = p2->next->pot;
            s->koef = p2->next->koef;
            p2 = p2->next;
        }
        else
        {
            s->pot = p1->next->pot;
            s->koef = (p1->next->koef + p2->next->koef);
            p1 = p1->next;
            p2 = p2->next;
        }
        z->next = s;
        z = s;
    }
    Position temp;
    if (p1->next == NULL)
        temp = p2->next;
    else
        temp = p1->next;
    while (temp != NULL)
    {
        Position s = NULL;
        s = (Position)malloc(sizeof(poli));
        if (s == NULL)
        {
            printf("Neuspjesna alokacija memorije!\n");
            return -1;
        }
        s->next = NULL;
        s->pot = temp->pot;
        s->koef = temp->koef;
        z->next = s;
        z = s;
        temp = temp->next;
    }
    return 0;
}

int umnozak(Position p1, Position p2, Position u)
{
    Position prvi = p1->next;
    Position drugi = p2->next;
    poli P;
    Position s = NULL;
    s = (Position)malloc(sizeof(poli));
    if (s == NULL)
    {
        printf("Neuspjesna alokacija memorije!\n");
        return -1;
    }
    s->next = NULL;
    P.next = s;
    while (prvi != NULL)
    {
        drugi = p2->next;
        while (drugi != NULL)
        {

            s->koef = prvi->koef * drugi->koef;
            s->pot = prvi->pot + drugi->pot;

            zbroj(&P, u, u);
            drugi = drugi->next;
        }
        prvi = prvi->next;
    }

    return 0;
}
