#include <windows.h>
#include "resource.h"

//窗口处理函数（自定义，处理消息)
LRESULT CALLBACK WinProc(HWND hWnd,UINT msgID, WPARAM wParam, LPARAM lParam){
	switch (msgID){
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd,msgID,wParam,lParam);
}
//入口函数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR ipCmdLine, int nCmdShow){
	//注册窗口类
	WNDCLASSEX wc;
	memset (& wc, 0, sizeof wc);								//将 wc 清零
	wc.cbSize = sizeof (WNDCLASSEX);							//变量所占字节数
	wc.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;			//窗口风格
	wc.hInstance = hInstance;									//当前进程实例句柄
	wc.lpszClassName = "Main";									//窗口类名
	wc.lpfnWndProc = WinProc;									//窗口处理函数
	wc.hbrBackground = GetSysColorBrush (COLOR_BTNHIGHLIGHT);	//窗口的背景
	if (!RegisterClassEx (& wc)) return 0;
	//使用字符串资源
	TCHAR szText[256]={0};
	LoadString(hInstance, IDS_WND, szText,256);
	HWND hWnd = CreateWindowEx(0, "Main", szText, WS_OVERLAPPEDWINDOW,
		100, 100, 500, 500, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	MSG nMsg = {0};
	while(GetMessage(&nMsg, NULL, 0, 0)){
		TranslateMessage(&nMsg);
		DispatchMessage(&nMsg);
	}
	return 0;
}