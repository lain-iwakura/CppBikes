#include "Tests.h"
#include <Bikes/Geom/Vector.h>
#include <Bikes/Testing.h>
#include <iostream>

using namespace Bikes;


class Vector2
{
public:

    //! Конструктор по умолчанию для определения в глобальных координатах.
    Vector2(
        rnum globalX = 0, //!< - проекция на ось OX в глобальном базисе
        rnum globalY = 0, //!< - проекция на ось OY в глобальном базисе
        rnum globalZ = 0  //!< - проекция на ось OZ в глобальном базисе
        );

    //! Конструктор для определения в локальных координатах.
    Vector2(
        rnum localX,	//!< - проекция на ось OX в локальном базисе
        rnum localY,	//!< - проекция на ось OY в локальном базисе
        rnum localZ,	//!< - проекция на ось OZ в локальном базисе
        const Basis &b	//!< - локальный базис.
        );

    //! Конструктор для определения по двум точкам вектор.
    Vector2(
        const Point &p1, //!< - начало вектора
        const Point &p2  //!< - конец вектора
        );

    //! Конструктор копирования.
    Vector2(const Vector2 &v);

    //! Оператор присваивания.
    Vector2& operator = (const Vector2 &v);

    //! Виртуальный деструктор.
    ~Vector2();

    //! Проекция на ось OX в собственном базисе. 
    rnum x() const;

    //! Проекция на ось OY в собственном базисе. 
    rnum y() const;

    //! Проекция на ось OZ в собственном базисе. 
    rnum z() const;

    //! Проекция на ось OX в базисе *b.
    rnum x(const Basis *b) const;

    //! Проекция на ось OY в базисе *b.
    rnum y(const Basis *b) const;

    //! Проекция на ось OZ в базисе *b.
    rnum z(const Basis *b) const;

    //! Проекция на ось OX в базисе b.
    rnum x(const Basis &b) const;

    //! Проекция на ось OY в базисе b.
    rnum y(const Basis &b) const;

    //! Проекция на ось OZ в базисе b.
    rnum z(const Basis &b) const;

    //! Вектор по проекциям в глобальном базисе.
    void setGlobal(
        rnum globalX, //!< - проекция на ось ОX
        rnum globalY, //!< - проекция на ось ОY
        rnum globalZ  //!< - проекция на ось ОZ
        );

    // Вектор по проекциям в собственном базисе.
    void setLocal(
        rnum localX, //!< - проекция на ось ОX
        rnum localY, //!< - проекция на ось ОY
        rnum localZ  //!< - проекция на ось ОZ
        );

    //! Вектор по проекциям в локальном базисе.
    void setLocal(
        rnum localX, //!< - проекция на ось ОX
        rnum localY, //!< - проекция на ось ОY
        rnum localZ, //!< - проекция на ось ОZ
        const Basis& b //!< - локальный базис
        );

    //! Установить длину.
    void setLength(rnum len);

    //! Масштабировать
    void scaling(rnum scaleFactor);

    //! Изменить проекцию на ось OX в собственном базисе.
    void setLocalX(rnum localX);

    //! Изменить проекцию на ось OY в собственном базисе.
    void setLocalY(rnum localY);

    //! Изменить проекцию на ось OZ в собственном базисе.
    void setLocalZ(rnum localZ);

    //! Изменить локальную проекцию на ось OX в базисе b.
    void setLocalX(rnum localX, const Basis& b);

    //! Изменить локальную проекцию на ось OY в базисе b.
    void setLocalY(rnum localY, const Basis& b);

    //! Изменить локальную проекцию на ось OZ в базисе b.
    void setLocalZ(rnum localZ, const Basis& b);

    //! Превратить в единичный вектор (разделить вектор на его длину).
    void normalize();

    //! Вращать вектор по правилу буравчика в направлении w на угол а.
    void rotate_W(const Vector2 &w, rnum a);

    //! Вращать вектор по правилу буравчика в направлении w на угол а.
    void rotate_W(const Vector2 &w, const TrAngle& a);

    //! Вращать вектор по правилу буравчика в направлении оси OX в глобальном базисе на угол a.
    void rotate_globalX(rnum a);

    //! Вращать вектор по правилу буравчика в направлении оси OX в глобальном базисе на угол a.
    void rotate_globalY(rnum a);

    //! Вращать вектор по правилу буравчика в направлении оси OX в глобальном базисе на угол a.
    void rotate_globalZ(rnum a);

    //! Получить длину вектора.
    rnum length() const;

    //! Получить длину вектора.
    rnum l() const;

    //! Получить единичный вектор соответсвующий данному вектору.
    Vector2 e() const;

    //! Проверить на равенство другому вектору.
    bool isEqual(const Vector2& v) const;

    //! Проверить на равенство дргуому веткору с заданной погрешностью.
    bool isEqual(
        const Vector2& v, //!< - вектор, с которым сравниваем
        rnum epsilon     //!< - максимальная разница проекций на оси в глобальном базисе сравниваемых векторов
        ) const;

    //! Проверить на колиниарность другому вектору с заданной погрешностью.
    bool isCollinear(
        const Vector2& v2, //!< - вектор, с которым сравниваем
        cosnum cos_angleEpsilon //!< - косинус максимально допустимого угла между векторами
        ) const;

    //! Получить угол между векторами.
    //! \note Медленнее чем cosAngle().
    radian angle(const Vector2& v) const;

    //! Получить косинус угла между векторами. 
    //! \note Быстрее чем angle().
    cosnum cosAngle(const Vector2& v) const;

    //! Получить сумму векторов.
    Vector2 operator + (const Vector2& v) const;

    //! Получить разницу векторов.
    Vector2 operator - (const Vector2& v) const;

    //! Получить произведение вектора на число.
    Vector2 operator * (rnum n) const;

    // Получить результат деления вектора на число.
    Vector2 operator / (rnum n) const;

    //! Получить скалярное произведение двух векторов.
    rnum   operator & (const Vector2& v) const;

    //! Получить Векторное произведение двух вектор.
    Vector2 operator * (const Vector2& v) const;

    //! Прибавить к данному вектору другой вектор.
    Vector2& operator += (const Vector2& v);

    //! Отнять от данного вектора  другой вектор.
    Vector2& operator -= (const Vector2& v);

    //! Умножить данный вектор на число.
    Vector2& operator *= (rnum n);

    //! Разделить данный вектор на число.
    Vector2& operator /= (rnum n);

    //! Умножить векторно данный вектор на другой вектор.
    Vector2& operator *= (const Vector2& v);

    //! Получить веткор противоположный данному вектору. 
    Vector2 operator -() const;

    //! Проверить на равенство другому вектору.
    bool operator ==(const Vector2 &v) const;

    //! Проверить на неравенство другому вектору.
    bool operator !=(const Vector2 &v) const;

    //! Проверить на равенство заданной величине длины вектора. 
    bool operator == (rnum l) const;

    //! Проверить на неравенство заданной величине длины вектора. 
    bool operator != (rnum l) const;

    //! Проверить, что длина вектора строго меньше заданной величины.
    bool operator <  (rnum l) const;

    //! Проверить, что длина вектора меньше или равна заданной величине.
    bool operator <= (rnum l) const;

    //! Проверить, что длина вектора строго больше заданной величины.
    bool operator >  (rnum l) const;

    //! Проверить, что длина вектора больше или равна заданной величины.
    bool operator >= (rnum l) const;

    //! Поулчить угол между двумя векторами.
    radian operator ^ (const Vector2 &v) const;

    //! Проверить, что длина данного вектора строго больше длины другого вектора.
    bool operator > (const Vector2 &v) const;

    //! Проверить, что длина данного вектора строго меньше другого вектора.
    bool operator < (const Vector2 &v) const;

    //! Проверить, что длина данного вектора больше или равна длине другого вектора.
    bool operator >= (const Vector2 &v) const;

    //! Проверить, что длина данного вектора меньше или равна длине другого вектора.
    bool operator <= (const Vector2 &v) const;

protected:

    rnum _gx; //!< - проекция на ось OX в глобальном базисе
    rnum _gy; //!< - проекция на ось OY в глобальном базисе
    rnum _gz; //!< - проекция на ось OZ в глобальном базисе

};

struct Str3x8
{
    double d1;
    double d2;
    double d3;
};

void test_virtualclass()
{
    BIKES_COUT_VAR(sizeof(Vector));
    BIKES_COUT_VAR(sizeof(Vector2));
    BIKES_COUT_VAR(sizeof(Str3x8));
}
