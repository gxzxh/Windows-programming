#include <windows.h>
//���ڴ��������Զ��壬������Ϣ)
LRESULT CALLBACK WinProc(HWND hWnd,UINT msgID, WPARAM wParam, LPARAM lParam){
	switch (msgID){
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	// ʹ��ϵͳ����������Ϣʣ����Ϣ
	return DefWindowProc(hWnd,msgID,wParam,lParam);
}

//��ں���
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR ipCmdLine, int nCmdShow){
	//ע�ᴰ����
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
	//��������
	HWND hWnd = CreateWindow("Main", "Window", WS_OVERLAPPEDWINDOW,
		100, 100, 1000, 500, NULL, NULL, hInstance, NULL);
	//��ʾ����
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	//��Ϣѭ��
	MSG nMsg = {0};
	while(GetMessage(&nMsg, NULL, 0, 0)){
		TranslateMessage(&nMsg);
		DispatchMessage(&nMsg);//����Ϣ����(����)���ڴ�����
	}
	return 0;
}
//���ڴ�����