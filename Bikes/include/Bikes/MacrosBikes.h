#ifndef INCLUDE_BIKES_MACROSBIKES_H
#define INCLUDE_BIKES_MACROSBIKES_H



#define MACROSBIKES_COMMA , 

#define MACROSBIKES_MAXNUMPARAM 9

#define MACROSBIKES_FOREACHPARAMLIST(MACROSNAME)\
    MACROSNAME(0)\
    MACROSNAME(1)\
    MACROSNAME(2)\
    MACROSNAME(3)\
    MACROSNAME(4)\
    MACROSNAME(5)\
    MACROSNAME(6)\
    MACROSNAME(7)\
    MACROSNAME(8)\
    MACROSNAME(9)\

#define MACROSBIKES_COMMA0
#define MACROSBIKES_COMMA1 ,
#define MACROSBIKES_COMMA2 ,
#define MACROSBIKES_COMMA3 ,
#define MACROSBIKES_COMMA4 ,
#define MACROSBIKES_COMMA5 ,
#define MACROSBIKES_COMMA6 ,
#define MACROSBIKES_COMMA7 ,
#define MACROSBIKES_COMMA8 ,
#define MACROSBIKES_COMMA9 ,

#define MACROSBIKES_NOTHING 

#define MACROSBIKES_CT0  
#define MACROSBIKES_CT1 class T1
#define MACROSBIKES_CT2 class T1, class T2
#define MACROSBIKES_CT3 class T1, class T2, class T3
#define MACROSBIKES_CT4 class T1, class T2, class T3, class T4
#define MACROSBIKES_CT5 class T1, class T2, class T3, class T4, class T5
#define MACROSBIKES_CT6 class T1, class T2, class T3, class T4, class T5, class T6
#define MACROSBIKES_CT7 class T1, class T2, class T3, class T4, class T5, class T6, class T7
#define MACROSBIKES_CT8 class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8
#define MACROSBIKES_CT9 class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9

#define MACROSBIKES_CT9_DEFTYPE(DefaultType) class T1=DefaultType, class T2=DefaultType, class T3=DefaultType, class T4=DefaultType, class T5=DefaultType, class T6=DefaultType, class T7=DefaultType, class T8=DefaultType, class T9=DefaultType 
#define MACROSBIKES_CT10_DEFTYPE(DefaultType) class T1=DefaultType, class T2=DefaultType, class T3=DefaultType, class T4=DefaultType, class T5=DefaultType, class T6=DefaultType, class T7=DefaultType, class T8=DefaultType, class T9=DefaultType, class T10=DefaultType 

#define MACROSBIKES_TT0 
#define MACROSBIKES_TT1 T1
#define MACROSBIKES_TT2 T1,T2
#define MACROSBIKES_TT3 T1,T2,T3
#define MACROSBIKES_TT4 T1,T2,T3,T4
#define MACROSBIKES_TT5 T1,T2,T3,T4,T5
#define MACROSBIKES_TT6 T1,T2,T3,T4,T5,T6
#define MACROSBIKES_TT7 T1,T2,T3,T4,T5,T6,T7
#define MACROSBIKES_TT8 T1,T2,T3,T4,T5,T6,T7,T8
#define MACROSBIKES_TT9 T1,T2,T3,T4,T5,T6,T7,T8,T9

#define MACROSBIKES_TTP0  
#define MACROSBIKES_TTP1 T1 par1
#define MACROSBIKES_TTP2 T1 par1, T2 par2
#define MACROSBIKES_TTP3 T1 par1, T2 par2, T3 par3
#define MACROSBIKES_TTP4 T1 par1, T2 par2, T3 par3, T4 par4
#define MACROSBIKES_TTP5 T1 par1, T2 par2, T3 par3, T4 par4, T5 par5
#define MACROSBIKES_TTP6 T1 par1, T2 par2, T3 par3, T4 par4, T5 par5, T6 par6
#define MACROSBIKES_TTP7 T1 par1, T2 par2, T3 par3, T4 par4, T5 par5, T6 par6, T7 par7
#define MACROSBIKES_TTP8 T1 par1, T2 par2, T3 par3, T4 par4, T5 par5, T6 par6, T7 par7, T8 par8
#define MACROSBIKES_TTP9 T1 par1, T2 par2, T3 par3, T4 par4, T5 par5, T6 par6, T7 par7, T8 par8, T9 par9

#define MACROSBIKES_TP0  
#define MACROSBIKES_TP1 T par1
#define MACROSBIKES_TP2 T par1, T par2
#define MACROSBIKES_TP3 T par1, T par2, T par3
#define MACROSBIKES_TP4 T par1, T par2, T par3, T par4
#define MACROSBIKES_TP5 T par1, T par2, T par3, T par4, T par5
#define MACROSBIKES_TP6 T par1, T par2, T par3, T par4, T par5, T par6
#define MACROSBIKES_TP7 T par1, T par2, T par3, T par4, T par5, T par6, T par7
#define MACROSBIKES_TP8 T par1, T par2, T par3, T par4, T par5, T par6, T par7, T par8
#define MACROSBIKES_TP9 T par1, T par2, T par3, T par4, T par5, T par6, T par7, T par8, T par9


#define MACROSBIKES_TTRP0 
#define MACROSBIKES_TTRP1 T1& par1
#define MACROSBIKES_TTRP2 T1& par1, T2& par2
#define MACROSBIKES_TTRP3 T1& par1, T2& par2, T3& par3
#define MACROSBIKES_TTRP4 T1& par1, T2& par2, T3& par3, T4& par4
#define MACROSBIKES_TTRP5 T1& par1, T2& par2, T3& par3, T4& par4, T5& par5
#define MACROSBIKES_TTRP6 T1& par1, T2& par2, T3& par3, T4& par4, T5& par5, T6& par6
#define MACROSBIKES_TTRP7 T1& par1, T2& par2, T3& par3, T4& par4, T5& par5, T6& par6, T7& par7
#define MACROSBIKES_TTRP8 T1& par1, T2& par2, T3& par3, T4& par4, T5& par5, T6& par6, T7& par7, T8& par8
#define MACROSBIKES_TTRP9 T1& par1, T2& par2, T3& par3, T4& par4, T5& par5, T6& par6, T7& par7, T8& par8, T9& par9

#define MACROSBIKES_TRP0  
#define MACROSBIKES_TRP1 T& par1
#define MACROSBIKES_TRP2 T& par1, T& par2
#define MACROSBIKES_TRP3 T& par1, T& par2, T& par3
#define MACROSBIKES_TRP4 T& par1, T& par2, T& par3, T& par4
#define MACROSBIKES_TRP5 T& par1, T& par2, T& par3, T& par4, T& par5
#define MACROSBIKES_TRP6 T& par1, T& par2, T& par3, T& par4, T& par5, T& par6
#define MACROSBIKES_TRP7 T& par1, T& par2, T& par3, T& par4, T& par5, T& par6, T& par7
#define MACROSBIKES_TRP8 T& par1, T& par2, T& par3, T& par4, T& par5, T& par6, T& par7, T& par8
#define MACROSBIKES_TRP9 T& par1, T& par2, T& par3, T& par4, T& par5, T& par6, T& par7, T& par8, T& par9


#define MACROSBIKES_TTCRP0  
#define MACROSBIKES_TTCRP1 const T1& par1
#define MACROSBIKES_TTCRP2 const T1& par1, const T2& par2
#define MACROSBIKES_TTCRP3 const T1& par1, const T2& par2, const T3& par3
#define MACROSBIKES_TTCRP4 const T1& par1, const T2& par2, const T3& par3, const T4& par4
#define MACROSBIKES_TTCRP5 const T1& par1, const T2& par2, const T3& par3, const T4& par4, const T5& par5
#define MACROSBIKES_TTCRP6 const T1& par1, const T2& par2, const T3& par3, const T4& par4, const T5& par5, const T6& par6
#define MACROSBIKES_TTCRP7 const T1& par1, const T2& par2, const T3& par3, const T4& par4, const T5& par5, const T6& par6, const T7& par7
#define MACROSBIKES_TTCRP8 const T1& par1, const T2& par2, const T3& par3, const T4& par4, const T5& par5, const T6& par6, const T7& par7, const T8& par8
#define MACROSBIKES_TTCRP9 const T1& par1, const T2& par2, const T3& par3, const T4& par4, const T5& par5, const T6& par6, const T7& par7, const T8& par8, const T9& par9


#define MACROSBIKES_TCRP0  
#define MACROSBIKES_TCRP1 const T& par1
#define MACROSBIKES_TCRP2 const T& par1, const T& par2
#define MACROSBIKES_TCRP3 const T& par1, const T& par2, const T& par3
#define MACROSBIKES_TCRP4 const T& par1, const T& par2, const T& par3, const T& par4
#define MACROSBIKES_TCRP5 const T& par1, const T& par2, const T& par3, const T& par4, const T& par5
#define MACROSBIKES_TCRP6 const T& par1, const T& par2, const T& par3, const T& par4, const T& par5, const T& par6
#define MACROSBIKES_TCRP7 const T& par1, const T& par2, const T& par3, const T& par4, const T& par5, const T& par6, const T& par7
#define MACROSBIKES_TCRP8 const T& par1, const T& par2, const T& par3, const T& par4, const T& par5, const T& par6, const T& par7, const T& par8
#define MACROSBIKES_TCRP9 const T& par1, const T& par2, const T& par3, const T& par4, const T& par5, const T& par6, const T& par7, const T& par8, const T& par9


#define MACROSBIKES_PP0  
#define MACROSBIKES_PP1 par1
#define MACROSBIKES_PP2 par1,par2
#define MACROSBIKES_PP3 par1,par2,par3
#define MACROSBIKES_PP4 par1,par2,par3,par4
#define MACROSBIKES_PP5 par1,par2,par3,par4,par5
#define MACROSBIKES_PP6 par1,par2,par3,par4,par5,par6
#define MACROSBIKES_PP7 par1,par2,par3,par4,par5,par6,par7
#define MACROSBIKES_PP8 par1,par2,par3,par4,par5,par6,par7,par8
#define MACROSBIKES_PP9 par1,par2,par3,par4,par5,par6,par7,par8,par9


#endif // <- INCLUDE_BIKES_MACROSBIKES_H
