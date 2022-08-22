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
	int			nombre = 0;
	long double	resultat = 0;
	printf(" Le prix ne peut être estimé pour un kilométrage > 396 245.\n Entrez le nombre de km (< 396 245):");
	scanf("%d", &nombre);
	{
		if (nombre >= 396245)
			printf("Le prix ne peut être estimé.\n");
		else
		{
			resultat = (tab->theta0 + (tab->theta1 * nombre));
			printf(" Le prix estimé est %.4Lg Euros.\n", resultat);
		}
	}
	FILE	*fichier = NULL;
	fichier = fopen("res.txt", "w");
	if (fichier != NULL)
	{
		fprintf(fichier, "\n Estimation mathématique 'classique'(méthode des moindres carrés) :\n theta0 = %.2Lf   et theta1 = %.5Lf\n", tab->theta0 , tab->theta1);
		fprintf(fichier, "  correlation r = %.4Lg\n", tab->r);
		fprintf(fichier, "  accuracy MAE = %.4Lg\n", tab->accur);
		fclose(fichier);
	}
	free (tab);
	return (0);
}
