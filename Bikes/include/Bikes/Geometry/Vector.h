#ifndef INCLUDEBIKES_VECTOR_H
#define INCLUDEBIKES_VECTOR_H

#include <Bikes/Types.h>

namespace Bikes
{

class Basis;
class Point;

class Vector
{
public:

 	rnum gx; //!< - �������� �� ��� OX � ����������(!) ������. ��� ��������� ��������� ������������ Vector::x()
	rnum gy; //!< - �������� �� ��� OY � ����������(!) ������. ��� ��������� ��������� ������������ Vector::y()
	rnum gz; //!< - �������� �� ��� OZ � ����������(!) ������. ��� ��������� ��������� ������������ Vector::z()

	//! ����������� �� ��������� ��� ����������� � ���������� �����������.
	Vector( 
		rnum globalX = 0, //!< - �������� �� ��� OX � ���������� ������.
		rnum globalY = 0, //!< - �������� �� ��� OY � ���������� ������.
		rnum globalZ = 0  //!< - �������� �� ��� OZ � ���������� ������.
		);

	//! ����������� ��� ����������� � ��������� �����������.
	Vector( 
		rnum localX,	//!< - �������� �� ��� OX � ��������� ������.
		rnum localY,	//!< - �������� �� ��� OY � ��������� ������.
		rnum localZ,	//!< - �������� �� ��� OZ � ��������� ������.
		const Basis &b	//!< - ��������� �����
		);

//cccccccccccccccccccccccccccc

	
	//! ����������� ��� ����������� �� ���� ������ ������
	Vector( 
		const Point &p1, //!< - ������ ������� 
		const Point &p2  //!< - ����� �������
		); 

	// ����������� �����������
	Vector( const Vector &v );
	
	Vector& operator = (const Vector &v); // ���������� ������������ �����������.

	virtual ~Vector(); 

	virtual rnum x() const; // �������� �� ��� OX � ���������(!) ������ *basis
	virtual rnum y() const; // �������� �� ��� OY � ���������(!) ������ *basis
	virtual rnum z() const; // �������� �� ��� OZ � ���������(!) ������ *basis

	rnum x(const Basis *b) const; // �������� �� ��� OX � ��������� ������ *b
	rnum y(const Basis *b) const; // �������� �� ��� OY � ��������� ������ *b
	rnum z(const Basis *b) const; // �������� �� ��� OZ � ��������� ������ *b

	rnum x(const Basis &b) const; // �������� �� ��� OX � ��������� ������ b
	rnum y(const Basis &b) const; // �������� �� ��� OY � ��������� ������ b
	rnum z(const Basis &b) const; // �������� �� ��� OZ � ��������� ������ b

	void setGlobal(rnum globalX, rnum globalY, rnum globalZ);  // ������ �� ��������� � ���������� ������
	
	virtual void setLocal(rnum localX, rnum localY, rnum localZ); // ������ �� ��������� � ��������� ������
	
	void setLocal(rnum localX, rnum localY, rnum localZ, const Basis& b); // ������ �� ��������� � ��������� ������ b
	
	virtual void setLocalX(rnum localX); // �������� ��������� �������� �� ��� OX
	virtual void setLocalY(rnum localY); // �������� ��������� �������� �� ��� OY
	virtual void setLocalZ(rnum localZ); // �������� ��������� �������� �� ��� OZ

	void setLocalX(rnum localX, const Basis& b); // �������� ��������� �������� �� ��� OX
	void setLocalY(rnum localY, const Basis& b); // �������� ��������� �������� �� ��� OY
	void setLocalZ(rnum localZ, const Basis& b); // �������� ��������� �������� �� ��� OZ
	
	void normalize(); // ���������� � ��������� ������ (��������� ������ �� ��� �����)
			
	void rotate_W(const Vector &w, rnum a); // ������� ������ �� ������� ��������� ������������ ��� w �� ���� a	
	void rotate_W(const Vector &w, const TrAngle& a);
	
	void rotate_globalX(rnum a); // ������� ������ �� ������� ��������� ������������ ��� OX(� ��������� ������) �� ���� a
	void rotate_globalY(rnum a); // ������� ������ �� ������� ��������� ������������ ��� OY(� ��������� ������) �� ���� a
	void rotate_globalZ(rnum a); // ������� ������ �� ������� ��������� ������������ ��� OZ(� ��������� ������) �� ���� a	


	rnum length() const; // ����� �������
	rnum l() const; // ����� �������

	Vector e() const; // ��������� ������ �������������� ������� �������

	bool isEqual(const Vector& v ) const;
	bool isEqual(const Vector& v, rnum epsilon) const; 
	

#ifdef PREBIKES_USE_TRANGLE	
	TrAngle angle(const Vector &v) const {return angle(*this,v);}  // �������� �������� �������
#else
	rnum angle(const Vector &v) const {return angle(*this,v);} 
#endif


#ifdef PREBIKES_USE_TRANGLE	
	static TrAngle angle(const Vector &v1, const Vector &v2); // ���� ����� ����� ���������
#else
	static rnum angle(const Vector &v1, const Vector &v2); // ���� ����� ����� ���������
#endif

	static bool isParallel(const Vector &v1, const Vector &v2); // v1,v2  �����������?
	static rnum parallelDistance(const Vector &v1, const Vector &v2); // ����� ���������� ����� ������������� ���������. ���� ������� �� �����������, �� ������������ 0.

	static bool isRightVectors(Vector v1, Vector v2, Vector v3=Vector(0,0,1)); // ������ ������ ��������?


	// �������� ���������:
	Vector operator + (const Vector& v) const; // �������� ���� ��������
	Vector operator - (const Vector& v) const; // ��������� ���� ��������
	Vector operator * (rnum n) const; // ��������� ������� �� �����
	Vector operator / (rnum n) const; // ������� ������� �� �����
	rnum   operator & (const Vector& v) const; // ��������� ������������ ���� ��������
	Vector operator * (const Vector& v) const; // ��������� ������������ ���� ������

	Vector& operator += (const Vector& v); // ��������� � ������� ������� ������ v
	Vector& operator -= (const Vector& v); // ������ �� ������� ������� ������ v
	Vector& operator *= (rnum n); // �������� ������ ������, ������� ��� �� n
	Vector& operator *= (const Vector& v);
	Vector& operator /= (rnum n); // �������� ������ ������, �������� ��� �� n

	Vector operator -() const; // ���������� (*this)*(-1)

	bool operator ==(const Vector &v) const; // ������, ���� �������� ������� v ���������� �� ����� ��� �� METRIC_O
	bool operator !=(const Vector &v) const; // �������� ����.. (��.����)
	
	bool operator == (rnum l) const;
	bool operator != (rnum l) const;
	bool operator <  (rnum l) const;
	bool operator <= (rnum l) const;
	bool operator >  (rnum l) const;
	bool operator >= (rnum l) const;


	//	Vector operator +() const;

	// �������������� ���������:
	Point operator % (const Vector &v) const;// ���������� Intersection(v)
	bool operator || (const Vector &v) const;// ���������� isParallel(*this,v)
	bool operator |=(const Vector &v) const; // ���������� isRightVectors(*this,v);
	Basis operator && (const Vector &v) const;// ���������� OrtoBasis_ByIJ(*this,v)
	Basis operator && (const Point &p) const;// ���������� OrtoBasis_ByIJ(*this,Vector(anchor,p))

#ifdef PREBIKES_USE_TRANGLE
	TrAngle operator ^ (const Vector &v) const;// ���������� Angle(v)
#else
	rnum operator ^ (const Vector &v) const;// ���������� Angle(v)
#endif

	Vector operator [] (const Basis &b) const;// ���������� inBasis(&b)
	Vector operator [] (const Basis *b) const;// ���������� inBasis(b)
	Vector& operator >> (const Basis &b);// ���������� SetBasis(&b)
	Vector& operator >> (const Basis *b);// ���������� SetBasis(b)
	Vector operator !() const;// ���������� Vector(true,*this,false).invert()
	bool operator > (const Vector &v) const;// ���������� length()>v.length()
	bool operator < (const Vector &v) const;// ���������� length()<v.length()


};

bool isRightHandVectors( const Vector& v1, const Vector& v2, const Vector& v3 );
bool isLeftHandVectors( const Vector& v1, const Vector& v2, const Vector& v3 );

}

#endif