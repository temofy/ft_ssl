/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosquitovaper <mosquitovaper@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 13:28:31 by cheller           #+#    #+#             */
/*   Updated: 2021/01/06 21:30:59 by mosquitovap      ###   ########.fr       */
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
