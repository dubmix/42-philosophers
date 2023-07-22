/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelanno <pdelanno@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 22:56:00 by pdelanno          #+#    #+#             */
/*   Updated: 2023/07/21 23:26:56 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int main(int argc, char *argv[])
{
	t_env	env;

	if (argc < 5 || argc > 6)
		err_msg("Wrong number of arguments");
	if (check_params(argc, argv) == 0)
		err_msg("Wrong parameters");
	init(&env, argc, argv);
	launch_threads(&env);
	return (0);
}

//4 800 300 300

int		check_params(int argc, char *argv[])
{
	int i;

	i = 1;
	while (i < argc)
	{
		if (ft_atoi(argv[i]) <= 0)
			return (0);
		i++;
	}
	if (ft_atoi(argv[1]) < 1)
		return (0);
	else if (ft_atoi(argv[2]) < 0)
		return (0);
	else if (ft_atoi(argv[3]) < 0)
		return (0);
	else if (ft_atoi(argv[4]) < 0)
		return (0);
	if (argc == 6 && ft_atoi(argv[5]) <= 0)
			return (0);
	return (1); 
}