#include "circularArray.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define MAX_OPERATIONS 8000
#define OK 0
#define ERROR 1
#define EMPTY_STACK -1

typedef enum {
    SA, SB, SS, PA, PB, RA, RB, RR, RRA, RRB, RRR
} Operation;

typedef struct {
    Operation ops[MAX_OPERATIONS];
    int count;
} Solution;

// Declaraciones de funciones
int next_index(int index, int slots);
int prev_index(int index, int slots);
int get_top(t_ciar *stack);
int get_back(t_ciar *stack);
int pop(t_ciar *arr);
int add(t_ciar *arr, int elem);
int rotate(t_ciar *arr);
int reverse_rotate(t_ciar *arr);
void swap(t_ciar *arr);
void push(t_ciar *from, t_ciar *to);
void sa(t_ciar *a);
void sb(t_ciar *b);
void ss(t_ciar *a, t_ciar *b);
void pa(t_ciar *b, t_ciar *a);
void pb(t_ciar *a, t_ciar *b);
void ra(t_ciar *a);
void rb(t_ciar *b);
void rr(t_ciar *a, t_ciar *b);
void rra(t_ciar *a);
void rrb(t_ciar *b);
void rrr(t_ciar *a, t_ciar *b);
int fill_stack(t_ciar *arr, int argc, char **argv);
int *ordenar_indices_por_contenido(t_ciar *arr);
void apply_operation(t_ciar *a, t_ciar *b, Operation op);
void undo_operation(t_ciar *a, t_ciar *b, Operation op);
int is_sorted(t_ciar *a);
void copy_solution(Solution *dest, Solution *src);
int backtrack(t_ciar *a, t_ciar *b, Solution *current, Solution *best, int depth);
Solution find_shortest_solution(t_ciar *a);
const char* operation_to_string(Operation op);
void print_solution(Solution *solution);

// Implementaciones de funciones

t_ciar *init_ciar(int items)
{
    t_ciar *ciar = (t_ciar *)malloc(sizeof(t_ciar));
    if (ciar == NULL)
        return NULL;
    ciar->buff = (int *)malloc(sizeof(int) * (items + 1));
    if (ciar->buff == NULL)
    {
        free(ciar);
        return NULL;
    }
    ciar->top = items / 2 + 1;
    ciar->back = items / 2;
    ciar->fill = 0;
    ciar->slots = items + 1;
    return ciar;
}

void free_ciar(t_ciar *arr)
{
    free(arr->buff);
    free(arr);
}

int next_index(int index, int slots)
{
    return (index + 1) % slots;
}

int prev_index(int index, int slots)
{
    return (index - 1 + slots) % slots;
}

int get_top(t_ciar *stack)
{
    return stack->buff[stack->top];
}

int get_back(t_ciar *stack)
{
    return stack->buff[stack->back];
}

int pop(t_ciar *arr)
{
    if (arr->fill > 0)
    {
        arr->top = next_index(arr->top, arr->slots);
        arr->fill--;
        if (arr->fill == 0)
            arr->top = next_index(arr->top, arr->slots);
        return OK;
    }
    else
        return EMPTY_STACK;
}

int add(t_ciar *arr, int elem)
{
    arr->top = prev_index(arr->top, arr->slots);
    arr->buff[arr->top] = elem;  // Añadido: asignar el elemento
    arr->fill++;
    return OK;
}

// ... (resto de las implementaciones de funciones)

int fill_stack(t_ciar *arr, int argc, char **argv)
{
    int i;
    int num;
    
    i = argc - 1;
    while (i > 0)
    {
        num = atoi(argv[i]);
        add(arr, num);
        i--;
    }
    return OK;
}

Solution find_shortest_solution(t_ciar *a)
{
    t_ciar *b = init_ciar(a->slots - 1);
    Solution current = {0}, best = {0};
    best.count = INT_MAX;

    backtrack(a, b, &current, &best, 0);

    free_ciar(b);
    return best;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Uso: %s <lista de números>\n", argv[0]);
        return 1;
    }

    t_ciar *stack_a = init_ciar(argc - 1);
    if (stack_a == NULL)
    {
        printf("Error: No se pudo inicializar stack_a\n");
        return 1;
    }

    fill_stack(stack_a, argc, argv);

    Solution best_solution = find_shortest_solution(stack_a);

    print_solution(&best_solution);

    free_ciar(stack_a);
    
    return 0;
}