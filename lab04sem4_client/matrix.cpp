#include "matrix.h"

matrix::matrix()
{
    matr.resize(1);
    matr[0].resize(1);
}

matrix::matrix(int size)
{
    matr.resize(size);
    for (int i = 0; i<size; ++i) matr[i].resize(size);
}

void matrix::replace()
{
    for (int i = 0; i < size(); ++i)
        for (int j = i; j < size(); ++j)
            if (matr[i][j] < 0)
                matr[i][j] = 0;
}

void matrix::set(int i, int j, int data)
{
    matr[i][j] = data;
}

int matrix::size() const
{
    return matr.size();
}

int matrix::at(int i, int j) const
{
    return matr[i][j];
}

bool matrix::isSorted()
{
    if (size() < 2) return false;
    bool res = true;
    int t = matr[0][0];
    for (int i = 1; i < size(); ++i)
    {
        if (t > matr[i][i]) res = false;
        t = matr[i][i];
    }
    return res;
}

int matrix::sum()
{
    int res = 0;
    for (int i = 0; i < size(); ++i)
        for (int j = 0; j < size(); ++j)
        {
            res += matr[i][j];
        }
    return res;
}

QVector<QVector<int> > matrix::get_matrix()
{
    return matr;
}

