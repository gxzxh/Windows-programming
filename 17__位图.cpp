#include <windows.h>
#include "resource.h"
HINSTANCE appInstance;
void OnPaint(HWND hwnd){
	PAINTSTRUCT ps={0};
	HDC hdc = BeginPaint(hwnd, &ps);//��ȡ��ͼ�豸���
	//����λͼ
	HBITMAP hBmp = LoadBitmap(appInstance,(char *)IDB_BITMAP1);
	//�����ڴ� DC
	HDC hMemdc = CreateCompatibleDC(hdc);
	//��λͼ�����ڴ� DC
	HGDIOBJ hOldBmp = SelectObject(hMemdc, hBmp);
	//1:1 ����
	//BitBlt(hdc, 0, 0, 48, 48, hMemdc, 0, 0, SRCCOPY);

	StretchBlt(hdc, 0, 0, 200, 200, hMemdc, 0, 0, 24, 24, SRCCOPY);
	// �ָ��ڴ� DC ��λͼ
	SelectObject(hMemdc, hOldBmp);
	//�ͷ�λͼ
	DeleteObject(hBmp);
	//�ͷ��ڴ�DC
	DeleteDC(hMemdc);
	EndPaint(hwnd,&ps);				//������ͼ���ͷž��
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {
	case WM_PAINT:
		OnPaint(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, Message, wParam, lParam);
		break;
	}
	return 0;
}

/* Win32 GUI����ġ�main����������������￪ʼִ�� */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {	
	appInstance = hInstance;
	WNDCLASSEX wc; HWND hwnd; MSG msg;

	memset(&wc, 0, sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);

	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszClassName = "WindowClass";

	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!",
			"Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}	
	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, "WindowClass", "Caption",
		WS_VISIBLE | WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		640, 480, NULL, NULL, hInstance, NULL);

	if (hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	while (GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
