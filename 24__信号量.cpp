#include <windows.h>
#include <stdio.h>
HANDLE g_hSemaphore = 0;
DWORD CALLBACK TestProc(LPVOID lpParameter){	
	while (true){
		WaitForSingleObject(g_hSemaphore, INFINITE); //µÈ´ýÐÅºÅÁ¿
		printf("++++++++\n");	
	}
	return 0;
}

int main(){
	g_hSemaphore=CreateSemaphore(NULL, 3, 10, NULL);
	DWORD nId = 0;
	HANDLE hThread = CreateThread(nullptr, 0, TestProc, NULL, 0, &nId);	
	getchar();
	ReleaseSemaphore(g_hSemaphore,5,NULL);
	WaitForSingleObject(hThread,INFINITE);
	CloseHandle(g_hSemaphore);
	return 0;
}

