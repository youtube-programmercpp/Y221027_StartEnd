#include <Windows.h>
#include <string>
#include <iostream>
int main()
{
	std::wstring sCommandLine(L"Project2");

	STARTUPINFOW startupInfo
	{ /*DWORD   cb             ;*/sizeof startupInfo
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
	};
	PROCESS_INFORMATION procInfo;
	if (CreateProcessW
	( /*_In_opt_    LPCWSTR               lpApplicationName   */nullptr
	, /*_Inout_opt_ LPCWSTR               lpCommandLine       */&sCommandLine.front()
	, /*_In_opt_    LPSECURITY_ATTRIBUTES lpProcessAttributes */nullptr
	, /*_In_opt_    LPSECURITY_ATTRIBUTES lpThreadAttributes  */nullptr
	, /*_In_        BOOL                  bInheritHandles     */false
	, /*_In_        DWORD                 dwCreationFlags     */0
	, /*_In_opt_    LPVOID                lpEnvironment       */nullptr
	, /*_In_opt_    LPCWSTR               lpCurrentDirectory  */nullptr
	, /*_In_        LPSTARTUPINFOW        lpStartupInfo       */&startupInfo
	, /*_Out_       LPPROCESS_INFORMATION lpProcessInformation*/&procInfo
	)) {
		if (WaitForSingleObject(procInfo.hProcess, INFINITE) == WAIT_OBJECT_0) {
			DWORD dwExitCode;
			if (GetExitCodeProcess(procInfo.hProcess, &dwExitCode))
				std::cout << dwExitCode << std::endl;
		}
		CloseHandle(procInfo.hProcess);
		CloseHandle(procInfo.hThread );
	}
}
