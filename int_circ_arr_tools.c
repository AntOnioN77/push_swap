/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_circ_arr_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antofern <antofern@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:54:36 by antofern          #+#    #+#             */
/*   Updated: 2024/08/08 16:59:48 by antofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "circular_array.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <math.h> // BORRAR (crear funcion)



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

int get_top(t_ciar *stack)
{
	if (stack->fill == 0)
			return (0);
	return (stack->buff[stack->top]);
}

int get_back(t_ciar *stack)
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

int swap(t_ciar *arr)// requiere % arr->slots en algún punto
{
	int	tmp;

	if (arr->fill < 2)
		return (ERROR);
	tmp = get_top(arr);
	arr->buff[arr->top] = arr->buff[next_index(arr->top, arr->slots)];
	arr->buff[next_index(arr->top, arr->slots)] = tmp;
	return (0);
}

int push(t_ciar *from, t_ciar *to)
{
	if (from->fill < 1)
		return (ERROR);
	if (to->max_fill == to->fill)
		return (ERROR);
	add(to, get_top(from));
	pop(from);
	return (0);
}


// -------ORDENES PARA LA ORDENACION-------


// !!!!!!!!!! CARGARSE printf, poner FT_printf

void sa(t_ciar *a)
{
	if (a == NULL)
		return;
	if (swap(a) == ERROR)
		return;
	printf("sa\n");
}

void sb(t_ciar *b)
{
	if (b == NULL)
		return;
	if (swap(b) == ERROR)
		return;
	printf("sb\n");
}

void	ss(t_ciar *a, t_ciar *b)
{
	if (a == NULL)
		return;
	if (b == NULL)
		return;
	if (swap(a) == ERROR)
		return;
	if (swap(b) == ERROR)
	{
	swap(a);
	return ;
	}
	printf("ss\n");
}

void	pa(t_ciar *b, t_ciar *a)
{

	if (push(b, a) == ERROR)
		return ;
	printf("pa\n");
}

void	pb(t_ciar *a, t_ciar *b)
{
	if (push(a, b) == ERROR)
		return ;
	printf("pb\n");/////////prueba
}

void	ra(t_ciar *a)
{
	if (a == NULL)
		return ;
	if (rotate(a) == ERROR)
		return;
	printf("ra\n");
}

void	rb(t_ciar *b)
{
	if (b == NULL)
		return;
	if (rotate(b) == ERROR)
		return;
	printf("rb\n");
}

void	rr(t_ciar *a, t_ciar *b)
{
	if (a == NULL)
		return;
	if (b == NULL)
		return;
	if (rotate(a) == ERROR)
		return;
	if (rotate(b) == ERROR)
	{
	reverse_rotate(a);
	return ;
	}
	printf("rr\n");
}

void	rra(t_ciar *a)
{
	if (a == NULL)
		return ;
	if (reverse_rotate(a) == ERROR)
		return ;
	printf("rra\n");
}

void	rrb(t_ciar *b)
{
	if (b == NULL)
		return ;
	if (reverse_rotate(b) == ERROR)
		return ;
	printf("rrb\n");
}


void	rrr(t_ciar *a, t_ciar *b)
{
	if (a == NULL)
		return ;
	if (b == NULL)
		return ;
	if (reverse_rotate(a) == ERROR)
		return ;
	if (reverse_rotate(b) == ERROR)
	{
	rotate(a);
	return ;
	}
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
//________________________ consulta de posiciones____________________
int get_n_element(const t_ciar *arr, t_level level) // retorna el valor contenido en el nºesimo elemento de la lista, considerando que el nº0 es arr->buff[arr->top]
{
	int indice;

	if (level >= arr->fill || level <= -(arr->fill))
		return (0);
	if (level < 0) {
        level = arr->fill + level;
    }
	
	indice = (level + arr->top) % arr->slots ;

	return (arr->buff[indice]);
}

// _______________________ Metodos de ordenación____________________


/*
int shorter_d(t_ciar *a, t_ciar *b)
{
	int chunk_size;
	int i;

	chunk_size = sqrt(a->fill);

	i = 0;
	while (++i < chunk_size)
		pyramid_step(a, b);
//	while (a->fill > 0)
//		doblebuble_step(a,b);
	
	return (0);
}
*/
//GENERADO PARA PRUEBAS BORRAR
void take_course(t_course *course, t_ciar *a, t_ciar *b)
{
	printf("entra en take_course\n");
    if (course == NULL)
    {
        printf("Course is NULL\n");
        return;
    }

    for (int i = 0; i < course->rr; i++)
    {
        rr(a,b);
    }
    for (int i = 0; i < course->rrr; i++)
    {
        rrr(a,b);
    }
    for (int i = 0; i < course->ra; i++)
    {
        ra(a);
    }
    for (int i = 0; i < course->rb; i++)
    {
        rb(b);
    }
    for (int i = 0; i < course->rra; i++)
    {
        rra(a);
    }
    for (int i = 0; i < course->rrb; i++)
    {
        rrb(b);
    }
	printf("ANTES DEL PUSH\npila_a->fill== %d pila_b.>fill==%d\n", a->fill, b->fill);

    for (int i = 0; i < course->pa; i++)
    {
        pa(b, a);
    }
	printf("DESPUES DEL PUSH\npila_a->fill== %d pila_b.>fill==%d\n", a->fill, b->fill);
}


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
        printf("777 ___Elementos en stack_a después de take_course: %d\n", stack_a->fill);
        printf("Elementos en stack_b después de take_course: %d\n", stack_b->fill);
    }

    return 0;
}
