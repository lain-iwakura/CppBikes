#ifndef TYPECOLLECTOR_H
#define TYPECOLLECTOR_H
#include <vector>

namespace CppBikes
{
	

//================================================================
// TypeCollector<Collector> ->
//================================================================
	template<class Collector>
	class TypeCollector
	{
	public:

		// Реестр типов
		template<class T> 
		class TypeRegister;

		// 
		template<class T> 
		class TypeDataArray;

		class TypeDataMap;

		typedef TypeDataArray<Collector> TypeDataContainer;

		template<int collectionId> 
		class TypeCollection;

		static int typeCount()
		{
			return typeIter;
		}

		template<class T>
		static int typeId()
		{
			return TypeRegister<T>::typeId;
		}

		
		

	private:
		static  int typeIter;		
	};
//--------
	template<class Collector>
	int TypeCollector<Collector>::typeIter=0;
//================================================================
// <- TypeCollector<Collector> 
//================================================================

	
	namespace Private
	{
		class AbstractTypeDataArray
		{
		public:
			virtual ~AbstractTypeDataArray(){}
		};
		//-------------
		class AbstractTypeData
		{
		public:
			virtual ~AbstractTypeData(){}
		};
		//-------------
		template<class DataT>
		class TypeData: public AbstractTypeData
		{
		public:	
			DataT d;
		};
	}


//================================================================
// TypeCollector<Collector>::TypeRegister<T> ->
//================================================================
	template<class Collector> template<class T>
	class TypeCollector<Collector>::TypeRegister
	{
	public:
		static const int typeId;
	};
//--------------	
	template<class Collector> template<class T>
	const int TypeCollector<Collector>::TypeRegister<T>::typeId=TypeCollector<Collector>::typeIter++;
//================================================================
// <- TypeCollector<Collector>::TypeRegister<T>
//================================================================



//================================================================
// TypeCollector<Collector>::TypeDataArray<DataT> ->
//================================================================
	template<class Collector> template<class T>
	class TypeCollector<Collector>::TypeDataArray: public Private::AbstractTypeDataArray, public TypeCollector<T>
	{
	public:

		TypeDataArray(): d(new std::vector<Private::AbstractTypeData*>(typeCount(),0)){}
		~TypeDataArray()
		{
			for(unsigned int i=0; i<d->size(); i++)
				if((*d)[i]) delete (*d)[i];
			delete d;
		}

		void clear()
		{
			for(unsigned int i=0; i<d->size(); i++)
				if((*d)[i]){delete (*d)[i]; (*d)[i]=0;}
		}

		template<class DataT>
		void clear()
		{
			int i=TypeRegister<DataT>::typeId;
			if((*d)[i]){delete (*d)[i]; (*d)[i]=0;}
		}

		template<class DataT>
		DataT& data()
		{
			Private::TypeData<DataT> *td=dynamic_cast<Private::TypeData<DataT> * >((*d)[TypeRegister<DataT>::typeId]);
			if(td==0)
			{
				td= new Private::TypeData<DataT>();
				(*d)[TypeRegister<DataT>::typeId]=td;
			}
			return td->d;
		}

		template<class DataT>
		const DataT& data() const 
		{
			Private::TypeData<DataT> *td=dynamic_cast<Private::TypeData<DataT> * >((*d)[TypeRegister<DataT>::typeId]);
			if(td==0)
			{
				td= new Private::TypeData<DataT>();
				(*d)[TypeRegister<DataT>::typeId]=td;
			}
			return td->d;
		}

	private:
		std::vector<Private::AbstractTypeData*> *d;
	};
//================================================================
// <- TypeCollector<Collector>::TypeDataArray<DataT>
//================================================================


//================================================================
// TypeCollector<Collector>::TypeDataContainer ->
//================================================================
	template<class Collector>
	class TypeCollector<Collector>::TypeDataMap: public TypeCollector<Collector>
	{
	public:

		TypeDataMap():d(new std::vector<Private::AbstractTypeDataArray*>(typeCount(),0)){}
		~TypeDataMap()
		{
			for(unsigned int i=0; i<d->size(); i++) 
				if((*d)[i]) delete (*d)[i];
			delete d;
		}

		void clear()
		{
			for(unsigned int i=0; i<d->size(); i++) 
				if((*d)[i]){ delete (*d)[i]; (*d)[i]=0; }
		}

		template <class T>
		void clear()
		{
			int i=TypeRegister<T>::typeId;
			if((*d)[i]){ delete (*d)[i]; (*d)[i]=0;	}
		}

		template<class T, class DataT>
		void clear()
		{
			int i=TypeRegister<T>::typeId;
			if(TypeDataArray<T>* tda= dynamic_cast<TypeDataArray<T>*>((*d)[i]))
			{
				tda->clear<DataT>();
			}
		}

		template<class T>
		TypeDataArray<T>& dataArray()
		{		
			TypeDataArray<T> *tda=dynamic_cast< TypeDataArray<T>* >((*d)[TypeRegister<T>::typeId]);
			if(tda==0)
			{
				tda=new TypeDataArray<T>();
				(*d)[TypeRegister<T>::typeId]=tda;
			}
			return *tda;
		}

		template<class T>
		const TypeDataArray<T>& dataArray() const
		{		
			TypeDataArray<T> *tda=dynamic_cast< TypeDataArray<T>* >((*d)[TypeRegister<T>::typeId]);
			if(tda==0)
			{
				tda=new TypeDataArray<T>();
				(*d)[TypeRegister<T>::typeId]=tda;
			}
			return *tda;
		}

		template<class T, class DataT>
		DataT& data()
		{		
			TypeDataArray<T> *tda=dynamic_cast< TypeDataArray<T>* >((*d)[TypeRegister<T>::typeId]);
			if(tda==0)
			{
				tda=new TypeDataArray<T>();
				(*d)[TypeRegister<T>::typeId]=tda;
			}
			return tda->data<DataT>();
		}

		template<class T, class DataT>
		const DataT& data() const
		{		
			TypeDataArray<T> *tda=dynamic_cast< TypeDataArray<T>* >((*d)[TypeRegister<T>::typeId]);
			if(tda==0)
			{
				tda=new TypeDataArray<T>();
				(*d)[TypeRegister<T>::typeId]=tda;
			}
			return tda->data<DataT>();
		}

	private:
		std::vector<Private::AbstractTypeDataArray*> *d;			
	};
//================================================================
// <- TypeCollector<Collector>::TypeDataContainer
//================================================================


//================================================================
// TypeCollector<Collector>::TypeCollection ->
//================================================================
	template<class Collector> template<int collectionId>
	class TypeCollector<Collector>::TypeCollection: public TypeCollector<TypeCollection<collectionId> >
	{		
	};
//================================================================
// <- TypeCollector<Collector>::TypeCollection
//================================================================



// 	template<class Collector>
// 	class TypeCollector<Collector>::TypeDataContainer


}//CppBikes

#endif //TYPECOLLECTOR_H