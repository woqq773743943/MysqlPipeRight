#include <stdio.h>
#include <memory.h>
#include <windows.h>
#define LEN 1024

void main() {
	char buff[LEN];
	HANDLE std_out = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE std_in = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE std_error = GetStdHandle(STD_ERROR_HANDLE);
	CloseHandle(std_out);
	CloseHandle(std_in);
	CloseHandle(std_error);
	Sleep(20000);
	fputs("test\n", stdout);
	fflush(stdout);
	/*while (true) {
		fgets(buff, LEN - 1, stdin);
		if (feof(stdin)) {
			break;
		}
		fputs(buff, stdout);
		fflush(stdout);
	}*/

}
/*#include <iostream>

using namespace std;

void main() {
	cout << "test"<<endl;
	char data[1024];
	while (cin >> data) {
		cout << data << endl;
	}
}*/

/*#include <iostream>
#include <string>
#include <windows.h>
using namespace std;
int main()
{
	//setvbuf(stdout, NULL, _IONBF, NULL);
	//fprintf(stderr, "c\n");
	//cout << "c";
	DWORD size;
	WriteFile(GetStdHandle(STD_OUTPUT_HANDLE),"test",4,&size,NULL);
	//printf("c\n");
	getchar();
}*/