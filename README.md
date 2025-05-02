WebView2 Control para MFC.

Este projeto fornece uma forma simples de utilizar o WebView2 dentro de projeto MFC, isso traz melhor utilização, pois em projetos mais antigos o sistema IE8 não fornecesse suporte a HTML5 e outras modernidades.

Projeto inicialmente desenvolvido para o "Patcher" do jogo Flyff, porém pode ser vinculado a qualquer aplicação MFC em C++.

✅ Verificando Disponibilidade do WebView2

```cpp
bool IsWebView2Available()
{
    Microsoft::WRL::ComPtr<ICoreWebView2Environment> dummyEnv;
    HRESULT hr = CreateCoreWebView2EnvironmentWithOptions(
        nullptr, nullptr, nullptr,
        Microsoft::WRL::Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(
            [](HRESULT result, ICoreWebView2Environment*) -> HRESULT {
                return S_OK;
            }).Get());

    return SUCCEEDED(hr);
}
```
🧪 Modo de uso

```cpp

CWebView2Ctrl	m_wndWebView2;

if (IsWebView2Available())
{
    m_wndWebView2.Create(NULL, NULL, WS_CHILD | WS_VISIBLE, rcWebView, this, AFX_IDW_PANE_FIRST);
    m_wndWebView2.Navigate(szURL);
}
```

📦 Requisitos

- WebView2 Runtime instalado no sistema
- Projeto MFC em C++
- SDK do Microsoft.Web.WebView2
- Suporte a C++17 ou superior

🔗 Links úteis

Documentação oficial do WebView2 (Microsoft): https://learn.microsoft.com/en-us/microsoft-edge/webview2/

