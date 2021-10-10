#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int value;
    struct node* next;
} Node;

Node* newNode(int val)
{
    Node* n = (Node*) malloc(sizeof(Node));
    n->value = val;
    n->next = NULL;
    return n;
}

int main()
{
    Node* n = newNode(5);
    printf("%d\n", n->value);

    return 0;
}
