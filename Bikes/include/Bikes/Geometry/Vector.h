#ifndef INCLUDEBIKES_VECTOR_H
#define INCLUDEBIKES_VECTOR_H

#include <Bikes/Types.h>

namespace Bikes
{

class Basis;
class Point;

//! ������ � 3-� ������ ������������.
class Vector
{
public:

 	rnum gx; //!< - �������� �� ��� OX � ���������� ������
	rnum gy; //!< - �������� �� ��� OY � ���������� ������
	rnum gz; //!< - �������� �� ��� OZ � ���������� ������

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
		const Basis &b	//!< - ��������� �����.
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

	//! ����������� ����������.
	virtual ~Vector(); 
	
	//! �������� �� ��� OX � ����������� ������. 
	virtual rnum x() const; 

	//! �������� �� ��� OY � ����������� ������. 
	virtual rnum y() const; 

	//! �������� �� ��� OZ � ����������� ������. 
	virtual rnum z() const; 

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
	virtual void setLocal(
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
	virtual void setLocalX(rnum localX); 

	//! �������� �������� �� ��� OY � ����������� ������.
	virtual void setLocalY(rnum localY);

	//! �������� �������� �� ��� OZ � ����������� ������.
	virtual void setLocalZ(rnum localZ);
	
	//! �������� ��������� �������� �� ��� OX � ������ b.
	void setLocalX(rnum localX, const Basis& b); 

	//! �������� ��������� �������� �� ��� OY � ������ b.
	void setLocalY(rnum localY, const Basis& b);

	//! �������� ��������� �������� �� ��� OZ � ������ b.
	void setLocalZ(rnum localZ, const Basis& b);	

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
	rnum   operator % (const Vector& v) const; 

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

};


//! ��������� ������ ������ �������.
bool isRightHandVectors( const Vector& v1, const Vector& v2, const Vector& v3 );

//! ��������� ����� ������ �������.
bool isLeftHandVectors( const Vector& v1, const Vector& v2, const Vector& v3 );


}

#endif