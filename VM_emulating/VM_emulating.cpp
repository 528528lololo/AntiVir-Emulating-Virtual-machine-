#define WINVER 0x0501
#define _WIN32_WINNT 0x0501
#define _WIN32_WINDOWS 0x0501
#define _WIN32_IE 0x0600

#define MAX_LOADSTRING 100
#define COPYRIGHT_ADOBE_FUCKAV_RU 1
// VM_emulating.cpp: определяет точку входа для приложения.
//    ____                      _       _           
//   |  _ \            /\      | |     | |          
//	| |_) |_   _     /  \   __| | ___ | |__   ___  
//	|  _ <| | | |   / /\ \ / _` |/ _ \| '_ \ / _ \ 
//	| |_) | |_| |  / ____ \ (_| | (_) | |_) |  __/ 
//	|____/ \__, | /_/    \_\__,_|\___/|_.__/ \___| 
//	        __/ |                                  
//	        |___/                                   



#include "stdafx.h"
#include "VM_emulating.h"
#include <Shlwapi.h>
#include <shellapi.h>
#include <string>
#include <fstream>

// Глобальные переменные:
HINSTANCE hInst;								// текущий экземпляр
	// имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:

LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);



void Registry(void) // вписываем в автозапуск
{ 
	DWORD dwType = REG_SZ; 
	HKEY key; 

	LONG er = RegOpenKeyEx (HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",0,KEY_WRITE,&key); // открываем ключ
	if (er != 0) 
		er = RegCreateKeyEx (HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", NULL, NULL, REG_OPTION_NON_VOLATILE, KEY_SET_VALUE, NULL, &key, NULL);

	TCHAR pfad[MAX_PATH]; 
	GetModuleFileName(NULL,pfad,MAX_PATH); // получаем полний путь к нашей программы
	RegSetValueEx(key, "VM emulate", 0, REG_SZ, (LPBYTE)pfad, (wcslen((const wchar_t *)pfad) + 1) * sizeof (wchar_t)); //запись в реестр

	RegCloseKey(key); // закрываем ключ
}


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	
	char szPath[0x100], szFileName[0x100]; 
	
	GetModuleFileName(NULL, szPath, sizeof(szPath)); 



	if(GetTickCount() > 35000) {
	
		
	} 
	


DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, About);






 	// TODO: разместите код здесь.
	MSG msg;
	HACCEL hAccelTable;


	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_VM_EMULATING));

	// Цикл основного сообщения:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}




LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: добавьте любой код отрисовки...
		EndPaint(hWnd, &ps);
		break;
		
	case WM_DESTROY:
	

		PostQuitMessage(0);
		break;
	
	case WM_CLOSE: {
		int userReply = MessageBox(hWnd,  "Do you stop exe without stopping amulate?", "", MB_YESNO | MB_ICONQUESTION);
		if (IDYES == userReply)
			DestroyWindow(hWnd);
				   }
		break;
	
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

bool res = FALSE;
bool res2 = FALSE;
bool res3 = FALSE;
bool res4 = FALSE;

char szPath[MAX_PATH] = {0};
STARTUPINFO         si = {0}, si2 = {0}, si3 = {0};
PROCESS_INFORMATION pi = {0}, pi2 = {0}, pi3 = {0};

bool FileExists(LPCTSTR fname)
{
	WIN32_FIND_DATA wfd;
	HANDLE hFind = ::FindFirstFile(fname, &wfd);
	if (INVALID_HANDLE_VALUE != hFind)
	{
		// Если этого не сделать то произойдет утечка ресурсов
		::FindClose(hFind);
		return true;
	}
	return false;
}
// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;


	case WM_COMMAND:
		
		switch(LOWORD(wParam)) {
		case IDC_BUTTON1: {
			
			if (res == FALSE) {

			
				si.cb = sizeof(STARTUPINFO);
				
				CreateProcess(NULL, "VBoxService.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si2, &pi2);
					
				
					
					res = TRUE;
			}
			else
			{
				res = false;
					
				TerminateProcess(pi.hProcess,NO_ERROR);
					
			}
						  }
			break;


		case IDC_BUTTON2: {

			if (res2 == FALSE) {


				si2.cb = sizeof(STARTUPINFO);

				if (!CreateProcess(NULL, "SbieSvc.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) 
					MessageBox(NULL, "CreateProcess error", "", NULL);

				std::ofstream fout("SbieDll.dll"); // создаём объект класса ofstream для записи и связываем его с файлом cppstudio.txt
				fout << " "; // запись строки в файл
				fout.close(); // закрываем файл
				
				res2 = TRUE;
			
		

			} else
			{
				res2 = false;
				TerminateProcess(pi2.hProcess,NO_ERROR);
				remove("SbieDll.dll");
			}
						  }

			break;
		case IDC_BUTTON3: {

			if (res3 == FALSE) {


				si3.cb = sizeof(STARTUPINFO);

				CreateProcess(NULL, "vmtoolsd.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si3, &pi3);         
					

				res3 = TRUE;
			}
			else
			{
				res3 = false;
				TerminateProcess(pi3.hProcess,NO_ERROR);
			}
						  }

			break;
	


		case IDC_BUTTON4:
			ShellExecute( NULL, "open", "https://fuckav.ru/",NULL,NULL,SW_SHOW);

			break;
			case IDC_BUTTON5: {
				/*
				if (PathIsDirectory(L"C:\\Temp\\isautorun"))
				{
					MessageBox(NULL, L"Already startup", L"", MB_OK);
				} else {
				} */
					Registry(); 
					///CreateDirectory(L"C:\\Temp\\isautorun", NULL);
			//	}
							  }
							  break;
				case IDC_BUTTON7: {

					if (res4 == FALSE) {
					 std::ofstream fout("dbghelp.dll"); // создаём объект класса ofstream для записи и связываем его с файлом cppstudio.txt
					fout << " "; // запись строки в файл
					fout.close(); // закрываем файл
					res4 = TRUE;
					} else {
						remove("dbghelp.dll");
						res4 = FALSE;
					}
				}
		case IDCANCEL:
			TerminateProcess(pi.hProcess,NO_ERROR);
			TerminateProcess(pi2.hProcess,NO_ERROR);
			TerminateProcess(pi3.hProcess,NO_ERROR);
			remove("dbghelp.dll");
			remove("SbieDll.dll");
			EndDialog(hDlg, 0);
			PostQuitMessage(0);
			break;
		}
		break;
	
	}
	return (INT_PTR)FALSE;
}
