#pragma once

#include "p-common/ProcessInfo.h"
#include "gui/ListView.h"

class ProcessInfoListView : public ListView
{
public:
	ProcessInfoListView();
	~ProcessInfoListView();

	virtual void setWindow(HWND hwnd);
	void addItem(int index, ProcessInfo *processInfo);
	void addRange(ProcessInfo **processInfo, size_t count);
	ProcessInfo *getSelectedProcessInfo();
	void sort(int columnIndex);

private:
	static int CALLBACK compareItem(LPARAM lparam1, LPARAM lparam2, LPARAM lParamSort);
};

