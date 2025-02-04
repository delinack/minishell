#include "minishell.h"

//int	count_substrings(char *str, char sep)
//{
//	int	i;
//	int	c;
//	int	in_sep;
//	int	single_quote;
//	int	double_quote;
//
//	i = -1;
//	c = 0;
//	in_sep = 0;
//	single_quote = 0;
//	double_quote = 0;
//	// s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'
//	while (str[i])
//	{
//		if (str[i] == '\'' && !double_quote)
//			single_quote = !single_quote;
//		else if (str[i] == '\"' && !single_quote)
//			double_quote = !double_quote;
//
//		i += 1;
//	}
//	return (c);
//}

int ft_cw(char const *s)
{
	int i;
	int cw;
	int	single_quote;
	int	double_quote;

	i = 0;
	cw = 0;
	single_quote = 0;
	double_quote = 0;
	while (s[i])
	{
		if (s[i] == '\'' && !double_quote)
		{
			single_quote = !single_quote;
			if (s[i - 1] != '\'' && !single_quote)
				cw++;
			i++;
			continue ;
		}
		else if (s[i] == '\"' && !single_quote)
		{
			double_quote = !double_quote;
			if (s[i - 1] != '\"' && !double_quote)
				cw++;
			i++;
			continue ;
		}
		if (double_quote || single_quote)
		{
			i++;
			continue ;
		}
		if (!ft_isspace(s[i]) && (!ft_isspace(s[i + 1]) || s[i + 1] == '\0'))
		{
			cw++;
		}
		i++;
	}
	return (cw);
}

int	*ft_count_size(const char *str, int *array_of_int, int cw)
{
	int	i;
	int	j;
	int	single_quote;
	int	double_quote;
	int	word_len;

	i = 0;
	j = -1;
	word_len = 0;
	single_quote = 0;
	double_quote = 0;
	array_of_int = malloc(sizeof(int) * cw);
	if (array_of_int == NULL)
		return (0);
	while (str[i])
	{
		if (str[i] == '\'' && !double_quote)
		{
			single_quote = !single_quote;
			i++;
			continue ;
		}
		else if (str[i] == '\"' && !single_quote)
		{
			double_quote = !double_quote;
			i++;
			continue ;
		}
		if (double_quote || single_quote)
		{
			i++;
			continue ;
		}
		if (!ft_isspace(str[i]))
			word_len++;
		if (!ft_isspace(str[i]) && (ft_isspace(str[i + 1]) || str[i + 1] == '\0'))
		{
			array_of_int[++j] = word_len;
			word_len = 0;
		}
		i++;
	}
	return (array_of_int);
}

char	**cmd_split(char *cmd)
{
	char	**a;
	int 	*array_of_int;
	int 	i;
	int		count_words;

	i = -1;
	count_words = ft_cw(cmd);
	a = malloc(sizeof(char *) * (count_words + 1));
	array_of_int = ft_count_size(cmd, array_of_int, count_words);
	while (++i < count_words)
		a[i] = malloc(sizeof(char) * (array_of_int[i] + 1));
 	return (a);
}