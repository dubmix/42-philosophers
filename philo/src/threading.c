/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelanno <pdelanno@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 16:40:00 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/15 11:20:52 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	launch_threads(t_env *env)
{
	int	i;
	int	ret;

	i = 0;
	env->start_time = get_time();
	while (i < env->number_of_philosophers)
	{
		env->philosopher[i].last_meal = get_time();
		ret = pthread_create(&env->philosopher[i].thread_id, NULL,
				pthread, &(env->philosopher[i]));
		if (ret != 0)
			exit(EXIT_FAILURE);
		i++;
	}
	death_checker(env);
	exit_threads(env);
}

void	*pthread(void *params)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)params;
	if (philosopher->id % 2 != 0
		&& philosopher->env->number_of_philosophers > 1)
		nap(philosopher->env->time_to_eat, philosopher);
	while (read_death(philosopher->env) == 0)
	{
		philosopher_eats(philosopher);
		if (philosopher->env->all_ate != 0
			|| philosopher->number_of_meals == philosopher->env->max_meals)
			break ;
		print_status(philosopher, "is sleeping");
		nap(philosopher->env->time_to_sleep, philosopher);
		print_status(philosopher, "is thinking");
	}
	return (NULL);
}

void	death_checker(t_env *env)
{
	int	i;

	while (env->all_ate == 0)
	{
		i = 0;
		while (i < env->number_of_philosophers && read_death(env) == 0)
		{
			if (pulse_check(env, i) >= (unsigned long)env->time_to_die)
			{
				if (env->philosopher[i].number_of_meals != env->max_meals)
					print_status(env->philosopher, "died");
				write_death(env);
			}
			i++;
		}
		if (read_death(env) != 0)
			break ;
		death_checker_sub(env);
	}
}

void	death_checker_sub(t_env *env)
{
	int	i;

	i = 0;
	while (env->max_meals <= -1 && i < env->number_of_philosophers
		&& env->philosopher[i].number_of_meals <= env->max_meals)
		i++;
	if (i == env->number_of_philosophers)
		env->all_ate = 1;
}

void	exit_threads(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->number_of_philosophers && env->number_of_philosophers != 1)
	{
		pthread_join(env->philosopher[i].thread_id, NULL);
		i++;
	}
	i = 0;
	while (i < env->number_of_philosophers)
	{
		pthread_mutex_destroy(&env->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&env->printing);
	pthread_mutex_destroy(&env->meal);
	pthread_mutex_destroy(&env->death);
}
