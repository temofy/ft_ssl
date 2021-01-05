
#include "libft.h"

void	ft_lstappend(t_list **alst, t_list *new)
{
    t_list  *tail;

    tail = (*alst);
	if (alst && new)
	{
        while (tail->next)
            tail = tail->next;
		tail->next = new;
	}
}