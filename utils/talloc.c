
#include "../includes/minishell.h"

t_heap	*heapnew(void *content)
{
	t_heap	*head;

	head = (t_heap *)malloc(sizeof(t_heap));
	if (!head)
		return (NULL);
	head->ptr = content;
	return (head);
}

void	heap_add_back(t_heap **lst, t_heap *new)
{
	t_heap	*temp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void	clearheap(t_heap **node)
{
	t_heap	*tmp;

	if (!node || !*node)
		return ;
	tmp = *node;
	while (node && *node)
	{
		free(tmp->ptr);
		tmp->ptr = NULL;
		tmp = tmp->next;
		free(*node);
		*node = tmp;
	}
}

void	*talloc(size_t __size)
{
	void	        *__ptr;
	t_heap      	*__node;
    static t_heap   *heap = NULL;

	__ptr = malloc(__size);
		// printf("pointer \033[32m%p\033[0m was allocated, size : \033[32m%ld\033[0m\n", __ptr, __size);
	if (__ptr == NULL)
		return (NULL);
	__node = heapnew(__ptr);
	if (!__node)
		return (free(__ptr), NULL);
	heap_add_back(&heap, __node);
	// if (D)
	return (__ptr);
}
