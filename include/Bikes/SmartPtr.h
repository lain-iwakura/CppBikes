#ifndef _BIKES_SMARTPTR_H_
#define _BIKES_SMARTPTR_H_
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <memory>

namespace Bikes
{

	template<class T>
	class Ptr
	{
	public:
		typedef typename boost::shared_ptr<T> Shared;
		typedef typename boost::weak_ptr<T> Weak;
		typedef typename std::auto_ptr<T> Auto;
				
	//--------------------------------------------------
		template<class PtrT>
		static T* get(const PtrT& ptr)
		{
			return ptr.get();
		}

		static T* get(T *p)
		{
			return p;
		}

		static const T* get(const T *p)
		{
			return p;
		}

		template<class PtrT>
		static void reset(PtrT& ptr, T* p)
		{
			ptr.reset(p);
		}

		static void reset( T*& rp, T* p)
		{
			if(rp) delete rp;
			rp=p;
		}		
	};

	
template<class TL, class TR>
typename Ptr<TL>::Shared dynamic_ptr_cast(typename const Ptr<TR>::Shared & r)
{
	return boost::dynamic_pointer_cast<TL>(r);
}

}

#define BIKES_GET_P(p) (&(*(p)))
 

#endif