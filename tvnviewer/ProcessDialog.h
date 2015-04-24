#pragma once

#include "gui/BaseDialog.h"
#include "resource.h"
#include "p-client-lib/RemoteProcessInterface.h"
#include "p-client-lib/RemoteProcessCore.h"
#include "ProcessInfoListView.h"

class ProcessDialog : public BaseDialog, public RemoteProcessInterface
{
public:
	ProcessDialog(RemoteProcessCore *core);

	// RemoteProcessInterface
	void setIdleState();
	void onRefreshProcessList();
	void onOpStarted();
	void onOpFinished(State state, BOOL result);
	void raise(Exception &ex);

protected:
	virtual BOOL onInitDialog();
	virtual BOOL onCommand(UINT controlID, UINT notificationID);

private:
	void onRefreshButtonClick();
	void onCancelButtonClick();
	void onOkButtonClick();

	void refreshProcessList();
	
	void initControls();
	void enableControls(BOOL enabled);

	BOOL m_isClosing;
	BOOL tryClose();

	Control m_refreshButton;
	Control m_cancelButton;
	ProcessInfoListView m_processListView;

	RemoteProcessCore *m_core;
};

