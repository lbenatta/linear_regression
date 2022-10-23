/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_regression_predict.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenatta <lbenatta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:17:45 by lbenatta          #+#    #+#             */
/*   Updated: 2022/10/23 15:57:00 by lbenatta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	main(void)
{
	int				f;
	char			*str;
	char			**strs;
	int				i;
	long double		theta0 = 0;
	long double		theta1 = 0;
	long double		nombre = 0;
	long double		resultat = 0;

	t_tab	*tab;

	printf(" Le prix ne peut être estimé pour un kilométrage >= 396271\n");
	printf(" Entrez le nombre de km (< 396271): ");
	if (scanf("%Le", &nombre) <= 0)
	{
		printf("Le prix ne peut être estimé.\n");
		unlink("theta.csv");
		return (0);
	}
	if ((nombre >= 396271) || (nombre < 0))
	{
		printf("Le prix ne peut être estimé.\n");
		unlink("theta.csv");
		return (0);
	}
	else
	{
		f = open("theta.csv", O_RDONLY, O_TRUNC);
		if (f == 0)
		{
			printf("Le fichier n'existe pas\n");
			unlink("theta.csv");
			return (0);
		}
		else
		{
			i = 0;
			tab = (t_tab *)malloc(sizeof(t_tab));
			memset(tab, 0, sizeof(t_tab));
			if (!tab)
			{
				printf("Échec de l'allocation\n");
				close(f);
				unlink("theta.csv");
			 	return (0);
			}
			str = get_next_line(f);
			if (str == NULL)
			{
				theta0 = 0;
				theta1 = 0;
				resultat = (theta0 + (theta1 * nombre));
				printf(" Le prix estimé est %.2Lf Euros.\n", resultat);
				free(tab);
				close(f);
				unlink("theta.csv");
				return (0);
			}
			else
			{
				strs = ft_split(str, ',');
				theta0 = ft_atoi(strs[0]);
				theta1 = atof(strs[1]);
					i++;
				free(str);
				ft_freesplit(strs);
				str = get_next_line(f);
				free(str);
				str = get_next_line(f);
				resultat = (theta0 + (theta1 * nombre));
				printf(" Le prix estimé est %.2Lf Euros.\n", resultat);
				printf("theta0 = %.2Lf\n", theta0);
				printf("theta1 = %.5Lf\n", theta1);
				free(str);
				free(tab);
				close(f);
				f = open("theta.csv", O_WRONLY | O_TRUNC);
				close(f);
				unlink("theta.csv");
				return (0);
			}
			free(str);
			ft_freesplit(strs);
			unlink("theta.csv");
		}
	}
}
