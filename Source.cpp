#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#pragma comment(lib, "d2d1")
#pragma comment(lib, "dwrite")

#include <windows.h>
#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>

TCHAR szClassName[] = TEXT("Window");

template<class Interface> inline void SafeRelease(Interface **ppInterfaceToRelease)
{
	if (*ppInterfaceToRelease != NULL)
	{
		(*ppInterfaceToRelease)->Release();
		(*ppInterfaceToRelease) = NULL;
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HWND hEdit;
	switch (msg)
	{
	case WM_CREATE:
		hEdit = CreateWindow(TEXT("EDIT"), 0, WS_VISIBLE | WS_CHILD | WS_VSCROLL | ES_MULTILINE | ES_READONLY, 0, 0, 0, 0, hWnd, 0, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		SendMessage(hEdit, EM_LIMITTEXT, 0, 0);
		PostMessage(hWnd, WM_COMMAND, IDOK, 0);
		break;
	case WM_SIZE:
		MoveWindow(hEdit, 0, 0, LOWORD(lParam), HIWORD(lParam), TRUE);
		break;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			SetWindowText(hEdit, 0);
			IDWriteFactory * factory;
			DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(factory), reinterpret_cast<IUnknown **>(&factory));
			IDWriteFontCollection * fonts;
			factory->GetSystemFontCollection(&fonts);
			UINT uFamilyCount = fonts->GetFontFamilyCount();
			for (UINT uFamilyIndex = 0; uFamilyIndex < uFamilyCount; ++uFamilyIndex)
			{
				IDWriteFontFamily * family;
				fonts->GetFontFamily(uFamilyIndex, &family);
				IDWriteLocalizedStrings * names;
				family->GetFamilyNames(&names);
				UINT uNameIndex;
				WCHAR locale[LOCALE_NAME_MAX_LENGTH];
				GetUserDefaultLocaleName(locale, _countof(locale));
				BOOL exists;
				names->FindLocaleName(locale, &uNameIndex, &exists);
				WCHAR name[64];
				names->GetString(exists ? uNameIndex : 0, name, _countof(name));
				SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)L"[");
				SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)name);
				SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)L"]\r\n");
				UINT uFontCount = family->GetFontCount();
				for (UINT i = 0; i < uFontCount; ++i)
				{
					IDWriteFont * font;
					family->GetFont(i, &font);
					switch (font->GetStyle())
					{
					case DWRITE_FONT_STYLE_NORMAL:
						SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)L"Normal");
						break;
					case DWRITE_FONT_STYLE_OBLIQUE:
						SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)L"Oblique");
						break;
					case DWRITE_FONT_STYLE_ITALIC:
						SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)L"Italic");
						break;
					}
					SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)L"-");
					switch (font->GetWeight())
					{
					case DWRITE_FONT_WEIGHT_THIN:
						SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)L"Thin");
						break;
					case DWRITE_FONT_WEIGHT_EXTRA_LIGHT:
						SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)L"ExtraLight");
						break;
					case DWRITE_FONT_WEIGHT_LIGHT:
						SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)L"Light");
						break;
					case DWRITE_FONT_WEIGHT_NORMAL:
						SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)L"Normal");
						break;
					case DWRITE_FONT_WEIGHT_MEDIUM:
						SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)L"Medium");
						break;
					case DWRITE_FONT_WEIGHT_DEMI_BOLD:
						SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)L"SemiBold");
						break;
					case DWRITE_FONT_WEIGHT_BOLD:
						SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)L"Bold");
						break;
					case DWRITE_FONT_WEIGHT_EXTRA_BOLD:
						SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)L"ExtraBold");
						break;
					case DWRITE_FONT_WEIGHT_BLACK:
						SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)L"Black");
						break;
					case DWRITE_FONT_WEIGHT_EXTRA_BLACK:
						SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)L"ExtraBlack");
						break;
					default:
						{
							TCHAR szWeight[16];
							wsprintf(szWeight, TEXT("%d"), font->GetWeight());
							SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)szWeight);
						}
						break;
					}
					SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)L"-");
					switch (font->GetStretch())
					{
					case 0:
						SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)L"Undefined");
						break;
					case 1:
						SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)L"UltraCondensed");
						break;
					case 2:
						SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)L"ExtraCondensed");
						break;
					case 3:
						SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)L"Condensed");
						break;
					case 4:
						SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)L"SemiCondensed");
						break;
					case 5:
						SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)L"Normal");
						break;
					case 6:
						SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)L"SemiExpanded");
						break;
					case 7:
						SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)L"Expanded");
						break;
					case 8:
						SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)L"ExtraExpanded");
						break;
					case 9:
						SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)L"UltraExpanded");
						break;
					}
					SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)L"\r\n");
					SafeRelease(&font);
				}
				SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)L"\r\n");
				SafeRelease(&names);
				SafeRelease(&family);
			}
			SafeRelease(&fonts);
			SafeRelease(&factory);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInst, LPSTR pCmdLine, int nCmdShow)
{
	MSG msg;
	WNDCLASS wndclass = {
		CS_HREDRAW | CS_VREDRAW,
		WndProc,
		0,
		0,
		hInstance,
		0,
		LoadCursor(0,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		0,
		szClassName
	};
	RegisterClass(&wndclass);
	HWND hWnd = CreateWindow(
		szClassName,
		TEXT("フォント一覧"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		0,
		CW_USEDEFAULT,
		0,
		0,
		0,
		hInstance,
		0
	);
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}
