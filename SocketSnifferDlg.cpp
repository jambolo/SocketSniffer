/****************************************************************************

                             SocketSnifferDlg.cpp

						Copyright 2000, John J. Bolton
	----------------------------------------------------------------------

	$Header: //depot/SocketSniffer/SocketSnifferDlg.cpp#2 $

	$NoKeywords: $

****************************************************************************/

#include "stdafx.h"

#include "SocketSnifferDlg.h"

#include "resource.h"
#include "../Libraries/Socket/Socket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static DWORD CALLBACK SaveLogCallback( DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb );


/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

CSocketSnifferDlg::CSocketSnifferDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSocketSnifferDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSocketSnifferDlg)
	m_Status = _T("");
	m_DisplayStyle = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}



/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

CSocketSnifferDlg::~CSocketSnifferDlg()
{
}



/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

void CSocketSnifferDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSocketSnifferDlg)
	DDX_Control(pDX, IDC_LOG, m_Log);
	DDX_Text(pDX, IDC_STATUS, m_Status);
	DDX_Radio(pDX, IDC_DISPLAY_STYLE_HEX, m_DisplayStyle);
	//}}AFX_DATA_MAP
}



/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

BEGIN_MESSAGE_MAP(CSocketSnifferDlg, CDialog)
	//{{AFX_MSG_MAP(CSocketSnifferDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CLEAR_LOG, OnClearLog)
	ON_BN_CLICKED(IDC_SAVE_LOG, OnSaveLog)
	ON_BN_CLICKED(IDC_DISPLAY_STYLE_HEX, OnDisplayStyle)
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_RADIO2, OnDisplayStyle)
	ON_BN_CLICKED(IDC_RADIO3, OnDisplayStyle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

BOOL CSocketSnifferDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// Set the log output to a fixed pitch font

	CHARFORMAT cf = { sizeof( CHARFORMAT ) };
	cf.dwMask = CFM_FACE;
	strcpy( cf.szFaceName, "Courier New" );
	m_Log.SetDefaultCharFormat( cf );

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}



/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSocketSnifferDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}



/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.

HCURSOR CSocketSnifferDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}




#if 0

/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

void CSocketSnifferDlg::OnSendToClient() 
{
	// Get the address and ports

	UpdateData( TRUE );

//	if ( m_pServerSocket )
//		m_pServerSocket->Send( LPCTSTR( m_Enter ), m_Enter.GetLength() );
}



/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

void CSocketSnifferDlg::OnSendToServer() 
{
	// Get the address and ports

	UpdateData( TRUE );

//	if ( m_pClientSocket )
//		m_pClientSocket->Send( LPCTSTR( m_Enter ), m_Enter.GetLength() );
}


#endif // 0



/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

void CSocketSnifferDlg::UpdateStatus( CString const & status)
{
	m_Status = "Status: ";
	m_Status += status;

	UpdateData( FALSE );
}



/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

namespace
{
	inline char itox( int i ) { return ( i <= 9 ) ? ( i + '0' ) : ( i - 10 + 'a' ); }
}


/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

void CSocketSnifferDlg::OnAccept( TSocket const & socket )
{
	CString ip;
	UINT port;
	const_cast< TSocket & >( socket ).GetPeerName( ip, port );
	PrefixLine( ip, port );

	m_Log.Append( CString( _T( "Accepted\r\n" ) ), CFE_BOLD );
}


/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

void CSocketSnifferDlg::OnClose( TSocket const & socket )
{
	CString ip;
	UINT port;
	const_cast< TSocket & >( socket ).GetPeerName( ip, port );
	PrefixLine( ip, port );

	m_Log.Append( CString( _T( "Closed\r\n" ) ), CFE_BOLD );
}


/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

void CSocketSnifferDlg::OnConnectRequest( TSocket const & socket, in_addr const & ip, int port )
{
	CString socket_ip;
	UINT socket_port;
	const_cast< TSocket & >( socket ).GetPeerName( socket_ip, socket_port );
	PrefixLine( socket_ip, socket_port );

	CString message;
	message.Format( _T( "Connect request - %d.%d.%d.%d:%d\r\n" ), ip.s_net, ip.s_host, ip.s_lh, ip.s_impno, port );

	m_Log.Append( message, CFE_BOLD );
}


/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

void CSocketSnifferDlg::OnBindRequest( TSocket const & socket, in_addr const & ip, int port )
{
	CString socket_ip;
	UINT socket_port;
	const_cast< TSocket & >( socket ).GetPeerName( socket_ip, socket_port );
	PrefixLine( socket_ip, socket_port );

	CString message;
	message.Format( _T( "Bind request - %d.%d.%d.%d:%d\r\n" ), ip.s_net, ip.s_host, ip.s_lh, ip.s_impno, port );

	m_Log.Append( message, CFE_BOLD );
}


/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

void CSocketSnifferDlg::OnConvey( TSocket const & socket, char const * data, int length )
{
	CString socket_ip;
	UINT socket_port;
	const_cast< TSocket & >( socket ).GetSockName( socket_ip, socket_port );

	switch ( m_DisplayStyle )
	{
	case DISPLAY_HEX:
	{

		// Display it in the log up to 16 bytes on a line

		int const max_line = 32;

		while ( length > 0 )
		{
			PrefixLine( socket_ip, socket_port );

			int const line_length = ( length > max_line ) ? max_line : length;
			CString line;

			for ( int i = 0; i < line_length; i++ )
			{
				line += itox( ( ( unsigned char ) data[i] ) / 16 );
				line += itox( ( ( unsigned char ) data[i] ) % 16 );
				line += ' ';
			}

			for ( i = line_length; i < max_line; i++ )
				line += _T( "   " );

			line += ' ';

			for ( i = 0; i < line_length; i++ )
				line += isprint( data[i] ) ? data[i] : '.';

			line += _T( "\r\n" );

			m_Log.Append( line );

			length -= line_length;
			data += line_length;
		}
		break;
	}

	case DISPLAY_TEXT:
	{
		PrefixLine( socket_ip, socket_port );

		CString message;

		for ( int i = 0; i < length; i++ )
		{
			if ( isprint(data[i] ) || isspace( data[i] ) )
			{
				message += data[i];
			}
			else
			{
				message += '%';
				message += itox( ( ( unsigned char ) data[i] ) / 16 );
				message += itox( ( ( unsigned char ) data[i] ) % 16 );
				message += '%';
			}
		}

		message += _T( "\r\n" );

		m_Log.Append( message );
		break;
	}

	case DISPLAY_NAPSTER:
	{
		static int continued_from_last_time = 0;	// Number of bytes left to display in the previous napster message
		static char header[4];						// Buffer for constructing the napster message header
		static int header_size = 0;					// Number of bytes already in the header buffer

		// This mess here extracts napster messages out of the the packet. Complications arise because
		// there can be less than one, one, or many napster messages per packet and they can also be
		// split between packets.

		while ( length > 0 )
		{
			int napster_message_length;

			// If this is not a continuation of the previous napster message, then get the header and the
			// size of the napster message from the header

			if ( continued_from_last_time <= 0 )
			{
				int const remaining_header_buffer_bytes = sizeof( header ) - header_size;

				// If there is enough data to fill the header, then fill it and display it and get the
				// napster message size

				if ( length >= remaining_header_buffer_bytes )
				{
					PrefixLine( socket_ip, socket_port );

					// Fill the header buffer

					memcpy( &header[ header_size ], data, remaining_header_buffer_bytes );

					// Get the size and type of the napster message

					napster_message_length = *reinterpret_cast< short const * >( &header[0] );
					int const napster_message_type =  *reinterpret_cast< short const * >( &header[2] );

					// Display the header

					CString header;
					header.Format( _T( "<%3d,%3d> " ), napster_message_length, napster_message_type );
					m_Log.Append( header, CFE_BOLD );

					length -= remaining_header_buffer_bytes;	// Less data
					data += remaining_header_buffer_bytes;		// Skip over header data
					header_size = 0;							// Header buffer is empty now that it has been displayed
				}
				else
				{
					// Fill the header buffer as much as possible

					memcpy( &header[ header_size ], data, length );
					header_size += length;
					length = 0;
					data += length;

					// The header is not complete so there is nothing to display -- just bail now to avoid
					// complication.

					break;			// Note: this breaks out of the while loop, not the switch
				}
			}

			// Otherwise, the size of the bytes in the napster message was saved the time before

			else
			{
				napster_message_length = continued_from_last_time;
			}

			// If this packet does not contain the entire napster message, then display what we have and
			// save for next time the number of bytes left.

			if ( napster_message_length > length )
			{
				continued_from_last_time = napster_message_length - length;	// This napster message is not complete
				napster_message_length = length;
			}
			else
			{
				continued_from_last_time = 0;	// This napster message is complete
			}

			CString message;

			for ( int i = 0; i < napster_message_length; i++ )
			{
				if ( isprint(data[i] ) || isspace( data[i] ) )
				{
					message += data[i];
				}
				else
				{
					message += '%';
					message += itox( ( ( unsigned char ) data[i] ) / 16 );
					message += itox( ( ( unsigned char ) data[i] ) % 16 );
					message += '%';
				}
			}

			// If the napster message is complete, then append a newline

			if ( continued_from_last_time <= 0 )
				message += _T( "\r\n" );

			m_Log.Append( message );

			length -= napster_message_length;
			data += napster_message_length;
		}
		break;
	}

	default:
		ASSERT( ( "Unhandled display type", false ) );
		break;
	}

}



/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

void CSocketSnifferDlg::OnClearLog() 
{
	m_Log.ClearAll();	
}



/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

void CSocketSnifferDlg::OnSaveLog() 
{
	// Get the log file

	CFileDialog file_dialog( FALSE, "rtf", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "*.rtf|*.rtf||" );
	int const rval = file_dialog.DoModal();
	if ( rval == IDCANCEL )
		return;

	CString const filename = file_dialog.GetPathName();

	// Open the file

	CFile file;
	if ( !file.Open( filename, CFile::modeCreate|CFile::modeWrite|CFile::shareExclusive ) )
	{
		AfxMessageBox( "Unable to open file for writing.", MB_OK );
		return;
	}

	// Output the log

	EDITSTREAM es = { (unsigned long)&file, 0, SaveLogCallback };
	m_Log.StreamOut( SF_RTF, es );

	// Close the file

	file.Close();
}



/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

void CSocketSnifferDlg::OnDisplayStyle() 
{
	UpdateData( TRUE );	
}


/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

void CSocketSnifferDlg::PrefixLine( CString const & ip, int port )
{
	CString prefix;
	prefix.Format( _T( "%15s:%-5d " ), LPCTSTR( ip ), port );

	m_Log.Append( prefix, 0, RGB( 255, 0, 0 ) );
}


/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

static DWORD CALLBACK SaveLogCallback( DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb )
{
	CFile * const file = reinterpret_cast< CFile * >( dwCookie );

	file->Write( pbBuff, cb );
	*pcb = cb;

	return 0;
}
