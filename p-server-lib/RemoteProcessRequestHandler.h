#pragma once

#include "util/inttypes.h"
#include "thread/AutoLock.h"
#include "network/RfbInputGate.h"
#include "network/RfbOutputGate.h"
#include "rfb/VendorDefs.h"
#include "rfb-sconn/RfbCodeRegistrator.h"
#include "rfb-sconn/RfbDispatcherListener.h"
#include "rfb-sconn/RfbClient.h"
#include "log-writer/LogWriter.h"
#include "p-common/PMessage.h"
#include "ProcessList.h"

class RemoteProcessRequestHandler : public RfbDispatcherListener
{
public:
	RemoteProcessRequestHandler(RfbCodeRegistrator *registrator,
		RfbOutputGate *output,
		Desktop *desktop,
		RfbClient *client,
		LogWriter *log);
	~RemoteProcessRequestHandler();
	virtual void onRequest(UINT32 reqCode, RfbInputGate *backGate);

private:
	void changeViewPort(ViewPortState *viewPort);
	void processListRequested(RfbInputGate *backGate);
	void processAttachRequested(RfbInputGate *backGate);
	void processDetachRequested(RfbInputGate *backGate);
	void lastRequestFailed(RfbInputGate *backGate, const TCHAR* msg);

	RfbCodeRegistrator *m_registrator;
	RfbClient *m_client;
	Desktop *m_desktop;
	RfbOutputGate *m_output;
	LogWriter *m_log;
};

