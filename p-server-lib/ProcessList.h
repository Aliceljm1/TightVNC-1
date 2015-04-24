#pragma once

#include "p-common/ProcessInfo.h"

using std::vector;

class ProcessList
{
public:
	ProcessList();
	~ProcessList();

	vector<ProcessInfo> *getProcesses();
private:
	vector<ProcessInfo> m_processes;
};

