#include "ProcessList.h"

BOOL CALLBACK EnumWidnowsProc(HWND hwnd, LPARAM lparam);

ProcessList::ProcessList()
{
}


ProcessList::~ProcessList()
{
}


BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	if (!IsWindowVisible(hwnd)) {
		return TRUE;
	}

	const int MAX__PROCESS_NAME_LENGHT = 80;
	TCHAR processName[MAX__PROCESS_NAME_LENGHT];

	if (GetWindowText(hwnd, processName, MAX__PROCESS_NAME_LENGHT) == 0)
	{
		return TRUE;
	}

	DWORD pid = 0;

	if (GetWindowThreadProcessId(hwnd, &pid) == 0)
	{
		return TRUE;
	}

	ProcessInfo p;
	p.setProcessPid(pid);
	p.setProcessName(processName);
	vector<ProcessInfo> *processes = (vector<ProcessInfo>*) lParam;
	processes->push_back(p);

	return TRUE;
}


vector<ProcessInfo> *ProcessList::getProcesses()
{
	if (m_processes.size() > 0) {
		m_processes.clear();
	}

	auto currentThreadId = GetCurrentThreadId();
	auto desktopHandle = GetThreadDesktop(currentThreadId);

	EnumDesktopWindows(desktopHandle, EnumWindowsProc, (LPARAM)&m_processes);

	return &m_processes;
}