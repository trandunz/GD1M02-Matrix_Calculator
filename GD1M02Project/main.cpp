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

void WriteResultantMatrixValues(HWND& _hwnd, WPARAM& _wparam);
void WriteBMatrixValues(HWND& _hwnd, WPARAM& _wparam);
void WriteAMatrixValues(HWND& _hwnd, WPARAM& _wparam);

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

void WriteResultantQuaternionValues(HWND& _hwnd, WPARAM& _wparam);
void WriteBQuaternionValues(HWND& _hwnd, WPARAM& _wparam);
void WriteAQuaternionValues(HWND& _hwnd, WPARAM& _wparam);

//Windows
HMENU g_hMenu;
HWND g_hDlgMatrix, g_hDlgTransformation, g_hDlgGaussian, g_hDlgQuaternion, g_hDlgSLERP;

// Data Used
CMatrix4 mat4A, mat4B, mat4Result;
CQuaternion quatA, quatB, quatResult;

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
			break;
		}
		case ID_CALCULATOR_TRANSFORMATION:
		{
			ShowWindow(g_hDlgTransformation, SW_SHOWNORMAL);
			break;
		}
		// Open Matrix Dialog
		case ID_CALCULATOR_GAUSSIAN:
		{
			ShowWindow(g_hDlgGaussian, SW_SHOWNORMAL);
			break;
		}
		// Open Gaussian Dialog
		case ID_CALCULATOR_QUATERNION:
		{
			ShowWindow(g_hDlgQuaternion, SW_SHOWNORMAL);
			break;
		}
		// Open Quaternion Dialog
		case ID_CALCULATOR_SLERP:
		{
			ShowWindow(g_hDlgSLERP, SW_SHOWNORMAL);
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
		//switch (LOWORD(_wparam))
		//{
		//
		//default:
		//	break;
		//}
		
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
		//switch (LOWORD(_wparam))
		//{
		//
		//default:
		//	break;
		//}

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
		//switch (LOWORD(_wparam))
		//{
		//
		//default:
		//	break;
		//}

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
//

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
		mat4Result.SetToZero();
		mat4Result = mat4A + mat4B;

		WriteResultantMatrixValues(_hwnd, _wparam);

		return TRUE;
	}

	return FALSE;
}

bool ProcessMatrixMinusInput(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDCANCEL)
	{
		mat4Result.SetToZero();
		mat4Result = mat4A - mat4B;

		WriteResultantMatrixValues(_hwnd, _wparam);

		return TRUE;
	}

	return FALSE;
}

bool ProcessMatrixMultiplyInput(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDOK2)
	{
		mat4Result.SetToZero();
		mat4Result = mat4A * mat4B;

		WriteResultantMatrixValues(_hwnd, _wparam);

		return TRUE;
	}

	return FALSE;
}

bool ProcessMatrixInverseMultiplyInput(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDOK5)
	{
		mat4Result.SetToZero();
		mat4Result = mat4B * mat4A;

		WriteResultantMatrixValues(_hwnd, _wparam);

		return TRUE;
	}

	return FALSE;
}

bool ProcessMatrixBToIdentity(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDOK8)
	{
		mat4B.SetToIdentity();

		WriteBMatrixValues(_hwnd, _wparam);

		return TRUE;
	}

	return FALSE;
}

bool ProcessMatrixBTranspose(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDOK11)
	{
		mat4B.Transpose();

		WriteBMatrixValues(_hwnd, _wparam);

		return TRUE;
	}

	return FALSE;
}

bool ProcessMatrixATranspose(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDOK9)
	{
		mat4A.Transpose();

		WriteAMatrixValues(_hwnd, _wparam);

		return TRUE;
	}

	return FALSE;
}

bool ProcessMatrixAToIdentity(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDOK4)
	{
		mat4A.SetToIdentity();

		WriteAMatrixValues(_hwnd, _wparam);

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
		WriteResultantMatrixValues(_hwnd, _wparam);

		return TRUE;
	}

	return FALSE;
}

bool ProcessMatrixAInverse(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDCANCEL2)
	{
		mat4Result = mat4A.LUDCInverse();
		WriteResultantMatrixValues(_hwnd, _wparam);

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
		WriteAMatrixValues(_hwnd, _wparam);

		return TRUE;
	}
	case IDOK10:
	{
		mat4B = mat4B * ReadFromEditBox(_hwnd, IDC_EDIT_BScaled);
		WriteBMatrixValues(_hwnd, _wparam);
		
		return TRUE;
	}
	default:
		return FALSE;
	}
}

void WriteResultantMatrixValues(HWND& _hwnd, WPARAM& _wparam)
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

void WriteBMatrixValues(HWND& _hwnd, WPARAM& _wparam)
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

void WriteAMatrixValues(HWND& _hwnd, WPARAM& _wparam)
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
		WriteResultantQuaternionValues(_hwnd, _wparam);

		return TRUE;
	}

	return FALSE;
}

bool ProcessQuaternionMinusInput(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDC_BUTTON5)
	{
		quatResult = quatA - quatB;
		WriteResultantQuaternionValues(_hwnd, _wparam);

		return TRUE;
	}

	return FALSE;
}

bool ProcessQuaternionInverseMinusInput(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDC_BUTTON6)
	{
		quatResult = quatB - quatA;
		WriteResultantQuaternionValues(_hwnd, _wparam);

		return TRUE;
	}

	return FALSE;
}

bool ProcessQuaternionMultiplyInput(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDC_BUTTON2)
	{
		quatResult = quatA * quatB;
		WriteResultantQuaternionValues(_hwnd, _wparam);

		return TRUE;
	}

	return FALSE;
}

bool ProcessQuaternionInverseMultiplyInput(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDC_BUTTON7)
	{
		quatResult = quatB * quatA;
		WriteResultantQuaternionValues(_hwnd, _wparam);

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
		WriteAQuaternionValues(_hwnd, _wparam);

		return TRUE;
	}

	return FALSE;
}

bool ProcessQuaternionBConjugate(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDC_BUTTON9)
	{
		quatB = quatB.GetConjugate();
		WriteBQuaternionValues(_hwnd, _wparam);

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
		WriteAQuaternionValues(_hwnd, _wparam);

		return TRUE;
	}

	return FALSE;
}

bool ProcessQuaternionBInverse(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDC_BUTTON13)
	{
		quatB = quatB.GetInverse();
		WriteBQuaternionValues(_hwnd, _wparam);

		return TRUE;
	}

	return FALSE;
}

bool ProcessQuaternionAScalarMultiplication(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDC_BUTTON14)
	{
		quatA *= ReadFromEditBox(_hwnd, IDC_EDIT9);
		WriteAQuaternionValues(_hwnd, _wparam);

		return TRUE;
	}

	return FALSE;
}

bool ProcessQuaternionBScalarMultiplication(HWND& _hwnd, WPARAM& _wparam)
{
	if (_wparam == IDC_BUTTON15)
	{
		quatB *= ReadFromEditBox(_hwnd, IDC_EDIT9);
		WriteBQuaternionValues(_hwnd, _wparam);

		return TRUE;
	}

	return FALSE;
}

void WriteResultantQuaternionValues(HWND& _hwnd, WPARAM& _wparam)
{
	WriteToEditBox(_hwnd, IDC_EDIT10, quatResult.GetX());
	WriteToEditBox(_hwnd, IDC_EDIT11, quatResult.GetY());
	WriteToEditBox(_hwnd, IDC_EDIT12, quatResult.GetZ());
	WriteToEditBox(_hwnd, IDC_EDIT13, quatResult.GetW());
}

void WriteBQuaternionValues(HWND& _hwnd, WPARAM& _wparam)
{
	WriteToEditBox(_hwnd, IDC_EDIT5, quatB.GetX());
	WriteToEditBox(_hwnd, IDC_EDIT6, quatB.GetY());
	WriteToEditBox(_hwnd, IDC_EDIT7, quatB.GetZ());
	WriteToEditBox(_hwnd, IDC_EDIT8, quatB.GetW());
}

void WriteAQuaternionValues(HWND& _hwnd, WPARAM& _wparam)
{
	WriteToEditBox(_hwnd, IDC_EDIT1, quatA.GetX());
	WriteToEditBox(_hwnd, IDC_EDIT2, quatA.GetY());
	WriteToEditBox(_hwnd, IDC_EDIT3, quatA.GetZ());
	WriteToEditBox(_hwnd, IDC_EDIT4, quatA.GetW());
}