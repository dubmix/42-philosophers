/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelanno <pdelanno@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 16:39:14 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/21 14:40:22 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

unsigned long	get_time(void)
{
	struct timeval	time;
	unsigned long	t;

	gettimeofday(&time, NULL);
	t = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (t);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			err_msg("Parameter not unsigned int");
		i++;
	}
	i = 0;
	while (str[i] >= 48 && str[i] <= 57)
	{
		nb = nb * 10 + (str[i] - 48);
		i++;
	}
	return (nb);
}

void	write_death(t_env *env)
{
	pthread_mutex_lock(&env->death);
	env->dead = 1;
	pthread_mutex_unlock(&env->death);
}

int	read_death(t_env *env)
{
	int	result;

	pthread_mutex_lock(&env->death);
	result = env->dead;
	pthread_mutex_unlock(&env->death);
	return (result);
}

unsigned long	pulse_check(t_env *env, int i)
{
	unsigned long	result;

	pthread_mutex_lock(&env->meal);
	result = get_time() - env->philosopher[i].last_meal;
	pthread_mutex_unlock(&env->meal);
	return (result);
}
