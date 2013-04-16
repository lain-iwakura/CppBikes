#include "MemoryBikes.h"

using namespace Bikes;








void copy_void(void *a, void *b, unsigned int n) // a=b;
{	
	char *cha=(char*)a;
	char *chb=(char*)b;
	for(int i=0; i<n; i++) cha[i]=chb[i];
}

bool isEqual_void(void *a, void *b, unsigned int n) // a==b
{
	char *cha=(char*)a;
	char *chb=(char*)b;
	for(int i=0; i<n; i++) if(cha[i]!=chb[i]) return false;
	return true;
}


void swap_void(void* a, void* b, unsigned int n) //c=a; a=b; b=c;
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
