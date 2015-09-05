#include "Tests.h"
#include <Bikes/Geom/Vector.h>
#include <Bikes/Testing.h>
#include <iostream>

using namespace Bikes;


class Vector2
{
public:

    //! ����������� �� ��������� ��� ����������� � ���������� �����������.
    Vector2(
        rnum globalX = 0, //!< - �������� �� ��� OX � ���������� ������
        rnum globalY = 0, //!< - �������� �� ��� OY � ���������� ������
        rnum globalZ = 0  //!< - �������� �� ��� OZ � ���������� ������
        );

    //! ����������� ��� ����������� � ��������� �����������.
    Vector2(
        rnum localX,	//!< - �������� �� ��� OX � ��������� ������
        rnum localY,	//!< - �������� �� ��� OY � ��������� ������
        rnum localZ,	//!< - �������� �� ��� OZ � ��������� ������
        const Basis &b	//!< - ��������� �����.
        );

    //! ����������� ��� ����������� �� ���� ������ ������.
    Vector2(
        const Point &p1, //!< - ������ �������
        const Point &p2  //!< - ����� �������
        );

    //! ����������� �����������.
    Vector2(const Vector2 &v);

    //! �������� ������������.
    Vector2& operator = (const Vector2 &v);

    //! ����������� ����������.
    ~Vector2();

    //! �������� �� ��� OX � ����������� ������. 
    rnum x() const;

    //! �������� �� ��� OY � ����������� ������. 
    rnum y() const;

    //! �������� �� ��� OZ � ����������� ������. 
    rnum z() const;

    //! �������� �� ��� OX � ������ *b.
    rnum x(const Basis *b) const;

    //! �������� �� ��� OY � ������ *b.
    rnum y(const Basis *b) const;

    //! �������� �� ��� OZ � ������ *b.
    rnum z(const Basis *b) const;

    //! �������� �� ��� OX � ������ b.
    rnum x(const Basis &b) const;

    //! �������� �� ��� OY � ������ b.
    rnum y(const Basis &b) const;

    //! �������� �� ��� OZ � ������ b.
    rnum z(const Basis &b) const;

    //! ������ �� ��������� � ���������� ������.
    void setGlobal(
        rnum globalX, //!< - �������� �� ��� �X
        rnum globalY, //!< - �������� �� ��� �Y
        rnum globalZ  //!< - �������� �� ��� �Z
        );

    // ������ �� ��������� � ����������� ������.
    void setLocal(
        rnum localX, //!< - �������� �� ��� �X
        rnum localY, //!< - �������� �� ��� �Y
        rnum localZ  //!< - �������� �� ��� �Z
        );

    //! ������ �� ��������� � ��������� ������.
    void setLocal(
        rnum localX, //!< - �������� �� ��� �X
        rnum localY, //!< - �������� �� ��� �Y
        rnum localZ, //!< - �������� �� ��� �Z
        const Basis& b //!< - ��������� �����
        );

    //! ���������� �����.
    void setLength(rnum len);

    //! ��������������
    void scaling(rnum scaleFactor);

    //! �������� �������� �� ��� OX � ����������� ������.
    void setLocalX(rnum localX);

    //! �������� �������� �� ��� OY � ����������� ������.
    void setLocalY(rnum localY);

    //! �������� �������� �� ��� OZ � ����������� ������.
    void setLocalZ(rnum localZ);

    //! �������� ��������� �������� �� ��� OX � ������ b.
    void setLocalX(rnum localX, const Basis& b);

    //! �������� ��������� �������� �� ��� OY � ������ b.
    void setLocalY(rnum localY, const Basis& b);

    //! �������� ��������� �������� �� ��� OZ � ������ b.
    void setLocalZ(rnum localZ, const Basis& b);

    //! ���������� � ��������� ������ (��������� ������ �� ��� �����).
    void normalize();

    //! ������� ������ �� ������� ��������� � ����������� w �� ���� �.
    void rotate_W(const Vector2 &w, rnum a);

    //! ������� ������ �� ������� ��������� � ����������� w �� ���� �.
    void rotate_W(const Vector2 &w, const TrAngle& a);

    //! ������� ������ �� ������� ��������� � ����������� ��� OX � ���������� ������ �� ���� a.
    void rotate_globalX(rnum a);

    //! ������� ������ �� ������� ��������� � ����������� ��� OX � ���������� ������ �� ���� a.
    void rotate_globalY(rnum a);

    //! ������� ������ �� ������� ��������� � ����������� ��� OX � ���������� ������ �� ���� a.
    void rotate_globalZ(rnum a);

    //! �������� ����� �������.
    rnum length() const;

    //! �������� ����� �������.
    rnum l() const;

    //! �������� ��������� ������ �������������� ������� �������.
    Vector2 e() const;

    //! ��������� �� ��������� ������� �������.
    bool isEqual(const Vector2& v) const;

    //! ��������� �� ��������� ������� ������� � �������� ������������.
    bool isEqual(
        const Vector2& v, //!< - ������, � ������� ����������
        rnum epsilon     //!< - ������������ ������� �������� �� ��� � ���������� ������ ������������ ��������
        ) const;

    //! ��������� �� ������������� ������� ������� � �������� ������������.
    bool isCollinear(
        const Vector2& v2, //!< - ������, � ������� ����������
        cosnum cos_angleEpsilon //!< - ������� ����������� ����������� ���� ����� ���������
        ) const;

    //! �������� ���� ����� ���������.
    //! \note ��������� ��� cosAngle().
    radian angle(const Vector2& v) const;

    //! �������� ������� ���� ����� ���������. 
    //! \note ������� ��� angle().
    cosnum cosAngle(const Vector2& v) const;

    //! �������� ����� ��������.
    Vector2 operator + (const Vector2& v) const;

    //! �������� ������� ��������.
    Vector2 operator - (const Vector2& v) const;

    //! �������� ������������ ������� �� �����.
    Vector2 operator * (rnum n) const;

    // �������� ��������� ������� ������� �� �����.
    Vector2 operator / (rnum n) const;

    //! �������� ��������� ������������ ���� ��������.
    rnum   operator & (const Vector2& v) const;

    //! �������� ��������� ������������ ���� ������.
    Vector2 operator * (const Vector2& v) const;

    //! ��������� � ������� ������� ������ ������.
    Vector2& operator += (const Vector2& v);

    //! ������ �� ������� �������  ������ ������.
    Vector2& operator -= (const Vector2& v);

    //! �������� ������ ������ �� �����.
    Vector2& operator *= (rnum n);

    //! ��������� ������ ������ �� �����.
    Vector2& operator /= (rnum n);

    //! �������� �������� ������ ������ �� ������ ������.
    Vector2& operator *= (const Vector2& v);

    //! �������� ������ ��������������� ������� �������. 
    Vector2 operator -() const;

    //! ��������� �� ��������� ������� �������.
    bool operator ==(const Vector2 &v) const;

    //! ��������� �� ����������� ������� �������.
    bool operator !=(const Vector2 &v) const;

    //! ��������� �� ��������� �������� �������� ����� �������. 
    bool operator == (rnum l) const;

    //! ��������� �� ����������� �������� �������� ����� �������. 
    bool operator != (rnum l) const;

    //! ���������, ��� ����� ������� ������ ������ �������� ��������.
    bool operator <  (rnum l) const;

    //! ���������, ��� ����� ������� ������ ��� ����� �������� ��������.
    bool operator <= (rnum l) const;

    //! ���������, ��� ����� ������� ������ ������ �������� ��������.
    bool operator >  (rnum l) const;

    //! ���������, ��� ����� ������� ������ ��� ����� �������� ��������.
    bool operator >= (rnum l) const;

    //! �������� ���� ����� ����� ���������.
    radian operator ^ (const Vector2 &v) const;

    //! ���������, ��� ����� ������� ������� ������ ������ ����� ������� �������.
    bool operator > (const Vector2 &v) const;

    //! ���������, ��� ����� ������� ������� ������ ������ ������� �������.
    bool operator < (const Vector2 &v) const;

    //! ���������, ��� ����� ������� ������� ������ ��� ����� ����� ������� �������.
    bool operator >= (const Vector2 &v) const;

    //! ���������, ��� ����� ������� ������� ������ ��� ����� ����� ������� �������.
    bool operator <= (const Vector2 &v) const;

protected:

    rnum _gx; //!< - �������� �� ��� OX � ���������� ������
    rnum _gy; //!< - �������� �� ��� OY � ���������� ������
    rnum _gz; //!< - �������� �� ��� OZ � ���������� ������

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
