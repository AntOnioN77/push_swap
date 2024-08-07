

#include "circular_array.h"

t_level		find_place_for(t_ciar *stack_a, int n)
{
	int i;


	if (stack_a->fill == 0 || stack_a->fill == 1)
		return (0);
	i = 0;
	while (i < stack_a->fill)
	{
		if (get_n_element(i) > n && get_n_element(i-1) < n)
			return(i);
		i++;
	}
}

t_course *synch_rotation(stack_a, stack_b, target_a, level_b)
{
	t_course *with_rr;
	t_course *whit_rrr;

	
}


int find_rigth_course(t_ciar *stack_a, t_ciar *stack_b ,t_course **best_course)
{
	t_level target_a;
	t_level level_b;
	t_course *this_course;

	level_b = -1; // valga de momento,deberia ser 0 pero me quedo sin lineas para el ++
	while (++level_b < stack_b->fill)
	{
		target_a = find_place_for(stack_a, get_n_element(stack_b, level_b));
		this_course = synch_rotation(stack_a, stack_b, target_a, level_b);
		if (!this_course)
			return (ERROR);
		if (!(*best_course) || this_course->steps < (*best_course)->steps)
		{
			free(*best_course);
			*best_course = this_course;
		}
		this_course = asynch_rotation(stack_a, stack_b, target_a, level_b);
		if (!this_course)
			return (ERROR);
		if (this_course->steps < (*best_course)->steps)
		{
			free(*best_course);
			*best_course = this_course;
		}
	}
	return (0);
}


/*Con giro sincrono (rr)
	rotando = mayor distancia al top
		rr = menor distancia al top,
		ra = (distancia de a al top) - (distancia de b al top), si es negativa  setear a 0;
		rb = (distancia de b al top) - (distancia de a al top), si es negativa  setear a 0;
	rotando inversamente = mayor distancia al top con %(...)
		(...)
	pasos totales = elegir la menor;
con giro asincrono
	rra = si tier >= (sice list /2) = size_list (+1?) - tier
	ra = si tier < (sice list /2) = tier;
	calcular para b tambien
	pasos totales = pasos de a + pasos de b;

se almacena solo el mejor
	en un struct que debe tener los pasos totales la posición (tier) al que corresponde y los pasos que dé de cada rr rrr ra rb rra rrb pa.
	*/


/* otras ideas.
	1- si encuentra la mediana al vaciar b en a la empuja abajo de manera que sera el pibote, cuando empecemos a ordenar
	2- vaciar la pila a en la pila b dividiendo en chunks de forma que los mas pekeños y los mas grandes queden en el centro y en
	el exterior el chunk con valores intermedios. (empezar por los chunks mas grandes con pb, y al llegar a la mitad empezar a hacer pb+rb)

	*/