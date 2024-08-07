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

run_rotate(t_place deeper , t_place higher, t_course *course)
{
	//to do
	course->steps = deeper.level + 1; //+1 por el pa
	course->rr = higher.level;
	course->rrr = 0;
	if (deeper.stack == 'a')
		{
			course->ra = deeper.level - higher.level;
			course->rb = 0;
		}
	if (deeper.stack == 'b')
	{
			course->rb = deeper.level - higher.level;
			course->ra = 0;
	}
	course->rra = 0;
	course->rrb = 0;
	course->pa	= 1;

}

run_reverse_rotate()
{}

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
		run_rotate(deeper, higher, &this_course);
	else
		run_reverse_rotate(deeper, higher, &this_course);
//test borrar lineas siguientes
	t_course course_prueba_1;
	t_course course_prueba_2;
	run_rotate(deeper, higher, &course_prueba_1);
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


//TO DO best course debe llegar inicializado, todo a 0 excepto steps, steps = MAX_INT

void find_rigth_course(t_ciar *stack_a, t_ciar *stack_b ,t_course *best_course)
{
	t_level target_a;
	t_level level_b;

	level_b = 0;
	while (level_b < stack_b->fill)
	{
		target_a = find_place_for(stack_a, get_n_element(stack_b, level_b));
		synch_rotation(target_a, level_b, best_course);
		asynch_rotation(target_a, level_b, best_course);
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