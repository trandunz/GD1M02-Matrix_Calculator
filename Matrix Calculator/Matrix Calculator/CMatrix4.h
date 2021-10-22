#pragma once
#ifndef _MATRIX4_H__
#define _MATRIX4_H__

#include <iostream>

class CMatrix4
{
public:
    inline CMatrix4()
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                m_Data[i][j] = i * j;
            }
        }
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

    inline CMatrix4& SetAsUnitMatrix()
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
        int j = 0;

        for (i = 0; i < 4; i++)
        {
            m_Data[i][i] = 1;
        }

        return *this;
    }

    inline float& operator () (int _row, int _column)
    {
        return m_Data[_row][_column];
    }

    inline CMatrix4& operator += (const CMatrix4& _rhs)
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

    inline CMatrix4& operator -= (const CMatrix4& _rhs)
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

    inline CMatrix4& operator *= (const CMatrix4& _rhs)
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

private:
    float m_Data[4][4];
};
#endif
