#if !defined( LOGCTRL_H_INCLUDED )
#define LOGCTRL_H_INCLUDED

#pragma once

/****************************************************************************

                                  LogCtrl.h

						Copyright 2000, John J. Bolton
	----------------------------------------------------------------------

	$Header: //depot/SocketSniffer/LogCtrl.h#2 $

	$NoKeywords: $

****************************************************************************/


/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

class LogCtrl : public CRichEditCtrl
{
// Construction
public:
	LogCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(LogCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	void Append( LPCTSTR text, DWORD effect = 0, COLORREF color = -1 );
	void AppendLine( LPCTSTR text, DWORD effect = 0, COLORREF color = -1 );

	void ClearAll();
	virtual ~LogCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(LogCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.


#endif // !defined( LOGCTRL_H_INCLUDED )
