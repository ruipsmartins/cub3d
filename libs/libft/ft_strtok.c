#include "libft.h"

static char	*ft_find_next_token(char *str, const char *delim)
{
	while (*str && ft_strchr(delim, *str))
		str++;
	return (str);
}

static char	*ft_find_token_end(char *str, const char *delim)
{
	while (*str && !ft_strchr(delim, *str))
		str++;
	return (str);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*last;
	char		*token_start;
	char		*token_end;

	if (str == NULL)
		str = last;
	if (str == NULL)
		return (NULL);
	str = ft_find_next_token(str, delim);
	if (*str == '\0')
	{
		last = NULL;
		return (NULL);
	}
	token_start = str;
	token_end = ft_find_token_end(str, delim);
	if (*token_end == '\0')
		last = NULL;
	else
	{
		*token_end = '\0';
		last = token_end + 1;
	}
	return (token_start);
}