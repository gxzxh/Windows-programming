#include <windows.h>
#include <stdio.h>
HANDLE g_hEvent = 0;
DWORD CALLBACK printProc(LPVOID lpParameter){
	while (true){
		WaitForSingleObject(g_hEvent,INFINITE); //�ȴ��¼��ź�
		ResetEvent(g_hEvent); //�����¼�ʱѡ���Զ���λ����Ҫ�����
		printf("++++++++\n");	
	}
	return 0;
}
DWORD CALLBACK CtrlProc(LPVOID lpParameter){
	while (true){
		Sleep(100);
		SetEvent(g_hEvent);
	}
	return 0;
}
int main(){
	DWORD nId = 0;
	HANDLE hThreads[2]={0};
	g_hEvent=CreateEvent(NULL, TRUE, FALSE, NULL);
	hThreads[0] = CreateThread(nullptr, 0, printProc, NULL, 0, &nId);
	hThreads[1] = CreateThread(nullptr, 0, CtrlProc, NULL, 0, &nId);
	WaitForMultipleObjects(2, hThreads, TRUE, INFINITE);
	CloseHandle(g_hEvent);
	return 0;
}