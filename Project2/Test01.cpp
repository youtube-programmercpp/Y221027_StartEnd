#include <stdio.h>
#include <iostream>
#include <stdlib.h>
int main()
{
	printf("Project2が動きました。\n");
	printf("******************************\n");
	int n;
	if (std::cin >> n)
		return n;
	else
		return EXIT_FAILURE;
}
