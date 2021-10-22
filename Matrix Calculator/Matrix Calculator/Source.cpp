#include "CMatrix4.h"
#include <conio.h>

bool m_bExit = false;

/// <summary>
/// Main Implementation Function
/// </summary>
/// <returns></returns>
int main()
{
	CMatrix4 matrix;
	matrix(2, 2) = 1337;
	matrix.Print();

	// Main Returns NULL
	return NULL;
}

unsigned GetKeyboardInput()
{
	unsigned input;
	input = _getch();
	return input;
}

void Update()
{
	while (!m_bExit)
	{
		
	}
}

void Render()
{
	std::cout << 
}