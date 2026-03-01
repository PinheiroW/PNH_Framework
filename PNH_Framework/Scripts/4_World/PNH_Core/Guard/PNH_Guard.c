/**
 * MOD: PNH_Core
 * MODULE: PNH_Guard
 */

class PNH_Guard
{
    private static ref map<string, EntityAI> m_TrackedIDs = new map<string, EntityAI>;

    static void CheckEntity(EntityAI entity)
    {
        if (!entity || !GetGame().IsServer()) return;
        if (!PNH_CoreConfig.Get().AntiDupeActive) return;

        string pID = GetIDString(entity);
        if (pID == "0_0_0_0") return;

        if (m_TrackedIDs.Contains(pID))
        {
            EntityAI existing = m_TrackedIDs.Get(pID);
            if (existing && existing != entity)
            {
                string playerName = "Ambiente";
                PlayerBase player = PlayerBase.Cast(entity.GetHierarchyRootPlayer());
                if (player && player.GetIdentity()) playerName = player.GetIdentity().GetName();

                TriggerDiscordAlert(playerName, entity.GetType(), pID);
                GetGame().ObjectDelete(entity);
                return;
            }
        }
        m_TrackedIDs.Insert(pID, entity);
    }

    static void TriggerDiscordAlert(string playerName, string itemType, string pID)
    {
        string webhook = PNH_CoreConfig.Get().AdminWebhookURL;
        
        // Verifica se o Webhook existe na configuração
        if (webhook == "" || webhook.Length() < 10)
        {
            PNH_Logger.Log("GUARD", "ERRO: Webhook de Admin nao configurado no PNH_Core_Settings.json");
            return;
        }

        string msg = "🛡️ **ALERTA ANTI-DUPE PNH** 🛡️\n";
        msg += "👤 **Jogador:** " + playerName + "\n";
        msg += "📦 **Item Excluído:** " + itemType + "\n";
        msg += "🔑 **ID:** `" + pID + "`\n";
        msg += "⚠️ *Removido automaticamente pelo sistema.*";

        Print("[PNH GUARD] A enviar alerta para o Discord...");
        PNH_DiscordManager.SendMessage(msg, "Admin");
    }

    static void SimulateAlert(PlayerBase player, string fakeItem)
    {
        string name = "Stress_Test_User";
        if (player && player.GetIdentity()) name = player.GetIdentity().GetName();
        
        TriggerDiscordAlert(name, fakeItem, "DEBUG_STRESS_ID_123");
    }

    static void RemoveFromTracking(EntityAI entity)
    {
        if (!entity) return;
        string pID = GetIDString(entity);
        if (m_TrackedIDs.Contains(pID)) m_TrackedIDs.Remove(pID);
    }

    private static string GetIDString(EntityAI entity)
    {
        int i1, i2, i3, i4;
        entity.GetPersistentID(i1, i2, i3, i4);
        return i1.ToString() + "_" + i2.ToString() + "_" + i3.ToString() + "_" + i4.ToString();
    }

    static void ClearCache()
    {
        m_TrackedIDs.Clear();
    }
}