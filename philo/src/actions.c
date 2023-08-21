/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelanno <pdelanno@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 16:40:43 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/15 11:09:39 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	nap(unsigned long time, t_philosopher *philosopher)
{
	unsigned long	start;

	start = get_time();
	while (read_death(philosopher->env) == 0)
	{
		if (get_time() - start >= time)
			break ;
		usleep(50);
	}
}

void	print_status(t_philosopher *philosopher, char *str)
{
	pthread_mutex_lock(&philosopher->env->printing);
	if (read_death(philosopher->env) == 0)
	{
		printf("%lu ", get_time() - philosopher->env->start_time);
		printf("%i ", philosopher->id);
		printf("%s\n", str);
	}
	pthread_mutex_unlock(&philosopher->env->printing);
}

void	philosopher_eats(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->env->forks[philosopher->left_fork_id]);
	print_status(philosopher, "has taken a fork");
	pthread_mutex_lock(&philosopher->env->forks[philosopher->right_fork_id]);
	print_status(philosopher, "has taken a fork");
	pthread_mutex_lock(&philosopher->env->meal);
	print_status(philosopher, "is eating");
	philosopher->last_meal = get_time();
	pthread_mutex_unlock(&philosopher->env->meal);
	philosopher->number_of_meals += 1;
	nap(philosopher->env->time_to_eat, philosopher);
	pthread_mutex_unlock(&philosopher->env->forks[philosopher->right_fork_id]);
	pthread_mutex_unlock(&philosopher->env->forks[philosopher->left_fork_id]);
}
