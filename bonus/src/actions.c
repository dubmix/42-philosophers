/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelanno <pdelanno@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 16:40:43 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/19 14:26:03 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	nap(unsigned long time)
{
	usleep(time * 1000);
}

void	print_status(t_philosopher *philosopher, char *str)
{
	sem_wait(philosopher->env->printing);
	if (philosopher->env->dead == 0)
	{
		printf("%lu ", get_time() - philosopher->env->start_time);
		printf("%i ", philosopher->id);
		printf("%s\n", str);
	}
	sem_post(philosopher->env->printing);
}

void	philosopher_eats(t_philosopher *philosopher)
{
	sem_wait(philosopher->env->forks);
	print_status(philosopher, "has taken a fork");
	sem_wait(philosopher->env->forks);
	print_status(philosopher, "has taken a fork");
	print_status(philosopher, "is eating");
	//usleep(philosopher->env->time_to_eat);
	nap(philosopher->env->time_to_eat);
	philosopher->next_meal = get_time() + (unsigned int)philosopher->env->time_to_die;
	//printf("actual last meal of %d is: %lu\n", philosopher->id, philosopher->last_meal);
	philosopher->number_of_meals += 1;
	sem_post(philosopher->env->forks);
	sem_post(philosopher->env->forks);
}
