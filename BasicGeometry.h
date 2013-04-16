// BasicGeometry �������� 3 ������, ���������� ������������ ��� �������
// �������������� ����� �� ��������� � � ������������:
//
// Point - ����� �����, �������� ����� ������������ � ���������� ������� ��������� (����� ��).
// ����� ����� ���� ��������� � ���������� ������ (��������� ��), 
// ��� ���� ����������� �������� � ���������� ������������. 
//
// Vector - ����� �������, �������� ������ ���������� (�������) 
// � ����� ���������� �� ��� ��������� ���������� ��.
// ������ ��� ��, ��� � �����, ����� ���� �������� � ���������� ������ (��������� ��) 
//
// Basis - ����� ������ (��������� ��), �������� ������ (������� ���������)
// � ����� ���������� ��������� (����� ���������).
// ���� ����� ������������, ��� �������, ����������� � ������� ������, ����������� � ���������� ��.


#ifndef CPPBYKES_BASICGEOMETRY_H
#define CPPBYKES_BASICGEOMETRY_H

//#include "List.h"
//#include "BasicMath.h"
#include <Bikes/Types.h>
#include <Bikes/List.h>
#include <Bikes/BasicMath.h>

//#define CPPBIKES_USE_TRANGLE

#ifdef CPPBIKES_USE_TRANGLE
#include <Bikes/TrigonometricAngle.h>
#endif

namespace Bikes
{

class Basis; 
class Vector;
class Point;
struct CylCoord;

//typedef double rnum; // ��� ��� �������� �������� ��������� � ���� �������� 
//const rnum METRIC_O=0.000001; // �������� rnum (�������������� ����������� ��������� => �������� 1 ��)
//typedef double rnum; // ��� ��� �������� ������� ������� 
//const rnum RADIAN_O=0.000001; // �������� rnum (����������� ������� => �������� ~ 3.82e-5 ��������  )

const rnum METRIC_O=0.000001; // �������� ��������� �������� �������� (�������������� ����������� ��������� => �������� 1 ��)
const rnum RADIAN_O=0.000001; // �������� ��������� ������� �������� (����������� ������� => �������� ~ 3.82e-5 ��������  )

// typedef Vector V;
// typedef Point P;


/////////////////////////// POINT /////////////////////////////////////////////
class Point //����� ����� {40b}
{	
public:

	const Basis *basis; // ��������� ����� (�� ��������� basis=0 - ���������� �����, �.�. ��������� ���������� ����� ����������)
	rnum gx; // ���������� X � ����������(!) ������ // ��� ��������� ��������� ������������ x()
	rnum gy; // ���������� Y � ����������(!) ������ // ��� ��������� ��������� ������������ y()
	rnum gz; // ���������� Z � ����������(!) ������ // ��� ��������� ��������� ������������ z()
	
	// ����������� �� ���������:
	// plx,ply,plz - ���������� ���������� � ������ *b (b=0 - ���������� �����), notransient=true/false - �������/��������� ������ 
	Point(rnum plx=0,rnum ply=0,rnum plz=0,const Basis *b=0, bool notransient=true);
	// Point(rnum plx=0,rnum ply=0,rnum plz=0,const Basis *b=0,);//notransient=false;

	// ����������� ��� ������� (��������������) �����:
	// NotNull=true/false => �������/������� �����; gx,gy,gz,*basis �������� �� p
	Point(bool NotNull, const Point &p=Point(), bool notransient=true); 
	
	// ���������� �����:
	// �������� gx,gy,gz,_null. ������������� � ������ p.basis. 
	Point(const Point &p); 
	
	// ����������� ������ ����� �� "�����" ������� v:
	Point(const Vector &v, bool notransient=true); 
	
	void operator =(const Point &p); // ���������� ������������ �����.
	void operator =(const Vector &v); // ����� �� ����� �������. 
	~Point(); // ������� ����� � ��������� ������� *basis.
	
	bool isNull() const; // �������(��������������) �����?  
	bool isTransient()const; // ��������� ������? // *��������*
	
	Point& Set(rnum px, rnum py, rnum pz,const Basis *b=0); //����� �� ����������� � ������ *b
	Point& SetGlobal(rnum pgx, rnum pgy, rnum pgz); // ����� �� ����������� � ���������� ������
	Point& SetLocal(rnum localx,rnum localy, rnum localz); // �����  �� ����������� � ��������� ������
	Point& SetLocalX(rnum localx); // �������� ��������� ���������� X
	Point& SetLocalY(rnum localy); // �������� ��������� ���������� Y
	Point& SetLocalZ(rnum localz); // �������� ��������� ���������� Z
	Point& SetBasis(const Basis *b); // �������� � ������ *b (b=0 �������� ������� � ���������� �����, �.�.  [��������� �����] = [���������� �����])
	Point& SetGlobalBasis(); // ������� �������� � ������ *basis (basis=0) // ��� �� ��������� ���� SetBasis(0);
	Point& ReplaceBasis(const Basis *b); // �������� ���������� ���������� ����� ����� �������, ����� ��� �������� � ����� ����� *b ��������� ���������� �� ����������
	Point& ReplaceGBasis(const Basis *b); // ���������� ReplaceBasis(Basis *b), �� �������, ��� ��������� �� ����������� ������ (basis -  ������������ � ��������� ������ 0)
	Point& Rotate_W(const Vector &w,rnum a); // ������� ����� �� ������� ��������� ������������ ��� w �� ���� a
	Point& Rotate_X(rnum a); //  ������� ����� �� ������� ��������� ������������ ��� OX(� ��������� ������) �� ���� a
	Point& Rotate_Y(rnum a); //  ������� ����� �� ������� ��������� ������������ ��� OY(� ��������� ������) �� ���� a
	Point& Rotate_Z(rnum a); //  ������� ����� �� ������� ��������� ������������ ��� OZ(� ��������� ������) �� ���� a
	
	rnum x() const; // ���������� X � ���������(!) ������ *basis
	rnum y() const; // ���������� Y � ���������(!) ������ *basis
	rnum z() const; // ���������� Z � ���������(!) ������ *basis
	rnum PolarAlpha() const;
	rnum PolarR() const;
	rnum lx(const Basis *b) const; // ���������� X � ��������� ������ *b
	rnum ly(const Basis *b) const; // ���������� Y � ��������� ������ *b
	rnum lz(const Basis *b) const; // ���������� Z � ��������� ������ *b
	rnum lx(const Basis &b) const; // ���������� X � ��������� ������ b
	rnum ly(const Basis &b) const; // ���������� Y � ��������� ������ b
	rnum lz(const Basis &b) const; // ���������� Z � ��������� ������ b
	Point inGlobalBasis() const; // �� �� ����� � ���������� ������
	Point inBasis(const Basis *b) const; // �� �� ����� � ������ *b
	Point inReplacedBasis(const Basis *b) const; // �� �� ����� � ���������� ������ (������ ReplaceBasis())
	Vector v() const;	// ������������� ����� � ������, ������ �������� ��������� � ������� ��������� ����������� ������ Point(0,0,0), � ������ �������� ��� �����.
	
	// �������� ���������:
	bool operator ==(const Point &p) const; // ������, ���� ����� p ����� � ����������� METRIC_O 
	bool operator !=(const Point &p) const;	// �������� ����... (��. ����)

	// �������������� ���������:
	Point operator [] (const Basis &b) const;// ���������� inBasis(&b)
	Point operator [] (const Basis *b) const;// ���������� inBasis(b)
	Point& operator >> (const Basis &b); // ���������� SetBasis(&b)
	Point& operator >> (const Basis *b); // ���������� SetBasis(b);
	Vector operator && (const Point &p) const; // ���������� Vector(*this,p)
	Point operator + (const Vector &v) const; // ���������� Point(Vector(*this)+v)
	Point operator - (const Vector &v) const; // ���������� Point(Vector(*this)-v)
	void operator +=(const Vector &v); // ����������� ����� �������� v
	void operator -=(const Vector &v); // ����������� ����� �������� -v
	////////////////////////////////

	
	static bool isEqual(const Point &p1, const Point &p2, rnum e=METRIC_O);


private:

	bool _transient; /*��������*/  // _transient=true => ��������� ������.
	// ��������� ������ �� ����� �������� � ������ � ������� ���������,
	// �.�. � *basis �� �������� ��������� �� ������ ������.

	bool _null;	 // _null=true - ������� ����� (�������������� �����)	

};
const Point p_gO(0,0,0,0); // ������ ��������� ����������� ������
const Point p_null(false,p_gO); // ������� (��������������) ����� �� ���������




/////////////////////////// VECTOR /////////////////////////////////////////////
class Vector // ����� ������� {80b}
{

public:
	const Basis *basis; // ��������� ����� (basis=0 - ���������� �����, �.�. ��������� �������� ����� ����������)
	Point anchor; // ����� ����������/�������� ������� (������ �������)
	rnum gx; // �������� �� ��� OX � ����������(!) ������ // ��� ��������� ��������� ������������ x()
	rnum gy; // �������� �� ��� OY � ����������(!) ������ // ��� ��������� ��������� ������������ y()
	rnum gz;	// �������� �� ��� OZ � ����������(!) ������ // ��� ��������� ��������� ������������ z()

	// ����������� �� ���������:
	// vx,vy,vz - �������� �� ��� ��������� � ������ *b, ap - ����� ����������(anchor), notransient=true/false=�������/��������� ������.
	Vector(rnum vx=0, rnum vy=0, rnum vz=0, const Point &ap=p_gO,const Basis *b=0, bool notransient=true);
	
	// ����������� ������� ������, ������� �������� �������� ����� p1, � ������ - ����� p2,
	// ������ ������������� � ������ *b.  
	Vector(const Point &p1, const Point &p2,const Basis *b=0, bool notransient=true); 
	
	// ����������� ��� ������� (��������������) ��������:
	// NotNull=true/false => �������/������� ������; anchor,gx,gy,gz, �������� �� v � ������������� � v.basis;
	Vector(bool NotNull,const Vector &v=Vector(), bool notransient=true);
	
	// ����������� �����:
	// �������� _null,anchor,gx,gy,gz, ������������� � ������ v.basis. 
	Vector(const Vector &v);
	
	// ����������� [�����]->[������]:
	// ������ ������, ������� �������� �������� ������ ���������� �� (Point(0,0,0)),
	// � ������ �������� ����� p.
	Vector(const Point &p,  bool notransient=true);
	
	void operator = (const Vector &v); // ���������� ������������ �����.
	void operator = (const Point &p); // ���������� ������������ [�����]->[������]
	operator Point(){ return destination();}
	~Vector(); // ������� ����� � ������� *basis
	
	bool isNull()const; // ������� ������?
	bool isTransient() const; // ��������� ������? 
		
	Vector& Set(rnum vx, rnum vy, rnum vz,const Basis *b=0); //������ �� ��������� � ������ *b
	Vector& SetGlobal(rnum gx, rnum gy, rnum gz);  // ������ �� ��������� � ���������� ������
	Vector& SetLocal(rnum localx, rnum localy, rnum localz); // ������ �� ��������� � ��������� ������
	Vector& SetLocalX(rnum localx); // �������� ��������� �������� �� ��� OX
	Vector& SetLocalY(rnum localy); // �������� ��������� �������� �� ��� OY
	Vector& SetLocalZ(rnum localz); // �������� ��������� �������� �� ��� OZ
	Vector& SetBasis(const Basis *b); // �������� � ������ *b
	Vector& SetGlobalBasis(); // ������� �������� � ������ *basis (basis=0) // ��� �� ��������� ���� SetBasis(0);
	Vector& ReplaceBasis(const Basis *b); // �������� ���������� �������� ������� ����� �������, ����� ��� �������� � ����� ����� *b ��������� �������� �� ���������� (� ��� �� ����� anchor.ReplaceBasis(b))
	Vector& ReplaceGBasis(const Basis *b); // ���������� ReplaceBasis(Basis *b), �� �������, ��� ��������� �� ����������� ������ (basis -  ������������ � ��������� ������ 0)
	Vector& normalize(); // ���������� � ��������� ������ (��������� ������ �� ��� �����)
	Vector& invert(); // ����������� ������ (�������� ������� ������ � �����)
	Vector& rotate_W(const Vector &w, rnum a); // ������� ������ �� ������� ��������� ������������ ��� w �� ���� a
	Vector& rotateWithoutFulcrum_W(const Vector &w, rnum a); // ���������� rotate_W(const Vector &w, rnum a), �� ����� ���������� �������� ����������.
	Vector& rotate_X(rnum a); // ������� ������ �� ������� ��������� ������������ ��� OX(� ��������� ������) �� ���� a
	Vector& rotate_Y(rnum a); // ������� ������ �� ������� ��������� ������������ ��� OY(� ��������� ������) �� ���� a
	Vector& rotate_Z(rnum a); // ������� ������ �� ������� ��������� ������������ ��� OZ(� ��������� ������) �� ���� a	
	
	rnum x() const; // �������� �� ��� OX � ���������(!) ������ *basis
	rnum y() const; // �������� �� ��� OY � ���������(!) ������ *basis
	rnum z() const; // �������� �� ��� OZ � ���������(!) ������ *basis
	rnum lx(const Basis *b) const; // �������� �� ��� OX � ��������� ������ *b
	rnum ly(const Basis *b) const; // �������� �� ��� OY � ��������� ������ *b
	rnum lz(const Basis *b) const; // �������� �� ��� OZ � ��������� ������ *b
	rnum lx(const Basis &b) const; // �������� �� ��� OX � ��������� ������ b
	rnum ly(const Basis &b) const; // �������� �� ��� OY � ��������� ������ b
	rnum lz(const Basis &b) const; // �������� �� ��� OZ � ��������� ������ b
	rnum length() const; // ����� �������
	Vector e() const; // ��������� ������ �������������� ������� �������
	Point destination() const; // ����� �� ����� �������
	Vector inBasis(const Basis *b) const; // ��� �� ������ � ������ *b
	Vector inGlobalBasis() const; //  ��� �� ������ � ���������� ������
	Vector inReplacedBasis(const Basis *b) const; // ��� �� ������ � ���������� ������ *b	



#ifdef CPPBIKES_USE_TRANGLE	
	TrAngle Angle(const Vector &v) const {return Angle(*this,v);}  // �������� �������� �������
#else
	rnum Angle(const Vector &v) const {return Angle(*this,v);} 
#endif
	
	Point Intersection(const Vector &v) const; // ����������� ���� ��������. 
	Point RangeIntersection(const Vector &v) const; 
	// ���� ������� �����������, �� ������������ ������� �����(p_null). 
	// ���� ������� ��������������, �� ������ ����������� ��������� ����� �������
	// �� ������� *this � ���������� ������ ������� ������������ ���������� �� ������� v

#ifdef CPPBIKES_USE_TRANGLE	
	static TrAngle Angle(const Vector &v1, const Vector &v2); // ���� ����� ����� ���������
#else
	static rnum Angle(const Vector &v1, const Vector &v2); // ���� ����� ����� ���������
#endif

	static bool isParallel(const Vector &v1, const Vector &v2); // v1,v2  �����������?
	static rnum ParallelDistance(const Vector &v1, const Vector &v2); // ����� ���������� ����� ������������� ���������. ���� ������� �� �����������, �� ������������ 0.
	
	static bool isRightVectors(Vector v1, Vector v2, Vector v3=Vector(0,0,1)); // ������ ������ ��������?
	
	// �������� ���������:
	Vector operator + (const Vector &v) const; // �������� ���� ��������
	Vector operator - (const Vector &v) const; // ��������� ���� ��������
	void operator += (const Vector &v); // ��������� � ������� ������� ������ v
	void operator -= (const Vector &v); // ������ �� ������� ������� ������ v
	rnum operator &(const Vector &v) const; // ��������� ������������ ���� ��������
	Vector operator *(const Vector &v) const; // ��������� ������������ ���� ��������
	Vector operator *(rnum n) const; // ��������� ������� �� �����
	Vector operator /(rnum n) const; // ������� ������� �� �����
	void operator *=(rnum n); // �������� ������ ������, ������� ��� �� n
	void operator /=(rnum n); // �������� ������ ������, �������� ��� �� n
	bool operator ==(const Vector &v) const; // ������, ���� �������� ������� v ���������� �� ����� ��� �� METRIC_O
	bool operator !=(const Vector &v) const; // �������� ����.. (��.����)
	Vector operator -() const; // ���������� (*this)*(-1)
//	Vector operator +() const;

	// �������������� ���������:
	Point operator % (const Vector &v) const;// ���������� Intersection(v)
	bool operator || (const Vector &v) const;// ���������� isParallel(*this,v)
	bool operator |=(const Vector &v) const; // ���������� isRightVectors(*this,v);
	Basis operator && (const Vector &v) const;// ���������� OrtoBasis_ByIJ(*this,v)
	Basis operator && (const Point &p) const;// ���������� OrtoBasis_ByIJ(*this,Vector(anchor,p))

#ifdef CPPBIKES_USE_TRANGLE
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


	// Phi & Lamda // (?)
	rnum Phi();	
	rnum Lamda();
	rnum Lamda2PI();


private:
	bool _transient; /*��������*/ // _transient=true - ��������� ������ (�� ����� �������� � ������ � ������� ���������)
	bool _null;  // _null=true - ������� ������ (�������������� ������)
};

const Vector v_gi(1,0,0,p_gO,0); // ��������� ������ ��������������� ��� OX ���������� ��
const Vector v_gj(0,1,0,p_gO,0); // ��������� ������ ��������������� ��� OY ���������� ��
const Vector v_gk(0,0,1,p_gO,0); // ��������� ������ ��������������� ��� OZ ���������� ��
const Vector v_null(false,Vector(0,0,0)); // ������� ������ �� ���������


/////////////////////////// BASIS /////////////////////////////////////////////
class Basis // ����� ��������� �� {288b}
{
	List<Vector*> *vectors; //������ ����������� ��������
	List<Point*> *points; //������ ����������� �����
public:
	Point O; // ������ ���������
	Vector i; // ��� OX
	Vector j; // ��� OY
	Vector k; // ��� OZ

	// ����������� �� ���������:
	// bi,bj,bk,bO ������ i,j,k,O
	Basis(const Vector &bi=v_gi,const Vector &bj=v_gj, const Vector &bk=v_gk, const Point &bO=p_gO);

	// ����������� �����:
	// ��������: i,j,k,O; �� ��������: vectors, points.
	Basis(const Basis &b);

	void operator =(const Basis &b);  //���������� ������������ �����.
	~Basis(); // ��� ����������� ������� ����������� � ���������� ��
	// ( vectors[i].basis=0; points[i].basis=0; ) 

	Basis& SetOrtoBasis_ByIJ(const Vector &bi,const Vector &bj); // ����������������� ������ �����,
	// � ������� ��������� OXY ������ ���������  bi,bj (bi ������ ����������� i, bi*bj ������ ����������� k, O=bi.anchor)
	Basis& SetOrtoBasisL_ByIJ(const Vector &bi, const Vector &bj);	//�� �� ��� � SetOrtoBasis_ByIJ, �� ����� �����	
	Basis& SetOrtoBasis_InXY_ByI(const Vector &bi); // ����������������� ������ �����,
	// � ������� k=v_gk, k*bi ������ ����������� j,  O=bi.anchor;  
	Basis& SetOrtoBasis_InXY_ByI_l(const Vector &bi); // �� �� ��� �	SetOrtoBasis_InXY_ByI, �� k=-v_gk;
	Basis& SetOrtoBasisL_InXY_ByI(const Vector &bi); // �� �� ��� �	SetOrtoBasis_InXY_ByI, �� ����� �����; 
	Basis& SetOrtoBasis_ByOXY(const Point &pO, const Point &pX, const Point &pY);	// ���������� SetOrtoBasis_ByIJ(Vector(pO,pX),Vector(pO,pY));
	Basis& SetO(const Point &pO); // ������� ������ ��������� 

	void Add(Point *p) const; //(?) ��������� ����� 
	void Add(Vector *v) const; //(?) ��������� ������ 
	void Remove(Point *p) const; //(?) ������� �������� ����� 
	void Remove(Vector *v) const; //(?) ������� �������� ������� 
	void RemoveAll() const; // ������� ��� ��������

	//////// extra operators ///////
	operator Basis*(){return this;}
	//Basis * operator ->(){return this;}
	const Basis& operator << (Point &p) const;// {p.SetBasis(this);  return *this;}
	const Basis& operator << (Vector &v) const;// {v.SetBasis(this);  return *this;}
	Vector operator [] (Vector &v) const;// {return v.inBasis(this);}
	Point operator [] (const Point &p) const;// {return p.inBasis(this);}
	////////////////////////////////
};


Basis OrtoBasis_ByIJ(const Vector &bi,const Vector &bj);	
Basis OrtoBasisL_ByIJ(const Vector &bi,const Vector &bj);	
Basis OrtoBasis_InXY_ByI(const Vector &bi);	
Basis OrtoBasisL_InXY_ByI(const Vector &bi);
Basis OrtoBasis_ByOXY(const Point &pO, const Point &pX, const Point &pY);

struct CylCoord
{
	rnum z;
	rnum r;
	rnum a;
};


CylCoord ToCylCoord(const Point &p);
CylCoord ToCylCoord_Arc(const Point &p);

Point FromCylCoord_Arc(rnum a, rnum r, rnum z=0, const Basis *b=0);
//Point FromCylCoord_Arc(TAngle a, rnum r, rnum z=0, const Basis *b=0);

}
#endif // BASICGEOMETRY_H

