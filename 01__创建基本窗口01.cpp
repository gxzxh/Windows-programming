#include <windows.h>
//窗口处理函数（自定义，处理消息)
LRESULT CALLBACK WinProc(HWND hWnd,UINT msgID, WPARAM wParam, LPARAM lParam){
	switch (msgID){
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	// 使用系统函数处理消息剩余消息
	return DefWindowProc(hWnd,msgID,wParam,lParam);
}

//入口函数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR ipCmdLine, int nCmdShow){
	//注册窗口类
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
	RegisterClass(&wc);		//注册类
	//创建窗口
	HWND hWnd = CreateWindow("Main", "Window", WS_OVERLAPPEDWINDOW,
		100, 100, 1000, 500, NULL, NULL, hInstance, NULL);
	//显示窗口
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	//消息循环
	MSG nMsg = {0};
	while(GetMessage(&nMsg, NULL, 0, 0)){
		TranslateMessage(&nMsg);
		DispatchMessage(&nMsg);//将消息交给(调用)窗口处理函数
	}
	return 0;
}
//窗口处理函数