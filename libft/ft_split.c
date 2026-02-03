/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmourey- <rmourey-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 18:24:47 by rmourey-          #+#    #+#             */
/*   Updated: 2026/01/19 14:44:20 by rmourey-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	size_t	i;
	size_t	in_word;
	int		count;

	i = 0;
	in_word = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (s[i] == c)
			in_word = 0;
		i++;
	}
	return (count);
}

static void	free_all(char **arr, size_t count)
{
	while (count--)
		free(arr[count]);
	free(arr);
}

static int	fill_result(char **result, char const *s, char c)
{
	size_t	i;
	size_t	start;
	size_t	word_idx;

	i = 0;
	word_idx = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			start = i;
			while (s[i] && s[i] != c)
				i++;
			result[word_idx] = ft_substr(s, start, i - start);
			if (!result[word_idx])
				return (free_all(result, word_idx), 0);
			word_idx++;
		}
	}
	result[word_idx] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**result;

	if (!s)
		return (NULL);
	result = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	if (!fill_result(result, s, c))
		return (NULL);
	return (result);
}
