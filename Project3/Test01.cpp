#include <Windows.h>
#include <iostream>
#include "../Dll1/Test01.h"
int main()
{
	//Dll1 をロードする
	//Windows API
	if (const auto hModule = LoadLibraryW(L"Dll1")) {
		//関数ポインタ
		if (const auto pfnTest = reinterpret_cast<decltype(Test)*>(GetProcAddress(hModule, "Test"))) {
			std::cout << (*pfnTest)() << std::endl;
		}

		//使い終わったらアンロード
		FreeLibrary(hModule);
	}
}
