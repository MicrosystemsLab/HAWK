#pragma once
#include <afxcoll.h>
#include "afxwin.h"

/* This class allows other classes to receive messages from STM.  To use the class, inherit from it and then
overload the stubs below.  The default behavior for any unhandled messages is to do nothing.*/

class STMDispatch
{
public:
	STMDispatch(void);
	~STMDispatch(void);
	//Overload to detect when a connection is available
	virtual void OnConnect();
	//Overload to detect when a connection is closed
	virtual void OnClose();
	//Overload to determine when meta data has been received, not safe to send before this
	virtual void OnMetaData();
	//Usually no need to overload this (use OnNewData), but included for completeness
	virtual void OnReceive();
	//Usually no need to overload this, but included for completeness
	virtual void OnSend();
	//Overload to react to errors
	virtual void OnError(int error);
	//Overload to receive STM messages
	virtual void OnNewData(CString MetaName, CByteArray* MsgData);
};
