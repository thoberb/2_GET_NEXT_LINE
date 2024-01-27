/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberthod <bberthod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 11:24:48 by bberthod          #+#    #+#             */
/*   Updated: 2023/01/13 13:02:59 by bberthod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// gcc get_next_line.c -D BUFFER_SIZE=42

int	is_it_the_end(char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if (c[i] == '\n')
			return (1);
		else
			i++;
	}
	return (0);
}

char	*free_save_rest(char *stash)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	while (stash[i] != '\n' && stash[i] != '\0')
		i++;
	while (stash[j + i])
		j++;
	new = malloc(sizeof(char) * (j + 1));
	if (!new)
		return (NULL);
	j = 0;
	while (stash[i++])
	{
		new[j] = stash[i];
		j++;
	}
	free(stash);
	new[j] = '\0';
	return (new);
}

char	*reading(int fd, char *c, char *stash)
{
	int		ret;

	ret = 0;
	while (ret >= 0)
	{
		ret = read(fd, c, BUFFER_SIZE);
		if (ret < 0)
			return (NULL);
		if (ret == 0)
			break ;
		c[ret] = '\0';
		stash = ft_strjoin(stash, c);
		if (is_it_the_end(stash) == 1 || ret == 0 || ret < BUFFER_SIZE)
			break ;
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	char		*c;
	static char	*stash;
	char		*line;

	if (fd < 0 || fd >= 1024)
		return (NULL);
	c = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!c)
		return (NULL);
	stash = reading(fd, c, stash);
	if (!stash)
		return (free(c), NULL);
	free(c);
	line = ft_strjoin_line(stash);
	if (!line)
		return (NULL);
	stash = free_save_rest(stash);
	if (line[0] == '\0')
		return (free(line), free(stash), NULL);
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*str;

// 	fd = open("fichier.txt", O_RDONLY);
// 	while (1)
// 	{
// 		str = get_next_line(fd);
// 		if (str == NULL)
// 			break ;
// 		printf("%s\n\n\n", str);
// 		free(str);
// 	}
// 	close(fd);
// }
