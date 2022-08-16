/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_regression_estimate.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenatta <lbenatta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:17:45 by lbenatta          #+#    #+#             */
/*   Updated: 2022/08/16 12:39:55 by lbenatta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
/*
void test(t_tab *tab)
{
	//printf("k : %f\n", tab->k[]);
	//printf("p : %f\n", tab->p[]);
	printf("TOTAL_X_km : %d\n", tab->sum_km);
	printf("TOTAL_Y_price : %d\n", tab->sum_price);
	printf("TOTAL_X2_sqr_km : %ld\n", tab->sum_sqr_km);
	printf("TOTAL_Y2_sqr_price : %ld\n", tab->sum_sqr_price);
	printf("TOTAL_XY_prod : %ld\n", tab->sum_pdt);
	printf("theta1 = %f\n", tab->theta1);
	printf("theta0 = %f\n", tab->theta0);
} */

int	main(void)
{
	int		f;
	char	*str;
	char	**strs;
	int		i;
	t_tab	*tab;

	f = open("data.csv", O_RDONLY);
	i = 0;
	tab = (t_tab *)malloc(sizeof(t_tab));
	str = get_next_line(f);
	free(str);
	str = get_next_line(f);
	while (str != NULL)
	{
		strs = ft_split(str, ',');
		tab->km[i] = ft_atoi(strs[0]);
		tab->price[i] = ft_atoi(strs[1]);
			i++;
		str = get_next_line(f);
	}
	tab->count = i;
	i = 0;
	tab->theta0 = 0;
	tab->theta1 = 0;
	tab->sum_price = 0;
	tab->mean_price = 0;
	tab->sum_km = 0;
	tab->mean_km = 0;
	tab->sum_sqr_price = 0;
	tab->sum_sqr_km = 0;
	tab->sum_cov = 0;
	tab->sum_cov = 0;
	tab->sum_var_km = 0;
	tab->sum_var_price = 0;
	tab->r = 0;
	for (i = 0; i < tab->count; i++)
	{
		tab->sum_km = tab->sum_km + tab->km[i];
		tab->mean_km = tab->sum_km / tab->count;
		tab->sum_price = tab->sum_price + tab->price[i];
		tab->mean_price = tab->sum_price / tab->count;
		tab->mean_km = tab->sum_km / tab->count;
		tab->sqr_km[i] = (long double)tab->km[i] * (long double)tab->km[i];
		tab->sqr_price[i] = tab->price[i] * tab->price[i];
		tab->sum_sqr_km = (long double)tab->sum_sqr_km + (long double)tab->sqr_km[i];
		tab->sum_sqr_price = tab->sum_sqr_price + tab->sqr_price[i];
		tab->pdt[i] = (long double)tab->km[i] * (long double)tab->price[i];
		tab->sum_pdt = tab->sum_pdt + tab->pdt[i];
	}
	if (i == tab->count)
	{
		tab->theta1 = ((tab->mean_km * tab->sum_price) - (tab->sum_pdt)) / ((tab->mean_km * tab->sum_km) - (tab->sum_sqr_km));
		tab->theta0 = (tab->mean_price - (tab->theta1 * tab->mean_km));
	}
	for (i = 0; i < tab->count; i++)
	{
		tab->diff_km[i] = (long double)tab->km[i] - (long double)tab->mean_km;
		tab->var_km[i] = powl((long double)tab->diff_km[i], 2);
		tab->sum_var_km = (long double)tab->sum_var_km + (long double)tab->var_km[i];
		tab->diff_price[i] = (long double)tab->price[i] - (long double)tab->mean_price;
		tab->var_price[i] = powl((long double)tab->diff_price[i], 2);
		tab->sum_var_price = (long double)tab->sum_var_price + (long double)tab->var_price[i];
		tab->cov[i] = (((long double)tab->diff_km[i]) * ((long double)tab->diff_price[i]));
		tab->sum_cov = (long double)tab->sum_cov + (long double)tab->cov[i];
		tab->r = tab->sum_cov / (sqrtl(tab->sum_var_km * tab->sum_var_price));
		tab->est_price[i] = (tab->theta1 * tab->km[i]) + tab->theta0;
		tab->delta_price[i] = cabs(tab->est_price[i] - tab->price[i]);
		tab->sum_delta_price = tab->sum_delta_price + (long double)tab->delta_price[i];
		tab->accur = 100 - (100 * (long double)tab->sum_delta_price / (long double)tab->sum_price);
	}
	//printf("sum_km : %Lf\n", tab->sum_km);
	//printf("sum_price : %Lf\n", tab->sum_price);
	//printf("mean_km : %Lf\n", tab->mean_km);
	//printf("mean_price : %Lf\n", tab->mean_price);
	//printf("sum_sqr_km : %Lf\n", tab->sum_sqr_km);
	//printf("sum_sqr_price : %Lf\n", tab->sum_sqr_price);
	//printf("sum_pdt : %Lf\n", tab->sum_pdt);
	printf(" Estimation mathématique (méthode des moindres carrés) : \n theta0 = %.2Lf   | theta1 = %.5Lf\n", tab->theta0 , tab->theta1);
	//printf("means:%Lf / %Lf\n", tab->mean_km, tab->mean_price);
	//printf("diffs:%Lf / %Lf\n", tab->diff_km[i], tab->diff_price[i]);
	//printf("sum_var_km = %Lf\n", tab->sum_var_km);
	//printf("sum_var_price = %Lf\n", tab->sum_var_price);
	//printf("sum_cov = %Lf\n", tab->sum_cov);
	//printf("sum_delta_price : %Lf\n", tab->sum_delta_price);
	printf(" correlation r = %.4Lg\n", tab->r);
	printf(" accuracy MAE = %.4Lg\n", tab->accur);
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
