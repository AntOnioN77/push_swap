/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circularArray.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antofern <antofern@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:01:26 by antofern          #+#    #+#             */
/*   Updated: 2024/07/24 17:15:12 by antofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_ciar
{
	int	*buff;
	int	top;
	int	back;
	int	slots;
	int	fill;
}	t_ciar;
#define ERROR 1
#define OK 0
#define EMPTY_STACK -1
#define FULL_STACK -2 //no debería ser posible



#define MAX_OPERATIONS 5 // Ajusta según sea necesario

typedef enum {
    SA, SB, SS, PA, PB, RA, RB, RR, RRA, RRB, RRR
} Operation;

typedef struct {
    Operation ops[MAX_OPERATIONS];
    int count;
} Solution;


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