#ifndef _BIKES_QUICKARRAY_H_
#define _BIKES_QUICKARRAY_H_
#include <Bikes/MacrosBikes.h>

#define AUXBIKES_QUICKARRAY_FILL_1(ARR,EL) ARR[0]=EL##1;
#define AUXBIKES_QUICKARRAY_FILL_2(ARR,EL) ARR[0]=EL##1; ARR[1]=EL##2;
#define AUXBIKES_QUICKARRAY_FILL_3(ARR,EL) ARR[0]=EL##1; ARR[1]=EL##2; ARR[2]=EL##3;
#define AUXBIKES_QUICKARRAY_FILL_4(ARR,EL) ARR[0]=EL##1; ARR[1]=EL##2; ARR[2]=EL##3; ARR[3]=EL##4;
#define AUXBIKES_QUICKARRAY_FILL_5(ARR,EL) ARR[0]=EL##1; ARR[1]=EL##2; ARR[2]=EL##3; ARR[3]=EL##4; ARR[4]=EL##5;
#define AUXBIKES_QUICKARRAY_FILL_6(ARR,EL) ARR[0]=EL##1; ARR[1]=EL##2; ARR[2]=EL##3; ARR[3]=EL##4; ARR[4]=EL##5; ARR[5]=EL##6;
#define AUXBIKES_QUICKARRAY_FILL_7(ARR,EL) ARR[0]=EL##1; ARR[1]=EL##2; ARR[2]=EL##3; ARR[3]=EL##4; ARR[4]=EL##5; ARR[5]=EL##6; ARR[6]=EL##7;
#define AUXBIKES_QUICKARRAY_FILL_8(ARR,EL) ARR[0]=EL##1; ARR[1]=EL##2; ARR[2]=EL##3; ARR[3]=EL##4; ARR[4]=EL##5; ARR[5]=EL##6; ARR[6]=EL##7; ARR[7]=EL##8;
#define AUXBIKES_QUICKARRAY_FILL_9(ARR,EL) ARR[0]=EL##1; ARR[1]=EL##2; ARR[2]=EL##3; ARR[3]=EL##4; ARR[4]=EL##5; ARR[5]=EL##6; ARR[6]=EL##7; ARR[7]=EL##8; ARR[8]=EL##9;
//#define AUXBIKES_QUICKARRAY_FILL_10(ARR,EL) ARR[0]=EL##1; ARR[1]=EL##2; ARR[2]=EL##3; ARR[3]=EL##4; ARR[4]=EL##5; ARR[5]=EL##6; ARR[6]=EL##7; ARR[7]=EL##8; ARR[8]=EL##9; ARR[9]=EL##10;

namespace Bikes
{
	template<class T, int n>
	struct QuickArray
	{
		operator T*(){return arr;}
		operator const T*() const {return arr;}
		T& operator[](int i){return arr[i];}
		const T& operator[](int i) const{return arr[i];}
		T arr[n];
	};

//===================================================================

#define AUXBIKES_QUICK_ARRAY(N)\
	template<class T>\
	QuickArray<T,N> quick_array(MACROSBIKES_TCRP##N)\
	{\
		QuickArray<T,N> arr;\
		AUXBIKES_QUICKARRAY_FILL_##N(arr,par);\
		return arr;\
	}

AUXBIKES_QUICK_ARRAY(1)
AUXBIKES_QUICK_ARRAY(2)
AUXBIKES_QUICK_ARRAY(3)
AUXBIKES_QUICK_ARRAY(4)
AUXBIKES_QUICK_ARRAY(5)
AUXBIKES_QUICK_ARRAY(6)
AUXBIKES_QUICK_ARRAY(7)
AUXBIKES_QUICK_ARRAY(8)
AUXBIKES_QUICK_ARRAY(9)

//===================================================================

#define AUXBIKES_QUICK_ARRAY_VAL(N)\
	template<class T>\
	QuickArray<T,N> quick_array_val(MACROSBIKES_TP##N)\
{\
	QuickArray<T,N> arr;\
	AUXBIKES_QUICKARRAY_FILL_##N(arr,par);\
	return arr;\
}


AUXBIKES_QUICK_ARRAY_VAL(1)
AUXBIKES_QUICK_ARRAY_VAL(2)
AUXBIKES_QUICK_ARRAY_VAL(3)
AUXBIKES_QUICK_ARRAY_VAL(4)
AUXBIKES_QUICK_ARRAY_VAL(5)
AUXBIKES_QUICK_ARRAY_VAL(6)
AUXBIKES_QUICK_ARRAY_VAL(7)
AUXBIKES_QUICK_ARRAY_VAL(8)
AUXBIKES_QUICK_ARRAY_VAL(9)

//===================================================================

#define AUXBIKES_QUICK_VECTOR(N)\
	template<class T>\
	std::vector<T> quick_vector(MACROSBIKES_TCRP##N)\
	{\
	std::vector<T> arr(N);\
	AUXBIKES_QUICKARRAY_FILL_##N(arr,par);\
	return arr;\
	}

AUXBIKES_QUICK_VECTOR(1)
AUXBIKES_QUICK_VECTOR(2)
AUXBIKES_QUICK_VECTOR(3)
AUXBIKES_QUICK_VECTOR(4)
AUXBIKES_QUICK_VECTOR(5)
AUXBIKES_QUICK_VECTOR(6)
AUXBIKES_QUICK_VECTOR(7)
AUXBIKES_QUICK_VECTOR(8)
AUXBIKES_QUICK_VECTOR(9)

//===================================================================

#define AUXBIKES_QUICK_VECTOR_VAL(N)\
	template<class T>\
	std::vector<T> quick_vector_val(MACROSBIKES_TP##N)\
	{\
		std::vector<T> arr(N);\
		AUXBIKES_QUICKARRAY_FILL_##N(arr,par);\
		return arr;\
	}

AUXBIKES_QUICK_VECTOR_VAL(1)
AUXBIKES_QUICK_VECTOR_VAL(2)
AUXBIKES_QUICK_VECTOR_VAL(3)
AUXBIKES_QUICK_VECTOR_VAL(4)
AUXBIKES_QUICK_VECTOR_VAL(5)
AUXBIKES_QUICK_VECTOR_VAL(6)
AUXBIKES_QUICK_VECTOR_VAL(7)
AUXBIKES_QUICK_VECTOR_VAL(8)
AUXBIKES_QUICK_VECTOR_VAL(9)


} // CppBikes
#endif