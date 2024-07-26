/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_circ_arr_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antofern <antofern@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:54:36 by antofern          #+#    #+#             */
/*   Updated: 2024/07/24 17:44:34 by antofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "circularArray.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>


t_ciar	*init_ciar(int items)
{
	t_ciar	*ciar;

	ciar = (t_ciar *)malloc(sizeof(t_ciar));
	if (ciar == NULL)
		return (NULL);
	ciar->buff = (int *)malloc(sizeof(int) * (items + 1)); //esto evita tener que comprobar si la lista esta llena y tener que cambiar la logica de rotate() en ese caso
	if (ciar->buff == NULL)
	{
		free(ciar);
		return (NULL);
	}
	ciar->top = items / 2 + 1;// con (items / 2) buscamos alejar top y back de el final del array, copiar arr[0] en arr[50] es la operacion más costosa posible.
	// con + 1, al hacer add() colocamos un elemento en top -1, por tanto en el primer add() top y back seran el mismo.
	ciar->back = items / 2;
	ciar->fill = 0;
	ciar->slots = items + 1;
	return (ciar);
}

void	free_ciar(t_ciar *arr)
{
	free(arr->buff);
	free(arr);
}

inline int next_index(int index, int slots)
{
    return (index + 1) % slots;
}

inline int prev_index(int index, int slots)
{
	return ((index - 1 + slots) % slots);
}

inline int get_top(t_ciar *stack)
{
	return (stack->buff[stack->top]);
}

inline int get_back(t_ciar *stack)
{
	return (stack->buff[stack->back]);
}


/*Con `if (arr->fill == 0)` compensamos que add() añade en top -1, y para una pila vacia en la que top == back, back señalaría a*/
int	pop(t_ciar *arr)
{
	if (arr->fill > 0)
	{
		arr->top = next_index(arr->top, arr->slots);
		arr->fill--;
		if (arr->fill == 0)
			arr->top = next_index(arr->top, arr->slots);
		return (OK);
	}
	else
		return (EMPTY_STACK);
}

int add(t_ciar *arr, int elem)
{
	arr->top = prev_index(arr->top, arr->slots);
	arr->fill++;
	arr->buff[arr->top] = elem; 
	return (OK);
}

int	rotate(t_ciar *arr)
{
	if (arr->fill < 2)
		return (ERROR);
	arr->back = next_index(arr->back, arr->slots);
	arr->buff[arr->back] = get_top(arr);//arr->buff[arr->top];
	arr->top = next_index(arr->top, arr->slots);
	return (OK);
}

int	reverse_rotate(t_ciar *arr)
{
	if (arr->fill < 2)
		return (ERROR);
	arr->top = prev_index(arr->top, arr->slots);
	arr->buff[arr->top] = get_back(arr);//arr->buff[arr->back];
	
	arr->back = prev_index(arr->back, arr->slots);
	return (OK);
}

void swap(t_ciar *arr)// requiere % arr->slots en algún punto
{
	int	tmp;

	if (arr->fill < 2)
		return ;
	tmp = get_top(arr);
	arr->buff[arr->top] = arr->buff[next_index(arr->top, arr->slots)];
	arr->buff[next_index(arr->top, arr->slots)] = tmp;
}
/*
void swap(t_ciar *arr)
{
    int tmp;
    int next_index;

    if (arr->fill < 2)
        return;
    tmp = get_top(arr);
    next_index = (arr->top + 1) % arr->slots;
    arr->buff[arr->top] = arr->buff[next_index];
    arr->buff[next_index] = tmp;
}
*/
void push(t_ciar *from, t_ciar *to)
{
	if (from->fill < 1)
		return ;
	add(to, get_top(from));
	pop(from);
}

// -------ORDENES PARA LA ORDENACION-------

void sa(t_ciar *a)
{
	if (a == NULL)
		return;
	swap(a);
	//ft_printf(sa);
}

void sb(t_ciar *b)
{
	swap(b);
	//ft_printf(sb);
}

void	ss(t_ciar *a, t_ciar *b)
{
	swap(a);
	swap(b);
	//ft_printf(ss);
}

void	pa(t_ciar *b, t_ciar *a)
{
	push(b, a);
	//ft_printf(pa);
}

void	pb(t_ciar *a, t_ciar *b)
{
	push(a, b);
	//ft_printf(pb);
}

void	ra(t_ciar *a)
{
	rotate(a);
	//ft_printf(ra);
}

void	rb(t_ciar *b)
{
	rotate(b);
	//ft_printf(rb);
}

void	rr(t_ciar *a, t_ciar *b)
{
	rotate(a);
	rotate(b);
	//ft_printf(rr);
}

void	rra(t_ciar *a)
{
	reverse_rotate(a);
	//ft_printf(rra);
}

void	rrb(t_ciar *b)
{
	reverse_rotate(b);
	//ft_printf(rrb);
}


void	rrr(t_ciar *a, t_ciar *b)
{
	reverse_rotate(a);
	reverse_rotate(b);
	//ft_printf(rrr);
}

// -------------------PUSH_SWAP---------------------

int fill_stack(t_ciar *arr, int argc, char **argv)
{
	int i;
	int num;
	
	//temporal
	i = 0;
	while(i < argc -1)
	{
		arr->buff[i] = 0;;
		i++;
	}
	//
	i = argc - 1;
	while (i > 0)
	{
		num = atoi(argv[i]); // CIDADO!! NO FT_-------------------------------------------------------
		add(arr, num);
		i--;
	}
	return OK;
}

/*short_stack(t_ciar *a, t_ciar *b)
{
	// elegir un algoritmo u otro para segun que cantidad de elementos

}*/

int *ordenar_indices_por_contenido(t_ciar *arr)
{
    int *indices;
    int i, j, temp;
    
    // Asignar memoria para el array de índices
    indices = (int *)malloc(sizeof(int) * arr->fill);
    if (!indices)
        return NULL;
    
    // Inicializar el array de índices
    for (i = 0; i < arr->fill; i++)
        indices[i] = i;
    
    // Ordenar los índices usando el algoritmo de burbuja
    for (i = 0; i < arr->fill - 1; i++)
    {
        for (j = 0; j < arr->fill - i - 1; j++)
        {
            if (arr->buff[(arr->top + indices[j]) % arr->slots] > 
                arr->buff[(arr->top + indices[j + 1]) % arr->slots])
            {
                // Intercambiar índices
                temp = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1] = temp;
            }
        }
    }
    
    return indices;
}



void apply_operation(t_ciar *a, t_ciar *b, Operation op) {
    switch(op) {
        case SA: sa(a); break;
        case SB: sb(b); break;
        case SS: ss(a, b); break;
        case PA: pa(b, a); break;
        case PB: pb(a, b); break;
        case RA: ra(a); break;
        case RB: rb(b); break;
        case RR: rr(a, b); break;
        case RRA: rra(a); break;
        case RRB: rrb(b); break;
        case RRR: rrr(a, b); break;
    }
}

void undo_operation(t_ciar *a, t_ciar *b, Operation op) {
    switch(op) {
        case SA: sa(a); break;
        case SB: sb(b); break;
        case SS: ss(a, b); break;
        case PA: pb(a, b); break;
        case PB: pa(b, a); break;
        case RA: rra(a); break;
        case RB: rrb(b); break;
        case RR: rrr(a, b); break;
        case RRA: ra(a); break;
        case RRB: rb(b); break;
        case RRR: rr(a, b); break;
    }
}

int is_sorted(t_ciar *a) {
    int i, prev, curr;
    for (i = 0; i < a->fill - 1; i++) {
        prev = a->buff[(a->top + i) % a->slots];
        curr = a->buff[(a->top + i + 1) % a->slots];
        if (prev > curr) return 0;
    }
    return 1;
}

void copy_solution(Solution *dest, Solution *src) {
    dest->count = src->count;
    for (int i = 0; i < src->count; i++) {
        dest->ops[i] = src->ops[i];
    }
}

int backtrack(t_ciar *a, t_ciar *b, Solution *current, Solution *best, int depth) {
    if (depth >= best->count) return 0; // Poda: si ya hemos superado la mejor solución, no seguimos

    if (is_sorted(a) && b->fill == 0) {
        if (current->count < best->count) {
            copy_solution(best, current);
        }
        return 1;
    }

    Operation ops[] = {SA, SB, SS, PA, PB, RA, RB, RR, RRA, RRB, RRR};
    int num_ops = sizeof(ops) / sizeof(ops[0]);

    for (int i = 0; i < num_ops; i++) {
        apply_operation(a, b, ops[i]);
        current->ops[current->count++] = ops[i];

        if (backtrack(a, b, current, best, depth + 1))
		{
            undo_operation(a, b, ops[i]);
            current->count--;
            return 1;
        }

        undo_operation(a, b, ops[i]);
        current->count--;
    }

    return 0;
}

Solution find_shortest_solution(t_ciar *a) {
    t_ciar *b = init_ciar(a->slots);
    Solution current = {0}, best = {0};
    best.count = INT_MAX;

    backtrack(a, b, &current, &best, 0);

    free_ciar(b);
    return best;
}

const char* operation_to_string(Operation op) {
    switch(op) {
        case SA: return "sa";
        case SB: return "sb";
        case SS: return "ss";
        case PA: return "pa";
        case PB: return "pb";
        case RA: return "ra";
        case RB: return "rb";
        case RR: return "rr";
        case RRA: return "rra";
        case RRB: return "rrb";
        case RRR: return "rrr";
        default: return "unknown";
    }
}



void print_solution(Solution *solution) {
    for (int i = 0; i < solution->count; i++) {
        printf("%s\n", operation_to_string(solution->ops[i]));
    }
}


int	main(int argc, char **argv)
{
	t_ciar *stack_a;
	//t_ciar *stack_b;
	//int *indices_ordenados;

	//validar datos de entrada

	stack_a = init_ciar(argc - 1);
	//stack_b = init_ciar(argc - 1);
	fill_stack(stack_a, argc, argv);

printf("%d\n", get_top(stack_a)); //prueba
	Solution best_solution = find_shortest_solution(stack_a);

	print_solution(&best_solution);
	//short_stack(stack_a, stack_b);
	
}