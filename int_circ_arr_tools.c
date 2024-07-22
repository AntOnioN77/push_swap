/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_circ_arr_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antofern <antofern@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:54:36 by antofern          #+#    #+#             */
/*   Updated: 2024/07/22 13:25:03 by antofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "circularArray.h"
#include <stddef.h>

//según está solo vale para iniciar la pila a desde 0
/*static void	addinit(t_ciar *arr, int elem)
{
	arr->buff[arr->fill] = elem;
	arr->fill++;
}
*/
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
	arr->buff[prev_index(arr->top, arr->slots)] = get_back(arr);//arr->buff[arr->back];
	arr->top = prev_index(arr->top, arr->slots);
	arr->back = prev_index(arr->back, arr->slots);
	return (OK);
}

void swap(t_ciar *arr)// requiere % arr->slots en algún punto
{
	int	tmp;

	if (arr->fill < 2)
		return ;
	tmp = get_top(arr);
	arr->buff[arr->top] = arr->buff[arr->top + 1];
	arr->buff[arr->top + 1] = tmp;
}

void push(t_ciar *from, t_ciar *to)
{
	if (from < 1)
		return ;
	add(to, get_top(from));
	pop(from);
}

int	fill_stack(t_ciar *arr, int argc, char **argv)
{
	//
}

int	main(int argc, char **argv)
{
	t_ciar *stack_a;
	t_ciar *stack_b;

	//validar datos de entrada

	stack_a = init_ciar(argc - 1);
	stack_b = init_ciar(argc - 1);
	fill_stack(stack_a, argc, argv);
	short_stack(stack_a, stack_b);
}