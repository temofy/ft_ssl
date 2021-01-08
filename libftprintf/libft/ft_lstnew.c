/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 19:12:49 by cheller           #+#    #+#             */
/*   Updated: 2021/01/07 19:12:51 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*lstnew;

	if (!(lstnew = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (content == NULL)
	{
		lstnew->content = NULL;
		lstnew->content_size = 0;
	}
	else
	{
		if ((lstnew->content = malloc(content_size + 1)) == NULL)
		{
			free(lstnew);
			return (NULL);
		}
		ft_strncpy(lstnew->content, content, content_size);
		((char*)lstnew->content)[content_size] = 0;
		lstnew->content_size = content_size;
	}
	lstnew->next = NULL;
	return (lstnew);
}
