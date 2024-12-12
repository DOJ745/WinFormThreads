#include "StdAfx.h"
#include "ThreadManager.h"

void ThreadManager::Start(ThreadParams params, Action<Object^>^ threadFunc) 
{
	if (m_WorkerThread != nullptr && m_WorkerThread->IsAlive) 
	{
		Debug::WriteLine("����� ��� �������!");
		return;
	}

	m_ThreadFunction = threadFunc; // ��������� ���������� �������
	m_StopEvent->Reset();          // ���������� ������ ���������
	m_WorkerThread = gcnew Thread(gcnew ParameterizedThreadStart(this, &ThreadManager::RunThread));
	m_WorkerThread->Name = "Test Thread " + params.data;
	m_WorkerThread->Start(params);
}

void ThreadManager::Stop() 
{
	if (m_WorkerThread != nullptr && m_WorkerThread->IsAlive) 
	{
		m_StopEvent->Set(); // ������������� ������ ���������
		m_WorkerThread->Join(); // ������� ���������� ������
		Debug::WriteLine("����� ������� ���������� �� ������.");
	}
}

void ThreadManager::RunThread(Object^ param) 
{
	try 
	{
		// ����� ���������������� �������
		if (m_ThreadFunction != nullptr) 
		{
			m_ThreadFunction(param);
		}
	} 
	catch (ThreadAbortException^) 
	{
		Debug::WriteLine("����� ��� �������!");
	} 
	catch (Exception^ ex) 
	{
		Debug::WriteLine("������ � ������: {0}", ex->Message);
	}
	finally
	{
		OnThreadCompleted();
	}
}