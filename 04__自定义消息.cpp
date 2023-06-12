#include <windows.h>
#include <stdio.h>
//���ձ�׼���������������������Ϣ
HANDLE g_hOutput = NULL;
#define WM_MYMESSAGE WM_USER + 100
//�����Զ�����Ϣ����
void OnMyMessage(HWND hWnd, WPARAM wParam, LPARAM lParam){
	char szText[256]={0};
	sprintf(szText, "%d %d\n", wParam, lParam);
	WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
}

//��Ӧ WM_CREAT ��Ϣ�ĺ���
void OnCreate(HWND hWnd, LPARAM lParam){
	CREATESTRUCT * pcs = (CREATESTRUCT *)lParam;
	char *pzText = (char *)pcs->lpCreateParams;
	WriteConsole(g_hOutput,pzText, strlen(pzText), NULL, NULL);
	//�����Զ�����Ϣ
	PostMessage(hWnd, WM_MYMESSAGE, 100, 200);
	//������ť���Ӵ��ڣ�
	CreateWindowEx(0, "Button", "����", WS_CHILD|WS_VISIBLE|WS_BORDER,
		0, 0, 100, 30, hWnd, NULL, 0, NULL);
}
//���ڴ��������Զ��壬������Ϣ)
LRESULT CALLBACK WinProc(HWND hWnd,UINT msgID, WPARAM wParam, LPARAM lParam){
	switch (msgID){
	case WM_MYMESSAGE:
		OnMyMessage(hWnd, wParam, lParam);
		break;
	case WM_CREATE:
		OnCreate(hWnd, lParam);
		break;
	case WM_DESTROY:		
		PostMessage(hWnd, WM_QUIT, 0, 0);
		break;
	}
	return DefWindowProc(hWnd, msgID, wParam, lParam);
}

//��ں���
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR ipCmdLine, int nCmdShow){
	//���ӿ���̨���ڣ����������Ϣ
	AllocConsole();
	g_hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	//ע����������
	WNDCLASS wc={0};
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hCursor = NULL;
	wc.hIcon = NULL;
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WinProc;
	wc.lpszClassName = "Main";
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);		//ע����
	//����������
	char *pszText = "������Ϣ\n";
	HWND hWnd = CreateWindowEx(0, "Main", "Window", WS_OVERLAPPEDWINDOW,
		100, 100, 500, 500, NULL, NULL, hInstance, pszText);
	//��ʾ����
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	//��Ϣѭ��
	MSG nMsg = {0};
	while(GetMessage(&nMsg, NULL, 0, 0)){
		TranslateMessage(&nMsg);
		DispatchMessage(&nMsg);//����Ϣ�������ڴ�����
	}
	return 0;
}