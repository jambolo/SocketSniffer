/****************************************************************************

                              SocketSniffer.cpp

						Copyright 2000, John J. Bolton
	----------------------------------------------------------------------

	$Header: //depot/SocketSniffer/SocketSniffer.cpp#2 $

	$NoKeywords: $

****************************************************************************/

#include "stdafx.h"

#include "SocketSniffer.h"

#include "SocketSnifferDlg.h"
#include "../Libraries/Socks5Server/Socks5Server.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

BEGIN_MESSAGE_MAP(CSocketSnifferApp, CWinApp)
	//{{AFX_MSG_MAP(CSocketSnifferApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()



/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

CSocketSnifferApp::CSocketSnifferApp()
	: m_pSocks5Server( 0 )
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}



/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

CSocketSnifferApp theApp;



/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

BOOL CSocketSnifferApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	AfxInitRichEdit();

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CSocketSnifferDlg dlg;
	m_pMainWnd = &dlg;

	m_pSocks5Server = new TSocks5Server( &dlg );
	if ( !m_pSocks5Server )
		throw std::bad_alloc();

	m_pSocks5Server->Initialize( 1080 );

	dlg.DoModal();

	delete m_pSocks5Server;

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}


/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

BOOL CSocketSnifferApp::OnIdle(LONG lCount) 
{
	// Server garbage collection
	m_pSocks5Server->OnIdle();

	return CWinApp::OnIdle(lCount);
}
