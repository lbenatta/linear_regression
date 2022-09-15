/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_regression_train.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenatta <lbenatta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:17:45 by lbenatta          #+#    #+#             */
/*   Updated: 2022/09/15 15:44:36 by lbenatta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

#define NUM_DATA 24

t_tab	*tab;

int main(void)
{
	int	f;
	char	*str;
	char	**strs;
	int	i;
	t_tab	*tab;

	f = open("data.csv", O_RDONLY);
	i = 0;
	tab = (t_tab *)malloc(sizeof(t_tab));
	memset(tab, 0, sizeof(t_tab));
	if(tab == 0)
	{
		printf("Échec de l'allocation\n");
		return(1);
	}
	str = get_next_line(f);
	free(str);
	str = get_next_line(f);
	while (str == NULL)
	{
		printf("Abs de donnees\n");
		return(1);
	}
	while (str != NULL)
	{
		strs = ft_split(str, ',');
		tab->km[i] = ft_atoi(strs[0]);
		tab->price[i] = ft_atoi(strs[1]);
			i++;
		free(str);
		ft_freesplit(strs);
		str = get_next_line(f);
	}
	free(str);
	
	int	j = 0;
	tab->learning_rate = 0.01;
	tab->count = i;
	tab->num_iterations = j;
	do
	{
		tab->sum_price_tr = 0;
		tab->sum_diff_price_tr = 0;
		tab->sum_sqr_diff = 0;
		tab->sum_prod_price_tr = 0;
		tab->cost = 0.0;
		tab->sum_cost = 0.0;
		tab->diff_cost = 0.0;
		tab->diff_price_tr[i] = 0;

		for (int i = 0 ; i < 24 ; i++)
		{
			tab->price_tr[i] = (tab->theta1 * (tab->km[i] / 10000)) + tab->theta0; // estimé
			tab->sum_price_tr =  (long double)tab->sum_price_tr + tab->price_tr[i];

			tab->diff_price_tr[i] = tab->price_tr[i] - (tab->price[i]/ 10000);
			tab->sum_diff_price_tr = (long double)tab->sum_diff_price_tr + tab->diff_price_tr[i]; // (estimé - reel)

			tab->sqr_diff[i] = (((tab->theta1 * (tab->km[i]/ 10000)) + tab->theta0) - (tab->price[i]/ 10000)) * (((tab->theta1 * (tab->km[i]/ 10000)) + tab->theta0) - (tab->price[i]/ 10000));
			tab->sum_sqr_diff = tab->sum_sqr_diff + tab->sqr_diff[i]; // pour le cost

			tab->prod_price_tr[i] = ((tab->theta1 * (tab->km[i]/ 10000) + tab->theta0) - (tab->price[i]/ 10000)) * (tab->km[i]/ 10000); // (estimé - reel) * km
			tab->sum_prod_price_tr = (long double)tab->sum_prod_price_tr + tab->prod_price_tr[i];

			tab->tempt0 = ((tab->learning_rate / NUM_DATA) * (long double)tab->sum_diff_price_tr);
			tab->tempt1 = ((tab->learning_rate / NUM_DATA) * (long double)tab->sum_prod_price_tr);

			tab->cost = (long double)tab->sum_sqr_diff / (2 * NUM_DATA);
			tab->sum_cost = (long double)tab->sum_cost + tab->cost;
		}
		if (i == 24)
		{
		 	tab->diff_cost = (long double)tab->sum_cost - tab->cost;
		 	tab->theta0 = tab->theta0 - tab->tempt0;
		 	tab->theta1 = tab->theta1 - tab->tempt1;
		 	tab->num_iterations++;
		 	printf("iterations: %d  | tempt0 : %Lf    | tempt1 : %Lf  | theta0 : %Lf    | theta1 : %Lf  |  sum_sqr_diff : %LF |\n " , tab->num_iterations, tab->tempt0, tab->tempt1, tab->theta0, tab->theta1, tab->sum_sqr_diff);
		 	//printf("cost :  %Lf | sum_cost : %Lf  | diff_cost :  %Lf | sum_diff_price_tr : %Lf  | sum_prod_price_tr : %Lf\n", tab->cost, tab->sum_cost, tab->diff_cost, tab->sum_diff_price_tr, tab->sum_prod_price_tr);
		}
	} while (((ABS(tab->tempt0) > 0.00000001) && (ABS(tab->tempt1) > 0.00000001)));
	//} while (tab->num_iterations <= 20);

	FILE	*fichier = NULL;
	fichier = fopen("res.txt", "a+");

	if (fichier != NULL)
	{
		printf("Estimation machine learning (méthode gradient descendant) : \nAvant entrainement : theta0 initial = 0  et theta1 initial  =  0 \n");
		printf("Après %d iterations : theta0 final =  %.2Lf   et theta1 final =  %.5Lf \n" , tab->num_iterations, (tab->theta0 * 10000), tab->theta1);
		fprintf(fichier,"\n \n Estimation Machine Learning (méthode du gradient descendant) :\n");
		fprintf(fichier, "Avant entrainement : theta0 initial = 0  et theta1 initial  =  0 \n");
		fprintf(fichier, "Après %d iterations : theta0 final =  %.2Lf  et theta1 final =  %.5Lf \n" , tab->num_iterations, (tab->theta0 * 10000), tab->theta1);
		fclose(fichier);
	}
	FILE	*fichier_ = NULL;
	fichier_ = fopen("theta.csv", "a+");
	if (fichier_ != NULL)
	{
		fprintf(fichier_, "%.2LF, %.5Lf\n", (tab->theta0 * 10000), tab->theta1);
		fclose(fichier_);
	}
	free (tab);
}
