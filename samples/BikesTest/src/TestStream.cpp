#include "Tests.h"

#include <Bikes/Stream/PolymorphicStreamer.h>
#include <Bikes/Stream/ByteStream.h>
#include <Bikes/Array/ByteArray.h>


using namespace Bikes;


class AClassBase
{
public:
    virtual ~AClassBase(){}

    AClassBase():base_var(0)    
    {
    }

    virtual AClassBase* clone() const = 0;

    virtual bool operator == (int b) const
    {
        return false;
    }
    
    double base_var;
};



class AClass : public AClassBase
{
public:
    AClass() :var(42){}

    CBIKES_CLONE_DECLDEF(AClass)

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
public:
    CBIKES_CLONE_DECLDEF(AClass2)
};

class ChildAClass : public AClass
{
public:
    static ChildAClass* create()
    {
        return new ChildAClass();
    }

    CBIKES_CLONE_DECLDEF(ChildAClass)

        operator bool() const
    {
        return false;
    }

private:
    ChildAClass()
    {
    }
};


class BClass
{
public:
    CBIKES_CLONE_DECLDEF(BClass)
};


class ABClass: 
    public AClass, 
    public BClass
{
public:
    CBIKES_CLONE_DECLDEF(ABClass)
};

void test_stream()
{
    ByteArray ba;
    ByteStream out(&ba);
    ByteStream in(&ba);

    {
        double dbl1 =1.1;
        double dbl2 =2.2;
        out << dbl1;
        out << dbl2;
    }

    double dbl1;
    double dbl2;
    in >> dbl1;
    in >> dbl2;
    
}
