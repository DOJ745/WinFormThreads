#include "StdAfx.h"
#include "MyController.h"

void MyController::ThreadFunction(Object^ param) 
{
	ThreadParams params = safe_cast<ThreadParams>(param);

	Debug::WriteLine("Поток начал работу с данными: {0}", params.data);
	int temp = 0;
	while (!m_ThreadManager->ShouldStop() && temp <= 5) 
	{
		temp++;
		Thread::Sleep(1000); // Имитация работы
		Debug::WriteLine("Поток работает с числом: {0} {1} секунд...", params.data, temp);
	}

	Debug::WriteLine("Поток завершил своё выполнение");
}