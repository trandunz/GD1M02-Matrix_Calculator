#pragma once
#ifndef _MATRIX4_H__
#define _MATRIX4_H__

#include <iostream>


class CMatrix4
{
public:
    CMatrix4()
    {
        SetZero();
    }

    inline void Print()
    {
        int i = 0;
        int j = 0;

        for (i = 0; i < 4; i++)
        {
            for (j = 0; j < 4; j++)
            {
                std::cout << m_Data[i][j] << ",";
            }
            std::cout << std::endl;
        }
    }

    inline CMatrix4& SetZero()
    {
        int i = 0;
        int j = 0;

        for (i = 0; i < 4; i++)
        {
            for (j = 0; j < 4; j++)
            {
                m_Data[i][j] = 0;
            }
        }

        return *this;
    }

    inline CMatrix4& SetAsLinear()
    {
        SetZero();

        int i = 0;

        for (i = 0; i < 4; i++)
        {
            m_Data[i][i] = 1;
        }

        return *this;
    }

    inline CMatrix4& Transpose()
    {
        float copy[4][4]{  };
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                copy[i][j] = m_Data[j][i];
            }
        }

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                m_Data[i][j] = copy[i][j];
            }   
        }

        return *this;
    }

    inline float Determinant()
    {
        float c = 1;
        float det = 1;

        for (int i = 0; i < 4; i++) 
        {
            for (int j = i + 1; j < 4; j++) 
            {
                c = m_Data[j][i] / m_Data[i][i];

                for (int k = i; k < 4; k++)
                {
                    m_Data[j][k] = m_Data[j][k] - c * m_Data[i][k];
                }
            }
        }
        for (int i = 0; i < 4; i++)
        {
            det *= m_Data[i][i];
        }

        return det;
    }

    inline CMatrix4 LUDCInverse(CMatrix4 _matrix)
    {
        float sum = 0;
        int i = 0;
        int j = 0;
        int k = 0;

        for (i = 1; i < 4; i++)
        {
            _matrix(0,i) /= _matrix(0,0);
        }

        for (i = 1; i < 4; i++)
        {
            for (j = i; j < 4; j++)
            {
                sum = 0;
                for (k = 0; k < i; k++)
                {
                    sum += _matrix(j,k) * _matrix(k, i);
                }

                _matrix(j, i) -= sum;
            }
            if (i == 3)
            {
                continue;
            }
            for (j = i + 1; j < 4; j++)
            {
                sum = 0;
                for (int k = 0; k < i; k++)
                {
                    sum += _matrix(i, k) * _matrix(k, j);
                    _matrix(i, j) = (_matrix(i, j) - sum) / _matrix(i, i);
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
                        x -= _matrix(j, k) * _matrix(k, i);
                    }
                }

                _matrix(j, i) = x / _matrix(j, j);
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
                    sum = 0;
                    for (int k = i; k < j; k++)
                    {
                        if (i == k)
                        {
                            sum += _matrix(k, j);
                        }
                        else
                        {
                            sum += (_matrix(k, j) * _matrix(i, k));
                        }

                        _matrix(i, j) = -sum;
                    }
                }
            }
        }

        for (i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                sum = 0;
                for (int k = ((i > j) ? i : j); k < 4; k++)
                {
                    if (j == k)
                    {
                        sum += _matrix(k, i);
                    }
                    else
                    {
                        sum += (_matrix(j, k) * _matrix(k, i));
                    }

                    _matrix(j, i) = sum;
                } 
            }
        }

        return _matrix;
    }

    inline CMatrix4& operator = (CMatrix4 _rhs)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                m_Data[i][j] = _rhs(i,j);
            }
        }
        return *this;
    }
    
    inline float& operator () (int _row, int _column)
    {
        return m_Data[_row][_column];
    }

    inline CMatrix4& operator += (CMatrix4& _rhs)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                m_Data[i][j] += _rhs.m_Data[i][j];
            }
        }

        return *this;
    }

    inline CMatrix4& operator -= (CMatrix4& _rhs)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                m_Data[i][j] -= _rhs.m_Data[i][j];
            }
        }

        return *this;
    }

    inline CMatrix4& operator *= (CMatrix4& _rhs)
    {
        float result[4][4];

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                result[i][j] = 0;

                for (int k = 0; k < 4; k++)
                {
                    result[i][j] += m_Data[i][k] * _rhs.m_Data[k][j];
                }
            }
        }

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                m_Data[i][j] = result[i][j];
            }
        }

        return *this;
    }

    inline CMatrix4& operator * (float _scalar)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                m_Data[i][j] *= _scalar;
            }
        }

        return *this;
    }

private:
    float m_Data[4][4];
};
#endif
