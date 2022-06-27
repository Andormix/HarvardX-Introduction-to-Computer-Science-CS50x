#include <stdio.h>
#include <stdlib.h>

// In c++ I think we don't need typedef
typedef struct node
{
    int number;
    struct node* next;  // We could do a linked list with pointers
}
node;

int main(void)
{
    // init node
    node n;
    n.number = 5;
    n.next = NULL;
    printf("Node created as variable (n) num: %i\n", n.number);

    node *p = malloc(sizeof(node));
    if (p != NULL)
    {
        //(*p).number = 0;
        p->number = 0;
    }
    printf("Node created as ptr (p) %i\n", p->number);
}


/* In python we can use an ordered linked list with arrays to try emulate pointers. 2 implementations:
 * 1) Node has a number (index in the array) of where is located next node
 * 2) ADT List have 2 arrays one with the info (nodes) and the other with the index of the following node
 *
 *    MEMO   0 1 2 3 4 5    6 7 8
 *           A B C D E F    - - -
 *    INDEX  3 4 1 2 5 -1   7 8 -1
 *
 *    Start = 0;  (A D C B E F)
 *    Empty nodes = 6   (6 7 8)
*/