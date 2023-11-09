/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leon <leon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 10:04:47 by lgrimmei          #+#    #+#             */
/*   Updated: 2023/08/05 14:25:50 by leon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
#include "libft.h"
#include <bsd/string.h>

char	*ft_strnstr(const char	*big, const char *little, size_t len)
{
	int		i;
	int		j;
	int		lent;

	lent = len;
	i = 0;
	j = 0;
	if (little[0] == 0)
		return ((char *)&big[0]);
	while (big[i] && (lent < 0 || i < (int)len))
	{
		if (big[i] == little[j])
		{
			j++;
			if (little[j] == '\0')
				return ((char *)&big[i - j + 1]);
		}
		else
		{
			i = i - j;
			j = 0;
		}
		i++;
	}
	return (NULL);
}


int	main(void)
{
	char little[] = "abcd";
	char big[] = "aaabcabcd";
	printf("%s\n", ft_strnstr(big, little, 9));
	printf("%s\n", strnstr(big, little, 9));
} */
