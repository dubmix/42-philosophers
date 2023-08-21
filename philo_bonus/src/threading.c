/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelanno <pdelanno@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 16:40:00 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/21 14:48:02 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	launch_processes(t_env *env)
{
	int	i;

	i = 0;
	env->start_time = get_time();
	sem_wait(env->stop);
	while (i < env->number_of_philosophers)
	{
		env->philosopher[i].pid = fork();
		if (env->philosopher[i].pid == 0)
		{
			processes(env->philosopher + i);
			exit(0);
		}
		i++;
	}
	sem_wait(env->stop);
	exit_threads(env);
}

void	*ft_death_checker(void *arg)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)arg;
	while (1)
	{
		sem_wait(philosopher->env->death);
		if (philosopher->next_meal < get_time())
		{
			print_status(philosopher, "died");
			sem_post(philosopher->env->stop);
			break ;
		}
		sem_post(philosopher->env->death);
	}
	return (NULL);
}

void	processes(t_philosopher *philosopher)
{
	pthread_t	death;

	philosopher->next_meal = get_time()
		+ (unsigned int)philosopher->env->time_to_die;
	pthread_create(&death, NULL, ft_death_checker, philosopher);
	pthread_detach(death);
	while (1)
	{
		philosopher_eats(philosopher);
		print_status(philosopher, "is sleeping");
		nap(philosopher->env->time_to_sleep);
		print_status(philosopher, "is thinking");
	}
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
	sem_close(env->death);
	sem_close(env->stop);
}
