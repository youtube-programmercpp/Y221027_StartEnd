#include <Windows.h>
#include "../Dll1/Test01.h"
#pragma comment(lib, "Dll1")
#include <iostream>
int main()
{
	std::cout << Test() << std::endl;
}
