/**
 * MOD: PNH_Core
 * FILE: PNH_PlayerUtils.c
 */

class PNH_PlayerUtils
{
    // Verifica se o ID do jogador consta na lista de SuperAdmins do JSON
    static bool IsAdminIdentity(PlayerIdentity identity)
    {
        if (!identity) return false;
        
        string sId = identity.GetPlainId();
        ref array<string> admins = PNH_CoreConfig.Get().SuperAdmins;
        
        if (admins && admins.Find(sId) != -1)
        {
            return true;
        }
        
        return false;
    }

    // Envia uma notificação centralizada para o jogador
    static void NotifyPlayer(PlayerBase player, string message)
    {
        if (player) 
            player.MessageStatus(message);
    }
}