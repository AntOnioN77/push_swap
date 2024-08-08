


#include "circular_array.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <math.h> // BORRAR (crear funcion)

int main(int argc, char **argv) {
    t_ciar *stack_a;
    t_ciar *stack_b;
    int n_elementos = argc - 1;

    // Validar datos de entrada
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <elementos>\n", argv[0]);
        return 1;
    }

    stack_a = init_ciar(argc - 1);
    stack_b = init_ciar(argc - 1);
    fill_stack(stack_a, argc, argv);

    while (n_elementos > 2) {
        pb(stack_a, stack_b);
        n_elementos--;
    }

    t_course best_course;
    init_course(&best_course);

    printf("Elementos en stack_a: %d\n", stack_a->fill);
    printf("Elementos en stack_b: %d\n", stack_b->fill);

    while (stack_b->fill > 0) {
        find_rigth_course(stack_a, stack_b, &best_course);
        printf("Best course: {steps: %d, rr: %d, rrr: %d, ra: %d, rb: %d, rra: %d, rrb: %d, pa: %d}\n",
               best_course.steps, best_course.rr, best_course.rrr, best_course.ra, best_course.rb,
               best_course.rra, best_course.rrb, best_course.pa);
        take_course(&best_course, stack_a, stack_b);
        printf("Elementos en stack_a después de take_course: %d\n", stack_a->fill);
        printf("Elementos en stack_b después de take_course: %d\n", stack_b->fill);
    }

    return 0;
}
