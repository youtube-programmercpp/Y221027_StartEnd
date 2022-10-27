#include <Windows.h>
#include <process.h>
#include <memory>

const std::unique_ptr<std::remove_pointer_t<HANDLE>, decltype(CloseHandle)*> hEvent
{ CreateEventW(nullptr, false, false, nullptr)
, CloseHandle
};

DWORD WINAPI ThreadProc(LPVOID lpThreadParameter)
{
	//UI スレッド
	MessageBoxA(nullptr, __FUNCTION__, "TEST", 0);
	(void)SetEvent(hEvent.get());
	return 0;
}

int main()
{
	if (const auto hThread = CreateThread
	( /*_In_opt_                  LPSECURITY_ATTRIBUTES  lpThreadAttributes */nullptr
	, /*_In_                      SIZE_T                 dwStackSize        */0
	, /*_In_                      LPTHREAD_START_ROUTINE lpStartAddress     */ThreadProc
	, /*_In_opt_ __drv_aliasesMem LPVOID                 lpParameter        */nullptr
	, /*_In_                      DWORD                  dwCreationFlags    */0
	, /*_Out_opt_                 LPDWORD                lpThreadId         */nullptr
	)) {
		(void)WaitForSingleObject(hEvent.get(), INFINITE);
		//スレッドの終了を待つ（必ず）
		(void)WaitForSingleObject(hThread, INFINITE);
		CloseHandle(hThread);
	}
	//ExitProcess が呼び出される
}
