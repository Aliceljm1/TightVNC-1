#include "gui/BaseDialog.h"
#include "ProcessDialog.h"
#include "resource.h"

ProcessDialog::ProcessDialog() : BaseDialog(IDD_PROCESS)
{
}

BOOL ProcessDialog::onCommand(UINT controlID, UINT notificationID)
{
	switch (controlID) {
	case IDC_REFRESH_PROCESS_BUTTON:
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