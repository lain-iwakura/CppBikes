#include "PlaneAnalysis.h"



List<IntersectPoint> FindIntersectPoints(AbstractLine *al1, AbstractLine *al2)
{
	List<IntersectPoint> ret;

	const List<Point> &inte=AbstractLine::LinesIntersections(al1,al2,true);	

	for(int i=0; i<inte.count(); i++)
	{
		TMETRIC s1=(inte[i]==al1->StartPoint())?(0):(al1->SCoordinateFromPoint(inte[i]));
		TMETRIC s2=(inte[i]==al2->StartPoint())?(0):(al2->SCoordinateFromPoint(inte[i]));

		int j=0;
		while(j<ret.count())
		{
			if(s1<ret[j].s1)break;
			j++;
		}

		bool right12;

		Vector v1=(s1==0)?(al1->InDirection()):(al1->sDirection(s1));
		Vector v2=(s2==0)?(al2->InDirection()):(al2->sDirection(s2));

		int rl_up=0; // Положение верхних концов пересечения (al2_up относительно al1_up)
		int rl_down=0; // Положение нижних концов пересечения (al2_down относительно al1_down)


		AbstractLine *al1_up=al1;
		AbstractLine *al2_up=al2;
		Vector v1_up=v1;
		Vector v2_up=v2;
		TMETRIC s1_up=s1;
		TMETRIC s2_up=s2;
		
		
		 
		for(;;) 
		{
				if(v1_up||v2_up) // совпадающее пересечение  ||
				{
					Vector rc1=(s1_up==0)?(al1_up->InRCurvature()):(al1_up->sRCurvature(s1));
					Vector rc2=(s2_up==0)?(al2_up->InRCurvature()):(al2_up->sRCurvature(s2));
					if(rc1.isNull()) // al1 - прямая  -
					{
						if(rc2.isNull()) // al2 - прямая	-
						{
							rl_up=0; // (!)
							// (?)
						}else // al2 - кривая	~
						{
							rl_up=(Vector::isRightVectors(v1_up,rc2))?(-1):(1);							
						}
					}else // al1 - кривая	~
					{
						if(rc2.isNull()) // al2 - прямая	-
						{
							rl_up=(Vector::isRightVectors(v1_up,rc1))?(1):(-1);							
						}else // al2 - кривая	~
						{
							if((rc1&rc2)<0) // противоположно-выпуклые  )(
							{
								rl_up=(Vector::isRightVectors(v1_up,rc2))?(-1):(1);								
							}else if(rc1==rc2) // равные кривизны   ((
							{
								rl_up=0; // (!)
								// (?)									
							}else // односторонне-выпуклые	(c
							{
								rl_up=(Vector::isRightVectors(v1_up,rc1)==(rc2<rc1))?(-1):(1);																	
							}
						}
					}
				}else // несовпадающее пересечение  \|
				{					
					rl_up=(Vector::isRightVectors(v1_up,v2_up))?(-1):(1);					
				}


			
				if(rl_up==0) // совпадение ||
				{				
					TMETRIC l1_up=al1_up->length()-s1_up;
					TMETRIC l2_up=al2_up->length()-s2_up;

					if(l1_up<l2_up) // переход вверх по первой линии
					{
						s1_up=0;
						s2_up=l2_up-l1_up;
						al1_up=al1_up->next();

						if(al1_up==0||al1_up==al1) break; //Верхний обрыв полилинии || зацикливание

						v1_up=al1_up->InDirection();
						v2_up=al2_up->sDirection(s2_up);
						
					}else // переход вверх по второй линии
					{
						s1_up=l1_up-l2_up;
						s2_up=0;
						al2_up=al2_up->next();

						if(al2_up==0||al2_up==al2) break; //Верхний обрыв полилинии || зацикливание

						v1_up=al1_up->sDirection(s1_up);
						v2_up=al2_up->InDirection();
					}
				}else // несовпадение (пересечение определено)
				{
					break;
				}				
		}// <- for(;;)					
						
		
		if(s1==0||s2==0) // пересечение на концах
		{
			AbstractLine *al1_down=al1;
			AbstractLine *al2_down=al2;
			Vector prV1=v1;
			Vector prV2=v2;

			if(s1==0) // пересечение на конце al1
			{
				al1_down=al1->previous();
				if(al1_down)
				{
					prV1=al1_down->OutDirection();
				}else{continue;} // Касание & нижний обрыв полилинии	K					
			}

			if(s2==0) // пересечение на конце al2
			{
				al2_down=al2->previous();
				if(al2_down)
				{
					prV2=al2_down->OutDirection();
				}else{continue;} // Касание & нижний обрыв полилинии	K
			}
					
			if(prV1||prV2) // совпадающее пересечение ||
			{
				Vector prRc1=al1_down->OutRCurvature();
				Vector prRc2=al2_down->OutRCurvature();
						
				if(prRc1.isNull()) // prAl1 - прямая  -
				{
					if(prRc2.isNull()) //prAl2 - прямая  -
					{
						rl_down=0;
					}else // prAl2 - кривая  ~
					{
						rl_down=(Vector::isRightVectors(prV1,prRc2))?(-1):(1);
					}
				}else // prAl1 - кривая  ~
				{
						if(prRc2.isNull()) // prAl2 - прямая  -
						{
							rl_down=(Vector::isRightVectors(prV2,prRc1))?(1):(-1);
						}else // prAl2 - кривая  ~
						{
							if((prRc1&prRc2)<0) // противоположно-выпуклые )(
							{
								rl_down=(Vector::isRightVectors(prV1,prRc2))?(-1):(1);
							}else if(prRc1==prRc2) // равные кривизны ((
							{
								rl_down=0;										
							}else // односторонне-выпуклые (c
							{
								rl_down=(Vector::isRightVectors(prV2,prRc1)==(prRc2<prRc1))?(-1):(1);									
							}
						}
					}
				}else // несовпадающее пересечение  \|
				{
					rl_down=(Vector::isRightVectors(prV1,prV2))?(1):(-1);
				}		

		}else // нормальное пересечение
		{
			rl_down=-rl_up;
		}


		if(rl_up==0||rl_down==0) //совпадение концов // Верхний обрыв полилинии (касание) || зацикливание :-(
		{
			/////////////////////???					
			continue;  
			/////////////////////???
		
		}else // несовпадение концов
		{
			if(rl_up!=rl_down) // Пересечение X
			{
				right12=(rl_up<0);				
			}else // Касание K 
			{
				continue;				
			}				
		}	

		ret.Insert(j,IntersectPoint(al1,al2,inte[i],s1,s2,right12));
	}
	

	return ret;
}






/*
						if(rc2.isNull()) //al2 - прямaя 
						{
							//???
							//???
							//???
						}else //al2 - кривая 
						{				
							Vector prRc2=prAl2->OutRCurvature();
							if(prRc2.isNull()) //предшествующая(al2) - прямая
							{
								if(prAl2->OutDirection()||
							}else //предшествующая(al2) - кривая
							{

							}
						}
					}else // несовпадающее пересечение	\|
					{
						Vector prV2=prAl2->OutDirection();						
						if(prV2||v1) //предшествующее(al2) совпадающее пересечение	||
						{
							Vector prRc2=prAl2->OutRCurvature();
							Vector rc1=al1->sRCurvature(s1);
							if(prRc2.isNull()) //предшествующая(al2) - прямая
							{
								if(rc1.isNull()) // al1 - прямая
								{
									// Здесь не обрабатывается (?)
									//	???
									//	???
									//	???
								}else // al1 - кривая
								{
									Vector::isRightVectors(rc1,v1);
									if(rc1&v2<0) // Касание  K
									{
										continue; 
									}else // Пересечение X
									{
										right12=Vector::isRightVectors(v1,v2);
									}
								}
							}else  //предшествующая(al2) - кривая
							{
								bool bX=(rc1.isNull()||((rc1&prRc2)<0)||(prRc2<rc1)) // правда, если al1 прямая или противоположно-выпуклая кривая или кривая с большей кривизной
								
								// Случай с равными кривизнами никак не обрабатывается! (?)
									
								if(((prRc2&v2)>0)==bX)) // Касание K
								{			
									continue;
								}else // Пересечение X
								{
									right12=Vector::isRightVectors(v1,v2);
								}																
							}							
						}else //предшествующее несовпадающее пересечение	\|
						{
							bool r12=Vector::isRightVectors(v1,v2);
							bool prR12=Vector::isRightVectors(v1,prV2);
							if(r12==prR12) // Пересечение!	X
							{
								right12=r12;
							} else {continue;} // Касание!	K
						}
						//*/
/*
		if(s1==0) //пересечение на конце 1ой линии
		{
			AbstractLine *prAl1=al1->previous();
			if(prAl1) // предшествующая часть полилинии(al1)
			{
				if(v1||v2) // совпадающее пересечение	||
				{
					//???
					//???
					//???
				}else // несовпадающее пересечение		\|
				{
				
					Vector prV1=prAl1->OutDirection();					
					if(prV1||v2) // предшествующее совпадающее пересечение ||
					{
						Vector prRc1=prAl1->OutRCurvature();
						if(prRc1.isNull()) //предшествующая прямая
						{
							//???
							//???
							//???
						}else  //предшествющая кривая
						{
							Vector rc2=al2->sRCurvature(s2);

							bool bX=(rc2.isNull()||((rc2&prRc1)<0)||(prRc1<rc2)); // правда, если al2 прямая или противоположно-выпуклая кривая или кривая с большей кривизной
								
							if(((prRc1&v1)>0)==bX) // Касание K
							{
								continue;
							}else // Пересечение X
							{
								right12=Vector::isRightVectors(v1,v2);
							}
						}		
					}else //предшествующее несовпадающее пересечение \|
					{
						bool r12=Vector::isRightVectors(v1,v2);
						bool prR12=Vector::isRightVectors(prV1,v2);
						if(r12==prR12) // Пересечение!	X
						{
							right12=r12;
						} else {continue;} // Касание!	K
					}
				}
			}else  {continue;} // Касание & обрыв полилинии	K

		}else // нормальное пересечение
		{
			// Считаем что касания быть не может  (?)
			right12=Vector::isRightVectors(v1,v2); // !(v1||v2)
			//???			
		}				

//*/















List<TMETRIC> AbstractLine::sIntersections(AbstractLine *al,bool ContinuesMode)
{
	List<TMETRIC> rl;
	List<Point> inte=LinesIntersections(this,al,ContinuesMode);	
	for(int i=0; i<inte.count(); i++)
	{
		TMETRIC s=SCoordinateFromPoint(inte[i]);
		int j=0;
		while(j<rl.count())
		{
			if(s<rl[j])break;
			j++;
		}
		rl.Insert(j,s);
	}

	return rl;
}









List<Point> AbstractLine::LinesIntersections(AbstractLine *l1, AbstractLine *l2, bool ContinuesMode)
{
	if(l1==l2) return List<Point>();
	LineType lt1=l1->line_type;
	LineType lt2=l2->line_type;
	Point p11(l1->StartPoint()),p12(l1->EndPoint());
	Point p21(l2->StartPoint()),p22(l2->EndPoint());
	List<Point> rpl;


	if(lt1==LT_ARCLINE)
	{
		if(lt2==LT_LINE) rpl+=AbstractLinesIntersections(l2,l1);
		else if(lt2==LT_ARCLINE)
		{
			AlArcline *arcl1=(AlArcline*)l1;
			AlArcline *arcl2=(AlArcline*)l2;
			Vector vo12(*arcl1->GetLinePoint(LP_CENTER),*arcl2->GetLinePoint(LP_CENTER));
			TMETRIC o12l=vo12.length();
			List<Point> arcp;

			if(isEqual(o12l,arcl1->r+arcl2->r,TMETRIC_O))
			{
				arcp+=(vo12*(arcl1->r/o12l)).destination();								
			}
			else if(o12l<(arcl1->r+arcl2->r)) 
			{
				TMETRIC r1=arcl1->r,r2=arcl2->r;
				TMETRIC ppt=(r1+r2+o12l)/2;
				TMETRIC h=sqrt(ppt*(ppt-r1)*(ppt-r2)*(ppt-o12l))*TMETRIC(2)/o12l;
				TMETRIC hx=sqrt(r1*r1-h*h);
				TMETRIC hx_=sqrt(r2*r2-h*h);
				if((hx+hx_>o12l+TMETRIC_O*2)&&(r1<r2)) hx*=-1;
				Basis b; b.SetOrtoBasis_ByIJ(vo12,arcl1->arcbas.k*vo12);
				arcp+=Point(hx,h,0,&b).inGlobalBasis();
				arcp+=Point(hx,-h,0,&b).inGlobalBasis();
			}
			for(int i=0; i<arcp.count(); i++)
			{
				Point rp=arcp[i];
				TAngle a1=arcl1->arcbas.i.AngleA(Vector(vo12.fulcrum,rp));
				TAngle a2=arcl2->arcbas.i.AngleA(Vector(vo12.destination(),rp));
				a1.Rad(); a2.Rad();
				bool rp1=false, rp2=false;
				if(ToCylCoord_Arc(rp.inBasis(&arcl1->arcbas)).a<=arcl1->angle)rp1=true;					
				if(ToCylCoord_Arc(rp.inBasis(&arcl2->arcbas)).a<=arcl2->angle)rp2=true;	
				if(rp1&&rp2) rpl+=rp;
			}
		}
	}else if(lt1==LT_LINE)
	{
		if(lt2==LT_LINE)
		{
			Vector v1(p11,p12);
			Vector v2(p21,p22);
			TMETRIC lv1=v1.length(), lv2=v2.length();
			Vector v1e=v1/lv1, v2e=v2/lv2;
			Point c=v1.Intersection(v2);

			if(c.isNull()) //если нет пересечений
			{
				if(ContinuesMode)
				{				
					Vector v12(p11,p21);
					TMETRIC pr11=-(v12&v2e);			
					if((pr11>-TMETRIC_O)&&(pr11<lv2+TMETRIC_O))
					{
						if((v12*v2e).length()<TMETRIC_O)
						{
							if(l1->previous())
							{
								if(l1->previous()==l2) return rpl;
								List<TMETRIC> ss=l1->previous()->sIntersections(l2,false);
								if(ss.count())if(isEqual(ss.last(),l1->previous()->length(),TMETRIC_O*2)) return rpl;
							}
							rpl+=p11;
							return rpl;
						}
					}
					TMETRIC pr21=v12&v1e;
					if((pr21>-TMETRIC_O)&&(pr21<lv1+TMETRIC_O))
					{
						if((v12*v1e).length()<TMETRIC_O)
						{
							if(l2->previous())
							{
								if(l2->previous()==l1) return rpl;
								List<TMETRIC> ss=l2->previous()->sIntersections(l1,false);
								if(ss.count())if(isEqual(ss.last(),l2->previous()->length(),TMETRIC_O*2)) return rpl;
							}
							rpl+=p21;
							return rpl;
						}
					}
				}
				return rpl;
			}
			TMETRIC pr1=Vector(p11,c)&v1e;
			TMETRIC pr2=Vector(p21,c)&v2e;
			if(pr1>0&&pr1<lv1&&pr2>0&&pr2<lv2)rpl+=c;
			//return rpl;
		} else if(lt2==LT_ARCLINE)
		{
			AlArcline *arcl=(AlArcline*)l2;
			Point pc=arcl->arcbas.O;
			Basis b; b.SetOrtoBasis_ByOXY(l1->StartPoint(),l1->EndPoint(),pc);pc.SetBasis(&b);
			TMETRIC pcy=pc.y();
			TMETRIC pcx=pc.x();
			// 			if(isEqual(pc.y(),arcl->r,TMETRIC_O))
			// 			{
			// 				Point rp(pc.x(),0,0,&b); rp.SetBasis(&arcl->arcbas);
			// 				TAMETRIC a=arcl->arcbas.i.Angle(Vector(pc,rp));				
			// 				if(pc.x()>=0&&pc.x()<=l1->length())
			// 				{
			// 					if((rp.y()>0&&(a<arcl->angle))||(rp.y()<0&&(2*PI-a)<arcl->angle)) rpl+=rp;
			// 				}
			// 			}else
			if(pcy<=arcl->r)
			{
				TMETRIC h=sqrt(arcl->r*arcl->r-pcy*pcy);
				TMETRIC ll1=l1->length();
				if((pcx-h)>=0&&(pcx-h)<=ll1)
				{
					Point rp(pcx-h,0,0,&b); rp.SetBasis(&arcl->arcbas);
					TAMETRIC a=arcl->arcbas.i.Angle(Vector(pc,rp));	
					if((rp.y()>0&&(a<arcl->angle))||(rp.y()<0&&(2*PI-a)<arcl->angle)) rpl+=rp.inGlobalBasis();
				}
				if(h!=0)if((pcx+h)>=0&&(pcx+h)<=ll1)
				{
					Point rp(pcx+h,0,0,&b); rp.SetBasis(&arcl->arcbas);
					TAMETRIC a=arcl->arcbas.i.Angle(Vector(pc,rp));	
					if((rp.y()>0&&(a<arcl->angle))||(rp.y()<0&&(2*PI-a)<arcl->angle))
						rpl+=rp.inGlobalBasis();
				}
			}
			if(rpl.count()<=1&&ContinuesMode)
			{
				CylCoord p11cyl=ToCylCoord_Arc(p11[arcl->arcbas]);
				if(isEqual(p11cyl.r,arcl->r,TMETRIC_O))	if(p11cyl.a>TMETRIC_O&&p11cyl.a<arcl->angle+TMETRIC_O)
				{
					bool no=false;
					if(l1->previous()) 
					{
						if(l1->previous()==l2) no=true;
						else
						{
							List<TMETRIC> ss=l1->previous()->sIntersections(l2,false);
							if(ss.count())if(isEqual(ss.last(),l1->previous()->length(),TMETRIC_O*2)){no=true;}						
						}
					}		
					if(!no)rpl+=p11;
				}
				if(rpl.count()<=1)
				{
					Vector v12(p11,p21);
					Vector v1e(p11,p12);
					TMETRIC lv1=v1e.length();
					v1e/=lv1;
					TMETRIC pr21=v12&v1e;			
					if((pr21>-TMETRIC_O)&&(pr21<lv1+TMETRIC_O))
					{
						if((v12*v1e).length()<TMETRIC_O)
						{
							bool no=false;
							if(l2->previous())
							{
								if(l2->previous()==l1) no=true;
								else
								{
									List<TMETRIC> ss=l2->previous()->sIntersections(l1,false);
									if(ss.count())if(isEqual(ss.last(),l2->previous()->length(),TMETRIC_O*2)) no=true;
								}
							}
							if(!no) rpl+=p11;
							//return rpl;
						}
					}
				}
			}

		}
	}

	if(lt1==LT_POLYLINE)
	{
		AlPolyline *pl=(AlPolyline*)l1;
		for(int i=0; i<pl->Count(); i++) rpl+=AbstractLinesIntersections(l2,(*pl)[i]/*,ContinuesMode*/);
	}else if(lt2==LT_POLYLINE)
	{
		AlPolyline *pl=(AlPolyline*)l2;
		for(int i=0; i<pl->Count(); i++) rpl+=AbstractLinesIntersections(l1,(*pl)[i]/*,ContinuesMode*/);
	}

	return rpl;
}












AlCircuit::AlCircuit():AbstractLine(LT_CIRCUIT)
{
	// WTF???
	OutCircuits+=PhantomObject<AlPolylineCircuit>();
	OutCircuits.last().Obj();
	OutCircuits+=PhantomObject<AlPolylineCircuit>();
	OutCircuits.last().Obj();
	OutCircuits.clear();
}

AlCircuit::AlCircuit(const AlCircuit &acirc):AbstractLine(LT_CIRCUIT),
OutCircuits(acirc.OutCircuits),InCircuits(acirc.InCircuits)
{

}

AlCircuit::~AlCircuit()
{

}

void AlCircuit::Clear()
{
	OutCircuits.clear();
	InCircuits.clear();
}



struct IntersectVector
{	
	TMETRIC s1;
	TMETRIC s2; //?
	bool rigth12;
};

// List<IntersectVector> LinesIntersectV(AbstractLine *al1, AbstractLine *al2)
// {
// 	List<TMETRIC> rl;
// 	List<Point> inte=LinesIntersections(al1,al2,ContinuesMode);	
// 	for(int i=0; i<inte.count(); i++)
// 	{
// 		TMETRIC s=SCoordinateFromPoint(inte[i]);
// 		int j=0;
// 		while(j<rl.count())
// 		{
// 			if(s<rl[j])break;
// 			j++;
// 		}
// 		rl.Insert(j,s);
// 	}
// 
// 	return rl;
// }




void AlCircuit::operator +=(const AlPolyline &pl)
{	
	if(pl.Count()<2) return;	
	OutCircuits+=PhantomObject<AlPolylineCircuit>();
	OutCircuits.last().Create(pl);
	AlPolylineCircuit /*plc(pl);//*/&plc=OutCircuits.last().Obj();	
	if(plc.StartPoint()!=plc.EndPoint()) plc+=&AlLine(plc.EndPoint(),plc.StartPoint());
	plc.Last()->setNext(plc.First());

//////////////////////////////////////////////////////////////

	struct  InderteminateIntersection
	{
		AbstractLine *al;
		bool InRight;
	};

	List<InderteminateIntersection> II;
	
	int i=0;
	int CurLevel=0;

	for(i=0;i<plc.Count();i++)
	{
		List<TMETRIC> sints;//=2*plc[i]->length();
		List<AbstractLine*> Lsints;
		List<AbstractLine*> CriticalLines;
		List<int> CriticalLinesI;
		
		for(int j=i+1; j<plc.Count(); j++)
		{			
			List<TMETRIC> si=plc[i]->sIntersections(plc[j]);
		//	List<IntersectPoint> si=plc[i]
			if(si.count())
			{
				if(plc[j]->previous()==plc[i])while(si.count()){if(isEqual(si.last(),plc[i]->length(),TMETRIC_O*3)) si.removeLast(); else break;}			
				else if(plc[j]->next()==plc[i])while(si.count()){if(isEqual(si.first(),0,TMETRIC_O*3)) si.removeFirst(); else break;}			
				bool crit=false;
				TMETRIC s1=0;
				TMETRIC s2=0;
				for(int zu=0; zu<si.count(); zu++)
				{
					int zuzu=0;
					while(zuzu<sints.count()){if(si[zu]<sints[zuzu]) break;	 zuzu++;}
					sints.Insert(zuzu,si[zu]);
					Lsints.Insert(zuzu,plc[j]);			
					if(!crit&&si.count()>1)
					{				
						s2=plc[j]->SCoordinateFromPoint(plc[i]->PointFromSCoordinate(si[zu]));
						if(s2<s1) crit=true;
						s1=s2;
					}
				}
				if(crit)
				{
					CriticalLines+=plc[j];
					CriticalLinesI+=si.count()-1;
				}
			}			
		}
		TMETRIC s_=0;

		if(plc[i]->preLine!=0)
		{
			if(Vector::isRightVectors(plc[i]->InDirection(),plc[i]->preLine->OutDirection()))
			{				
				CurLevel-=1;
			}else
			{
				CurLevel+=1;
			}	
		}
		plc[i]->Level=CurLevel;
		int dl=plc[i]->Level;
		if(dl<0)
		{
			for(int ii=0; ii<=i; ii++) plc[ii]->Level-=dl;
			CurLevel-=dl;
		}
		int i0=i;
		for(int zu=0; zu<sints.count(); zu++)
		{
			AbstractLine *Ltr=Lsints[zu];
			TMETRIC s1=sints[zu]-s_; s_+=s1;
			TMETRIC s2=Ltr->SCoordinateFromPoint(plc[i]->PointFromSCoordinate(s1));
			if(s1<TMETRIC_O)
			{
			}
// 			else if(s1>plc[i]->length()-TMETRIC_O)
// 			{
// 				i++;
// 				plc[i]->Level=CurLevel;			
// 			}
			else
			{
				plc.intersectS(i,s1);i++;
				if(plc[i]->preLine!=0)
				{
					plc[i]->preLine->nextLine=plc[i-1];
					plc[i-1]->preLine=plc[i]->preLine;	
					plc[i]->preLine=0;
				}
				plc[i-1]->Level=plc[i]->Level;
			}
			
			int j=plc.iLine(Ltr);
			
			bool crit=false;
			if(s2<TMETRIC_O)
			{
			}
// 			else if(s2>plc[j]->length()-TMETRIC_O)
// 			{
// 				j++;
// 			}
			else 
			{
				for(int cri=0; cri<CriticalLines.count(); cri++)
				{
					if(Ltr==CriticalLines[cri])
					{
						/*if(!(Vector::isRightVectors(plc[i]->InDirection(),plc[j]->SDirection(s2))))*/ crit=true;
						CriticalLinesI[cri]--; 
						if(CriticalLinesI[cri]==0){CriticalLines.removeAt(cri); CriticalLinesI.removeAt(cri);}
						break;
					}
				}		
				if(!crit){ plc.intersectS(j,s2);j++;}
				else
				{
					plc[j]->Invert();
					plc.intersectS(j,plc[j]->length()-s2,false);
					plc[j]->Invert();
					plc[j+1]->Invert();
					if(plc[j]->nextLine!=0)
					{
						plc[j+1]->nextLine=plc[j]->nextLine;
						plc[j]->nextLine->preLine=plc[j+1];
						plc[j]->nextLine=0;
					}
					j++;
				}

				
				if(plc[j]->preLine!=0)
				{
					plc[j]->preLine->nextLine=plc[j-1];
					plc[j-1]->preLine=plc[j]->preLine;	
					plc[j]->preLine=0;
				}	
			}
			
			
			plc[i]->preLine=plc[j-1];
			plc[j-1]->nextLine=plc[i];
			plc[i-1]->nextLine=plc[j];
			plc[j]->preLine=plc[i-1];

			if(Vector::isRightVectors(plc[i]->InDirection(),plc[j]->InDirection()))
			{				
				CurLevel-=1;
			}else
			{
				CurLevel+=1;
			}	
			plc[i]->Level=CurLevel;
			dl=plc[i]->Level;
			if(dl<0)
			{
				for(int ii=0; ii<=i; ii++) plc[ii]->Level-=dl;
				CurLevel-=dl;
			}
		}	
	}


 	for(int i=0; i<plc.Count(); i++)
 	{		
 		if(plc[i]->markers[LM_TRAVERSE]) continue;
 		if(plc[i]->Level==0)
 		{
			AbstractLine *Ltr=plc[i];
			AbstractLine *CurLine=plc[i];
 			TAMETRIC ACirc=0;
 			PhantomObject<AlPolylineCircuit> rCirc; rCirc.Create();
 			//rCirc.Obj()+=plc[i]; 			
			int iBr=0;
			for(;;)
			{
				iBr++;
				rCirc.Obj()+=Ltr;				
				Vector v1=Ltr->StartPoint()&&Ltr->EndPoint();
				do 
				{
					Ltr->markers[LM_TRAVERSE]=true;
					if(Ltr->nextLine!=0) Ltr=Ltr->nextLine;
					else Ltr=plc.relativeLine(Ltr,+1);
					if(Ltr==CurLine) break;
				} while(Ltr->length()<TMETRIC_O);				
				Vector v2=Ltr->StartPoint()&&Ltr->EndPoint();				
				ACirc+=Vector::Angle(v1,v2)*((Vector::isRightVectors(v1,v2))?(1):(-1));
				
				if(Ltr==CurLine) break;
				if(iBr>plc.Count()+2) return;
			}
			Vector v1=rCirc.Obj().Last()->StartPoint()&&rCirc.Obj().Last()->EndPoint();
			Vector v2=rCirc.Obj().First()->StartPoint()&&rCirc.Obj().First()->EndPoint();
			ACirc+=Vector::Angle(v1,v2)*((Vector::isRightVectors(v1,v2))?(1):(-1));
			if(ACirc>0)
			{
				OutCircuits+=PhantomObject<AlPolylineCircuit>();
				OutCircuits.last().TakeAway(rCirc);
			}else
			{
				InCircuits+=PhantomObject<AlPolylineCircuit>();
				InCircuits.last().TakeAway(rCirc);
			}
 		}
 	}


//*//*
return;
//*/
// 	if(OutCircuits.count()==0)
// 	{
// 		OutCircuits+=plc;
// 		return;
// 	}

////////////////////////////////////////////////////////////
/*
	Point startCross(false);
	int iCurLine=-1;
	AbstractLine *CurStartLine=0;
	AbstractLine *CurEndLine=0;
	bool br=false;
	for(int i=0; i<plc.Count(); i++)
	{
		for(int j=i+1; j<plc.Count(); j++)
		{
			List<TMETRIC> sint=plc[i]->sIntersections(plc[j]);
			if(sint.count())
			{
				//if(sint.)
				TMETRIC si=sint.first();
				TMETRIC sj=plc[j]->SCoordinateFromPoint(plc[i]->PointFromSCoordinate(si));
				if(Vector::isRightVectors(plc[i]->sDirection(si),plc[j]->sDirection(sj)))
				{
					CurStartLine=plc[i]; 						
					plc.intersectS(j,sj); CurEndLine=plc[j];
					plc.intersectS(i,si);
				}else
				{
					CurStartLine=plc[j];
					plc.intersectS(j,sj); 
					plc.intersectS(i,si); CurEndLine=plc[i];
				}							
				br=true;
				break;
			}
		}
		if(br) break;
		plc[i]->markers[LM_NOINTERSECTIONS]=true;
	}
	if(!CurStartLine)
	{
		OutCircuits+=PhantomObject<AlPolylineCircuit>();
		OutCircuits.first().Obj(plc);
		return;
	}





////////////////////////////////////////////////////////// :-(

////////////////////////////////////////////////////////// :-(

////////////////////////////////////////////////////////// :-(


	for(int iii=0;;iii++)
	{
		TAMETRIC Atr=0;
		AbstractLine *Ltr=CurStartLine;
		AbstractLine *Ltrtr=0;
		int Itr=plc.iLine(CurStartLine);
		//Point StCrosP=CurStartLine->StartPoint();
		PhantomObject<AlPolylineCircuit> rCirc(true);
		bool badCirc=false;
		bool CurEndLineBR=false;

		for(int iCtrl=0;iCtrl<plc.Count()*2+2; iCtrl++)
		{
			if(Ltr==CurEndLine)
			{
				CurEndLineBR=true;
// 				Ltr->markers[LM_TRAVERSE]=true;
// 				rCirc.Obj()+=Ltr;
// 				Vector v1=Ltr->StartPoint()&&Ltr->EndPoint();
// 				Vector v2=CurStartLine->StartPoint()&&CurStartLine->EndPoint();
// 				Atr+=Vector::Angle(v1,v2)*((V::isRightVectors(v1,v2))?(1):(-1));
// 				break;
			} else CurEndLineBR=false;
			if(Ltr->markers[LM_NOINTERSECTIONS]||Ltr->markers[LM_TRAVERSE])
			{
				Ltr->markers[LM_TRAVERSE]=true;
				Vector v1=Ltr->StartPoint()&&Ltr->EndPoint();
				rCirc.Obj()+=Ltr;				
				Itr=plc.iRelative(Itr,+1);
				Ltr=plc[Itr];	
				Vector v2=Ltr->StartPoint()&&Ltr->EndPoint();
				Atr+=Vector::Angle(v1,v2)*((V::isRightVectors(v1,v2))?(1):(-1));
				continue;
			}

			/// Ищем  пересечение //////////////////////////////
			TMETRIC sint=Ltr->length()+TMETRIC_O;
			int sintI=-1;
			for(int i=1; i<plc.Count(); i++)
			{
				int CsintI=plc.iRelative(Itr,i);
				Ltrtr=plc[CsintI];
				if(Ltrtr->markers[LM_NOINTERSECTIONS]||Ltrtr->markers[LM_TRAVERSE]) continue;
				List<TMETRIC> trsint=Ltr->sIntersections(Ltrtr);
				if(trsint.count())if(trsint.first()<sint)
				{
					sint=trsint.first();
					sintI=CsintI;
				}
			}	
			///////////////////////////////// Поискали пересечение

			
				if(sintI!=-1) //если таки нашли пересечение
				{
					Ltrtr=plc[sintI];
					TMETRIC str=sint;
					TMETRIC strtr=Ltrtr->SCoordinateFromPoint(Ltr->PointFromSCoordinate(str));
					if(Vector::isRightVectors(Ltr->sDirection(str),Ltrtr->sDirection(strtr)))
					{
						//вот ведь незадача
					//	badCirc=true;

						if(Itr<sintI)
						{
							plc.intersectS(sintI,strtr); CurEndLine=plc[sintI];
							plc.intersectS(Itr,sint);
						}else
						{
							plc.intersectS(Itr,sint);
							plc.intersectS(sintI,strtr); CurEndLine=plc[sintI];							
						}

						Atr=0;
						CurStartLine=Ltr;
						CurStartLine->markers[LM_TRAVERSE]=false;
						CurEndLine->markers[LM_TRAVERSE]=false;
						
						Ltr=CurStartLine;
						Ltrtr=0;
						Itr=plc.iLine(CurStartLine);
//						StCrosP=CurStartLine->StartPoint();
						rCirc.Create();
						continue;
					}else
					{	
						Ltrtr=plc[sintI];
						if(Itr<sintI)
						{
							plc.intersectS(sintI,strtr); 
							plc.intersectS(Itr,sint);
						}else
						{
							plc.intersectS(Itr,sint);
							plc.intersectS(sintI,strtr); 
							Itr+=1;
						}

						rCirc.Obj()+=plc[Itr];
						plc[Itr]->markers[LM_TRAVERSE]=true;
						Vector v1=Ltr->StartPoint()&&Ltr->EndPoint();
						Ltr=Ltrtr;
						Vector v2=Ltr->StartPoint()&&Ltr->EndPoint();
						Atr+=Vector::Angle(v1,v2)*((V::isRightVectors(v1,v2))?(1):(-1));
						Itr=plc.iLine(Ltr);
					}												
				}else // а если не нашли
				{	
					if(CurEndLineBR)
					{				
						Ltr->markers[LM_TRAVERSE]=true;
						rCirc.Obj()+=Ltr;
						Vector v1=Ltr->StartPoint()&&Ltr->EndPoint();
						Vector v2=CurStartLine->StartPoint()&&CurStartLine->EndPoint();
						Atr+=Vector::Angle(v1,v2)*((V::isRightVectors(v1,v2))?(1):(-1));
						break;
					}else
					{					
						Vector v1=Ltr->StartPoint()&&Ltr->EndPoint();
						rCirc.Obj()+=Ltr;	
						Ltr->markers[LM_TRAVERSE]=true;
						Itr=plc.iRelative(Itr,+1);
						Ltr=plc[Itr];	
						Vector v2=Ltr->StartPoint()&&Ltr->EndPoint();
						Atr+=Vector::Angle(v1,v2)*((V::isRightVectors(v1,v2))?(1):(-1));
					}
				}
		}

// 		if(badCirc)
// 		{
// 		}else 
		if(rCirc.Obj().Count()>1)
		{
			if(Atr>0)
			{
				OutCircuits+=PhantomObject<AlPolylineCircuit>();
				OutCircuits.last().TakeAway(rCirc);
			}else
			{
				InCircuits+=PhantomObject<AlPolylineCircuit>();
				InCircuits.last().TakeAway(rCirc);
			}
		}
/////////////////////////////////////////////////////////////////////////////////////
		int i=plc.iLine(CurEndLine);
		int CurLevel=1;
		bool br=false;
		int ibr=0;
		List<AbstractLine*> SelfIntersecEnds;
		for(;;)
		{	
			if(ibr>plc.Count()+1){br=true; break;}
			ibr++;
			i=plc.iRelative(i,+1);
			if(plc[i]->markers[LM_TRAVERSE]) continue;
			
			List<TMETRIC> sints;//=2*plc[i]->length();
			List<int> Isints;
			//int isint=-1;
			for(int j=0; j<plc.Count(); j++)
			{
				if(plc[j]->markers[LM_TRAVERSE]||plc[j]->markers[LM_NOINTERSECTIONS]) continue;
				List<TMETRIC> si=plc[i]->sIntersections(plc[j]);
				for(int zu=0; zu<si.count(); zu++)
				{
					int zuzu=0;
					while(zuzu<sints.count()){if(si[zu]<sints[zuzu]) break;	 zuzu++;}
					sints.Insert(zuzu,si[zu]);
					Isints.Insert(zuzu,j);				
				}
			}
			if(sints.count())
			{
				bool Br=false;
				for(int zu=0; zu<sints.count(); zu++)
				{
					int j=Isints[zu];
					TMETRIC s1=sints[zu];
					TMETRIC s2=plc[j]->SCoordinateFromPoint(plc[i]->PointFromSCoordinate(s1));
					if(Vector::isRightVectors(plc[i]->sDirection(s1),plc[j]->sDirection(s2)))
					{
						CurLevel-=1;
					}else
					{
						CurLevel+=1;
					}	
					if(CurLevel==0)
					{
						CurStartLine=plc[i];	
						if(i>j)
						{					
							plc.intersectS(i,s1); plc[i]->markers[LM_TRAVERSE]=true;
							plc.intersectS(j,s2); CurEndLine=plc[j];
						}else
						{
							plc.intersectS(j,s2); CurEndLine=plc[j];
							plc.intersectS(i,s1); plc[i]->markers[LM_TRAVERSE]=true;
						}
						Br=true;
						break;
					}						
				}
				if(Br) break;
			}else
			{
				plc[i]->markers[LM_TRAVERSE]=true;
			}

// 			for(int zu=0; zu<SelfIntersecEnds.count(); zu++)
// 			{
// 				if(SelfIntersecEnds[zu]==plc[i])
// 				{
// 					CurLevel-=1;
// 					SelfIntersecEnds.removeAt(zu);
// 					break;
// 				}				
// 			}
// 			if(CurLevel==0)
// 			{	
// 				CurStartLine=plc.relativeLine(i,+1);
// 				break;
// 			}

			
		}

		if(br) break;
	}
//*/
}


void AlCircuit::operator -=(AlPolyline &polycirc)
{
	//if(OutCircuits.count()==0) return;
}




bool PointInCircuit(Point p, List<Point> *ps, bool closed)
{
	TMETRIC a=0;
	Vector v(p,closed?ps->last():ps->first());
	Vector nv;
	Basis b;
	for(int i=closed?0:1; i<ps->count(); i++)
	{
		nv=Vector(p,ps->at(i));
		b.SetOrtoBasis_InXY_ByI(v);
		a+=v.Angle(nv)*signum(nv.inBasis(&b).y());
		v=nv;
	}
	return (abs(a)>PI);
}

List<int> MaxCircuit_i(List<Point> *ps) // что это??
{
 		return List<int>();
}

List<Point> MaxCircuit(List<Point> *ps) // что это??
{
	List<Point> rps;
	List<int> ic; for(int i=0; i<ps->count(); i++) ic+=i;
// 	List<int> irps=MaxCircuit_i(ps);
// 	for(int i=0; i<irps.count(); i++) rps+=ps->at(irps[i]);
	if(ps->count()<=3)
	{
	 	rps=*ps;
	}else
	{
		int ipst=0;
		for(int i=0; i<ps->count(); i++) if((*ps)[ipst].x()>(*ps)[i].x()) ipst=i;
		rps+=(*ps)[ipst];
		//ic.removeOne(ipst);
		Basis b; b.SetO((*ps)[ipst]);
		while((rps.first()!=rps.last()&&ic.count())||rps.count()<=1)
		{
			int ipn=ic.first();	
			//*if(ipn==ipst)ipn=*/
			for(int i=0; i<ic.count(); i++)
			{
				if(ic[i]!=ipn) if(ToCylCoord((*ps)[ic[i]].inBasis(&b)).a>ToCylCoord((*ps)[ipn].inBasis(&b)).a)ipn=ic[i];
			}
			ic.remove(ipn);
			b.SetOrtoBasis_InXY_ByI(Vector(rps.last(),(*ps)[ipn])); 
			rps+=(*ps)[ipn]; b.SetO(rps.last());
		}
	}
	return rps;
}


TMETRIC CircuitAreaABS(List<Point> &ps){return abs(CircuitArea(ps));}
TMETRIC CircuitArea(List<Point> &ps)
{
	if(ps.count()<3) return 0;
	TMETRIC A=0;
	Basis b;
	for(int i=2; i<ps.count(); i++)
	{
		Vector v(ps[0],ps[i-1]);
		b.SetOrtoBasis_InXY_ByI(v);
		ps[i].SetBasis(&b);
		A+=ps[i].y()*TMETRIC(0.5)*v.length();
	}
	return A;
}

TMETRIC APolylineCircuitAreaABS(AlPolyline &pl){return abs(APolylineCircuitArea(pl));}

TMETRIC APolylineCircuitArea(AlPolyline &pl)
{
	TMETRIC A=0;

	Basis b;
	if(pl.Count()>2)
	{		
		for(int i=2; i<pl.Count(); i++)
		{
			Vector v(pl[0]->StartPoint(),pl[i-1]->StartPoint());//,pl[i]->StartPoint());
			b.SetOrtoBasis_InXY_ByI(v);
			A+=pl[i]->StartPoint().inBasis(&b).y()*TMETRIC(0.5)*v.length();
		}
		if(pl.StartPoint()!=pl.EndPoint())
		{	
			Vector v(pl[0]->StartPoint(),pl[pl.Count()-2]->EndPoint());//,pl[i]->StartPoint());
			b.SetOrtoBasis_InXY_ByI(v);
			A+=pl.Last()->EndPoint().inBasis(&b).y()*TMETRIC(0.5)*v.length();
		}
	}	

	for(int i=0; i<pl.Count(); i++)
	{
		if(pl[i]->line_type==AL::LT_LINE) {continue;}
		else if(pl[i]->line_type==AL::LT_ARCLINE)
		{
			AlArcline *arc=(AlArcline*)pl[i];
			b.SetOrtoBasis_InXY_ByI(V(arc->StartPoint(), arc->EndPoint()));
			A+=(arc->r*arc->r*TMETRIC(0.5)*arc->angle)*signum(arc->MiddlePoint().inBasis(&b).y());
		}else if(pl[i]->line_type==AL::LT_POLYLINE)
		{
			A+=APolylineCircuitArea(*(AlPolyline*)pl[i]);
		}else
		{
			A+=CircuitArea(pl[i]->toPolyline());
		}
	}
	return A;
}

