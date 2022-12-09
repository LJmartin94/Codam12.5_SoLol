/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/02 17:19:57 by limartin      #+#    #+#                 */
/*   Updated: 2022/12/02 19:25:45 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	if (str != NULL)
	{
		while (str[len])
			len++;
	}
	return (len);
}

void	ft_print_msg(const char *str)
{
	write(1, str, ft_strlen(str));
}

/* Checks whether two strings are equal,
 up to the length of the shortest string*/
int	ft_strcmp(const char *str1, const char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

void	*ft_safe_malloc(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (ret == NULL)
	{
		ft_print_msg("Malloc failure occurred.\n");
		exit(0);
	}
	return (ret);
}
