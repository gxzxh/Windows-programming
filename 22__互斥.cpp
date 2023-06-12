#include <windows.h>
#include <iostream>
#include <stdio.h>
HANDLE hMutex = nullptr;
DWORD WINAPI TestProc(LPVOID lpParameter){
	using namespace std;
	char *p=(char*)lpParameter;
	while(1){
		WaitForSingleObject(hMutex, INFINITE);//�Ⱥ򻥳�
		for (int i=0;i<strlen(p);i++){
			putchar(p[i]);
			Sleep(10);
		}
		putchar('\n');
		ReleaseMutex(hMutex);//�ͷŻ���
	}
	return 0;
}
int main(){
	char *szText1="********";
	char *szText2="��������";
	DWORD nId = 0;
	hMutex = CreateMutex(NULL, FALSE,NULL);	//��������
	HANDLE hThread01 = CreateThread(nullptr,0,TestProc,szText1,0,&nId);
	HANDLE hThread02 = CreateThread(nullptr,0,TestProc,szText2,0,&nId);
	getchar();
	CloseHandle(hMutex);	//�رջ���
	return 0;
}