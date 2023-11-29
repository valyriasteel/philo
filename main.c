#include "philo.h"

void	my_sleep(u32 time)
{
	u32	start;

	start = gettime();
	while (31)
	{
		if (gettime() - start >= time)
			break ;
		usleep(30);
	}
}

void	take_forks(t_philosophers *philo)
{
	t_philomain	*pm;

	pm = philo->pm;
	pthread_mutex_lock(&pm->mutexes[philo->right_fork_id - 1]);
	print(philo, "has taken a fork");
	if (philo->pm->philo_nb == 1)
	{
		my_sleep(pm->time_to_die);
		pthread_mutex_unlock(&pm->mutexes[philo->right_fork_id - 1]);
		return ;
	}
	pthread_mutex_lock(&pm->mutexes[philo->left_fork_id - 1]);
	print(philo, "has taken a fork");
	print(philo, "is eating");
	philo->end_time_to_eat = gettime();
	philo->eat++;
	my_sleep(pm->time_to_eat);
	pthread_mutex_unlock(&pm->mutexes[philo->right_fork_id - 1]);
	pthread_mutex_unlock(&pm->mutexes[philo->left_fork_id - 1]);
	print(philo, "is sleeping");
	my_sleep(pm->time_to_sleep);
	print(philo, "is thinking");
}

void	*my_thread(void *value)
{
	t_philosophers	*philo;

	philo = value;
	if (philo->id % 2 == 0)
		usleep(6000);
	while (philo->pm->is_dead == false)
	{
		take_forks(philo);
		if (philo->eat == philo->pm->must_eat)
			break ;
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	int	i;
	t_philomain	philomain;

	i = -1;
	if (ac != 5 && ac != 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (1);
	}
	if (init_arguments(ac, av, &philomain) == false)
		return (1);
	init_philo(&philomain, 0);
	philomain.threads = malloc(sizeof(pthread_t) * philomain.philo_nb);
	if (!philomain.threads)
		return (1);
	while (++i < philomain.philo_nb)
	{
		philomain.philos[i].end_time_to_eat = gettime();
		pthread_create(&philomain.threads[i], NULL, my_thread, \
		&philomain.philos[i]);
	}
	i = -1;
	while (1)
	{
		if (++i < philomain.philo_nb)
		{
			if (gettime() - philomain.philos[i].end_time_to_eat \
			>= philomain.time_to_die)
			{
				print(philomain.philos, "died");
				philomain.is_dead = true;
				break ;
			}
			if (philomain.philos[i].eat == philomain.must_eat)
				break ;
		}
		else
			i = -1;
	}
	i = -1;
	while (++i < philomain.philo_nb)
		pthread_join(philomain.threads[i], NULL);
	pthread_mutex_destroy(&philomain.printing);
	i = -1;
	while (++i < philomain.philo_nb)
		pthread_mutex_destroy(&philomain.mutexes[i]);
	return (0);
}
