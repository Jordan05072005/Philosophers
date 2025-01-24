/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:55:45 by jguaglio          #+#    #+#             */
/*   Updated: 2025/01/24 14:55:45 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size <= 0)
		return (ft_strlen(src));
	while (src[i] && i < (size - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

static int	strlen_char(char charset, char *str, int j)
{
	int	i;

	i = 0;
	while (str[i + j])
	{
		if (charset == str[i + j])
			return (i);
		i++;
	}
	return (i);
}

static int	ft_nbr_word(char *str, char charset)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if ((charset != str[i])
			&& (charset == str[i + 1] || str[i + 1] == '\0'))
			counter++;
		i++;
	}
	return (counter);
}

static void	free_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	**ft_split(char *s, char c)
{
	char	**str_final;
	int		i;
	int		i_m;

	i = 0;
	i_m = 0;
	str_final = malloc((ft_nbr_word(s, c) + 1) * sizeof(char *));
	if (str_final == NULL)
		return (NULL);
	while (s[i])
	{
		if (c != s[i])
		{
			str_final[i_m] = malloc((strlen_char(c, s, i) + 1) * sizeof(char));
			if (str_final[i_m] == NULL)
				return (free_str(str_final), NULL);
			ft_strlcpy(str_final[i_m++], &s[i], strlen_char(c, s, i) + 1);
			i += strlen_char(c, s, i);
		}
		else
			i++;
	}
	str_final[i_m] = 0;
	return (str_final);
}
