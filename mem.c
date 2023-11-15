#include "shell.h"

/**
 * _bfree - frees a pointer and NULLs the address
 * @p: address of the pointer to be freed
 *
 * Return: 1 if freed, otherwise 0.
 */
int _bfree(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}

