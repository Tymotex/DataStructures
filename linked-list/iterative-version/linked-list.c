#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <limits.h>
#include "linked-list.h"

struct node {
    int val;
    struct node *next;
};

// ===== Inserting Nodes =====
// Iteratively insert a node into a linked list
Node *insert(Node *head, int value, int insertionIndex) {
    // Separately dealing with the case where we want to insert at the very front of the list:
    if (insertionIndex == 0) {
        Node *newHead = malloc(sizeof(struct node));
        newHead -> val = value;
        newHead -> next = head;
        return newHead;
    } else {
        Node *curr = head;
        for (int i = 1; curr != NULL; i++) {
            if (i == insertionIndex) {
                Node *nextNode = curr -> next;
                curr -> next = malloc(sizeof(struct node));
                curr -> next -> val = value;
                curr -> next -> next = nextNode;
                break;
            }
            curr = curr -> next;
        }
        return head;
    }
}

// ===== Deleting Nodes =====
// Iteratively delete a node with the given target value from the list
Node *delete(Node *head, int targetValue) {
    Node *curr = head;
    Node *prev = NULL;
    while (curr != NULL) {
        if (curr -> val == targetValue) {
            Node *nextNode = curr -> next;
            free(curr);
            if (prev == NULL) {
                return nextNode;
            } else {
                prev -> next = nextNode;
                return head;
            }
        }
        prev = curr;
        curr = curr -> next;
    }
}

// ===== Determine Length =====
// Iteratively count the nodes in a linked list
int getLength(Node *head) {
    int count = 0;
    Node *curr = head;
    while (curr != NULL) { 
        count++;
        curr = curr -> next;
    }
    return count;
}

// ===== Search List =====
// Iteratively search for a value in the list. Returns true if the value exists,
// false otherwise
bool search(Node *head, int targetValue) {
    Node *curr = head;
    while (curr != NULL) {
        if (curr -> val == targetValue) return true;
        curr = curr -> next;
    }
    return false;
}

// ===== Reverse List =====
// Iteratively reverse the list
Node *reverse(Node *head) {
    Node *curr = head;
    Node *prevNode = NULL;
    while (curr != NULL) {
        Node *nextNode = curr -> next;
        curr -> next = prevNode;
        prevNode = curr;
        curr = nextNode;
    }
    return prevNode;
}

// ===== Sorting List =====
// Iteratively sort the list
Node *sortList(Node *head) {
    Node *newHead = NULL;
    int size = getLength(head);
    for (int i = 0; i < size; i++) {
        int min = INT_MAX;
        Node *curr = head;
        while (curr != NULL) {
            if (curr -> val < min) {
                min = curr -> val;
            }
            curr = curr -> next;
        }
        head = delete(head, min);
        newHead = append(newHead, min);
    }
    return newHead;
}

// ===== Free List =====
// Iteratively free the nodes of the list
void freeList(Node *head) {
    Node *curr = head;
    while (curr != NULL) {
        Node *nextNode = curr -> next;
        free(curr);
        curr = nextNode;
    }
}

// ===== Traverse List =====
// Iteratively traverse and print the list
void traverseAndPrint(Node *head) {
    setlocale(LC_CTYPE, "");
    while (head != NULL) {
        // Prints the → unicode character
        printf("%d %lc ", head -> val, (wint_t)0x2192);
        head = head -> next;
    }
    // Prints the ╳ unicode character
    printf("%lc\n", (wint_t)0x2573);
}

// ===== Others Functions =====

Node *append(Node *head, int newValue) {
    int size = getLength(head);
    if (head == NULL) {
        head = insert(head, newValue, 0);
    } else {
        head = insert(head, newValue, size);
    }
    return head;
}
