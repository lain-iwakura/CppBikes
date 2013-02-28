// BasicGeometry содержит 3 класса, являющиеся инструментом для решения
// геометрических задач на плоскости и в пространстве:
//
// Point - класс точки, задается тремя координатами в глобальной системе координат (далее СК).
// Точка может быть привязана к некоторому базису (локальной СК), 
// что дает возможность работать с локальными координатами. 
//
// Vector - класс вектора, задается точкой приложения (началом) 
// и тремя проекциями на оси координат глобальной СК.
// Вектор так же, как и точка, может быть привязан к некоторому базису (локальной СК) 
//
// Basis - класс базиса (локальная СК), задается точкой (началом координат)
// и тремя единичными векторами (осями координат).
// Если базис уничтожается, все объекты, привязанные к данному базису, переводятся в глобальную СК.


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

//typedef double RNUM; // тип для хранения линейных координат и длин отрезков 
//const RNUM METRIC_O=0.000001; // точность RNUM (предполагаемая размерность километры => точность 1 мм)
//typedef double RNUM; // тип для хранения угловых величин 
//const RNUM RADIAN_O=0.000001; // точность RNUM (размерность радианы => точность ~ 3.82e-5 градусов  )

const RNUM METRIC_O=0.000001; // точность измерения линейных размеров (предполагаемая размерность километры => точность 1 мм)
const RNUM RADIAN_O=0.000001; // точность измерения угловых размеров (размерность радианы => точность ~ 3.82e-5 градусов  )

// typedef Vector V;
// typedef Point P;


/////////////////////////// POINT /////////////////////////////////////////////
class Point //Класс точки {40b}
{	
public:

	const Basis *basis; // локальный базис (по умолчанию basis=0 - глобальный базис, т.е. локальные координаты равны глобальным)
	RNUM gx; // координата X в глобальном(!) базисе // для получения локальной использовать x()
	RNUM gy; // координата Y в глобальном(!) базисе // для получения локальной использовать y()
	RNUM gz; // координата Z в глобальном(!) базисе // для получения локальной использовать z()
	
	// Конструктор по умолчанию:
	// plx,ply,plz - логкальные координаты в базисе *b (b=0 - глобальный базис), notransient=true/false - обычный/временный объект 
	Point(RNUM plx=0,RNUM ply=0,RNUM plz=0,const Basis *b=0, bool notransient=true);
	// Point(RNUM plx=0,RNUM ply=0,RNUM plz=0,const Basis *b=0,);//notransient=false;

	// Конструктор для нулевых (несуществующих) точек:
	// NotNull=true/false => обычная/нулевая точка; gx,gy,gz,*basis копируем из p
	Point(bool NotNull, const Point &p=Point(), bool notransient=true); 
	
	// Консруктор копии:
	// Копируем gx,gy,gz,_null. Привязываемся к базису p.basis. 
	Point(const Point &p); 
	
	// Конструктор задает точку на "конце" вектора v:
	Point(const Vector &v, bool notransient=true); 
	
	void operator =(const Point &p); // Аналогично конструктору копии.
	void operator =(const Vector &v); // Точка на конце вектора. 
	~Point(); // удаляем связь с локальным базисом *basis.
	
	bool isNull() const; // Нулевая(несуществующая) точка?  
	bool isTransient()const; // Временный объект? // *рудимент*
	
	Point& Set(RNUM px, RNUM py, RNUM pz,const Basis *b=0); //Точка по координатам в базисе *b
	Point& SetGlobal(RNUM pgx, RNUM pgy, RNUM pgz); // Точка по координатам в глобальном базисе
	Point& SetLocal(RNUM localx,RNUM localy, RNUM localz); // Точка  по координатам в локальном базисе
	Point& SetLocalX(RNUM localx); // Изменить локальную координату X
	Point& SetLocalY(RNUM localy); // Изменить локальную координату Y
	Point& SetLocalZ(RNUM localz); // Изменить локальную координату Z
	Point& SetBasis(const Basis *b); // Привязка к базису *b (b=0 означает перейти в глобальный базис, т.е.  [локальный базис] = [глобальный базис])
	Point& SetGlobalBasis(); // Удалить привязку к базису *basis (basis=0) // тот же результат дает SetBasis(0);
	Point& ReplaceBasis(const Basis *b); // Изменить глобальные координаты точки таким образом, чтобы при переходе в новый базис *b локальные координаты не изменились
	Point& ReplaceGBasis(const Basis *b); // Аналогично ReplaceBasis(Basis *b), но считаем, что переходим из глобального базиса (basis -  игнорируется и считается равным 0)
	Point& Rotate_W(const Vector &w,RNUM a); // вращать точку по правилу буравчика относительно оси w на угол a
	Point& Rotate_X(RNUM a); //  вращать точку по правилу буравчика относительно оси OX(в локальном базисе) на угол a
	Point& Rotate_Y(RNUM a); //  вращать точку по правилу буравчика относительно оси OY(в локальном базисе) на угол a
	Point& Rotate_Z(RNUM a); //  вращать точку по правилу буравчика относительно оси OZ(в локальном базисе) на угол a
	
	RNUM x() const; // координата X в локальном(!) базисе *basis
	RNUM y() const; // координата Y в локальном(!) базисе *basis
	RNUM z() const; // координата Z в локальном(!) базисе *basis
	RNUM PolarAlpha() const;
	RNUM PolarR() const;
	RNUM lx(const Basis *b) const; // координата X в локальном базисе *b
	RNUM ly(const Basis *b) const; // координата Y в локальном базисе *b
	RNUM lz(const Basis *b) const; // координата Z в локальном базисе *b
	RNUM lx(const Basis &b) const; // координата X в локальном базисе b
	RNUM ly(const Basis &b) const; // координата Y в локальном базисе b
	RNUM lz(const Basis &b) const; // координата Z в локальном базисе b
	Point inGlobalBasis() const; // та же точка в глобальном базисе
	Point inBasis(const Basis *b) const; // та же точка в базисе *b
	Point inReplacedBasis(const Basis *b) const; // та же точка в замещенном базисе (аналог ReplaceBasis())
	Vector v() const;	// преобразовать точку в вектор, начало которого совпадает с началом координат глобального базиса Point(0,0,0), а концом является эта точка.
	
	// Основные операторы:
	bool operator ==(const Point &p) const; // Правда, если точка p лежит в окрестности METRIC_O 
	bool operator !=(const Point &p) const;	// Неправда если... (см. выше)

	// Дополнительные операторы:
	Point operator [] (const Basis &b) const;// возвращает inBasis(&b)
	Point operator [] (const Basis *b) const;// возвращает inBasis(b)
	Point& operator >> (const Basis &b); // возвращает SetBasis(&b)
	Point& operator >> (const Basis *b); // возвращает SetBasis(b);
	Vector operator && (const Point &p) const; // возвращает Vector(*this,p)
	Point operator + (const Vector &v) const; // возвращает Point(Vector(*this)+v)
	Point operator - (const Vector &v) const; // возвращает Point(Vector(*this)-v)
	void operator +=(const Vector &v); // перемещение точки вектором v
	void operator -=(const Vector &v); // перемещение точки вектором -v
	////////////////////////////////

	
	static bool isEqual(const Point &p1, const Point &p2, RNUM e=METRIC_O);


private:

	bool _transient; /*рудимент*/  // _transient=true => временный объект.
	// Временный объект не имеет привязки к базису в котором находится,
	// т.е. в *basis не хранится указатель на данный объект.

	bool _null;	 // _null=true - нулевая точка (несуществующая точка)	

};
const Point p_gO(0,0,0,0); // начало координат глобального базиса
const Point p_null(false,p_gO); // нулевая (несуществующая) точка по умолчанию




/////////////////////////// VECTOR /////////////////////////////////////////////
class Vector // Класс вектора {80b}
{

public:
	const Basis *basis; // локальный базис (basis=0 - глобальный базис, т.е. локальные проекции равны глобальным)
	Point anchor; // точка приложения/привязки вектора (начало вектора)
	RNUM gx; // проекция на ось OX в глобальном(!) базисе // для получения локальной использовать x()
	RNUM gy; // проекция на ось OY в глобальном(!) базисе // для получения локальной использовать y()
	RNUM gz;	// проекция на ось OZ в глобальном(!) базисе // для получения локальной использовать z()

	// Конструктор по умолчанию:
	// vx,vy,vz - проекции на оси координат в базисе *b, ap - точка приложения(anchor), notransient=true/false=обычный/временный объект.
	Vector(RNUM vx=0, RNUM vy=0, RNUM vz=0, const Point &ap=p_gO,const Basis *b=0, bool notransient=true);
	
	// Конструктор создает вектор, началом которого является точка p1, а концом - точка p2,
	// вектор привязывается к базису *b.  
	Vector(const Point &p1, const Point &p2,const Basis *b=0, bool notransient=true); 
	
	// Конструктор для нулевых (несуществующих) векторов:
	// NotNull=true/false => обычный/нулевой вектор; anchor,gx,gy,gz, копируем из v и привязываемся к v.basis;
	Vector(bool NotNull,const Vector &v=Vector(), bool notransient=true);
	
	// Конструктор копии:
	// Копируем _null,anchor,gx,gy,gz, привязываемся к базису v.basis. 
	Vector(const Vector &v);
	
	// Конструктор [точка]->[вектор]:
	// задает вектор, началом которого является начало глобальной СК (Point(0,0,0)),
	// а концом является точка p.
	Vector(const Point &p,  bool notransient=true);
	
	void operator = (const Vector &v); // Аналогично конструктору копии.
	void operator = (const Point &p); // Аналогично конструктору [точка]->[вектор]
	operator Point(){ return destination();}
	~Vector(); // удаляем связь с базисом *basis
	
	bool isNull()const; // нулевой вектор?
	bool isTransient() const; // временный объект? 
		
	Vector& Set(RNUM vx, RNUM vy, RNUM vz,const Basis *b=0); //Вектор по проекциям в базисе *b
	Vector& SetGlobal(RNUM gx, RNUM gy, RNUM gz);  // Вектор по проекциям в глобальном базисе
	Vector& SetLocal(RNUM localx, RNUM localy, RNUM localz); // Вектор по проекциям в локальном базисе
	Vector& SetLocalX(RNUM localx); // Изменить локальную проекцию на ось OX
	Vector& SetLocalY(RNUM localy); // Изменить локальную проекцию на ось OY
	Vector& SetLocalZ(RNUM localz); // Изменить локальную проекцию на ось OZ
	Vector& SetBasis(const Basis *b); // Привязка к базису *b
	Vector& SetGlobalBasis(); // Удалить привязку к базису *basis (basis=0) // тот же результат дает SetBasis(0);
	Vector& ReplaceBasis(const Basis *b); // Изменить глобальные проекции вектора таким образом, чтобы при переходе в новый базис *b локальные проекции не изменились (а так же вызов anchor.ReplaceBasis(b))
	Vector& ReplaceGBasis(const Basis *b); // Аналогично ReplaceBasis(Basis *b), но считаем, что переходим из глобального базиса (basis -  игнорируется и считается равным 0)
	Vector& normalize(); // Превратить в единичный вектор (разделить вектор на его длину)
	Vector& invert(); // Перевернуть вектор (поменять местами начало и конец)
	Vector& rotate_W(const Vector &w, RNUM a); // вращать вектор по правилу буравчика относительно оси w на угол a
	Vector& rotateWithoutFulcrum_W(const Vector &w, RNUM a); // Аналогично rotate_W(const Vector &w, RNUM a), но точка приложения остается неизменной.
	Vector& rotate_X(RNUM a); // вращать вектор по правилу буравчика относительно оси OX(в локальном базисе) на угол a
	Vector& rotate_Y(RNUM a); // вращать вектор по правилу буравчика относительно оси OY(в локальном базисе) на угол a
	Vector& rotate_Z(RNUM a); // вращать вектор по правилу буравчика относительно оси OZ(в локальном базисе) на угол a	
	
	RNUM x() const; // проекция на ось OX в локальном(!) базисе *basis
	RNUM y() const; // проекция на ось OY в локальном(!) базисе *basis
	RNUM z() const; // проекция на ось OZ в локальном(!) базисе *basis
	RNUM lx(const Basis *b) const; // проекция на ось OX в локальном базисе *b
	RNUM ly(const Basis *b) const; // проекция на ось OY в локальном базисе *b
	RNUM lz(const Basis *b) const; // проекция на ось OZ в локальном базисе *b
	RNUM lx(const Basis &b) const; // проекция на ось OX в локальном базисе b
	RNUM ly(const Basis &b) const; // проекция на ось OY в локальном базисе b
	RNUM lz(const Basis &b) const; // проекция на ось OZ в локальном базисе b
	RNUM length() const; // длина вектора
	Vector e() const; // единичный вектор соответсвующий данному вектору
	Point destination() const; // точка на конце вектора
	Vector inBasis(const Basis *b) const; // тот же вектор в базисе *b
	Vector inGlobalBasis() const; //  тот же вектор в глобальном базисе
	Vector inReplacedBasis(const Basis *b) const; // тот же вектор в замещенном базисе *b	



#ifdef CPPBIKES_USE_TRANGLE	
	TrAngle Angle(const Vector &v) const {return Angle(*this,v);}  // вероятно ненужная функция
#else
	RNUM Angle(const Vector &v) const {return Angle(*this,v);} 
#endif
	
	Point Intersection(const Vector &v) const; // Пересечение двух векторов. 
	Point RangeIntersection(const Vector &v) const; 
	// Если вектора параллельны, то возвращается нулевая точка(p_null). 
	// Если вектора скрещивающиеся, то точкой пересечения считается точка лежащая
	// на векторе *this и являющаяся концом отрезка минимального расстояния до вектора v

#ifdef CPPBIKES_USE_TRANGLE	
	static TrAngle Angle(const Vector &v1, const Vector &v2); // угол между двумя векторами
#else
	static RNUM Angle(const Vector &v1, const Vector &v2); // угол между двумя векторами
#endif

	static bool isParallel(const Vector &v1, const Vector &v2); // v1,v2  прарллельны?
	static RNUM ParallelDistance(const Vector &v1, const Vector &v2); // Найти расстояние между параллельными векторами. Если векторы не параллельны, то возвращается 0.
	
	static bool isRightVectors(Vector v1, Vector v2, Vector v3=Vector(0,0,1)); // правая тройка векторов?
	
	// Основные операторы:
	Vector operator + (const Vector &v) const; // сложение двух векторов
	Vector operator - (const Vector &v) const; // вычитание двух векторов
	void operator += (const Vector &v); // прибавить к данному вектору вектор v
	void operator -= (const Vector &v); // отнять от данного вектора вектор v
	RNUM operator &(const Vector &v) const; // скалярное произведение двух векторов
	Vector operator *(const Vector &v) const; // векторное произведение двух векторов
	Vector operator *(RNUM n) const; // умножение вектора на число
	Vector operator /(RNUM n) const; // деление вектора на число
	void operator *=(RNUM n); // изменить данный вектор, умножив его на n
	void operator /=(RNUM n); // изменить данный вектор, разделив его на n
	bool operator ==(const Vector &v) const; // Правда, если проекции вектора v отличаются не более чем на METRIC_O
	bool operator !=(const Vector &v) const; // Неправда если.. (см.выше)
	Vector operator -() const; // возвращает (*this)*(-1)
//	Vector operator +() const;

	// Дополнительные операторы:
	Point operator % (const Vector &v) const;// возвращает Intersection(v)
	bool operator || (const Vector &v) const;// возвращает isParallel(*this,v)
	bool operator |=(const Vector &v) const; // возвращает isRightVectors(*this,v);
	Basis operator && (const Vector &v) const;// возвращает OrtoBasis_ByIJ(*this,v)
	Basis operator && (const Point &p) const;// возвращает OrtoBasis_ByIJ(*this,Vector(anchor,p))

#ifdef CPPBIKES_USE_TRANGLE
	TrAngle operator ^ (const Vector &v) const;// возвращает Angle(v)
#else
	RNUM operator ^ (const Vector &v) const;// возвращает Angle(v)
#endif
	
	Vector operator [] (const Basis &b) const;// возвращает inBasis(&b)
	Vector operator [] (const Basis *b) const;// возвращает inBasis(b)
	Vector& operator >> (const Basis &b);// возвращает SetBasis(&b)
	Vector& operator >> (const Basis *b);// возвращает SetBasis(b)
	Vector operator !() const;// возвращает Vector(true,*this,false).invert()
	bool operator > (const Vector &v) const;// возвращает length()>v.length()
	bool operator < (const Vector &v) const;// возвращает length()<v.length()


	// Phi & Lamda // (?)
	RNUM Phi();	
	RNUM Lamda();
	RNUM Lamda2PI();


private:
	bool _transient; /*рудимент*/ // _transient=true - временный объект (не имеет привязки к базису в котором находится)
	bool _null;  // _null=true - нулевой вектор (несуществующий вектор)
};

const Vector v_gi(1,0,0,p_gO,0); // единичный вектор соответствующий оси OX глобальной СК
const Vector v_gj(0,1,0,p_gO,0); // единичный вектор соответствующий оси OY глобальной СК
const Vector v_gk(0,0,1,p_gO,0); // единичный вектор соответствующий оси OZ глобальной СК
const Vector v_null(false,Vector(0,0,0)); // нулевой вектор по умолчанию


/////////////////////////// BASIS /////////////////////////////////////////////
class Basis // Класс локальной СК {288b}
{
	List<Vector*> *vectors; //список привязанных векторов
	List<Point*> *points; //список привязанных точек
public:
	Point O; // Начало координат
	Vector i; // ось OX
	Vector j; // ось OY
	Vector k; // ось OZ

	// Конструктор по умолчанию:
	// bi,bj,bk,bO задают i,j,k,O
	Basis(const Vector &bi=v_gi,const Vector &bj=v_gj, const Vector &bk=v_gk, const Point &bO=p_gO);

	// Конструктор копии:
	// Копируем: i,j,k,O; Не копируем: vectors, points.
	Basis(const Basis &b);

	void operator =(const Basis &b);  //Аналогично конструктору копии.
	~Basis(); // Все привязанные объекты переводятся в глобальную СК
	// ( vectors[i].basis=0; points[i].basis=0; ) 

	Basis& SetOrtoBasis_ByIJ(const Vector &bi,const Vector &bj); // Ортонормированный правый базис,
	// в котором плоскость OXY задана векторами  bi,bj (bi задает направление i, bi*bj задает направление k, O=bi.anchor)
	Basis& SetOrtoBasisL_ByIJ(const Vector &bi, const Vector &bj);	//То же что и SetOrtoBasis_ByIJ, но базис левый	
	Basis& SetOrtoBasis_InXY_ByI(const Vector &bi); // Ортонормированный правый базис,
	// в котором k=v_gk, k*bi задает направление j,  O=bi.anchor;  
	Basis& SetOrtoBasis_InXY_ByI_l(const Vector &bi); // то же что и	SetOrtoBasis_InXY_ByI, но k=-v_gk;
	Basis& SetOrtoBasisL_InXY_ByI(const Vector &bi); // то же что и	SetOrtoBasis_InXY_ByI, но базис левый; 
	Basis& SetOrtoBasis_ByOXY(const Point &pO, const Point &pX, const Point &pY);	// возвращает SetOrtoBasis_ByIJ(Vector(pO,pX),Vector(pO,pY));
	Basis& SetO(const Point &pO); // Выбрать начало координат 

	void Add(Point *p) const; //(?) Привязать точку 
	void Add(Vector *v) const; //(?) Привязать вектор 
	void Remove(Point *p) const; //(?) удалить привязку точки 
	void Remove(Vector *v) const; //(?) удалить привязку вектора 
	void RemoveAll() const; // удалить все привязки

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

