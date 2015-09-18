/*
Topological sort (Algorithm T) in c. (2.2.3)
Just sorts a set of edges between numbers from 1-9
*/

#include <stdio.h>

// First, a straitforward translation of knuth's algorithm.
// Afterwards I might try to write it in more of a c style.

// uses char because we only care about numbers 1-9
struct link {
    int successor;
    struct link* next;
};

struct node {
    int count;
    struct link* top;
};

void top_sort(int* edges, int *result)
{
    // in knuth he reuses the count for the queue but I'm just going to
    // have another array because it's simpler.
    int queue[10] = {};
    struct node nodes[10] = {};

    int link_count = 0;
    struct link links[100] = {};

    // Read input
    int i = 0;
    int from, to;
    while ((from = edges[i]) != 0) {
        to = edges[i+1];

        // update count
        nodes[to].count++;

        // push link
        struct link* l = &links[link_count++];
        l->successor = to;
        l->next = nodes[from].top;
        nodes[from].top = l;

        i += 2;
    }

    //
    int r = 0;
    for (int k = 1; k < 10; k++) {
        if (nodes[k].count == 0) {
            queue[r] = k;
            r = k;
        }
    }

    int output = 0;
    int f = queue[0];
    while (f != 0) {
        // output f
        result[output++] = f;
        struct link* p = nodes[f].top;
        
        if (p == NULL) {
            f = queue[f];
        } else {
            if (--nodes[p->successor].count == 0) {
                queue[r] = 
            }
            
            
            nodes[nodes[f].top+1].count--;
        }
        
    }

    
    
}

int main(void) {

    int input[] = {9, 2,
                   3, 7,
                   7, 5,
                   5, 8,
                   8, 6,
                   4, 6,
                   1, 3,
                   7, 4,
                   9, 5,
                   2, 8,
                   0};

    int sorted[10];
    top_sort(input, sorted);

    printf("Sorted Order: ");
    for (int i = 0; i < 10; i++) {
        printf("%u ", sorted[i]);
    }
    
    printf("\n");
}
