/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlogtenb <tlogtenb@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 20:04:13 by tlogtenb          #+#    #+#             */
/*   Updated: 2025/10/08 19:29:01 by tlogtenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strlcpy(char *dst, char *src, int size)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (src && src[ret])
		ret++;
	while (src && src[i] && i < size)
	{
		dst[i] = src[i];
		i++;
	}
	if (size > 0)
	{
		if (i == size)
			i--;
		dst[i] = '\0';
	}
	return (ret);
}

char	*ft_strdup(char *s)
{
	int		i;
	int		len;
	char	*d;

	i = 0;
	len = 0;
	if (!s)
		return (NULL);
	while (s[len])
		len++;
	d = malloc((len + 1) * sizeof(char));
	if (!d)
		return (NULL);
	while (s[i])
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	return (d);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ret;
	int		s1_size;
	int		s2_size;

	s1_size = 0;
	s2_size = 0;
	while (s1 && s1[s1_size])
		s1_size++;
	while (s2[s2_size])
		s2_size++;
	ret = malloc(s1_size + s2_size + 1);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s1, s1_size + 1);
	ft_strlcpy(ret + s1_size, s2, s2_size + 1);
	return (ret);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*ret;
	int		s_len;
	int		s_start_len;

	if (!s)
		return (NULL);
	s_len = 0;
	s_start_len = 0;
	while (s[s_len])
		s_len++;
	if (s_len < start)
	{
		start = s_len;
		len = 0;
	}
	while (s[s_start_len + start])
		s_start_len++;
	if ((s_start_len < len) && !(s_len < start))
		len = s_start_len;
	ret = malloc(len + 1);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s + start, len + 1);
	return (ret);
}
