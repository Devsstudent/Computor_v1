#include "comp.h"
#include <stdio.h>
#include <math.h>
float	one_solu(t_equation eq)
{
	return ((-eq.first_deg)/(2*eq.second_deg));
}

float	first_solu(t_equation eq, float res)
{
	float	a;

	a = (-eq.first_deg + sqrtf(res));
	if (a == 0)
		return (0);
	float	b;
	b = a / (2 * eq.second_deg);
	return (b);
}

float second_solu(t_equation eq, float res)
{
	float	a;

	a = (-eq.first_deg - sqrtf(res));
	if (a == 0)
		return (0);
	float	b;
	b = a / (2 * eq.second_deg);
	return (b);
}

bool	solution(t_equation eq)
{
	float	res;

	res = (eq.first_deg * eq.first_deg) - 4 * (eq.second_deg * eq.constant);
	if (res < 0)
		return (false);
	else if (res == 0)
		printf("1 solution :%f\n", one_solu(eq));
	else
		printf("2 solution : %f %f\n", first_solu(eq, res), second_solu(eq, res));
	return (true);
}

int	main(int ac, char **av)
{
	t_equation	eq;

	eq.second_deg = atof(av[1]);
	eq.first_deg = atof(av[2]);
	eq.constant = atof(av[3]);
	if (!solution(eq))
	{
		printf("No solution\n");
		return (1);
	}
}
