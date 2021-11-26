//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2020 Media Design School
//
// File Name	:	Main.cpp
// Description	:	Main Implementation File
// Author		:	William Inman
// Mail			:	William.inman@mediadesign.school.nz
//

#define WIN32_LEAN_AND_MEA
#define WINDOW_CLASS_NAME L"WINCLASS1"

// Non-Local Includes
#include <windows.h>   // Include all the windows headers.
#include <windowsx.h>  // Include useful macros.
#include "utils.h"
#include "resource.h"

// Local Includes
#include "CMatrix4.h"
#include "CQuaternion.h"
#include "CGaussianElimination.h"
#include "CSlerp.h"
#include "CTransformation.h"

void MakeWindow(HWND& hwnd, HINSTANCE& _hInstance);
void InitHWND(WNDCLASSEX& winclass, HINSTANCE& _hInstance);

void SetupModelessDBoxes(HWND& hwnd, HINSTANCE& _hInstance);

void Update(MSG& msg);

void TranslateAndDispatchMessage(MSG& msg);

//MatrixDlgProc Functions
bool ProcessMatrixAInput(HWND& _hwnd, WPARAM& _wparam);
bool ProcessMatrixBInput(HWND& _hwnd, WPARAM& _wparam);
bool ProcessMatrixAdditionInput(HWND& _hwnd, WPARAM& _wparam);
bool ProcessMatrixMinusInput(HWND& _hwnd, WPARAM& _wparam);
bool ProcessMatrixMultiplyInput(HWND& _hwnd, WPARAM& _wparam);
bool ProcessMatrixInverseMultiplyInput(HWND& _hwnd, WPARAM& _wparam);
bool ProcessMatrixBToIdentity(HWND& _hwnd, WPARAM& _wparam);
bool ProcessMatrixBTranspose(HWND& _hwnd, WPARAM& _wparam);
bool ProcessMatrixATranspose(HWND& _hwnd, WPARAM& _wparam);
bool ProcessMatrixAToIdentity(HWND& _hwnd, WPARAM& _wparam);
bool ProcessMatrixBDeterminant(HWND& _hwnd, WPARAM& _wparam);
bool ProcessMatrixADeterminant(HWND& _hwnd, WPARAM& _wparam);
bool ProcessMatrixBInverse(HWND& _hwnd, WPARAM& _wparam);
bool ProcessMatrixAInverse(HWND& _hwnd, WPARAM& _wparam);
bool ProcessMatrixScalarMultiplication(HWND& _hwnd, WPARAM& _wparam);

void WriteResultantMatrix(HWND& _hwnd, WPARAM& _wparam);
void WriteBMatrix(HWND& _hwnd, WPARAM& _wparam);
void WriteAMatrix(HWND& _hwnd, WPARAM& _wparam);

//QuaternionDlgProc Functions
bool ProcessQuaternionAInput(HWND& _hwnd, WPARAM& _wparam);
bool ProcessQuaternionBInput(HWND& _hwnd, WPARAM& _wparam);
bool ProcessQuaternionAdditionInput(HWND& _hwnd, WPARAM& _wparam);
bool ProcessQuaternionMinusInput(HWND& _hwnd, WPARAM& _wparam);
bool ProcessQuaternionInverseMinusInput(HWND& _hwnd, WPARAM& _wparam);
bool ProcessQuaternionMultiplyInput(HWND& _hwnd, WPARAM& _wparam);
bool ProcessQuaternionInverseMultiplyInput(HWND& _hwnd, WPARAM& _wparam);
bool ProcessQuaternionDotProduct(HWND& _hwnd, WPARAM& _wparam);
bool ProcessQuaternionAConjugate(HWND& _hwnd, WPARAM& _wparam);
bool ProcessQuaternionBConjugate(HWND& _hwnd, WPARAM& _wparam);
bool ProcessQuaternionAMagnitude(HWND& _hwnd, WPARAM& _wparam);
bool ProcessQuaternionBMagnitude(HWND& _hwnd, WPARAM& _wparam);
bool ProcessQuaternionAInverse(HWND& _hwnd, WPARAM& _wparam);
bool ProcessQuaternionBInverse(HWND& _hwnd, WPARAM& _wparam);
bool ProcessQuaternionAScalarMultiplication(HWND& _hwnd, WPARAM& _wparam);
bool ProcessQuaternionBScalarMultiplication(HWND& _hwnd, WPARAM& _wparam);

void WriteResultantQuaternion(HWND& _hwnd, WPARAM& _wparam);
void WriteBQuaternion(HWND& _hwnd, WPARAM& _wparam);
void WriteAQuaternion(HWND& _hwnd, WPARAM& _wparam);

//Gaussian Elimination Functions
bool ProcessGEInput(HWND& _hwnd, WPARAM& _wparam);
bool ProcessGEMultiplyInput(HWND& _hwnd, WPARAM& _wparam);
bool ProcessGESwapInput(HWND& _hwnd, WPARAM& _wparam);
bool ProcessGEAdditionInput(HWND& _hwnd, WPARAM& _wparam);
void CheckEchelonForm(HWND& _hwnd);

void WriteGEValues(HWND& _hwnd, WPARAM& _wparam);

//Slerp Functions
bool ProcessQuaternionASlerpInput(HWND& _hwnd, WPARAM& _wparam);
bool ProcessQuaternionBSlerpInput(HWND& _hwnd, WPARAM& _wparam);
bool ProcessQuaternionResultantSlerpInput(HWND& _hwnd, WPARAM& _wparam);

bool ProcessSlerpInput(HWND& _hwnd, WPARAM& _wparam);
bool ProcessInducedMatrixAInput(HWND& _hwnd, WPARAM& _wparam);
bool ProcessInducedMatrixBInput(HWND& _hwnd, WPARAM& _wparam);
bool ProcessInducedSlerpMatrixInput(HWND& _hwnd, WPARAM& _wparam);

void WriteQuaternionResultantSlerp(HWND& _hwnd, WPARAM& _wparam);
void WriteResultantSlerpMatrix(HWND& _hwnd, WPARAM& _wparam);

//Transformation Functions
bool ProcessResultantTransformationMatrixInput(HWND& _hwnd, WPARAM& _wparam);

bool ProcessScaleTransformationInput(HWND& _hwnd, WPARAM& _wparam);
bool ProcessTranslateTransformationInput(HWND& _hwnd, WPARAM& _wparam);
bool ProcessRotateTransformationInput(HWND& _hwnd, WPARAM& _wparam);
bool ProcessProjectTransformationInput(HWND& _hwnd, WPARAM& _wparam);

void WriteResultantTransformationMatrix(HWND& _hwnd, WPARAM& _wparam);

//Windows
HMENU g_hMenu;
HWND g_hDlgMatrix, g_hDlgTransformation, g_hDlgGaussian, g_hDlgQuaternion, g_hDlgSLERP;

// Data Used
CMatrix4 mat4A, mat4B, mat4Result;
CQuaternion quatA, quatB, quatResult;
CGaussianElimination geMatrix;

LRESULT CALLBACK WindowProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam)
{
	// This is the main message handler of the system.
	PAINTSTRUCT ps; // Used in WM_PAINT.
	HDC hdc;        // Handle to a device context.

	switch (_msg)
	{
	case WM_CREATE:
	{
		// Do initialization stuff here.

		// Return Success.
		return (0);
	}
	break;

	case WM_PAINT:
	{
		// Simply validate the window.
		hdc = BeginPaint(_hwnd, &ps);

		// You would do all your painting here...
		EndPaint(_hwnd, &ps);

		// Return Success.
		return (0);
	}
	break;

	case WM_COMMAND:
	{
		switch (LOWORD(_wparam))
		{
		case ID_EXIT:
		{
			PostQuitMessage(0);
			break;
		}
		case ID_CALCULATOR_MATRIX:
		{
			ShowWindow(g_hDlgMatrix, SW_SHOWNORMAL);
			mat4A.SetToZero();
			mat4B.SetToZero();
			mat4Result.SetToZero();
			break;
		}
		case ID_CALCULATOR_TRANSFORMATION:
		{
			ShowWindow(g_hDlgTransformation, SW_SHOWNORMAL);
			mat4Result.SetToIdentity();
			break;
		}
		case ID_CALCULATOR_GAUSSIAN:
		{
			ShowWindow(g_hDlgGaussian, SW_SHOWNORMAL);
			geMatrix.SetToZero();
			break;
		}
		case ID_CALCULATOR_QUATERNION:
		{
			ShowWindow(g_hDlgQuaternion, SW_SHOWNORMAL);
			quatA.SetToZero();
			quatB.SetToZero();
			quatResult.SetToZero();
			break;
		}
		case ID_CALCULATOR_SLERP:
		{
			ShowWindow(g_hDlgSLERP, SW_SHOWNORMAL);
			quatA.SetToZero();
			quatB.SetToZero();
			quatResult.SetToZero();
			mat4Result.SetToZero();
			break;
		}
		}

		return(0);
	}
	break;

	case WM_DESTROY:
	{
		// Kill the application, this sends a WM_QUIT message.
		PostQuitMessage(0);

		// Return success.
		return (0);
	}
	break;
	} 
	 
	//
	// Return
	return (DefWindowProc(_hwnd, _msg, _wparam, _lparam));
}

//
// CALCULATORS
//
BOOL CALLBACK MatrixDlgProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam)
{
	switch (_msg)
	{
	case WM_COMMAND:
	{
		//Process Input Fields
		if (ProcessMatrixAInput(_hwnd, _wparam)) {}
		else if (ProcessMatrixBInput(_hwnd, _wparam)) {}

		//Process Operations
		if (ProcessMatrixAdditionInput(_hwnd, _wparam)) {}
		else if (ProcessMatrixMinusInput(_hwnd, _wparam)) {}
		else if (ProcessMatrixMultiplyInput(_hwnd, _wparam)) {}
		else if (ProcessMatrixInverseMultiplyInput(_hwnd, _wparam)) {}
		else if (ProcessMatrixBToIdentity(_hwnd, _wparam)) {}
		else if (ProcessMatrixBTranspose(_hwnd, _wparam)) {}
		else if (ProcessMatrixATranspose(_hwnd, _wparam)) {}
		else if (ProcessMatrixAToIdentity(_hwnd, _wparam)) {}
		else if (ProcessMatrixBDeterminant(_hwnd, _wparam)) {}
		else if (ProcessMatrixADeterminant(_hwnd, _wparam)) {}
		else if (ProcessMatrixBInverse(_hwnd, _wparam)) {}
		else if (ProcessMatrixAInverse(_hwnd, _wparam)) {}
		else if (ProcessMatrixScalarMultiplication(_hwnd, _wparam)) {}

		return TRUE;
	}
	//case WM_ENABLE:
	//{
	//	int i = 0;
	//}
	case WM_CLOSE:
	{
		ShowWindow(_hwnd, SW_HIDE);

		return TRUE;
	}
	}

	return FALSE;
}
BOOL CALLBACK TransformationDlgProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam)
{
	switch (_msg)
	{
	case WM_COMMAND:
	{
		//Process Input Fields
		if (ProcessResultantTransformationMatrixInput(_hwnd, _wparam)) {};

		//Process Operations
		if (ProcessScaleTransformationInput(_hwnd, _wparam)) {}
		else if (ProcessTranslateTransformationInput(_hwnd, _wparam)) {}
		else if (ProcessRotateTransformationInput(_hwnd, _wparam)) {}
		else if (ProcessProjectTransformationInput(_hwnd, _wparam)) {}

		return TRUE;
	}
	case WM_CLOSE:
	{
		ShowWindow(_hwnd, SW_HIDE);
		return TRUE;
	}
	}
	return FALSE;
}
BOOL CALLBACK GaussianDlgProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam)
{
	switch (_msg)
	{
	case WM_COMMAND:
	{
		//Process Input Fields
		ProcessGEInput(_hwnd, _wparam);
	
		//Process Operations
		if (ProcessGEAdditionInput(_hwnd, _wparam)) {}
		else if (ProcessGESwapInput(_hwnd, _wparam)) {}
		else if (ProcessGEMultiplyInput(_hwnd, _wparam)) {}
	
		return TRUE;
	}
	case WM_CLOSE:
	{
		ShowWindow(_hwnd, SW_HIDE);
		return TRUE;
	}
	}
	return FALSE;
}
BOOL CALLBACK QuaternionDlgProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam)
{
	switch (_msg)
	{
	case WM_COMMAND:
	{
		//Process Input Fields
		if (ProcessQuaternionAInput(_hwnd, _wparam)) {}
		else if (ProcessQuaternionBInput(_hwnd, _wparam)) {}
	
		//Process Operations
		if (ProcessQuaternionAdditionInput(_hwnd, _wparam)) {}
		else if (ProcessQuaternionMinusInput(_hwnd, _wparam)) {}
		else if (ProcessQuaternionInverseMinusInput(_hwnd, _wparam)) {}
		else if (ProcessQuaternionMultiplyInput(_hwnd, _wparam)) {}
		else if (ProcessQuaternionInverseMultiplyInput(_hwnd, _wparam)) {}
		else if (ProcessQuaternionDotProduct(_hwnd, _wparam)) {}
		else if (ProcessQuaternionAConjugate(_hwnd, _wparam)) {}
		else if (ProcessQuaternionBConjugate(_hwnd, _wparam)) {}
		else if (ProcessQuaternionAMagnitude(_hwnd, _wparam)) {}
		else if (ProcessQuaternionBMagnitude(_hwnd, _wparam)) {}
		else if (ProcessQuaternionAInverse(_hwnd, _wparam)) {}
		else if (ProcessQuaternionBInverse(_hwnd, _wparam)) {}
		else if (ProcessQuaternionAScalarMultiplication(_hwnd, _wparam)) {}
		else if (ProcessQuaternionBScalarMultiplication(_hwnd, _wparam)) {}
	
		return TRUE;
	}
	case WM_CLOSE:
	{
		ShowWindow(_hwnd, SW_HIDE);
	
		return TRUE;
	}
	}
	return FALSE;
}
BOOL CALLBACK SLERPDlgProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam)	
{
	switch (_msg)
	{
	case WM_COMMAND:
	{
		//Process Input Fields
		if (ProcessQuaternionASlerpInput(_hwnd, _wparam)) {}
		else if (ProcessQuaternionBSlerpInput(_hwnd, _wparam)) {}
		else if (ProcessQuaternionResultantSlerpInput(_hwnd, _wparam)) {}

		//Process Operations
		if (ProcessSlerpInput(_hwnd, _wparam)) {}
		else if (ProcessInducedMatrixAInput(_hwnd, _wparam)) {}
		else if (ProcessInducedMatrixBInput(_hwnd, _wparam)) {}
		else if (ProcessInducedSlerpMatrixInput(_hwnd, _wparam)) {}

		return TRUE;
	}
	case WM_CLOSE:
	{
		ShowWindow(_hwnd, SW_HIDE);
		return TRUE;
	}
	}
	return FALSE;
}
//0

//
// int Main() Equivilent
//
int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdLine, int _nCmdShow)
{
	WNDCLASSEX winclass; // This will hold the class we create.
	HWND hwnd;           // Generic window handle.
	MSG msg;             // Generic message.

	InitHWND(winclass, _hInstance);

	// Register the window class
	if (!RegisterClassEx(&winclass))
	{
		return (0);
	}

	//Load the Menu
	g_hMenu = LoadMenu(_hInstance, MAKEINTRESOURCE(IDR_MENU1));

	MakeWindow(hwnd, _hInstance);

	if (!(hwnd))
	{
		return (0);
	}

	//Create the modeless dialog boxes for the calculators
	//Matrix Calculator
	SetupModelessDBoxes(hwnd, _hInstance);

	//
	// Update
	Update(msg);

	//
	// Return Main
	return (static_cast<int>(msg.wParam));
}

void InitHWND(WNDCLASSEX& winclass, HINSTANCE& _hInstance)
{
	winclass.cbSize = sizeof(WNDCLASSEX);
	winclass.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc = WindowProc;
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = _hInstance;
	winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground =
		static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	winclass.lpszMenuName = NULL;
	winclass.lpszClassName = WINDOW_CLASS_NAME;
	winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
}

void SetupModelessDBoxes(HWND& hwnd, HINSTANCE& _hInstance)
{
	g_hDlgMatrix = CreateDialog(_hInstance, MAKEINTRESOURCE(IDD_DialogMatrix), hwnd, (DLGPROC)MatrixDlgProc);
	g_hDlgTransformation = CreateDialog(_hInstance, MAKEINTRESOURCE(IDD_DialogTransformations), hwnd, (DLGPROC)TransformationDlgProc);
	g_hDlgGaussian = CreateDialog(_hInstance, MAKEINTRESOURCE(IDD_DialogGaussian), hwnd, (DLGPROC)GaussianDlgProc);
	g_hDlgQuaternion = CreateDialog(_hInstance, MAKEINTRESOURCE(IDD_DialogQuaternion), hwnd, (DLGPROC)QuaternionDlgProc);
	g_hDlgSLERP = CreateDialog(_hInstance, MAKEINTRESOURCE(IDD_DialogSLERP), hwnd, (DLGPROC)SLERPDlgProc);
}

void MakeWindow(HWND& hwnd, HINSTANCE& _hInstance)
{
	// Create Window
	hwnd = CreateWindowEx(NULL,    // Extended style.
		   WINDOW_CLASS_NAME,      // Class.
		   L"Matrix Calculator Bundle",   // Title.
		   WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		   0, 0,                   // Initial x,y.
		   400, 100,               // Initial width, height.
		   NULL,                   // Handle to parent.
		   g_hMenu,                // Handle to menu.
		   _hInstance,             // Instance of this application.
		   NULL);                  // Extra creation parameters.
}

//
// Main Update Implementation
//
void Update(MSG& msg)
{
	while (true)
	{
		// Test if there is a message in queue, if so get it.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// Test For Quit
			if (msg.message == WM_QUIT)
			{
				break;
			}

			TranslateAndDispatchMessage(msg);
		}
	}
}

void TranslateAndDispatchMessage(MSG& msg)
{
	if ((g_hDlgMatrix == 0 && g_hDlgTransformation == 0 &&
		g_hDlgGaussian == 0 && g_hDlgQuaternion == 0 && g_hDlgSLERP == 0) ||
		(!IsDialogMessage(g_hDlgMatrix, &msg) &&
			!IsDialogMessage(g_hDlgTransformation, &msg) &&
			!IsDialogMessage(g_hDlgGaussian, &msg) &&
			!IsDialogMessage(g_hDlgQuaternion, &msg) &&
			!IsDialogMessage(g_hDlgSLERP, &msg)))
	{
		// Translate any accelerator keys.
		TranslateMessage(&msg);
		// Send the message to the window proc.
		DispatchMessage(&msg);
	}
}

bool ProcessMatrixAInput(HWND& _hwnd, WPARAM& _wparam)
{
	switch ((LOWORD(_wparam)))
	{
	case IDC_EDIT_A11:
	{
		mat4A(0, 0) = ReadFromEditBox(_hwnd, IDC_EDIT_A11);
		return TRUE;
	}
	case IDC_EDIT_A12:
	{
		mat4A(0, 1) = ReadFromEditBox(_hwnd, IDC_EDIT_A12);
		return TRUE;
	}
	case IDC_EDIT_A13:
	{
		mat4A(0, 2) = ReadFromEditBox(_hwnd, IDC_EDIT_A13);
		return TRUE;
	}
	case IDC_EDIT_A14:
	{
		mat4A(0, 3) = ReadFromEditBox(_hwnd, IDC_EDIT_A14);
		return TRUE;
	}
	case IDC_EDIT_A21:
	{
		mat4A(1, 0) = ReadFromEditBox(_hwnd, IDC_EDIT_A21);
		return TRUE;
	}
	case IDC_EDIT_A22:
	{
		mat4A(1, 1) = ReadFromEditBox(_hwnd, IDC_EDIT_A22);
		return TRUE;
	}
	case IDC_EDIT_A23:
	{
		mat4A(1, 2) = ReadFromEditBox(_hwnd, IDC_EDIT_A23);
		return TRUE;
	}
	case IDC_EDIT_A24:
	{
		mat4A(1, 3) = ReadFromEditBox(_hwnd, IDC_EDIT_A24);
		return TRUE;
	}
	case IDC_EDIT_A31:
	{
		mat4A(2, 0) = ReadFromEditBox(_hwnd, IDC_EDIT_A31);
		return TRUE;
	}
	case IDC_EDIT_A32:
	{
		mat4A(2, 1) = ReadFromEditBox(_hwnd, IDC_EDIT_A32);
		return TRUE;
	}
	case IDC_EDIT_A33:
	{
		mat4A(2, 2) = ReadFromEditBox(_hwnd, IDC_EDIT_A33);
		return TRUE;
	}
	case IDC_EDIT_A34:
	{
		mat4A(2, 3) = ReadFromEditBox(_hwnd, IDC_EDIT_A34);
		return TRUE;
	}
	case IDC_EDIT_A41:
	{
		mat4A(3, 0) = ReadFromEditBox(_hwnd, IDC_EDIT_A41);
		return TRUE;
	}
	case IDC_EDIT_A42:
	{
		mat4A(3, 1) = ReadFromEditBox(_hwnd, IDC_EDIT_A42);
		return TRUE;
	}
	case IDC_EDIT_A43:
	{
		mat4A(3, 2) = ReadFromEditBox(_hwnd, IDC_EDIT_A43);
		return TRUE;
	}
	case IDC_EDIT_A44:
	{
		mat4A(3, 3) = ReadFromEditBox(_hwnd, IDC_EDIT_A44);
		return TRUE;
	}
	}

	return FALSE;
}

bool ProcessMatrixBInput(HWND& _hwnd, WPARAM& _wparam)
{
	switch ((LOWORD(_wparam)))
	{
	case IDC_EDIT_B11:
	{
		mat4B(0, 0) = ReadFromEditBox(_hwnd, IDC_EDIT_B11);
		return TRUE;
	}
	case IDC_EDIT_B12:
	{
		mat4B(0, 1) = ReadFromEditBox(_hwnd, IDC_EDIT_B12);
		return TRUE;
	}
	case IDC_EDIT_B13:
	{
		mat4B(0, 2) = ReadFromEditBox(_hwnd, IDC_EDIT_B13);
		return TRUE;
	}
	case IDC_EDIT_B14:
	{
		mat4B(0, 3) = ReadFromEditBox(_hwnd, IDC_EDIT_B14);
		return TRUE;
	}
	case IDC_EDIT_B21:
	{
		mat4B(1, 0) = ReadFromEditBox(_hwnd, IDC_EDIT_B21);
		return TRUE;
	}
	case IDC_EDIT_B22:
	{
		mat4B(1, 1) = ReadFromEditBox(_hwnd, IDC_EDIT_B22);
		return TRUE;
	}
	case IDC_EDIT_B23:
	{
		mat4B(1, 2) = ReadFromEditBox(_hwnd, IDC_EDIT_B23);
		return TRUE;
	}
	case IDC_EDIT_B24:
	{
		mat4B(1, 3) = ReadFromEditBox(_hwnd, IDC_EDIT_B24);
		return TRUE;
	}
	case IDC_EDIT_B31:
	{
		mat4B(2, 0) = ReadFromEditBox(_hwnd, IDC_EDIT_B31);
		return TRUE;
	}
	case IDC_EDIT_B32:
	{
		mat4B(2, 1) = ReadFromEditBox(_hwnd, IDC_EDIT_B32);
		return TRUE;
	}
	case IDC_EDIT_B33:
	{
		mat4B(2, 2) = ReadFromEditBox(_hwnd, IDC_EDIT_B33);
		return TRUE;
	}
	case IDC_EDIT_B34:
	{
		mat4B(2, 3) = ReadFromEditBox(_hwnd, IDC_EDIT_B34);
		return TRUE;
	}
	case IDC_EDIT_B41:
	{
		mat4B(3, 0) = ReadFromEditBox(_hwnd, IDC_EDIT_B41);
		return TRUE;
	}
	case IDC_EDIT_B42:
	{
		mat4B(3, 1) = ReadFromEditBox(_hwnd, IDC_EDIT_B42);
		return TRUE;
	}
	case IDC_EDIT_B43:
	{
		mat4B(3, 2) = ReadFromEditBox(_hwnd, IDC_EDIT_B43);
		return TRUE;
	}
	case IDC_EDIT_B44:
	{
		mat4B(3, 3) = ReadFromEditBox(_hwnd, IDC_EDIT_B44);
		return TRUE;
	}
	}

	return FALSE;
}

bool ProcessMatrixAdditionInput(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDOK)
	{
		mat4Result = mat4A + mat4B;

		WriteResultantMatrix(_hwnd, _wparam);
		return TRUE;
	}

	return FALSE;
}

bool ProcessMatrixMinusInput(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDCANCEL)
	{
		mat4Result = mat4A - mat4B;
		WriteResultantMatrix(_hwnd, _wparam);

		return TRUE;
	}

	return FALSE;
}

bool ProcessMatrixMultiplyInput(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDOK2)
	{
		mat4Result = mat4A * mat4B;
		WriteResultantMatrix(_hwnd, _wparam);

		return TRUE;
	}

	return FALSE;
}

bool ProcessMatrixInverseMultiplyInput(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDOK5)
	{
		mat4Result = mat4B * mat4A;
		WriteResultantMatrix(_hwnd, _wparam);

		return TRUE;
	}

	return FALSE;
}

bool ProcessMatrixBToIdentity(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDOK8)
	{
		mat4B.SetToIdentity();

		WriteBMatrix(_hwnd, _wparam);

		return TRUE;
	}

	return FALSE;
}

bool ProcessMatrixBTranspose(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDOK11)
	{
		mat4B.Transpose();

		WriteBMatrix(_hwnd, _wparam);

		return TRUE;
	}

	return FALSE;
}

bool ProcessMatrixATranspose(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDOK9)
	{
		mat4A.Transpose();

		WriteAMatrix(_hwnd, _wparam);

		return TRUE;
	}

	return FALSE;
}

bool ProcessMatrixAToIdentity(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDOK4)
	{
		mat4A.SetToIdentity();

		WriteAMatrix(_hwnd, _wparam);

		return TRUE;
	}

	return FALSE;
}

bool ProcessMatrixBDeterminant(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDOK7)
	{
		WriteToEditBox(_hwnd, IDC_EDIT_DetB, mat4B.Determinant());

		return TRUE;
	}

	return FALSE;
}

bool ProcessMatrixADeterminant(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDOK3)
	{
		WriteToEditBox(_hwnd, IDC_EDIT_DetA, mat4A.Determinant());

		return TRUE;
	}

	return FALSE;
}

bool ProcessMatrixBInverse(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDCANCEL3)
	{
		mat4Result = mat4B.LUDCInverse();
		WriteResultantMatrix(_hwnd, _wparam);

		return TRUE;
	}

	return FALSE;
}

bool ProcessMatrixAInverse(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDCANCEL2)
	{
		mat4Result = mat4A.LUDCInverse();
		WriteResultantMatrix(_hwnd, _wparam);

		return TRUE;
	}

	return FALSE;
}

bool ProcessMatrixScalarMultiplication(HWND& _hwnd, WPARAM& _wparam)
{
	switch (LOWORD(_wparam))
	{
	case IDOK6:
	{
		mat4A = mat4A * ReadFromEditBox(_hwnd, IDC_EDIT_AScaled);
		WriteAMatrix(_hwnd, _wparam);

		return TRUE;
	}
	case IDOK10:
	{
		mat4B = mat4B * ReadFromEditBox(_hwnd, IDC_EDIT_BScaled);
		WriteBMatrix(_hwnd, _wparam);
		
		return TRUE;
	}
	default:
		return FALSE;
	}
}

void WriteResultantMatrix(HWND& _hwnd, WPARAM& _wparam)
{
	WriteToEditBox(_hwnd, IDC_EDIT_R11, mat4Result(0, 0));
	WriteToEditBox(_hwnd, IDC_EDIT_R12, mat4Result(0, 1));
	WriteToEditBox(_hwnd, IDC_EDIT_R13, mat4Result(0, 2));
	WriteToEditBox(_hwnd, IDC_EDIT_R14, mat4Result(0, 3));
	WriteToEditBox(_hwnd, IDC_EDIT_R21, mat4Result(1, 0));
	WriteToEditBox(_hwnd, IDC_EDIT_R22, mat4Result(1, 1));
	WriteToEditBox(_hwnd, IDC_EDIT_R23, mat4Result(1, 2));
	WriteToEditBox(_hwnd, IDC_EDIT_R24, mat4Result(1, 3));
	WriteToEditBox(_hwnd, IDC_EDIT_R31, mat4Result(2, 0));
	WriteToEditBox(_hwnd, IDC_EDIT_R32, mat4Result(2, 1));
	WriteToEditBox(_hwnd, IDC_EDIT_R33, mat4Result(2, 2));
	WriteToEditBox(_hwnd, IDC_EDIT_R34, mat4Result(2, 3));
	WriteToEditBox(_hwnd, IDC_EDIT_R41, mat4Result(3, 0));
	WriteToEditBox(_hwnd, IDC_EDIT_R42, mat4Result(3, 1));
	WriteToEditBox(_hwnd, IDC_EDIT_R43, mat4Result(3, 2));
	WriteToEditBox(_hwnd, IDC_EDIT_R44, mat4Result(3, 3));
}

void WriteBMatrix(HWND& _hwnd, WPARAM& _wparam)
{
	WriteToEditBox(_hwnd, IDC_EDIT_B11, mat4B(0, 0));
	WriteToEditBox(_hwnd, IDC_EDIT_B12, mat4B(0, 1));
	WriteToEditBox(_hwnd, IDC_EDIT_B13, mat4B(0, 2));
	WriteToEditBox(_hwnd, IDC_EDIT_B14, mat4B(0, 3));
	WriteToEditBox(_hwnd, IDC_EDIT_B21, mat4B(1, 0));
	WriteToEditBox(_hwnd, IDC_EDIT_B22, mat4B(1, 1));
	WriteToEditBox(_hwnd, IDC_EDIT_B23, mat4B(1, 2));
	WriteToEditBox(_hwnd, IDC_EDIT_B24, mat4B(1, 3));
	WriteToEditBox(_hwnd, IDC_EDIT_B31, mat4B(2, 0));
	WriteToEditBox(_hwnd, IDC_EDIT_B32, mat4B(2, 1));
	WriteToEditBox(_hwnd, IDC_EDIT_B33, mat4B(2, 2));
	WriteToEditBox(_hwnd, IDC_EDIT_B34, mat4B(2, 3));
	WriteToEditBox(_hwnd, IDC_EDIT_B41, mat4B(3, 0));
	WriteToEditBox(_hwnd, IDC_EDIT_B42, mat4B(3, 1));
	WriteToEditBox(_hwnd, IDC_EDIT_B43, mat4B(3, 2));
	WriteToEditBox(_hwnd, IDC_EDIT_B44, mat4B(3, 3));
}

void WriteAMatrix(HWND& _hwnd, WPARAM& _wparam)
{
	WriteToEditBox(_hwnd, IDC_EDIT_A11, mat4A(0, 0));
	WriteToEditBox(_hwnd, IDC_EDIT_A12, mat4A(0, 1));
	WriteToEditBox(_hwnd, IDC_EDIT_A13, mat4A(0, 2));
	WriteToEditBox(_hwnd, IDC_EDIT_A14, mat4A(0, 3));
	WriteToEditBox(_hwnd, IDC_EDIT_A21, mat4A(1, 0));
	WriteToEditBox(_hwnd, IDC_EDIT_A22, mat4A(1, 1));
	WriteToEditBox(_hwnd, IDC_EDIT_A23, mat4A(1, 2));
	WriteToEditBox(_hwnd, IDC_EDIT_A24, mat4A(1, 3));
	WriteToEditBox(_hwnd, IDC_EDIT_A31, mat4A(2, 0));
	WriteToEditBox(_hwnd, IDC_EDIT_A32, mat4A(2, 1));
	WriteToEditBox(_hwnd, IDC_EDIT_A33, mat4A(2, 2));
	WriteToEditBox(_hwnd, IDC_EDIT_A34, mat4A(2, 3));
	WriteToEditBox(_hwnd, IDC_EDIT_A41, mat4A(3, 0));
	WriteToEditBox(_hwnd, IDC_EDIT_A42, mat4A(3, 1));
	WriteToEditBox(_hwnd, IDC_EDIT_A43, mat4A(3, 2));
	WriteToEditBox(_hwnd, IDC_EDIT_A44, mat4A(3, 3));
}

bool ProcessQuaternionAInput(HWND& _hwnd, WPARAM& _wparam)
{
	switch ((LOWORD(_wparam)))
	{
	case IDC_EDIT1:
	{
		quatA.SetX(ReadFromEditBox(_hwnd, IDC_EDIT1));
		return TRUE;
	}
	case IDC_EDIT2:
	{
		quatA.SetY(ReadFromEditBox(_hwnd, IDC_EDIT2));
		return TRUE;
	}
	case IDC_EDIT3:
	{
		quatA.SetZ(ReadFromEditBox(_hwnd, IDC_EDIT3));
		return TRUE;
	}
	case IDC_EDIT4:
	{
		quatA.SetW(ReadFromEditBox(_hwnd, IDC_EDIT4));
		return TRUE;
	}
	}

	return FALSE;
}

bool ProcessQuaternionBInput(HWND& _hwnd, WPARAM& _wparam)
{
	switch ((LOWORD(_wparam)))
	{
	case IDC_EDIT5:
	{
		quatB.SetX(ReadFromEditBox(_hwnd, IDC_EDIT5));
		return TRUE;
	}
	case IDC_EDIT6:
	{
		quatB.SetY(ReadFromEditBox(_hwnd, IDC_EDIT6));
		return TRUE;
	}
	case IDC_EDIT7:
	{
		quatB.SetZ(ReadFromEditBox(_hwnd, IDC_EDIT7));
		return TRUE;
	}
	case IDC_EDIT8:
	{
		quatB.SetW(ReadFromEditBox(_hwnd, IDC_EDIT8));
		return TRUE;
	}
	}

	return FALSE;
}

bool ProcessQuaternionAdditionInput(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDC_BUTTON1)
	{
		quatResult = quatA + quatB;
		WriteResultantQuaternion(_hwnd, _wparam);

		return TRUE;
	}

	return FALSE;
}

bool ProcessQuaternionMinusInput(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDC_BUTTON5)
	{
		quatResult = quatA - quatB;
		WriteResultantQuaternion(_hwnd, _wparam);

		return TRUE;
	}

	return FALSE;
}

bool ProcessQuaternionInverseMinusInput(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDC_BUTTON6)
	{
		quatResult = quatB - quatA;
		WriteResultantQuaternion(_hwnd, _wparam);

		return TRUE;
	}

	return FALSE;
}

bool ProcessQuaternionMultiplyInput(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDC_BUTTON2)
	{
		quatResult = quatA * quatB;
		WriteResultantQuaternion(_hwnd, _wparam);

		return TRUE;
	}

	return FALSE;
}

bool ProcessQuaternionInverseMultiplyInput(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDC_BUTTON7)
	{
		quatResult = quatB * quatA;
		WriteResultantQuaternion(_hwnd, _wparam);

		return TRUE;
	}

	return FALSE;
}

bool ProcessQuaternionDotProduct(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDC_BUTTON8)
	{
		WriteToEditBox(_hwnd, IDC_EDIT9, quatA.DotProduct(quatB));

		return TRUE;
	}

	return FALSE;
}

bool ProcessQuaternionAConjugate(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDC_BUTTON3)
	{
		quatA = quatA.GetConjugate();
		WriteAQuaternion(_hwnd, _wparam);

		return TRUE;
	}

	return FALSE;
}

bool ProcessQuaternionBConjugate(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDC_BUTTON9)
	{
		quatB = quatB.GetConjugate();
		WriteBQuaternion(_hwnd, _wparam);

		return TRUE;
	}

	return FALSE;
}

bool ProcessQuaternionAMagnitude(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDC_BUTTON10)
	{
		WriteToEditBox(_hwnd, IDC_EDIT9, quatA.GetMagnitude());

		return TRUE;
	}

	return FALSE;
}

bool ProcessQuaternionBMagnitude(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDC_BUTTON11)
	{
		WriteToEditBox(_hwnd, IDC_EDIT9, quatB.GetMagnitude());

		return TRUE;
	}

	return FALSE;
}

bool ProcessQuaternionAInverse(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDC_BUTTON12)
	{
		quatA = quatA.GetInverse();
		WriteAQuaternion(_hwnd, _wparam);

		return TRUE;
	}

	return FALSE;
}

bool ProcessQuaternionBInverse(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDC_BUTTON13)
	{
		quatB = quatB.GetInverse();
		WriteBQuaternion(_hwnd, _wparam);

		return TRUE;
	}

	return FALSE;
}

bool ProcessQuaternionAScalarMultiplication(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDC_BUTTON14)
	{
		quatA *= ReadFromEditBox(_hwnd, IDC_EDIT9);
		WriteAQuaternion(_hwnd, _wparam);

		return TRUE;
	}

	return FALSE;
}

bool ProcessQuaternionBScalarMultiplication(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDC_BUTTON15)
	{
		quatB *= ReadFromEditBox(_hwnd, IDC_EDIT9);
		WriteBQuaternion(_hwnd, _wparam);

		return TRUE;
	}

	return FALSE;
}

void WriteResultantQuaternion(HWND& _hwnd, WPARAM& _wparam)
{
	WriteToEditBox(_hwnd, IDC_EDIT10, quatResult.GetX());
	WriteToEditBox(_hwnd, IDC_EDIT11, quatResult.GetY());
	WriteToEditBox(_hwnd, IDC_EDIT12, quatResult.GetZ());
	WriteToEditBox(_hwnd, IDC_EDIT13, quatResult.GetW());
}

void WriteBQuaternion(HWND& _hwnd, WPARAM& _wparam)
{
	WriteToEditBox(_hwnd, IDC_EDIT5, quatB.GetX());
	WriteToEditBox(_hwnd, IDC_EDIT6, quatB.GetY());
	WriteToEditBox(_hwnd, IDC_EDIT7, quatB.GetZ());
	WriteToEditBox(_hwnd, IDC_EDIT8, quatB.GetW());
}

void WriteAQuaternion(HWND& _hwnd, WPARAM& _wparam)
{
	WriteToEditBox(_hwnd, IDC_EDIT1, quatA.GetX());
	WriteToEditBox(_hwnd, IDC_EDIT2, quatA.GetY());
	WriteToEditBox(_hwnd, IDC_EDIT3, quatA.GetZ());
	WriteToEditBox(_hwnd, IDC_EDIT4, quatA.GetW());
}

bool ProcessGEInput(HWND& _hwnd, WPARAM& _wparam)
{
	switch ((LOWORD(_wparam)))
	{
	case IDC_EDIT1:
	{
		geMatrix.SetRowAndColumn(0, 0, ReadFromEditBox(_hwnd, IDC_EDIT1));
		return TRUE;
	}
	case IDC_EDIT4:
	{
		geMatrix.SetRowAndColumn(0, 1, ReadFromEditBox(_hwnd, IDC_EDIT4));
		return TRUE;
	}
	case IDC_EDIT2:
	{
		geMatrix.SetRowAndColumn(0, 2, ReadFromEditBox(_hwnd, IDC_EDIT2));
		return TRUE;
	}
	case IDC_EDIT3:
	{
		geMatrix.SetRowAndColumn(0, 3, ReadFromEditBox(_hwnd, IDC_EDIT3));
		return TRUE;
	}
	case IDC_EDIT5:
	{
		geMatrix.SetRowAndColumn(1, 0, ReadFromEditBox(_hwnd, IDC_EDIT5));
		return TRUE;				
	}								
	case IDC_EDIT8:					
	{								
		geMatrix.SetRowAndColumn(1, 1, ReadFromEditBox(_hwnd, IDC_EDIT8));
		return TRUE;				
	}								
	case IDC_EDIT6:					
	{								
		geMatrix.SetRowAndColumn(1, 2, ReadFromEditBox(_hwnd, IDC_EDIT6));
		return TRUE;				
	}								
	case IDC_EDIT7:					
	{								
		geMatrix.SetRowAndColumn(1, 3, ReadFromEditBox(_hwnd, IDC_EDIT7));
		return TRUE;
	}
	case IDC_EDIT9:
	{
		geMatrix.SetRowAndColumn(2, 0, ReadFromEditBox(_hwnd, IDC_EDIT9));
		return TRUE;
	}
	case IDC_EDIT12:
	{
		geMatrix.SetRowAndColumn(2, 1, ReadFromEditBox(_hwnd, IDC_EDIT12));
		return TRUE;
	}
	case IDC_EDIT10:
	{
		geMatrix.SetRowAndColumn(2, 2, ReadFromEditBox(_hwnd, IDC_EDIT10));
		return TRUE;
	}
	case IDC_EDIT11:
	{
		geMatrix.SetRowAndColumn(2, 3, ReadFromEditBox(_hwnd, IDC_EDIT11));
		return TRUE;
	}
	}

	return FALSE;
}

bool ProcessGEMultiplyInput(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDC_BUTTON1)
	{
		geMatrix.MultiplyRowByScalar
		(
			(int)ReadFromEditBox(_hwnd, IDC_EDIT13),
			ReadFromEditBox(_hwnd, IDC_EDIT14)
		);

		WriteGEValues(_hwnd, _wparam);
		CheckEchelonForm(_hwnd);
		return TRUE;
	}

	return FALSE;
}

bool ProcessGESwapInput(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDC_BUTTON2)
	{
		geMatrix.SwapRow((int)ReadFromEditBox(_hwnd, IDC_EDIT16), (int)ReadFromEditBox(_hwnd, IDC_EDIT17));
		WriteGEValues(_hwnd, _wparam);
		CheckEchelonForm(_hwnd);
		return TRUE;
	}

	return FALSE;
}

bool ProcessGEAdditionInput(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDC_BUTTON3)
	{
		geMatrix.RowAddition
		(
			ReadFromEditBox(_hwnd, IDC_EDIT19),
			(int)ReadFromEditBox(_hwnd, IDC_EDIT20),
			(int)ReadFromEditBox(_hwnd, IDC_EDIT22)
		);

		WriteGEValues(_hwnd, _wparam);
		CheckEchelonForm(_hwnd);
		return TRUE;
	}

	return FALSE;
}

void CheckEchelonForm(HWND& _hwnd)
{
	bool bIsInRowEchelon = geMatrix.IsInRowEchelon();
	bool bIsInReducedRowEchelon = geMatrix.IsInReducedRowEchelon();

	if (bIsInRowEchelon && bIsInReducedRowEchelon)
	{
		MessageBox(_hwnd, L"The matrix is in row echelon form and in reduced row echelon form", L"", MB_OK);
	}
	else if (bIsInRowEchelon)
	{
		MessageBox(_hwnd, L"The matrix is in row echelon form", L"", MB_OK);
	}
	else if (bIsInReducedRowEchelon)
	{
		MessageBox(_hwnd, L"The matrix is in reduced row echelon form", L"", MB_OK);
	}
}

void WriteGEValues(HWND& _hwnd, WPARAM& _wparam)
{
	WriteToEditBox(_hwnd, IDC_EDIT1, geMatrix.GetRowAndColumn(0, 0));
	WriteToEditBox(_hwnd, IDC_EDIT4, geMatrix.GetRowAndColumn(0, 1));
	WriteToEditBox(_hwnd, IDC_EDIT2, geMatrix.GetRowAndColumn(0, 2));
	WriteToEditBox(_hwnd, IDC_EDIT3, geMatrix.GetRowAndColumn(0, 3));
	WriteToEditBox(_hwnd, IDC_EDIT5, geMatrix.GetRowAndColumn(1, 0));
	WriteToEditBox(_hwnd, IDC_EDIT8, geMatrix.GetRowAndColumn(1, 1));
	WriteToEditBox(_hwnd, IDC_EDIT6, geMatrix.GetRowAndColumn(1, 2));
	WriteToEditBox(_hwnd, IDC_EDIT7, geMatrix.GetRowAndColumn(1, 3));
	WriteToEditBox(_hwnd, IDC_EDIT9, geMatrix.GetRowAndColumn(2, 0));
	WriteToEditBox(_hwnd, IDC_EDIT12, geMatrix.GetRowAndColumn(2, 1));
	WriteToEditBox(_hwnd, IDC_EDIT10, geMatrix.GetRowAndColumn(2, 2));
	WriteToEditBox(_hwnd, IDC_EDIT11, geMatrix.GetRowAndColumn(2, 3));
}

bool ProcessQuaternionASlerpInput(HWND& _hwnd, WPARAM& _wparam)
{
	switch (LOWORD(_wparam))
	{
	case IDC_EDIT1:
	{
		quatA.SetX(ReadFromEditBox(_hwnd, IDC_EDIT1));
		return TRUE;
	}
	case IDC_EDIT2:
	{
		quatA.SetY(ReadFromEditBox(_hwnd, IDC_EDIT2));
		return TRUE;
	}
	case IDC_EDIT3:
	{
		quatA.SetZ(ReadFromEditBox(_hwnd, IDC_EDIT3));
		return TRUE;
	}
	case IDC_EDIT4:
	{
		quatA.SetW(ReadFromEditBox(_hwnd, IDC_EDIT4));
		return TRUE;
	}
	}

	return FALSE;
}

bool ProcessQuaternionBSlerpInput(HWND& _hwnd, WPARAM& _wparam)
{
	switch (LOWORD(_wparam))
	{
	case IDC_EDIT5:
	{
		quatB.SetX(ReadFromEditBox(_hwnd, IDC_EDIT5));
		return TRUE;
	}
	case IDC_EDIT6:
	{
		quatB.SetY(ReadFromEditBox(_hwnd, IDC_EDIT6));
		return TRUE;
	}
	case IDC_EDIT7:
	{
		quatB.SetZ(ReadFromEditBox(_hwnd, IDC_EDIT7));
		return TRUE;
	}
	case IDC_EDIT8:
	{
		quatB.SetW(ReadFromEditBox(_hwnd, IDC_EDIT8));
		return TRUE;
	}
	}

	return FALSE;
}

bool ProcessQuaternionResultantSlerpInput(HWND& _hwnd, WPARAM& _wparam)
{
	switch (LOWORD(_wparam))
	{
	case IDC_EDIT10:
	{
		quatResult.SetX(ReadFromEditBox(_hwnd, IDC_EDIT10));
		return TRUE;
	}
	case IDC_EDIT11:
	{
		quatResult.SetY(ReadFromEditBox(_hwnd, IDC_EDIT11));
		return TRUE;
	}
	case IDC_EDIT12:
	{
		quatResult.SetZ(ReadFromEditBox(_hwnd, IDC_EDIT12));
		return TRUE;
	}
	case IDC_EDIT13:
	{
		quatResult.SetW(ReadFromEditBox(_hwnd, IDC_EDIT13));
		return TRUE;
	}
	}

	return FALSE;
}

bool ProcessSlerpInput(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDC_BUTTON1)
	{
		quatResult = CSlerp::Slerp(quatA, quatB, ReadFromEditBox(_hwnd, IDC_EDIT9));
		WriteQuaternionResultantSlerp(_hwnd, _wparam);

		return TRUE;
	}

	return FALSE;
}

bool ProcessInducedMatrixAInput(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDC_BUTTON2)
	{
		mat4Result = quatA.InducedMatrix();
		WriteResultantSlerpMatrix(_hwnd, _wparam);

		return TRUE;
	}

	return false;
}

bool ProcessInducedMatrixBInput(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDC_BUTTON3)
	{
		mat4Result = quatB.InducedMatrix();
		WriteResultantSlerpMatrix(_hwnd, _wparam);

		return TRUE;
	}

	return false;
}

bool ProcessInducedSlerpMatrixInput(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDC_BUTTON4)
	{
		quatResult = CSlerp::Slerp(quatA, quatB, ReadFromEditBox(_hwnd, IDC_EDIT9));
		mat4Result = quatResult.InducedMatrix();

		WriteQuaternionResultantSlerp(_hwnd, _wparam);
		WriteResultantSlerpMatrix(_hwnd, _wparam);

		return TRUE;
	}

	return false;
}

void WriteQuaternionResultantSlerp(HWND& _hwnd, WPARAM& _wparam)
{
	WriteToEditBox(_hwnd, IDC_EDIT10, quatResult.GetX());
	WriteToEditBox(_hwnd, IDC_EDIT11, quatResult.GetY());
	WriteToEditBox(_hwnd, IDC_EDIT12, quatResult.GetZ());
	WriteToEditBox(_hwnd, IDC_EDIT13, quatResult.GetW());
}

void WriteResultantSlerpMatrix(HWND& _hwnd, WPARAM& _wparam)
{
	WriteToEditBox(_hwnd, IDC_EDIT34, mat4Result(0, 0));
	WriteToEditBox(_hwnd, IDC_EDIT35, mat4Result(0, 1));
	WriteToEditBox(_hwnd, IDC_EDIT36, mat4Result(0, 2));
	WriteToEditBox(_hwnd, IDC_EDIT37, mat4Result(0, 3));
	WriteToEditBox(_hwnd, IDC_EDIT38, mat4Result(1, 0));
	WriteToEditBox(_hwnd, IDC_EDIT39, mat4Result(1, 1));
	WriteToEditBox(_hwnd, IDC_EDIT40, mat4Result(1, 2));
	WriteToEditBox(_hwnd, IDC_EDIT41, mat4Result(1, 3));
	WriteToEditBox(_hwnd, IDC_EDIT42, mat4Result(2, 0));
	WriteToEditBox(_hwnd, IDC_EDIT43, mat4Result(2, 1));
	WriteToEditBox(_hwnd, IDC_EDIT44, mat4Result(2, 2));
	WriteToEditBox(_hwnd, IDC_EDIT45, mat4Result(2, 3));
	WriteToEditBox(_hwnd, IDC_EDIT46, mat4Result(3, 0));
	WriteToEditBox(_hwnd, IDC_EDIT47, mat4Result(3, 1));
	WriteToEditBox(_hwnd, IDC_EDIT48, mat4Result(3, 2));
	WriteToEditBox(_hwnd, IDC_EDIT49, mat4Result(3, 3));
}

bool ProcessResultantTransformationMatrixInput(HWND& _hwnd, WPARAM& _wparam)
{
	switch (LOWORD(_wparam))
	{
	case IDC_EDIT16:
		mat4Result(0, 0) = ReadFromEditBox(_hwnd, IDC_EDIT16);
		WriteToEditBox(_hwnd, IDC_EDIT47, mat4Result(0, 0));
		return TRUE;

	case IDC_EDIT18:
		mat4Result(0, 1) = ReadFromEditBox(_hwnd, IDC_EDIT18);
		WriteToEditBox(_hwnd, IDC_EDIT51, mat4Result(0, 1));
		return TRUE;

	case IDC_EDIT19:
		mat4Result(0, 2) = ReadFromEditBox(_hwnd, IDC_EDIT19);
		WriteToEditBox(_hwnd, IDC_EDIT55, mat4Result(0, 2));
		return TRUE;

	case IDC_EDIT20:
		mat4Result(0, 3) = ReadFromEditBox(_hwnd, IDC_EDIT20);
		WriteToEditBox(_hwnd, IDC_EDIT59, mat4Result(0, 3));
		return TRUE;
	
	
	case IDC_EDIT21:
		mat4Result(1, 0) = ReadFromEditBox(_hwnd, IDC_EDIT21);
		WriteToEditBox(_hwnd, IDC_EDIT48, mat4Result(1, 0));
		return TRUE;

	case IDC_EDIT22:
		mat4Result(1, 1) = ReadFromEditBox(_hwnd, IDC_EDIT22);
		WriteToEditBox(_hwnd, IDC_EDIT52, mat4Result(1, 1));
		return TRUE;

	case IDC_EDIT23:
		mat4Result(1, 2) = ReadFromEditBox(_hwnd, IDC_EDIT23);
		WriteToEditBox(_hwnd, IDC_EDIT56, mat4Result(1, 2));
		return TRUE;

	case IDC_EDIT8:
		mat4Result(1, 3) = ReadFromEditBox(_hwnd, IDC_EDIT8);
		WriteToEditBox(_hwnd, IDC_EDIT60, mat4Result(1, 3));
		return TRUE;


	case IDC_EDIT9:
		mat4Result(2, 0) = ReadFromEditBox(_hwnd, IDC_EDIT9);
		WriteToEditBox(_hwnd, IDC_EDIT49, mat4Result(2, 0));
		return TRUE;

	case IDC_EDIT10:
		mat4Result(2, 1) = ReadFromEditBox(_hwnd, IDC_EDIT10);
		WriteToEditBox(_hwnd, IDC_EDIT53, mat4Result(2, 1));
		return TRUE;

	case IDC_EDIT11:
		mat4Result(2, 2) = ReadFromEditBox(_hwnd, IDC_EDIT11);
		WriteToEditBox(_hwnd, IDC_EDIT57, mat4Result(2, 2));
		return TRUE;

	case IDC_EDIT12:
		mat4Result(2, 3) = ReadFromEditBox(_hwnd, IDC_EDIT12);
		WriteToEditBox(_hwnd, IDC_EDIT61, mat4Result(2, 3));
		return TRUE;


	case IDC_EDIT24:
		mat4Result(3, 0) = ReadFromEditBox(_hwnd, IDC_EDIT24);
		WriteToEditBox(_hwnd, IDC_EDIT50, mat4Result(3, 0));
		return TRUE;

	case IDC_EDIT25:
		mat4Result(3, 1) = ReadFromEditBox(_hwnd, IDC_EDIT25);
		WriteToEditBox(_hwnd, IDC_EDIT54, mat4Result(3, 1));
		return TRUE;

	case IDC_EDIT26:
		mat4Result(3, 2) = ReadFromEditBox(_hwnd, IDC_EDIT26);
		WriteToEditBox(_hwnd, IDC_EDIT58, mat4Result(3, 2));
		return TRUE;

	case IDC_EDIT27:
		mat4Result(3, 3) = ReadFromEditBox(_hwnd, IDC_EDIT27);
		WriteToEditBox(_hwnd, IDC_EDIT62, mat4Result(3, 3));
		return TRUE;
	}

	return FALSE;
}

bool ProcessScaleTransformationInput(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDC_BUTTON4)
	{
		mat4Result *= CTransformation::Scale
		(
			ReadFromEditBox(_hwnd, IDC_EDIT1),
			ReadFromEditBox(_hwnd, IDC_EDIT2),
			ReadFromEditBox(_hwnd, IDC_EDIT3)
		);
		WriteResultantTransformationMatrix(_hwnd, _wparam);

		return TRUE;
	}

	return FALSE;
}

bool ProcessTranslateTransformationInput(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDC_BUTTON15)
	{
		mat4Result *= CTransformation::Translation
		(
			ReadFromEditBox(_hwnd, IDC_EDIT4),
			ReadFromEditBox(_hwnd, IDC_EDIT5),
			ReadFromEditBox(_hwnd, IDC_EDIT6)
		);
		WriteResultantTransformationMatrix(_hwnd, _wparam);

		return TRUE;
	}

	return FALSE;
}

bool ProcessRotateTransformationInput(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDC_BUTTON16)
	{
		unsigned int uAxisOfRotation = 0;
		if (IsDlgButtonChecked(_hwnd, IDC_RADIO1)) { uAxisOfRotation = 0; }
		else if (IsDlgButtonChecked(_hwnd, IDC_RADIO2)) { uAxisOfRotation = 1; }
		else if (IsDlgButtonChecked(_hwnd, IDC_RADIO3)) { uAxisOfRotation = 2; }

		mat4Result *= CTransformation::EulerRotation(uAxisOfRotation, ReadFromEditBox(_hwnd, IDC_EDIT13));
		WriteResultantTransformationMatrix(_hwnd, _wparam);

		return TRUE;
	}

	return FALSE;
}

bool ProcessProjectTransformationInput(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDC_BUTTON17)
	{
		unsigned int uAxisOfProjection = 0;
		if (IsDlgButtonChecked(_hwnd, IDC_RADIO4)) { uAxisOfProjection = 0; }
		else if (IsDlgButtonChecked(_hwnd, IDC_RADIO5)) { uAxisOfProjection = 1; }
		else if (IsDlgButtonChecked(_hwnd, IDC_RADIO6)) { uAxisOfProjection = 2; }

		mat4Result *= CTransformation::Projection(uAxisOfProjection, ReadFromEditBox(_hwnd, IDC_EDIT15));
		WriteResultantTransformationMatrix(_hwnd, _wparam);

		return TRUE;
	}

	return FALSE;
}

void WriteResultantTransformationMatrix(HWND& _hwnd, WPARAM& _wparam)
{
	//Column-Major Format
	WriteToEditBox(_hwnd, IDC_EDIT16, mat4Result(0, 0));
	WriteToEditBox(_hwnd, IDC_EDIT18, mat4Result(0, 1));
	WriteToEditBox(_hwnd, IDC_EDIT19, mat4Result(0, 2));
	WriteToEditBox(_hwnd, IDC_EDIT20, mat4Result(0, 3));

	WriteToEditBox(_hwnd, IDC_EDIT21, mat4Result(1, 0));
	WriteToEditBox(_hwnd, IDC_EDIT22, mat4Result(1, 1));
	WriteToEditBox(_hwnd, IDC_EDIT23, mat4Result(1, 2));
	WriteToEditBox(_hwnd, IDC_EDIT8,  mat4Result(1, 3));

	WriteToEditBox(_hwnd, IDC_EDIT9,  mat4Result(2, 0));
	WriteToEditBox(_hwnd, IDC_EDIT10, mat4Result(2, 1));
	WriteToEditBox(_hwnd, IDC_EDIT11, mat4Result(2, 2));
	WriteToEditBox(_hwnd, IDC_EDIT12, mat4Result(2, 3));

	WriteToEditBox(_hwnd, IDC_EDIT24, mat4Result(3, 0));
	WriteToEditBox(_hwnd, IDC_EDIT25, mat4Result(3, 1));
	WriteToEditBox(_hwnd, IDC_EDIT26, mat4Result(3, 2));
	WriteToEditBox(_hwnd, IDC_EDIT27, mat4Result(3, 3));

	//Row-Major Format
	WriteToEditBox(_hwnd, IDC_EDIT47, mat4Result(0, 0));
	WriteToEditBox(_hwnd, IDC_EDIT48, mat4Result(1, 0));
	WriteToEditBox(_hwnd, IDC_EDIT49, mat4Result(2, 0));
	WriteToEditBox(_hwnd, IDC_EDIT50, mat4Result(3, 0));

	WriteToEditBox(_hwnd, IDC_EDIT51, mat4Result(0, 1));
	WriteToEditBox(_hwnd, IDC_EDIT52, mat4Result(1, 1));
	WriteToEditBox(_hwnd, IDC_EDIT53, mat4Result(2, 1));
	WriteToEditBox(_hwnd, IDC_EDIT54, mat4Result(3, 1));

	WriteToEditBox(_hwnd, IDC_EDIT55, mat4Result(0, 2));
	WriteToEditBox(_hwnd, IDC_EDIT56, mat4Result(1, 2));
	WriteToEditBox(_hwnd, IDC_EDIT57, mat4Result(2, 2));
	WriteToEditBox(_hwnd, IDC_EDIT58, mat4Result(3, 2));

	WriteToEditBox(_hwnd, IDC_EDIT59, mat4Result(0, 3));
	WriteToEditBox(_hwnd, IDC_EDIT60, mat4Result(1, 3));
	WriteToEditBox(_hwnd, IDC_EDIT61, mat4Result(2, 3));
	WriteToEditBox(_hwnd, IDC_EDIT62, mat4Result(3, 3));
}
