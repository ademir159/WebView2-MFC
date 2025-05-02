#include "stdafx.h"
#include "CWebView2Ctrl.h"

using namespace Microsoft::WRL;

BEGIN_MESSAGE_MAP(CWebView2Ctrl, CWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

CWebView2Ctrl::CWebView2Ctrl() {}
CWebView2Ctrl::~CWebView2Ctrl() {}

BOOL CWebView2Ctrl::CreateWebView2Ctrl(CWnd* pParentWnd, UINT nID)
{
	CRect rect;
	pParentWnd->GetDlgItem(nID)->GetWindowRect(&rect);
	pParentWnd->ScreenToClient(&rect);

	return Create(NULL, NULL, WS_CHILD | WS_VISIBLE, rect, pParentWnd, nID);
}

int CWebView2Ctrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	InitializeWebView();
	return 0;
}

void CWebView2Ctrl::InitializeWebView()
{
	HRESULT hr = CreateCoreWebView2EnvironmentWithOptions(
		nullptr, nullptr, nullptr,
		Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(
			[this](HRESULT result, ICoreWebView2Environment* env) -> HRESULT {
		return this->OnCreateEnvironmentCompleted(result, env);
	}).Get());

	if (FAILED(hr))
	{
		AfxMessageBox(_T("Erro ao iniciar WebView2"));
	}
}

HRESULT CWebView2Ctrl::OnCreateEnvironmentCompleted(HRESULT result, ICoreWebView2Environment* env)
{
	if (FAILED(result)) return result;

	m_environment = env;

	return env->CreateCoreWebView2Controller(
		this->GetSafeHwnd(),
		Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>(
			[this](HRESULT result, ICoreWebView2Controller* controller) -> HRESULT {
		return this->OnCreateControllerCompleted(result, controller);
	}).Get()
		);
}

HRESULT CWebView2Ctrl::OnCreateControllerCompleted(HRESULT result, ICoreWebView2Controller* controller)
{
	if (FAILED(result)) return result;

	m_controller = controller;
	controller->get_CoreWebView2(&m_webview);

	CRect rect;
	GetClientRect(&rect);
	controller->put_Bounds(rect);

	m_isWebViewReady = true;

	if (!m_pendingUrl.IsEmpty()) {
		m_webview->Navigate(m_pendingUrl.AllocSysString());
		m_pendingUrl.Empty();
	}

	return S_OK;
}

void CWebView2Ctrl::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	if (m_controller)
	{
		RECT bounds = { 0, 0, cx, cy };
		m_controller->put_Bounds(bounds);
	}
}

void CWebView2Ctrl::Navigate(CString strURL)
{
	if (m_isWebViewReady && m_webview) {
		m_webview->Navigate(strURL.AllocSysString());
	}
	else {
		m_pendingUrl = strURL;
	}
}


