#include <stdlib.h>
#include <stdio.h>

struct foo {
    int field;
};
struct foo foo[5];

int main(void)
{
    for (int i=0; i<5; i++) {
        foo[i].field = i;
    }

    struct foo bar = foo[2];
    bar.field = 999;
    printf("bar: %i, foo[2]: %i\n", bar.field, foo[2].field);

    struct foo* baz = &foo[2];
    baz->field = 999;
    printf("baz: %i, foo[2]: %i", baz->field, foo[2].field);

    struct foo* wat = malloc(sizeof(struct foo));
    *wat = foo[2];
    printf("baz: %i, foo[2]: %i", baz->field, foo[2].field);
}
