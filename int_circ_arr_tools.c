/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_circ_arr_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antofern <antofern@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:54:36 by antofern          #+#    #+#             */
/*   Updated: 2024/07/21 22:45:42 by antofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "circularArray.h"

//según está solo vale para iniciar la pila a desde 0
static void	addinit(t_ciar *arr, int elem)
{
	arr->buff[arr->fill] = elem;
	arr->fill++;
}

t_ciar	*ciar_int_init(int items)
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
	ciar->top = 0;
	ciar->back = items - 1;
	ciar->fill = 0;
	ciar->slots = items + 1;
	return (ciar);
}

void	ciar_free(t_ciar *arr)
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
    return (index - 1 + slots) % slots;
}

int	pop(t_ciar *arr)
{
	if (arr->fill > 0)
	{
		arr->top = next_index(arr->top, arr->slots);
		arr->fill--;
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
	if (arr->fill <= 0)
		return (EMPTY_STACK);
	arr->back = next_index(arr->back, arr->slots);
	arr->buff[arr->back] = arr->buff[arr->top];
	arr->top = next_index(arr->top, arr->slots);
	return (OK);
}

int	reverse_rotate(t_ciar *arr)
{
	if (arr->fill <= 0)
		return (EMPTY_STACK);
	arr->buff[prev_index(arr->top, arr->slots)] = arr->buff[arr->back];
	arr->top = prev_index(arr->top, arr->slots);
	arr->back = prev_index(arr->back, arr->slots);
	return (OK);
}


//int get_top()
//int get_back()
//int swap(t_ciarr *arr)// requiere % arr->slots en algún punto
//int push(t_ciarr from, t_ciar to)// utiliza add() y pop()

//	