/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenatta <lbenatta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:17:45 by lbenatta          #+#    #+#             */
/*   Updated: 2022/08/16 11:21:28 by lbenatta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

//# include "libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <ctype.h>
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <complex.h>
//# include "./mlx/mlx.h"
//# include "./minilibx-linux/mlx.h"
//# include <X11/keysym.h>
//# include <X11/X.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# ifndef MAX_FD
#  define MAX_FD 256
# endif

typedef struct t_tab
{
	long double	km[24];
	long double	price[24];
	long double	theta0;
	long double	theta1;
	long double	count;
// ---------------  estimate ------------------
	long double	sum_price;
	long double	sum_km;
	long double	mean_price;
	long double	mean_km;
	long double	sqr_price[24];
	long double	sqr_km[24];
	long double	sum_sqr_price;
	long double	sum_sqr_km;
	long double	pdt[24];
	long double	sum_pdt;
	long double	diff_km[24];
	long double	diff_price[24];
	long double	cov[24];
	long double	var_km[24];
	long double	var_price[24];
	long double	sum_cov;
	long double	sum_var_km;
	long double	sum_var_price;
	long double	r;
	long double	est_price[24];
	long double	delta_price[24];
	long double	sum_delta_price;
	long double	accur;
// -------------   train -----------------------
	int			i;
	int			j;
	int			num_iterations;
	long double	price_tr[24];
	long double	diff_price_tr[24];
	long double	prod_price_tr[24];
	long double	sqr_diff[24];
	long double	sum_sqr_diff;
	long double	sum_price_tr;
	long double	sum_diff_price_tr;
	long double	sum_sqr_diff_price_tr;
	long double	sum_prod_price_tr;
	long double	cost;
	long double	sum_cost;
	long double	diff_cost;
	long double	dtempt1;
	long double	dtempt0;
	long double	tempt0;
	long double	tempt1;
	long double	learning_rate;

}	t_tab;

int		ft_atoi(const char *str);

char	*get_next_line(int fd);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *str, int n);
char	*ft_strdup(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);

size_t	ft_strlen(const char *str);

void	test(t_tab *tab);
#endif
