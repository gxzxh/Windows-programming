#include <windows.h>
#include "resource.h"
void OnCommand(HWND hWnd,WPARAM wParam){
	switch (LOWORD(wParam)){
	case ID_NEW:
		MessageBox(hWnd,"�½��˵�����","�˵���Ϣ",MB_OK);
		break;
	default:
		break;
	}
}
/* �����ﴦ�����еĴ�����Ϣ���������룩 */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {/* ���٣��رգ�����ʱ�������߳��˳� */
	case WM_COMMAND:
		OnCommand(hwnd,wParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;				 /* ʹ��Ĭ�ϵ������������������������Ϣ */
	default:
		return DefWindowProc(hwnd, Message, wParam, lParam);
		break;
	}
	return 0;
}

/* Win32 GUI����ġ�main����������������￪ʼִ�� */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {	
	WNDCLASSEX wc;	/* �������ô��ڵ����� */
	HWND hwnd; 		/* ���ǵĴ��ھ����H����handle���������WND����windows�����ڣ��� */
	MSG msg; 		/* ������ʱ�����յ�����Ϣ */	
	/* �Ƚ������ṹȫ�����㣬Ȼ����������Ҫ���ֶ� */

	memset(&wc, 0, sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);

	/* COLOR_WINDOWS+1Ϊ��ɫ��Ctrl+���������COLOR_WINDOW���Բ鿴���Ķ��� */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); /* ���ر�׼ͼ�� */
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION); /* ���ر�׼ͼ�� */
	wc.lpszMenuName	= (char*)IDR_MENU1;

	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}	
	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, "WindowClass", "Caption", WS_VISIBLE | WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, /* x */ 
		CW_USEDEFAULT, /* y */
		640, /* ���ڿ�� */
		480, /* ���ڸ߶� */
		NULL, NULL, hInstance, NULL);

	if (hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	//���ؼ��ټ�����ȡ���
	HACCEL hAccel = LoadAccelerators(hInstance,(char *)IDR_ACCELERATOR1);

	while (GetMessage(&msg, NULL, 0, 0) > 0) {
		if (! TranslateAccelerator(hwnd,hAccel,&msg)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return msg.wParam;
}