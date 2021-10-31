#include "CQuaternion.h"

void CQuaternion::SetZero()
{
	m_Quaternion.x = 0;
	m_Quaternion.y = 0;
	m_Quaternion.z = 0;
	m_Quaternion.w = 0;
}

void CQuaternion::SetIdentity()
{
	m_Quaternion.x = 0;
	m_Quaternion.y = 0;
	m_Quaternion.z = 0;
	m_Quaternion.w = 1;
}

void CQuaternion::SetQuaternion(float _r, float _i, float _j, float _k)
{
	m_Quaternion.x = _r;
	m_Quaternion.y = _i;
	m_Quaternion.z = _j;
	m_Quaternion.w = _k;
}

CQuaternion CQuaternion::Conjugate()
{
	CQuaternion conjugate;
	conjugate.SetQuaternion(m_Quaternion.x, -m_Quaternion.y, -m_Quaternion.z, -m_Quaternion.w);
	return conjugate;
}

CQuaternion::CQuaternion()
{
}
