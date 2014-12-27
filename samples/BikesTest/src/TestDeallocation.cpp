#include "Tests.h"
#include <Bikes/Types.h>
#include <Bikes/Testing.h>
#include <Bikes/Mathem/Constants.h>
#include  <ctime>
#include <iostream>
#include <vector>
#include <Bikes/Array/List.h>

using namespace std;
using namespace Bikes;

struct TestStruct
{
	TestStruct() :ch1(1), ch2(2), ch3(3), ch4(4){}
	char ch1;
	char ch2;
	char ch3;
	char ch4;
	int i1;
	int i2;
	int i3;
	int i4;
};


// new/delete

void test_deallocation()
{
    /*
	typedef TestStruct TestType;
	typedef TestType* TestTypeP;
 	sznum N = 1000 * 1000 * 10;

	std::vector<TestType*> arr1(N);
	std::vector<TestType*> arr2(N);
	
	rnum t;

	BIKES_TIMETEST_START(N)
	arr1[BIKES_TIMETEST_ITER] = new TestType;
	//arr2[BIKES_TIMETEST_ITER] = new TestType;
	BIKES_TIMETEST_FINISH(t)
	cout << " time{x=new Type} = " << t << endl;

	//BIKES_TIMETEST_START(N)					 	
	//BIKES_TIMETEST_FINISH(t);
	//cout << " time{x=new Type} = " << t << endl;

 	

	BIKES_TIMETEST_START(N)	
	delete[] arr1[BIKES_TIMETEST_ITER];
	//delete arr2[BIKES_TIMETEST_ITER];
	BIKES_TIMETEST_FINISH(t)
	cout << "time{delete[]}  = " << t << endl;

	
	BIKES_TIMETEST_START(N)
	
	BIKES_TIMETEST_FINISH(t)
	cout << "time{delete} = " << t << endl;


	N *= 10;
	double a;
	BIKES_TIMETEST_START(N)
	double b = PI*BIKES_TIMETEST_ITER;
	a = b;
	BIKES_TIMETEST_FINISH(t);
	cout << "time{z=x*y=" << a << "} = " << t << endl;
						
	BIKES_TIMETEST_START(N)
	a = sin(PI*BIKES_TIMETEST_ITER);
	BIKES_TIMETEST_FINISH(t);
	cout << "time{z=cos(x*y)="<< a <<"} = " << t << endl;	

	BIKES_TIMETEST_START(N)
	a = sqrt(BIKES_TIMETEST_ITER);
	BIKES_TIMETEST_FINISH(t)
	cout << "time{z=sqrt(x)=" << a << "} = " << t << endl;
	//*/
}




void test_List()
{
	typedef double TestType;
	typedef List<TestType> L;
//	typedef List2<TestType> L2;
	typedef std::vector<TestType> V;
		
    BIKES_COUT_VAR(sizeof(std::vector<TestType>));
	BIKES_COUT_VAR(sizeof(List<TestType>));	
//	cout << "sizeof(List2<TestType>) = " << sizeof(List2<TestType>) << endl;

	sznum N = 100000;
	std::vector<L*> l(N);	
	std::vector<V*> v(N);
//	std::vector<IConstArray<TestType>*> l2(N);

	rnum t;

    std::vector<int>* p_vv = new std::vector<int>(10 * 1000, 0);
    std::vector<int>& vv = *p_vv;



    BIKES_TIMETEST_START(N)
    for (sznum i = 0; i < vv.size(); ++i)
        vv[i] += BIKES_TIMETEST_ITER;
    BIKES_TIMETEST_FINISH(t)
        cout << "t{vv[i] += val} =" << t << endl;

    BIKES_TIMETEST_START(N)
    for (std::vector<int>::iterator i = vv.begin(); i != vv.end(); ++i)
        *i += BIKES_TIMETEST_ITER;
    BIKES_TIMETEST_FINISH(t)
        cout << "t{*i += val} =" << t << endl;


    delete p_vv;

	BIKES_TIMETEST_START(N)
		v[BIKES_TIMETEST_ITER] = new V;
	BIKES_TIMETEST_FINISH(t)
		cout << "t{new V} = " << t << endl;

	BIKES_TIMETEST_START(N)
		delete v[BIKES_TIMETEST_ITER];
	BIKES_TIMETEST_FINISH(t)
		cout << "t{delete V} = " << t << endl;




	BIKES_TIMETEST_START(N)
		l[BIKES_TIMETEST_ITER] = new L;
	BIKES_TIMETEST_FINISH(t)
	cout << "t{new L} = " << t << endl;

	BIKES_TIMETEST_START(N)
		delete l[BIKES_TIMETEST_ITER];
	BIKES_TIMETEST_FINISH(t)
		cout << "t{delete L} = " << t << endl;



											   
// 	BIKES_TIMETEST_START(N)
// 		l2[BIKES_TIMETEST_ITER] = new L2;
// 	BIKES_TIMETEST_FINISH(t)
// 		cout << "t{new L2} = " << t << endl;
// 
// 	BIKES_TIMETEST_START(N)
// 		delete l2[BIKES_TIMETEST_ITER];
// 	BIKES_TIMETEST_FINISH(t)
// 		cout << "t{delete L2} = " << t << endl;
}
