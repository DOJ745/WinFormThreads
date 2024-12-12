#include "StdAfx.h"
#include "MyController.h"

void MyController::ThreadFunction(Object^ param) 
{
	ThreadParams params = safe_cast<ThreadParams>(param);

	Debug::WriteLine("����� ����� ������ � �������: {0}", params.data);
	int temp = 0;
	while (!m_ThreadManager->ShouldStop() && temp <= 5) 
	{
		temp++;
		Thread::Sleep(1000); // �������� ������
		Debug::WriteLine("����� �������� � ������: {0} {1} ������...", params.data, temp);
	}

	Debug::WriteLine("����� �������� ��� ����������");
}