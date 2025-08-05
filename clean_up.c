#include "minishell.h"

t_save	**save_add(void)
{
	static t_save	*save;

	if (save == NULL)
	{
		save = malloc(sizeof(t_save));
		if (!save)
			return (NULL);
		save->add = NULL;
		save->next = NULL;
	}
	return (&save);
}

void	*ft_malloc(size_t size)
{
	void	*add;
	t_save	*head;

	add = malloc(size);
	if (!add)
		return (0);
	head = malloc(sizeof(t_save));
	if (!head)
		return (0);
	head->add = add;
	head->next = *save_add();
	*save_add() = head;
	return (add);
}

int is_ft_malloc_ptr(void *ptr)
{
    t_save *head = *save_add();
    while (head)
	{
        if (head->add == ptr)
            return (1);
        head = head->next;
    }
    return (0);
}

void	ft_free_all(void)
{
	t_save	*head;
	t_save	*temp;
	int		i;

	i = 0;
	head = *save_add();
	while (head)
	{
		printf("===============================\n");
		temp = head;
		head = head->next;
		if (temp->add)
			 (temp->add);
        if(temp)
		    free(temp);
		i++;
	}
}