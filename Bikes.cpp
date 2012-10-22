#include "Bikes.h"

using namespace CppBikes;







// long long iBit64(int i)
// {
// 	return 1U<<(i);
// }
// 
// 
// int iBit32( int i )
// {
// 
// }
// 
// short iBit16( int i )
// {
// 
// }
// 
// 
unsigned char iBit8( int i ){return 1U<<(i);}















void VoidCopy(void *a, void *b, unsigned int n) // a=b;
{	
	char *cha=(char*)a;
	char *chb=(char*)b;
	for(int i=0; i<n; i++) cha[i]=chb[i];
}

bool VoidIsEqual(void *a, void *b, unsigned int n) // a==b
{
	char *cha=(char*)a;
	char *chb=(char*)b;
	for(int i=0; i<n; i++) if(cha[i]!=chb[i]) return false;
	return true;
}


void VoidInterchange(void* a, void* b, unsigned int n) //c=a; a=b; b=c;
{	
	char buf;
	char *cha=(char*)a;
	char *chb=(char*)b;
	for(int i=0; i<n; i++)
	{
		buf=cha[i];
		cha[i]=chb[i];
		chb[i]=buf;
	}
}
