#include "TrigonometricAngle.h"


namespace CppBikes
{





TrAngle::TrAngle(RNUM cos_val, bool sin_negative)
{
	setCos(cos_val,sin_negative);
}

TrAngle::TrAngle( RNUM ang_rad )
{
	setRad(ang_rad);
}

TrAngle::TrAngle()
{
	setCos(1.0,false);
}

TrAngle::TrAngle( RNUM rad_val, RNUM sin_val, RNUM cos_val, RNUM tan_val, char mdat ):
_mdat(mdat),
_sin(sin_val),
_cos(cos_val),
_tan(tan_val),
_rad(rad_val)
{
	if( (_mdat&MD_SINCALC)&&(_sin<0) ) _mdat|=MD_SINM;
	if( (_mdat&MD_COSCALC)&&(_cos<0) ) _mdat|=MD_COSM;
}



void TrAngle::setRad(RNUM rad)
{
	_mdat=MD_RADCALC;
	_rad=rad;
	RNUM na=NormAngle(rad);
	if(na<0)
	{
		_mdat|=MD_SINM;
		if(-na>PIdiv2)_mdat|=MD_COSM;
	}else if(na>PIdiv2) _mdat|=MD_COSM;	
}

void TrAngle::setDeg(RNUM deg)
{
	setRad(DEG_to_RAD(deg));
}


void TrAngle::setCos(RNUM cos_val, bool sin_negative)
{
	_mdat=MD_COSCALC;
	if(sin_negative)_mdat|=MD_SINM;
	if(cos_val<0)_mdat|=MD_COSM;
	_cos=cos_val;
}

void TrAngle::setSin(RNUM sin_val, bool cos_negative)
{
	_mdat=MD_SINCALC;
	if(cos_negative)_mdat|=MD_COSM;
	if(sin_val<0) _mdat|=MD_SINM;
	_sin=sin_val;
}
void TrAngle::setTan(RNUM tan_val, bool cos_negative)
{
	_mdat=MD_TANCALC;
	if(cos_negative) _mdat|=MD_COSM;
	if(tan_val>0) 
	{
		if(cos_negative) _mdat|=MD_SINM;
	}else if(!cos_negative) _mdat|=MD_SINM;
	_tan=tan_val;
}


RNUM TrAngle::Sin()
{
	if(_mdat&MD_SINCALC) return _sin;
	_mdat|=MD_SINCALC;
	_mdat|=MD_TRCALC;

	if(_mdat&MD_COSCALC)
	{
		_sin=sqrt(1-_cos*_cos);
		if(_mdat&MD_SINM) _sin=-_sin;
		
	}else if(_mdat&MD_TANCALC)
	{	
		_sin=sqrt(1.0/(1.0+_tan*_tan));
		if(_mdat&MD_SINM) _sin=-_sin;
	
	}else if(_mdat&MD_RADCALC)
	{		
		_sin=::sin(_rad);			
	} else 
	{
		_sin=0;
	}
	return _sin;
}
RNUM TrAngle::Cos()
{
	if(_mdat&MD_COSCALC) return _cos;
	_mdat|=MD_COSCALC;
	_mdat|=MD_TRCALC;

	if(_mdat&MD_SINCALC)
	{		
		_cos=sqrt(1-_sin*_sin);
		if(_mdat&MD_COSM) _cos=-_cos;

	}else if(_mdat&MD_TANCALC)
	{	
		_cos=sqrt(1.0/(1.0/(_tan*_tan)+1.0));
		if(_mdat&MD_COSM) _cos=-_cos;		

	} else if(_mdat&MD_RADCALC)
	{	
		_cos=::cos(_rad);		
	}else
	{
		_cos=1;
	}	
	return _cos;
}
RNUM TrAngle::Tg()
{
	if(_mdat&MD_TANCALC) return _tan;
	_mdat|=MD_TANCALC;

	if(_mdat&MD_TRCALC)
	{		
		RNUM co=Cos();
		if(co==0) _tan=RNUM_INFINITY;
		else _tan=Sin()/co;
		
	}else if(_mdat&MD_RADCALC)
	{	
		_tan=::tan(_rad);
	}else
	{
		_tan=0;
	}
	_mdat|=MD_TRCALC;
	return _tan;
}
RNUM TrAngle::Rad()
{
	if(_mdat&MD_RADCALC) return _rad;
	_mdat|=MD_RADCALC;

	if(_mdat&MD_COSCALC)
	{		
		_rad=arccos(_cos);		
		if(_mdat&MD_SINM) _rad=-_rad;
		
	}else if(_mdat&MD_SINCALC)
	{		
		_rad=arcsin(_sin);		
		if(_mdat&MD_COSM)
		{
			if(_rad>0) _rad=PI-_rad;
			else _rad=-PI-_rad;
		}
	
	}else if(_mdat&MD_TANCALC)
	{		
		_rad=atan(_tan);
		//...?
		if(_mdat&MD_COSM)
		{
			if(_rad>0) _rad=PI-_rad;
			else _rad=-PI-_rad;
		}
		//...?				
	}else
	{
		_rad=0;
	}
	return _rad;
}
RNUM TrAngle::Deg()
{
	return RAD_to_DEG(Rad());
}

RNUM TrAngle::sSin()
{	
	return (_mdat&MD_SINM)?(-1.0):(1.0);
}
RNUM TrAngle::sCos()
{
	return (_mdat&MD_COSM)?(-1.0):(1.0);
}


TrAngle TrAngle::operator+ (TrAngle &ta )
{
	TrAngle r;
	r._mdat=MD_NULL;
	bool rc=ta._mdat&_mdat&MD_RADCALC;
	if(rc)
	{
		r.setRad(_rad+ta._rad);		
	}
	
	if((ta._mdat&_mdat&MD_TRCALC)||(!rc))
	{
		r._mdat|=MD_SINCALC|MD_COSCALC|MD_TRCALC;
		r._cos=Cos()*ta.Cos()-Sin()*ta.Sin(); //~?
		r._sin=Sin()*ta.Cos()+Cos()*ta.Sin(); //~?
		//if(r._cos<0)r._mdat|=MD_COSM;
		//if(r._sin<0)r._mdat|=MD_SINM;
	}

	return r;	
}

CppBikes::TrAngle TrAngle::operator-( TrAngle &ta )
{
	TrAngle r;
	r._mdat=MD_NULL;
	bool rc=ta._mdat&_mdat&MD_RADCALC;
	if(rc)
	{
		r.setRad(_rad-ta._rad);		
	}

	if((ta._mdat&_mdat&MD_TRCALC)||(!rc))
	{
		r._mdat|=MD_SINCALC|MD_COSCALC|MD_TRCALC;
		r._cos=Cos()*ta.Cos()+Sin()*ta.Sin(); //~?
		r._sin=Sin()*ta.Cos()-Cos()*ta.Sin(); //~?
		if(r._cos<0)r._mdat|=MD_COSM;
		if(r._sin<0)r._mdat|=MD_SINM;
	}

	return r;	
}

TrAngle TrAngle::operator-()
{
	return TrAngle(-_rad,-_sin,_cos,-_tan,_mdat^MD_SINM);
}

void TrAngle::operator+=( TrAngle &ta )
{		
	_mdat^=MD_TANCALC;
	bool rc=ta._mdat&_mdat&MD_RADCALC;
	if(rc)_rad+=ta._rad;	
	else _mdat^=MD_RADCALC;

	if((ta._mdat&_mdat&MD_TRCALC)||(!rc))
	{			
		RNUM c=Cos();
		RNUM s=Sin();
		RNUM c_=ta.Cos();
		RNUM s_=ta.Sin();
		_cos=c*c_-s*s_; //~?
		_sin=s*c_+c*s_; //~?
		if(_cos<0)_mdat|=MD_COSM;
		else _mdat&=MD_NCOSM;
		if(_sin<0)_mdat|=MD_SINM;		
		else _mdat&=MD_NSINM;
	}
}



void TrAngle::operator-=( TrAngle &ta )
{
	_mdat&=MD_NTANCALC;
	bool rc=ta._mdat&_mdat&MD_RADCALC;
	if(rc)_rad-=ta._rad;	
	else _mdat&=MD_RADCALC;

	if((ta._mdat&_mdat&MD_TRCALC)||(!rc))
	{		
		RNUM c=Cos();
		RNUM s=Sin();
		RNUM c_=ta.Cos();
		RNUM s_=ta.Sin();
		_cos=c*c_+s*s_; //~?
		_sin=s*c_-c*s_; //~?
		if(_cos<0)_mdat|=MD_COSM;
		else _mdat&=MD_NCOSM;
		if(_sin<0)_mdat|=MD_SINM;		
		else _mdat&=MD_NSINM;
	}
}

bool TrAngle::operator<( RNUM ang_rad )
{
	return Rad()<ang_rad;
}

bool TrAngle::operator<=( RNUM ang_rad )
{
	return Rad()<=ang_rad;
}

bool TrAngle::operator>( RNUM ang_rad )
{
	return Rad()>ang_rad;
}


bool TrAngle::operator>=( RNUM ang_rad )
{
	return Rad()>=ang_rad;
}

void TrAngle::trCalc()
{
	Sin();
	Cos();
	Tg();
}

RNUM TrAngle::Tan()
{
	return Tg();
}


void TrAngle::operator+=( RNUM ang_rad )
{
	setRad(ang_rad+Rad());
}

void TrAngle::operator-=( RNUM ang_rad )
{
	setRad(Rad()-ang_rad);
}



bool TrAngle::operator>( TrAngle &ta )
{
	if(_mdat&ta._mdat&MD_RADCALC)
	{
		return _rad>ta._rad;
	}
	if(_mdat&ta._mdat&MD_SINCALC)
	{
		if(_mdat&MD_COSM)
		{
			if(_mdat&MD_COSM)
			{
				//if(_mdat&MD_SINM) return 
			}else
			{

			}
		}else
		{
			if(ta._mdat&MD_COSM)
			{
				//...
			}else
			{
				return _sin>ta._sin;
			}
		}
	}
	//if((_mdat&MD_COSCALC)||(ta._mdat&MD_COSCALC))
	{

	}

	return Rad()>Rad();
}

bool TrAngle::operator<( TrAngle &ta )
{
	return Rad()<ta.Rad();
}

}