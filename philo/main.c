#include "philosophers.h"


void init_table(t_table *table)
{
    create_philos(table);

}

int main(int c, char **v)
{
    t_table table;

    memset(&table, 0, sizeof(t_table));
    if (c < 5 || c > 6)
    {
        printf("Error: Invalid arguments\n");
        return (1);
    }
    table.num_philos = ft_atoi(v[1]);
    table.time_to_die = ft_atoi(v[2]);
    table.time_to_eat = ft_atoi(v[3]);
    table.time_to_sleep = ft_atoi(v[4]);
    if (v[5])
        table.philo_must_eat = ft_atoi(v[5]);
    init_table(&table);
}