// C++サンプルプログラム：自己再起動 Copyright(C) 2022 https://www.youtube.com/@ProgrammerCpp
#include <Windows.h>
#include <string>

//無限再帰を避けるために追加のコマンドライン引数を設ける
static const wchar_t 再起動時固有コマンドライン引数[] = L" {E1B8B9E6-D75E-4797-9327-F91D08C5E5BE}";//自分自身を再起動する際の追加引き数（決して重複しない乱数）

//再起動コマンドラインクラス
class RestartCommandLine {
	LPCWSTR first     ; //コマンドラインの先頭
	LPCWSTR last      ; //コマンドラインの末尾（の次）
	LPCWSTR supposed  ; //再起動時固有コマンドライン引数が想定される位置
public:
	RestartCommandLine() noexcept
		: first   { GetCommandLineW() }
		, last    { &first[lstrlenW(first)] }
		, supposed{ last - (_countof(再起動時固有コマンドライン引数) - 1) }
	{
	}
	//再起動時固有コマンドライン引数を追加して返す
	std::wstring operator()() const
	{
		std::wstring 新たなコマンドライン;
		const auto 元の長さ     = last - first   ;
		const auto 追加分の長さ = last - supposed;
		新たなコマンドライン.resize(元の長さ + 追加分の長さ);
		std::copy(first                         , last                                         , &新たなコマンドライン[    0   ]);//元の分をコピー
		std::copy(再起動時固有コマンドライン引数, &再起動時固有コマンドライン引数[追加分の長さ], &新たなコマンドライン[元の長さ]);//追加分をコピー
		return 新たなコマンドライン;
	}
	//再起動前であれば true、再起動後であれば false を返す
	explicit operator bool() const noexcept
	{
		if (first < supposed && wmemcmp(supposed, 再起動時固有コマンドライン引数, last - supposed) == 0) {
			//再起動時固有コマンドライン引数が指定されている
			//当プロセスは再起動後である
			return false;
		}
		else {
			//再起動時固有コマンドライン引数は指定されていない
			//当プロセスは再起動前である
			return true;
		}
	}
};
int wmain()
{
	if (RestartCommandLine command_line{}) {
		//再起動前である
		//再起動時固有コマンドライン引数を追加して起動する
		STARTUPINFOW startupinfo;
		GetStartupInfoW(&startupinfo);
		PROCESS_INFORMATION procinfo;
		if (CreateProcessW
		( /*_In_opt_    LPCWSTR               lpApplicationName   */nullptr
		, /*_Inout_opt_ LPWSTR                lpCommandLine       */&command_line().front()//追加された引数を含むコマンドラインを与える
		, /*_In_opt_    LPSECURITY_ATTRIBUTES lpProcessAttributes */nullptr
		, /*_In_opt_    LPSECURITY_ATTRIBUTES lpThreadAttributes  */nullptr
		, /*_In_        BOOL                  bInheritHandles     */false
		, /*_In_        DWORD                 dwCreationFlags     */0
		, /*_In_opt_    LPVOID                lpEnvironment       */nullptr
		, /*_In_opt_    LPCWSTR               lpCurrentDirectory  */nullptr
		, /*_In_        LPSTARTUPINFOW        lpStartupInfo       */&startupinfo
		, /*_Out_       LPPROCESS_INFORMATION lpProcessInformation*/&procinfo
		)) {
			CloseHandle(procinfo.hThread);
			CloseHandle(procinfo.hProcess);
		}
	}
	else {
		//再起動後である
		//再起動後の処理をここに書く
	}
}
/*
https://detail.chiebukuro.yahoo.co.jp/qa/question_detail/q14270593699
1×3=さん

2022/11/6 0:26

1回答

こんにちは。C++についての質問です。
今、C++でコンソールアプリを作っているのですが、「自分自身を再起動する（新しい別のものを起動し、自分を終了する）」ということがしたいのですが、検索してもよく分かりませんでした。自分の知識不足ですが、どなたかわかる方教えていだたけないでしょうか。

C言語関連 | プログラミング・14閲覧・25
*/
