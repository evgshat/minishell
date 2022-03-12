#include "minishell.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*tmp_s;

	tmp_s = (char *)s;
	i = 0;
	while (tmp_s[i] != 0)
	{
		if (tmp_s[i] == c)
			return (&tmp_s[i]);
		i++;
	}
	if (c == '\0')
		return (&tmp_s[i]);
	return (NULL);
}
