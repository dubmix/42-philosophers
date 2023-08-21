/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelanno <pdelanno@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 22:43:00 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/15 11:07:31 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_philosopher
{
	int				id;
	int				left_fork_id;
	int				right_fork_id;
	int				number_of_meals;
	unsigned long	last_meal;
	struct s_env	*env;
	pthread_t		thread_id;
}	t_philosopher;

typedef struct s_env
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				all_ate;
	int				max_meals;
	int				dead;
	t_philosopher	philosopher[200];
	unsigned long	start_time;
	pthread_mutex_t	meal;
	pthread_mutex_t	printing;
	pthread_mutex_t	death;
	pthread_mutex_t	forks[200];
}	t_env;

void			err_msg(char *str);
unsigned long	get_time(void);
int				check_params(int argc, char *argv[]);

void			nap(unsigned long time, t_philosopher *philosopher);
void			print_status(t_philosopher *philosopher, char *str);
int				philosopher_eats(t_philosopher *philosopher);

void			init(t_env *env, int argc, char *argv[]);
void			launch_threads(t_env *env);
void			*pthread(void *params);
void			death_checker(t_env *env);
void			death_checker_sub(t_env *env);
void			exit_threads(t_env *env);

int				ft_atoi(const char *str);

void			convert_args(t_env *env, int argc, char *argv[]);
void			init_mutex(t_env *env);
int				init_philos(t_env *env);

int				read_death(t_env *env);
void			write_death(t_env *env);
unsigned long	pulse_check(t_env *env, int i);

#endif
