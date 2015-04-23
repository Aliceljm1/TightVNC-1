#include "RemoteProcessOperationEventListener.h"


RemoteProcessOperationEventListener::RemoteProcessOperationEventListener() { }
RemoteProcessOperationEventListener::~RemoteProcessOperationEventListener() { }
void RemoteProcessOperationEventListener::onStarted(RemoteProcessOperation *operation) { }
void RemoteProcessOperationEventListener::onFinished(RemoteProcessOperation *operation) { }
void RemoteProcessOperationEventListener::onError(RemoteProcessOperation *operation, const TCHAR *msg) { }
void RemoteProcessOperationEventListener::onInfo(RemoteProcessOperation *operation, const TCHAR *msg) { }
