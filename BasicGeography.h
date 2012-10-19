#ifndef BASICGEOGRAPHY_H
#define BASICGEOGRAPHY_H
#include "BasicMath.h"
#include "BasicGeometry.h"




// ��������� ���������� �����:
const double GEO_A=6378245; // ������� ������� [�]
const double GEO_ALPHA=/*1.0/2.0;//*/(1.0/298.29974); // =(EE_A-EE_B)/EE_A
const double GEO_B=(1.0-GEO_ALPHA)*GEO_A; // ����� ������� [�]
const double GEO_R=(GEO_A+GEO_B)/2.0; // ������� ������ [�]
const double GEO_EE=GEO_ALPHA*(2.0-GEO_ALPHA); // e^2



struct DegMinSecAngle
{
	int deg;
	char min;
	char sec;
	bool negative;

	DegMinSecAngle(int  d=0, char  m=0, char  s=0, bool neg=false);
	DegMinSecAngle(double a_rad){setFromRad(a_rad);}	
	void operator = (double a_rad){setFromRad(a_rad);}
	operator double(){ return toRad();}

	void setFromRad(double a_rad);
	void setFromDeg(double a_deg);
	double toRad();
	double toDeg();
		

	int sign();
};




struct PhiLamCoord // ����� � ��/������ �����������
{
	PhiLamCoord(double Phi=0,double Lamda=0):phi(Phi),lam(Lamda){}
	double phi;
	double lam;
};



// ��� �����:
Point PhiLam_to_PointS(TAMETRIC phi, TAMETRIC lam);  // ������������� (��,�����) � (x,y,z)
PhiLamCoord Point_to_PhiLamS(const Point &p); // ������������� (x,y,z) � (��,�����)

// ��� ����������:
Point PhiLam_to_PointE(TAMETRIC phi, TAMETRIC lam); // ������������� (��,�����) � (x,y,z)
Point PhiLam_to_PointE(const PhiLamCoord &phi_lam);  // ������������� (��,�����) � (x,y,z)
PhiLamCoord Point_to_PhiLamE(const Point &p); // ������������� (x,y,z) � (��,�����)


Vector EllipsePhiTan(const Point &p);
Vector EllipseLamTan(const Point &p);

void MovePointToEllipsoidSurface(Point &p);


#endif