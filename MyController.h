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

	virtual ~MyController() 
	{
		StopThread();
	};

	void StartThread(Action<Object^>^ function) 
	{
		ThreadParams params;
		params.data = m_Number;
		m_ThreadManager->Start(params, function);
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

