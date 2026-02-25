/**
 * MOD: PNH_Core
 * FILE: MissionServer.c
 */

modded class MissionServer
{
    ref PNH_BroadcastManager m_PnhBroadcast;
    ref map<string, ref PNH_PlayerProfile> m_OnlineProfiles;

    override void OnInit()
    {
        super.OnInit();
        PNH_Logger.Init();
        PNH_CoreConfig.Load(); 
        m_PnhBroadcast = new PNH_BroadcastManager();
        m_OnlineProfiles = new map<string, ref PNH_PlayerProfile>();
        
        PNH_Guard.ClearCache();

        PNH_RpcManager.Get().Register(9992, this, "HandleGlobalRadio");
        PNH_RpcManager.Get().Register(9993, this, "HandleAdminCommands");
        PNH_RpcManager.Get().Register(9994, this, "HandleRadioToggle");

        PNH_Logger.Log("Core", "PNH Core 2.0 :: Sistemas Inicializados.");
    }

    override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity)
    {
        super.InvokeOnConnect(player, identity);
        if (!player || !identity) return;

        string steamID = identity.GetPlainId();
        ref PNH_PlayerProfile profile = PNH_Persistence.LoadProfile(steamID);
        
        profile.JoinCount++;
        m_OnlineProfiles.Insert(steamID, profile);
        PNH_Persistence.SaveProfile(profile);
    }

    override void InvokeOnDisconnect(PlayerBase player)
    {
        super.InvokeOnDisconnect(player);
        if (player && player.GetIdentity())
        {
            string steamID = player.GetIdentity().GetPlainId();
            if (m_OnlineProfiles.Contains(steamID))
            {
                PNH_Persistence.SaveProfile(m_OnlineProfiles.Get(steamID));
                m_OnlineProfiles.Remove(steamID);
            }
        }
    }

    void HandleAdminCommands(ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        Param1<string> data;
        if (!ctx.Read(data)) return;
        if (!sender || !PNH_PlayerUtils.IsAdminIdentity(sender)) return;

        string command = data.param1;
        PlayerBase player = PlayerBase.Cast(sender.GetPlayer());

        if (command == "!reload")
        {
            PNH_CoreConfig.Load();
            if (player) PNH_PlayerUtils.NotifyPlayer(player, "Configs Recarregadas!");
        }
        else if (command == "!debug")
        {
            string info = "Admin: OK | Perfis Online: " + m_OnlineProfiles.Count();
            if (player) PNH_PlayerUtils.NotifyPlayer(player, info);
        }
        else if (command == "!stress")
        {
            if (!player) return;
            
            PNH_PlayerUtils.NotifyPlayer(player, "A iniciar Stress Test: 50x M4A1_Green...");
            
            vector pos = player.GetPosition();
            for (int i = 0; i < 50; i++)
            {
                // Cria dispersão para as armas não ficarem no mesmo ponto exato
                vector spawnPos = pos;
                spawnPos[0] = spawnPos[0] + Math.RandomFloat(-3, 3);
                spawnPos[2] = spawnPos[2] + Math.RandomFloat(-3, 3);
                
                GetGame().CreateObjectEx("M4A1_Green", spawnPos, ECE_PLACE_ON_SURFACE);
            }
            
            PNH_Guard.SimulateAlert(player, "M4A1_Green_Stress");
            PNH_PlayerUtils.NotifyPlayer(player, "Teste finalizado. Verifique o chao e o Discord.");
        }
    }

    void HandleRadioToggle(ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if (!sender) return;
        string steamID = sender.GetPlainId();
        if (m_OnlineProfiles.Contains(steamID))
        {
            PNH_PlayerProfile profile = m_OnlineProfiles.Get(steamID);
            profile.IsRadioMuted = !profile.IsRadioMuted;
            PNH_Persistence.SaveProfile(profile);
            
            PlayerBase p = PlayerBase.Cast(sender.GetPlayer());
            string status = "LIGADO";
            if (profile.IsRadioMuted) status = "MUTADO";
            if (p) PNH_PlayerUtils.NotifyPlayer(p, "Radio: " + status);
        }
    }

    void HandleGlobalRadio(ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        Param1<string> data;
        if (!ctx.Read(data)) return;
        GetGame().ChatPlayer("[RADIO] " + sender.GetName() + ": " + data.param1);
    }

    override void OnUpdate(float timeslice)
    {
        super.OnUpdate(timeslice);
        if (m_PnhBroadcast) m_PnhBroadcast.Update(timeslice);
    }
}