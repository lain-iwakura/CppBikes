#ifndef INCLUDE_BIKES_TYPECOLLECTING_TYPEHIERRARCHY_H
#define INCLUDE_BIKES_TYPECOLLECTING_TYPEHIERRARCHY_H
#include <Bikes/TypeCollecting/NullTypes.h>

namespace Bikes
{
//==============================================================================
template<class BaseType, class ChildType—andidate>
class TypeHierrarchy
{
private:
    static Inner::SmallType _isChildType(BaseType*);
    static Inner::BigType _isChildType(void*);
public:
    enum{
        exists = sizeof(_isChildType((ChildType—andidate*)0)) == sizeof(Inner::SmallType)
    };    
};
template<class T>
class TypeHierrarchy<T,T>
{
public:
    enum{
        exists = false
    };
};
//==============================================================================
template<class T1, class T2>
struct TypeEqual
{
    enum{
        result = false
    };
};
template<class T>
struct TypeEqual<T, T>
{
    enum{
        result = true
    };
};
//==============================================================================
enum Relation
{
    NoRelation = 0,
    EqualRealtion,
    ChildRealtion,
    ParentRealtion
};

template<class LeftT, class RightT>
struct TypeRelation
{
    enum{
        leftRelation = 
            (TypeHierrarchy<LeftT, RightT>::exists) ? (ParentRealtion) :
            ((TypeHierrarchy<RightT, LeftT>::exists) ? (ChildRealtion) :
            ((TypeEqual<RightT, LeftT>::result) ? (EqualRealtion) :
            (NoRelation))),

        rightRelation =  
            (leftRelation == ChildRealtion) ? (ParentRealtion) :
            ((leftRelation == ParentRealtion) ? (ChildRealtion) :
            ((leftRelation == EqualRealtion) ? (EqualRealtion) :
            (NoRelation)))
    };
    //static const Relation rightRelation;
};

// template<class LeftT,class RightT>
// const Relation TypeRelation<LeftT, RightT>::leftRelation =
//     (TypeHierrarchy<LeftT, RightT>::exists) ? (ParentRealtion) :
//     ((TypeHierrarchy<RightT, LeftT>::exists) ? (ChildRealtion) :
//     ((TypeEqual<RightT, LeftT>::result) ? (EqualRealtion) :
//     (NoRelation)));
// 
// template<class LeftT, class RightT>
// const Relation TypeRelation<LeftT,RightT>::rightRelation = 
//     (leftRelation == ChildRealtion) ? (ParentRealtion) :
//     ((leftRelation == ParentRealtion) ? (ChildRealtion) :
//     ((leftRelation == EqualRealtion) ? (EqualRealtion) :
//     (NoRelation)));

} // Bikes
#endif // <- INCLUDE_BIKES_TYPECOLLECTING_TYPEHIERRARCHY_H

