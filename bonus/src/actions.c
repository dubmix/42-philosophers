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

void	nap(unsigned long time, t_philosopher *philosopher)
{
	unsigned long	start;

	start = get_time();
	while (philosopher->env->dead == 0)
	{
		if (get_time() - start >= time)
			break ;
		usleep(50);
	}
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
	philosopher->last_meal = get_time();
	//printf("actual last meal of %d is: %lu\n", philosopher->id, philosopher->last_meal);
	philosopher->number_of_meals += 1;
	nap(philosopher->env->time_to_eat, philosopher);
	sem_post(philosopher->env->forks);
	sem_post(philosopher->env->forks);
}
