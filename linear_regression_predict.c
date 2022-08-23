/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_regression_predict.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenatta <lbenatta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:17:45 by lbenatta          #+#    #+#             */
/*   Updated: 2022/08/22 17:58:56 by lbenatta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	main(void)
{    
    int	        f;
	char	    *str;
	char	    **strs;
	int	        i;
    long double         theta0;
    long double         theta1;
    int         nombre = 0;
	long double     	resultat = 0;
	t_tab	*tab;

    printf(" Le prix ne peut être estimé pour un kilométrage > 396 245.\n Entrez le nombre de km (< 396 245):");
	scanf("%d", &nombre);
	{
		if (nombre >= 396245)
			printf("Le prix ne peut être estimé.\n");
		else
        {
            f = open("theta.csv", O_RDONLY);
	        i = 0;
	        tab = (t_tab *)malloc(sizeof(t_tab));
	        str = get_next_line(f);
	        free(str);
	        str = get_next_line(f);
            while (str == NULL)
	        {
	 	        theta0 = 0;
	 	        theta1 = 0;
                resultat = (theta0 + (theta1 * nombre));
		        printf(" Le prix estimé est %.2Lf Euros.\n", resultat);
                return (0);
            }
	        while (str != NULL)
	        {
		        strs = ft_split(str, ',');
		    	theta0 = ft_atoi(strs[0]);
		        theta1 = atof(strs[1]);
			         i++;
		        str = get_next_line(f);
				resultat = (theta0 + (theta1 * nombre));
		        printf(" Le prix estimé est %.2Lf Euros.\n", resultat);
                return (0);
            }
			//printf("%.2Lf\n", theta0);
			//printf("%.5Lf\n", theta1);
			return (0);
        }
    }
}