#include "TrigonometricAngle.h"


namespace Bikes
{


TrAngleConst::TrAngleConst( rnum ang_rad )
{
	TrAngle ang(ang_rad);
	rad_val=ang_rad;
	sin_val=ang.sin();
	cos_val=ang.cos();
	tan_val=ang.tan();
}

TrAngleConst::TrAngleConst( rnum _rad_val/*=0*/,rnum _sin_val/*=0*/, rnum _cos_val/*=1*/, rnum _tan_val/*=0*/ ) :
rad_val(_rad_val),sin_val(_sin_val),cos_val(_cos_val),tan_val(_tan_val)
{

}

TrAngleConst::TrAngleConst():
rad_val(0),sin_val(0),cos_val(1),tan_val(0)
{

}


TrAngleConst& TrAngleConst::operator=( rnum ang_rad )
{
	TrAngle ang(ang_rad);
	rad_val=ang_rad;
	sin_val=ang.sin();
	cos_val=ang.cos();
	tan_val=ang.tan();
	return *this;
}

TrAngleConst::operator rnum () const
{
	return rad_val;
}




TrAngle::TrAngle(rnum cos_val, bool sin_negative)
{
	setCos(cos_val,sin_negative);
}

TrAngle::TrAngle( rnum ang_rad )
{
	setRad(ang_rad);
}

TrAngle::TrAngle()
{
	setCos(1.0,false);
}

TrAngle::TrAngle( rnum rad_val, rnum sin_val, rnum cos_val, rnum tan_val, char mdat ):
_mdat(mdat),
_sin(sin_val),
_cos(cos_val),
_tan(tan_val),
_rad(rad_val)
{
	if( (_mdat&MD_SINCALC)&&(_sin<0) ) _mdat|=MD_SINM;
	if( (_mdat&MD_COSCALC)&&(_cos<0) ) _mdat|=MD_COSM;
}



void TrAngle::setRad(rnum rad)
{
	_mdat=MD_RADCALC;
	_rad=rad;
	rnum na=normAngle(rad);
	if(na<0)
	{
		_mdat|=MD_SINM;
		if(-na>PIdiv2)_mdat|=MD_COSM;
	}else if(na>PIdiv2) _mdat|=MD_COSM;	
}

void TrAngle::setDeg(rnum deg)
{
	setRad(DEG_to_RAD(deg));
}


void TrAngle::setCos(rnum cos_val, bool sin_negative)
{
	_mdat=MD_COSCALC;
	if(sin_negative)_mdat|=MD_SINM;
	if(cos_val<0)_mdat|=MD_COSM;
	_cos=cos_val;
}

void TrAngle::setSin(rnum sin_val, bool cos_negative)
{
	_mdat=MD_SINCALC;
	if(cos_negative)_mdat|=MD_COSM;
	if(sin_val<0) _mdat|=MD_SINM;
	_sin=sin_val;
}
void TrAngle::setTan(rnum tan_val, bool cos_negative)
{
	_mdat=MD_TANCALC;
	if(cos_negative) _mdat|=MD_COSM;
	if(tan_val>0) 
	{
		if(cos_negative) _mdat|=MD_SINM;
	}else if(!cos_negative) _mdat|=MD_SINM;
	_tan=tan_val;
}


rnum TrAngle::sin()
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
rnum TrAngle::cos()
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
rnum TrAngle::tg()
{
	if(_mdat&MD_TANCALC) return _tan;
	_mdat|=MD_TANCALC;

	if(_mdat&MD_TRCALC)
	{		
		rnum co=cos();
		if(co==0) _tan=RNUM_INFINITY;
		else _tan=sin()/co;
		
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
rnum TrAngle::rad()
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
rnum TrAngle::deg()
{
	return RAD_to_DEG(rad());
}

rnum TrAngle::sSin()
{	
	return (_mdat&MD_SINM)?(-1.0):(1.0);
}
rnum TrAngle::sCos()
{
	return (_mdat&MD_COSM)?(-1.0):(1.0);
}


TrAngle TrAngle::operator+ (TrAngle &ta )
{
	TrAngle r;
	r._mdat=MD_NULL;	
	if(ta._mdat&_mdat&MD_RADCALC)
	{
		r.setRad(_rad+ta._rad);		
		if((ta._mdat&_mdat&MD_TRCALC))
		{
			r._mdat|=MD_SINCALC|MD_COSCALC|MD_TRCALC;
			rnum s=sin();
			rnum c=cos();
			rnum s_=ta.sin();
			rnum c_=ta.cos();
			r._cos=c*c_-s*s_; //~?
			r._sin=s*c_+c*s_; //~?			
		}
	}else
	{
		r._mdat|=MD_SINCALC|MD_COSCALC|MD_TRCALC;
		rnum s=sin();
		rnum c=cos();
		rnum s_=ta.sin();
		rnum c_=ta.cos();
		r._cos=c*c_-s*s_; //~?
		r._sin=s*c_+c*s_; //~?	
		if(r._cos<0)r._mdat|=MD_COSM;
		if(r._sin<0)r._mdat|=MD_SINM;
	}
	

	return r;	
}

TrAngle TrAngle::operator+( const TrAngleConst &ta )
{
	TrAngle r;
	r._mdat=MD_NULL;
	if(_mdat&MD_RADCALC)
	{
		r.setRad(_rad+ta.rad_val);		
		if(_mdat&MD_TRCALC)
		{
			r._mdat|=MD_SINCALC|MD_COSCALC|MD_TRCALC;
			rnum s=sin();
			rnum c=cos();
			rnum s_=ta.sin_val;
			rnum c_=ta.cos_val;
			r._cos=c*c_-s*s_; //~?
			r._sin=s*c_+c*s_; //~?	
		}
	}else
	{
		r._mdat|=MD_SINCALC|MD_COSCALC|MD_TRCALC;
		rnum s=sin();
		rnum c=cos();
		rnum s_=ta.sin_val;
		rnum c_=ta.cos_val;
		r._cos=c*c_-s*s_; //~?
		r._sin=s*c_+c*s_; //~?	
		if(r._cos<0)r._mdat|=MD_COSM;
		if(r._sin<0)r._mdat|=MD_SINM;
	}

	return r;	
}

Bikes::TrAngle TrAngle::operator-( TrAngle &ta )
{
	TrAngle r;
	r._mdat=MD_NULL;	
	if(ta._mdat&_mdat&MD_RADCALC)
	{
		r.setRad(_rad-ta._rad);	
		if((ta._mdat&_mdat&MD_TRCALC))
		{
			r._mdat|=MD_SINCALC|MD_COSCALC|MD_TRCALC;
			rnum s=sin();
			rnum c=cos();
			rnum s_=ta.sin();
			rnum c_=ta.cos();
			r._cos=c*c_+s*s_; //~?
			r._sin=s*c_-c*s_; //~?		
		}
	}else
	{
		r._mdat|=MD_SINCALC|MD_COSCALC|MD_TRCALC;
		rnum s=sin();
		rnum c=cos();
		rnum s_=ta.sin();
		rnum c_=ta.cos();
		r._cos=c*c_+s*s_; //~?
		r._sin=s*c_-c*s_; //~?	
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
	_mdat&=MD_NTANCALC;	
	if(ta._mdat&_mdat&MD_RADCALC)
	{	
		if(ta._mdat&_mdat&MD_TRCALC)
		{			
			_rad+=ta._rad;	
			rnum c=cos();
			rnum s=sin();
			rnum c_=ta.cos();
			rnum s_=ta.sin();
			_cos=c*c_-s*s_; //~?
			_sin=s*c_+c*s_; //~?
			if(_cos<0)_mdat|=MD_COSM;
			else _mdat&=MD_NCOSM;
			if(_sin<0)_mdat|=MD_SINM;		
			else _mdat&=MD_NSINM;
		}else
		{
			setRad(_rad+ta._rad);
		}
	}else
	{
		_mdat&=MD_NRADCALC;
		rnum c=cos();
		rnum s=sin();
		rnum c_=ta.cos();
		rnum s_=ta.sin();
		_cos=c*c_-s*s_; //~?
		_sin=s*c_+c*s_; //~?
		if(_cos<0)_mdat|=MD_COSM;
		else _mdat&=MD_NCOSM;
		if(_sin<0)_mdat|=MD_SINM;		
		else _mdat&=MD_NSINM;
	}

}
void TrAngle::operator+=( const TrAngleConst &ta )
{
	_mdat&=MD_NTANCALC;	
	if(_mdat&MD_RADCALC)
	{		
		if( _mdat&MD_TRCALC )
		{		
			_rad+=ta.rad_val;	
			rnum c=cos();
			rnum s=sin();
			rnum c_=ta.cos_val;
			rnum s_=ta.sin_val;
			_cos=c*c_-s*s_; //~?
			_sin=s*c_+c*s_; //~?
			if(_cos<0)_mdat|=MD_COSM;
			else _mdat&=MD_NCOSM;
			if(_sin<0)_mdat|=MD_SINM;		
			else _mdat&=MD_NSINM;
		}else
		{
			setRad(_rad+ta.rad_val);
		}
	}else
	{
		rnum c=cos();
		rnum s=sin();
		rnum c_=ta.cos_val;
		rnum s_=ta.sin_val;
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
	
	if(ta._mdat&_mdat&MD_RADCALC)
	{
		if(ta._mdat&_mdat&MD_TRCALC)
		{	
			_rad-=ta._rad;	
			rnum c=cos();
			rnum s=sin();
			rnum c_=ta.cos();
			rnum s_=ta.sin();
			_cos=c*c_+s*s_; //~?
			_sin=s*c_-c*s_; //~?
			if(_cos<0)_mdat|=MD_COSM;
			else _mdat&=MD_NCOSM;
			if(_sin<0)_mdat|=MD_SINM;		
			else _mdat&=MD_NSINM;
		}else
		{
			setRad(_rad-ta._rad);
		}
	}
	else
	{
		_mdat&=MD_NRADCALC;
		rnum c=cos();
		rnum s=sin();
		rnum c_=ta.cos();
		rnum s_=ta.sin();
		_cos=c*c_+s*s_; //~?
		_sin=s*c_-c*s_; //~?
		if(_cos<0)_mdat|=MD_COSM;
		else _mdat&=MD_NCOSM;
		if(_sin<0)_mdat|=MD_SINM;		
		else _mdat&=MD_NSINM;
	}
}

void TrAngle::operator-=( const TrAngleConst &ta )
{
	_mdat&=MD_NTANCALC;

	if(_mdat&MD_RADCALC)
	{
		if(_mdat&MD_TRCALC)
		{	
			_rad-=ta.rad_val;	
			rnum c=cos();
			rnum s=sin();
			rnum c_=ta.cos_val;
			rnum s_=ta.sin_val;
			_cos=c*c_+s*s_; //~?
			_sin=s*c_-c*s_; //~?
			if(_cos<0)_mdat|=MD_COSM;
			else _mdat&=MD_NCOSM;
			if(_sin<0)_mdat|=MD_SINM;		
			else _mdat&=MD_NSINM;
		}else
		{
			setRad(_rad-ta.rad_val);
		}
	}
	else
	{
		_mdat&=MD_NRADCALC;
		rnum c=cos();
		rnum s=sin();
		rnum c_=ta.cos_val;
		rnum s_=ta.sin_val;
		_cos=c*c_+s*s_; //~?
		_sin=s*c_-c*s_; //~?
		if(_cos<0)_mdat|=MD_COSM;
		else _mdat&=MD_NCOSM;
		if(_sin<0)_mdat|=MD_SINM;		
		else _mdat&=MD_NSINM;
	}
}

TrAngle TrAngle::operator-( const TrAngleConst &ta )
{
	TrAngle r;
	r._mdat=MD_NULL;	
	if(_mdat&MD_RADCALC)
	{
		r.setRad(_rad-ta.rad_val);	
		if(_mdat&MD_TRCALC)
		{
			r._mdat|=MD_SINCALC|MD_COSCALC|MD_TRCALC;
			rnum s=sin();
			rnum c=cos();
			rnum s_=ta.sin_val;
			rnum c_=ta.cos_val;
			r._cos=c*c_+s*s_; //~?
			r._sin=s*c_-c*s_; //~?		
		}
	}else
	{
		r._mdat|=MD_SINCALC|MD_COSCALC|MD_TRCALC;
		rnum s=sin();
		rnum c=cos();
		rnum s_=ta.sin_val;
		rnum c_=ta.cos_val;
		r._cos=c*c_+s*s_; //~?
		r._sin=s*c_-c*s_; //~?	
		if(r._cos<0)r._mdat|=MD_COSM;
		if(r._sin<0)r._mdat|=MD_SINM;
	}


	return r;	
}



bool TrAngle::operator<( rnum ang_rad )
{
	return rad()<ang_rad;
}

bool TrAngle::operator<=( rnum ang_rad )
{
	return rad()<=ang_rad;
}

bool TrAngle::operator>( rnum ang_rad )
{
	return rad()>ang_rad;
}


bool TrAngle::operator>=( rnum ang_rad )
{
	return rad()>=ang_rad;
}

void TrAngle::trCalc()
{
	sin();
	cos();
	tg();
}

rnum TrAngle::tan()
{
	return tg();
}


void TrAngle::operator+=( rnum ang_rad )
{
	setRad(ang_rad+rad());
}


void TrAngle::operator-=( rnum ang_rad )
{
	setRad(rad()-ang_rad);
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
			if(ta._mdat&MD_COSM)
			{
				//....
// 				if(_sin>0)
// 				{
// 					return _sin<ta._sin;
// 				}else
// 				{
					//.....
// 					return _sin<ta._sin;
// 				}
				//....
			}else
			{
				return _sin>0;
			}
		}else
		{
			if(ta._mdat&MD_COSM)
			{
				return ta._sin<0;
			}else
			{
				return _sin>ta._sin;
			}
		}
	}
	//if((_mdat&MD_COSCALC)||(ta._mdat&MD_COSCALC))
	{

	}

	return rad()>rad();
}

bool TrAngle::operator<( TrAngle &ta )
{
	return rad()<ta.rad();
}

rnum TrAngle::ctg()
{
	return 1.0/not0(tg());
}






}