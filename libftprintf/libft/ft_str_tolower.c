/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_tolower.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 18:15:18 by cheller           #+#    #+#             */
/*   Updated: 2021/01/08 18:44:00 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_tolower(char *str)
{
	size_t	i;

	if (!str)
		return (NULL);
	i = -1;
	while (str[++i])
		str[i] = ft_tolower(str[i]);
	return (str);
}
