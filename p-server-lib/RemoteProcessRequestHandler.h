#pragma once

#include "util/inttypes.h"
#include "thread/AutoLock.h"
#include "network/RfbInputGate.h"
#include "network/RfbOutputGate.h"
#include "rfb/VendorDefs.h"
#include "rfb-sconn/RfbCodeRegistrator.h"
#include "rfb-sconn/RfbDispatcherListener.h"
#include "log-writer/LogWriter.h"
#include "p-common/PMessage.h"

class RemoteProcessRequestHandler : public RfbDispatcherListener
{
public:
	RemoteProcessRequestHandler(RfbCodeRegistrator *registrator,
		RfbOutputGate *output,
		LogWriter *log);
	~RemoteProcessRequestHandler();
	virtual void onRequest(UINT32 reqCode, RfbInputGate *backGate);

private:
	void processListRequested(RfbInputGate *backGate);
	void lastRequestFailed(RfbInputGate *backGate, const TCHAR* msg);

	RfbCodeRegistrator *m_registrator;
	RfbOutputGate *m_output;
	LogWriter *m_log;
};

