#include "includes/minishell.h"
#include "libft/libft.h"

int main()
{
	int i = 2;
	int j = 0;
	
	
	
	((i != j) || printf("%d", 10));
//     char *str = ft_strdup("\"hhhhhppejkbf wehjfg \"");
//     int l = ft_strchr(str + 1, '\"') - str - 1;
//     printf("%d\n", l);
}

// static int	token_len(char const *s, int *index)
// {
// 	int		len;
// 	int		c;
// 	int		i;

// 	len = 0;
// 	i = 0;
// 	while (*(s + (*index)) && is_space(*(s + (*index))))
// 		(*index)++;
// 	if (is_operator(*(s + (*index))))
// 		return (token_len2(s));
// 	i = *index;
// 	while (*(s + i) && !is_space(*(s + i)) && !is_operator(*(s + i)))
// 	{
// 		if (*(s + i) == '\"' || *(s + i) == '\'')
// 		{
// 			(assign(&c, *(s + i)), assign(&i, i + 1));
// 			while (*(s + i) && *(s + i) != c)
// 				assign(&i, i + 1), assign(&len, len + 1);
// 			i++;
// 		}
// 		else
// 			assign(&i, i + 1), assign(&len, len + 1);
// 	}
// 	return (len);
// }
