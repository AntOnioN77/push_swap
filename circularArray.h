/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circularArray.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antofern <antofern@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:01:26 by antofern          #+#    #+#             */
/*   Updated: 2024/07/21 22:48:52 by antofern         ###   ########.fr       */
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