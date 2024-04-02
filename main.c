#include "comp.h"
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

float ft_sqrt_float(float nb) {
    float guess = nb / 2.0; // Initial guess, can be any positive value
    float prevGuess; // Variable to store the previous guess
    
    // Iterate until convergence
    do {
        prevGuess = guess;
        guess = (guess + nb / guess) / 2.0; // Update the guess using Newton's method
    } while (prevGuess != guess); // Continue until the guess no longer changes
    
    return guess;
}
float	one_solu(t_equation eq)
{
	return ((-eq.first_deg)/(2*eq.second_deg));
}

float	first_solu(t_equation eq, float res)
{
	float	a;

	a = (-eq.first_deg + ft_sqrt_float(res));
	if (a == 0)
		return (0);
	float	b;
	b = a / (2 * eq.second_deg);
	return (b);
}

float second_solu(t_equation eq, float res)
{
	float	a;

	a = (-eq.first_deg - ft_sqrt_float(res));
	if (a == 0)
		return (0);
	float	b;
	b = a / (2 * eq.second_deg);
	return (b);
}

bool	solution(t_equation eq)
{
	float	res;

	if (!eq.first_deg)
		return (false);
	res = (eq.first_deg * eq.first_deg) - 4 * (eq.second_deg * eq.constant);
	if (res < 0)
		return (false);
	else if (res == 0)
		printf("1 solution :%f\n", one_solu(eq));
	else
		printf("2 solution : %f %f\n", first_solu(eq, res), second_solu(eq, res));
	return (true);
}

bool check_pattern(char *equation, int *idx, int *degree)
{
	if (!equation)
		return (false);
	if (equation[*idx] && !isspace(equation[*idx]))
		return (false);
	(*idx)++;
	if (equation[*idx] && equation[*idx] != '*')
		return (false);
	(*idx)++;
	if (equation[*idx] && !isspace(equation[*idx]))
		return (false);
	(*idx)++;
	if ((equation[*idx] && equation[*idx] != 'X') || (equation[*idx + 1] && equation[*idx + 1] != '^') || ((equation[*idx + 2] && !isdigit(equation[*idx + 2])) || (equation[*idx + 3] && isdigit(equation[*idx + 3]))))
		return (false);
	(*idx) = (*idx) + 2;
	*degree = atoi(&equation[*idx]);
	(*idx) = (*idx) + 1;
	if (equation[*idx] && equation[*idx] != ' ' && equation[*idx] != '=')
		return (false);
	return (true);

}

bool fill_equation(t_equation *eq, char *equation)
{
	int i = 0;
	int value = 0;
	int degree = -1;
	int type = 1;
	//bool equation_operator = false;

	//printf("%s\n", equation);
	while (equation && equation[i] && equation[i] != '='){
		//printf("\n");
		if (isdigit(equation[i]) || (type != 0 && equation[i] == '-')){
		//	printf("%c ", equation[i]);
			if (equation[i] == '-' && equation[i + 1] && !isdigit(equation[i + 1]))
				return (false);
			value = atoi(&equation[i]);
			while (equation[i] && isdigit(equation[i]))
			{
				i++;
			}
			if (!check_pattern(equation, &i, &degree))
				return (false);
		//	printf("degre : %i ", degree);
			//Polynomial > 2 non geree
			if (degree > 2)
				return (false);
			if (type == 1)
			{
				if (degree == 1)
					eq->first_deg += value;
				else if (degree == 0)
					eq->constant += value;
				else if (degree == 2)
					eq->second_deg += value;
			}
			else {
				if (degree == 1)
					eq->first_deg -= value;
				else if (degree == 0)
					eq->constant -= value;
				else if (degree == 2)
					eq->second_deg -= value;
			}
			if (!equation[i])
			{
				continue ;
			}
			else if (equation[i] == '='){
				break ;
			}
			type = 0;
			//checker le char + *
		}
		if (equation[i] == '+')
			type = 1;
		else if (equation[i] == '-') type = 2;
		i++;
	}
	return (true);
}


int	main(int ac, char **av)
{
	t_equation developped_form;
	t_equation left;
	t_equation right;

	if (ac != 2)
	{
		printf("Wrong arguments format\n");
		return (1);
	}
	memset(&developped_form, 0, sizeof(developped_form));
	memset(&left, 0, sizeof(left));
	memset(&right, 0, sizeof(right));

	//check the format maybe
	if (!fill_equation(&left, av[1]))
	{
		printf("Format error\n");
		return (1);
	}

	char *right_part = strchr(av[1], '=');
	if (!right_part)
	{
		printf("Format error\n");
		return (1);
	}
	if (!fill_equation(&right, right_part + 1))
	{
		printf("Format error\n");
		return (1);
	}
	
	printf("left form : %fx2 %fx %f\n", left.second_deg, left.first_deg, left.constant);
	developped_form.second_deg = left.second_deg - right.second_deg;
	developped_form.first_deg = left.first_deg - right.first_deg;
	developped_form.constant = left.constant - right.constant;

	printf("developeed form : %fx2 %fx %f\n", developped_form.second_deg, developped_form.first_deg, developped_form.constant);

	if (!solution(developped_form))
	{
		printf("No solution\n");
		return (1);
	}
	return (0);
}
