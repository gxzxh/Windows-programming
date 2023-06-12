#include <windows.h>
#include "resource.h"

//窗口处理函数（自定义，处理消息)
LRESULT CALLBACK WinProc(HWND hWnd,UINT msgID, WPARAM wParam, LPARAM lParam){
	HINSTANCE hAppInst = GetModuleHandle(NULL);
	HMENU hMain = LoadMenu(hAppInst, (char *)IDR_MENU1);
	HMENU hPopup = GetSubMenu(hMain, 0);//获取子菜单
	switch (msgID){
	case WM_CONTEXTMENU://处理弹出式菜单
		TrackPopupMenu(hPopup,TPM_CENTERALIGN | TPM_VCENTERALIGN,
			LOWORD(lParam), HIWORD(lParam),0,hWnd,NULL);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd,msgID,wParam,lParam);
}
//入口函数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR ipCmdLine, int nCmdShow){
	//hAppInst = hInstance;
	//注册窗口类
	WNDCLASSEX wc;
	memset (& wc, 0, sizeof wc);						//将 wc 清零
	wc.cbSize = sizeof (WNDCLASSEX);					//变量所占字节数
	wc.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;	//窗口风格
	wc.hInstance = hInstance;							//当前进程实例句柄
	wc.lpszClassName = "Main";							//窗口类名
	wc.lpfnWndProc = WinProc;							//窗口处理函数
	wc.hbrBackground = GetSysColorBrush (COLOR_WINDOW);	//窗口的背景
	wc.lpszMenuName = (char *)IDR_MENU1;
	if (!RegisterClassEx (& wc)) return 0;
	//创建窗口
	HWND hWnd = CreateWindowEx(0, "Main", "Window", WS_OVERLAPPEDWINDOW,
		100, 100, 500, 500, NULL, NULL, hInstance, NULL);
	//显示窗口
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	//消息循环
	MSG nMsg = {0};
	while(GetMessage(&nMsg, NULL, 0, 0)){
		TranslateMessage(&nMsg);
		DispatchMessage(&nMsg);//将消息交给窗口处理函数
	}
	return 0;
}