#include "ProcessDialog.h"

ProcessDialog::ProcessDialog(RemoteProcessCore* core)
	: BaseDialog(IDD_PROCESS), m_core(core)
{
}


ProcessDialog::~ProcessDialog() { }


BOOL ProcessDialog::onCommand(UINT controlID, UINT notificationID)
{
	switch (controlID) {
	case IDC_REFRESH_PROCESS_BUTTON:
		onRefreshButtonClick();
		break;
	case IDOK:
		onOkButtonClick();
		break;
	case IDCANCEL:
		onCancelButtonClick();
		break;
	default:
		return FALSE;
	}

	return TRUE;
}


void ProcessDialog::onOpStarted()
{
	enableControls(FALSE);
}


void ProcessDialog::enableControls(BOOL enabled)
{
	m_refreshButton.setEnabled(enabled);
	m_processListView.setEnabled(enabled);
	m_cancelButton.setEnabled(!enabled);
}


void ProcessDialog::onOpFinished(State state, BOOL result)
{
	if (m_isClosing)
	{
		kill(IDOK);
		return;
	}

	enableControls(TRUE);
	m_core->onUpdateState(state, result);
}


BOOL ProcessDialog::onInitDialog()
{
	m_isClosing = FALSE;

	initControls();
	enableControls(TRUE);

	return TRUE;
}


void ProcessDialog::initControls()
{
	auto hwnd = m_ctrlThis.getWindow();

	m_refreshButton.setWindow(GetDlgItem(hwnd, IDC_REFRESH_PROCESS_BUTTON));
	m_processListView.setWindow(GetDlgItem(hwnd, IDC_REMOTE_PROCESS_LIST));

	m_cancelButton.setWindow(GetDlgItem(hwnd, IDC_CANCEL_BUTTON));
}


void ProcessDialog::raise(Exception &ex)
{
	MessageBox(m_ctrlThis.getWindow(), ex.getMessage(),
		_T("Exception"), MB_OK | MB_ICONERROR);
	throw ex;
}


void ProcessDialog::onRefreshButtonClick()
{
	refreshProcessList();
}


void ProcessDialog::onCancelButtonClick()
{
	tryClose();

	m_cancelButton.setEnabled(false);
}


void ProcessDialog::onOkButtonClick()
{
	m_isClosing = TRUE;

	auto selectedProcess = m_processListView.getSelectedProcessInfo();
	if (selectedProcess == nullptr)
	{
		onDetachProcess();
		return;
	}

	onAttachProcess(selectedProcess->getProcessPid());
}


BOOL ProcessDialog::tryClose()
{
	if (m_core->isIdle()) {
		kill(IDCANCEL);
		return TRUE;
	}

	auto response = MessageBox(m_ctrlThis.getWindow(),
		_T("Do you want to close remote process dialog and terminate current operation?"),
		_T("Remote Process Dialog"),
		MB_YESNO | MB_ICONQUESTION);

	if (response != IDYES) {
		m_isClosing = TRUE;
		m_core->terminateCurrentOperation();
		return TRUE;
	}

	return FALSE;
}


void ProcessDialog::setIdleState()
{
	m_processListView.clear();
	auto processList = m_core->getRemoteProcessList();
	ProcessInfo *processInfo = &processList->front();
	m_processListView.addRange(&processInfo, processList->size());
}


void ProcessDialog::refreshProcessList()
{
	m_core->remoteProcessListOperation();
}

void ProcessDialog::onRefreshProcessList()
{
	refreshProcessList();
}

void ProcessDialog::onDetachProcess()
{
	m_core->remoteProcessDetachOperation();
}

void ProcessDialog::onAttachProcess(DWORD pid)
{
	m_core->remoteProcessAttachOperation(pid);
}