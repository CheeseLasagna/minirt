#include "libft.h"

int		lenun(unsigned int n)
{
	int length;

	length = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		length++;
		n = n / 10;
	}
	return (length);
}

char	*ft_itoaun(unsigned int n)
{
	char *ptr;
	int len;

	len = lenun(n);
	ptr = (char*)malloc(sizeof(char) * (len + 1));
	if (ptr == NULL)
		return (NULL);
	ptr[len--] = '\0';
	while (len >= 0)
	{
		ptr[len--] = n % 10 + 48;
		n = n / 10;
	}
	return (ptr);
}
