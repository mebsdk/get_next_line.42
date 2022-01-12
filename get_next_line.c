/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-sadk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 11:07:02 by mes-sadk          #+#    #+#             */
/*   Updated: 2021/12/12 16:49:26 by mes-sadk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

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
	static char	sr_fd[BUFFER_SIZE + 1];
	char		*join;
	int			x;

	join = ft_strdup(sr_fd);
	while (!ft_memchr(join, '\n', BUFFER_SIZE) && join)
	{
		x = read (fd, sr_fd, BUFFER_SIZE);
		if ((x == -1 && !*sr_fd) || !(x || join) || !(x || *join))
			return (ft_del(join));
		sr_fd[x] = '\0';
		join = ft_strjoin(join, sr_fd);
		if (x < BUFFER_SIZE || !join)
			break ;
	}
	if (!join || !*join)
		return (ft_del(join));
	ft_sanl(sr_fd, ft_eol(sr_fd));
	return (ft_substr(join, 0, ft_eol(join)));
}

char	*get_next_line(int fd)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	return (get_line(fd));
}
