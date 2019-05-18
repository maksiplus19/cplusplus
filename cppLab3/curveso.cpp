#include "curveso.h"

void CurveSO::translate(QVector<double> &X, QVector<double> &Y)
{
    double x, y, cos, sin, x_sh, y_sh;

    getCosSin(cos, sin);

    if (type==Curve::Parabola)
    {
        if (coef[0][0])
        {
            x = -coef[0][2]/(2*coef[0][0]);
            y = -(coef[0][2]*coef[0][2] - 4*coef[0][0]*coef[2][2])/(4*coef[0][0]);
        }
        else
        {
            x = -coef[1][2]/(2*coef[1][1]);
            y = -(coef[1][2]*coef[1][2] - 4*coef[1][1]*coef[2][2])/(4*coef[1][1]);
        }
    }
    else
    {
        x = (coef[0][1]*coef[1][2]-coef[0][2]*coef[1][1]) / D;
        y = (coef[0][2]*coef[0][1]-coef[0][0]*coef[1][2]) / D;
    }

    for (int i = 0; i<X.size(); ++i)
    {
        x_sh = X[i]*cos + Y[i]*sin;
        y_sh = Y[i]*cos - X[i]*sin;

        X[i] = x + x_sh;
        Y[i] = y + y_sh;
    }
}

void CurveSO::getCosSin(double &cos, double &sin)
{
    double lambda1, lambda2, discr;
    discr = std::sqrt(I*I - 4*D);
    lambda1 = (I + discr)/2;
    lambda2 = (I - discr)/2;
    if (abs(lambda1) > abs(lambda2) && type != Curve::Ellipse) std::swap(lambda1, lambda2);
    if (coef[0][1]==0 && coef[0][0] == lambda1)
    {
        cos = 1;
        sin = 0;
        return;
    }
    if (coef[0][1] != 0 || coef[0][0] != lambda1)
    {
        cos = coef[0][1] / (std::sqrt( std::pow(lambda1-coef[0][0], 2) + coef[0][1]*coef[0][1] ));
        sin = (lambda1 - coef[0][0]) / (std::sqrt(std::pow(lambda1-coef[0][0], 2) + coef[0][1]*coef[0][1]));
    }
    else
    {
        QMessageBox::warning(nullptr, "Ошибка", "Невозможно посчитать поворот");
        return;
    }
}

int CurveSO::get_type()
{
    return type;
}

QString CurveSO::get_name()
{
    return name;
}

void CurveSO::set_name(QString s)
{
    name = s;
}

std::map<QString, double> CurveSO::get_invariants()
{
    std::map<QString, double> map;
    map.insert(std::pair<QString, double>("delta", delta));
    map.insert(std::pair<QString, double>("D", D));
    map.insert(std::pair<QString, double>("I", I));
    map.insert(std::pair<QString, double>("B", B));
    return map;
}

CurveSO::CurveSO()
{
    this->type = Curve::None;
}

CurveSO::CurveSO(double a11, double a12, double a13, double a22, double a23, double a33, QString name)
{
    this->name = name;

    this->coef[0][0] = a11;
    this->coef[0][1] = this->coef[1][0] = a12 = a12/2;
    this->coef[0][2] = this->coef[2][0] = a13 = a13/2;
    this->coef[1][1] = a22;
    this->coef[1][2] = this->coef[2][1] = a23 = a23/2;
    this->coef[2][2] = a33;

    this->delta = a11*a22*a33 + a12*a23*a13 + a13*a12*a23 - (a13*a22*a13 + a12*a12*a33 + a23*a23*a11);
    this->D = a11*a22 - a12*a12;
    this->I = a11 + a22;
    this->B = a11*a33 - a13*a13 + a22*a33 - a23*a23;

    if (this->delta != 0)
    {
        if (this->D > 0 && this->delta*this->I < 0)
            if (this->I*this->I == 4*this->D)this->type = Curve::Circle;
                    else this->type = Curve::Ellipse;
        else if (this->D > 0 && this->delta*this->I > 0) this->type = Curve::UnDrawing;
        else if (this->D < 0) this->type = Curve::Hyperbola;
        else if (this->D == 0) this->type = Curve::Parabola;
        else this->type = Curve::None;
    }
    else
    {
        this->name = Curve::UnDrawing;
    }

    if (this->type == Curve::None) QMessageBox::about(nullptr, "Ошибка", "Не удалось Определить тип кривой");
}

std::ostream &operator<<(std::ostream &stream, const CurveSO& curve)
{
    stream << curve.coef[0][0] << " " << curve.coef[0][1] << " " << curve.coef[0][2] << " " <<
                                   curve.coef[1][1] << " " << curve.coef[1][2] << " " <<
                                                              curve.coef[2][2] << " " << std::endl;
    return stream;
}

std::istream &operator>>(std::istream &stream, CurveSO& curve)
{
    stream >> curve.coef[0][0] >> curve.coef[0][1] >> curve.coef[0][2] >>
                                  curve.coef[1][1] >> curve.coef[1][2] >>
                                                      curve.coef[2][2];
    return stream;
}

CurveSO::operator bool() const
{
    int sum = 0;
    for (int i=0; i<3; i++)
    {
        for (int j=0; j<3; j++)
        {
            sum += abs(coef[i][j]);
        }
    }
    return sum;
}

std::pair<QVector<double>, QVector<double> > CurveSO::count(double minX, double maxX, double step)
{
    QVector<double> X, Y;
    if (type == Curve::UnDrawing || type == Curve::None)
        return std::pair<QVector<double>, QVector<double>>(X, Y);
    double a, b, lambda1, lambda2, discr, y, p;
    discr = std::sqrt(I*I - 4*D);
    lambda1 = (I + discr)/2;
    lambda2 = (I - discr)/2;
    if (abs(lambda1) > abs(lambda2)) std::swap(lambda1, lambda2);
    switch (this->type) {
    case Curve::Ellipse: case Curve::Circle:
        a = std::sqrt((-1/lambda1) * (delta/D));
        b = std::sqrt((-1/lambda2) * (delta/D));
        for (double x = -a; x<=a; x+=step/2)
        {
            X.push_back(x);
            y = b*sqrt(1 - x*x / (a*a));
            if (y != y) y = 0;
            Y.push_back(y);
        }
        X.push_back(a);
        Y.push_back(0);
        for (double x = a; x>=-a-step; x-=step/2)
        {
            X.push_back(x);
            y = -b*sqrt(1 - x*x / (a*a));
            if (y != y) y = 0;
            Y.push_back(y);
        }
        break;

    case Curve::Parabola: //y^2 = 2px // y = +-sqrt(2px) // p = sqrt(-delta/(I*I*I)
        p = std::sqrt(-delta/(I*I*I));
        for (double x=50; x>0; x-=step)
        {
            X.push_back(x);
            y = sqrt(2*p*x);
            Y.push_back(y);;
        }
        for (double x=0; x<=50; x+=step)
        {
            X.push_back(x);
            y = -sqrt(2*p*x);
            Y.push_back(y);;
        }
        break;

    case Curve::Hyperbola:
        if (lambda1*D>0)
            std::swap(lambda1, lambda2);
        a = std::sqrt(-delta/(lambda1*D));
        b = std::sqrt(delta/(lambda2*D));
        for(double x=-a*50; x<-a; x+=step)
        {
            X.push_back(x);
            y = b*std::sqrt(x*x/(a*a)-1);
            Y.push_back(y);
        }
        for (double x=-a; x>-a*50; x-=step)
        {
            X.push_back(x);
            y = -b*std::sqrt(x*x/(a*a)-1);
            Y.push_back(y);
        }
        X.push_back(a);
        Y.push_back(NAN);
        for (double x=a*50; x>a; x-=step)
        {
            X.push_back(x);
            y = b*std::sqrt(x*x/(a*a)-1);
            Y.push_back(y);
        }
        for (double x=a; x<a*50; x+=step)
        {
            X.push_back(x);
            y = -b*std::sqrt(x*x/(a*a)-1);
            Y.push_back(y);
        }
        break;
    default:
        break;
    }

    translate(X, Y);
    return std::pair<QVector<double>, QVector<double>>(X, Y);
}

