#include <Geom/Basis.h>
#include <Geom/VectorPair.h>

namespace Bikes
{

Basis::Basis( const Vector& vi, const Vector& vj, const Vector& vk ):
	i(vi),
	j(vj),
	k(vk)
{
}

Basis::Basis( const VectorPair& pair_ij, const Vector& vk ):
	i(pair_ij.vi),
	j(pair_ij.vj),
	k(vk)
{
}

Basis::Basis( const Vector& vi, const VectorPair& pair_jk ):
	i(vi),
	j(pair_jk.vi),
	k(pair_jk.vj)
{
}

Basis::Basis( const Basis& ijk ):
	i(ijk.i),
	j(ijk.j),
	k(ijk.j)
{
}

Basis::Basis( const Vector& vi, const Vector& vj, bool right/*=true*/ )
{
	setOrtonormalByIJ(vi,vj,right);
}

Basis::Basis( const VectorPair& pair_ij, bool right/*=true*/ )
{
	setOrtonormalByIJ(pair_ij.vi,pair_ij.vj,right);
}

Basis::~Basis()
{
}

void Basis::normalize()
{
	i.normalize();
	j.normalize();
	k.normalize();
}

void Basis::setScale( rnum scale )
{
	i.setLength(scale);
	j.setLength(scale);
	k.setLength(scale);
}

void Basis::scaling( rnum scaleFactor )
{
	i *= scaleFactor;
	j *= scaleFactor;
	k *= scaleFactor;
}

void Basis::setOrtonormalByIJ( const Vector& vi, const Vector& vj, bool right)
{
	i = vi;
	k = vi*vj;
	i.normalize();
	k.normalize();
	if(right)		
		j = k*i;
	else
		j = i*k;
}

void Basis::setOrtonormalByIJ( const VectorPair& ij, bool right/*=true*/ )
{
	setOrtonormalByIJ(ij.vi,ij.vj,right);
}

}