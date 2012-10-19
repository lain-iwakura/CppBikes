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


#ifndef BASICGEOMETRY_H
#define BASICGEOMETRY_H

#include "ContainerInterface.h"
#include "BasicMath.h"

class Basis; 
class Vector;
class Point;
struct CylCoord;


typedef double TMETRIC; // ��� ��� �������� �������� ��������� � ���� �������� 
const TMETRIC TMETRIC_O=0.000001; // �������� TMETRIC (�������������� ����������� ��������� => �������� 1 ��)
typedef double TAMETRIC; // ��� ��� �������� ������� ������� 
const TAMETRIC TAMETRIC_O=0.000001; // �������� TAMETRIC (����������� ������� => �������� ~ 3.82e-5 ��������  )


// typedef Vector Vector;
// typedef Point P;


/////////////////////////// POINT /////////////////////////////////////////////
class Point //����� �����
{	
public:

	const Basis *basis; // ��������� ����� (�� ��������� basis=0 - ���������� �����, �.�. ��������� ���������� ����� ����������)
	TMETRIC gx; // ���������� X � ����������(!) ������ // ��� ��������� ��������� ������������ x()
	TMETRIC gy; // ���������� Y � ����������(!) ������ // ��� ��������� ��������� ������������ y()
	TMETRIC gz;	// ���������� Z � ����������(!) ������ // ��� ��������� ��������� ������������ z()
	
	// ����������� �� ���������:
	// plx,ply,plz - ���������� ���������� � ������ *b (b=0 - ���������� �����), notransient=true/false - �������/��������� ������ 
	Point(TMETRIC plx=0,TMETRIC ply=0,TMETRIC plz=0,const Basis *b=0, bool notransient=true);
	// Point(TMETRIC plx=0,TMETRIC ply=0,TMETRIC plz=0,const Basis *b=0,);//notransient=false;

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
	
	Point& Set(TMETRIC px, TMETRIC py, TMETRIC pz,const Basis *b=0); //����� �� ����������� � ������ *b
	Point& SetGlobal(TMETRIC pgx, TMETRIC pgy, TMETRIC pgz); // ����� �� ����������� � ���������� ������
	Point& SetLocal(TMETRIC localx,TMETRIC localy, TMETRIC localz); // �����  �� ����������� � ��������� ������
	Point& SetLocalX(TMETRIC localx); // �������� ��������� ���������� X
	Point& SetLocalY(TMETRIC localy); // �������� ��������� ���������� Y
	Point& SetLocalZ(TMETRIC localz); // �������� ��������� ���������� Z
	Point& SetBasis(const Basis *b); // �������� � ������ *b (b=0 �������� ������� � ���������� �����, �.�.  [��������� �����] = [���������� �����])
	Point& SetGlobalBasis(); // ������� �������� � ������ *basis (basis=0) // ��� �� ��������� ���� SetBasis(0);
	Point& ReplaceBasis(const Basis *b); // �������� ���������� ���������� ����� ����� �������, ����� ��� �������� � ����� ����� *b ��������� ���������� �� ����������
	Point& ReplaceGBasis(const Basis *b); // ���������� ReplaceBasis(Basis *b), �� �������, ��� ��������� �� ����������� ������ (basis -  ������������ � ��������� ������ 0)
	Point& Rotate_W(const Vector &w,TAMETRIC a); // ������� ����� �� ������� ��������� ������������ ��� w �� ���� a
	Point& Rotate_X(TAMETRIC a); //  ������� ����� �� ������� ��������� ������������ ��� OX(� ��������� ������) �� ���� a
	Point& Rotate_Y(TAMETRIC a); //  ������� ����� �� ������� ��������� ������������ ��� OY(� ��������� ������) �� ���� a
	Point& Rotate_Z(TAMETRIC a); //  ������� ����� �� ������� ��������� ������������ ��� OZ(� ��������� ������) �� ���� a
	
	TMETRIC x() const; // ���������� X � ���������(!) ������ *basis
	TMETRIC y() const; // ���������� Y � ���������(!) ������ *basis
	TMETRIC z() const; // ���������� Z � ���������(!) ������ *basis
	TAMETRIC PolarAlpha() const;
	TMETRIC PolarR() const;
	TMETRIC lx(const Basis *b) const; // ���������� X � ��������� ������ *b
	TMETRIC ly(const Basis *b) const; // ���������� Y � ��������� ������ *b
	TMETRIC lz(const Basis *b) const; // ���������� Z � ��������� ������ *b
	Point inGlobalBasis() const; // �� �� ����� � ���������� ������
	Point inBasis(const Basis *b) const; // �� �� ����� � ������ *b
	Point inReplacedBasis(const Basis *b) const; // �� �� ����� � ���������� ������ (������ ReplaceBasis())
	Vector v() const;	// ������������� ����� � ������, ������ �������� ��������� � ������� ��������� ����������� ������ Point(0,0,0), � ������ �������� ��� �����.
	
	// �������� ���������:
	bool operator ==(const Point &p) const; // ������, ���� ����� p ����� � ����������� TMETRIC_O 
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

	
	static bool isEqual(const Point &p1, const Point &p2, TMETRIC e=TMETRIC_O);


private:

	bool _transient; /*��������*/  // _transient=true => ��������� ������.
	// ��������� ������ �� ����� �������� � ������ � ������� ���������,
	// �.�. � *basis �� �������� ��������� �� ������ ������.

	bool _null;	 // _null=true - ������� ����� (�������������� �����)	

};
const Point p_gO(0,0,0,0); // ������ ��������� ����������� ������
const Point p_null(false,p_gO); // ������� (��������������) ����� �� ���������




/////////////////////////// VECTOR /////////////////////////////////////////////
class Vector // ����� �������
{

public:
	const Basis *basis; // ��������� ����� (basis=0 - ���������� �����, �.�. ��������� �������� ����� ����������)
	Point fulcrum; // ����� ���������� ������� (������ �������)
	TMETRIC gx; // �������� �� ��� OX � ����������(!) ������ // ��� ��������� ��������� ������������ x()
	TMETRIC gy; // �������� �� ��� OY � ����������(!) ������ // ��� ��������� ��������� ������������ y()
	TMETRIC gz;	// �������� �� ��� OZ � ����������(!) ������ // ��� ��������� ��������� ������������ z()

	// ����������� �� ���������:
	// vx,vy,vz - �������� �� ��� ��������� � ������ *b, fp - ����� ����������(fulcrum), notransient=true/false=�������/��������� ������.
	Vector(TMETRIC vx=0, TMETRIC vy=0, TMETRIC vz=0, const Point &fp=p_gO,const Basis *b=0, bool notransient=true);
	
	// ����������� ������� ������, ������� �������� �������� ����� p1, � ������ - ����� p2,
	// ������ ������������� � ������ *b.  
	Vector(const Point &p1, const Point &p2,const Basis *b=0, bool notransient=true); 
	
	// ����������� ��� ������� (��������������) ��������:
	// NotNull=true/false => �������/������� ������; fulcrum,gx,gy,gz, �������� �� v � ������������� � v.basis;
	Vector(bool NotNull,const Vector &v=Vector(), bool notransient=true);
	
	// ����������� �����:
	// �������� _null,fulcrum,gx,gy,gz, ������������� � ������ v.basis. 
	Vector(const Vector &v);
	
	// ����������� [�����]->[������]:
	// ������ ������, ������� �������� �������� ������ ���������� �� (Point(0,0,0)),
	// � ������ �������� ����� p.
	Vector(const Point &p,  bool notransient=true);
	
	void operator = (const Vector &v); // ���������� ������������ �����.
	void operator = (const Point &p); // ���������� ������������ [�����]->[������]
	~Vector(); // ������� ����� � ������� *basis
	
	bool isNull()const; // ������� ������?
	bool isTransient() const; // ��������� ������? 
		
	Vector& Set(TMETRIC vx, TMETRIC vy, TMETRIC vz,const Basis *b=0); //������ �� ��������� � ������ *b
	Vector& SetGlobal(TMETRIC gx, TMETRIC gy, TMETRIC gz);  // ������ �� ��������� � ���������� ������
	Vector& SetLocal(TMETRIC localx, TMETRIC localy, TMETRIC localz); // ������ �� ��������� � ��������� ������
	Vector& SetLocalX(TMETRIC localx); // �������� ��������� �������� �� ��� OX
	Vector& SetLocalY(TMETRIC localy); // �������� ��������� �������� �� ��� OY
	Vector& SetLocalZ(TMETRIC localz); // �������� ��������� �������� �� ��� OZ
	Vector& SetBasis(const Basis *b); // �������� � ������ *b
	Vector& SetGlobalBasis(); // ������� �������� � ������ *basis (basis=0) // ��� �� ��������� ���� SetBasis(0);
	Vector& ReplaceBasis(const Basis *b); // �������� ���������� �������� ������� ����� �������, ����� ��� �������� � ����� ����� *b ��������� �������� �� ���������� (� ��� �� ����� fulcrum.ReplaceBasis(b))
	Vector& ReplaceGBasis(const Basis *b); // ���������� ReplaceBasis(Basis *b), �� �������, ��� ��������� �� ����������� ������ (basis -  ������������ � ��������� ������ 0)
	Vector& normalize(); // ���������� � ��������� ������ (��������� ������ �� ��� �����)
	Vector& invert(); // ����������� ������ (�������� ������� ������ � �����)
	Vector& rotate_W(const Vector &w, TAMETRIC a); // ������� ������ �� ������� ��������� ������������ ��� w �� ���� a
	Vector& rotateWithoutFulcrum_W(const Vector &w, TAMETRIC a); // ���������� rotate_W(const Vector &w, TAMETRIC a), �� ����� ���������� �������� ����������.
	Vector& rotate_X(TAMETRIC a); // ������� ������ �� ������� ��������� ������������ ��� OX(� ��������� ������) �� ���� a
	Vector& rotate_Y(TAMETRIC a); // ������� ������ �� ������� ��������� ������������ ��� OY(� ��������� ������) �� ���� a
	Vector& rotate_Z(TAMETRIC a); // ������� ������ �� ������� ��������� ������������ ��� OZ(� ��������� ������) �� ���� a	
	
	TMETRIC x() const; // �������� �� ��� OX � ���������(!) ������ *basis
	TMETRIC y() const; // �������� �� ��� OY � ���������(!) ������ *basis
	TMETRIC z() const; // �������� �� ��� OZ � ���������(!) ������ *basis
	TMETRIC lx(const Basis *b) const; // �������� �� ��� OX � ��������� ������ *b
	TMETRIC ly(const Basis *b) const; // �������� �� ��� OY � ��������� ������ *b
	TMETRIC lz(const Basis *b) const; // �������� �� ��� OZ � ��������� ������ *b
	TMETRIC length() const; // ����� �������
	Vector e() const; // ��������� ������ �������������� ������� �������
	Point destination() const; // ����� �� ����� �������
	Vector inBasis(const Basis *b) const; // ��� �� ������ � ������ *b
	Vector inGlobalBasis() const; //  ��� �� ������ � ���������� ������
	Vector inReplacedBasis(const Basis *b) const; // ��� �� ������ � ���������� ������ *b	

// 	TAngle AngleA(const Vector &v) const;  // � �������� ����������
	TAMETRIC Angle(const Vector &v) const {return Angle(*this,v);} 
	
	Point Intersection(const Vector &v) const; // ����������� ���� ��������. 
	Point RangeIntersection(const Vector &v) const; 
	// ���� ������� �����������, �� ������������ ������� �����(p_null). 
	// ���� ������� ��������������, �� ������ ����������� ��������� ����� �������
	// �� ������� *this � ���������� ������ ������� ������������ ���������� �� ������� v
	
	static TAMETRIC Angle(const Vector &v1, const Vector &v2); // ���� ����� ����� ���������
	static bool isParallel(const Vector &v1, const Vector &v2); // v1,v2  �����������?
	static TMETRIC ParallelDistance(const Vector &v1, const Vector &v2); // ����� ���������� ����� ������������� ���������. ���� ������� �� �����������, �� ������������ 0.
	
	static bool isRightVectors(Vector v1, Vector v2, Vector v3=Vector(0,0,1)); // ������ ������ ��������?
	
	// �������� ���������:
	Vector operator + (const Vector &v) const; // �������� ���� ��������
	Vector operator - (const Vector &v) const; // ��������� ���� ��������
	void operator += (const Vector &v); // ��������� � ������� ������� ������ v
	void operator -= (const Vector &v); // ������ �� ������� ������� ������ v
	TMETRIC operator &(const Vector &v) const; // ��������� ������������ ���� ��������
	Vector operator *(const Vector &v) const; // ��������� ������������ ���� ��������
	Vector operator *(TMETRIC n) const; // ��������� ������� �� �����
	Vector operator /(TMETRIC n) const; // ������� ������� �� �����
	void operator *=(TMETRIC n); // �������� ������ ������, ������� ��� �� n
	void operator /=(TMETRIC n); // �������� ������ ������, �������� ��� �� n
	bool operator ==(const Vector &v) const; // ������, ���� �������� ������� v ���������� �� ����� ��� �� TMETRIC_O
	bool operator !=(const Vector &v) const; // �������� ����.. (��.����)
	Vector operator -() const; // ���������� (*this)*(-1)
//	Vector operator +() const;

	// �������������� ���������:
	Point operator % (const Vector &v) const;// ���������� Intersection(v)
	bool operator || (const Vector &v) const;// ���������� isParallel(*this,v)
	bool operator |=(const Vector &v) const; // ���������� isRightVectors(*this,v);
	Basis operator && (const Vector &v) const;// ���������� OrtoBasis_ByIJ(*this,v)
	Basis operator && (const Point &p) const;// ���������� OrtoBasis_ByIJ(*this,Vector(fulcrum,p))
	TAMETRIC operator ^ (const Vector &v) const;// ���������� AngleA(v)
	Vector operator [] (const Basis &b) const;// ���������� inBasis(&b)
	Vector operator [] (const Basis *b) const;// ���������� inBasis(b)
	Vector& operator >> (const Basis &b);// ���������� SetBasis(&b)
	Vector& operator >> (const Basis *b);// ���������� SetBasis(b)
	Vector operator !() const;// ���������� Vector(true,*this,false).invert()
	bool operator > (const Vector &v) const;// ���������� length()>v.length()
	bool operator < (const Vector &v) const;// ���������� length()<v.length()


	// Phi & Lamda // (?)
	TAMETRIC Phi();	
	TAMETRIC Lamda();
	TAMETRIC Lamda2PI();


private:
	bool _transient; /*��������*/ // _transient=true - ��������� ������ (�� ����� �������� � ������ � ������� ���������)
	bool _null;  // _null=true - ������� ������ (�������������� ������)
};

const Vector v_gi(1,0,0,p_gO,0); // ��������� ������ ��������������� ��� OX ���������� ��
const Vector v_gj(0,1,0,p_gO,0); // ��������� ������ ��������������� ��� OY ���������� ��
const Vector v_gk(0,0,1,p_gO,0); // ��������� ������ ��������������� ��� OZ ���������� ��
const Vector v_null(false,Vector(0,0,0)); // ������� ������ �� ���������


/////////////////////////// BASIS /////////////////////////////////////////////
class Basis // ����� ��������� �� 
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
	// � ������� ��������� OXY ������ ���������  bi,bj (bi ������ ����������� i, bi*bj ������ ����������� k, O=bi.fulcrum)
	Basis& SetOrtoBasisL_ByIJ(const Vector &bi, const Vector &bj);	//�� �� ��� � SetOrtoBasis_ByIJ, �� ����� �����	
	Basis& SetOrtoBasis_InXY_ByI(const Vector &bi); // ����������������� ������ �����,
	// � ������� k=v_gk, k*bi ������ ����������� j,  O=bi.fulcrum;  
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
	TMETRIC z;
	TMETRIC r;
	TAMETRIC a;
};


CylCoord ToCylCoord(const Point &p);
CylCoord ToCylCoord_Arc(const Point &p);

Point FromCylCoord_Arc(TAMETRIC a, TMETRIC r, TMETRIC z=0, const Basis *b=0);
//Point FromCylCoord_Arc(TAngle a, TMETRIC r, TMETRIC z=0, const Basis *b=0);


#endif // BASICGEOMETRY_H

