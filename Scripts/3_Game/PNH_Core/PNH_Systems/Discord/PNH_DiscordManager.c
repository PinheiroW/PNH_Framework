/*
    MOD: PNH_Core
    FILE: PNH_DiscordManager.c
    DESC: Sistema centralizado para envio de mensagens para o Discord.
*/

class PNH_DiscordManager
{
    private static ref PNH_DiscordManager m_Instance;

    void PNH_DiscordManager()
    {
        PNH_Logger.Log("Discord", "Gestor de Discord Inicializado.");
    }

    static PNH_DiscordManager Get()
    {
        if (!m_Instance)
        {
            m_Instance = new PNH_DiscordManager();
        }
        return m_Instance;
    }

    // =============================================================
    // FUNÇÃO PRINCIPAL DE ENVIO
    // =============================================================
    /**
     * @brief Envia mensagem para o Discord.
     * @param message: O texto da mensagem.
     * @param type: O tipo de canal ("System", "Admin", "Chat", "Login", "Kill", "Mission").
     */
    void Send(string message, string type = "System")
    {
        string url = "";
        PNH_CoreSettings settings = PNH_CoreConfig.Get();

        // 1. Seleciona a Webhook correta baseada no tipo
        if (type == "System")       url = settings.SystemWebhookURL;
        else if (type == "Admin")   url = settings.AdminWebhookURL;
        else if (type == "Chat")    url = settings.ChatWebhookURL;
        else if (type == "Login")   url = settings.LoginWebhookURL;
        else if (type == "Mission") url = settings.MissionsWebhookURL;
        else                        url = settings.SystemWebhookURL; // Fallback

        // Se não tiver URL configurada, cancela (evita erros no log)
        if (url == "") return;

        // 2. Prepara o JSON para o Discord
        // Nota: O Discord exige um formato JSON específico {"content": "mensagem"}
        string json = "{\"content\": \"" + message + "\"}";

        // 3. Envia o Request
        RestContext ctx = GetRestApi().GetRestContext(url);
        ctx.SetHeader("application/json");
        ctx.POST(null, "", json);
    }
    
    // Atalho estático para facilitar o uso em outros mods
    static void SendMessage(string msg, string channel)
    {
        Get().Send(msg, channel);
    }
}