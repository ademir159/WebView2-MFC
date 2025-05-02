#pragma once

#include "stdafx.h"
#include <wrl.h>
#include <include/wil/com.h>
#include <include/WebView2.h>

class CWebView2Ctrl : public CWnd
{
public:
	CWebView2Ctrl();
	virtual ~CWebView2Ctrl();

	BOOL CreateWebView2Ctrl(CWnd* pParentWnd, UINT nID);


	void Navigate(CString strURL);

protected:
	Microsoft::WRL::ComPtr<ICoreWebView2> m_webview;
	Microsoft::WRL::ComPtr<ICoreWebView2Controller> m_controller;
	Microsoft::WRL::ComPtr<ICoreWebView2Environment> m_environment;

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);


	DECLARE_MESSAGE_MAP()

private:
	CString m_pendingUrl;
	bool m_isWebViewReady = false;

	void InitializeWebView();

	HRESULT OnCreateEnvironmentCompleted(HRESULT result, ICoreWebView2Environment* env);
	HRESULT OnCreateControllerCompleted(HRESULT result, ICoreWebView2Controller* controller);
};
