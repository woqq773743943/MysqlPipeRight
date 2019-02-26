#include <Windows.h>
#include <iostream>
#include <string>

using namespace std;

void invoke(string exe);

int main(int argc, char* argv[])
{
	//string exe = "C:\\Users\\DALAOCHEN\\Desktop\\mysql-5.7.10\\bld\\client\\Debug\\mysql.exe -uroot -proot";
	string exe = "hello.exe";
	invoke(exe);
	return 0;
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
		CloseHandle(pi.hThread);
		const int max = 20*1024;
		char buf[max] = { 0 };
		char input[max] = { 0 };
		DWORD dw;
		ReadFile(hOutReadPipe, buf, max - 1, &dw, NULL);
		cout << buf;
		memset(buf, 0, sizeof(buf));
		WriteFile(hInWritePipe, "show databases;\n", strlen("show databases;\n"), &dw, NULL);
		while(ReadFile(hOutReadPipe, buf, max - 1, &dw, NULL)){
			cout << buf;
			memset(buf, 0, sizeof(buf));
			fgets(input, max - 1, stdin);
			WriteFile(hInWritePipe, input, strlen(input), &dw, NULL);
			memset(input, 0, sizeof(input));
		}
		CloseHandle(pi.hProcess);

	}

	CloseHandle(hInReadPipe);
	CloseHandle(hInWritePipe);
	CloseHandle(hOutWritePipe);
	CloseHandle(hOutReadPipe);
}
