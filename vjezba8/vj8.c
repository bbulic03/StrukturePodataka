#include<stdio.h>
#include<stdlib.h>

struct stablo;
typedef struct stablo* poz;
struct stablo
{
    int el;
    poz l;
    poz d;
};

void ispisOrder(poz current);
void ispisPostorder(poz current);
void ispisPreorder(poz current);
int Height(poz current);
int currentLevel(poz current, int lvl);
poz unos(poz current, int x);
poz trazi(poz current, int x);

int main(void)
{
    poz root = NULL;
    int n = 0, i = 0, x = 0;

    printf("Unesite broj elemenata stabla: ");
    scanf("%d", &n);
    printf("Unesite elemente:\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &x);
        root = unos(root, x);
    }
    printf("\nIspis inorder:\n");
    ispisOrder(root);
    printf("\nIspis postorder:\n");
    ispisPostorder(root);
    printf("\nIspis preorder:\n");
    ispisPreorder(root);

    return 0;
}
void ispisOrder(poz current)
{
    if (current == NULL)
        return;
    ispisOrder(current->l);
    printf("%d ", current->el);
    ispisOrder(current->d);
    return;
}

poz unos(poz current, int x)
{
    poz q = NULL;
    if (current == NULL)
    {
        q = (poz)malloc(sizeof(struct stablo));
        q->el = x;
        q->l = NULL;
        q->d = NULL;
        return q;
    }
    else if (x < current->el)
        current->l = unos(current->l, x);
    else if (x > current->el)
        current->d = unos(current->d, x);
    return current;
}

void ispisPostorder(poz current)
{
    if (current == NULL)
        return;
    ispisPostorder(current->l);
    ispisPostorder(current->d);
    printf("%d ", current->el);
}

void ispisPreorder(poz current)
{
    if (current == NULL)
        return;
    printf("%d ", current->el);
    ispisPreorder(current->l);
    ispisPreorder(current->d);
}

poz trazi(poz current, int x)
{
    if (current == NULL)
        return NULL;
    else if (x < current->el)
        return trazi(current->l, x);
    else if (x > current->el)
        return trazi(current->d, x);
    return current;
}

int Height(poz current) {

    if (current == NULL)
        return 0;
    else {
        int LHeight = Height(current->l);
        int RHeight = Height(current->d);

        if (LHeight > RHeight)
            return (LHeight + 1);
        else
            return (RHeight + 1);
    }
}

int currentLevel(poz current, int lvl) {

    if (current == NULL)
        return 0;

    if (lvl == 1) {
        printf(" %d ", current->el);
    }
    else if (lvl > 1) {
        currentLevel(current->l, lvl - 1);
        currentLevel(current->d, lvl - 1);
    }

    return 1;
}