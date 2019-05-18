#ifndef MATRIX_H
#define MATRIX_H

#include <algorithm>
#include "QVector"
#include "QDataStream"

class matrix
{
    QVector<QVector<int>> matr;
public:
    matrix();
    matrix(int size);

    void set(int i, int j, int data);
    int size() const;
    int at(int i, int j) const;
    QVector<QVector<int>> get_matrix();
    void work();
//    QString to_string();

    operator QString();

    friend QDataStream& operator <<(QDataStream& stream, const matrix& m)
    {
        for (auto& row: m.matr)
        {
            for (int el: row)
            {
                stream << el;
            }
        }
        return stream;
    }
    friend QDataStream& operator >>(QDataStream& stream, matrix& m)
    {
        for (int i = 0; i < m.size(); ++i)
        {
            for (int j = 0; j < m.matr[i].size(); ++j)
            {
                int a;
                stream >> a;
                m.matr[i][j] = a;
            }
        }
        return stream;
    }
};

#endif // MATRIX_H
