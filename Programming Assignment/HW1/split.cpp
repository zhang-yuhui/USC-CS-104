/*
CSCI 104: Homework 1 Problem 1

Write a recursive function to split a sorted singly-linked
list into two sorted linked lists, where one has the even 
numbers and the other contains the odd numbers. Students 
will receive no credit for non-recursive solutions. 
To test your program write a separate .cpp file and #include
split.h.  **Do NOT add main() to this file**. When you submit
the function below should be the only one in this file.
*/

#include "split.h"

/* Add a prototype for a helper function here if you need */
void reverse(Node*& node);

void split(Node*& in, Node*& odds, Node*& evens)
{
    /* Add code here */
    if (in == nullptr)
        return;

    int value = in->value;
    Node* next = in->next;

    if (value % 2 == 0) {
        in->next = evens;
        evens = in;
        split(next, odds, evens);
    } else {
        in->next = odds;
        odds = in;
        split(next, odds, evens);
    }

    reverse(odds);
    reverse(evens);
}

/* If you needed a helper function, write it here */

void reverse(Node*& node) {
    if (node == nullptr || node->next == nullptr)
        return;

    Node* rest = node->next;
    reverse(rest);

    node->next->next = node;
    node->next = nullptr;
    node = rest;
}