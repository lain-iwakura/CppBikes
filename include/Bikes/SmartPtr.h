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
	};

}



#endif