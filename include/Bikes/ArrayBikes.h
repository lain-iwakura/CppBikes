#ifndef _BIKES_ARRAYBIKES_H_
#define _BIKES_ARRAYBIKES_H_

namespace Bikes
{
	template<class ArrT, class ItmT>
	bool array_find(const ArrT & arr, int start_index, int end_index, const ItmT& itm, int *index=0)
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
	bool array_find(const ArrT & arr, int arr_size, const ItmT& itm, int *index=0)
	{
		return array_find(arr,0,arr_size-1,itm,index);
	}
	
	template<class ArrT, class ItmT>
	bool array_find(const ArrT & arr, const ItmT& itm, int *index=0)
	{
		return array_find(arr,arr.size(),itm,index);
	}

	template<class ArrT, class ItmT>
	bool array_remove(ArrT &arr, const ItmT& itm)
	{
		int index;
		if(array_find(arr,itm,&index))
		{
			arr.erase(arr.begin()+index);
			return true;
		}
		return false;
	}
}

#endif