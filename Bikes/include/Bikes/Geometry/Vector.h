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

 	rnum gx; //!< - проекция на ось OX в глобальном(!) базисе. Для получения локальной использовать Vector::x()
	rnum gy; //!< - проекция на ось OY в глобальном(!) базисе. Для получения локальной использовать Vector::y()
	rnum gz; //!< - проекция на ось OZ в глобальном(!) базисе. Для получения локальной использовать Vector::z()

	//! Конструктор по умолчанию для определения в глобальных координатах.
	Vector( 
		rnum globalX = 0, //!< - проекция на ось OX в глобальном базисе.
		rnum globalY = 0, //!< - проекция на ось OY в глобальном базисе.
		rnum globalZ = 0  //!< - проекция на ось OZ в глобальном базисе.
		);

	//! Конструктор для определения в локальных координатах.
	Vector( 
		rnum localX,	//!< - проекция на ось OX в локальном базисе.
		rnum localY,	//!< - проекция на ось OY в локальном базисе.
		rnum localZ,	//!< - проекция на ось OZ в локальном базисе.
		const Basis &b	//!< - локальный базис
		);

//cccccccccccccccccccccccccccc

	
	//! Конструктор для определения по двум точкам вектор
	Vector( 
		const Point &p1, //!< - начало вектора 
		const Point &p2  //!< - конец вектора
		); 

	// Конструктор копирования
	Vector( const Vector &v );
	
	Vector& operator = (const Vector &v); // Аналогично конструктору копирования.

	virtual ~Vector(); 

	virtual rnum x() const; // проекция на ось OX в локальном(!) базисе *basis
	virtual rnum y() const; // проекция на ось OY в локальном(!) базисе *basis
	virtual rnum z() const; // проекция на ось OZ в локальном(!) базисе *basis

	rnum x(const Basis *b) const; // проекция на ось OX в локальном базисе *b
	rnum y(const Basis *b) const; // проекция на ось OY в локальном базисе *b
	rnum z(const Basis *b) const; // проекция на ось OZ в локальном базисе *b

	rnum x(const Basis &b) const; // проекция на ось OX в локальном базисе b
	rnum y(const Basis &b) const; // проекция на ось OY в локальном базисе b
	rnum z(const Basis &b) const; // проекция на ось OZ в локальном базисе b

	void setGlobal(rnum globalX, rnum globalY, rnum globalZ);  // Вектор по проекциям в глобальном базисе
	
	virtual void setLocal(rnum localX, rnum localY, rnum localZ); // Вектор по проекциям в локальном базисе
	
	void setLocal(rnum localX, rnum localY, rnum localZ, const Basis& b); // Вектор по проекциям в локальном базисе b
	
	virtual void setLocalX(rnum localX); // Изменить локальную проекцию на ось OX
	virtual void setLocalY(rnum localY); // Изменить локальную проекцию на ось OY
	virtual void setLocalZ(rnum localZ); // Изменить локальную проекцию на ось OZ

	void setLocalX(rnum localX, const Basis& b); // Изменить локальную проекцию на ось OX
	void setLocalY(rnum localY, const Basis& b); // Изменить локальную проекцию на ось OY
	void setLocalZ(rnum localZ, const Basis& b); // Изменить локальную проекцию на ось OZ
	
	void normalize(); // Превратить в единичный вектор (разделить вектор на его длину)
			
	void rotate_W(const Vector &w, rnum a); // вращать вектор по правилу буравчика относительно оси w на угол a	
	void rotate_W(const Vector &w, const TrAngle& a);
	
	void rotate_globalX(rnum a); // вращать вектор по правилу буравчика относительно оси OX(в локальном базисе) на угол a
	void rotate_globalY(rnum a); // вращать вектор по правилу буравчика относительно оси OY(в локальном базисе) на угол a
	void rotate_globalZ(rnum a); // вращать вектор по правилу буравчика относительно оси OZ(в локальном базисе) на угол a	


	rnum length() const; // длина вектора
	rnum l() const; // длина вектора

	Vector e() const; // единичный вектор соответсвующий данному вектору

	bool isEqual(const Vector& v ) const;
	bool isEqual(const Vector& v, rnum epsilon) const; 
	

#ifdef PREBIKES_USE_TRANGLE	
	TrAngle angle(const Vector &v) const {return angle(*this,v);}  // вероятно ненужная функция
#else
	rnum angle(const Vector &v) const {return angle(*this,v);} 
#endif


#ifdef PREBIKES_USE_TRANGLE	
	static TrAngle angle(const Vector &v1, const Vector &v2); // угол между двумя векторами
#else
	static rnum angle(const Vector &v1, const Vector &v2); // угол между двумя векторами
#endif

	static bool isParallel(const Vector &v1, const Vector &v2); // v1,v2  прарллельны?
	static rnum parallelDistance(const Vector &v1, const Vector &v2); // Найти расстояние между параллельными векторами. Если векторы не параллельны, то возвращается 0.

	static bool isRightVectors(Vector v1, Vector v2, Vector v3=Vector(0,0,1)); // правая тройка векторов?


	// Основные операторы:
	Vector operator + (const Vector& v) const; // сложение двух векторов
	Vector operator - (const Vector& v) const; // вычитание двух векторов
	Vector operator * (rnum n) const; // умножение вектора на число
	Vector operator / (rnum n) const; // деление вектора на число
	rnum   operator & (const Vector& v) const; // скалярное произведение двух векторов
	Vector operator * (const Vector& v) const; // векторное произведение двух вектор

	Vector& operator += (const Vector& v); // прибавить к данному вектору вектор v
	Vector& operator -= (const Vector& v); // отнять от данного вектора вектор v
	Vector& operator *= (rnum n); // изменить данный вектор, умножив его на n
	Vector& operator *= (const Vector& v);
	Vector& operator /= (rnum n); // изменить данный вектор, разделив его на n

	Vector operator -() const; // возвращает (*this)*(-1)

	bool operator ==(const Vector &v) const; // Правда, если проекции вектора v отличаются не более чем на METRIC_O
	bool operator !=(const Vector &v) const; // Неправда если.. (см.выше)
	
	bool operator == (rnum l) const;
	bool operator != (rnum l) const;
	bool operator <  (rnum l) const;
	bool operator <= (rnum l) const;
	bool operator >  (rnum l) const;
	bool operator >= (rnum l) const;


	//	Vector operator +() const;

	// Дополнительные операторы:
	Point operator % (const Vector &v) const;// возвращает Intersection(v)
	bool operator || (const Vector &v) const;// возвращает isParallel(*this,v)
	bool operator |=(const Vector &v) const; // возвращает isRightVectors(*this,v);
	Basis operator && (const Vector &v) const;// возвращает OrtoBasis_ByIJ(*this,v)
	Basis operator && (const Point &p) const;// возвращает OrtoBasis_ByIJ(*this,Vector(anchor,p))

#ifdef PREBIKES_USE_TRANGLE
	TrAngle operator ^ (const Vector &v) const;// возвращает Angle(v)
#else
	rnum operator ^ (const Vector &v) const;// возвращает Angle(v)
#endif

	Vector operator [] (const Basis &b) const;// возвращает inBasis(&b)
	Vector operator [] (const Basis *b) const;// возвращает inBasis(b)
	Vector& operator >> (const Basis &b);// возвращает SetBasis(&b)
	Vector& operator >> (const Basis *b);// возвращает SetBasis(b)
	Vector operator !() const;// возвращает Vector(true,*this,false).invert()
	bool operator > (const Vector &v) const;// возвращает length()>v.length()
	bool operator < (const Vector &v) const;// возвращает length()<v.length()


};

bool isRightHandVectors( const Vector& v1, const Vector& v2, const Vector& v3 );
bool isLeftHandVectors( const Vector& v1, const Vector& v2, const Vector& v3 );

}

#endif