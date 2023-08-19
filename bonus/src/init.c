/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelanno <pdelanno@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:30:18 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/15 11:20:24 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	init(t_env *env, int argc, char *argv[])
{
	convert_args(env, argc, argv);
	env->all_ate = 0;
	env->dead = 0;
	init_semaphores(env);
	init_philos(env);
}

void	convert_args(t_env *env, int argc, char *argv[])
{
	env->number_of_philosophers = ft_atoi(argv[1]);
	env->time_to_die = ft_atoi(argv[2]);
	env->time_to_eat = ft_atoi(argv[3]);
	env->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		env->max_meals = ft_atoi(argv[5]);
	else
		env->max_meals = -1;
}

void	init_semaphores(t_env *env)
{
	sem_unlink("forks");
	sem_unlink("printing");
	sem_unlink("meal");
	sem_unlink("stop");
	env->forks = sem_open("forks", O_CREAT, 0644, env->number_of_philosophers);
	env->printing = sem_open("printing", O_CREAT, 0644, 1);
	env->meal = sem_open("meal", O_CREAT, 0644, 1);
	env->stop = sem_open("stop", O_CREAT, 0644, 1);
}

int	init_philos(t_env *env)
{
	int	i;

	//env->forks = NULL;
	//env->printing = NULL;
	i = env->number_of_philosophers - 1;
	while (i >= 0)
	{
		env->philosopher[i].id = i + 1;
		env->philosopher[i].pid = -1;
		env->philosopher[i].number_of_meals = 0;
		env->philosopher[i].last_meal = 0;
		env->philosopher[i].env = env;
		i--;
	}
	return (0);
}
