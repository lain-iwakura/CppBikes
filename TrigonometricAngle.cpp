#include "TrigonometricAngle.h"


using namespace CppBikes;



TrAngle::TrAngle(RNUM cos_val, bool sin_negative)
{
	setCos(cos_val,sin_negative);
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
	if(_mdat&MD_COSCALC)
	{
		_sin=sqrt(1-_cos*_cos);
		if(_mdat&MD_SINM) _sin=-_sin;
		_mdat|=MD_SINCALC;
		return _sin;
	}
	if(_mdat&MD_TANCALC)
	{
		_mdat|=MD_SINCALC;
		_sin=sqrt(1.0/(1.0+_tan*_tan));
		if(_mdat&MD_SINM) _sin=-_sin;
		return _sin;
	}
	if(_mdat&MD_RADCALC)
	{
		_mdat|=MD_SINCALC;
		_sin=::sin(_rad);
		return _sin;
	}
	return 0;
}
RNUM TrAngle::Cos()
{
	if(_mdat&MD_COSCALC) return _cos;
	if(_mdat&MD_SINCALC)
	{
		_mdat|=MD_COSCALC;
		_cos=sqrt(1-_sin*_sin);
		if(_mdat&MD_COSM) _cos*=-_cos;
		
		return _cos;
	}
	if(_mdat&MD_TANCALC)
	{
		_mdat|=MD_COSCALC;
		_cos=sqrt(1.0/(1.0/(_tan*_tan)+1.0));
		if(_mdat&MD_COSM) _cos=-_cos;
		return _cos;
	}
	if(_mdat&MD_RADCALC)
	{
		_mdat|=MD_COSCALC;
		_cos=::cos(_rad);
		return _cos;
	}
	return 1;
}
RNUM TrAngle::Tg()
{
	if(_mdat&MD_TANCALC) return _tan;
	if(_mdat&(MD_COSCALC|MD_SINCALC))
	{
		_mdat|=MD_TANCALC;
		_tan=Sin()/Cos(); 		
		return _tan;
	}
	if(_mdat&MD_RADCALC)
	{
		_mdat|=MD_TANCALC;
		_tan=::tan(_rad);
	}
	return 0;
}
RNUM TrAngle::Rad()
{
	if(_mdat&MD_RADCALC) return _rad;
	if(_mdat&MD_COSCALC)
	{
		_rad=arccos(_cos);
		_mdat|=MD_RADCALC;
		return _rad;
	}
	if(_mdat&MD_SINCALC)
	{
		_rad=arcsin(_sin);
		_mdat|=MD_RADCALC;
		return _rad;
	}
	if(_mdat&MD_TANCALC)
	{
		_rad=atan(_tan);
		_mdat|=MD_RADCALC;
		return _rad;
	}
	return 0;
}
RNUM TrAngle::Deg()
{
	return RAD_to_DEG(Rad());
}

RNUM TrAngle::sigSin()
{
	return (_mdat&MD_SINM)?(-1.0):(1.0);
}
RNUM TrAngle::sigCos()
{
	return (_mdat&MD_COSM)?(-1.0):(1.0);
}