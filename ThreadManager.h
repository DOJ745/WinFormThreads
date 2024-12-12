#pragma once
#include "IThreadMethods.h"
#include "ThreadParams.h"

using namespace System;
using namespace System::Threading;
using namespace System::Diagnostics;

public ref class ThreadManager : public IThreadMethods
{
public:
	EventHandler^ m_ThreadCompleted; // Событие о завершении выполнении потока

private:
	Thread^ m_WorkerThread;
	ManualResetEvent^ m_StopEvent;		// Событие для остановки потока
	Action<Object^>^ m_ThreadFunction;	// Делегат для функции потока

public:
	ThreadManager(): m_StopEvent(gcnew ManualResetEvent(false)) {};

	~ThreadManager()
	{
		Stop();
	}

	bool ShouldStop() 
	{
		return m_StopEvent->WaitOne(0); // Проверяем, установлен ли сигнал
	}

	virtual void Start(ThreadParams params, Action<Object^>^ threadFunc);

	virtual void Stop();

	virtual void RunThread(Object^ param);

private:
	//virtual void RunThread(Object^ param);

	void OnThreadCompleted() 
	{
		if (m_ThreadCompleted != nullptr) 
		{
			m_ThreadCompleted(this, EventArgs::Empty);
		}
	};
};

