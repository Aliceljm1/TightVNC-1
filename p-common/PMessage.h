#pragma once

#include "util/inttypes.h"

class PMessage
{
public:
	const static char PROCESS_LIST_REQUEST_SIG[];
	const static char PROCESS_LIST_REPLY_SIG[];
	const static UINT32 PROCESS_LIST_REPLY = 0xBB000100;
	const static UINT32 PROCESS_LIST_REQUEST = 0xBB000101;

	const static char LAST_REQUEST_FAILED_REPLY_SIG[];
	const static UINT32 LAST_REQUEST_FAILED_REPLY = 0xBB000400;
};
