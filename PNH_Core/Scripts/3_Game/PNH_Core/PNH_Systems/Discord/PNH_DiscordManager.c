/*
    MOD: PNH_Core
    FILE: PNH_DiscordManager.c
    DESC: Sistema centralizado para envio de mensagens com fila (Queue) para evitar Rate Limit.
*/

class PNH_DiscordManager
{
    private static ref PNH_DiscordManager m_Instance;
    
    // Arrays que atuarão como a nossa fila de envios
    private ref array<string> m_UrlQueue;
    private ref array<string> m_PayloadQueue;

    void PNH_DiscordManager()
    {
        m_UrlQueue = new array<string>;
        m_PayloadQueue = new array<string>;
        
        // Cria um loop assíncrono que roda a função ProcessQueue a cada 1500ms
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(ProcessQueue, 1500, true);
        
        PNH_Logger.Log("Discord", "Gestor de Discord Inicializado (Com Fila Ativa).");
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
    // FUNÇÃO PRINCIPAL DE ENVIO (AGORA VAI PARA A FILA)
    // =============================================================
    /**
     * @brief Adiciona mensagem na fila para o Discord.
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

        if (url == "") return;

        // 2. Prepara o JSON para o Discord
        string json = "{\"content\": \"" + message + "\"}";

        // 3. Adiciona à fila em vez de enviar instantaneamente
        m_UrlQueue.Insert(url);
        m_PayloadQueue.Insert(json);
    }
    
    // =============================================================
    // PROCESSADOR DA FILA
    // =============================================================
    /**
     * @brief Processa um item da fila a cada ciclo (chamado pelo CallLater).
     */
    void ProcessQueue()
    {
        if (m_UrlQueue.Count() > 0)
        {
            // Pega o primeiro da fila
            string url = m_UrlQueue.Get(0);
            string json = m_PayloadQueue.Get(0);

            // Envia o Request
            RestContext ctx = GetRestApi().GetRestContext(url);
            ctx.SetHeader("application/json");
            ctx.POST(null, "", json);

            // Remove o item já processado da fila para o próximo assumir o índice 0
            m_UrlQueue.Remove(0);
            m_PayloadQueue.Remove(0);
        }
    }
    
    // Atalho estático para facilitar o uso em outros mods
    static void SendMessage(string msg, string channel)
    {
        Get().Send(msg, channel);
    }
}