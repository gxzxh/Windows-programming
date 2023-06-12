#include <windows.h>
#include <stdio.h>
//���ձ�׼���������������������Ϣ
HANDLE g_hOutput = NULL;

//��Ӧ WM_CREATE ��Ϣ���Զ��庯��
void OnCreate(HWND hWnd, LPARAM lParam) {
	CREATESTRUCT * pcs = (CREATESTRUCT *)lParam;
	char *pzText = (char *)pcs->lpCreateParams;
	WriteConsole(g_hOutput, pzText, strlen(pzText), NULL, NULL);
	//������ť���Ӵ��ڣ�
	CreateWindowEx(0, "Button", "����", WS_CHILD | WS_VISIBLE | WS_BORDER,
	               0, 0, 100, 30, hWnd, NULL, 0, NULL);
}
//��Ӧ WM_SIZE ��Ϣ���Զ��庯��
void OnSize(HANDLE hWnd, LPARAM lParam) {
	short nWidth = LOWORD(lParam);
	short nHeight = HIWORD(lParam);
	char szText[256] = {0};
	sprintf(szText, "WM_SIZE����ȣ�%4d���߶ȣ�%4d\n", nWidth, nHeight);
	WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
}
//���ڴ��������Զ��壬������Ϣ)
LRESULT CALLBACK WinProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam) {
	switch (msgID) {
		case WM_SIZE:
			OnSize(hWnd, lParam);
			break;
		case WM_CREATE:
			OnCreate(hWnd, lParam);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_SYSCOMMAND:
			if (wParam == SC_CLOSE) {
				int nRet = MessageBox(hWnd, "�Ƿ��˳���", "ABC", MB_YESNO);
				if (nRet == IDNO)
					return 0;
			}
			break;
	}
	return DefWindowProc(hWnd, msgID, wParam, lParam);
}

//��ں���
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR ipCmdLine, int nCmdShow) {
	//���ӿ���̨���ڣ����������Ϣ
	AllocConsole();
	g_hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	//ע����������
	WNDCLASS wc = {0};
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
	char pszText[] = "������Ϣ\n";
	HWND hWnd = CreateWindowEx(0, "Main", "Window", WS_OVERLAPPEDWINDOW,
	                           100, 100, 500, 500, NULL, NULL, hInstance, pszText);
	//��ʾ����
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	//��Ϣѭ��
	MSG nMsg = {0};
	while (GetMessage(&nMsg, NULL, 0, 0)) {
		TranslateMessage(&nMsg);
		DispatchMessage(&nMsg);//����Ϣ�������ڴ�����
	}
	return 0;
}
