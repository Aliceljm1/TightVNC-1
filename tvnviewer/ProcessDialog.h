#pragma once

class ProcessDialog : public BaseDialog
{
public:
	ProcessDialog();
protected:
	virtual BOOL onCommand(UINT controlID, UINT notificationID);
};

