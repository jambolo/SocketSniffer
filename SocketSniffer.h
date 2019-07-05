#if !defined( SOCKETSNIFFER_H_INCLUDED )
#define SOCKETSNIFFER_H_INCLUDED

#pragma once

/****************************************************************************

                               SocketSniffer.h

						Copyright 2000, John J. Bolton
	----------------------------------------------------------------------

	$Header: //depot/SocketSniffer/SocketSniffer.h#2 $

	$NoKeywords: $

****************************************************************************/

class TSocks5Server;


/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

class CSocketSnifferApp : public CWinApp
{
public:
	CSocketSnifferApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSocketSnifferApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL OnIdle(LONG lCount);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSocketSnifferApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	TSocks5Server * m_pSocks5Server;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.


#endif // !defined( SOCKETSNIFFER_H_INCLUDED )
