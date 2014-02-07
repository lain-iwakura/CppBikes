#include <Geometry/VectorTriple.h>
#include <Geometry/VectorPair.h>

namespace Bikes
{
	void f();
	{
		Vector v1;
		Vector v2;
		Vector v3;

		Basis b; 

		b = v1 & v2 & v3;

		b = v1 && v2 && v3;



	}

VectorTriple::VectorTriple( const Vector& vi, const Vector& vj, const Vector& vk ):
	i(vi),
	j(vj),
	k(vk)
{
}

VectorTriple::VectorTriple( const VectorPair& pair_ij, const Vector& vk ):
	i(pair_ij.i),
	j(pair_ij.j),
	k(vk)
{
}

VectorTriple::VectorTriple( const Vector& vi, const VectorPair& pair_jk ):
	i(vi),
	j(pair_jk.i),
	k(pair_jk.j)
{
}

VectorTriple::VectorTriple( const VectorTriple& ijk ):
	i(ijk.i),
	j(ijk.j),
	k(ijk.j)
{
}

VectorTriple::~VectorTriple()
{
}

void VectorTriple::normalize()
{
	i.normalize();
	j.normalize();
	k.normalize();
}

// void VectorTriple::ortonormalise_byIJ()
// {
// 	k = i * j;
// }

void VectorTriple::setScale( rnum scale )
{
	i.setLength(scale);
	j.setLength(scale);
	k.setLength(scale);
}

void VectorTriple::scaling( rnum scaleFactor )
{
	i *= scaleFactor;
	j *= scaleFactor;
	k *= scaleFactor;
}

void VectorTriple::setOrtonormalByIJ( const Vector& vi, const Vector& vj, bool right)
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

void VectorTriple::setOrtonormalByIJ( const VectorPair& ij, bool right/*=true*/ )
{
	setOrtonormalByIJ(ij.i,ij.j,right);
}

}