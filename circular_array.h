/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circular_array.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antofern <antofern@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:01:26 by antofern          #+#    #+#             */
/*   Updated: 2024/08/08 16:09:10 by antofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CIRCULAR_ARRAY_H
#define CIRCULAR_ARRAY_H

typedef struct s_ciar
{
	int	*buff;
	int	top;
	int	back;
	int	slots;
	int	fill;
	int max_fill;
}	t_ciar;
#define ERROR 1
#define OK 0
#define EMPTY_STACK -1
#define FULL_STACK -2 //no debería ser posible

typedef int t_level;
typedef struct s_place
{
	char	stack_name;
	t_level	level;
	int		middel_of_stack;
	int		stack_size;
	int		reverse_level;
}	t_place;

typedef struct s_course
{
	int	level; //? innecesario?
	int	content;//? innecesario?
	int steps;
	int	rr;
	int	rrr;
	int	ra;
	int	rb;
	int	rra;
	int	rrb;
	int pa;
}	t_course;

t_ciar	*init_ciar(int items);
int next_index(int index, int slots);
int prev_index(int index, int slots);
int get_top(t_ciar *stack);
int get_back(t_ciar *stack);
int pop(t_ciar *arr);
int add(t_ciar *arr, int elem);
int rotate(t_ciar *arr);
int reverse_rotate(t_ciar *arr);
int swap(t_ciar *arr);
int push(t_ciar *from, t_ciar *to);
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
void	free_ciar(t_ciar *arr);
int get_level(t_ciar *arr, int index);
int get_n_element(const t_ciar *arr, t_level level);

t_level		find_place_for(t_ciar *stack_a, int n);
void	run_sync_rotate(t_place deeper , t_place higher, t_course *course);
void synch_rotation(t_place a, t_place b, t_course *best_course);
void	asynch_rotation(t_place position_in_a, t_place position_in_b, t_course *best_course);
t_place init_place(t_ciar *stack, t_level level, char stack_name);
void find_rigth_course(t_ciar *stack_a, t_ciar *stack_b ,t_course *best_course);
void init_course(t_course *course);

void take_course(t_course *course, t_ciar *a, t_ciar *b);// BORRAESTO

#endif /* CIRCULAR_ARRAY_H */
