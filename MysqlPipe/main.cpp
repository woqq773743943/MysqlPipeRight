#include <Windows.h>
#include <iostream>
#include <string>
#include <thread>
using namespace std;

void invoke(string exe);

int main(int argc, char* argv[])
{
	//string exe = "C:\\Users\\DALAOCHEN\\Desktop\\mysql-5.7.10\\bld\\client\\Debug\\mysql.exe -uroot -proot";
	string exe = "hello.exe";
	invoke(exe);
	return 0;
}

void thread_func(HANDLE hInReadPipe, HANDLE hInWritePipe, HANDLE hOutReadPipe, HANDLE hOutWritePipe) {
	Sleep(5000);
	CloseHandle(hInReadPipe);
	CloseHandle(hOutReadPipe);
	cout << "close hInReadPipe and hOutReadPipe"<< endl;
	Sleep(5000);
	CloseHandle(hInWritePipe);
	CloseHandle(hOutWritePipe);
	cout << "close hInWritePipe and hOutWritePipe" << endl;
}

void invoke(string exe)
{
	SECURITY_ATTRIBUTES saPipe;
	saPipe.nLength = sizeof(SECURITY_ATTRIBUTES);
	saPipe.lpSecurityDescriptor = NULL;
	saPipe.bInheritHandle = TRUE;

	HANDLE hInReadPipe, hInWritePipe;
	if (!CreatePipe(&hInReadPipe,
		&hInWritePipe,
		&saPipe,
		0))
		return;

	HANDLE hOutReadPipe, hOutWritePipe;
	if (!CreatePipe(&hOutReadPipe,
		&hOutWritePipe,
		&saPipe,
		0))
		return;
	PROCESS_INFORMATION pi;
	STARTUPINFOA si;
	memset(&si, 0, sizeof(si));
	si.hStdInput = hInReadPipe;
	si.hStdError = hOutWritePipe;
	si.hStdOutput = hOutWritePipe;
	si.dwFlags = STARTF_USESTDHANDLES;
	si.cb = sizeof(si);

	if (CreateProcessA(NULL, "hello.exe", NULL, NULL, true, CREATE_DEFAULT_ERROR_MODE
		, NULL, NULL, &si, &pi))
	{
		thread mythread(thread_func, hInReadPipe, hInWritePipe, hOutReadPipe, hOutWritePipe);
		//CloseHandle(pi.hThread); 
		//CloseHandle(pi.hProcess);
		const int max = 20*1024;
		char buf[max] = { 0 };
		char input[max] = { 0 };
		DWORD dw;
		ReadFile(hOutReadPipe, buf, max - 1, &dw, NULL);
		cout << buf;
		memset(buf, 0, sizeof(buf));
		mythread.join();
	}
}
