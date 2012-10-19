#include "AbstractContainer.h"





////////////////////// AbstractContainerModel ///////////////////////////////


AbstractContainerModel::~AbstractContainerModel()
{
	if(_container)
	{
		//_container->RemoveModel(*this); //?
		_container->RemoveModel(index);
	}
}


//////////////////////// AbstractContainer /////////////////////////////////
// 
BoolMarkerList AbstractContainer::_indexList;

int AbstractContainer::ReserveIndex()
{
	int c=_indexList.count();
	for(int i=0; i<c; i++)
		if(!_indexList[i]){ _indexList[i]=true; return i;}
	_indexList[c]=true;
	return c;
}

void AbstractContainer::ReleaseIndex(int index)
{
	//if(_indexList.isSet(index)) 
	_indexList[index]=false;
}


AbstractContainer::AbstractContainer()
{

}

AbstractContainer::~AbstractContainer()
{

// 	for(int i=0; i<_models.size(); i++)
// 	{
// 		//if(_models[i]) _models->ContainerLeaved();
// 	}
}


AbstractContainerModel* AbstractContainer::Model(AbstractContainerModelMap *map/*=0*/ )
{
	PMap<AbstractContainerModel*>::iterator itr=_modelsMap.find(map);
	if(itr==_modelsMap.end()) return 0;
	return  _modelsMap[itr->first];

}




void AbstractContainer::RemoveModel(AbstractContainerModel &model)
{
	RemoveModel(model.index);	
}

int AbstractContainer::ModelsCount() const
{
	return _models.size();
}

void AbstractContainer::ModelsClear()
{
	for(int i =0;i<_models.size(); i++)
	{
		_models[i]->ContainerLeaved();
	}
	_models.clear();
}

void AbstractContainer::operator+=( AbstractContainerModel &m )
{
	SetModel(m);
}

void AbstractContainer::SetModel(AbstractContainerModel &model)
{
// 	
// 	model._container=this;
// 	_modelsMap[model._map]=&model;
// 

// 	m->_containers.remove(this);		
// 	for(int i=0; i<_models.count(); i++)
// 		{
// 			if(_models[i]==m)
// 			{
// 				_models[i]=0;				
// 				break;
// 			}
// 		}
// 	}
// 
// 	for(int i=_models.count(); i<=index; i++) _models+=0;
// 
// 	if(_models[index])
// 	{
// 		if(_models[index]!=m)
// 		{
// 			_models[index]->_containers.remove(this);
// 			_models[index]->ContainerLeaved(this);
// 		}		
// 	}
// 
// 	_models[index]=m;
// 
// 	if(m)
// 	{
// 		m->_containers+=this;
// 	}
}
