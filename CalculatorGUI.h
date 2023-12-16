#pragma once

#include "resource.h"
#include "framework.h" // indirectly including windows.h

#include <CommCtrl.h>
#include <objbase.h>

#include <string>
#include <stack>

class CalculatorGUI
{
public:
	CalculatorGUI(HINSTANCE instance);
	virtual ~CalculatorGUI();

	void CreateGUIWindow();
	HWND CreateButton(LPCWSTR text, int menuID, int x, int y, int w, int h);

	LRESULT CALLBACK ButtonClick(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT CALLBACK EqualClick(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) noexcept;

	void toPostfixExpression(std::wstring);
	float eveluatePostfixExpression(std::wstring);


private:
	bool decimalAlreadyAdded = false;
	bool divByZero;
	std::wstring* wstr;
	HINSTANCE g_instance;
	HWND hCalcWnd;
	HWND hEdit;
};
