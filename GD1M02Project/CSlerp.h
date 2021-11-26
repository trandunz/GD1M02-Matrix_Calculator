#pragma once
#ifndef _SLERP_H__
#define _SLERP_H__

#include <iostream>

#include "CQuaternion.h"
#include "CMatrix4.h"

static class CSlerp
{
public:
	static CQuaternion Slerp(CQuaternion& _qA, CQuaternion& _qB, float _t)
	{
		CQuaternion a = _qA;
		CQuaternion b = _qB;
		float theta = acosf(_qA.DotProduct(_qB) / (_qA.GetMagnitude() * _qB.GetMagnitude()));

		// Small Angle ? Lerp : Slerp
		if (theta <= 0.01f && theta >= -0.01f)
		{
			a.SetW(Lerp(a.GetW(), b.GetW(), _t));
			a.SetX(Lerp(a.GetX(), b.GetX(), _t));
			a.SetY(Lerp(a.GetY(), b.GetY(), _t));
			a.SetZ(Lerp(a.GetZ(), b.GetZ(), _t));
		}
		else
		{
			a *= (sinf((1 - _t) * theta)) / (sinf(theta));
			b *= (sinf(_t * theta)) / (sinf(theta));
			a += b;
		}

		return a;
	}

	static inline float Lerp(float _a, float _b, float _t)
	{
		if (_t <= 0.5f)
		{
			return _a + ((_b - _a) * _t);
		}
		else
		{
			return _b - ((_b - _a) * (1.0f - _t));
		}
	}
};
#endif

