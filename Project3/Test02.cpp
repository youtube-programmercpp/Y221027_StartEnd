#include <Windows.h>
#include <Y221027_Sub/Test01.h>
#include <iostream>
#pragma comment(lib, "Y221027_Sub")
int main()
{
	//�ʂ̏ꏊ�ɂ���Dll1 �����[�h����
	//Windows API
	if (const auto hModule = LoadLibraryW(LR"(Y:\source\youtube-programmercpp\Y221027_Sub\x64\Debug\Y221027_Sub.dll)")) {
		std::cout << Test() << std::endl;

		//�g���I�������A�����[�h
		FreeLibrary(hModule);
	}
}
