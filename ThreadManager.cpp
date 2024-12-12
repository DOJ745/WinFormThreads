#include "StdAfx.h"
#include "ThreadManager.h"

void ThreadManager::Start(ThreadParams params, Action<Object^>^ threadFunc) 
{
	if (m_WorkerThread != nullptr && m_WorkerThread->IsAlive) 
	{
		Debug::WriteLine("Поток уже запущен!");
		return;
	}

	m_ThreadFunction = threadFunc; // Сохраняем переданную функцию
	m_StopEvent->Reset();          // Сбрасываем сигнал остановки
	m_WorkerThread = gcnew Thread(gcnew ParameterizedThreadStart(this, &ThreadManager::RunThread));
	m_WorkerThread->Name = "Test Thread " + params.data;
	m_WorkerThread->Start(params);
}

void ThreadManager::Stop() 
{
	if (m_WorkerThread != nullptr && m_WorkerThread->IsAlive) 
	{
		m_StopEvent->Set(); // Устанавливаем сигнал остановки
		m_WorkerThread->Join(); // Ожидаем завершения потока
		Debug::WriteLine("Поток успешно остановлен по кнопке.");
	}
}

void ThreadManager::RunThread(Object^ param) 
{
	try 
	{
		// Вызов пользовательской функции
		if (m_ThreadFunction != nullptr) 
		{
			m_ThreadFunction(param);
		}
	} 
	catch (ThreadAbortException^) 
	{
		Debug::WriteLine("Поток был прерван!");
	} 
	catch (Exception^ ex) 
	{
		Debug::WriteLine("Ошибка в потоке: {0}", ex->Message);
	}
	finally
	{
		OnThreadCompleted();
	}
}