#include <Bikes/Stream/ByteStream.h>
#include <Bikes/Array/ByteArray.h>
#include <Bikes/Array/List.h>
#include "Tests.h"
#include <Bikes/TypeTools/Info.h>
#include <typeinfo.h>
#include <iostream>
#include <Bikes/Testing.h>
#include <Bikes/TypeTools/ToTypeStack.h>
#include <Bikes/TypeTools/TypeStackHolder.h>
#include <Bikes/AnyObject.h>

using namespace Bikes;
using namespace TT;
using namespace TypeStack;



struct Str
{
	double x;
	double y;
	double z;
};

class AClassBase
{
public:

    virtual bool operator == (int b) const
    {
        return false;
    }

};

class AClass : public AClassBase
{
public:
    AClass() :var(42){}

    bool operator ==(int b) const
    {
        return b == var;
    }
private:
    int var;
    friend class BClass;
};


class AClass2 : public AClassBase
{
};

class ChildAClass : public AClass
{
};


class BClass
{
public:
    BClass() :bbb(777){}
    int bbb;
};


class ABClass: 
    public AClass, 
    public BClass
{
};

typedef TT::TypeStack::Element<
            Element<
                Element<ABClass,BClass>,
                Element<
                    Element<ChildAClass,AClass2>,
                    AClassBase
                    >
                >,
                Element<Element<BClass, ChildAClass>, AClass>
            >
            AClassStack;


typedef RemoveDuplicates<AClassStack>::ResultStack AClassStackD;
typedef SortDescending<AClassStackD, CompareByHierrarchy>::ResultStack AClassSortStack;

#define COMMA ,

#define PRINT_STACK(STACK)                                                     \
    BIKES_COUT_TYPE(TypeAt<STACK COMMA 0>::ResultType);                        \
    BIKES_COUT_TYPE(TypeAt<STACK COMMA 1>::ResultType);                        \
    BIKES_COUT_TYPE(TypeAt<STACK COMMA 2>::ResultType);                        \
    BIKES_COUT_TYPE(TypeAt<STACK COMMA 3>::ResultType);                        \
    BIKES_COUT_TYPE(TypeAt<STACK COMMA 4>::ResultType);                        \
    BIKES_COUT_TYPE(TypeAt<STACK COMMA 5>::ResultType);                        \
    BIKES_COUT_TYPE(TypeAt<STACK COMMA 6>::ResultType);                        \
    BIKES_COUT_TYPE(TypeAt<STACK COMMA 7>::ResultType);                        \
    BIKES_COUT_TYPE(TypeAt<STACK COMMA 8>::ResultType);                        \
    BIKES_COUT_TYPE(TypeAt<STACK COMMA 9>::ResultType);                        \
    BIKES_COUT_TYPE(TypeAt<STACK COMMA 10>::ResultType);                       \
    BIKES_COUT_TYPE(TypeAt<STACK COMMA 11>::ResultType);                       \
    BIKES_COUT_TYPE(TypeAt<STACK COMMA 12>::ResultType);                       \

template<class T, class StackT>
class MyStackHolder
{
public:

    typedef std::vector<int> HeldType;
    MyStackHolder():
        arr(TT::TypeStack::Count<StackT>::result)
    {
    }
    virtual ~MyStackHolder()
    {
    }

    template<num i>
    void initialize()
    {
        arr[i] = sizeof(T) + sizeof(typename TT::TypeStack::TypeAt<StackT,i>::ResultType);
    }

    template<num i>
    void deinitialize()
    {
    }

    HeldType& get()
    {
        return arr;
    }

private:
    std::vector<int> arr;
};


template<class T>
void testFindBaseT(const T* p1, const T* p2)
{
    BIKES_COUT_TYPE(T);
}

using namespace std;
int main()
{

    AnyObject anyObj;

    anyObj.set<ABClass, AClass, BClass, AClassBase, AClass2 >(new ABClass);

    BClass* instB = anyObj.get<BClass>();
    AClass2* instA2 = anyObj.get<AClass2>();
    ABClass* instAB = anyObj.get<ABClass>();
    double* instDouble = anyObj.get<double>();

    double dval = 112345;
    anyObj = dval;

    double* _dval = anyObj.get<double>();

    //testFindBaseT<AClassBase>((AClass2*)(0), (AClass*)(0));



    typedef ToTypeStack<AClass2, AClass, ChildAClass, ABClass, AClassBase, AClass>::ResultStack AFamilyStack;

    auto& aObjects = TypeStackHolder<AFamilyStack>::get();

    auto& ob = TypeStackHolder<NullType>::get();

    typedef ToTypeStack<double, AClassStack, ToTypeStack<float, int>, char >::ResultStack TStack;

    int c = TT::TypeStack::Count<TStack>::result;

    PRINT_STACK(TStack);


    std::vector<int>& arr = TypeStackHolder<TStack, MyStackHolder<int, TStack> >::get();
   
       
    AClass* a = new AClass;
    AClassBase &b = *a;

 
    bool be = (b == 42);

   // int val = BClass::val<TestTMR<int AClass::*, &AClass::var> >(a);

   // BIKES_COUT_VAR(val);

    typedef const AClass * TestType1;
    typedef const TestType1& TestType2;

    BIKES_COUT_VAR(__cplusplus);
/*
    BIKES_COUT_VAR(typeid(TypeInfo<TestType1>::Type()).name());
    BIKES_COUT_VAR(typeid(TypeInfo<TestType1>::ClearType()).name());
    BIKES_COUT_VAR(typeid(TypeInfo<TestType1>::NotReference()).name());
    BIKES_COUT_VAR(typeid(TypeInfo<TestType1>::NotPointerNotReference()).name());
    BIKES_COUT_VAR(typeid(TypeInfo<TestType1>::NotConstNotPointerNotReference()).name());
    BIKES_COUT_VAR(TypeInfo<TestType1>::isConst);
    BIKES_COUT_VAR(TypeInfo<TestType1>::isPointer);
    BIKES_COUT_VAR(TypeInfo<TestType1>::isConstPointer);
    BIKES_COUT_VAR(TypeInfo<TestType1>::isReference);
    BIKES_COUT_VAR(TypeInfo<TestType1>::isConstReference);

    BIKES_COUT_VAR(typeid(TypeInfo<TestType2>::Type()).name());
    BIKES_COUT_VAR(typeid(TypeInfo<TestType2>::ClearType()).name());
    BIKES_COUT_VAR(typeid(TypeInfo<TestType2>::NotReference()).name());
    BIKES_COUT_VAR(typeid(TypeInfo<TestType2>::NotPointerNotReference()).name());
    BIKES_COUT_VAR(typeid(TypeInfo<TestType2>::NotConstNotPointerNotReference()).name());
    BIKES_COUT_VAR(TypeInfo<TestType2>::isConst);
    BIKES_COUT_VAR(TypeInfo<TestType2>::isPointer);
    BIKES_COUT_VAR(TypeInfo<TestType2>::isConstPointer);
    BIKES_COUT_VAR(TypeInfo<TestType2>::isReference);
    BIKES_COUT_VAR(TypeInfo<TestType2>::isConstReference);

  
    bool  f1 = TypeInfo<double>::OtherType<char>::isChildType;
    bool  f2 = TypeInfo<Str>::OtherType<char>::isChildType;

    //*/

	sznum vchar = sizeof(std::vector<char>);
	sznum vint = sizeof(std::vector<int>);
	sznum vdouble = sizeof(std::vector<Str>);

	sznum lchar = sizeof(List<char>);
	sznum lint = sizeof(List<int>);
    sznum ldouble = sizeof(List<Str>);


    //	test_List();
    //test_deallocation();

    //	return 0;
        List<ByteArray>& arr_in = *(new List<ByteArray>);
        List<ByteArray>& arr_out = *(new List<ByteArray>);

            ByteArray io;

            ByteStream bs(&io);

            for (sznum i = 0; i < 240; i++)
            {
                char ch = i;
                char ch2 = i + 2;
                char ch3 = i + 5;
                char ch4 = i + 7;

                ByteArray* ba1 = new ByteArray();
                ByteArray* ba2 = new ByteArray();
                ByteArray* ba3 = new ByteArray();
                ByteArray* ba4 = new ByteArray();

                ba1->push_back(ch);
                ba1->push_back('\0');

                ba2->push_back(ch2);
                ba2->push_back('\0');

                ba3->push_back(ch);
                ba3->push_back(ch2);
                ba3->push_back('\0');

                ba4->push_back(ch3);
                ba4->push_back(ch4);
                ba4->push_back('\0');

                arr_out.take_back(ba1);
                arr_out.take_back(ba2);
                arr_out.take_back(ba3);
                arr_out.take_back(ba4);

                arr_out.push_back(*ba4);
                arr_out.push_back(*ba3);
                arr_out.push_back(*ba2);
                arr_out.push_back(*ba1);

                bs.writeRecurrentData(*ba1);
                bs.writeRecurrentData(*ba2);
                bs.writeRecurrentData(*ba3);
                bs.writeRecurrentData(*ba4);

                bs.writeRecurrentData(*ba4);
                bs.writeRecurrentData(*ba3);
                bs.writeRecurrentData(*ba2);
                bs.writeRecurrentData(*ba1);
            }

            io.setReadIndex(0);
            bs.setIO(&io);

            for (sznum i = 0; i < 240; i++)
            {
                for (sznum j = 0; j < 8; j++)
                {
                    ByteArray *ba = new ByteArray();
                    bs.readRecurrentData(*ba);
                    arr_in.take_back(ba);
                }
            }


            bool ok = true;
            for (sznum i = 0; i < arr_out.size(); i++)
            {
                if (arr_in[i] != arr_out[i])
                    ok = false;
            }


            delete &arr_in;
            delete &arr_out;
            

	return 0;
}
