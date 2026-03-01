/*
    MOD: PNH_Core
    FILE: PNH_BroadcastManager.c
    DESC: Envia mensagens automáticas baseadas no JSON de configuração.
*/

class PNH_BroadcastManager
{
    protected float m_Timer;
    protected int m_CurrentMsgIndex;

    void Update(float timeslice)
    {
        m_Timer += timeslice;

        float intervalSeconds = PNH_CoreConfig.Get().BroadcastIntervalMin * 60;
        
        if (m_Timer >= intervalSeconds)
        {
            m_Timer = 0;
            SendNextMessage();
        }
    }

    void SendNextMessage()
    {
        array<string> messages = PNH_CoreConfig.Get().BroadcastMessages;
        
        if (messages.Count() == 0) return;

        if (m_CurrentMsgIndex >= messages.Count())
            m_CurrentMsgIndex = 0;

        string msg = messages.Get(m_CurrentMsgIndex);
        
        // Envia para todos os jogadores online via Chat
        GetGame().ChatPlayer("[SERVER]: " + msg);
        
        PNH_Logger.Log("Broadcast", "Mensagem enviada: " + msg);
        m_CurrentMsgIndex++;
    }
}