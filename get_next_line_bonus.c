/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberthod <bberthod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 10:38:04 by bberthod          #+#    #+#             */
/*   Updated: 2023/01/13 13:05:10 by bberthod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*stash[FD_SIZE];
	char		*line;

	if (fd < 0 || fd >= 4096)
		return (NULL);
	c = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!c)
		return (NULL);
	stash[fd] = reading(fd, c, stash[fd]);
	if (!stash[fd])
		return (free(c), NULL);
	free(c);
	line = ft_strjoin_line(stash[fd]);
	if (!line)
		return (NULL);
	stash[fd] = free_save_rest(stash[fd]);
	if (line[0] == '\0')
		return (free(line), free(stash[fd]), NULL);
	return (line);
}

// int main()
// {
// 	int fd01, fd02, fd03;
// 	char *line = NULL;

// 	fd01 = open("test01.txt", O_RDONLY);
// 	fd02 = open("test02.txt", O_RDONLY);
// 	fd03 = open("test03.txt", O_RDONLY);

// 	//FD 01 first line
// 	printf("FD01 | First Line | FD return %s\n", get_next_line(fd01));
// 	free(line);

// 	//FD02 second line
// 	printf("FD02 | First Line | FD return %s\n", get_next_line(fd02));
// 	free(line);

// 	//FD03 third line
// 	printf("FD03 | First Line | FD return %s\n", get_next_line(fd03));
// 	free(line);

// 	//FD01 First Line
// 	printf("FD01 | Second Line | FD return %s\n", get_next_line(fd01));
// 	free(line);

// 	//FD03 Third Line
// 	printf("FD03 | Second Line | FD return %s\n", get_next_line(fd03));
// 	free(line);

// 	//FD03 Third Line
// 	printf("FD03 | Third Line | FD return %s\n", get_next_line(fd03));
// 	free(line);
// }
