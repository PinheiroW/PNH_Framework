/**
 * MOD: PNH_Core
 * FILE: PNH_ChatController.c
 */

modded class MissionGameplay
{
    ref PNH_RadioMenu m_RadioMenu;

    void OpenRadioSafe()
    {
        if (!m_RadioMenu) m_RadioMenu = new PNH_RadioMenu;
        if (GetGame().GetUIManager().GetMenu() != m_RadioMenu)
        {
            GetGame().GetUIManager().ShowScriptedMenu(m_RadioMenu, NULL);
        }
    }

    override void OnEvent(EventType eventTypeId, Param params)
    {
        if (eventTypeId == ChatMessageEventTypeID)
        {
            ChatMessageEventParams chatParams = ChatMessageEventParams.Cast(params);
            if (chatParams)
            {
                string text = chatParams.param3;
                
                // COMANDO DA UI
                if (text == "!radio")
                {
                    GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(OpenRadioSafe, 200);
                    return;
                }

                // COMANDOS DE ADMIN (Adicionado !stress aqui)
                if (text == "!debug" || text == "!reload" || text == "!stress")
                {
                    PNH_RpcManager.Get().SendRPC(9993, new Param1<string>(text));
                    return; 
                }

                // RADIO GLOBAL (.g)
                if (text.Length() > 3 && text.Substring(0, 2) == ".g")
                {
                    string msg = text.Substring(3, text.Length() - 3);
                    PNH_RpcManager.Get().SendRPC(9992, new Param1<string>(msg));
                    return;
                }
            }
        }
        super.OnEvent(eventTypeId, params);
    }
}