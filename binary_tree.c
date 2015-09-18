#include <stdio.h>

typedef struct tree {
    int val;
    struct tree* lhs;
    struct tree* rhs;
} Tree;

// Recursive version.
void
tree_print(Tree* tree)
{
    tree_print(tree->lhs);
    printf("%i", tree->val);
    tree_print(tree->rhs);
}

int main(int argn, char* argv[]) {
    leaf1 = {.val = 1, }
    
    printf("Hello World\n");
}
