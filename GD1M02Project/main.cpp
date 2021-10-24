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

void MakeWindow(HWND& hwnd, HINSTANCE& _hInstance);
void InitHWND(WNDCLASSEX& winclass, HINSTANCE& _hInstance);

void SetupModelessDBoxes(HWND& hwnd, HINSTANCE& _hInstance);

void Update(MSG& msg);

void TranslateAndDispatchMessage(MSG& msg);

bool ProcessInputFields(HWND& _hwnd, WPARAM& _wparam);
void ProcessMatAInput(HWND& _hwnd, WPARAM& _wparam);
void ProcessMatrixBInput(HWND& _hwnd, WPARAM& _wparam);
void ProcessAdditionInput(HWND& _hwnd, WPARAM& _wparam);
void ProcessMinusInput(HWND& _hwnd, WPARAM& _wparam);
void ProcessMultiplyInput(HWND& _hwnd, WPARAM& _wparam);
void ProcessInverseMultiplyInput(HWND& _hwnd, WPARAM& _wparam);
void ProcessBToIdentity(HWND& _hwnd, WPARAM& _wparam);
void ProcessBTranspose(HWND& _hwnd, WPARAM& _wparam);
void ProcessATranspose(HWND& _hwnd, WPARAM& _wparam);
void ProcessAToIdentity(HWND& _hwnd, WPARAM& _wparam);
void ProcessBDeterminant(HWND& _hwnd, WPARAM& _wparam);
void ProcessADeterminant(HWND& _hwnd, WPARAM& _wparam);
void ProcessBInverse(HWND& _hwnd, WPARAM& _wparam);
void ProcessAInverse(HWND& _hwnd, WPARAM& _wparam);
void ProcessScalarMultiplication(HWND& _hwnd, WPARAM& _wparam);

void WriteResultantMatrixValues(HWND& _hwnd, WPARAM& _wparam);
void WriteBMatrixValues(HWND& _hwnd, WPARAM& _wparam);
void WriteAMatrixValues(HWND& _hwnd, WPARAM& _wparam);

HMENU g_hMenu;
HWND g_hDlgMatrix, g_hDlgTransformation, g_hDlgGaussian, g_hDlgQuaternion, g_hDlgSLERP;

// The Three Matricies
CMatrix4 matrixA, matrixB, resultantMat;

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
		default:
			break;
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

	default:
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
	static float _value;

	switch (_msg)
	{
	case WM_COMMAND:
	{
		if (ProcessInputFields(_hwnd, _wparam))
		{
			ProcessAdditionInput(_hwnd, _wparam);
			ProcessMinusInput(_hwnd, _wparam);
			ProcessMultiplyInput(_hwnd, _wparam);
			ProcessInverseMultiplyInput(_hwnd, _wparam);
			ProcessBToIdentity(_hwnd, _wparam);
			ProcessBTranspose(_hwnd, _wparam);
			ProcessATranspose(_hwnd, _wparam);
			ProcessAToIdentity(_hwnd, _wparam);
			ProcessBDeterminant(_hwnd, _wparam);
			ProcessADeterminant(_hwnd, _wparam);
			ProcessBInverse(_hwnd, _wparam);
			ProcessAInverse(_hwnd, _wparam);
			ProcessScalarMultiplication(_hwnd, _wparam);

			return TRUE;
		}
	}
	case WM_CLOSE:
	{
		MessageBox(_hwnd, ToWideString(_value).c_str(), L"Default Value", MB_OK);
		ShowWindow(_hwnd, SW_HIDE);

		return TRUE;
		break;
	}
	default:
		break;
	}

	return FALSE;
}
BOOL CALLBACK TransformationDlgProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam)
{

	switch (_msg)
	{
	
	case WM_COMMAND:
	{
		switch (LOWORD(_wparam))
		{

		default:
			break;
		}
		
	return TRUE;
	break;

	}
	case WM_CLOSE:
	{
		ShowWindow(_hwnd, SW_HIDE);
		return TRUE;
		break;
	}
	default:
		break;
	}
	return FALSE;
}
BOOL CALLBACK GaussianDlgProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam)
{

	switch (_msg)
	{
	case WM_COMMAND:
	{
		switch (LOWORD(_wparam))
		{

		default:
			break;
		}

		return TRUE;
		break;

	}
	case WM_CLOSE:
	{
		ShowWindow(_hwnd, SW_HIDE);
		return TRUE;
		break;
	}
	default:
		break;
	}
	return FALSE;
}
BOOL CALLBACK QuaternionDlgProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam)
{

	switch (_msg)
	{
	case WM_COMMAND:
	{
		switch (LOWORD(_wparam))
		{

		default:
			break;
		}

		return TRUE;
		break;

	}
	case WM_CLOSE:
	{
		ShowWindow(_hwnd, SW_HIDE);
		return TRUE;
		break;
	}
	default:
		break;
	}
	return FALSE;
}
BOOL CALLBACK SLERPDlgProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam)	
{

	switch (_msg)
	{
	case WM_COMMAND:
	{
		switch (LOWORD(_wparam))
		{

		default:
			break;
		}

		return TRUE;
		break;
	}
	case WM_CLOSE:
	{
		ShowWindow(_hwnd, SW_HIDE);
		return TRUE;
		break;
	}
	default:
		break;
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

bool ProcessInputFields(HWND& _hwnd, WPARAM& _wparam)
{
	ProcessMatAInput(_hwnd, _wparam);
	ProcessMatrixBInput(_hwnd, _wparam);

	return TRUE;
}

void ProcessMatAInput(HWND& _hwnd, WPARAM& _wparam)
{
	switch ((LOWORD(_wparam)))
	{
	case IDC_EDIT_A11:
	{
		matrixA(0, 0) = ReadFromEditBox(_hwnd, IDC_EDIT_A11);
		break;
	}
	case IDC_EDIT_A12:
	{
		matrixA(0, 1) = ReadFromEditBox(_hwnd, IDC_EDIT_A12);
		break;
	}
	case IDC_EDIT_A13:
	{
		matrixA(0, 2) = ReadFromEditBox(_hwnd, IDC_EDIT_A13);
		break;
	}
	case IDC_EDIT_A14:
	{
		matrixA(0, 3) = ReadFromEditBox(_hwnd, IDC_EDIT_A14);
		break;
	}
	case IDC_EDIT_A21:
	{
		matrixA(1, 0) = ReadFromEditBox(_hwnd, IDC_EDIT_A21);
		break;
	}
	case IDC_EDIT_A22:
	{
		matrixA(1, 1) = ReadFromEditBox(_hwnd, IDC_EDIT_A22);
		break;
	}
	case IDC_EDIT_A23:
	{
		matrixA(1, 2) = ReadFromEditBox(_hwnd, IDC_EDIT_A23);
		break;
	}
	case IDC_EDIT_A24:
	{
		matrixA(1, 3) = ReadFromEditBox(_hwnd, IDC_EDIT_A24);
		break;
	}
	case IDC_EDIT_A31:
	{
		matrixA(2, 0) = ReadFromEditBox(_hwnd, IDC_EDIT_A31);
		break;
	}
	case IDC_EDIT_A32:
	{
		matrixA(2, 1) = ReadFromEditBox(_hwnd, IDC_EDIT_A32);
		break;
	}
	case IDC_EDIT_A33:
	{
		matrixA(2, 2) = ReadFromEditBox(_hwnd, IDC_EDIT_A33);
		break;
	}
	case IDC_EDIT_A34:
	{
		matrixA(2, 3) = ReadFromEditBox(_hwnd, IDC_EDIT_A34);
		break;
	}
	case IDC_EDIT_A41:
	{
		matrixA(3, 0) = ReadFromEditBox(_hwnd, IDC_EDIT_A41);
		break;
	}
	case IDC_EDIT_A42:
	{
		matrixA(3, 1) = ReadFromEditBox(_hwnd, IDC_EDIT_A42);
		break;
	}
	case IDC_EDIT_A43:
	{
		matrixA(3, 2) = ReadFromEditBox(_hwnd, IDC_EDIT_A43);
		break;
	}
	case IDC_EDIT_A44:
	{
		matrixA(3, 3) = ReadFromEditBox(_hwnd, IDC_EDIT_A44);
		break;
	}
	default:
		break;
	}
}

void ProcessMatrixBInput(HWND& _hwnd, WPARAM& _wparam)
{
	switch ((LOWORD(_wparam)))
	{
	case IDC_EDIT_B11:
	{
		matrixB(0, 0) = ReadFromEditBox(_hwnd, IDC_EDIT_B11);
		break;
	}
	case IDC_EDIT_B12:
	{
		matrixB(0, 1) = ReadFromEditBox(_hwnd, IDC_EDIT_B12);
		break;
	}
	case IDC_EDIT_B13:
	{
		matrixB(0, 2) = ReadFromEditBox(_hwnd, IDC_EDIT_B13);
		break;
	}
	case IDC_EDIT_B14:
	{
		matrixB(0, 3) = ReadFromEditBox(_hwnd, IDC_EDIT_B14);
		break;
	}
	case IDC_EDIT_B21:
	{
		matrixB(1, 0) = ReadFromEditBox(_hwnd, IDC_EDIT_B21);
		break;
	}
	case IDC_EDIT_B22:
	{
		matrixB(1, 1) = ReadFromEditBox(_hwnd, IDC_EDIT_B22);
		break;
	}
	case IDC_EDIT_B23:
	{
		matrixB(1, 2) = ReadFromEditBox(_hwnd, IDC_EDIT_B23);
		break;
	}
	case IDC_EDIT_B24:
	{
		matrixB(1, 3) = ReadFromEditBox(_hwnd, IDC_EDIT_B24);
		break;
	}
	case IDC_EDIT_B31:
	{
		matrixB(2, 0) = ReadFromEditBox(_hwnd, IDC_EDIT_B31);
		break;
	}
	case IDC_EDIT_B32:
	{
		matrixB(2, 1) = ReadFromEditBox(_hwnd, IDC_EDIT_B32);
		break;
	}
	case IDC_EDIT_B33:
	{
		matrixB(2, 2) = ReadFromEditBox(_hwnd, IDC_EDIT_B33);
		break;
	}
	case IDC_EDIT_B34:
	{
		matrixB(2, 3) = ReadFromEditBox(_hwnd, IDC_EDIT_B34);
		break;
	}
	case IDC_EDIT_B41:
	{
		matrixB(3, 0) = ReadFromEditBox(_hwnd, IDC_EDIT_B41);
		break;
	}
	case IDC_EDIT_B42:
	{
		matrixB(3, 1) = ReadFromEditBox(_hwnd, IDC_EDIT_B42);
		break;
	}
	case IDC_EDIT_B43:
	{
		matrixB(3, 2) = ReadFromEditBox(_hwnd, IDC_EDIT_B43);
		break;
	}
	case IDC_EDIT_B44:
	{
		matrixB(3, 3) = ReadFromEditBox(_hwnd, IDC_EDIT_B44);
		break;
	}
	default:
		break;
	}
}

void ProcessAdditionInput(HWND& _hwnd, WPARAM& _wparam)
{
	switch (_wparam)
	{
	case IDOK:
	{
		resultantMat.SetZero();
		resultantMat = matrixA;
		resultantMat += matrixB;

		WriteResultantMatrixValues(_hwnd, _wparam);
		break;
	}
	default:
		break;
	}
}

void ProcessMinusInput(HWND& _hwnd, WPARAM& _wparam)
{
	switch (_wparam)
	{
	case IDCANCEL:
	{
		resultantMat.SetZero();
		resultantMat = matrixA;
		resultantMat -= matrixB;

		WriteResultantMatrixValues(_hwnd, _wparam);
		break;
	}
	default:
		break;
	}
}

void ProcessMultiplyInput(HWND& _hwnd, WPARAM& _wparam)
{
	switch (_wparam)
	{
	case IDOK2:
	{
		resultantMat.SetZero();
		resultantMat = matrixA;
		resultantMat *= matrixB;

		WriteResultantMatrixValues(_hwnd, _wparam);
		break;
	}
	default:
		break;
	}
}

void ProcessInverseMultiplyInput(HWND& _hwnd, WPARAM& _wparam)
{
	switch (_wparam)
	{
	case IDOK5:
	{
		resultantMat.SetZero();
		resultantMat = matrixB;
		resultantMat *= matrixA;

		WriteResultantMatrixValues(_hwnd, _wparam);
		break;
	}
	default:
		break;
	}
}

void ProcessBToIdentity(HWND& _hwnd, WPARAM& _wparam)
{
	switch (_wparam)
	{
	case IDOK8:
	{
		matrixB.SetAsLinear();

		WriteToEditBox(_hwnd, IDC_EDIT_B11, matrixB(0, 0));
		WriteToEditBox(_hwnd, IDC_EDIT_B12, matrixB(0, 1));
		WriteToEditBox(_hwnd, IDC_EDIT_B13, matrixB(0, 2));
		WriteToEditBox(_hwnd, IDC_EDIT_B14, matrixB(0, 3));
		WriteToEditBox(_hwnd, IDC_EDIT_B21, matrixB(1, 0));
		WriteToEditBox(_hwnd, IDC_EDIT_B22, matrixB(1, 1));
		WriteToEditBox(_hwnd, IDC_EDIT_B23, matrixB(1, 2));
		WriteToEditBox(_hwnd, IDC_EDIT_B24, matrixB(1, 3));
		WriteToEditBox(_hwnd, IDC_EDIT_B31, matrixB(2, 0));
		WriteToEditBox(_hwnd, IDC_EDIT_B32, matrixB(2, 1));
		WriteToEditBox(_hwnd, IDC_EDIT_B33, matrixB(2, 2));
		WriteToEditBox(_hwnd, IDC_EDIT_B34, matrixB(2, 3));
		WriteToEditBox(_hwnd, IDC_EDIT_B41, matrixB(3, 0));
		WriteToEditBox(_hwnd, IDC_EDIT_B42, matrixB(3, 1));
		WriteToEditBox(_hwnd, IDC_EDIT_B43, matrixB(3, 2));
		WriteToEditBox(_hwnd, IDC_EDIT_B44, matrixB(3, 3));
		break;
	}
	default:
		break;
	}
}

void ProcessBTranspose(HWND& _hwnd, WPARAM& _wparam)
{
	switch (_wparam)
	{
	case IDOK11:
	{
		matrixB.Transpose();

		WriteBMatrixValues(_hwnd, _wparam);
		break;
	}
	default:
		break;
	}
}

void ProcessATranspose(HWND& _hwnd, WPARAM& _wparam)
{
	switch (_wparam)
	{
	case IDOK9:
	{
		matrixA.Transpose();

		WriteAMatrixValues(_hwnd, _wparam);
		break;
	}
	default:
		break;
	}
}

void ProcessAToIdentity(HWND& _hwnd, WPARAM& _wparam)
{
	switch (_wparam)
	{
	case IDOK4:
	{
		matrixA.SetAsLinear();

		WriteAMatrixValues(_hwnd, _wparam);
		break;
	}
	default:
		break;
	}
}

void ProcessBDeterminant(HWND& _hwnd, WPARAM& _wparam)
{
	switch (_wparam)
	{
	case IDOK7:
	{
		WriteToEditBox(_hwnd, IDC_EDIT_DetB, matrixB.Determinant());
		break;
	}
	default:
		break;
	}
}

void ProcessADeterminant(HWND& _hwnd, WPARAM& _wparam)
{
	switch (_wparam)
	{
	case IDOK3:
	{
		WriteToEditBox(_hwnd, IDC_EDIT_DetA, matrixA.Determinant());
		break;
	}
	default:
		break;
	}
}

void ProcessBInverse(HWND& _hwnd, WPARAM& _wparam)
{
	switch (_wparam)
	{
	case IDCANCEL3:
	{
		resultantMat = matrixB.LUDCInverse(matrixB);
		WriteResultantMatrixValues(_hwnd, _wparam);
		break;
	}
	default:
		break;
	}
}

void ProcessAInverse(HWND& _hwnd, WPARAM& _wparam)
{
	switch (_wparam)
	{
	case IDCANCEL2:
	{
		resultantMat = matrixA.LUDCInverse(matrixA);
		WriteResultantMatrixValues(_hwnd, _wparam);
		break;
	}
	default:
		break;
	}
}

void ProcessScalarMultiplication(HWND& _hwnd, WPARAM& _wparam)
{
	switch (LOWORD(_wparam))
	{
	case IDOK6:
	{
		matrixA = matrixA * ReadFromEditBox(_hwnd, IDC_EDIT_AScaled);
		WriteAMatrixValues(_hwnd, _wparam);
		break;
	}
	case IDOK10:
	{

		matrixB = matrixB * ReadFromEditBox(_hwnd, IDC_EDIT_BScaled);
		WriteBMatrixValues(_hwnd, _wparam);
		break;
	}
	default:
		break;
	}
}

void WriteResultantMatrixValues(HWND& _hwnd, WPARAM& _wparam)
{
	WriteToEditBox(_hwnd, IDC_EDIT_R11, resultantMat(0, 0));
	WriteToEditBox(_hwnd, IDC_EDIT_R12, resultantMat(0, 1));
	WriteToEditBox(_hwnd, IDC_EDIT_R13, resultantMat(0, 2));
	WriteToEditBox(_hwnd, IDC_EDIT_R14, resultantMat(0, 3));
	WriteToEditBox(_hwnd, IDC_EDIT_R21, resultantMat(1, 0));
	WriteToEditBox(_hwnd, IDC_EDIT_R22, resultantMat(1, 1));
	WriteToEditBox(_hwnd, IDC_EDIT_R23, resultantMat(1, 2));
	WriteToEditBox(_hwnd, IDC_EDIT_R24, resultantMat(1, 3));
	WriteToEditBox(_hwnd, IDC_EDIT_R31, resultantMat(2, 0));
	WriteToEditBox(_hwnd, IDC_EDIT_R32, resultantMat(2, 1));
	WriteToEditBox(_hwnd, IDC_EDIT_R33, resultantMat(2, 2));
	WriteToEditBox(_hwnd, IDC_EDIT_R34, resultantMat(2, 3));
	WriteToEditBox(_hwnd, IDC_EDIT_R41, resultantMat(3, 0));
	WriteToEditBox(_hwnd, IDC_EDIT_R42, resultantMat(3, 1));
	WriteToEditBox(_hwnd, IDC_EDIT_R43, resultantMat(3, 2));
	WriteToEditBox(_hwnd, IDC_EDIT_R44, resultantMat(3, 3));
}

void WriteBMatrixValues(HWND& _hwnd, WPARAM& _wparam)
{
	WriteToEditBox(_hwnd, IDC_EDIT_B11, matrixB(0, 0));
	WriteToEditBox(_hwnd, IDC_EDIT_B12, matrixB(0, 1));
	WriteToEditBox(_hwnd, IDC_EDIT_B13, matrixB(0, 2));
	WriteToEditBox(_hwnd, IDC_EDIT_B14, matrixB(0, 3));
	WriteToEditBox(_hwnd, IDC_EDIT_B21, matrixB(1, 0));
	WriteToEditBox(_hwnd, IDC_EDIT_B22, matrixB(1, 1));
	WriteToEditBox(_hwnd, IDC_EDIT_B23, matrixB(1, 2));
	WriteToEditBox(_hwnd, IDC_EDIT_B24, matrixB(1, 3));
	WriteToEditBox(_hwnd, IDC_EDIT_B31, matrixB(2, 0));
	WriteToEditBox(_hwnd, IDC_EDIT_B32, matrixB(2, 1));
	WriteToEditBox(_hwnd, IDC_EDIT_B33, matrixB(2, 2));
	WriteToEditBox(_hwnd, IDC_EDIT_B34, matrixB(2, 3));
	WriteToEditBox(_hwnd, IDC_EDIT_B41, matrixB(3, 0));
	WriteToEditBox(_hwnd, IDC_EDIT_B42, matrixB(3, 1));
	WriteToEditBox(_hwnd, IDC_EDIT_B43, matrixB(3, 2));
	WriteToEditBox(_hwnd, IDC_EDIT_B44, matrixB(3, 3));
}

void WriteAMatrixValues(HWND& _hwnd, WPARAM& _wparam)
{
	WriteToEditBox(_hwnd, IDC_EDIT_A11, matrixA(0, 0));
	WriteToEditBox(_hwnd, IDC_EDIT_A12, matrixA(0, 1));
	WriteToEditBox(_hwnd, IDC_EDIT_A13, matrixA(0, 2));
	WriteToEditBox(_hwnd, IDC_EDIT_A14, matrixA(0, 3));
	WriteToEditBox(_hwnd, IDC_EDIT_A21, matrixA(1, 0));
	WriteToEditBox(_hwnd, IDC_EDIT_A22, matrixA(1, 1));
	WriteToEditBox(_hwnd, IDC_EDIT_A23, matrixA(1, 2));
	WriteToEditBox(_hwnd, IDC_EDIT_A24, matrixA(1, 3));
	WriteToEditBox(_hwnd, IDC_EDIT_A31, matrixA(2, 0));
	WriteToEditBox(_hwnd, IDC_EDIT_A32, matrixA(2, 1));
	WriteToEditBox(_hwnd, IDC_EDIT_A33, matrixA(2, 2));
	WriteToEditBox(_hwnd, IDC_EDIT_A34, matrixA(2, 3));
	WriteToEditBox(_hwnd, IDC_EDIT_A41, matrixA(3, 0));
	WriteToEditBox(_hwnd, IDC_EDIT_A42, matrixA(3, 1));
	WriteToEditBox(_hwnd, IDC_EDIT_A43, matrixA(3, 2));
	WriteToEditBox(_hwnd, IDC_EDIT_A44, matrixA(3, 3));
}
