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
#include <CppBikes/Types.h>
#include <CppBikes/List.h>
#include <CppBikes/BasicMath.h>

//#define CPPBIKES_USE_TRANGLE

#ifdef CPPBIKES_USE_TRANGLE
#include <CppBikes/TrigonometricAngle.h>
#endif

namespace CppBikes
{

class Basis; 
class Vector;
class Point;
struct CylCoord;

//typedef double RNUM; // ��� ��� �������� �������� ��������� � ���� �������� 
//const RNUM METRIC_O=0.000001; // �������� RNUM (�������������� ����������� ��������� => �������� 1 ��)
//typedef double RNUM; // ��� ��� �������� ������� ������� 
//const RNUM RADIAN_O=0.000001; // �������� RNUM (����������� ������� => �������� ~ 3.82e-5 ��������  )

const RNUM METRIC_O=0.000001; // �������� ��������� �������� �������� (�������������� ����������� ��������� => �������� 1 ��)
const RNUM RADIAN_O=0.000001; // �������� ��������� ������� �������� (����������� ������� => �������� ~ 3.82e-5 ��������  )

// typedef Vector V;
// typedef Point P;


/////////////////////////// POINT /////////////////////////////////////////////
class Point //����� ����� {40b}
{	
public:

	const Basis *basis; // ��������� ����� (�� ��������� basis=0 - ���������� �����, �.�. ��������� ���������� ����� ����������)
	RNUM gx; // ���������� X � ����������(!) ������ // ��� ��������� ��������� ������������ x()
	RNUM gy; // ���������� Y � ����������(!) ������ // ��� ��������� ��������� ������������ y()
	RNUM gz; // ���������� Z � ����������(!) ������ // ��� ��������� ��������� ������������ z()
	
	// ����������� �� ���������:
	// plx,ply,plz - ���������� ���������� � ������ *b (b=0 - ���������� �����), notransient=true/false - �������/��������� ������ 
	Point(RNUM plx=0,RNUM ply=0,RNUM plz=0,const Basis *b=0, bool notransient=true);
	// Point(RNUM plx=0,RNUM ply=0,RNUM plz=0,const Basis *b=0,);//notransient=false;

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
	
	Point& Set(RNUM px, RNUM py, RNUM pz,const Basis *b=0); //����� �� ����������� � ������ *b
	Point& SetGlobal(RNUM pgx, RNUM pgy, RNUM pgz); // ����� �� ����������� � ���������� ������
	Point& SetLocal(RNUM localx,RNUM localy, RNUM localz); // �����  �� ����������� � ��������� ������
	Point& SetLocalX(RNUM localx); // �������� ��������� ���������� X
	Point& SetLocalY(RNUM localy); // �������� ��������� ���������� Y
	Point& SetLocalZ(RNUM localz); // �������� ��������� ���������� Z
	Point& SetBasis(const Basis *b); // �������� � ������ *b (b=0 �������� ������� � ���������� �����, �.�.  [��������� �����] = [���������� �����])
	Point& SetGlobalBasis(); // ������� �������� � ������ *basis (basis=0) // ��� �� ��������� ���� SetBasis(0);
	Point& ReplaceBasis(const Basis *b); // �������� ���������� ���������� ����� ����� �������, ����� ��� �������� � ����� ����� *b ��������� ���������� �� ����������
	Point& ReplaceGBasis(const Basis *b); // ���������� ReplaceBasis(Basis *b), �� �������, ��� ��������� �� ����������� ������ (basis -  ������������ � ��������� ������ 0)
	Point& Rotate_W(const Vector &w,RNUM a); // ������� ����� �� ������� ��������� ������������ ��� w �� ���� a
	Point& Rotate_X(RNUM a); //  ������� ����� �� ������� ��������� ������������ ��� OX(� ��������� ������) �� ���� a
	Point& Rotate_Y(RNUM a); //  ������� ����� �� ������� ��������� ������������ ��� OY(� ��������� ������) �� ���� a
	Point& Rotate_Z(RNUM a); //  ������� ����� �� ������� ��������� ������������ ��� OZ(� ��������� ������) �� ���� a
	
	RNUM x() const; // ���������� X � ���������(!) ������ *basis
	RNUM y() const; // ���������� Y � ���������(!) ������ *basis
	RNUM z() const; // ���������� Z � ���������(!) ������ *basis
	RNUM PolarAlpha() const;
	RNUM PolarR() const;
	RNUM lx(const Basis *b) const; // ���������� X � ��������� ������ *b
	RNUM ly(const Basis *b) const; // ���������� Y � ��������� ������ *b
	RNUM lz(const Basis *b) const; // ���������� Z � ��������� ������ *b
	RNUM lx(const Basis &b) const; // ���������� X � ��������� ������ b
	RNUM ly(const Basis &b) const; // ���������� Y � ��������� ������ b
	RNUM lz(const Basis &b) const; // ���������� Z � ��������� ������ b
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

	
	static bool isEqual(const Point &p1, const Point &p2, RNUM e=METRIC_O);


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
	RNUM gx; // �������� �� ��� OX � ����������(!) ������ // ��� ��������� ��������� ������������ x()
	RNUM gy; // �������� �� ��� OY � ����������(!) ������ // ��� ��������� ��������� ������������ y()
	RNUM gz;	// �������� �� ��� OZ � ����������(!) ������ // ��� ��������� ��������� ������������ z()

	// ����������� �� ���������:
	// vx,vy,vz - �������� �� ��� ��������� � ������ *b, ap - ����� ����������(anchor), notransient=true/false=�������/��������� ������.
	Vector(RNUM vx=0, RNUM vy=0, RNUM vz=0, const Point &ap=p_gO,const Basis *b=0, bool notransient=true);
	
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
		
	Vector& Set(RNUM vx, RNUM vy, RNUM vz,const Basis *b=0); //������ �� ��������� � ������ *b
	Vector& SetGlobal(RNUM gx, RNUM gy, RNUM gz);  // ������ �� ��������� � ���������� ������
	Vector& SetLocal(RNUM localx, RNUM localy, RNUM localz); // ������ �� ��������� � ��������� ������
	Vector& SetLocalX(RNUM localx); // �������� ��������� �������� �� ��� OX
	Vector& SetLocalY(RNUM localy); // �������� ��������� �������� �� ��� OY
	Vector& SetLocalZ(RNUM localz); // �������� ��������� �������� �� ��� OZ
	Vector& SetBasis(const Basis *b); // �������� � ������ *b
	Vector& SetGlobalBasis(); // ������� �������� � ������ *basis (basis=0) // ��� �� ��������� ���� SetBasis(0);
	Vector& ReplaceBasis(const Basis *b); // �������� ���������� �������� ������� ����� �������, ����� ��� �������� � ����� ����� *b ��������� �������� �� ���������� (� ��� �� ����� anchor.ReplaceBasis(b))
	Vector& ReplaceGBasis(const Basis *b); // ���������� ReplaceBasis(Basis *b), �� �������, ��� ��������� �� ����������� ������ (basis -  ������������ � ��������� ������ 0)
	Vector& normalize(); // ���������� � ��������� ������ (��������� ������ �� ��� �����)
	Vector& invert(); // ����������� ������ (�������� ������� ������ � �����)
	Vector& rotate_W(const Vector &w, RNUM a); // ������� ������ �� ������� ��������� ������������ ��� w �� ���� a
	Vector& rotateWithoutFulcrum_W(const Vector &w, RNUM a); // ���������� rotate_W(const Vector &w, RNUM a), �� ����� ���������� �������� ����������.
	Vector& rotate_X(RNUM a); // ������� ������ �� ������� ��������� ������������ ��� OX(� ��������� ������) �� ���� a
	Vector& rotate_Y(RNUM a); // ������� ������ �� ������� ��������� ������������ ��� OY(� ��������� ������) �� ���� a
	Vector& rotate_Z(RNUM a); // ������� ������ �� ������� ��������� ������������ ��� OZ(� ��������� ������) �� ���� a	
	
	RNUM x() const; // �������� �� ��� OX � ���������(!) ������ *basis
	RNUM y() const; // �������� �� ��� OY � ���������(!) ������ *basis
	RNUM z() const; // �������� �� ��� OZ � ���������(!) ������ *basis
	RNUM lx(const Basis *b) const; // �������� �� ��� OX � ��������� ������ *b
	RNUM ly(const Basis *b) const; // �������� �� ��� OY � ��������� ������ *b
	RNUM lz(const Basis *b) const; // �������� �� ��� OZ � ��������� ������ *b
	RNUM lx(const Basis &b) const; // �������� �� ��� OX � ��������� ������ b
	RNUM ly(const Basis &b) const; // �������� �� ��� OY � ��������� ������ b
	RNUM lz(const Basis &b) const; // �������� �� ��� OZ � ��������� ������ b
	RNUM length() const; // ����� �������
	Vector e() const; // ��������� ������ �������������� ������� �������
	Point destination() const; // ����� �� ����� �������
	Vector inBasis(const Basis *b) const; // ��� �� ������ � ������ *b
	Vector inGlobalBasis() const; //  ��� �� ������ � ���������� ������
	Vector inReplacedBasis(const Basis *b) const; // ��� �� ������ � ���������� ������ *b	



#ifdef CPPBIKES_USE_TRANGLE	
	TrAngle Angle(const Vector &v) const {return Angle(*this,v);}  // �������� �������� �������
#else
	RNUM Angle(const Vector &v) const {return Angle(*this,v);} 
#endif
	
	Point Intersection(const Vector &v) const; // ����������� ���� ��������. 
	Point RangeIntersection(const Vector &v) const; 
	// ���� ������� �����������, �� ������������ ������� �����(p_null). 
	// ���� ������� ��������������, �� ������ ����������� ��������� ����� �������
	// �� ������� *this � ���������� ������ ������� ������������ ���������� �� ������� v

#ifdef CPPBIKES_USE_TRANGLE	
	static TrAngle Angle(const Vector &v1, const Vector &v2); // ���� ����� ����� ���������
#else
	static RNUM Angle(const Vector &v1, const Vector &v2); // ���� ����� ����� ���������
#endif

	static bool isParallel(const Vector &v1, const Vector &v2); // v1,v2  �����������?
	static RNUM ParallelDistance(const Vector &v1, const Vector &v2); // ����� ���������� ����� ������������� ���������. ���� ������� �� �����������, �� ������������ 0.
	
	static bool isRightVectors(Vector v1, Vector v2, Vector v3=Vector(0,0,1)); // ������ ������ ��������?
	
	// �������� ���������:
	Vector operator + (const Vector &v) const; // �������� ���� ��������
	Vector operator - (const Vector &v) const; // ��������� ���� ��������
	void operator += (const Vector &v); // ��������� � ������� ������� ������ v
	void operator -= (const Vector &v); // ������ �� ������� ������� ������ v
	RNUM operator &(const Vector &v) const; // ��������� ������������ ���� ��������
	Vector operator *(const Vector &v) const; // ��������� ������������ ���� ��������
	Vector operator *(RNUM n) const; // ��������� ������� �� �����
	Vector operator /(RNUM n) const; // ������� ������� �� �����
	void operator *=(RNUM n); // �������� ������ ������, ������� ��� �� n
	void operator /=(RNUM n); // �������� ������ ������, �������� ��� �� n
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
	RNUM operator ^ (const Vector &v) const;// ���������� Angle(v)
#endif
	
	Vector operator [] (const Basis &b) const;// ���������� inBasis(&b)
	Vector operator [] (const Basis *b) const;// ���������� inBasis(b)
	Vector& operator >> (const Basis &b);// ���������� SetBasis(&b)
	Vector& operator >> (const Basis *b);// ���������� SetBasis(b)
	Vector operator !() const;// ���������� Vector(true,*this,false).invert()
	bool operator > (const Vector &v) const;// ���������� length()>v.length()
	bool operator < (const Vector &v) const;// ���������� length()<v.length()


	// Phi & Lamda // (?)
	RNUM Phi();	
	RNUM Lamda();
	RNUM Lamda2PI();


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
	RNUM z;
	RNUM r;
	RNUM a;
};


CylCoord ToCylCoord(const Point &p);
CylCoord ToCylCoord_Arc(const Point &p);

Point FromCylCoord_Arc(RNUM a, RNUM r, RNUM z=0, const Basis *b=0);
//Point FromCylCoord_Arc(TAngle a, RNUM r, RNUM z=0, const Basis *b=0);

}
#endif // BASICGEOMETRY_H

