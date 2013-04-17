#ifndef _BIKES_TESTBIKES_H_
#define _BIKES_TESTBIKES_H_

namespace Bikes
{
	
	template<class T>
	bool isPointer(const T&){return false;}

	template<class T>
	bool isPointer(const T*){return true;}

namespace Test
{
	//TODO: добавить тесты

	bool test_ByteStream();
	bool test_RawArray();
	bool test_BikesStream();
	bool test_main();
}	
}

#endif