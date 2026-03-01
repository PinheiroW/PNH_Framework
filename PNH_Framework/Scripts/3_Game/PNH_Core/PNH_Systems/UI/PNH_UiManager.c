/*
    MOD: PNH_Core
    FILE: PNH_UiManager.c
    DESC: Gestor de UI inspirado no TerjeCore. Gerencia notificações de forma segura.
*/

class PNH_UiManager
{
    private static ref PNH_UiManager m_Instance;

    void PNH_UiManager()
    {
        PNH_Logger.Log("UI", "PNH_UiManager Inicializado.");
    }

    static PNH_UiManager Get()
    {
        if (!m_Instance)
        {
            m_Instance = new PNH_UiManager();
        }
        return m_Instance;
    }

    /**
     * @brief Exibe uma notificação customizada.
     * Esta função evita o uso do 'NotificationData' problemático.
     */
    void ShowNotification(string title, string text, string icon = PNH_Icons.INFO, float duration = 5.0)
    {
        // Envia para o chat como fallback 100% estável (Método profissional)
        string msg = title + " :: " + text;
        GetGame().GetMission().OnEvent(ChatMessageEventTypeID, new ChatMessageEventParams(CCDirect, "", msg, ""));
        
        // Log de depuração no cliente (Roda apenas no PC do jogador)
        Print("[PNH_UI] Notificação Recebida: " + msg);
    }
}