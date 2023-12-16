#include "CalculatorGUI.h"

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#define IDC_BUTTONCE                    1005
#define IDC_BUTTONC                     1006
#define IDC_BUTTONBKSP                  1007
#define IDC_BUTTONDIVIDE                1008
#define IDC_BUTTONSEVEN                 1009
#define IDC_BUTTONEIGHT                 1010
#define IDC_BUTTONNINE                  1011
#define IDC_BUTTONMULTIPLY              1012
#define IDC_BUTTONFOUR                  1013
#define IDC_BUTTONFIVE                  1014
#define IDC_BUTTONSIX                   1015
#define IDC_BUTTONMINUS                 1016
#define IDC_BUTTONONE                   1017
#define IDC_BUTTONTWO                   1018
#define IDC_BUTTONTHREE                 1019
#define IDC_BUTTONPLUS                  1020
#define IDC_BUTTONPLUSMINUS             1021
#define IDC_BUTTONZERO                  1022
#define IDC_BUTTONPOINT                 1023
#define IDC_BUTTONEQUALS                1024
#define IDC_EDIT                        1033

CalculatorGUI* ginst;

CalculatorGUI::CalculatorGUI(HINSTANCE instance) {
	g_instance = instance;
	hCalcWnd = hEdit = NULL;
	wstr = new std::wstring();
	divByZero = false;
}

CalculatorGUI::~CalculatorGUI() {
}

INT_PTR CALLBACK WndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	CalculatorGUI* inst;
	if (message == WM_CREATE)
	{
		inst = (CalculatorGUI*)((LPCREATESTRUCT)lParam)->lpCreateParams;
		//SetWindowLongPtr(hDlg, GWLP_USERDATA, PtrToUlong(inst));
		ginst = inst;
	}
	else
	{
		//inst = (CalculatorGUI*) UlongToPtr(GetWindowLongPtr(hDlg,GWLP_USERDATA));
		inst = ginst;
	}
	switch (message)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTONZERO:
		case IDC_BUTTONONE:
		case IDC_BUTTONTWO:
		case IDC_BUTTONTHREE:
		case IDC_BUTTONFOUR:
		case IDC_BUTTONFIVE:
		case IDC_BUTTONSIX:
		case IDC_BUTTONSEVEN:
		case IDC_BUTTONEIGHT:
		case IDC_BUTTONNINE:

		case IDC_BUTTONPLUS:
		case IDC_BUTTONMINUS:
		case IDC_BUTTONMULTIPLY:
		case IDC_BUTTONDIVIDE:

		case IDC_BUTTONCE:
		case IDC_BUTTONC:
		case IDC_BUTTONBKSP:

		case IDC_BUTTONPOINT:
		case IDC_BUTTONPLUSMINUS:

			inst->ButtonClick((HWND)lParam, message, wParam, lParam);
			break;
		case IDC_BUTTONEQUALS:
			inst->EqualClick((HWND)lParam, message, wParam, lParam);
			break;
		default:
			break;
		}
		break;
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hDlg, message, wParam, lParam);
	}
	return 0;
}

HWND CalculatorGUI::CreateButton(LPCWSTR text, int menuID, int x, int y, int w, int h) {
	HWND wnd =  CreateWindowEx(0, L"BUTTON", text, WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_BORDER, x , y , w, h, hCalcWnd, (HMENU) menuID, g_instance, NULL);
	//m_map->emplace(std::pair<int, HWND>(menuID, wnd));
	return wnd;
}

void CalculatorGUI::CreateGUIWindow() {

	// Register the window class
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = g_instance;
	wcex.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_ICONBIG));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"CALCCLASS";
	wcex.hIconSm = LoadIcon(NULL, MAKEINTRESOURCE(IDI_ICONSMALL));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, L"Window Registration Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
		return ;
	}

	

	hCalcWnd = CreateWindowEx(0, L"CALCCLASS", L"Calculator", 
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		100, 100, 300, 400, NULL, NULL, g_instance, this);

	SendMessage(hCalcWnd, WM_SETICON, IMAGE_ICON, (LPARAM)LoadIcon(g_instance, MAKEINTRESOURCE(IDI_ICONBIG)));
	
	hEdit = CreateWindowEx(0, L"EDIT", L"0", WS_CHILD|WS_VISIBLE|WS_BORDER|ES_RIGHT| ES_RIGHT | ES_AUTOHSCROLL | ES_READONLY | ES_NUMBER, 10, 10, 270, 30, hCalcWnd, (HMENU) IDC_EDIT, g_instance, nullptr);

	int x, y, h, w;
	x = 15;
	y = 50;
	h = w = 50;
	
	int buffer = 5;

	int i = 0;
	int j = 0;
	// Create Number Buttons
	CreateButton(L"CE", IDC_BUTTONCE, x, y + (h + buffer) * j, w, h);
	CreateButton(L"C", IDC_BUTTONC, x + (w + buffer) * ++i, y + (h + buffer) * j, w, h);
	CreateButton(L"BKSP", IDC_BUTTONBKSP, x + (w + buffer) * ++i, y + (h + buffer) * j, w, h);
	CreateButton(L"/", IDC_BUTTONDIVIDE, x + (w + buffer) * ++i, y + (h + buffer) * j, w, h);

	i = 0;
	j++;
	CreateButton(L"7", IDC_BUTTONSEVEN, x, y + (h + buffer) * j, w, h);
	CreateButton(L"8", IDC_BUTTONEIGHT, x + (w + buffer) * ++i, y + (h + buffer) * j, w, h);
	CreateButton(L"9", IDC_BUTTONNINE, x + (w + buffer) * ++i, y + (h + buffer) * j, w, h);
	CreateButton(L"x", IDC_BUTTONMULTIPLY, x + (w + buffer) * ++i, y + (h + buffer) * j, w, h);

	i = 0;
	j++;
	CreateButton(L"4", IDC_BUTTONFOUR, x, y + (h + buffer) * j, w, h);
	CreateButton(L"5", IDC_BUTTONFIVE, x + (w + buffer) * ++i, y + (h + buffer) * j, w, h);
	CreateButton(L"6", IDC_BUTTONSIX, x + (w + buffer) * ++i, y + (h + buffer) * j, w, h);
	CreateButton(L"-", IDC_BUTTONMINUS, x + (w + buffer) * ++i, y + (h + buffer) * j, w, h);

	i = 0;
	j++;
	CreateButton(L"1", IDC_BUTTONONE, x, y + (h + buffer) * j, w, h);
	CreateButton(L"2", IDC_BUTTONTWO, x + (w + buffer) * ++i, y + (h + buffer) * j, w, h);
	CreateButton(L"3", IDC_BUTTONTHREE, x + (w + buffer) * ++i, y + (h + buffer) * j, w, h);
	CreateButton(L"+", IDC_BUTTONPLUS, x + (w + buffer) * ++i, y + (h + buffer) * j, w, h);

	i = 0;
	j++;
	CreateButton(L"+/-", IDC_BUTTONPLUSMINUS, x, y + (h + buffer) * j, w, h);
	CreateButton(L"0", IDC_BUTTONZERO, x + (w + buffer) * ++i, y + (h + buffer) * j, w, h);
	CreateButton(L".", IDC_BUTTONPOINT, x + (w + buffer) * ++i, y + (h + buffer) * j, w, h);
	CreateButton(L"=", IDC_BUTTONEQUALS, x + (w + buffer) * ++i, y + (h + buffer) * j, w, h);

	ShowWindow(hCalcWnd, SW_SHOWDEFAULT);
	UpdateWindow(hCalcWnd);
	
}


LRESULT CALLBACK CalculatorGUI::ButtonClick(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) noexcept {

	if (LOWORD(wParam) == IDC_BUTTONC || LOWORD(wParam) == IDC_BUTTONCE)
	{
		SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)L"0");
		decimalAlreadyAdded = false;
		return 0;
	}
	else if (LOWORD(wParam) == IDC_BUTTONPOINT) {
		if (decimalAlreadyAdded)
		{
			return 0;
		}
		else {
			decimalAlreadyAdded = true;
		}
	}
	else if (LOWORD(wParam) == IDC_BUTTONPLUS || LOWORD(wParam) == IDC_BUTTONMINUS
		|| LOWORD(wParam) == IDC_BUTTONMULTIPLY || LOWORD(wParam) == IDC_BUTTONDIVIDE) {
		if (decimalAlreadyAdded)
		{
			decimalAlreadyAdded = false;
		}
	}


	// Get the button text
	int len = GetWindowTextLength(hWnd) + 1;
	WCHAR* buttonText = new WCHAR[len];
	GetWindowText(hWnd, buttonText, len);
	
	// Get the current text in Edit Control
	//len = GetWindowTextLength(hEdit) + 1;
	len = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
	WCHAR* currentText = nullptr;
	currentText = (WCHAR*)malloc(len);
	//GetWindowText(hEdit, currentText, len);
	int x = SendMessage(hEdit, WM_GETTEXT, len + 1, (LPARAM)currentText);

	

	//wcscat_s(currentText, (len+1),  buttonText);
	
	if (currentText != NULL)
	{
		if (lstrlen(currentText) == 1)
		{
			wstr->append(currentText[0] == L'0' ? L"" : currentText);
		}
		else {
			wstr->append(currentText);
		}
	}

	if (LOWORD(wParam) == IDC_BUTTONBKSP)
	{
		if (wstr->size() != 0)
		{
			wstr->pop_back();
		}
		SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM) (wstr->size() != 0 ? wstr->c_str() : L"0"));
		wstr->clear();
		return 0;
	}
	else if (LOWORD(wParam) == IDC_BUTTONPLUSMINUS)
	{
		bool done = false;
		for (std::wstring::iterator it = wstr->end() - 1; it != wstr->begin(); it--)
		{
			if (!isdigit(*it) && *it != L'.') {
				if (isdigit(*(it - 1)) || *(it - 1) == L'.')
				{
					it = wstr->insert(it + 1, L'-');
				}
				else {
					it = wstr->erase(it);
				}
				done = true;
				break;
			}
		}
		if (!done)
		{
			std::wstring::iterator it = wstr->begin();
			if (isdigit(*(it)) || *(it) == L'.')
			{
				it = wstr->insert(it, L'-');
			}
			else {
				it = wstr->erase(it);
			}
		}
		SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)(wstr->size() != 0 ? wstr->c_str() : L"0"));
		wstr->clear();
		return 0;
	}

	wstr->append(buttonText);

	// update the text in the edit control
	SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)(LPARAM)(wstr->size() != 0 ? wstr->c_str() : L"0"));

	// Cleanup
	wstr->clear();
	//free(currentText);
	//delete currentText;
	return 0;
}

// Function that handles equal button click event
LRESULT CALLBACK CalculatorGUI::EqualClick(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) noexcept {

	// Get the current text in Edit Control
	int len = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0) + 1;
	
	WCHAR* currentText = nullptr;
	currentText = (WCHAR*)malloc(len);
	//GetWindowText(hEdit, currentText, len);
	SendMessage(hEdit, WM_GETTEXT, len + 1, (LPARAM)currentText);

	// Evaluate the expression
	wstr->append(currentText);
	// Evaluation (actual calculation)

	toPostfixExpression(*wstr);
	divByZero = false;
	float f = eveluatePostfixExpression(*wstr);
	wstr->clear();
	wstr->append(std::to_wstring(f));

	// update the text in the edit control
	//SetWindowText(hEdit, currentText);
	if (divByZero)
	{
		wstr->clear();
		divByZero = false;
	}
	SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)(wstr->size() != 0 ? wstr->c_str() : L"0"));

	wstr->clear();
	// Cleanup

	return 0;
}

int prec(wchar_t c) {
	if (c == L'^')
	{
		return 3;
	}
	else if (c == L'/' || c == L'x')
	{
		return 2;
	}
	else if (c == L'+' || c == L'-')
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

void CalculatorGUI::toPostfixExpression(std::wstring infix) {
	std::wstring postfix;

	std::stack<wchar_t> st;
	for (int i = 0; i < infix.length(); i++)
	{
		wchar_t c = infix[i];
		
		if ((c >= L'0' && c <= L'9') || c == L'.')
		{
			postfix += c;
		}
		else if (c == L'(')
		{
			st.push(L'(');
		}
		else if (c == L')')
		{
			while (st.top() != L'(')
			{
				postfix += st.top();
				st.pop();
			}
			st.pop();
		}
		else
		{
			if (c == L'+' || c == L'-' || c == L'x' || c == L'/')
			{

				if (infix[i + 1] == L'-')
				{
					postfix += L'N';
					i++;
				}
			}

			while (!st.empty() && prec(infix[i]) <= prec(st.top()))
			{
				postfix += st.top();
				st.pop();
			}
			st.push(c);
			postfix += L' ';

		}
	}
	while (!st.empty())
	{
		postfix += st.top();
		st.pop();
	}

	wstr->clear();
	wstr->append(postfix);
}

float CalculatorGUI::eveluatePostfixExpression(std::wstring postfixx) {

	const wchar_t* postfix = wstr->c_str();
	std::stack<float> st;
	int i;
	
	for (i = 0; postfix[i]; i++)
	{
		if (postfix[i] == L' ')
			continue;
		else if (isdigit(postfix[i]) || postfix[i] == L'.' || postfix[i] == L'N')
		{
			bool neg = false;
			std::wstring ns;
			float num = 0.0f;
			if (postfix[i] == L'N')
			{
				neg = true;
				i++;
				i++;
			}

			//if (postfix[i] == L' ')i++;

			while (isdigit(postfix[i]) || postfix[i] == L'.')
			{
				ns += postfix[i];
				//num = num * 10 + (int)(postfix[i] - L'0');
				i++;
			}
			i--;
			if (ns.size() != 0)
			{
				num = std::stof(ns);
				if (neg)
				{
					num = -num;
				}
			}

			st.push(num);
		}
		else
		{
			float val1 = st.top();
			st.pop();

			if (st.empty())
			{
				return val1;
			}

			float val2 = st.top();
			st.pop();
			switch (postfix[i])
			{
			case L'+':
				st.push(val2 + val1);
				break;
			case L'-':
				st.push(val2 - val1);
				break;
			case L'x':
				st.push(val2 * val1);
				break;
			case L'/':
				if (val1 == 0) {
					divByZero = true;
					MessageBox(NULL, L"Cannot Divide By Zero", L"Stop!!!", MB_OK | MB_ICONHAND);
					return 0;
				}
				st.push(val2 / val1);
				break;
			default:
				break;
			}
		}
	}
	return st.top();
}


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	if (SUCCEEDED(CoInitialize(NULL)))
	{

		(new CalculatorGUI(hInstance))->CreateGUIWindow();
		
		MSG m;
		while (GetMessage(&m, NULL, 0, 0))
		{
			TranslateMessage(&m);
			DispatchMessage(&m);
		}

		CoUninitialize();
		return (int)m.wParam;
	}

	return 0;
}




