#ifndef INCLUDE_BIKES_ARRAY_QUICKARRAY_H
#define INCLUDE_BIKES_ARRAY_QUICKARRAY_H
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

namespace Bikes
{

	template<class T, sznum n>
	class QuickArray
	{
	public:

		QuickArray()
		{
		}

		operator T*()
		{
			return arr;
		}

		operator const T*() const 
		{
			return arr;
		}

		T& operator[](int i)
		{
			return arr[i];
		}

		const T& operator[](int i) const
		{
			return arr[i];
		}

		sznum size() const 
		{
			return n;
		}

		T arr[n];
	};

//===================================================================

#define AUXBIKES_QUICK_ARRAY(N)\
	template<class T>\
	QuickArray<T,N> quick_array(TBIKES_TCRP##N)\
	{\
		QuickArray<T,N> arr;\
		AUXBIKES_QUICKARRAY_FILL_##N(arr,par);\
		return arr;\
	}

MBIKES_FOREACHPARAMLIST(AUXBIKES_QUICK_ARRAY)

//===================================================================

#define AUXBIKES_QUICK_ARRAY_VAL(N)\
	template<class T>\
	QuickArray<T,N> quick_array_val(TBIKES_TP##N)\
{\
	QuickArray<T,N> arr;\
	AUXBIKES_QUICKARRAY_FILL_##N(arr,par);\
	return arr;\
}

MBIKES_FOREACHPARAMLIST(AUXBIKES_QUICK_ARRAY_VAL)

//===================================================================

#define AUXBIKES_QUICK_VECTOR(N)\
	template<class T>\
	std::vector<T> quick_vector(TBIKES_TCRP##N)\
	{\
	std::vector<T> arr(N);\
	AUXBIKES_QUICKARRAY_FILL_##N(arr,par);\
	return arr;\
	}

MBIKES_FOREACHPARAMLIST(AUXBIKES_QUICK_VECTOR)

//===================================================================

#define AUXBIKES_QUICK_VECTOR_VAL(N)\
	template<class T>\
	std::vector<T> quick_vector_val(TBIKES_TP##N)\
	{\
		std::vector<T> arr(N);\
		AUXBIKES_QUICKARRAY_FILL_##N(arr,par);\
		return arr;\
	}

MBIKES_FOREACHPARAMLIST(AUXBIKES_QUICK_VECTOR_VAL)

} 
#endif // <- INCLUDE_BIKES_ARRAY_QUICKARRAY_H
