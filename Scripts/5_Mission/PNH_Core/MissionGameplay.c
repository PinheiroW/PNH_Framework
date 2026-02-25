/*
    MOD: PNH_Core
    FILE: MissionGameplay.c
    DESC: Hook do cliente para receber notificações via rede.
*/

modded class MissionGameplay
{
    override void OnMissionStart()
    {
        super.OnMissionStart();
        
        // Regista o canal RPC 9991 para escutar notificações vindas do servidor
        if (PNH_RpcManager.Get())
        {
            PNH_RpcManager.Get().Register(9991, this, "HandlePnhNotification");
        }
        
        PNH_Logger.Log("Client", "MissionGameplay iniciado. Escutando RPC: 9991");
    }

    // Função que é disparada quando o servidor manda o RPC 9991
    void HandlePnhNotification(ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        Param2<string, string> data;
        if (!ctx.Read(data)) return;

        // Chama o nosso UiManager para mostrar a mensagem
        PNH_UiManager.Get().ShowNotification(data.param1, data.param2);
    }
}