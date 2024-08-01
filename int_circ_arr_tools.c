/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_circ_arr_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antofern <antofern@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:54:36 by antofern          #+#    #+#             */
/*   Updated: 2024/08/01 17:36:06 by antofern         ###   ########.fr       */
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
	ciar->max_fill = items;
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
	if (stack->fill == 0)
			return (0);
	return (stack->buff[stack->top]);
}

inline int get_back(t_ciar *stack)
{
	if (stack->fill == 0)
			return (0);
	return (stack->buff[stack->back]);
}

/* NO TESTEADA El nivel inicial es 0. Un nivel de -1  indica que la pila no contiene ningun elemento en esa posicion.*/
int get_level(t_ciar *arr, int index)
{
	int result;

	result = (index - arr->top + arr->slots) % arr->slots;
	if ((result +1) > arr->fill)
		return (-1);
	return (result);
}

/*Con `if (arr->fill == 0)` compensamos que add() añade en top -1, y para una pila vacia en la que top == back, back señalaría a*/
int	pop(t_ciar *arr)
{
	if (arr->fill > 0)
	{
		arr->buff[arr->top] = 0; // SOLO PARA PRUEBA
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
	if (arr->fill >= arr->max_fill)
		return (FULL_STACK);
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
	printf("sa");
}

void sb(t_ciar *b)
{
	swap(b);
	printf("sb");
}

void	ss(t_ciar *a, t_ciar *b)
{
	swap(a);
	swap(b);
	printf("ss");
}

void	pa(t_ciar *b, t_ciar *a)
{
	push(b, a);
	printf("pa\n");
}

void	pb(t_ciar *a, t_ciar *b)
{
	push(a, b);
	printf("pb\n");/////////prueba
}

void	ra(t_ciar *a)
{
	rotate(a);
	printf("ra\n");
}

void	rb(t_ciar *b)
{
	rotate(b);
	printf("rb\n");
}

void	rr(t_ciar *a, t_ciar *b)
{
	rotate(a);
	rotate(b);
	printf("rr\n");
}

void	rra(t_ciar *a)
{
	reverse_rotate(a);
	printf("rra\n");
}

void	rrb(t_ciar *b)
{
	reverse_rotate(b);
	printf("rrb\n");
}


void	rrr(t_ciar *a, t_ciar *b)
{
	reverse_rotate(a);
	reverse_rotate(b);
	printf("rrr\n");
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
void print_status(t_ciar *stack_a, t_ciar *stack_b)
{
	printf("PILA_A back:%d, top:%d\n", stack_a->back, stack_a->top );
	printf("%d", stack_a->buff[0]);
	printf("%d", stack_a->buff[1]);
	printf("%d", stack_a->buff[2]);
	printf("%d", stack_a->buff[3]);
	printf("%d\n", stack_a->buff[4]);

	printf("PILA_B back:%d, top:%d\n", stack_a->back, stack_a->top );
	printf("%d", stack_b->buff[0]);
	printf("%d", stack_b->buff[1]);
	printf("%d", stack_b->buff[2]);
	printf("%d", stack_b->buff[3]);
	printf("%d\n", stack_b->buff[4]);
}

int	main(int argc, char **argv)
{
	t_ciar *stack_a;
	t_ciar *stack_b;
	//int *indices_ordenados;

	//validar datos de entrada

	stack_a = init_ciar(argc - 1);
	stack_b = init_ciar(argc - 1);
	fill_stack(stack_a, argc, argv);
printf ("inicio");
	print_status(stack_a, stack_b);
	ra(stack_a);
	ra(stack_a);
	pb(stack_a, stack_b);
	ra(stack_a);
	pa(stack_b, stack_a);
	ra(stack_a);
printf ("fin");
	print_status(stack_a, stack_b);
	//short_stack(stack_a, stack_b);
	return (0);
}
