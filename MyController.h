#pragma once
#include "ThreadManager.h"

using namespace System::Diagnostics;

public ref class MyController
{
private:
	int m_Number;
	ThreadManager^ m_ThreadManager;

public:
	MyController(void): m_Number(0)
		, m_ThreadManager(gcnew ThreadManager())
	{};

	~MyController() 
	{
		StopThread();
	};

	void StartThread(Action<Object^>^ function, System::String^ threadName) 
	{
		ThreadParams params;
		params.data = m_Number;
		m_ThreadManager->Start(params, function, threadName);
	};

	void StopThread() 
	{
		m_ThreadManager->Stop();
	};

	void SetNumber(int newNumber) 
	{
		m_Number = newNumber;
	};

	int GetNumber() 
	{
		return m_Number;
	};

	ThreadManager^ GetThreadManager()
	{
		return m_ThreadManager;
	}

	void ThreadFunction(Object^ param);
};

