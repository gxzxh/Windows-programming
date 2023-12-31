#include <windows.h>
#include <stdio.h>
//接收标准输出句柄，用于输出调试信息
HANDLE g_hOutput = NULL;

//响应 WM_CREATE 消息的自定义函数
void OnCreate(HWND hWnd, LPARAM lParam) {
	CREATESTRUCT * pcs = (CREATESTRUCT *)lParam;
	char *pzText = (char *)pcs->lpCreateParams;
	WriteConsole(g_hOutput, pzText, strlen(pzText), NULL, NULL);
	//创建按钮（子窗口）
	CreateWindowEx(0, "Button", "静心", WS_CHILD | WS_VISIBLE | WS_BORDER,
	               0, 0, 100, 30, hWnd, NULL, 0, NULL);
}
//响应 WM_SIZE 消息的自定义函数
void OnSize(HANDLE hWnd, LPARAM lParam) {
	short nWidth = LOWORD(lParam);
	short nHeight = HIWORD(lParam);
	char szText[256] = {0};
	sprintf(szText, "WM_SIZE：宽度：%4d，高度：%4d\n", nWidth, nHeight);
	WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
}
//窗口处理函数（自定义，处理消息)
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
				int nRet = MessageBox(hWnd, "是否退出？", "ABC", MB_YESNO);
				if (nRet == IDNO)
					return 0;
			}
			break;
	}
	return DefWindowProc(hWnd, msgID, wParam, lParam);
}

//入口函数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR ipCmdLine, int nCmdShow) {
	//增加控制台窗口，输出调试信息
	AllocConsole();
	g_hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	//注册主窗口类
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
	RegisterClass(&wc);		//注册类
	//创建主窗口
	char pszText[] = "附加信息\n";
	HWND hWnd = CreateWindowEx(0, "Main", "Window", WS_OVERLAPPEDWINDOW,
	                           100, 100, 500, 500, NULL, NULL, hInstance, pszText);
	//显示窗口
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	//消息循环
	MSG nMsg = {0};
	while (GetMessage(&nMsg, NULL, 0, 0)) {
		TranslateMessage(&nMsg);
		DispatchMessage(&nMsg);//将消息交给窗口处理函数
	}
	return 0;
}
