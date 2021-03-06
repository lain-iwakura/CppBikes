#ifndef PREBIKES_SAVEDCOMMANDSMACROS_H
#define PREBIKES_SAVEDCOMMANDSMACROS_H


#define SCMD_BINDFUNCTOR_1(FUNC,P1) Loki::BindFirst(FUNC,P1)
#define SCMD_BINDFUNCTOR_2(FUNC,P1,P2) Loki::BindFirst(SCMD_BINDFUNCTOR_1(FUNC,P1),P2)
#define SCMD_BINDFUNCTOR_3(FUNC,P1,P2,P3) Loki::BindFirst(SCMD_BINDFUNCTOR_2(FUNC,P1,P2),P3)
#define SCMD_BINDFUNCTOR_4(FUNC,P1,P2,P3,P4) Loki::BindFirst(SCMD_BINDFUNCTOR_3(FUNC,P1,P2,P3),P4)
#define SCMD_BINDFUNCTOR_5(FUNC,P1,P2,P3,P4,P5) Loki::BindFirst(SCMD_BINDFUNCTOR_4(FUNC,P1,P2,P3,P4),P5)


#define SCMD_FUNC_R0(FUNC,TR) Loki::Functor<TR>(&FUNC)
#define SCMD_FUNC_R1(FUNC,TR,TP1) Loki::Functor<TR,LOKI_TYPELIST_1(TP1) >(&FUNC)
#define SCMD_FUNC_R2(FUNC,TR,TP1,TP2) Loki::Functor<TR,LOKI_TYPELIST_2(TP1,TP2) >(&FUNC)
#define SCMD_FUNC_R3(FUNC,TR,TP1,TP2,TP3) Loki::Functor<TR,LOKI_TYPELIST_3(TP1,TP2,TP3) >(&FUNC)
#define SCMD_FUNC_R4(FUNC,TR,TP1,TP2,TP3,TP4) Loki::Functor<TR,LOKI_TYPELIST_4(TP1,TP2,TP3,TP4) >(&FUNC)
#define SCMD_FUNC_R5(FUNC,TR,TP1,TP2,TP3,TP4,TP5) Loki::Functor<TR,LOKI_TYPELIST_5(TP1,TP2,TP3,TP4,TP5) >(&FUNC)


#define SCMD_FUNC_0(FUNC) Loki::Functor<void>(&FUNC)
#define SCMD_FUNC_1(FUNC,TP1) Loki::Functor<void,LOKI_TYPELIST_1(TP1) >(&FUNC)
#define SCMD_FUNC_2(FUNC,TP1,TP2) Loki::Functor<void,LOKI_TYPELIST_2(TP1,TP2) >(&FUNC)
#define SCMD_FUNC_3(FUNC,TP1,TP2,TP3) Loki::Functor<void,LOKI_TYPELIST_3(TP1,TP2,TP3) >(&FUNC)
#define SCMD_FUNC_4(FUNC,TP1,TP2,TP3,TP4) Loki::Functor<void,LOKI_TYPELIST_4(TP1,TP2,TP3,TP4) >(&FUNC)
#define SCMD_FUNC_5(FUNC,TP1,TP2,TP3,TP4,TP5) Loki::Functor<void,LOKI_TYPELIST_5(TP1,TP2,TP3,TP4,TP5) >(&FUNC)


#define SCMD_OBJECTFUNC_R0(ClassObj,OBJ,FuncName,TR) Loki::Functor<TR>(&OBJ,(TR(ClassObj::*)())(&ClassObj::FuncName))
#define SCMD_OBJECTFUNC_R1(ClassObj,OBJ,FuncName,TR,TP1) Loki::Functor<TR,LOKI_TYPELIST_1(TP1)>(&OBJ,(TR(ClassObj::*)(TP1))(&ClassObj::FuncName))
#define SCMD_OBJECTFUNC_R2(ClassObj,OBJ,FuncName,TR,TP1,TP2) Loki::Functor<TR,LOKI_TYPELIST_2(TP1,TP2)>(&OBJ,(TR(ClassObj::*)(TP1,TP2))(&ClassObj::FuncName))
#define SCMD_OBJECTFUNC_R3(ClassObj,OBJ,FuncName,TR,TP1,TP2,TP3) Loki::Functor<TR,LOKI_TYPELIST_3(TP1,TP2,TP3)>(&OBJ,(TR(ClassObj::*)(TP1,TP2,TP3))(&ClassObj::FuncName))
#define SCMD_OBJECTFUNC_R4(ClassObj,OBJ,FuncName,TR,TP1,TP2,TP3,TP4) Loki::Functor<TR,LOKI_TYPELIST_4(TP1,TP2,TP3,TP4)>(&OBJ,(TR(ClassObj::*)(TP1,TP2,TP3,TP4))(&ClassObj::FuncName))
#define SCMD_OBJECTFUNC_R5(ClassObj,OBJ,FuncName,TR,TP1,TP2,TP3,TP4,TP5) Loki::Functor<TR,LOKI_TYPELIST_5(TP1,TP2,TP3,TP4,TP5)>(&OBJ,(TR(ClassObj::*)(TP1,TP2,TP3,TP4,TP5))(&ClassObj::FuncName))


#define SCMD_OBJECTFUNC_0(ClassObj,OBJ,FuncName) Loki::Functor<void>(&OBJ, (void(ClassObj::*)()) (&ClassObj::FuncName) )
#define SCMD_OBJECTFUNC_1(ClassObj,OBJ,FuncName,TP1) Loki::Functor<void,LOKI_TYPELIST_1(TP1)>(&OBJ,(void(ClassObj::*)(TP1))(&ClassObj::FuncName))
#define SCMD_OBJECTFUNC_2(ClassObj,OBJ,FuncName,TP1,TP2) Loki::Functor<void,LOKI_TYPELIST_2(TP1,TP2)>(&OBJ,(void(ClassObj::*)(TP1,TP2))(&ClassObj::FuncName))
#define SCMD_OBJECTFUNC_3(ClassObj,OBJ,FuncName,TP1,TP2,TP3) Loki::Functor<void,LOKI_TYPELIST_3(TP1,TP2,TP3)>(&OBJ,(void(ClassObj::*)(TP1,TP2,TP3))(&ClassObj::FuncName))
#define SCMD_OBJECTFUNC_4(ClassObj,OBJ,FuncName,TP1,TP2,TP3,TP4) Loki::Functor<void,LOKI_TYPELIST_4(TP1,TP2,TP3,TP4)>(&OBJ,(void(ClassObj::*)(TP1,TP2,TP3,TP4))(&ClassObj::FuncName))
#define SCMD_OBJECTFUNC_5(ClassObj,OBJ,FuncName,TP1,TP2,TP3,TP4,TP5) Loki::Functor<void,LOKI_TYPELIST_5(TP1,TP2,TP3,TP4,TP5)>(&OBJ,(void(ClassObj::*)(TP1,TP2,TP3,TP4,TP5))(&ClassObj::FuncName))


#define SCMD_FUNCTOR_R0(ClassObj,OBJ,FuncName,TR) SCMD_OBJECTFUNC_R0(ClassObj,OBJ,FuncName,TR)
#define SCMD_FUNCTOR_R1(ClassObj,OBJ,FuncName,TR,TP1,par1) SCMD_BINDFUNCTOR_1(SCMD_OBJECTFUNC_R1(ClassObj,OBJ,FuncName,TR,TP1),par1)
#define SCMD_FUNCTOR_R2(ClassObj,OBJ,FuncName,TR,TP1,par1,TP2,par2) SCMD_BINDFUNCTOR_2(SCMD_OBJECTFUNC_R2(ClassObj,OBJ,FuncName,TR,TP1,TP2),par1,par2)
#define SCMD_FUNCTOR_R3(ClassObj,OBJ,FuncName,TR,TP1,par1,TP2,par2,TP3,par3) SCMD_BINDFUNCTOR_3(SCMD_OBJECTFUNC_R3(ClassObj,OBJ,FuncName,TR,TP1,TP2,TP3),par1,par2,par3)
#define SCMD_FUNCTOR_R4(ClassObj,OBJ,FuncName,TR,TP1,par1,TP2,par2,TP3,par3,TP4,par4) SCMD_BINDFUNCTOR_4(SCMD_OBJECTFUNC_R4(ClassObj,OBJ,FuncName,TR,TP1,TP2,TP3,TP4),par1,par2,par3,par4)
#define SCMD_FUNCTOR_R5(ClassObj,OBJ,FuncName,TR,TP1,par1,TP2,par2,TP3,par3,TP4,par4,TP5,par5) SCMD_BINDFUNCTOR_5(SCMD_OBJECTFUNC_R5(ClassObj,OBJ,FuncName,TR,TP1,TP2,TP3,TP4,TP5),par1,par2,par3,par4,par5)


#define SCMD_FUNCTOR_0(ClassObj,OBJ,FuncName) SCMD_OBJECTFUNC_0(ClassObj,OBJ,FuncName)
#define SCMD_FUNCTOR_1(ClassObj,OBJ,FuncName,TP1,par1) SCMD_BINDFUNCTOR_1(SCMD_OBJECTFUNC_1(ClassObj,OBJ,FuncName,TP1),par1)
#define SCMD_FUNCTOR_2(ClassObj,OBJ,FuncName,TP1,par1,TP2,par2) SCMD_BINDFUNCTOR_2(SCMD_OBJECTFUNC_2(ClassObj,OBJ,FuncName,TP1,TP2),par1,par2)
#define SCMD_FUNCTOR_3(ClassObj,OBJ,FuncName,TP1,par1,TP2,par2,TP3,par3) SCMD_BINDFUNCTOR_3(SCMD_OBJECTFUNC_3(ClassObj,OBJ,FuncName,TP1,TP2,TP3),par1,par2,par3)
#define SCMD_FUNCTOR_4(ClassObj,OBJ,FuncName,TP1,par1,TP2,par2,TP3,par3,TP4,par4) SCMD_BINDFUNCTOR_4(SCMD_OBJECTFUNC_4(ClassObj,OBJ,FuncName,TP1,TP2,TP3,TP4),par1,par2,par3,par4)
#define SCMD_FUNCTOR_5(ClassObj,OBJ,FuncName,TP1,par1,TP2,par2,TP3,par3,TP4,par4,TP5,par5) SCMD_BINDFUNCTOR_4(SCMD_OBJECTFUNC_4(ClassObj,OBJ,FuncName,TP1,TP2,TP3,TP4,TP5),par1,par2,par3,par4,par5)



/*
#define SCMD_OBJECTFUNC_R0(OBJ,FUNC,TR) Loki::Functor<TR>(&OBJ,&FUNC)
#define SCMD_OBJECTFUNC_R1(OBJ,FUNC,TR,TP1) Loki::Functor<TR,LOKI_TYPELIST_1(TP1) >(&OBJ,&FUNC)
#define SCMD_OBJECTFUNC_R2(OBJ,FUNC,TR,TP1,TP2) Loki::Functor<TR,LOKI_TYPELIST_2(TP1,TP2) >(&OBJ,&FUNC)
#define SCMD_OBJECTFUNC_R3(OBJ,FUNC,TR,TP1,TP2,TP3) Loki::Functor<TR,LOKI_TYPELIST_3(TP1,TP2,TP3) >(&OBJ,&FUNC)
#define SCMD_OBJECTFUNC_R4(OBJ,FUNC,TR,TP1,TP2,TP3,TP4) Loki::Functor<TR,LOKI_TYPELIST_4(TP1,TP2,TP3,TP4) >(&OBJ,&FUNC)
#define SCMD_OBJECTFUNC_R5(OBJ,FUNC,TR,TP1,TP2,TP3,TP4,TP5) Loki::Functor<TR,LOKI_TYPELIST_5(TP1,TP2,TP3,TP4,TP5) >(&OBJ,&FUNC)


#define SCMD_OBJECTFUNC_0(OBJ,FUNC) Loki::Functor<void>(&OBJ,&FUNC)
#define SCMD_OBJECTFUNC_1(pOBJ,FUNC,TP1) Loki::Functor<void,LOKI_TYPELIST_1(TP1) >(pOBJ,&FUNC)
#define SCMD_OBJECTFUNC_2(pOBJ,FUNC,TP1,TP2) Loki::Functor<void,LOKI_TYPELIST_2(TP1,TP2) >(pOBJ,&FUNC)
#define SCMD_OBJECTFUNC_3(OBJ,FUNC,TP1,TP2,TP3) Loki::Functor<void,LOKI_TYPELIST_3(TP1,TP2,TP3) >(&OBJ,&FUNC)
#define SCMD_OBJECTFUNC_4(OBJ,FUNC,TP1,TP2,TP3,TP4) Loki::Functor<void,LOKI_TYPELIST_4(TP1,TP2,TP3,TP4) >(&OBJ,&FUNC)
#define SCMD_OBJECTFUNC_5(OBJ,FUNC,TP1,TP2,TP3,TP4,TP5) Loki::Functor<void,LOKI_TYPELIST_5(TP1,TP2,TP3,TP4,TP5) >(&OBJ,&FUNC)
*/

#endif