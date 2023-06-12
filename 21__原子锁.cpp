#include <iostream>
#include <windows.h>
using namespace std;
long g_value = 0;
DWORD CALLBACK TestProc( LPVOID pParam ) {
	for ( int i = 0; i < 1000000; i++ ) {
		InterlockedIncrement(&g_value);//++操作
		InterlockedDecrement(&g_value);//--操作
	}
	return 0;
}
int main() {
	DWORD nId = 0;
	HANDLE hThreads[2] = {0};
	hThreads[0] = CreateThread( NULL, 0, TestProc, nullptr, 0, &nId );
	hThreads[1] = CreateThread( NULL, 0, TestProc, nullptr, 0, &nId );
	WaitForMultipleObjects( 2, hThreads, true, INFINITE );
	cout << g_value << endl;
	cout << "结束！" << endl;
	return 0;
}
