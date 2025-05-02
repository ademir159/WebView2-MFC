WebView2 Availability Checker (MFC)

Este projeto fornece uma forma simples de verificar se o WebView2 está disponível no sistema antes de inicializar o componente em um projeto MFC.

✅ Verificando Disponibilidade do WebView2

A função abaixo retorna true se o runtime do WebView2 estiver instalado e pronto para uso:

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

Antes de criar o controle WebView2, chame IsWebView2Available() para garantir que o runtime está disponível. Exemplo:

```cpp
if (IsWebView2Available())
{
    m_wndWebView2_2.Create(NULL, NULL, WS_CHILD | WS_VISIBLE, rcWebView, this, AFX_IDW_PANE_FIRST);
    m_wndWebView2_2.Navigate(szURL);
}
```

📦 Requisitos

- WebView2 Runtime instalado no sistema
- Projeto MFC em C++
- SDK do Microsoft.Web.WebView2
- Suporte a C++17 ou superior

🔗 Links úteis

Documentação oficial do WebView2 (Microsoft): https://learn.microsoft.com/en-us/microsoft-edge/webview2/
