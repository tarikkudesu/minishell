#include "includes/minishell.h"

void f() {system("leaks a.out");}

int main()
{
	atexit(f);
	char *str = getenv("PATH");
	printf("%s\n", str);
	free(str);
}