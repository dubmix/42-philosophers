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

// void	*test_process(t_philosopher *philosopher)
// {
// 	print_status(philosopher, "is sleeping");
// 	return (NULL);
// }

void	launch_processes(t_env *env)
{
	int	i;

	i = 0;
	env->start_time = get_time();
	while (i < env->number_of_philosophers)
	{
		env->philosopher[i].last_meal = get_time();
		env->philosopher[i].pid = fork();
		if (env->philosopher[i].pid == 0)
		{
			processes(env->philosopher + i);
			exit(0);
		}
		i++;
	}
	// faire fonction qui update le last_meal dans le parent process
	death_checker(env);
	exit_threads(env);
}

void	processes(t_philosopher *philosopher)
{
	if (philosopher->id % 2 != 0
		&& philosopher->env->number_of_philosophers > 1)
		nap(philosopher->env->time_to_eat, philosopher);
	while (philosopher->env->dead == 0)
	{
		philosopher_eats(philosopher);
		if (philosopher->env->all_ate != 0
			|| philosopher->number_of_meals == philosopher->env->max_meals)
			break ;
		print_status(philosopher, "is sleeping");
		nap(philosopher->env->time_to_sleep, philosopher);
		print_status(philosopher, "is thinking");
	}
}

void	death_checker(t_env *env)
{
	int	i;

	while (env->all_ate == 0)
	{
		i = 0;
		while (i < env->number_of_philosophers && env->dead == 0)
		{
			//sem_wait(env->meal);
			printf("i is: %d\n", i);
			printf("last meal of %d is: %lu\n", env->philosopher[i].id, env->philosopher[i].last_meal);
			usleep(100000);
			if ((get_time() - (env->philosopher[i].last_meal))
				>= (unsigned long)env->time_to_die)
			{
				if (env->philosopher[i].number_of_meals != env->max_meals)
					print_status(env->philosopher, "died");
				env->dead = 1;
			}
			//sem_post(env->meal);
			i++;
		}
		if (env->dead != 0)
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
		kill(env->philosopher[i].pid, SIGKILL);
		i++;
	}
	sem_close(env->forks);
	sem_close(env->printing);
	sem_close(env->meal);
}
