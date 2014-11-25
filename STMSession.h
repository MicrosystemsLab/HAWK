#pragma once
#include <afxsock.h>
#include "STMDispatch.h"

/* This class implements an STM client using TCP/IP.  As of this time, the class does not have the ability to
act as a server */
class STMSession : public CAsyncSocket
{
public:
	STMSession(void);
	~STMSession(void);
	int Connect(CString IPAddress, int Port);			//Call this function to establish a connection to a server.
	int Disconnect();									//Closes a session
	int SendMsg(CString msgMeta, CByteArray *msgData);	//Sends an STM message, there must be meta data available when
														//you call this function, so wait on the OnMetaData() callback
														//from STMDispatch before calling it.
	void SetDispatch(STMDispatch *pDis);				//Call this function to set the object to send messages to.
														//The object must inherit from STMDispatch, see STMDispatch.h
														//for more information.
	
	//Overloaded functions from CAsyncSocket, refer to the CAsyncSocket documentation for more information.
	void OnConnect(int nErrorCode);
	void OnReceive(int nErrorCode); 
	void OnSend(int nErrorCode);
	void OnClose(int nErrorCode);

private:
	STMDispatch *m_pDis;								//Pointer to the place to dispatch messages to
	CByteArray m_recvBuf;								//Buffer for incoming messages
	CByteArray m_msgData;								//Current message: data
	CString m_msgMeta;									//Current message: name
	CString *m_metaData;								//Meta data table
	int m_numMeta;										//Number of Meta Items
	int m_metaDefined;									//Keep track of whether we have meta data yet
	int ProcessMsg();									//Internal function to process a message
	int DecodeMeta(char* buffer);						//Internal function to process the meta data message
	int GetIDfromName(CString Name, unsigned short * MetaID, int *found);	//Maps a message id into a meta element
};
