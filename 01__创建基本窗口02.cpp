#include <windows.h>
//���ڴ��������Զ��壬������Ϣ)
LRESULT CALLBACK WinProc(HWND hWnd,UINT msgID, WPARAM wParam, LPARAM lParam){
	switch (msgID){
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd,msgID,wParam,lParam);
}
//��ں���
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR ipCmdLine, int nCmdShow){
	//ע�ᴰ����
	WNDCLASSEX wc;
	memset (& wc, 0, sizeof wc);						//�� wc ����
	wc.cbSize = sizeof (WNDCLASSEX);					//������ռ�ֽ���
	wc.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;	//���ڷ��
	wc.hInstance = hInstance;							//��ǰ����ʵ�����
	wc.lpszClassName = "Main";							//��������
	wc.lpfnWndProc = WinProc;							//���ڴ�����
	wc.hbrBackground = GetSysColorBrush (COLOR_WINDOW);	//���ڵı���
	if (!RegisterClassEx (& wc)) return 0;
	//��������
	HWND hWnd = CreateWindowEx(0, "Main", "Window", WS_OVERLAPPEDWINDOW,
		100, 100, 1000, 500, NULL, NULL, hInstance, NULL);
	//��ʾ����
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	//��Ϣѭ��
	MSG nMsg = {0};
	while(GetMessage(&nMsg, NULL, 0, 0)){
		TranslateMessage(&nMsg);
		DispatchMessage(&nMsg);//����Ϣ�������ڴ�����
	}
	return 0;
}