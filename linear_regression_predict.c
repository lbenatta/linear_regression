/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_regression_predict.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenatta <lbenatta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:17:45 by lbenatta          #+#    #+#             */
/*   Updated: 2022/08/29 16:12:12 by lbenatta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	main(void)
{
	int					f;
	char				*str;
	char				**strs;
	int					i;
	long double			theta0 = 0;
	long double			theta1 = 0;
	long double			nombre = 0;
	long double			resultat = 0;
	
	t_tab	*tab;

	printf(" Le prix ne peut être estimé pour un kilométrage >= 396271\n"); 
	printf(" Entrez le nombre de km (< 396271):\n"); 
	scanf("%Lf", &nombre);

	if ((nombre >= 396271) || (nombre <= 0) || (isdigit(nombre) != 0))
		printf("Le prix ne peut être estimé.\n");
	else
	{
		f = open("theta.txt", O_RDONLY);
		if (f == 0)
		{
			printf("Le fichier n'existe pas\n");
			return(0);
		}
		else
		{
			i = 0;
			tab = (t_tab *)malloc(sizeof(t_tab));
			if (tab == NULL)
			{
				printf("Échec de l'allocation\n");
				return(1);
			}
			str = get_next_line(f);
			free(str);
			str = get_next_line(f);
			if (str == NULL)
			{
				theta0 = 0;
				theta1 = 0;
				resultat = (theta0 + (theta1 * nombre));
				printf(" Le prix estimé est %.2Lf Euros.\n", resultat);
				free(tab);
				close(f);
				return (1);
			}
			else
			{
				strs = ft_split(str, ' ');
				theta0 = ft_atoi(strs[0]);
				theta1 = atof(strs[1]);
					i++;
				free(str);
				ft_freesplit(strs);
				str = get_next_line(f);
				resultat = (theta0 + (theta1 * nombre));
				printf(" Le prix estimé est %.2Lf Euros.\n", resultat);
				//printf("%.2Lf\n", theta0);
				//printf("%.5Lf\n", theta1);
				free(tab);
				free(str);
				close(f);
				return (0);
			}
			free(tab);
			free(str);
			return (0);
		}
	}

}