#ifndef MYCPP_QUEUE_H
#define MYCPP_QUEUE_H


namespace mycpp
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
		Queue():head(0),tail(0)
		{				
		}

		~Queue()
		{
			if(head)
			{
				QueueItem<T> *qi=head;
				QueueItem<T> *nqi=head;
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
			
			if(tail)
			{
				tail->next=nqi;
				tail=nqi;			
			}else
			{
				tail=nqi;
				head=nqi;
			}						
		}

		T* get() const // возвращает первый элемент // не_безопасно в случае пустой очереди
		{
			return head->data;
		}

		void erase() // удаляет последний элемент // не_безопасно в случае пустой очереди  
		{
			QueueItem<T> *rqi=head;
			head=head->next;
			if(head==0) tail=0;
			delete rqi;			
		}



		T* pass() // get()+ erase()
		{
			QueueItem<T> *rqi=head;			
			head=head->next;
			if(head==0) tail=0;
			T *r=rqi->data;
			rqi->data=0;
			delete rqi;
			return r;
		}

		
		bool isEmpty() const // потоко_не_безопасно в случае пустой очереди
		{
			//return head==0;//?
			return tail==0;
		}

		int size() const // потоко_не_безопасно и медленно
		{
			if(head)
			{		
				int s=1;
				QueueItem<T> *qi=head;
				while(qi=qi->next) s++;
				return s;
			}
			return 0;
		}

		void clear() // очищает очередь // потоко_не_безопасно
		{
			if(head)
			{
				QueueItem<T> *qi=head;
				QueueItem<T> *nqi=head;
				while(nqi)
				{
					qi=nqi;
					nqi=nqi->next;
					delete qi;
				}
				head=0;
				tail=0;
			}
		}

		void add(const T &obj){	take(new T(obj));}
		void operator +=(T *pObj){take(pObj);}
		void operator +=(const T &obj){take(new T(obj));}

	private:
		QueueItem<T> *head;
		QueueItem<T> *tail;

	};


}


#endif