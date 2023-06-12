#include <windows.h>
#include <iostream>
DWORD WINAPI TestProc(LPVOID lpParameter){
	using namespace std;
	char *p=(char*)lpParameter;
	for(int i=0; i<10;i++){
		cout << p << endl;
		Sleep(1000);
	}
	return 0;
}
int main(){
	char *szText1="11111111";
	char *szText2="22222222";
	DWORD nId = 0;
	HANDLE hThread01 = CreateThread(nullptr,0,TestProc,szText1,0,&nId);
	HANDLE hThread02 = CreateThread(nullptr,0,TestProc,szText2,0,&nId);
	HANDLE hThreads[]={hThread01, hThread02};
	//WaitForSingleObject(hThread01, INFINITE );
	//WaitForSingleObject(hThread02, INFINITE );
	WaitForMultipleObjects(2,hThreads,TRUE,INFINITE);
	return 0;
}

