#include "philosophers.h"

int main(int argc, char **argv)
{
    t_diner    *diner;

    init_diner(&diner, argc, argv);
    dining(&diner);
	clean_diner(&diner);
    return (0);
}
