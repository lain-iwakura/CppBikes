#ifndef ABSTRACTCONTAINER_H
#define ABSTRACTCONTAINER_H
#include "List.h"
#include "PhantomObject.h"
#include "SetList.h"
#include <map>

namespace CppBikes
{


template<class T> class PMap: public std::map<void*,T>
{
public:

	typedef std::map<void*,T> pmap;

	//template<class TKey> T& operator[](TKey &k){return pmap::operator [](&k);}

	//using pmap::operator [];

// 	T& operator [](void *k)
// 	{
// 		return pmap::operator [](k);
// 	}

	T& At(int i) 
	{
        typename std::map<void*,T>::iterator it(this->begin());
		for(int j=0; j<i; j++)it++;

		return pmap::operator [](it->first);
	}

	int Count() const
	{
        return this->size();
	}

//	using pmap::size;
//	using pmap::clear;

};


//////////////////////////////////////////////////
//////////////////////////////////////////////////
//////////////////////////////////////////////////
class AbstractContainer;
class AbstractContainerModelMap;
template<class T> class ContainerModelMap;
////////////





////////////////////////////////////
class AbstractContainerModel
{
public:
	AbstractContainerModel(int i=0, AbstractContainer* ac=0):index(i),_container(ac){}	
	virtual ~AbstractContainerModel();

protected:
	AbstractContainer* _container;
	//AbstractContainerModelMap* _map;
	int index;
 	virtual void ContainerLeaved() // (X) (?)	
	{
		_container=0; //?
	}
	
	friend class AbstractContainer;	
};
////////////////////////////////////






////////////////////////////////////
template<class T>
class ContainerModelMapItem: public AbstractContainerModel
{
public:

	ContainerModelMapItem(int i=0,AbstractContainer* ac=0):AbstractContainerModel(i,ac){}
	ContainerModelMapItem(const T& obj, AbstractContainerModelMap *m=0,AbstractContainer* ac=0):AbstractContainerModel(m,ac),OBJ(obj){}
	T OBJ;		
};
////////////////////////////////////





////////////////////////////////////
class AbstractContainerModelMap
{
protected:
	virtual void ContainerLeaved(AbstractContainerModel* model){}
};
////////////////////////////////////



////////////////////////////////////
class AbstractContainer
{
public:

	AbstractContainer();
	AbstractContainer(const AbstractContainer &ac); //?
	virtual ~AbstractContainer();

 	AbstractContainerModel* Model(AbstractContainerModelMap *map=0); //?
	AbstractContainerModel* Model(int i)
	{
		if(i>=_models.size()) return 0;
		return _models[i];
	}
	template<class T> ContainerModelMapItem<T>* ModelT(ContainerModelMap<T> *)
	{
    //	if(TypeInfo<T>::id >=_models.size()) return 0;
        return 0;//_models[TypeInfo<T>::id];
		//static T o;//?
		//static List<T> lo; //?
	}

//	AbstractContainerModel* PassModel(AbstractContainerModelMap *map=0);

	//template<T> AbstractContainerModel* TModel(ContainerModelMapItem<T> &it); //???????

	void SetModel(AbstractContainerModel &m);

	void SetModel(AbstractContainerModel *m, int i=0)
	{
		if(i>=_models.size())
		{
			//_models.reserve(i+1);
			_models.resize(i+1,0);			
		}
		_models[i]=m;		
	}

	template<class T> void SetModelT(T * pO)
	{
//		for(int i=_models.size(); i<=TypeInfo<T>::id; i++) _models.push_back(0);
    //	_models[TypeInfo<T>::id]=pO;
	}


	void RemoveModel(AbstractContainerModel &m);
	void RemoveModel(int i)
	{
		if(i<_models.size()) _models[i]=0;
	}
	void operator +=(AbstractContainerModel &m);
	int ModelsCount() const;
	void ModelsClear();

	static int ReserveIndex();			 // ~
	static void ReleaseIndex(int index); // ~

	
private:
	static BoolMarkerList _indexList;
	std::vector<AbstractContainerModel*> _models;
	PMap<AbstractContainerModel* > _modelsMap; // <- pContainerModelMap
	friend class AbstractContainerModel;
};
////////////////////////////////////




template<class T> class ContainerModelMap: private AbstractContainerModelMap //private ContainerModelMapItem<T>::ContainerModelMapItemParent
{
public:


// 	ContainerModelMap(int abstractContainerIndex):contents()
// 	{
// 		contIndex=abstractContainerIndex;
// 		AbstractContainer::ReserveIndex(abstractContainerIndex);
// 	}

	ContainerModelMap():contents()
	{
		contIndex=AbstractContainer::ReserveIndex();		
	}

	~ContainerModelMap()
	{
		AbstractContainer::ReleaseIndex(contIndex);		
	}



	T& operator [](AbstractContainer &ACont){return (*this)[&ACont];}
	T& operator [](AbstractContainer *ACont) // может вернуть "чужой" объект (если другой объект того же типа был записан с тем же индексом)
	{
		ContainerModelMapItem<T> *tm=dynamic_cast<ContainerModelMapItem<T> *>(ACont->Model(contIndex));
		if(tm)	return tm->OBJ;

		contents.Take(tm=new ContainerModelMapItem<T>(contIndex,ACont));		
		ACont->SetModel(tm,contIndex);
		return tm->OBJ; 
	}

	T& operator [](int i){return contents[i];}
	const T& operator [](int i) const {return contents[i];}

// 	void Set(AbstractContainer *ACont, const T &obj){Set(*ACont,obj);}
// 	void Set(AbstractContainer &ACont, const T &obj)
// 	{
// 		ContainerModelMapItem<T> *tm=(ContainerModelMapItem<T> *)ACont.Model(contIndex);
// 		if(tm)// if(ContainerModelMapItem<T> *tm=dynamic_cast<ContainerModelMapItem<T> *>(m))
// 		{
// 			tm->OBJ=obj;
// 		}else
// 		{
// 			contents.Take(new ContainerModelMapItem<T>(obj,this));
// 			ACont.SetModel(contents.last());
// 		}
// 	}
	

	T* At(const AbstractContainer *ACont) {return At(*ACont);}
	T* At(const AbstractContainer &ACont) 
	{
		ContainerModelMapItem<T> *tm=(ContainerModelMapItem<T> *)ACont.Model(contIndex);
		if(tm)// if(ContainerModelMapItem<T> *tm=dynamic_cast<ContainerModelMapItem<T> *>(m)) return tm->pObj();
		{
			return &tm->OBJ;
		}
		return 0;
	}

	T* At(int i) 
	{
		if(i>contents.count()||i<0) return 0;
		return &contents[i];
	}

	int Count() const {return contents.count();}
	
	bool RemoveAt(const AbstractContainer *ACont){return RemoveAt(*ACont);}
	bool RemoveAt(const AbstractContainer &ACont)
	{
		AbstractContainerModel *m=ACont.Model(contIndex);
		if(m) if(ContainerModelMapItem<T> *tm=dynamic_cast<ContainerModelMapItem<T> *>(m))
		{			
			if(contents.removeThat(tm))
			{
				return true;
			}else return false;
		}
		return false;
	}
	bool RemoveAt(int i)
	{
		if(i>contents.count()||i<0) return false;
		contents.removeAt(i);
		return true;
	}

	void Clear()
	{
		contents.clear();
	}

	void RemoveFreeItems()
	{
		for(int i=0; i<contents.count(); i++)
		{
			if(contents[i]._container==0)
			{
				contents.removeAt(i); 
				i--;
			}
		}
	}

private:
	int contIndex;
    List<ContainerModelMapItem<T> > contents;

// 	void ItemContainerLeaved(/*int index,*/ContainerModelMapItem<T>* cmmi, AbstractContainer* c ) //?
// 	{
// 		if(cmmi->ContainersCount()==0)
// 		{		
// 			contents.removeThat(cmmi);
// 		}
// 	}

	friend class AbstractContainer;
};
/////////////////////////////////////////////////////////


//template<class T> int ContainerModelMap<T>::stindex=AbstractContainer::ReserveIndex();


}
#endif
