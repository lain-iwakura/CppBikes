#ifndef INCLUDE_BIKES_TBIKES_H
#define INCLUDE_BIKES_TBIKES_H



#define MBIKES_COMMA , 

#define TBIKES_MAXNUMPARAM 9

#define MBIKES_FOREACHPARAMLIST(MACROSNAME)\
    MACROSNAME(0)\
    MACROSNAME(1)\
    MACROSNAME(2)\
    MACROSNAME(3)\
    MACROSNAME(4)\
    MACROSNAME(5)\
    MACROSNAME(6)\
    MACROSNAME(7)\
    MACROSNAME(8)\
    MACROSNAME(9)


#define MBIKES_COMMA0
#define MBIKES_COMMA1 ,
#define MBIKES_COMMA2 ,
#define MBIKES_COMMA3 ,
#define MBIKES_COMMA4 ,
#define MBIKES_COMMA5 ,
#define MBIKES_COMMA6 ,
#define MBIKES_COMMA7 ,
#define MBIKES_COMMA8 ,
#define MBIKES_COMMA9 ,

#define TBIKES_NOTHING 

#define TBIKES_CT(N) TBIKES_CT##N
#define TBIKES_CT0  
#define TBIKES_CT1 class T1
#define TBIKES_CT2 class T1, class T2
#define TBIKES_CT3 class T1, class T2, class T3
#define TBIKES_CT4 class T1, class T2, class T3, class T4
#define TBIKES_CT5 class T1, class T2, class T3, class T4, class T5
#define TBIKES_CT6 class T1, class T2, class T3, class T4, class T5, class T6
#define TBIKES_CT7 class T1, class T2, class T3, class T4, class T5, class T6, class T7
#define TBIKES_CT8 class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8
#define TBIKES_CT9 class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9

#define TBIKES_CT9_DEFTYPE(DefaultType) class T1=DefaultType, class T2=DefaultType, class T3=DefaultType, class T4=DefaultType, class T5=DefaultType, class T6=DefaultType, class T7=DefaultType, class T8=DefaultType, class T9=DefaultType 
#define TBIKES_CT10_DEFTYPE(DefaultType) class T1=DefaultType, class T2=DefaultType, class T3=DefaultType, class T4=DefaultType, class T5=DefaultType, class T6=DefaultType, class T7=DefaultType, class T8=DefaultType, class T9=DefaultType, class T10=DefaultType 

#define TBIKES_TT(N) TBIKES_TT##N
#define TBIKES_TT0 
#define TBIKES_TT1 T1
#define TBIKES_TT2 T1,T2
#define TBIKES_TT3 T1,T2,T3
#define TBIKES_TT4 T1,T2,T3,T4
#define TBIKES_TT5 T1,T2,T3,T4,T5
#define TBIKES_TT6 T1,T2,T3,T4,T5,T6
#define TBIKES_TT7 T1,T2,T3,T4,T5,T6,T7
#define TBIKES_TT8 T1,T2,T3,T4,T5,T6,T7,T8
#define TBIKES_TT9 T1,T2,T3,T4,T5,T6,T7,T8,T9

#define TBIKES_TTP(N) TBIKES_TTP##N
#define TBIKES_TTP0  
#define TBIKES_TTP1 T1 par1
#define TBIKES_TTP2 T1 par1, T2 par2
#define TBIKES_TTP3 T1 par1, T2 par2, T3 par3
#define TBIKES_TTP4 T1 par1, T2 par2, T3 par3, T4 par4
#define TBIKES_TTP5 T1 par1, T2 par2, T3 par3, T4 par4, T5 par5
#define TBIKES_TTP6 T1 par1, T2 par2, T3 par3, T4 par4, T5 par5, T6 par6
#define TBIKES_TTP7 T1 par1, T2 par2, T3 par3, T4 par4, T5 par5, T6 par6, T7 par7
#define TBIKES_TTP8 T1 par1, T2 par2, T3 par3, T4 par4, T5 par5, T6 par6, T7 par7, T8 par8
#define TBIKES_TTP9 T1 par1, T2 par2, T3 par3, T4 par4, T5 par5, T6 par6, T7 par7, T8 par8, T9 par9

#define TBIKES_TP(N) TBIKES_TP##N
#define TBIKES_TP0  
#define TBIKES_TP1 T par1
#define TBIKES_TP2 T par1, T par2
#define TBIKES_TP3 T par1, T par2, T par3
#define TBIKES_TP4 T par1, T par2, T par3, T par4
#define TBIKES_TP5 T par1, T par2, T par3, T par4, T par5
#define TBIKES_TP6 T par1, T par2, T par3, T par4, T par5, T par6
#define TBIKES_TP7 T par1, T par2, T par3, T par4, T par5, T par6, T par7
#define TBIKES_TP8 T par1, T par2, T par3, T par4, T par5, T par6, T par7, T par8
#define TBIKES_TP9 T par1, T par2, T par3, T par4, T par5, T par6, T par7, T par8, T par9

#define TBIKES_TTRP(N) TBIKES_TTRP##N
#define TBIKES_TTRP0 
#define TBIKES_TTRP1 T1& par1
#define TBIKES_TTRP2 T1& par1, T2& par2
#define TBIKES_TTRP3 T1& par1, T2& par2, T3& par3
#define TBIKES_TTRP4 T1& par1, T2& par2, T3& par3, T4& par4
#define TBIKES_TTRP5 T1& par1, T2& par2, T3& par3, T4& par4, T5& par5
#define TBIKES_TTRP6 T1& par1, T2& par2, T3& par3, T4& par4, T5& par5, T6& par6
#define TBIKES_TTRP7 T1& par1, T2& par2, T3& par3, T4& par4, T5& par5, T6& par6, T7& par7
#define TBIKES_TTRP8 T1& par1, T2& par2, T3& par3, T4& par4, T5& par5, T6& par6, T7& par7, T8& par8
#define TBIKES_TTRP9 T1& par1, T2& par2, T3& par3, T4& par4, T5& par5, T6& par6, T7& par7, T8& par8, T9& par9

#define TBIKES_TRP(N) TBIKES_TRP##N
#define TBIKES_TRP0  
#define TBIKES_TRP1 T& par1
#define TBIKES_TRP2 T& par1, T& par2
#define TBIKES_TRP3 T& par1, T& par2, T& par3
#define TBIKES_TRP4 T& par1, T& par2, T& par3, T& par4
#define TBIKES_TRP5 T& par1, T& par2, T& par3, T& par4, T& par5
#define TBIKES_TRP6 T& par1, T& par2, T& par3, T& par4, T& par5, T& par6
#define TBIKES_TRP7 T& par1, T& par2, T& par3, T& par4, T& par5, T& par6, T& par7
#define TBIKES_TRP8 T& par1, T& par2, T& par3, T& par4, T& par5, T& par6, T& par7, T& par8
#define TBIKES_TRP9 T& par1, T& par2, T& par3, T& par4, T& par5, T& par6, T& par7, T& par8, T& par9

#define TBIKES_TTCRP(N) TBIKES_TTCRP0##N
#define TBIKES_TTCRP0  
#define TBIKES_TTCRP1 const T1& par1
#define TBIKES_TTCRP2 const T1& par1, const T2& par2
#define TBIKES_TTCRP3 const T1& par1, const T2& par2, const T3& par3
#define TBIKES_TTCRP4 const T1& par1, const T2& par2, const T3& par3, const T4& par4
#define TBIKES_TTCRP5 const T1& par1, const T2& par2, const T3& par3, const T4& par4, const T5& par5
#define TBIKES_TTCRP6 const T1& par1, const T2& par2, const T3& par3, const T4& par4, const T5& par5, const T6& par6
#define TBIKES_TTCRP7 const T1& par1, const T2& par2, const T3& par3, const T4& par4, const T5& par5, const T6& par6, const T7& par7
#define TBIKES_TTCRP8 const T1& par1, const T2& par2, const T3& par3, const T4& par4, const T5& par5, const T6& par6, const T7& par7, const T8& par8
#define TBIKES_TTCRP9 const T1& par1, const T2& par2, const T3& par3, const T4& par4, const T5& par5, const T6& par6, const T7& par7, const T8& par8, const T9& par9

#define TBIKES_TCRP(N) TBIKES_TCRP##N
#define TBIKES_TCRP0  
#define TBIKES_TCRP1 const T& par1
#define TBIKES_TCRP2 const T& par1, const T& par2
#define TBIKES_TCRP3 const T& par1, const T& par2, const T& par3
#define TBIKES_TCRP4 const T& par1, const T& par2, const T& par3, const T& par4
#define TBIKES_TCRP5 const T& par1, const T& par2, const T& par3, const T& par4, const T& par5
#define TBIKES_TCRP6 const T& par1, const T& par2, const T& par3, const T& par4, const T& par5, const T& par6
#define TBIKES_TCRP7 const T& par1, const T& par2, const T& par3, const T& par4, const T& par5, const T& par6, const T& par7
#define TBIKES_TCRP8 const T& par1, const T& par2, const T& par3, const T& par4, const T& par5, const T& par6, const T& par7, const T& par8
#define TBIKES_TCRP9 const T& par1, const T& par2, const T& par3, const T& par4, const T& par5, const T& par6, const T& par7, const T& par8, const T& par9

#define TBIKES_PP(N) TBIKES_PP##N
#define TBIKES_PP0  
#define TBIKES_PP1 par1
#define TBIKES_PP2 par1,par2
#define TBIKES_PP3 par1,par2,par3
#define TBIKES_PP4 par1,par2,par3,par4
#define TBIKES_PP5 par1,par2,par3,par4,par5
#define TBIKES_PP6 par1,par2,par3,par4,par5,par6
#define TBIKES_PP7 par1,par2,par3,par4,par5,par6,par7
#define TBIKES_PP8 par1,par2,par3,par4,par5,par6,par7,par8
#define TBIKES_PP9 par1,par2,par3,par4,par5,par6,par7,par8,par9

#define CBIKES_THISTYPE_CLONE_DECLDEF virtual ThisType* clone() const { return new ThisType(*this); }

#define CBIKES_CLONE_DECLDEF(ClassName) virtual ClassName* clone() const { return new ClassName(*this); }

#define CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(ClassName)                      \
ClassName(){}                                                                  \
ClassName(const ClassName&){}                                                  \
ClassName& operator=(const ClassName&){ return *this; }                        \
~ClassName(){}

#endif // <- INCLUDE_BIKES_TBIKES_H
