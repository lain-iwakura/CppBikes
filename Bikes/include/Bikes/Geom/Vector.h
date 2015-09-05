#ifndef INCLUDE_BIKES_GEOM_VECTOR_H
#define INCLUDE_BIKES_GEOM_VECTOR_H

#include <Bikes/Types.h>

namespace Bikes
{

class Basis;
class Point;
class TrAngle;

//! ������ � 3-� ������ ������������.
class Vector
{
public:

	//! ����������� �� ��������� ��� ����������� � ���������� �����������.
	Vector( 
		rnum globalX = 0, //!< - �������� �� ��� OX � ���������� ������
		rnum globalY = 0, //!< - �������� �� ��� OY � ���������� ������
		rnum globalZ = 0  //!< - �������� �� ��� OZ � ���������� ������
		);

	//! ����������� ��� ����������� � ��������� �����������.
	Vector( 
		rnum localX,	//!< - �������� �� ��� OX � ��������� ������
		rnum localY,	//!< - �������� �� ��� OY � ��������� ������
		rnum localZ,	//!< - �������� �� ��� OZ � ��������� ������
        const IConstBasis &b	//!< - ��������� �����.
		);

	//! ����������� ��� ����������� �� ���� ������ ������.
	Vector( 
		const Point &p1, //!< - ������ �������
		const Point &p2  //!< - ����� �������
		); 

	//! ����������� �����������.
	Vector( const Vector &v );

	//! �������� ������������.
	Vector& operator = (const Vector &v); 

	//! ������������� ����������.
	 ~Vector(); 

     //! �������� �� ��� OX � ���������� ������. 
     rnum& rx(); //?

     //! �������� �� ��� OY � ���������� ������. 
     rnum& ry(); //?

     //! �������� �� ��� OZ � ���������� ������. 
     rnum& rz(); //?
	
	//! �������� �� ��� OX � ���������� ������. 
	 rnum x() const; 

	//! �������� �� ��� OY � ���������� ������. 
	 rnum y() const; 

	//! �������� �� ��� OZ � ���������� ������. 
	 rnum z() const; 

	//! �������� �� ��� OX � ������ *b.
	rnum lx(const IConstBasis *b) const; 

	//! �������� �� ��� OY � ������ *b.
	rnum ly(const IConstBasis *b) const; 

	//! �������� �� ��� OZ � ������ *b.
	rnum lz(const IConstBasis *b) const; 

	//! �������� �� ��� OX � ������ b.
    rnum lx(const IConstBasis &b) const;

	//! �������� �� ��� OY � ������ b.
    rnum ly(const IConstBasis &b) const;

	//! �������� �� ��� OZ � ������ b.
    rnum lz(const IConstBasis &b) const;

	//! ������ �� ��������� � ���������� ������.
	void setGlobal(
		rnum globalX, //!< - �������� �� ��� �X
		rnum globalY, //!< - �������� �� ��� �Y
		rnum globalZ  //!< - �������� �� ��� �Z
		);  
	

	//! ������ �� ��������� � ��������� ������.
	void setLocal(
		rnum localX, //!< - �������� �� ��� �X
		rnum localY, //!< - �������� �� ��� �Y
		rnum localZ, //!< - �������� �� ��� �Z
        const IConstBasis& b //!< - ��������� �����
		); 

	//! ���������� �����.
	void setLength(rnum len);

	//! ��������������
	void scale(rnum scaleFactor);
	
	//! �������� ��������� �������� �� ��� OX � ������ b.
    void setLocalX(rnum localX, const IConstBasis& b);

	//! �������� ��������� �������� �� ��� OY � ������ b.
    void setLocalY(rnum localY, const IConstBasis& b);

	//! �������� ��������� �������� �� ��� OZ � ������ b.
    void setLocalZ(rnum localZ, const IConstBasis& b);

	//! ���������� � ��������� ������ (��������� ������ �� ��� �����).
	void normalize(); 
			
	//! ������� ������ �� ������� ��������� � ����������� w �� ���� �.
	void rotate_W(const Vector &w, rnum a); 

	//! ������� ������ �� ������� ��������� � ����������� w �� ���� �.
	void rotate_W(const Vector &w, const TrAngle& a);
	
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
	Vector e() const; 

	//! ��������� �� ��������� ������� �������.
	bool isEqual(const Vector& v ) const;

	//! ��������� �� ��������� ������� ������� � �������� ������������.
	bool isEqual(
		const Vector& v, //!< - ������, � ������� ����������
		rnum epsilon     //!< - ������������ ������� �������� �� ��� � ���������� ������ ������������ ��������
		) const; 

	//! ��������� �� ������������� ������� ������� � �������� ������������.
	bool isCollinear(
		const Vector& v2, //!< - ������, � ������� ����������
		cosnum cos_angleEpsilon //!< - ������� ����������� ����������� ���� ����� ���������
		) const;
	
	//! �������� ���� ����� ���������.
	//! \note ��������� ��� cosAngle().
	radian angle(const Vector& v) const;

	//! �������� ������� ���� ����� ���������. 
	//! \note ������� ��� angle().
	cosnum cosAngle(const Vector& v) const;
	
	//! �������� ����� ��������.
	Vector operator + (const Vector& v) const; 

	//! �������� ������� ��������.
	Vector operator - (const Vector& v) const; 

	//! �������� ������������ ������� �� �����.
	Vector operator * (rnum n) const; 

	// �������� ��������� ������� ������� �� �����.
	Vector operator / (rnum n) const; 

	//! �������� ��������� ������������ ���� ��������.
	rnum   operator & (const Vector& v) const; 

	//! �������� ��������� ������������ ���� ������.
	Vector operator * (const Vector& v) const; 

	//! ��������� � ������� ������� ������ ������.
	Vector& operator += (const Vector& v); 

	//! ������ �� ������� �������  ������ ������.
	Vector& operator -= (const Vector& v); 

	//! �������� ������ ������ �� �����.
	Vector& operator *= (rnum n); 

	//! ��������� ������ ������ �� �����.
	Vector& operator /= (rnum n); 

	//! �������� �������� ������ ������ �� ������ ������.
	Vector& operator *= (const Vector& v);
	
	//! �������� ������ ��������������� ������� �������. 
	Vector operator -() const; 

	//! ��������� �� ��������� ������� �������.
	bool operator ==(const Vector &v) const; 

	//! ��������� �� ����������� ������� �������.
	bool operator !=(const Vector &v) const; 
	
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
	radian operator ^ (const Vector &v) const;
		
	//! ���������, ��� ����� ������� ������� ������ ������ ����� ������� �������.
	bool operator > (const Vector &v) const;

	//! ���������, ��� ����� ������� ������� ������ ������ ������� �������.
	bool operator < (const Vector &v) const;

	//! ���������, ��� ����� ������� ������� ������ ��� ����� ����� ������� �������.
	bool operator >= (const Vector &v) const;

	//! ���������, ��� ����� ������� ������� ������ ��� ����� ����� ������� �������.
	bool operator <= (const Vector &v) const;

protected:

    rnum _gx; //!< - �������� �� ��� OX � ���������� ������
    rnum _gy; //!< - �������� �� ��� OY � ���������� ������
    rnum _gz; //!< - �������� �� ��� OZ � ���������� ������
};


//! ��������� ������ ������ �������.
bool isRightHandVectors( const Vector& v1, const Vector& v2, const Vector& v3 );

//! ��������� ����� ������ �������.
bool isLeftHandVectors( const Vector& v1, const Vector& v2, const Vector& v3 );


}

#endif // <- INCLUDE_BIKES_GEOM_VECTOR_H
