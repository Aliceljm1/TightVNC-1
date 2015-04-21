#pragma once

class ProcessDialog : public BaseDialog
{
public:
	ProcessDialog(RemoteViewerCore& remoteViewer);
protected:
	virtual BOOL onCommand(UINT controlID, UINT notificationID);

private:
	void onRefreshProcessList();

	RemoteViewerCore& m_remoteViewer;
};

