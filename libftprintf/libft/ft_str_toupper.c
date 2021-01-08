/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_toupper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 19:04:22 by cheller           #+#    #+#             */
/*   Updated: 2021/01/07 19:25:11 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_toupper(char *str)
{
	size_t	i;

	if (!str)
		return (NULL);
	i = -1;
	while (str[++i])
		str[i] = ft_toupper(str[i]);
	return (str);
}
