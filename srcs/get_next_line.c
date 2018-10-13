/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebrucke <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 09:43:08 by sebrucke          #+#    #+#             */
/*   Updated: 2018/10/13 19:21:25 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

static t_fd_GNL	*get_struct(t_fd_GNL *head, int fd)
{
	t_fd_GNL*lst;

	if (head->fd == fd)
		return (head);
	if (head->next == NULL)
	{
		if (!(lst = (t_fd_GNL *)malloc(sizeof(t_fd_GNL))))
			return (0);
		lst->fd = fd;
		lst->content = ft_strnew(BUFF_SIZE);
		if (!lst->content)
			return (0);
		head->next = lst;
		lst->next = NULL;
		lst->ret_read = 1;
		return (lst);
	}
	else
		lst = get_struct(head->next, fd);
	return (lst);
}

static int		free_lst(t_fd_GNL *head, t_fd_GNL *lst)
{
	if (head->next != lst)
		free_lst(head->next, lst);
	else
	{
		head->next = lst->next;
		if (lst && lst->content)
		{
			ft_strdel(&lst->content);
		}
		if (lst)
		{
			free(lst);
		}
	}
	return (0);
}

static char		*ft_strdup_free(char *s1, char **s2)
{
	char	*str;

	if ((str = ft_strnew(ft_strlen(s1))))
		ft_strcpy(str, s1);
	if (s2 && *s2)
		ft_strdel(s2);
	return (str);
}

static t_fd_GNL	*while_read(t_fd_GNL *head, int fd)
{
	char		*tmp;
	char		buff[BUFF_SIZE + 1];
	t_fd_GNL	*lst;

	lst = get_struct(head, fd);
	while ((lst->ret_read = read(lst->fd, buff, BUFF_SIZE)))
	{
		buff[lst->ret_read] = '\0';
		tmp = ft_strjoin(lst->content, buff);
		if (!tmp)
			return (0);
		ft_strdel(&lst->content);
		lst->content = ft_strdup(tmp);
		if (!lst)
			return (0);
		ft_strdel(&tmp);
		if (ft_strchr(lst->content, '\n'))
			break ;
	}
	return (lst);
}

int				get_next_line(const int fd, char **line)
{
	static t_fd_GNL	head;
	t_fd_GNL		*lst;
	char			*aft_nb;

	head.fd = -1;
	aft_nb = 0;
	if (line && fd >= 0 && read(fd, aft_nb, 0) != -1)
	{
		if (!(lst = while_read(&head, fd)))
			return (-1);
		if (lst->content && ft_strlen(lst->content))
			aft_nb = ft_strchr(lst->content, '\n');
		if (aft_nb)
		{
			*line = ft_strsub(lst->content, 0, aft_nb - lst->content);
			lst->content = ft_strdup_free(aft_nb + 1, &lst->content);
		}
		else if (lst->content && ft_strlen(lst->content) > 0)
			*line = ft_strdup_free(lst->content, &lst->content);
		else
			return (free_lst(&head, lst));
		return (1);
	}
	return (-1);
}
