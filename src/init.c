/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 19:38:31 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/12/30 04:34:43 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	mutex_init(t_sim *sim, int i)
{
	if (pthread_mutex_init(&sim->log_mutex, NULL) != 0)
	{
		printf("log mutex initialization failed\n");
		destroy_mutex(i, sim);
	}
	if (pthread_mutex_init(&sim->alive_mutex, NULL) != 0)
	{
		printf("alive mutex initialization failed\n");
		pthread_mutex_destroy(&sim->log_mutex);
		i = 0;
		destroy_mutex(i, sim);
	}
}

void	init_sim(t_sim *sim, char **argv)
{
	int	i;

	sim->philos_count = ft_atoi(argv[1]);
	sim->time_to_die = ft_atoi(argv[2]);
	sim->time_to_eat = ft_atoi(argv[3]);
	sim->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		sim->required_meals = ft_atoi(argv[5]);
	else
		sim->required_meals = -1;
	sim->all_alive = 1;
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->philos_count);
	i = -1;
	while (++i < sim->philos_count)
	{
		if (pthread_mutex_init(&sim->forks[i], NULL) != 0)
		{
			printf("Error initializing mutex for fork %d\n", i);
			destroy_mutex(i, sim);
		}
	}
	mutex_init(sim, i);
}

void	init_philos(t_sim *sim, t_philo *philos)
{
	int		i;

	i = 0;
	while (i < sim->philos_count)
	{
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].left_fork = &sim->forks[i];
		philos[i].right_fork = &sim->forks[(i + 1) % sim->philos_count];
		philos[i].sim = sim;
		if (pthread_mutex_init(&philos[i].state_mutex, NULL) != 0)
		{
			while (i > 0)
				pthread_mutex_destroy(&philos[--i].state_mutex);
			free(philos);
			return ;
		}
		i++;
	}
}

void	init_all_data(char **argv) //continue_it
{
	t_philo		*philos;
	t_sim		*simulation;

	simulation = malloc(sizeof(t_sim));
	init_sim(simulation, argv);
	philos = malloc(sizeof(t_philo) * simulation->philos_count);
	if (!philos)
		return ;
	init_philos(simulation, philos);
	simulation->philos = philos;
	simulation->start_time = get_current_time();
	// to revise
	if (simulation->philos_count == 1)
	{
		log_state(&philos[0], "has taken a fork");
		accurate_sleep(simulation->time_to_die);
		log_state(&philos[0], "died");
		clean(philos, simulation);
		exit(0);
	}
}
