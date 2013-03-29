#ifndef _CPPBIKES_ARRAYBIKES_H_
#define _CPPBIKES_ARRAYBIKES_H_

namespace CppBikes
{
	
	template<class ArrT, class ItmT>
	bool find(const ArrT & arr, int start_index, int end_index, const ItmT& itm, int *index=0)
	{
		for(int i=start_index; i<=end_index; i++)
		{
			if(arr[i]==itm)
			{
				if(index) *index=i;
				return true;
			}
		}
		return false;
	}

	template<class ArrT, class ItmT>
	bool find(const ArrT & arr, int arr_size, const ItmT& itm, int *index=0)
	{
		return find(arr,0,arr_size-1,itm,index);
	}
	
	template<class ArrT, class ItmT>
	bool find(const ArrT & arr, const ItmT& itm, int *index=0)
	{
		return find(arr,arr.size(),itm,index);
	}

	template<class ItmT>
	bool remove(std::vector<ItmT> &arr, const ItmT& itm)
	{
		int index;
		if(find(arr,itm,&index))
		{
			arr.erase(arr.begin()+index);
			return true;
		}
		return false;
	}
}

#endif