#pragma once
#ifndef _TRANSFORMATION_H__
#define _TRANSFORMATION_H__

#include "CMatrix4.h"
#include <cmath>

static class CTransformation
{
public:
	static CMatrix4 Scale(float _fX, float _fY, float _fZ)
	{
		CMatrix4 mat4Result;
		mat4Result.SetToIdentity();
		
		mat4Result(0, 0) *= _fX;
		mat4Result(1, 1) *= _fY;
		mat4Result(2, 2) *= _fZ;

		return mat4Result;
	}
	
	static CMatrix4 Translation(float _fX, float _fY, float _fZ)
	{
		CMatrix4 mat4Result;
		mat4Result.SetToIdentity();

		mat4Result(0, 3) = _fX;
		mat4Result(1, 3) = _fY;
		mat4Result(2, 3) = _fZ;

		return mat4Result;
	}
	
	static CMatrix4 EulerRotation(unsigned int _iAxisOfRotation, float _fAngle, bool IsDeg = true)
	{
		//For _iAxisOfRotation, 0 = X-axis, 1 = Y-axis, 2 = Z-axis
		CMatrix4 mat4Result;
		mat4Result.SetToIdentity();
		
		if (IsDeg) { _fAngle *= 3.14159f / 180.0f; }

		switch (_iAxisOfRotation)
		{
		case 0:
			mat4Result(1, 1) = cosf(_fAngle);
			mat4Result(1, 2) = -sinf(_fAngle);
			mat4Result(2, 1) = sinf(_fAngle);
			mat4Result(2, 2) = cosf(_fAngle);
			break;
		case 1:
			mat4Result(0, 0) = cosf(_fAngle);
			mat4Result(0, 2) = sinf(_fAngle);
			mat4Result(2, 0) = -sinf(_fAngle);
			mat4Result(2, 2) = cosf(_fAngle);
			break;
		case 2:
			mat4Result(0, 0) = cosf(_fAngle);
			mat4Result(0, 1) = -sinf(_fAngle);
			mat4Result(1, 0) = sinf(_fAngle);
			mat4Result(1, 1) = cosf(_fAngle);
			break;
		}

		return mat4Result;
	}
	
	static CMatrix4 Projection(float _fDistanceFromViewer, float _fAngle)
	{
		//For _iAxisOfRotation, 0 = X-axis, 1 = Y-axis, 2 = Z-axis
		CMatrix4 mat4Result;
		mat4Result.SetToIdentity();

		mat4Result(3, 3) = 0;
		if (_fDistanceFromViewer != 0)
		{
			mat4Result(3, 2) = 1.0f / _fDistanceFromViewer;
		}
		else
		{
			mat4Result(3, 2) = 0.0f;
		}
		
		return mat4Result;
	}
};
#endif