#pragma once
#include "IThreadMethods.h"
#include "ThreadParams.h"

using namespace System;
using namespace System::Threading;
using namespace System::Diagnostics;

public ref class ThreadManager : public	IThreadMethods
{
public:
	EventHandler^ m_ThreadCompleted;	// Событие о завершении выполнении потока

private:
	Thread^ m_WorkerThread;				// Объект для создания потока
	ManualResetEvent^ m_StopEvent;		// Событие для остановки потока
	Action<Object^>^ m_ThreadFunction;	// Делегат для функции потока
	String^ m_ThreadName;				// Имя потока

public:
	ThreadManager(): 
		m_StopEvent(gcnew ManualResetEvent(false))
		, m_ThreadName("My Thread")
	{};

	virtual ~ThreadManager()
	{
		Stop();
	}

	bool ShouldStop() 
	{
		return m_StopEvent->WaitOne(0); // Проверяем, установлен ли сигнал
	}

	virtual void Start(ThreadParams params, Action<Object^>^ threadFunc, System::String^ threadName);

	virtual void Stop();

private:
	virtual void RunThread(Object^ param);

	void OnThreadCompleted() 
	{
		if (m_ThreadCompleted != nullptr) 
		{
			m_ThreadCompleted(this, EventArgs::Empty);
		}
	};
};

