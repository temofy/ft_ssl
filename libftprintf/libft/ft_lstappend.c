/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 19:11:30 by cheller           #+#    #+#             */
/*   Updated: 2021/01/07 19:12:34 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstappend(t_list **alst, t_list *new)
{
	t_list	*tail;

	tail = (*alst);
	if (alst && new)
	{
		while (tail->next)
			tail = tail->next;
		tail->next = new;
	}
}
