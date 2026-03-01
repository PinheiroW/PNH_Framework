/**
 * MOD: PNH_Core
 * FILE: PNH_CoreConfig.c
 */

class PNH_CoreSettings
{
    string SystemWebhookURL = "";   
    string AdminWebhookURL = "";    
    string ChatWebhookURL = "";     
    string LoginWebhookURL = "";    
    string WelcomeWebhookURL = "";
    string MissionsWebhookURL = ""; 
    
    bool DebugMode = true;
    bool AntiDupeActive = true; 
    float BroadcastIntervalMin = 10.0;
    ref array<string> BroadcastMessages; 
    ref array<string> SuperAdmins;

    void PNH_CoreSettings()
    {
        BroadcastMessages = new array<string>;
        BroadcastMessages.Insert("Bem-vindo ao PNH Core 2.0!");
        SuperAdmins = new array<string>;
    }
}

class PNH_CoreConfig
{
    private static ref PNH_CoreSettings m_Settings;
    private static const string CONFIG_PATH = "$profile:PNH_Core/PNH_Core_Settings.json";

    static void Load()
    {
        m_Settings = new PNH_CoreSettings();
        if (!FileExist("$profile:PNH_Core/")) MakeDirectory("$profile:PNH_Core/");

        if (FileExist(CONFIG_PATH))
        {
            JsonFileLoader<PNH_CoreSettings>.JsonLoadFile(CONFIG_PATH, m_Settings);
            PNH_Logger.Log("Config", "Configuracoes Carregadas.");
        }
        else
        {
            Save();
        }
    }

    static void Save()
    {
        JsonFileLoader<PNH_CoreSettings>.JsonSaveFile(CONFIG_PATH, m_Settings);
    }

    static PNH_CoreSettings Get()
    {
        if (!m_Settings) Load();
        return m_Settings;
    }
}