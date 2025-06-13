#include "../includes/philo.h"

int main(int argc, char *argv[])
{
  t_table table;

  if (argc == 5 || argc == 6)
  {
    parse_input(&table, argv);
    data_init(&table);
    dinner_start(&table);
    free_destroy(&table);
  }
  else
    error_exit("WRONG INPUT");
  return 0;
}
