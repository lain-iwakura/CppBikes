// Dependeds: loki

#ifndef SAVEDCOMMAND_H
#define SAVEDCOMMAND_H

#include <loki/Functor.h>
//#include "loki/Function.h"
#include <loki/TypelistMacros.h>

#include <Bikes/Queue.h>

#define SCMD_THREADSLEEP_MICROSECONDS 10

#include "SavedCommandsMacros.h" //?
#include <QWaitCondition>


namespace CppBikes
{

	class SavedCommand
	{
	public:
		virtual ~SavedCommand(){}
		virtual void exec()=0;
	};

	

	template<class RT>	class SavedCommandFunctor:	public Loki::Functor<RT>, public SavedCommand
	{
	public:
		
		SavedCommandFunctor(const Loki::Functor<RT> &fu):Loki::Functor<RT>(fu){}
		void operator = (const Loki::Functor<RT> &fu){ Loki::Functor<RT>::operator =(fu);}

		~SavedCommandFunctor(){}

		void exec()
		{
			(*this)();
		}
	};

	


	class SavedCommandsQueue: public Queue<SavedCommand>
	{
	public:

		

		template<class RT> void takeCommandFunctor(const Loki::Functor<RT> &fu)
		{
			take(new SavedCommandFunctor<RT>(fu));
		}		
		template<class RT> void operator +=(const Loki::Functor<RT> &fu)
		{
			take(new SavedCommandFunctor<RT>(fu));
		}


		void execCommand() // не_безопасно в случае пустой очереди
		{
			head()->exec();
			erase();
		}

		int commandCount()
		{
			return size(); 
		}


	};




	template<class ThreadClass, class MutexClass>
	class SavedCommandsThread: private SavedCommandsQueue, private ThreadClass
	{
	public:


		SavedCommandsThread():stop_complete(false),stop_now(false),stop_clearAndRestart(false),completeMutex_lock(false)
		{

		}

		void takeCommand(SavedCommand *cmd)
		{
			queueMutex.lock();
			SavedCommandsQueue::take(cmd);
			queueMutex.unlock();
			runCondition.wakeAll();
		}


		void queueLock()
		{
// 			int i=0;
// 			while(!queueMutex.tryLock()) i++;
// 			if(i>0)
// 			{
 // 				int a=0;
// 			}
			queueMutex.lock();
		}
		void queueUnlock(){queueMutex.unlock();}

		template<class RT> void takeCommandFunctor(const Loki::Functor<RT> &fu)
		{
			queueMutex.lock();
			SavedCommandsQueue::take(new SavedCommandFunctor<RT>(fu));
			queueMutex.unlock();
			runCondition.wakeAll();
		}		
		template<class RT> void operator +=(const Loki::Functor<RT> &fu)
		{
			queueMutex.lock();
			SavedCommandsQueue::take(new SavedCommandFunctor<RT>(fu));
			queueMutex.unlock();
			runCondition.wakeAll();
		}

		
		void stopComplete(bool enbl=true)
		{
			stopMutex.lock();
			stop_complete=enbl;
			stop_now=false;
			stopMutex.unlock();
			runCondition.wakeAll();
		}

		void stopNow() 
		{
			stopMutex.lock();
			stop_complete=true;
			stop_now=true;
			stopMutex.unlock();
			ThreadClass::wait();
		}


		/**********************************************************************************************//**
		 * \fn	void SavedCommandsThread::startCommandsExec(bool clear_and_restart=false,
		 * 		bool stop_when_complete=false)
		 *
		 * \brief	Starts the commands execute.
		 *
		 * \author	Andrey Kostin
		 * \date	04.09.2012
		 *
		 * \param	clear_and_restart 	(optional) the clear and restart.
		 * \param	stop_when_complete	(optional) the stop when complete.
		 **************************************************************************************************/
		void startCommandsExec(bool clear_and_restart=false, bool stop_when_complete=false)
		{
			if(!ThreadClass::isRunning())
			{
				stop_complete=stop_when_complete;
				stop_now=false;
				stop_clearAndRestart=clear_and_restart;
				completeMutex_lock=false;
				ThreadClass::start();
			}else
			{
				stopMutex.lock();
				stop_now=false;
				stop_complete=stop_when_complete;
				stop_clearAndRestart=clear_and_restart;
				stopMutex.unlock();
				runCondition.wakeAll();
			}
		}

		bool isAllCommandsExec() // все команды исполнены?
		{
			if(ThreadClass::isRunning())
			{
				queueMutex.lock();
				bool r=SavedCommandsQueue::isEmpty();
				queueMutex.unlock();
				return r;
			}
			return SavedCommandsQueue::isEmpty();
		}
		
		bool isProcessing() // идет исполнение команд?
		{
			if(ThreadClass::isRunning())
			{
				queueMutex.lock();
				bool r=SavedCommandsQueue::isEmpty();
				queueMutex.unlock();
				return !r;
			}
			return false;
		}
		
		void clearAndRestart() // очищает очередь, возвращает управление после очистки
		{			
			QMutex mu;
			mu.lock();
			startCommandsExec(true);			
			completeCondition.wait(&mu);
			mu.unlock();

			//if(!ThreadClass::isRunning()) startCommandsExec();
		}
		
		void waitForComplete() // возвращает управление после того как все команды будут исполнены или поток будет остановлен
		{  
			QMutex mu;
			mu.lock();
			typedef SavedCommandsThread<ThreadClass,MutexClass> t;
			//takeCommandFunctor(SCMD_FUNCTOR_0(t,*this,completeFunc));			
			queueMutex.lock();
			SavedCommandsQueue::take(new SavedCommandFunctor<void>(SCMD_FUNCTOR_0(t,*this,completeFunc)));
			queueMutex.unlock();
			//runCondition.wakeAll();
			completeCondition.wait(&mu);
			mu.unlock();
			//completeMutex.lock();
			//completeMutex.unlock();
		}
		void completeFunc()
		{
			//completeMutexUnlock();
			completeCondition.wakeAll();			
		}

	private:

		void run()
		{
			//completeMutexLock();
			queueMutex.lock();
			int cc=SavedCommandsQueue::commandCount();
			queueMutex.unlock();

			while(true)
			{
				stopMutex.lock();
				bool _stop_complete=stop_complete;
				bool _stop_now=stop_now;
				bool _stop_clearAndRestart=stop_clearAndRestart;
				stop_clearAndRestart=false;
				stopMutex.unlock();

				if(_stop_now) break;
				
				if(_stop_clearAndRestart)
				{					
					queueMutex.lock();
					SavedCommandsQueue::clear();
					queueMutex.unlock();
					completeCondition.wakeAll();
					//completeMutexUnlock();//?
					//completeMutexLock();
					cc=0;
					continue;
				}

				if(cc==0)
				{
					//completeMutexUnlock();
					if(_stop_complete) break;
					else
					{

// #ifdef SCMD_THREADSLEEP_MICROSECONDS
// 						ThreadClass::usleep(SCMD_THREADSLEEP_MICROSECONDS); //?
// #endif
						
// 						QMutex mu;mu.lock();
// 						runCondition.wait(&mu,SCMD_THREADSLEEP_MICROSECONDS);
// 						mu.unlock();

						queueMutex.lock();
						cc=SavedCommandsQueue::commandCount();
						queueMutex.unlock();
						continue;
					}
				}
				
				//completeMutexLock();
				for(int i=0; i<cc-1; i++) execCommand();
				queueMutex.lock();
				execCommand();
				//completeMutexLock();
				cc=SavedCommandsQueue::commandCount();
				queueMutex.unlock();
			}
			//completeMutexUnlock();
		}


		QWaitCondition completeCondition;
		QWaitCondition runCondition;

		MutexClass queueMutex;
		MutexClass stopMutex;		
		bool stop_complete;
		bool stop_now;
		bool stop_clearAndRestart;
		
		MutexClass completeMutex;
		bool completeMutex_lock;
		void completeMutexLock()
		{
			if(!completeMutex_lock) completeMutex.lock();
			completeMutex_lock=true;
		}
		void completeMutexUnlock()
		{
			if(completeMutex_lock) completeMutex.unlock();
			completeMutex_lock=false;
		}


		
	};
	
	
}



#endif
