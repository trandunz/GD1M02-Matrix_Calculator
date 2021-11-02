#pragma once
#ifndef _MATRIX4_H__
#define _MATRIX4_H__

#include <iostream>

class CMatrix4
{
public:
    inline CMatrix4()
    {
        SetToZero();
    }

    inline void Print()
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                std::cout << m_fData[i][j] << ',';
            }
            std::cout << std::endl;
        }
    }

    inline CMatrix4& SetToZero()
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                m_fData[i][j] = 0.0f;
            }
        }

        return *this;
    }

    inline CMatrix4& SetToIdentity()
    {
        SetToZero();

        for (int i = 0; i < 4; i++)
        {
            m_fData[i][i] = 1;
        }

        return *this;
    }

    inline CMatrix4& Transpose()
    {
        //Create a 4x4 array to store the data of the transposed matrix
        float fCopy[4][4];
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                fCopy[i][j] = m_fData[j][i];
            }
        }

        //Set the data in the 4x4 array to the matrix
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                m_fData[i][j] = fCopy[i][j];
            }
        }

        return *this;
    }

    inline float Determinant()
    {
        //Create a 4x4 array to store the data of the transposed matrix
        float fCopy[4][4];
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                fCopy[i][j] = m_fData[j][i];
            }
        }

        //Calculate the determinant
        float fResult = 1;

        for (int i = 0; i < 4; i++)
        {
            for (int k = i + 1; k < 4; k++)
            {
                float c = fCopy[k][i] / fCopy[i][i];
                for (int j = i; j < 4; j++)
                {
                    fCopy[k][j] = fCopy[k][j] - c * fCopy[i][j];
                }
            }
        }

        for (int i = 0; i < 4; i++)
        {
            fResult *= fCopy[i][i];
        }

        return fResult;
    }

    inline CMatrix4 LUDCInverse()
    {
        CMatrix4 mat4Result = *this;
        float fSum = 0;
        int i = 0;
        int j = 0;
        int k = 0;

        for (i = 1; i < 4; i++)
        {
            mat4Result.m_fData[0][i] /= mat4Result.m_fData[0][0];
        }

        for (i = 1; i < 4; i++)
        {
            for (j = i; j < 4; j++)
            {
                fSum = 0;
                for (k = 0; k < i; k++)
                {
                    fSum += mat4Result.m_fData[j][k] * mat4Result.m_fData[k][i];
                }

                mat4Result.m_fData[j][i] -= fSum;
            }
            if (i == 3)
            {
                continue;
            }
            for (j = i + 1; j < 4; j++)
            {
                fSum = 0;
                for (int k = 0; k < i; k++)
                {
                    fSum += mat4Result.m_fData[i][k] * mat4Result.m_fData[k][j];
                    mat4Result.m_fData[i][j] = (mat4Result.m_fData[i][j] - fSum) / mat4Result.m_fData[i][i];
                }
            }
        }

        float x = 1.0f;
        for (i = 0; i < 4; i++)
        {
            for (int j = i; j < 4; j++)
            {
                x = 1;
                if (i != j)
                {
                    x = 0;
                    for (int k = i; k < j; k++)
                    {
                        x -= mat4Result.m_fData[j][k] * mat4Result.m_fData[k][i];
                    }
                }

                mat4Result.m_fData[j][i] = x / mat4Result.m_fData[j][j];
            }
        }

        for (i = 0; i < 4; i++)
        {
            for (j = i; j < 4; j++)
            {
                if (i == j)
                {
                    continue;
                }
                else
                {
                    fSum = 0;
                    for (int k = i; k < j; k++)
                    {
                        if (i == k)
                        {
                            fSum += mat4Result.m_fData[k][j];
                        }
                        else
                        {
                            fSum += mat4Result.m_fData[k][j] * mat4Result.m_fData[i][k];
                        }

                        mat4Result.m_fData[i][j] = -fSum;
                    }
                }
            }
        }

        for (i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                fSum = 0;
                for (int k = ((i > j) ? i : j); k < 4; k++)
                {
                    if (j == k)
                    {
                        fSum += mat4Result.m_fData[k][i];
                    }
                    else
                    {
                        fSum += mat4Result.m_fData[j][k] * mat4Result.m_fData[k][i];
                    }

                    mat4Result.m_fData[j][i] = fSum;
                }
            }
        }

        return mat4Result;
    }

    inline CMatrix4& operator = (CMatrix4 _rhs)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                m_fData[i][j] = _rhs.m_fData[i][j];
            }
        }

        return *this;
    }

    inline float& operator () (int _i, int _jumn)
    {
        return m_fData[_i][_jumn];
    }

    inline CMatrix4 operator + (CMatrix4& _rhs)
    {
        CMatrix4 mat4Result = *this;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                mat4Result.m_fData[i][j] = m_fData[i][j] + _rhs.m_fData[i][j];
            }
        }

        return mat4Result;
    }

    inline CMatrix4& operator += (CMatrix4& _rhs)
    {
        *this = *this + _rhs;

        return *this;
    }

    inline CMatrix4 operator - (CMatrix4& _rhs)
    {
        CMatrix4 mat4Result = *this;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                mat4Result.m_fData[i][j] = m_fData[i][j] - _rhs.m_fData[i][j];
            }
        }

        return mat4Result;
    }

    inline CMatrix4& operator -= (CMatrix4& _rhs)
    {
        *this = *this - _rhs;

        return *this;
    }

    inline CMatrix4 operator * (CMatrix4& _rhs)
    {
        CMatrix4 mat4Result;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                for (int k = 0; k < 4; k++)
                {
                    mat4Result.m_fData[i][j] += m_fData[i][k] * _rhs.m_fData[k][j];
                }
            }
        }

        return mat4Result;
    }

    inline CMatrix4& operator *= (CMatrix4& _rhs)
    {
        *this = *this * _rhs;

        return *this;
    }

    inline CMatrix4 operator * (float _fScalar)
    {
        CMatrix4 mat4Result = *this;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                mat4Result.m_fData[i][j] *= _fScalar;
            }
        }

        return mat4Result;
    }

    inline CMatrix4& operator *= (float _fScalar)
    {
        *this = *this * _fScalar;

        return *this;
    }

private:
    float m_fData[4][4];
};
#endif