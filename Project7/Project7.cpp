// Project7.cpp : コマンドライン実験C++サンプルプログラム：Copyright(C) 2022 https://www.youtube.com/@ProgrammerCpp
#include <Windows.h>
#include <iostream>
#include <array>
#include <string>

HANDLE CreateProcessA(_Inout_ LPSTR lpCommandLine)
{
	PROCESS_INFORMATION procInfo;
	if (CreateProcessA
	( /*_In_opt_    LPCSTR                lpApplicationName   */nullptr
	, /*_Inout_opt_ LPSTR                 lpCommandLine       */lpCommandLine
	, /*_In_opt_    LPSECURITY_ATTRIBUTES lpProcessAttributes */nullptr
	, /*_In_opt_    LPSECURITY_ATTRIBUTES lpThreadAttributes  */nullptr
	, /*_In_        BOOL                  bInheritHandles     */false
	, /*_In_        DWORD                 dwCreationFlags     */0
	, /*_In_opt_    LPVOID                lpEnvironment       */nullptr
	, /*_In_opt_    LPCSTR                lpCurrentDirectory  */nullptr
	, /*_In_        LPSTARTUPINFO         lpStartupInfo       */std::array<STARTUPINFOA, 1>
		{ /*DWORD   cb             ;*/sizeof(STARTUPINFOA)
		, /*LPWSTR  lpReserved     ;*/{}
		, /*LPWSTR  lpDesktop      ;*/{}
		, /*LPWSTR  lpTitle        ;*/{}
		, /*DWORD   dwX            ;*/{}
		, /*DWORD   dwY            ;*/{}
		, /*DWORD   dwXSize        ;*/{}
		, /*DWORD   dwYSize        ;*/{}
		, /*DWORD   dwXCountChars  ;*/{}
		, /*DWORD   dwYCountChars  ;*/{}
		, /*DWORD   dwFillAttribute;*/{}
		, /*DWORD   dwFlags        ;*/{}
		, /*WORD    wShowWindow    ;*/{}
		, /*WORD    cbReserved2    ;*/{}
		, /*LPBYTE  lpReserved2    ;*/{}
		, /*HANDLE  hStdInput      ;*/{}
		, /*HANDLE  hStdOutput     ;*/{}
		, /*HANDLE  hStdError      ;*/{}
		}.data()
	, /*_Out_       LPPROCESS_INFORMATION lpProcessInformation*/&procInfo
	)) {
		(void)CloseHandle(procInfo.hThread );
		return procInfo.hProcess;
	}
	else
		return nullptr;
}
int main()
{
	for (;;) {
		(std::cout << "コマンドライン：").flush();
		std::string command_line;
		if (std::getline(std::cin, command_line)) {
			if (const auto hProcess = CreateProcessA(&command_line.front())) {
				if (WaitForSingleObject(hProcess, INFINITE) == WAIT_OBJECT_0) {
					DWORD dwExitCode;
					if (GetExitCodeProcess(hProcess, &dwExitCode))
						std::cout << "終了コードは " << dwExitCode << " でした。\n";
					else
						std::cerr << "GetExitCodeProcess 関数でエラーが発生しました。\n";
				}
				else
					std::cerr << "WaitForSingleObject 関数でエラーが発生しました。\n";
				(void)CloseHandle(hProcess);
			}
			else
				std::cerr << "CreateProcessA 関数でエラーが発生しました。\n";
		}
		else
			break;
	}
}
