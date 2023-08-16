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
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>
# include <fcntl.h>
# include <signal.h>

typedef struct s_philosopher
{
	int				id;
	int				number_of_meals;
	unsigned long	last_meal;
	struct s_env	*env;
	pid_t			pid;
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
	sem_t			*meal;
	sem_t			*printing;
	sem_t			*forks;
}	t_env;

void			err_msg(char *str);
unsigned long	get_time(void);
int				check_params(int argc, char *argv[]);

void			nap(unsigned long time, t_philosopher *philosopher);
void			print_status(t_philosopher *philosopher, char *str);
void			philosopher_eats(t_philosopher *philosopher);

void			init(t_env *env, int argc, char *argv[]);
void			launch_processes(t_env *env);
void			processes(t_philosopher *philosopher);
void			death_checker(t_env *env);
void			death_checker_sub(t_env *env);
void			exit_threads(t_env *env);

int				ft_atoi(const char *str);

void			convert_args(t_env *env, int argc, char *argv[]);
void			init_semaphores(t_env *env);
int				init_philos(t_env *env);

#endif
