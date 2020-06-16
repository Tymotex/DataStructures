#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>

void printColoured(char *text) {
    printf("\033[01;33m");
    printf("%s", text);
    printf("\033[0m");
}

// Node definition:
struct node {
    int val;
    struct node *next;
};
typedef struct node Node;

Node *buildList(int *values, int size) {
    if (size == 0) {
        return NULL;
    }
    Node *curr = malloc(sizeof(struct node));
    curr -> val = values[0];
    curr -> next = buildList(values + 1, size - 1);
    return curr;
}

void traverseAndPrint(Node *head) {
    setlocale(LC_CTYPE, "");
    if (head == NULL) {
        printf("%lc\n", (wint_t)0x2573);
        return;
    }
    printf("%d %lc ", head -> val, (wint_t)0x2192);
    traverseAndPrint(head -> next);
}
// Ignore everything above here.
// ===========================================
//      Determining length of the list 
// ===========================================
/*

    struct node {
        int val;
        struct node *next;
    };
    typedef struct node Node;

*/

int lengthIterative(Node *head) {
    Node *curr = head;
    int count = 0;
    while (curr != NULL) {
        count++;
        curr = curr -> next;
    }
    return count;
}

// Recursive version
int length(Node *head) {
    return (head == NULL) ? (0) : (1 + length(head -> next));
}

// ===========================================
//             Freeing the list 
// ===========================================
/*

    struct node {
        int val;
        struct node *next;
    };
    typedef struct node Node;
    
*/

/*
 * Problem: given the head of a linked list, free all the nodes in that list
 */
void freeListIterative(Node *head) {
    Node *curr = head;
    while (curr != NULL) {
        Node *nextNode = curr -> next;
        free(curr);
        curr = nextNode;
    }
}

void freeListRecursive(Node *head) {
    if (head == NULL) {
        return;
    } else {
        Node *nextNode = head -> next;
        free(head);
        freeListRecursive(nextNode);
    }
}

// ===========================================

int main() {
    printColoured("|===== List 1 =====|\n");

    // Building a linked list with 4 nodes:
    // 2 -> 4 -> 6 -> 8
    int values[4] = {2, 4, 6, 8};
    Node *head = buildList(values, 4);
    traverseAndPrint(head);

    // printColoured("|===== Freeing List 1 =====|\n");
    // // freeListIterative(head);
    // freeListRecursive(head);

    printColoured("|===== Length of List 1 =====|\n");
    printf("Length: %d\n", length(head));

    return 0;
}










// Verify there are no leaks with:
// valgrind --leak-check=full --tool=memcheck ./testLinkedList