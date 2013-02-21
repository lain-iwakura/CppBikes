#ifndef TYPEREGISTER_H
#define TYPEREGISTER_H

namespace CppBikes
{	

	class BaseTypeRegister
	{
	public:
		static int typeCount();	
	protected:
		static int typeIter;
	};	
	
	template<class T>
	class TypeRegister: public BaseTypeRegister
	{
	public:
		static const int typeId;
	};

	template<class T>
	const int TypeRegister<T>::typeId=BaseTypeRegister::typeIter++;

}
#endif