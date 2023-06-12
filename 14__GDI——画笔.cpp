#include <windows.h>
void OnPaint(HWND hwnd){
	PAINTSTRUCT ps={0};
	HDC hdc = BeginPaint(hwnd, &ps);				//获取绘图设备句柄
	HPEN hPen = CreatePen(PS_SOLID,4,RGB(255,0,0));	//创建画笔
	HGDIOBJ hOldPen = SelectObject(hdc, hPen);

	MoveToEx(hdc, 0, 0, NULL);					// 设置窗口当前点
	LineTo(hdc,640,445);						// 画线
	Rectangle(hdc,10,10,100,100);				// 矩形
	Ellipse(hdc,200,200,300,300);				// 绘制圆形

	SelectObject(hdc, hOldPen);	// 恢复画笔
	DeleteObject(hPen);			// 释放画笔
	
	EndPaint(hwnd,&ps);							//结束绘图，释放句柄
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

/* Win32 GUI程序的“main”函数：程序从这里开始执行 */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {	
	WNDCLASSEX wc;
	HWND hwnd;
	MSG msg;

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
