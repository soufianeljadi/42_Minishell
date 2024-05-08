#include <stdio.h>
#include <libc.h>
int is_single(char *str)
{
	int s;
	int d;
	int i;

	i = 0;
	s = d = 0;
	int j = 0;
	while (str[i])
	{
		if (str[i] == '\'' && d == 0)
			s = s + 1;
		else if (str[i] == '"' && s == 0)
			d = d + 1;
		if (d == 2)
			d = 0;
		if (s == 2)
			s = 0;
		if (str[i] == '$')
			break;
		i++;
	}
	if (s == 1)
		return (1);
	else
		return (0);

	return (0);
}
void f()
{
	system("leaks a.out");
}
int main()
{
	atexit(f);
	// char *str = "  \"'\"'$PWD'\"'\"   ";
	char *str = "  'PWD'   ";
	printf("%d\n", is_single(str));
	
	return (0);
}