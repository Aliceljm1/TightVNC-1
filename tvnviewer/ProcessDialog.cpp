#include "gui/BaseDialog.h"
#include "viewer-core/RemoteViewerCore.h"
#include "ProcessDialog.h"
#include "resource.h"

ProcessDialog::ProcessDialog(RemoteViewerCore& remoteViewer) : BaseDialog(IDD_PROCESS), m_remoteViewer(remoteViewer)
{
}

BOOL ProcessDialog::onCommand(UINT controlID, UINT notificationID)
{
	switch (controlID) {
	case IDC_REFRESH_PROCESS_BUTTON:
		onRefreshProcessList();
		return FALSE;
	case IDOK:
		kill(1);
		return TRUE;
	case IDCANCEL:
		kill(0);
		return TRUE;
	default:
		return FALSE;
	}
}

void ProcessDialog::onRefreshProcessList() {
	m_remoteViewer.sendGetProcessListRequest();
}