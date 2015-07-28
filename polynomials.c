#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

struct Term {
    int coefficient;
    int x_power;
    int y_power;
    int z_power;
    int next;
};

#define MAX_TERMS 50
struct Polynomial {
    int num_terms;
    int freelist;
    struct Term terms[MAX_TERMS];
};

void
power_print(char var, int power)
{
    if (power > 0) {
        printf("%c", var);
    }
    if (power > 1) {
        printf("^%i", power);
    }
}

void
polynomial_print(struct Polynomial p)
{
    bool first = true;
    for (int i = p.terms[0].next; i != 0; i = p.terms[i].next) {
        struct Term term = p.terms[i];

        bool negative = false;
        
        if (term.coefficient < 0) {
            term.coefficient *= -1;
            negative = true;
        }

        if (!first) {
            if (negative) {
                printf(" %s ", "-");
            } else {
                printf(" %s ", "+");
            }
        } else {
            first = false;
            if (negative) {
                printf("%s", "-");
            }
        }
        
        if (term.coefficient != 1) {
            printf("%i", term.coefficient);
        }
        
        power_print('x', term.x_power);
        power_print('y', term.y_power);
        power_print('z', term.z_power);
    }
    printf("\n");
}

// @TODO: This won't work for powers over 9. Need a better way to do this.
int
term_comparison(struct Term* term)
{
    return (100 * term->x_power +
            10 * term->y_power +
            term->z_power);
}

struct Term*
polynomial_push_term(struct Polynomial* p)
{
    struct Term* new_term;
    if (p->freelist != 0) {
        new_term = &p->terms[p->freelist];
        p->freelist = new_term->next;
                
    } else {
        if (p->num_terms == MAX_TERMS) {
            // Error, too many terms already.
            assert(false);
        }
        new_term = &p->terms[++p->num_terms];
    }

    return new_term;
}

// Add a new term to the polynomial.
void
polynomial_add_term(struct Polynomial* p,
                    int coefficient,
                    int x_power,
                    int y_power,
                    int z_power)
{
    // Can't have a coefficient of 0.
    assert(coefficient != 0);
    
    // push term
    struct Term* new_term = polynomial_push_term(p);
    
    new_term->coefficient = coefficient;
    new_term->x_power = x_power;
    new_term->y_power = y_power;
    new_term->z_power = z_power;
    
    if (p->terms[0].next == 0) {
        p->terms[0].next = p->num_terms;
        new_term->next = 0;
        return;
    }

    int new_term_comparison = term_comparison(new_term);

    int prev = 0;
    int current = p->terms[0].next;
    do {
        struct Term* current_term = &p->terms[current];
        int current_term_comparison = term_comparison(current_term);
        
        if (new_term_comparison > current_term_comparison) {
            p->terms[prev].next = p->num_terms;
            new_term->next = current;
            return;
        }

        prev = current;
        current = current_term->next;
    } while (prev != 0);

    // Error, didn't find a place to insert!
    // @TODO: Return an error or something.
    assert(0);
};

// Adds Q to P, altering P to be the result.
// @TODO: Error out if either of the polynomials aren't sorted correctly.
void
polynomial_add_polynomial(struct Polynomial* p, struct Polynomial* q)
{
    int prev_term = 0;
    int current_term = p->terms[0].next;
    int current_q_term = q->terms[0].next;

    do {
        struct Term* p_term = &p->terms[current_term];
        struct Term* q_term = &q->terms[current_q_term];

        int p_compare = term_comparison(p_term);
        int q_compare = term_comparison(q_term);

        if (q_compare < p_compare) {
            // step p
            prev_term = current_term;
            current_term = p_term->next;
            
        } else if (q_compare == p_compare) {
            // add coefficiants
            p_term->coefficient += q_term->coefficient;

            // if coefficient == 0, remove term.
            if (p_term->coefficient == 0) {

                // push old term to freelist
                p_term->next = p->freelist;
                p->freelist = current_term;

                // remove term from linked list
                p->terms[prev_term].next = p_term->next;
                current_term = p_term->next;
            }
            
            // step q
            current_q_term = q_term->next;
            
        } else {
            // insert node from q here.

            // push new term onto p.
            // try to pop from free list.
            struct Term* new_term = polynomial_push_term(p);

            *new_term = *q_term;
            p->terms[prev_term].next = p->num_terms;
            new_term->next = current_term;
            
            // step q
            current_q_term = q_term->next;
        }
        
    } while (current_q_term != 0);
    
}

int main(int argc, char* argv[])
{
    // x + y + z
    struct Polynomial p = {};
    polynomial_add_term(&p, 1, 1, 0, 0); // 1x
    polynomial_add_term(&p, 1, 0, 1, 0); // 1y
    polynomial_add_term(&p, 1, 0, 0, 1); // 1z

    // x^2 -2y - z
    struct Polynomial q = {};
    polynomial_add_term(&q, 1, 2, 0, 0);  // 1x^2
    polynomial_add_term(&q, -2, 0, 1, 0); // -2y
    polynomial_add_term(&q, -1, 0, 0, 1); // -1z

    polynomial_print(p);
    polynomial_print(q);

    polynomial_add_polynomial(&p, &q);

    polynomial_print(p);
}
