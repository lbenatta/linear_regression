/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_regression_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenatta <lbenatta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:17:45 by lbenatta          #+#    #+#             */
/*   Updated: 2022/09/05 11:54:38 by lbenatta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	ft_atoi(const char *str)
{
	int			i;
	int			neg;
	long double	res;

	i = 0;
	neg = 0;
	res = 0;
	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\v') || \
	(str[i] == '\n') || (str[i] == '\r') || (str[i] == '\f'))
		i++;
	if ((str[i] == '+') || (str[i] == '-'))
	{
		if (str[i] == '-')
			neg++;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = ((res * 10) + (str[i] - '0'));
		i++;
	}
	if (neg % 2 != 0)
		res = -res;
	return (res);
}

//-----------------------ft_split------------------------------------
static int	ft_charset(char charset, char a)
{
	if (charset == a)
		return (1);
	else
		return (0);
}

static int	ft_word(char sep, char *str)
{
	int	i;
	int	wd;

	i = 0;
	wd = 0;
	while (ft_charset(sep, str[i]) == 1 && str[i])
		i++;
	while (str[i])
	{
		wd++;
		while (ft_charset(sep, str[i]) == 0 && str[i])
			i++;
		while (ft_charset(sep, str[i]) == 1 && str[i])
			i++;
	}
	return (wd);
}

static char	*ft_strdupi(const char *str, char sep)
{
	int		i;
	int		v;
	char	*res;

	i = 0;
	v = 0;
	while (str[i] && ft_charset(sep, str[i]) == 0)
		i++;
	res = (char *)malloc((i + 1) * sizeof (char));
	i = 0;
	if (!res)
		return (0);
	while (ft_charset(sep, str[i]) == 1 && str[i])
		i++;
	while (ft_charset(sep, str[i]) == 0 && str[i])
	{
		res[v] = str[i];
		i++;
		v++;
	}
	res[v] = '\0';
	return (res);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		v;
	char	**split;

	split = (char **)malloc((ft_word(c, ((char *)s)) + 1) * sizeof(char *));
	if (!split)
		return (0);
	v = 0;
	i = 0;
	while (ft_charset(c, s[i]) == 1 && s[i])
		i++;
	while (s[i])
	{
		split[v] = ft_strdupi(&s[i], c);
		if (!split[v])
			return (0);
		while (ft_charset(c, s[i]) == 0 && s[i])
			i++;
		while (ft_charset(c, s[i]) == 1 && s[i])
		{
			i++;
			v++;
		}
	}
	split[ft_word(c, ((char *)s))] = 0;
	return (split);
	free(split);
}

//--------------------------GNL.c ------------------------------------
void	free_null(char **ptr)
{
	if (*ptr != NULL)
	{
		free(*ptr);
		ptr = NULL;
	}
}

char	*join_line(int nl_position, char **buffer)
{
	char	*res;
	char	*tmp;

	tmp = NULL;
	if (nl_position <= 0)
	{
		if (**buffer == '\0')
		{
			free(*buffer);
			*buffer = NULL;
			return (NULL);
		}
		res = *buffer;
		*buffer = NULL;
		return (res);
	}
	tmp = ft_substr(*buffer, nl_position, BUFFER_SIZE);
	res = *buffer;
	res[nl_position] = 0;
	*buffer = tmp;
	return (res);
	free(tmp);
}

char	*read_line(int fd, char **buffer, char *read_return)
{
	ssize_t	mem_read;
	char	*tmp;
	char	*next_line;

	next_line = ft_strchr(*buffer, '\n');
	tmp = NULL;
	mem_read = 0;
	while (next_line == NULL)
	{
		mem_read = read(fd, read_return, BUFFER_SIZE);
		if (mem_read <= 0)
			return (join_line(mem_read, buffer));
		read_return[mem_read] = 0;
		tmp = ft_strjoin(*buffer, read_return);
		free_null(buffer);
		*buffer = tmp;
		next_line = ft_strchr(*buffer, '\n');
	}
	return (join_line(next_line - *buffer + 1, buffer));
}

char	*get_next_line(int fd)
{
	static char	*buffer[MAX_FD + 1];
	char		*read_return;
	char		*res;

	if (fd < 0 || fd > MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	read_return = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (read_return == NULL)
		return (NULL);
	if (!buffer[fd])
		buffer[fd] = ft_strdup("");
	res = read_line(fd, &buffer[fd], read_return);
	free_null(&read_return);
	return (res);
}

//-------------------------GNL_utils ---------------
char	*ft_strchr(const char *str, int n)
{
	char	*tmp;

	tmp = (char *) str;
	while (*tmp != (char)n)
	{
		if (*tmp == 0)
			return (NULL);
		tmp++;
	}
	return ((char *)tmp);
}

size_t	ft_strlen(const char *str)
{
	size_t	a;

	a = 0;
	while (str[a])
		a++;
	return (a);
}

char	*ft_strdup(const char *str)
{
	size_t	i;
	size_t	len;
	char	*s;

	len = ft_strlen(str) + 1;
	s = (char *)malloc(sizeof(char) * len);
	if (s == NULL)
		return (NULL);
	i = -1;
	while (++i < len)
		s[i] = str[i];
	return (s);
	free(s);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	srclen;
	char	*str;

	if (!s)
		return (NULL);
	srclen = ft_strlen(s);
	if (start > srclen)
		return (ft_strdup(""));
	if (start + len > srclen)
		len = srclen - start;
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s[start + i] && i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
	free(str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;
	size_t	size;

	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = (char *)malloc(sizeof(char) * size);
	if (!str)
		return (NULL);
	if (str != 0)
	{
		i = -1;
		while (s1[++i])
			str[i] = s1[i];
		j = -1;
		while (s2[++j])
			str[i + j] = s2[j];
		str[i + j] = '\0';
	}
	return (str);
	free(str);
}

int	ft_freesplit(char **strs)
{
	int	i;
	i = 0;

	while (strs[i])
	{
		free(strs[i]);
		strs[i] = NULL;
		i++;;
	}
	free(strs);
	strs = NULL;
	return (0);
}
