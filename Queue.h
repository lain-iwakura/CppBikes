#ifndef MYCPP_QUEUE_H
#define MYCPP_QUEUE_H


namespace CppBikes
{

	template<class T> class QueueItem
	{
	public:
		QueueItem(T *d=0, QueueItem<T> *_next=0):data(d),next(_next)
		{			
		}
		QueueItem(const T &d, QueueItem<T> *_next=0):data(new T(d)),next(_next)
		{			
		}
		QueueItem(const QueueItem<T> &qi, QueueItem<T> *_next=0):next(_next)
		{
			if(qi.data) data=new T(*qi.data);
			else qi.data=0;
		}
		void operator = (const QueueItem<T> &qi)
		{
			if(data) delete data;
			if(qi.data) data=new T(*qi.data);
			else data=0;
		}
		~QueueItem()
		{
			if(data) delete data;
		}

		T *data;
		QueueItem<T> *next;
	};



	template<class T> class Queue
	{
	public:
		Queue():_head(0),_tail(0)
		{				
		}

		~Queue()
		{
			if(_head)
			{
				QueueItem<T> *qi=_head;
				QueueItem<T> *nqi=_head;
				while(nqi)
				{
					qi=nqi;
					nqi=nqi->next;
					delete qi;
				}
			}
		}		



		void take(T *pObj) // потоко_не_безопасно в случае пустой очереди 
		{
			QueueItem<T> *nqi=new QueueItem<T>(pObj);
			
			if(_tail)
			{
				_tail->next=nqi;
				_tail=nqi;			
			}else
			{
				_tail=nqi;
				_head=nqi;
			}						
		}

		void takeQueue(Queue<T> &q)
		{
			if(q._head)
			{			
				if(_tail) _tail->next=q._head;							
				else _head=q._head;	
				_tail=q._tail;
				q._tail=0;
				q._head=0;
			}
		}

		void takeOneItem(Queue<T> &q) // берем один элемент из головы q и добавляем в конец
		{
// 			if(q._head)
// 			{
				if(_tail)
				{
					_tail->next=q._head;
					_tail=q._head;			
				}else
				{
					_tail=q._head;
					_head=q._head;
				}
				//QueueItem<T> *nqi=q._head;
				q._head=q._head->next;
				if(q._head==0) q._tail=0;
				_tail->next=0;				
//			}
		}

		T* head() const // возвращает первый элемент // не_безопасно в случае пустой очереди
		{
			return _head->data;
		}

		T* tail() const // возвращает последний элемент // не_безопасно в случае пустой очереди
		{
			return _tail->data;
		}

		void erase() // удаляет первый элемент // не_безопасно в случае пустой очереди  
		{
			QueueItem<T> *rqi=_head;
			_head=_head->next;
			if(_head==0) _tail=0;
			delete rqi;			
		}


		T* pass() // get()+ erase()
		{
			QueueItem<T> *rqi=_head;			
			_head=_head->next;
			if(_head==0) _tail=0;
			T *r=rqi->data;
			rqi->data=0;
			delete rqi;
			return r;
		}
		

		
		bool isEmpty() const // потоко_не_безопасно в случае пустой очереди
		{
			//return head==0;//?
			return _tail==0;
		}

		int size() const // потоко_не_безопасно и медленно
		{
			if(_head)
			{		
				int s=1;
				QueueItem<T> *qi=_head;
				while(qi=qi->next) s++;
				return s;
			}
			return 0;
		}

		void clear() // очищает очередь // потоко_не_безопасно
		{
			if(_head)
			{
				QueueItem<T> *qi=_head;
				QueueItem<T> *nqi=_head;
				while(nqi)
				{
					qi=nqi;
					nqi=nqi->next;
					delete qi;
				}
				_head=0;
				_tail=0;
			}
		}

		void add(const T &obj){	take(new T(obj));}
		void operator +=(T *pObj){take(pObj);}
		void operator +=(const T &obj){take(new T(obj));}

	private:
		QueueItem<T> *_head;
		QueueItem<T> *_tail;

	};


}


#endif