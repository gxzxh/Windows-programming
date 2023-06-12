#include <windows.h>
#include<string.h>
#include<tchar.h>
#include<stdio.h>
#include<winuser.h>

//增加控制台窗口
HANDLE g_Output = NULL;
void OnLbut(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	char szText[256] = {0};
	sprintf(szText, "WM_CHAR 编码值：%llu, %d %d\n", wParam, LOWORD(lParam), HIWORD(lParam));
	sprintf(szText, "WM_CHAR 编码值：%llu, %d %d\n", wParam, LOWORD(lParam), HIWORD(lParam));
	WriteConsole(g_Output, szText, strlen(szText), NULL, NULL);
}

//窗口处理函数（自定义，处理消息)
LRESULT CALLBACK WinProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam) {
	switch (msgID) {
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_LBUTTONDOWN:
			OnLbut(hWnd, wParam, lParam);
			break;
	}
	return DefWindowProc(hWnd, msgID, wParam, lParam);
}
/* Win32 GUI程序的“main”函数：程序从这里开始执行 */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR ipCmdLine, int nCmdShow) {
	//增加控制台窗口
	AllocConsole();
	g_Output = GetStdHandle(STD_OUTPUT_HANDLE);
	//注册窗口类
	WNDCLASSEX wc;
	memset (& wc, 0, sizeof wc);						//将 wc 清零
	wc.cbSize = sizeof (WNDCLASSEX);					//变量所占字节数
	wc.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;	//窗口风格
	wc.hInstance = hInstance;							//当前进程实例句柄
	wc.lpszClassName = "Main";							//窗口类名
	wc.lpfnWndProc = WinProc;							//窗口处理函数
	wc.hbrBackground = GetSysColorBrush (COLOR_WINDOW);	//窗口的背景
	if (!RegisterClassEx (& wc)) return 0;
	//创建窗口
	HWND hWnd = CreateWindowEx(0, "Main", "Window", WS_OVERLAPPEDWINDOW,
	                           100, 100, 1000, 500, NULL, NULL, hInstance, NULL);
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
