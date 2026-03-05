/**
 * MOD: PNH_Core
 * FILE: PNH_ChatController.c
 */

modded class MissionGameplay
{
    override void OnEvent(EventType eventTypeId, Param params)
    {
        if (eventTypeId == ChatMessageEventTypeID)
        {
            ChatMessageEventParams chatParams = ChatMessageEventParams.Cast(params);
            if (chatParams)
            {
                string text = chatParams.param3;

                // COMANDOS DE ADMIN (Segurança: Comando !stress removido)
                if (text == "!debug" || text == "!reload")
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