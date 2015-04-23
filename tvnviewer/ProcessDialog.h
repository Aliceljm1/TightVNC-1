#pragma once

#include "gui/BaseDialog.h"
#include "resource.h"
#include "p-client-lib/RemoteProcessCore.h"

class ProcessDialog : public BaseDialog
{
public:
	ProcessDialog(RemoteProcessCore *core);
protected:
	virtual BOOL onCommand(UINT controlID, UINT notificationID);

private:
	void onRefreshProcessList();

	RemoteProcessCore *m_core;
};

