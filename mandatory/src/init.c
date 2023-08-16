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
	init_mutex(env);
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

void	init_mutex(t_env *env)
{
	int	i;
	int	ret;

	i = env->number_of_philosophers - 1;
	while (i >= 0)
	{
		ret = pthread_mutex_init(&env->forks[i], NULL);
		if (ret != 0)
			err_msg("Mutex initialization failed");
		i--;
	}
	ret = pthread_mutex_init(&env->printing, NULL);
	if (ret != 0)
		err_msg("Mutex initialization failed");
	ret = pthread_mutex_init(&env->meal, NULL);
	if (ret != 0)
		err_msg("Mutex initialization failed");
}

int	init_philos(t_env *env)
{
	int	i;

	i = env->number_of_philosophers - 1;
	while (i >= 0)
	{
		env->philosopher[i].id = i + 1;
		env->philosopher[i].number_of_meals = 0;
		env->philosopher[i].left_fork_id = i;
		env->philosopher[i].right_fork_id = (i + 1)
			% env->number_of_philosophers;
		env->philosopher[i].last_meal = 0;
		env->philosopher[i].env = env;
		i--;
	}
	return (0);
}
