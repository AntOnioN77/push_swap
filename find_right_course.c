#include <assert.h> //borrar, es de prueba



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

void	run_sync_rotate(t_place deeper , t_place higher, t_course *course)
{
	course->steps = deeper.level + 1; //+1 por el pa
	// TO DO arregla esto:
	course->rr = higher.level;//que pasa en caso de que el resultado sea mayor que el numero de operaciones necesarias para hacer que higuer sobrepase el top? esto podria suceder si la pila con higher es mucho mas grande que la pila con  deeper.
	course->rrr = 0;
	if (deeper.stack_name == 'a')
		{
			course->ra = deeper.level - higher.level;
			course->rb = 0;
		}
	if (deeper.stack_name == 'b')
	{
			course->rb = deeper.level - higher.level;
			course->ra = 0;
	}
	course->rra = 0;
	course->rrb = 0;
	course->pa	= 1;

}


/*
void	run_reverse_rotate(t_place deeper , t_place higher, t_course *course)
{
	t_place near_back;
	t_place farth_back;

	if ((deeper.stack_size - deeper.level) <= (higher.stack_size - higher.level))
		{
			near_back = deeper;
			farth_back = higher;
		}
	else
		{
			near_back = higher;
			farth_back = deeper;
		}

	course->steps = 

}
*/

//no separar esta función de run reverse_rotate
static void	rename_a_b(t_place *deeper, t_place *higher, t_place **place_a ,t_place **place_b)
{
	if (deeper->stack_name == 'a')
	{
		*place_a = deeper;
		*place_b = higher;
	}
	else
	{
		*place_a = higher;
		*place_b = deeper;
	}
}

void	run_sync_reverse_rotate(t_place deeper , t_place higher, t_course *course)
{
	t_place *place_a;
	t_place *place_b;

	rename_a_b(&deeper, &higher, &place_a, &place_b);
	if (deeper.reverse_level > higher.reverse_level)
		course->steps = deeper.reverse_level + 1; //+1 por pa.
	else
		course->steps = higher.reverse_level + 1; //+1 por pa.
	course->rr = 0;
	if (higher.reverse_level <= deeper.reverse_level)
		course->rrr = higher.reverse_level;
	else
		course->rrr = deeper.reverse_level;
	course->ra = 0;
	if (place_a->reverse_level > place_b->reverse_level)
	{
		course->rra = place_a->reverse_level - place_b->reverse_level;
		course->rrb = 0;
	}
	else
	{
		course->rra = 0;
		course->rrb = place_b->reverse_level - place_a->reverse_level;
	}
}



void *synch_rotation(t_place a, t_place b, t_course *best_course)
{
	t_place deeper;
	t_place higher;
	t_course this_course;

	this_course.level = best_course->level;
	if (a.level > b.level)
	{
		deeper = a;
		higher = b;
	}
	else
	{
		deeper = b;
		higher = a;
	}
	if (higher.level <= higher.middel_of_stack) // parece buena para otro fin (&& (deeper.level - higher.level) <= deeper.middel_of_stack)
		run_sync_rotate(deeper, higher, &this_course);
	else
		run_reverse_rotate(deeper, higher, &this_course);
//test borrar lineas siguientes
	t_course course_prueba_1;
	t_course course_prueba_2;
	run_sync_rotate(deeper, higher, &course_prueba_1);
	run_reverse_rotate(deeper, higher, &course_prueba_2);
	if (course_prueba_1.steps < course_prueba_2.steps )
		{
		assert(this_course.steps == course_prueba_1.steps);
		}
	else
		{
		assert(this_course.steps == course_prueba_2.steps);
		}
//fin test
	if (this_course.steps < best_course->steps)
		memcpy(best_course, &this_course, sizeof(t_course));// pasar a ft_!!!
}

asynch_rotation(t_place position_in_a, t_place position_in_b, t_course best_course)
{
	t_course this_course;

	if (position_in_a.middel_of_stack >= position_in_a.level)
		run_rotate(this_course, position_in_a, 0);
		run_reverse_rotate(this_course, position_in_b, this_course.steps);
	else

}

t_place init_place(t_ciar *stack, t_level level, char stack_name)
{
    t_place new_place;

    new_place.stack_name = stack_name;
    new_place.level = level;
    new_place.middel_of_stack = stack->fill / 2;
    new_place.stack_size = stack->fill;
	if (level == 0)
		new_place.reverse_level = 0;
	else
    	new_place.reverse_level = stack->fill - level;
    return new_place;
}

//TO DO best course debe llegar inicializado, todo a 0 excepto steps, steps = MAX_INT
void find_rigth_course(t_ciar *stack_a, t_ciar *stack_b ,t_course *best_course)
{
	t_level level_a;
	t_level level_b;
	t_place	position_in_a;
	t_place	position_in_b;

	level_b = 0;
	while (level_b < stack_b->fill)
	{
		level_a = find_place_for(stack_a, get_n_element(stack_b, level_b));
		position_in_a = init_place(stack_a, level_a, 'a');
		position_in_b = init_place(stack_b, level_b, 'b');
		synch_rotation(position_in_a, position_in_b, best_course);
		asynch_rotation(position_in_a, position_in_b, best_course);
		level_b++;
	}
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