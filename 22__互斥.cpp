#include <windows.h>
#include <iostream>
#include <stdio.h>
HANDLE hMutex = nullptr;
DWORD WINAPI TestProc(LPVOID lpParameter){
	using namespace std;
	char *p=(char*)lpParameter;
	while(1){
		WaitForSingleObject(hMutex, INFINITE);//µÈºò»¥³â
		for (int i=0;i<strlen(p);i++){
			putchar(p[i]);
			Sleep(10);
		}
		putchar('\n');
		ReleaseMutex(hMutex);//ÊÍ·Å»¥³â
	}
	return 0;
}
int main(){
	char *szText1="********";
	char *szText2="¡ª¡ª¡ª¡ª";
	DWORD nId = 0;
	hMutex = CreateMutex(NULL, FALSE,NULL);	//´´½¨»¥³â
	HANDLE hThread01 = CreateThread(nullptr,0,TestProc,szText1,0,&nId);
	HANDLE hThread02 = CreateThread(nullptr,0,TestProc,szText2,0,&nId);
	getchar();
	CloseHandle(hMutex);	//¹Ø±Õ»¥³â
	return 0;
}