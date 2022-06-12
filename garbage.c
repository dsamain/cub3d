/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:13:43 by dsamain           #+#    #+#             */
/*   Updated: 2022/05/03 17:59:46 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_node	*g_new(void *new_elem)
{
	t_node	*out;

	out = malloc(sizeof(t_node));
	if (out)
	{
		out->next = NULL;
		out->elem = new_elem;
	}
	return (out);
}

int	g_push(t_node **garbage, void *elem)
{
	t_node	*new_node;

	new_node = g_new(elem);
	if (!new_node)
		return (0);
	if (!(*garbage))
	{
		*garbage = new_node;
		return (1);
	}
	new_node->next = *garbage;
	*garbage = new_node;
	return (1);
}

void	g_print(t_node *garbage)
{
	t_node	*cur;
	int		idx;

	idx = 0;
	if (!garbage)
		return ;
	cur = garbage;
	while (cur && cur->elem)
	{
		printf("%p ", cur->elem);
		cur = cur->next;
	}
	printf("\n");
}

void	clear_node(t_node *garbage)
{
	t_node *nxt;

	if (!garbage)
		return ;
	nxt = garbage->next;
	if (garbage->elem)
		free(garbage->elem);
	free(garbage);
	clear_node(nxt);
}

int	g_clear(t_node **garbage, char *msg)
{
	if (msg)
		printf("%s\n", msg);
	if (!garbage)
		return (0);
	printf("| clearing : ");
	//g_print(*garbage);
	clear_node(*garbage);
	*garbage = NULL;
	return (0);
}

void	*ft_malloc(t_data *data, int size)
{
	void	*out;

	out = malloc(size);
	if (!out || !g_push(&data->garbage, out))
	{
		g_clear(&data->garbage, "malloc error!");
		exit(1);
	}
	return (out);
}
