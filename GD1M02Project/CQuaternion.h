#pragma once
#include <cmath>

class CQuaternion
{
public:
	inline CQuaternion()
	{
		SetToZero();
	}

	inline void SetToZero()
	{
		m_fData[0] = 0;
		m_fData[1] = 0;
		m_fData[2] = 0;
		m_fData[3] = 0;
	}

	inline void SetToIdentity()
	{
		m_fData[0] = 1;
		m_fData[1] = 0;
		m_fData[2] = 0;
		m_fData[3] = 0;
	}

	inline void SetQuaternion(float _fW, float _fX, float _fY, float _fZ)
	{
		m_fData[0] = _fW;
		m_fData[1] = _fX;
		m_fData[2] = _fY;
		m_fData[3] = _fZ;
	}

	inline CQuaternion CrossProduct(CQuaternion& _rhs)
	{
		CQuaternion quatResult;
		float fTheta = 0;
		//Vector4 normal;

		// Magnitude() * _rhs.Magnitude() * sin(theta) * normal

		return quatResult;
	}

	inline CQuaternion GetInverse()
	{
		CQuaternion quatResult;
		float fMagnitude = GetMagnitude();

		if (fMagnitude != 0)
		{
			quatResult = GetConjugate();
			quatResult *= 1 / (fMagnitude * fMagnitude);
		}

		return quatResult;
	}

	inline CQuaternion UnitCrossProduct(CQuaternion& _rhs)
	{
		CQuaternion quatResult;

		quatResult.SetQuaternion(
			m_fData[2] * _rhs.m_fData[3] - m_fData[3] * _rhs.m_fData[2],
			m_fData[3] * _rhs.m_fData[1] - m_fData[1] * _rhs.m_fData[3],
			m_fData[1] * _rhs.m_fData[2] - m_fData[2] * _rhs.m_fData[1],
			m_fData[0] * _rhs.m_fData[0]);

		return quatResult;
	}

	inline float DotProduct(CQuaternion& _rhs)
	{
		return (m_fData[0] * _rhs.GetW()) + (m_fData[1] * _rhs.GetX()) + (m_fData[2] * _rhs.GetY()) + (m_fData[3] * _rhs.GetZ());
	}

	inline CQuaternion GetUnit()
	{
		CQuaternion quatResult;

		float fMagnitude = GetMagnitude();
		quatResult.SetQuaternion(
			m_fData[0] / fMagnitude,
			m_fData[1] / fMagnitude,
			m_fData[2] / fMagnitude,
			m_fData[3] / fMagnitude);

		return quatResult;
	}

	inline float GetMagnitude()
	{
		return sqrt
		(
			(m_fData[1] * m_fData[1]) +
			(m_fData[2] * m_fData[2]) +
			(m_fData[3] * m_fData[3]) +
			(m_fData[0] * m_fData[0]));
	}

	inline CQuaternion GetConjugate()
	{
		CQuaternion quatConjugate;
		quatConjugate.SetQuaternion(m_fData[0], -m_fData[1], -m_fData[2], -m_fData[3]);

		return quatConjugate;
	}

	inline float GetW() { return m_fData[0]; };
	inline float GetX() { return m_fData[1]; };
	inline float GetY() { return m_fData[2]; };
	inline float GetZ() { return m_fData[3]; };

	inline void SetW(float _value) { m_fData[0] = _value; };
	inline void SetX(float _value) { m_fData[1] = _value; };
	inline void SetY(float _value) { m_fData[2] = _value; };
	inline void SetZ(float _value) { m_fData[3] = _value; };

	inline CQuaternion& operator = (CQuaternion _rhs)
	{
		m_fData[0] = _rhs.GetW();
		m_fData[1] = _rhs.GetX();
		m_fData[2] = _rhs.GetY();
		m_fData[3] = _rhs.GetZ();

		return *this;
	}

	inline CMatrix4 InducedMatrix()
	{
		CMatrix4 mat4Result;

		mat4Result(0, 0) = (2.0f * m_fData[0] * m_fData[0]) - 1.0f + (2 * m_fData[1] * m_fData[1]);
		mat4Result(0, 1) = (2.0f * m_fData[1] * m_fData[2]) + (2.0f * m_fData[0] * m_fData[3]);
		mat4Result(0, 2) = (2.0f * m_fData[1] * m_fData[3]) - (2.0f * m_fData[0] * m_fData[2]);

		mat4Result(1, 0) = (2.0f * m_fData[1] * m_fData[2]) - (2.0f * m_fData[0] * m_fData[3]);
		mat4Result(1, 1) = (2.0f * m_fData[0] * m_fData[0]) - 1.0f + (2 * m_fData[2] * m_fData[2]);
		mat4Result(1, 2) = (2.0f * m_fData[2] * m_fData[3]) + (2.0f * m_fData[0] * m_fData[1]);

		mat4Result(2, 0) = (2.0f * m_fData[1] * m_fData[3]) + (2.0f * m_fData[0] * m_fData[2]);
		mat4Result(2, 1) = (2.0f * m_fData[2] * m_fData[3]) - (2.0f * m_fData[0] * m_fData[1]);
		mat4Result(2, 2) = (2.0f * m_fData[0] * m_fData[0]) - 1.0f + (2 * m_fData[3] * m_fData[3]);

		mat4Result(3, 3) = 1.0f;

		return mat4Result;
	}

	inline CQuaternion operator * (CQuaternion& _rhs)
	{
		CQuaternion quatResult;
		quatResult.SetQuaternion(
			(m_fData[0] * _rhs.GetW()) - (m_fData[1] * _rhs.GetX()) - (m_fData[2] * _rhs.GetY()) - (m_fData[3] * _rhs.GetZ()),
			(m_fData[0] * _rhs.GetX()) + (m_fData[1] * _rhs.GetW()) + (m_fData[2] * _rhs.GetZ()) - (m_fData[3] * _rhs.GetY()),
			(m_fData[0] * _rhs.GetY()) - (m_fData[1] * _rhs.GetZ()) + (m_fData[2] * _rhs.GetW()) + (m_fData[3] * _rhs.GetX()),
			(m_fData[0] * _rhs.GetZ()) + (m_fData[1] * _rhs.GetY()) - (m_fData[2] * _rhs.GetX()) + (m_fData[3] * _rhs.GetW()));
		
		return quatResult;
	}

	inline CQuaternion& operator *= (CQuaternion& _rhs)
	{
		*this = *this * _rhs;
		return *this;
	}

	inline CQuaternion operator * (float _fScalar)
	{
		CQuaternion quatResult;
		quatResult.SetQuaternion(m_fData[0] * _fScalar, m_fData[1] * _fScalar, m_fData[2] * _fScalar, m_fData[3] * _fScalar);
		return quatResult;
	}

	inline CQuaternion& operator *= (float _fScalar)
	{
		*this = *this * _fScalar;
		return *this;
	}

	inline CQuaternion operator + (CQuaternion& _rhs)
	{
		CQuaternion quatResult;
		quatResult.SetQuaternion(m_fData[0] + _rhs.GetW(), m_fData[1] + _rhs.GetX(), m_fData[2] + _rhs.GetY(), m_fData[3] + _rhs.GetZ());
		return quatResult;
	}

	inline CQuaternion& operator += (CQuaternion& _rhs)
	{
		*this = *this + _rhs;
		return *this;
	}

	inline CQuaternion operator - (CQuaternion& _rhs)
	{
		CQuaternion quatResult;
		quatResult.SetQuaternion(m_fData[0] - _rhs.GetW(), m_fData[1] - _rhs.GetX(), m_fData[2] - _rhs.GetY(), m_fData[3] - _rhs.GetZ());
		return quatResult;
	}

	inline CQuaternion& operator -= (CQuaternion& _rhs)
	{
		*this = *this - _rhs;
		return *this;
	}

	private:
		//m_fData[0] = w, m_fData[1] = x, m_fData[2] = y, m_fData[3] = z
		float m_fData[4];
};

