/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelanno <pdelanno@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 22:56:00 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/15 11:12:43 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

//4 800 300 300
//even nb of philos the sum of both cant exceed the 2nd arg
//odd nb of philos it needs to b 3 times (ie 1210 400 400)

int	main(int argc, char *argv[])
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

int	check_params(int argc, char *argv[])
{
	int	i;

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
