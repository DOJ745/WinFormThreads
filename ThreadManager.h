#pragma once
#include "IThreadMethods.h"
#include "ThreadParams.h"

using namespace System;
using namespace System::Threading;
using namespace System::Diagnostics;

public ref class ThreadManager : public IThreadMethods
{
public:
	EventHandler^ m_ThreadCompleted; // ������� � ���������� ���������� ������

private:
	Thread^ m_WorkerThread;
	ManualResetEvent^ m_StopEvent;		// ������� ��� ��������� ������
	Action<Object^>^ m_ThreadFunction;	// ������� ��� ������� ������

public:
	ThreadManager(): m_StopEvent(gcnew ManualResetEvent(false)) {};

	~ThreadManager()
	{
		Stop();
	}

	bool ShouldStop() 
	{
		return m_StopEvent->WaitOne(0); // ���������, ���������� �� ������
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

