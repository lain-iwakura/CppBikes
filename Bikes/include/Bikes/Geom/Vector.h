#ifndef INCLUDE_BIKES_GEOM_VECTOR_H
#define INCLUDE_BIKES_GEOM_VECTOR_H

#include <Bikes/Types.h>

namespace Bikes
{

class Basis;
class Point;
class TrAngle;

//! Вектор в 3-х мерном пространстве.
class Vector
{
public:

	//! Конструктор по умолчанию для определения в глобальных координатах.
	Vector( 
		rnum globalX = 0, //!< - проекция на ось OX в глобальном базисе
		rnum globalY = 0, //!< - проекция на ось OY в глобальном базисе
		rnum globalZ = 0  //!< - проекция на ось OZ в глобальном базисе
		);

	//! Конструктор для определения в локальных координатах.
	Vector( 
		rnum localX,	//!< - проекция на ось OX в локальном базисе
		rnum localY,	//!< - проекция на ось OY в локальном базисе
		rnum localZ,	//!< - проекция на ось OZ в локальном базисе
        const IConstBasis &b	//!< - локальный базис.
		);

	//! Конструктор для определения по двум точкам вектор.
	Vector( 
		const Point &p1, //!< - начало вектора
		const Point &p2  //!< - конец вектора
		); 

	//! Конструктор копирования.
	Vector( const Vector &v );

	//! Оператор присваивания.
	Vector& operator = (const Vector &v); 

	//! НЕвиртуальный деструктор.
	 ~Vector(); 

     //! Проекция на ось OX в глобальном базисе. 
     rnum& rx(); //?

     //! Проекция на ось OY в глобальном базисе. 
     rnum& ry(); //?

     //! Проекция на ось OZ в глобальном базисе. 
     rnum& rz(); //?
	
	//! Проекция на ось OX в глобальном базисе. 
	 rnum x() const; 

	//! Проекция на ось OY в глобальном базисе. 
	 rnum y() const; 

	//! Проекция на ось OZ в глобальном базисе. 
	 rnum z() const; 

	//! Проекция на ось OX в базисе *b.
	rnum lx(const IConstBasis *b) const; 

	//! Проекция на ось OY в базисе *b.
	rnum ly(const IConstBasis *b) const; 

	//! Проекция на ось OZ в базисе *b.
	rnum lz(const IConstBasis *b) const; 

	//! Проекция на ось OX в базисе b.
    rnum lx(const IConstBasis &b) const;

	//! Проекция на ось OY в базисе b.
    rnum ly(const IConstBasis &b) const;

	//! Проекция на ось OZ в базисе b.
    rnum lz(const IConstBasis &b) const;

	//! Вектор по проекциям в глобальном базисе.
	void setGlobal(
		rnum globalX, //!< - проекция на ось ОX
		rnum globalY, //!< - проекция на ось ОY
		rnum globalZ  //!< - проекция на ось ОZ
		);  
	

	//! Вектор по проекциям в локальном базисе.
	void setLocal(
		rnum localX, //!< - проекция на ось ОX
		rnum localY, //!< - проекция на ось ОY
		rnum localZ, //!< - проекция на ось ОZ
        const IConstBasis& b //!< - локальный базис
		); 

	//! Установить длину.
	void setLength(rnum len);

	//! Масштабировать
	void scale(rnum scaleFactor);
	
	//! Изменить локальную проекцию на ось OX в базисе b.
    void setLocalX(rnum localX, const IConstBasis& b);

	//! Изменить локальную проекцию на ось OY в базисе b.
    void setLocalY(rnum localY, const IConstBasis& b);

	//! Изменить локальную проекцию на ось OZ в базисе b.
    void setLocalZ(rnum localZ, const IConstBasis& b);

	//! Превратить в единичный вектор (разделить вектор на его длину).
	void normalize(); 
			
	//! Вращать вектор по правилу буравчика в направлении w на угол а.
	void rotate_W(const Vector &w, rnum a); 

	//! Вращать вектор по правилу буравчика в направлении w на угол а.
	void rotate_W(const Vector &w, const TrAngle& a);
	
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
	Vector e() const; 

	//! Проверить на равенство другому вектору.
	bool isEqual(const Vector& v ) const;

	//! Проверить на равенство дргуому веткору с заданной погрешностью.
	bool isEqual(
		const Vector& v, //!< - вектор, с которым сравниваем
		rnum epsilon     //!< - максимальная разница проекций на оси в глобальном базисе сравниваемых векторов
		) const; 

	//! Проверить на колиниарность другому вектору с заданной погрешностью.
	bool isCollinear(
		const Vector& v2, //!< - вектор, с которым сравниваем
		cosnum cos_angleEpsilon //!< - косинус максимально допустимого угла между векторами
		) const;
	
	//! Получить угол между векторами.
	//! \note Медленнее чем cosAngle().
	radian angle(const Vector& v) const;

	//! Получить косинус угла между векторами. 
	//! \note Быстрее чем angle().
	cosnum cosAngle(const Vector& v) const;
	
	//! Получить сумму векторов.
	Vector operator + (const Vector& v) const; 

	//! Получить разницу векторов.
	Vector operator - (const Vector& v) const; 

	//! Получить произведение вектора на число.
	Vector operator * (rnum n) const; 

	// Получить результат деления вектора на число.
	Vector operator / (rnum n) const; 

	//! Получить скалярное произведение двух векторов.
	rnum   operator & (const Vector& v) const; 

	//! Получить Векторное произведение двух вектор.
	Vector operator * (const Vector& v) const; 

	//! Прибавить к данному вектору другой вектор.
	Vector& operator += (const Vector& v); 

	//! Отнять от данного вектора  другой вектор.
	Vector& operator -= (const Vector& v); 

	//! Умножить данный вектор на число.
	Vector& operator *= (rnum n); 

	//! Разделить данный вектор на число.
	Vector& operator /= (rnum n); 

	//! Умножить векторно данный вектор на другой вектор.
	Vector& operator *= (const Vector& v);
	
	//! Получить веткор противоположный данному вектору. 
	Vector operator -() const; 

	//! Проверить на равенство другому вектору.
	bool operator ==(const Vector &v) const; 

	//! Проверить на неравенство другому вектору.
	bool operator !=(const Vector &v) const; 
	
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
	radian operator ^ (const Vector &v) const;
		
	//! Проверить, что длина данного вектора строго больше длины другого вектора.
	bool operator > (const Vector &v) const;

	//! Проверить, что длина данного вектора строго меньше другого вектора.
	bool operator < (const Vector &v) const;

	//! Проверить, что длина данного вектора больше или равна длине другого вектора.
	bool operator >= (const Vector &v) const;

	//! Проверить, что длина данного вектора меньше или равна длине другого вектора.
	bool operator <= (const Vector &v) const;

protected:

    rnum _gx; //!< - проекция на ось OX в глобальном базисе
    rnum _gy; //!< - проекция на ось OY в глобальном базисе
    rnum _gz; //!< - проекция на ось OZ в глобальном базисе
};


//! Проверить правую тройку векторв.
bool isRightHandVectors( const Vector& v1, const Vector& v2, const Vector& v3 );

//! Проверить левую тройку векторв.
bool isLeftHandVectors( const Vector& v1, const Vector& v2, const Vector& v3 );


}

#endif // <- INCLUDE_BIKES_GEOM_VECTOR_H
