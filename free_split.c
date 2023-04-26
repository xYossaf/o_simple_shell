#include "main.h"
/**
 * free_split - frees
 * @arr: arr
 * Return: void
 */
void free_split(char **arr)
{
for (int i = 0; arr[i] != NULL; i++)
{
free(arr[i]);
}

free(arr);
}
