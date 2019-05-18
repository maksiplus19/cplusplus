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

QVector<QVector<int> > matrix::get_matrix()
{
    return matr;
}

void matrix::work()
{
    int s = size();
    QVector<std::pair<int, QVector<int>>> sum(s);

    for (QVector<int> v: matr)
    {
        std::pair<int, QVector<int>> p(std::accumulate(v.begin(), v.end(), 0), v);
        sum.push_back(p);
    }

    std::sort(sum.begin(), sum.end(), [](std::pair<int, QVector<int>> left, std::pair<int, QVector<int>> right)
    {
        return left.first < right.first;
    });

    for (int i = 0; i < s; ++i)
    {
        matr[i] = sum[i].second;
    }
}

matrix::operator QString()
{
    QString res;
    for (auto v: matr)
    {
        for (int el: v)
        {
            res += QString::number(el) + " ";
        }
        res += "\n";
    }
    return res;
}

