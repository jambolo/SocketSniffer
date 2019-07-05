#if !defined( SOCKETSNIFFERDLG_H_INCLUDED )
#define SOCKETSNIFFERDLG_H_INCLUDED

#pragma once

/****************************************************************************

                              SocketSnifferDlg.h

						Copyright 2000, John J. Bolton
	----------------------------------------------------------------------

	$Header: //depot/SocketSniffer/SocketSnifferDlg.h#2 $

	$NoKeywords: $

****************************************************************************/

#include "../Libraries/Socks5Server/Socks5ServerClient.h"
#include "resource.h"
#include "LogCtrl.h"


class TSocket;
struct in_addr;

/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

class CSocketSnifferDlg : public CDialog, public TSocks5ServerClient
{
// Construction
public:
	CSocketSnifferDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CSocketSnifferDlg();

	// Overrides TSocks5ServerClient
	virtual void OnAccept( TSocket const & socket );
	virtual void OnClose( TSocket const & socket );
	virtual void OnConnectRequest( TSocket const & socket, in_addr const & ip, int port );
	virtual void OnBindRequest( TSocket const & socket, in_addr const & ip, int port );
	virtual void OnConvey( TSocket const & socket, char const * data, int length );

// Dialog Data
	//{{AFX_DATA(CSocketSnifferDlg)
	enum { IDD = IDD_SOCKETSNIFFER_DIALOG };
	TLogCtrl	m_Log;
	CString		m_Status;
	int			m_DisplayStyle;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSocketSnifferDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSocketSnifferDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClearLog();
	afx_msg void OnSaveLog();
	afx_msg void OnDisplayStyle();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:

	enum TDisplayStyle
	{
		DISPLAY_HEX,
		DISPLAY_TEXT,
		DISPLAY_NAPSTER
	};

	void UpdateStatus( CString const & status );
	void PrefixLine( CString const & ip, int port );
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.


#endif // !defined( SOCKETSNIFFERDLG_H_INCLUDED )
