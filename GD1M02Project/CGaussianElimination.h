#pragma once
#ifndef _GAUSSIAN_H__
#define _GAUSSIAN_H__

#include <iostream>

/// <summary>
/// RIPPED STRAIGHT FROM https://www.geeksforgeeks.org/gaussian-elimination/ 
/// JUST HERE AS A START SO WE CAN WORK OUT HOW TO DO IT
/// </summary>

class CGaussianElimination
{
public:

    inline CGaussianElimination()
    {
        SetZero();
    }

    inline CGaussianElimination& SetZero()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                m_Matrix[i][j] = 0.0f;
            }
        }

        return *this;
    }

    inline void SetRowAndColumn(int _i, int _j, float _value)
    {
        m_Matrix[_j][_j] = _value;
    }

    inline void MultiplyRowByScalar(int _i, float _scalar)
    {
        for (int j = 0; j < 4; j++)
        {
            m_Matrix[_i][j] *= _scalar;
        }
    }

    inline void RowAddition(float _scalar, int _row, int _row2)
    {
        float tempMatrix[3][4]{};
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                tempMatrix[i][j] = m_Matrix[i][j];
            }
        }
        
        for (int j = 0; j < 4; j++)
        {
            tempMatrix[_row][j] *= _scalar;
        }

        for (int j = 0; j < 4; j++)
        {
            m_Matrix[_row2][j] += tempMatrix[_row][j];
        }
    }

    inline void GuassianElimination()
    {
        /* reduction into r.e.f. */
        int singular_flag = ReduceMatrix();

        /* if matrix is singular */
        if (singular_flag != -1)
        {
            return;
        }

        /* get solution to system and print it using
           backward substitution */
        CalculateUnknowns();
    }

	inline int ReduceMatrix()
	{
        for (int k = 0; k < 3; k++)
        {
            // Initialize maximum value and index for pivot
            int i_max = k;
            int v_max = (int)m_Matrix[i_max][k];

            /* find greater amplitude for pivot if any */
            for (int i = k + 1; i < 3; i++)
                if (abs(m_Matrix[i][k]) > v_max)
                    v_max = m_Matrix[i][k], i_max = i;

            /* if a prinicipal diagonal element  is zero,
             * it denotes that m_Matrixrix is singular, and
             * will lead to a division-by-zero later. */
            if (!m_Matrix[k][i_max])
                return k; // m_Matrixrix is singular

            /* Swap the greatest value row with current row */
            if (i_max != k)
                SwapRow(k, i_max);


            for (int i = k + 1; i < 3; i++)
            {
                /* factor f to set current row kth element to 0,
                 * and subsequently remaining kth column to 0 */
                float f = m_Matrix[i][k] / m_Matrix[k][k];

                /* subtract fth multiple of corresponding kth
                   row element*/
                for (int j = k + 1; j <= 3; j++)
                    m_Matrix[i][j] -= m_Matrix[k][j] * f;

                /* filling lower triangular m_Matrixrix with zeros*/
                m_Matrix[i][k] = 0;
            }
        }

        return -1;
	}

    inline void CalculateUnknowns() 
    {
        float x[3];  // An array to store solution

        /* Start calculating from last equation up to the
            first */
        for (int i = 2; i >= 0; i--)
        {
            /* start with the RHS of the equation */
            x[i] = m_Matrix[i][3];

            /* Initialize j to i+1 since matrix is upper
               triangular*/
            for (int j = i + 1; j < 3; j++)
            {
                /* subtract all the lhs values
                 * except the coefficient of the variable
                 * whose value is being calculated */
                x[i] -= m_Matrix[i][j] * x[j];
            }

            /* divide the RHS by the coefficient of the
               unknown being calculated */
            x[i] = x[i] / m_Matrix[i][i];
        }
    }

    inline void SwapRow(int _i, int _i2)
    {
        for (int k = 0; k <= 3; k++)
        {
            float temp = m_Matrix[_i][k];
            m_Matrix[_i][k] = m_Matrix[_i2][k];
            m_Matrix[_i2][k] = temp;
        }
    }

private:
	float m_Matrix[3][4]{};
};
#endif _GAUSSIAN_H__
