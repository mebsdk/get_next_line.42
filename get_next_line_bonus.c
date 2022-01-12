/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-sadk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 12:24:34 by mes-sadk          #+#    #+#             */
/*   Updated: 2021/12/12 16:49:22 by mes-sadk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"

/***************************************\
*                FT_EOL                 *
\***************************************/
int	ft_eol(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		if (s[i++] == '\n')
			return (i);
	return (i);
}

/***************************************\
*          	 	FT_SANL 	            *
\***************************************/
void	ft_sanl(char *sr, int i)
{
	char	*p;

	p = sr + i;
	while (*p)
		*sr++ = *p++;
	while (sr < p)
		*sr++ = '\0';
}

/***************************************\
*             FT_STRDUP                 *
\***************************************/
char	*ft_strdup(const char *s)
{
	char	*p;
	int		i;

	i = 0;
	p = malloc(ft_strlen((char *)s) + 1);
	if (!p)
		return (NULL);
	while (*s)
		p[i++] = *s++;
	p[i] = '\0';
	return (p);
}

/***************************************\
*			GET_NEXT_LINE			    *
\***************************************/
char	*get_line(int fd)
{
	static char	sr_fd[1024][BUFFER_SIZE + 1];
	char		*join;
	int			x;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 256)
		return (NULL);
	join = ft_strdup(sr_fd[fd]);
	while (!ft_memchr(join, '\n', BUFFER_SIZE) && join)
	{
		x = read (fd, sr_fd[fd], BUFFER_SIZE);
		if ((x == -1 && !*sr_fd[fd]) || !(x || join) || !(x || *join))
			return (ft_del(join));
		sr_fd[fd][x] = '\0';
		join = ft_strjoin(join, sr_fd[fd]);
		if (x < BUFFER_SIZE || !join)
			break ;
	}
	if (!join || !*join)
		return (ft_del(join));
	ft_sanl(sr_fd[fd], ft_eol(sr_fd[fd]));
	return (ft_substr(join, 0, ft_eol(join)));
}

char	*get_next_line(int fd)
{
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024)
		return (NULL);
	return (get_line(fd));
}
