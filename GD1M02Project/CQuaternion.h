#pragma once
#include <cmath>

class CQuaternion
{
public:
	struct Vector4
	{
		float x = 0;
		float y = 0;
		float z = 0;
		float w = 0;
	};

	CQuaternion();

	inline CQuaternion& operator = (CQuaternion& _rhs)
	{
		m_Quaternion.x = _rhs.GetReal();
		m_Quaternion.y = _rhs.GetI();
		m_Quaternion.z = _rhs.GetJ();
		m_Quaternion.w = _rhs.GetK();
		return *this;
	}

	inline CQuaternion operator * (CQuaternion& _rhs)
	{
		CQuaternion product;
		product.SetQuaternion(
			m_Quaternion.x * _rhs.GetJ() - m_Quaternion.z * _rhs.GetI() + m_Quaternion.x * _rhs.GetK() + m_Quaternion.w * _rhs.GetReal(),
			m_Quaternion.z * _rhs.GetReal() - m_Quaternion.x * _rhs.GetJ() + m_Quaternion.y * _rhs.GetK() + m_Quaternion.w * _rhs.GetI(),
			m_Quaternion.x * _rhs.GetI() - m_Quaternion.y * _rhs.GetReal() + m_Quaternion.z * _rhs.GetK() + m_Quaternion.w * _rhs.GetJ(),
			m_Quaternion.w * _rhs.GetK() - m_Quaternion.x * _rhs.GetReal() - m_Quaternion.y * _rhs.GetI() - m_Quaternion.z * _rhs.GetJ());
		return product;
	}
	inline CQuaternion& operator * (float _scalar)
	{
		SetQuaternion(m_Quaternion.x * _scalar, m_Quaternion.y * _scalar, m_Quaternion.z * _scalar, m_Quaternion.w * _scalar);
		return *this;
	}

	inline CQuaternion operator + (CQuaternion& _rhs)
	{
		CQuaternion product;
		product.SetQuaternion(m_Quaternion.x + _rhs.GetReal(), m_Quaternion.y + _rhs.GetI(), m_Quaternion.z + _rhs.GetJ(), m_Quaternion.w + _rhs.GetK());
		return product;
	}
	inline CQuaternion operator - (CQuaternion& _rhs)
	{
		CQuaternion product;
		product.SetQuaternion(m_Quaternion.x - _rhs.GetReal(), m_Quaternion.y - _rhs.GetI(), m_Quaternion.z - _rhs.GetJ(), m_Quaternion.w - _rhs.GetK());
		return product;
	}


	void SetZero();
	void SetIdentity();
	void SetQuaternion(float _r, float _i, float _j, float _k);

	inline CQuaternion CrossProduct(CQuaternion& _rhs)
	{
		CQuaternion product;
		float theta = 0;
		Vector4 normal;

		// Magnitude() * _rhs.Magnitude() * sin(theta) * normal

		return product;
	}

	inline CQuaternion UnitCrossProduct(CQuaternion& _rhs)
	{
		CQuaternion product;
		product.SetQuaternion(
			m_Quaternion.y * _rhs.m_Quaternion.z - m_Quaternion.z * _rhs.m_Quaternion.y,
			m_Quaternion.z * _rhs.m_Quaternion.x - m_Quaternion.x * _rhs.m_Quaternion.z,
			m_Quaternion.x * _rhs.m_Quaternion.y - m_Quaternion.y * _rhs.m_Quaternion.x,
			m_Quaternion.w * _rhs.m_Quaternion.w);
		return product;
	}

	inline float Magnitude() 
	{
		return sqrt((m_Quaternion.x * m_Quaternion.x) + (m_Quaternion.y * m_Quaternion.y) + (m_Quaternion.z * m_Quaternion.z) + (m_Quaternion.w * m_Quaternion.w));
	}

	CQuaternion Conjugate();

	inline float GetReal() { return m_Quaternion.x; };
	inline float GetI() { return m_Quaternion.y; };
	inline float GetJ() { return m_Quaternion.z; };
	inline float GetK() { return m_Quaternion.w; };

	inline float SetReal(float _value) { m_Quaternion.x = _value; };
	inline float SetI(float _value) { m_Quaternion.y = _value; };
	inline float SetJ(float _value) { m_Quaternion.z = _value; };
	inline float SetK(float _value) { m_Quaternion.w = _value; };

	Vector4 m_Quaternion;
};

