#pragma once
#include "ThreadParams.h"

public interface class IThreadMethods
{
public:
	void Start(ThreadParams params, System::Action<Object^>^ threadFunc, System::String^ threadName);
	void Stop();
};

