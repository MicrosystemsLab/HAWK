#include "StdAfx.h"
#include "STMDispatch.h"

STMDispatch::STMDispatch(void)
{
}
STMDispatch::~STMDispatch(void)
{
}
//Overload to detect when a connection is available
void STMDispatch::OnConnect()
{
}
//Overload to detect when a connection is closed
void STMDispatch::OnClose()
{
}
//Overload to determine when meta data has been received, not safe to send before this
void STMDispatch::OnMetaData()
{
}
//Usually no need to overload this (use OnNewData), but included for completeness
void STMDispatch::OnReceive()
{
}
//Usually no need to overload this, but included for completeness
void STMDispatch::OnSend()
{
}
//Overload to react to errors
void STMDispatch::OnError(int error)
{
}
//Overload to receive STM messages
void STMDispatch::OnNewData(CString MetaName, CByteArray* MsgData)
{
}