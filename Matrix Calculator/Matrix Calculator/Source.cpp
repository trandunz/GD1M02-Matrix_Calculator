#include "CMatrix4.h"

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