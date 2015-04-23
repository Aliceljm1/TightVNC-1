#include "ProcessDialog.h"

ProcessDialog::ProcessDialog(RemoteProcessCore* core)
	: BaseDialog(IDD_PROCESS), m_core(core)
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
	m_core->remoteProcessListOperation();
}