#include "philo.h"

bool init_arguments(int ac, char **av, t_philomain *philomain)
{
    philomain->is_dead = false;
    pthread_mutex_init(&philomain->printing, NULL);
    philomain->philo_nb = ft_atoi(av[1]);
    philomain->time_to_die = ft_atoi(av[2]);
    philomain->time_to_eat = ft_atoi(av[3]);
    philomain->time_to_sleep = ft_atoi(av[4]);
    if (ac == 6)
    {
        philomain->must_eat = ft_atoi(av[5]);
        if (philomain->must_eat < 0)
        {
            printf("Invalid argument\n");
            return (false);
        }
    }
    else
        philomain->must_eat = -1;
    if (philomain->philo_nb <= 0 || philomain->time_to_die < 0 ||
        philomain->time_to_eat < 0 || philomain->time_to_sleep < 0)
    {
        printf("Invalid argument\n");
        return (false);
    }
    return (true);
}

bool init_philo(t_philomain *pm, int i)
{
    pm->mutexes = malloc(sizeof(pthread_mutex_t) * pm->philo_nb);
	if(!pm->mutexes)
		return(false);
	pm->philos = malloc(sizeof(t_philosophers) * pm->philo_nb);
	if(!pm->philos)
		return(false);
	while(i < pm->philo_nb)
	{
		if (pthread_mutex_init(&pm->mutexes[i++], NULL) != 0)
		{
			printf("Mutex init failed\n");
			return(false);
		}
	}
	i = -1;
	while(++i < pm->philo_nb)
	{
		pm->philos[i].id = i + 1;
		pm->philos[i].right_fork_id = (pm->philos[i].id % pm->philo_nb) + 1;
		pm->philos[i].left_fork_id = pm->philos[i].id;
        pm->philos[i].pm = pm;
        pm->philos[i].eat = 0;
	}
    pm->time = gettime();
    return(true);
}