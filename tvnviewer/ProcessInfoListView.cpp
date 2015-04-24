#include "ProcessInfoListView.h"


ProcessInfoListView::ProcessInfoListView()
{
	sort(1);
}


ProcessInfoListView::~ProcessInfoListView() { }


void ProcessInfoListView::setWindow(HWND hwnd)
{
	ListView::setWindow(hwnd);

	ListView::addColumn(0, _T("Name"), 200);
	ListView::addColumn(1, _T("PID"), 80, LVCFMT_RIGHT);

	ListView::setFullRowSelectStyle(true);
}


void ProcessInfoListView::addItem(int index, ProcessInfo *processInfo)
{
	const TCHAR *processName = processInfo->getProcessName();

	ListView::addItem(index, processName, (LPARAM) processInfo);

	StringStorage pidString;
	pidString.format(_T("%d"), processInfo->getProcessPid());
	ListView::setSubItemText(index, 1, pidString.getString());

	ListView::sort();
}


void ProcessInfoListView::addRange(ProcessInfo **processesInfo, size_t count)
{
	int listIndex = max(0, ListView::getCount() - 1);
	ProcessInfo *wrapProcesses = *processesInfo;
	for (auto i = 0; i < count; ++i)
	{
		ProcessInfo *p = &wrapProcesses[i];
		addItem(listIndex++, p);
	}

	ListView::sort();
}


ProcessInfo *ProcessInfoListView::getSelectedProcessInfo()
{
	auto index = ListView::getSelectedIndex();
	if (index == -1) {
		return nullptr;
	}

	auto rawItem = ListView::getSelectedItem();
	return reinterpret_cast<ProcessInfo*>(rawItem.tag);
}


void ProcessInfoListView::sort(int columnIndex)
{
	ListView::sort(columnIndex, compareItem);
}


int ProcessInfoListView::compareItem(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	auto descendingOrder = lParamSort < 0;
	if (descendingOrder)
	{
		lParamSort = abs(lParamSort);
		return compareItem(lParam2, lParam1, lParamSort);
	}

	auto firstItem = reinterpret_cast<ProcessInfo*>(lParam1);
	auto secondItem = reinterpret_cast<ProcessInfo*>(lParam2);
	auto sortColumn = lParamSort - 1;
	auto compare = 0;

	switch (sortColumn)
	{
	case 0:
		return _tcsicmp(firstItem->getProcessName(), secondItem->getProcessName());
	case 1:
		compare = firstItem->getProcessPid() - secondItem->getProcessPid();
		if (compare != 0)
		{
			return compare;
		}
		return compareItem(lParam1, lParam2, 1);
	default:
		_ASSERT(false);
		return 0;
	}
}