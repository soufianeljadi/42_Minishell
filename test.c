#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (!s)
		return (NULL);
	if (!len || start >= strlen(s))
		return (strdup(""));
	i = strlen(s) - start ;
	if (i > len)
		i = len;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (0);
	strlcpy(str, s + start, i + 1);
	return (str);
}

void sera_expander(char *s)
{
	int i = 0;
	char *tmp;
	printf("s = %s\n", s);
	while (s[i])
	{
        printf("hrfgjehrgjehrgjfhj\n");
      if (s[i] == '\'')
	  {
		  i++;
		  while (s[i] != '\'')
			  i++;
		tmp = ft_substr(s, 1, i - 1);
	  }
	  i++;			
	}
		printf("tmp = %s\n", tmp);
}

int main()
{
    sera_expander("hello 'world' 'hello' 'world'");
    return 0;
}
