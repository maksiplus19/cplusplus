#ifndef CURVESO_H
#define CURVESO_H
#include <QMessageBox>
#include <QString>
#include <vector>
#include <map>
#include <iostream>

namespace Curve {
enum CurveType {
    None = 0,
    Ellipse = 1,
    Parabola = 2,
    Hyperbola = 3,
    Circle = 4,
    Dot = 5,
    CrossLines = 6,
    Line = 7,
    ParallelLine = 9,
    UnDrawing = 10
};

struct curveStruct
{
    double coef;
    int deg;
    QString arg;
};
}

class CurveSO
{
private:
    int type;
    double coef[3][3];
    double delta;
    double D;
    double I;
    double B;
    QString name;

    void translate(QVector<double>&, QVector<double>&);
    void getCosSin(double &cos, double &sin);
public:
    int get_type();
    QString get_name();
    void set_name(QString);

    std::map<QString, double> get_invariants();
    std::pair<QVector<double>, QVector<double>> count(double minX, double maxX, double step=0.1);

    CurveSO();
    CurveSO(double a11, double a12, double a13, double a22, double a23, double a33, QString name);

    operator bool() const;

    friend std::ostream& operator<<(std::ostream& stream, const CurveSO& curve);
    friend std::istream& operator>>(std::istream& srteam, CurveSO& curve);
};

Q_DECLARE_METATYPE(CurveSO)

#endif // CURVESO_H
