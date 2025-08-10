#include "minishell.h"


static t_save *g_save = NULL;

t_save **save_add(void)
{
    return (&g_save);
}

void *ft_malloc(size_t size)
{
    void    *add;
    t_save  *head;

    add = malloc(size);
    if (!add)
        return (NULL);
    
    head = malloc(sizeof(t_save));
    if (!head)
    {
        free(add);
        return (NULL);
    }
    
    head->add = add;
    head->next = g_save;
    g_save = head;
    
    return (add);
}

int is_malloc_ptr(void *ptr)
{
    t_save *head = g_save;
    
    while (head)
    {
        if (head->add == ptr)
            return (1);
        head = head->next;
    }
    return (0);
}

void ft_free_single(void *ptr)
{
    t_save *head = g_save;
    t_save *prev = NULL;
    
    if (!ptr)
        return;
    
    while (head)
    {
        if (head->add == ptr)
        {
            if (prev)
                prev->next = head->next;
            else
                g_save = head->next;
            
            free(head->add);
            free(head);
            return;
        }
        prev = head;
        head = head->next;
    }
    if (ptr)
        free(ptr);
}

void ft_free_2d_gc_array(char **arr)
{
    int i;
    
    if (!arr)
        return;
    
    i = 0;
    while (arr[i])
    {
        ft_free_single(arr[i]);
        i++;
    }
    ft_free_single(arr);
}

void ft_free_all(void)
{
    t_save *head = g_save;
    t_save *temp;

    while (head)
    {
        temp = head;
        head = head->next;
        if (temp->add)
        {
            free(temp->add);
            temp->add = NULL;  // Prevent double free
        }
        free(temp);
    }
    g_save = NULL;
}
// t_save	**save_add(void)
// {
// 	static t_save	*save;

// 	if (save == NULL)
// 	{
// 		save = malloc(sizeof(t_save));
// 		if (!save)
// 			return (NULL);
// 		save->add = NULL;
// 		save->next = NULL;
// 	}
// 	return (&save);
// }

// void	*ft_malloc(size_t size)
// {
//     void	*add;
//     t_save	*head;

//     add = malloc(size);
//     if (!add)
//         return (0);
//     head = malloc(sizeof(t_save));
//     if (!head)
//     {
//         free(add);
//         return (0);
//     }
//     head->add = add;
//     head->next = *save_add();
//     *save_add() = head;
//     return (add);
// }

// int is_malloc_ptr(void *ptr)
// {
//     t_save *head = *save_add();
//     while (head)
// 	{
//         if (head->add == ptr)
//             return (1);
//         head = head->next;
//     }
//     return (0);
// }

// void	ft_free_all(void)
// {
// 	t_save	*head;
// 	t_save	*temp;

// 	head = *save_add();
// 	*save_add() = NULL;
// 	while (head)
// 	{
// 		temp = head;
// 		head = head->next;
// 		if (temp->add)
// 			free(temp->add);
// 		free(temp);
// 	}
// }