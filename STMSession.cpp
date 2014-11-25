#include "StdAfx.h"
#include "STMSession.h"
#include "STMDispatch.h"
#include "STM Convert.h"


STMSession::STMSession(void)
{
	if( AfxSocketInit() == FALSE)
	{ 
		AfxMessageBox("Sockets Could Not Be Initialized"); 
	}
}

STMSession::~STMSession(void)
{

}
int STMSession::Disconnect()
{
	if(!(CAsyncSocket::ShutDown(2)))
	{
		CAsyncSocket::Close();
		return CAsyncSocket::GetLastError();
	}
	else
	{
		CAsyncSocket::Close();
		return 0;
	}
}

int STMSession::Connect(CString IPAddress, int Port)
{
	int error = 0;
	/* Attempt to connect to TCP server... */
	if(!CAsyncSocket::Create())
		return CAsyncSocket::GetLastError();
	else if(!CAsyncSocket::Connect(IPAddress, Port))
	{
		error = CAsyncSocket::GetLastError();
		if (error == WSAEWOULDBLOCK)
			return 0;
		else
		{
			CAsyncSocket::Close();
			return error;
		}	
	}
	else
		return 0;
}
void STMSession::OnSend(int nErrorCode)
{
	if(nErrorCode)
	{
		m_pDis->OnError(nErrorCode);
	}
	else
	{
		m_pDis->OnSend();
	}
	CAsyncSocket::OnSend(nErrorCode);
}
void STMSession::OnClose(int nErrorCode)
{
	//delete m_metaData;
	if(nErrorCode)
	{
		m_pDis->OnError(nErrorCode);
	}
	else
	{
		m_pDis->OnClose();
	}
	CAsyncSocket::OnClose(nErrorCode);
}

int STMSession::SendMsg(CString msgMeta, CByteArray *msgData)
{
	unsigned short int id = 0;
	int found = 0, result = 0, size = 0;
	char flatInt[4];
	char flatUShort[2];
	CByteArray buffer;
	GetIDfromName(msgMeta, &id, &found);
	if(found)
	{
		buffer.SetSize(msgData->GetSize());
		CopyMemory(buffer.GetData(), msgData->GetData(), msgData->GetSize());
		ushortFlatten(&id, flatUShort);
		buffer.InsertAt(0, flatUShort[1]);
		buffer.InsertAt(0, flatUShort[0]);
		size = (int)(buffer.GetSize());
		intFlatten(&size, flatInt);
		buffer.InsertAt(0, flatInt[3]);
		buffer.InsertAt(0, flatInt[2]);
		buffer.InsertAt(0, flatInt[1]);
		buffer.InsertAt(0, flatInt[0]);

		result = CAsyncSocket::Send(buffer.GetData(), (int)buffer.GetSize());
		if(result == SOCKET_ERROR)
		{
			m_pDis->OnError(CAsyncSocket::GetLastError());
			return -1;
		}
		else if(result != (int)(buffer.GetSize()))
		{
			return -1;  //Not all data was sent
		}
		else
		{
			return result; // Number of bytes sent
		}
	}
	else
	{
		//Meta data wasn't found
		return -2;
	}
}

void STMSession::OnConnect(int nErrorCode)
{
	m_metaDefined = 0;
	if(nErrorCode)
	{
		m_pDis->OnError(nErrorCode);
	}
	else
	{
		m_pDis->OnConnect();
	}
	CAsyncSocket::OnConnect(nErrorCode); 
}
void STMSession::OnReceive(int nErrorCode)
{
	DWORD DataSize = 0;
	int DataRead = 0;
	CByteArray tempAry;

	if(nErrorCode)
	{
		m_pDis->OnError(nErrorCode);
	}
	else
	{
		if(!CAsyncSocket::IOCtl(FIONREAD, &DataSize))
		{
			m_pDis->OnError(CAsyncSocket::GetLastError());
		}
		else
		{
			tempAry.SetSize(DataSize);
			DataRead = Receive(tempAry.GetData(), DataSize);
			if (!DataRead)
			{
				//Disconnected
				m_pDis->OnError(1);
			}
			else if(DataRead == SOCKET_ERROR)
			{
				m_pDis->OnError(CAsyncSocket::GetLastError());
			}
			else if(DataRead != DataSize)
			{
				//Data is the wrong size
			}
			else
			{
				m_recvBuf.Append(tempAry);
				ProcessMsg();
			}
		}
		m_pDis->OnReceive();
	}
	CAsyncSocket::OnReceive(nErrorCode);
}

int STMSession::DecodeMeta(char* buffer)
{
	int MetaElementLen = 0, x;
	char *placeHolder = buffer;
	
	m_numMeta = intUnflatten(buffer);		// How many elements are in the Meta Data
	m_metaData = new CString[m_numMeta];	//Allocate memory for the Meta Data
	
	placeHolder = placeHolder + 4;				// placeHolder keeps track of where you are in receive buffer
	
	for(x = 0; x < m_numMeta; x++)
	{
		MetaElementLen = intUnflatten(placeHolder); //MetaElementLen is the length of the Meta Element about to be read 
		placeHolder = placeHolder + 4;		
		m_metaData[x] = CString(placeHolder, MetaElementLen);
		placeHolder = placeHolder+MetaElementLen;
	}
	m_metaDefined = 1;
	return 1;
}

int STMSession::ProcessMsg()
{
	int datasize = 0, metaindex = 0;
	while(m_recvBuf.GetCount() >= 4)
	{
		datasize = intUnflatten((char*)m_recvBuf.GetData());
		if(m_recvBuf.GetCount() >= datasize+4)
		{
			if(!m_metaDefined)
			{
				if(DecodeMeta((char*)(m_recvBuf.GetData()+4)))
				{
					m_recvBuf.RemoveAt(0, datasize+4);
				}
				m_pDis->OnMetaData();
			}
			else
			{
				metaindex = ushortUnflatten((char*)(m_recvBuf.GetData()+4));
				m_msgMeta = m_metaData[metaindex];
				m_msgData.SetSize(datasize-2);
				CopyMemory (m_msgData.GetData(), m_recvBuf.GetData()+6, datasize-2);
				m_recvBuf.RemoveAt(0, datasize+4);
				m_pDis->OnNewData(m_msgMeta, &m_msgData);
			}
		}
		else
		{
			return 0;
		}
	}
	return 0;	
}

void STMSession::SetDispatch(STMDispatch *pDis)
{
	m_pDis = pDis;
}


int STMSession::GetIDfromName(CString Name, unsigned short * MetaID, int *found)
{
	unsigned short x;
	
	*found=0;
	
	for (x=0; x<m_numMeta; x++)
	{
		if (Name == m_metaData[x])
		{
			*found=1;
			*MetaID=x;
		}
	}
	return 0;
}

